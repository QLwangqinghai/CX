
#include "XHashTable.h"

static inline size_t __XHashTablePageCapacityExponentRoundUp(size_t count) {
    if (count == 0) {
        return 3;
    }
    const size_t one = 1;
    size_t e = SIZE_BITS_COUNT - USizeLeadingZerosCount(count);
    size_t shift = (count == (one << e)) ? e : (e + 1);
    shift = (shift + 1) >> 1;
    return MAX(shift, 3);
}
static inline size_t __XHashTablePageCapacityExponentRoundDown(size_t count) {
    size_t shift = __XHashTablePageCapacityExponentRoundUp(count) - 1;
    return MAX(shift, 3);
}

size_t XImmutableHashTableBucketCount(size_t elementCount, size_t * _Nonnull shift) {
    XAssert(shift, "");
    if (0 == elementCount) {
        *shift = SIZE_BITS_COUNT - 1;
        return 0;
    } else {
        const size_t one = 1;
        size_t tmpE = SIZE_BITS_COUNT - USizeLeadingZerosCount(elementCount);
        size_t e = (elementCount == (one << tmpE)) ? tmpE : (tmpE + 1);
        *shift = e;
        return one << e;
    }
}

int __XMutableHashTableCompareToHashCode(void * _Nonnull element, void * _Nonnull target, void * _Nullable context) {
    const XHashElementType_s * elementType = context;
    size_t elementHashCode = elementType->getKeyHashCode(element);
    size_t hashCode = *(size_t *)target;
    if (elementHashCode < hashCode) {
        return -1;
    } else if (elementHashCode > hashCode) {
        return 1;
    } else {
        return 0;
    }
}

void XImmutableHashTableDeinit(XImmutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit) {
    XAssert(deinit, "");
    size_t elementSize = elementType->size;
    ssize_t * bucketIndexs = (ssize_t *)table->payload;
    uint8_t * elements = (uint8_t *)(bucketIndexs + table->bucketCount);
    for (ssize_t index=0; index<table->count; index++) {
        uint8_t * element = elements + index * elementSize;
        deinit(element);
    }
    *(ssize_t *)&(table->count) = 0;
}

ssize_t XImmutableHashTableGetCount(XImmutableHashTable_s * _Nonnull table) {
    return table->count;
}

/// return unretained object
bool_t XImmutableHashTableGetElement(XImmutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer) {
    XAssert(keyBuffer, "");
    XAssert(elementBuffer, "");
    
    if (table->count <= 0) {
        return false;
    }
    
    size_t elementSize = elementType->size;
    ssize_t * bucketIndexs = (ssize_t *)table->payload;
    uint8_t * elements = (uint8_t *)(bucketIndexs + table->bucketCount);
    
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    ssize_t bucketIndex = hashCode >> table->bucketIndexShift;
    ssize_t start = bucketIndexs[bucketIndex];
    ssize_t end = table->count;
    if (bucketIndex != table->bucketCount - 1) {
        end = bucketIndexs[bucketIndex + 1];
    }
    
    ssize_t low = start;
    ssize_t high = end - 1;
    ssize_t location = -1;
    
    while (low <= high) {
        ssize_t mid = low + (high - low) / 2;
        uint8_t * element = elements + mid * elementSize;
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode > hashCode) {
            high = mid - 1;
        } else if (elementHashCode < hashCode) {
            low = mid + 1;
        } else {
            location = mid;
            if (elementType->isKeyMatch(element, keyBuffer)) {
                memcpy(elementBuffer, element, elementSize);
                return true;
            }
            break;
        }
    }
    if (location < 0) {
        return false;
    }
    
    // hash(node[location]) == hash(key)
    
    // location-1 -> low
    for (ssize_t index=location-1; index>=low; index--) {
        uint8_t * element = elements + index * elementSize;
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(element, keyBuffer)) {
                memcpy(elementBuffer, element, elementSize);
                return true;
            }
        } else {
            break;
        }
    }
    
    // location+1 -> high
    for (ssize_t index=location+1; index<=high; index++) {
        uint8_t * element = elements + index * elementSize;
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(element, keyBuffer)) {
                memcpy(elementBuffer, element, elementSize);
                return true;
            }
        } else {
            break;
        }
    }
    return false;
}

void XImmutableHashTableEnumerate(XImmutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context) {
    XAssert(func, "");
    
    size_t elementSize = elementType->size;
    ssize_t * bucketIndexs = (ssize_t *)table->payload;
    uint8_t * elements = (uint8_t *)(bucketIndexs + table->bucketCount);
    bool_t stop = false;
    for (ssize_t index=0; index<table->count; index++) {
        uint8_t * element = elements + index * elementSize;
        func(index, element, subfunc, context, &stop);
        if (stop) {
            return;
        }
    }
}




XMutableHashTable_s * _Nonnull XMutableHashTableCreate(XClassRef _Nonnull class, XObjectOption option, const XHashElementType_s * _Nonnull elementType, ssize_t capacity) {
    XMutableHashTable_s * result = (XMutableHashTable_s *)XObjectAllocate(class, option, sizeof(XMutableHashTable_s), __XCollectionLayoutMutable);
    result->count = 0;
    
    if (capacity > 0) {
        const size_t one = 1;
        size_t pageCapacityExponent = __XHashTablePageCapacityExponentRoundUp(capacity);
        size_t bucketCount = one << pageCapacityExponent;
        size_t bucketIndexShift = SIZE_BITS_COUNT - pageCapacityExponent;
        XDeque_s * _Nullable storage = XAllocate(sizeof(XDeque_s) * bucketCount);
        for (ssize_t i=0; i<bucketCount; i++) {
            XDeque_s * target = storage + i;
            XDequeInit(target, elementType->size, 0);
        }
        result->bucketCount = bucketCount;
        result->bucketIndexShift = bucketIndexShift;
        result->pageCapacityExponent = pageCapacityExponent;
        result->storage = storage;
    } else {
        size_t pageCapacityExponent = 3;
        size_t bucketIndexShift = SIZE_BITS_COUNT - pageCapacityExponent;
        result->bucketCount = 0;
        result->bucketIndexShift = bucketIndexShift;
        result->pageCapacityExponent = pageCapacityExponent;
        result->storage = NULL;
    }
    return result;
}
void XMutableHashTableDeinit(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit) {
    ssize_t count = 0;
    XAssert(deinit, "");
    for (size_t bucketIndex=0; bucketIndex<table->bucketCount; bucketIndex++) {
        XDeque_s * bucket = table->storage + bucketIndex;
        size_t dcount = XDequeGetCount(bucket);
        for (ssize_t index=0; index<dcount; index++) {
            void * element = XDequeElementAtIndex(bucket, index);
            deinit(element);
            count += 1;
        }
        XDequeDeinit(bucket);
    }
    XAssert(count == table->count, "");
    if (table->storage) {
        XDeallocate(table->storage);
        table->storage = NULL;
        table->bucketCount = 0;
    }
    table->count = 0;
}

ssize_t XMutableHashTableGetCount(XMutableHashTable_s * _Nonnull table) {
    return table->count;
}

bool_t XMutableHashTableGetElement(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer) {
    if (table->count <= 0) {
        return false;
    }
    XAssert(keyBuffer, "");
    XAssert(elementBuffer, "");
    XAssert(table->storage, "");
    
    size_t elementSize = elementType->size;
    XDeque_s * storage = table->storage;
    
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    ssize_t bucketIndex = hashCode >> table->bucketIndexShift;
    
    XDeque_s * bucket = storage + bucketIndex;
    ssize_t low = 0;
    ssize_t high = XDequeGetCount(bucket) - 1;
    ssize_t location = -1;
    
    while (low <= high) {
        ssize_t mid = low + (high - low) / 2;
        void * element = XDequeElementAtIndex(bucket, mid);
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode > hashCode) {
            high = mid - 1;
        } else if (elementHashCode < hashCode) {
            low = mid + 1;
        } else {
            location = mid;
            if (elementType->isKeyMatch(element, keyBuffer)) {
                memcpy(elementBuffer, element, elementSize);
                return true;
            }
            break;
        }
    }
    if (location < 0) {
        return false;
    }
    
    // hash(node[location]) == hash(key)
    // location-1 -> low
    for (ssize_t index=location-1; index>=low; index--) {
        void * element = XDequeElementAtIndex(bucket, index);
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(element, keyBuffer)) {
                memcpy(elementBuffer, element, elementSize);
                return true;
            }
        } else {
            break;
        }
    }
    
    // location+1 -> high
    for (ssize_t index=location+1; index<=high; index++) {
        void * element = XDequeElementAtIndex(bucket, index);
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(element, keyBuffer)) {
                memcpy(elementBuffer, element, elementSize);
                return true;
            }
        } else {
            break;
        }
    }
    return false;
}

void __XMutableHashTableResize(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, size_t pageCapacityExponent) {
    const size_t one = 1;
    size_t bucketCount = one << pageCapacityExponent;
    size_t bucketIndexShift = SIZE_BITS_COUNT - pageCapacityExponent;
    
    if (table->bucketCount == 0) {
        XAssert(NULL == table->storage, "");
        XDeque_s * _Nullable storage = XAllocate(sizeof(XDeque_s) * bucketCount);
        for (ssize_t i=0; i<bucketCount; i++) {
            XDeque_s * target = storage + i;
            XDequeInit(target, elementType->size, 0);
        }
        table->bucketCount = bucketCount;
        table->bucketIndexShift = bucketIndexShift;
        table->pageCapacityExponent = pageCapacityExponent;
        table->storage = storage;
        return;
    }
    if (bucketCount == table->bucketCount) {
        return;
    }
    XDeque_s * _Nullable storage = XAllocate(sizeof(XDeque_s) * bucketCount);
    if (bucketCount < table->bucketCount) {
        // 合并
        size_t stepLength = table->bucketCount / bucketCount;
        for (ssize_t i=0; i<bucketCount; i++) {
            XDeque_s * target = storage + i;
            ssize_t count = 0;
            for (ssize_t sidx=0; sidx<stepLength; sidx++) {
                XDeque_s * src = table->storage + (i * stepLength) + sidx;
                count += XDequeGetCount(src);
            }
            XDequeInit(target, elementType->size, count);
            for (ssize_t sidx=0; sidx<stepLength; sidx++) {
                XDeque_s * src = table->storage + (i * stepLength) + sidx;
                ssize_t dcount = XDequeGetCount(src);
                for (ssize_t itemIndex=0; itemIndex<dcount; itemIndex++) {
                    XDequeAppendElement(target, elementType->size, XDequeElementAtIndex(src, itemIndex));
                }
            }
        }
    } else {
        // 分裂
        size_t stepLength = bucketCount / table->bucketCount;
        for (ssize_t sbi=0; sbi<table->bucketCount; sbi++) {
            XDeque_s * src = table->storage + sbi;
            
            if (NULL == src->buffer) {
                for (ssize_t dbioffset=0; dbioffset<stepLength; dbioffset++) {
                    XDeque_s * target = storage + sbi * stepLength + dbioffset;
                    XDequeInit(target, elementType->size, 0);
                }
            } else {
                size_t srcStartIndex = 0;
                for (ssize_t dbioffset=0; dbioffset<stepLength; dbioffset++) {
                    XDeque_s * target = storage + sbi * stepLength + dbioffset;
                    
                    // bsearchIndexOfEnd
                    size_t srcEndIndex = 0;
                    XDequeInit(target, elementType->size, srcEndIndex - srcStartIndex);
                    for (ssize_t itemIndex=srcStartIndex; itemIndex<srcEndIndex; itemIndex++) {
                        XDequeAppendElement(target, elementType->size, XDequeElementAtIndex(src, itemIndex));
                    }
                    srcStartIndex = srcEndIndex;
                }
            }
        }
    }
    
    XDeque_s * oldStorage = table->storage;
    size_t oldBucketCount = table->bucketCount;
    table->bucketCount = bucketCount;
    table->bucketIndexShift = bucketIndexShift;
    table->pageCapacityExponent = pageCapacityExponent;
    table->storage = storage;
    for (size_t i=0; i<oldBucketCount; i++) {
        XDeque_s * src = oldStorage + i;
        XDequeDeinit(src);
    }
    XDeallocate(oldStorage);
}
void __XMutableHashTableInsert(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, size_t bucketIndex, size_t index, const void * _Nonnull elementBuffer) {
    XDeque_s * bucket = table->storage + bucketIndex;
    XDequeInsertElement(bucket, elementType->size, index, elementBuffer);
    table->count += 1;
    
    size_t pageCapacityExponent = __XHashTablePageCapacityExponentRoundUp(table->count);
    if (__XHashTablePageCapacityExponentRoundUp(table->count) > pageCapacityExponent) {
        // resize
        __XMutableHashTableResize(table, elementType, pageCapacityExponent);
    }
}
void __XMutableHashTableRemove(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, size_t bucketIndex, size_t index, bool_t allowReduceCapacity, void * _Nonnull old) {
    XDeque_s * bucket = table->storage + bucketIndex;
    XDequeRemoveElement(bucket, elementType->size, index, allowReduceCapacity, old);
    table->count -= 1;

    if (allowReduceCapacity) {
        const size_t one = 1;
        size_t pageCapacityExponent = __XHashTablePageCapacityExponentRoundUp(table->count);
        size_t pageCapacity = one << pageCapacityExponent;
        
        if (table->pageCapacityExponent != pageCapacityExponent && table->count < pageCapacity * (pageCapacity / 4 * 3)) {
            // do resize
            __XMutableHashTableResize(table, elementType, pageCapacityExponent);
        }
    }
}

// update value, 如果有oldElement， 返回true
bool_t XMutableHashTableReplace(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull elementBuffer, void * _Nullable oldElementBuffer) {
    XAssert(elementBuffer, "");
    XAssert(oldElementBuffer, "");
    
    if (0 == table->bucketCount) {
        XAssert(0 == table->count, "");
        size_t pageCapacityExponent = __XHashTablePageCapacityExponentRoundUp(1);
        __XMutableHashTableResize(table, elementType, pageCapacityExponent);
    } else {
        XAssert(table->storage, "");
    }
    
    void * keyBuffer = elementBuffer;
    size_t elementSize = elementType->size;
    XDeque_s * storage = table->storage;
    
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    ssize_t bucketIndex = hashCode >> table->bucketIndexShift;
    XDeque_s * bucket = storage + bucketIndex;
    
    if (NULL == bucket->buffer) {
        __XMutableHashTableInsert(table, elementType, bucketIndex, 0, elementBuffer);
        return false;
    }
    ssize_t location = XIndexNotFound;
    if (XRingBufferBSearch(bucket->buffer, false, &hashCode, __XMutableHashTableCompareToHashCode, (void *)elementType, &location)) {
        // hash(node[location]) == hash(key)

        {
            void * element = XDequeElementAtIndex(bucket, location);
            if (elementType->isKeyMatch(element, keyBuffer)) {
                memcpy(oldElementBuffer, element, elementSize);
                memcpy(element, elementBuffer, elementSize);
                return true;
            }
        }
        
        // location - 1 -> low
        for (ssize_t index=location-1; index>=0; index--) {
            void * element = XDequeElementAtIndex(bucket, index);
            size_t elementHashCode = elementType->getKeyHashCode(element);
            if (elementHashCode == hashCode) {
                if (elementType->isKeyMatch(element, keyBuffer)) {
                    memcpy(oldElementBuffer, element, elementSize);
                    memcpy(element, elementBuffer, elementSize);
                    return true;
                }
            } else {
                break;
            }
        }
        
        // location+1 -> high
        for (ssize_t index=location+1; index<=XDequeGetCount(bucket); index++) {
            void * element = XDequeElementAtIndex(bucket, index);
            size_t elementHashCode = elementType->getKeyHashCode(element);
            if (elementHashCode == hashCode) {
                if (elementType->isKeyMatch(element, keyBuffer)) {
                    memcpy(oldElementBuffer, element, elementSize);
                    memcpy(element, elementBuffer, elementSize);
                    return true;
                }
            } else {
                break;
            }
        }
    }
    __XMutableHashTableInsert(table, elementType, bucketIndex, location, elementBuffer);
    return false;
//    size_t count = XDequeGetCount(bucket);
//    if (count <= 0) {
//        __XMutableHashTableInsert(table, elementType, bucketIndex, 0, elementBuffer);
//        return false;
//    } else if (count == 1) {
//        void * element = XDequeElementAtIndex(bucket, elementSize, 0);
//        size_t elementHashCode = elementType->getKeyHashCode(element);
//        if (elementHashCode > hashCode) {
//            __XMutableHashTableInsert(table, elementType, bucketIndex, 0, elementBuffer);
//            return false;
//        } else if (elementHashCode < hashCode) {
//            __XMutableHashTableInsert(table, elementType, bucketIndex, 1, elementBuffer);
//            return false;
//        } else {
//            if (elementType->isKeyMatch(element, keyBuffer)) {
//                memcpy(oldElementBuffer, element, elementSize);
//                memcpy(element, elementBuffer, elementSize);
//                return true;
//            } else {
//                __XMutableHashTableInsert(table, elementType, bucketIndex, 1, elementBuffer);
//                return false;
//            }
//        }
//    } else {
//        ssize_t low = 0;
//        ssize_t high = count - 1;
//        ssize_t location = -1;
//        {
//            void * element = XDequeElementAtIndex(bucket, elementSize, low);
//            size_t elementHashCode = elementType->getKeyHashCode(element);
//            if (elementHashCode > hashCode) {
//                __XMutableHashTableInsert(table, elementType, bucketIndex, 0, elementBuffer);
//                return false;
//            } else if (elementHashCode == hashCode) {
//                location = 0;
//            }
//        }
//        {
//            void * element = XDequeElementAtIndex(bucket, elementSize, high);
//            size_t elementHashCode = elementType->getKeyHashCode(element);
//            if (elementHashCode < hashCode) {
//                __XMutableHashTableInsert(table, elementType, bucketIndex, count, elementBuffer);
//                return false;
//            } else if (elementHashCode == hashCode) {
//                location = high;
//            }
//        }
//
//        while (location < 0 && low < high) {
//            ssize_t mid = low + (high - low) / 2;
//            void * element = XDequeElementAtIndex(bucket, elementSize, mid);
//            size_t elementHashCode = elementType->getKeyHashCode(element);
//            if (mid == low) {
//                XAssert(elementHashCode < hashCode, "");
//                location = mid + 1;
//                break;
//            }
//
//            if (elementHashCode > hashCode) {
//                high = mid;
//            } else if (elementHashCode < hashCode) {
//                low = mid;
//            } else {
//                location = mid;
//                break;
//            }
//        }
//        if (location < 0) {
//            return false;
//        }
//
//        {
//            void * element = XDequeElementAtIndex(bucket, elementSize, location);
//            size_t elementHashCode = elementType->getKeyHashCode(element);
//
//            if (elementHashCode > hashCode) {
//                __XMutableHashTableInsert(table, elementType, bucketIndex, location, elementBuffer);
//                return false;
//            } else if (elementHashCode < hashCode) {
//                abort();
//            } else {
//                if (elementType->isKeyMatch(element, keyBuffer)) {
//                    memcpy(oldElementBuffer, element, elementSize);
//                    memcpy(element, elementBuffer, elementSize);
//                    return true;
//                }
//
//                // hash(node[location]) == hash(key)
//                // location-1 -> low
//                for (ssize_t index=location-1; index>=low; index--) {
//                    void * element = XDequeElementAtIndex(bucket, elementSize, index);
//                    size_t elementHashCode = elementType->getKeyHashCode(element);
//                    if (elementHashCode == hashCode) {
//                        if (elementType->isKeyMatch(element, keyBuffer)) {
//                            memcpy(elementBuffer, element, elementSize);
//                            return true;
//                        }
//                    } else {
//                        break;
//                    }
//                }
//
//                // location+1 -> high
//                for (ssize_t index=location+1; index<=high; index++) {
//                    void * element = XDequeElementAtIndex(bucket, elementSize, index);
//                    size_t elementHashCode = elementType->getKeyHashCode(element);
//                    if (elementHashCode == hashCode) {
//                        if (elementType->isKeyMatch(element, keyBuffer)) {
//                            memcpy(elementBuffer, element, elementSize);
//                            return true;
//                        }
//                    } else {
//                        __XMutableHashTableInsert(table, elementType, bucketIndex, index, elementBuffer);
//                        return false;
//                    }
//                }
//            }
//        }
//        return false;
//    }
}



// 如果有oldElement， 返回true
bool_t XMutableHashTableRemove(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, bool_t allowReduceCapacity, void * _Nullable oldElementBuffer) {
    if (table->count <= 0) {
        return false;
    }
    XAssert(keyBuffer, "");
    XAssert(oldElementBuffer, "");
    XAssert(table->storage, "");
    
    XDeque_s * storage = table->storage;
    
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    ssize_t bucketIndex = hashCode >> table->bucketIndexShift;
    XDeque_s * bucket = storage + bucketIndex;
    if (NULL == bucket->buffer) {
        return false;
    }
    ssize_t location = XIndexNotFound;
    if (XRingBufferBSearch(bucket->buffer, false, &hashCode, __XMutableHashTableCompareToHashCode, (void *)elementType, &location)) {
        if (elementType->isKeyMatch(XDequeElementAtIndex(bucket, location), keyBuffer)) {
            __XMutableHashTableRemove(table, elementType, bucketIndex, location, allowReduceCapacity, oldElementBuffer);
            // resize if needs
            
            return true;
        }
        
        // hash(node[location]) == hash(key)
        // location - 1 -> low
        for (ssize_t index=location-1; index>=0; index--) {
            void * element = XDequeElementAtIndex(bucket, index);
            size_t elementHashCode = elementType->getKeyHashCode(element);
            if (elementHashCode == hashCode) {
                if (elementType->isKeyMatch(element, keyBuffer)) {
                    __XMutableHashTableRemove(table, elementType, bucketIndex, location, allowReduceCapacity, oldElementBuffer);
                    // resize if needs

                    return true;
                }
            } else {
                break;
            }
        }
        
        // location+1 -> high
        for (ssize_t index=location+1; index<=XDequeGetCount(bucket); index++) {
            void * element = XDequeElementAtIndex(bucket, index);
            size_t elementHashCode = elementType->getKeyHashCode(element);
            if (elementHashCode == hashCode) {
                if (elementType->isKeyMatch(element, keyBuffer)) {
                    __XMutableHashTableRemove(table, elementType, bucketIndex, location, allowReduceCapacity, oldElementBuffer);
                    
                    // resize if needs

                    return true;
                }
            } else {
                break;
            }
        }
    }
    return false;
}

typedef struct {
    ssize_t count;
    const XHashElementType_s * _Nonnull elementType;
    ssize_t * _Nonnull bucketIndexs;
    uint8_t * _Nonnull elements;
    void (* _Nonnull copyElement)(void * _Nonnull dst, const void * _Nonnull src);
} XMutableHashTableRemoveAllContext_s;

void __XMutableHashTableRemoveAllEnumerate(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable _context, bool_t * _Nonnull stop) {
    XMutableHashTableRemoveAllContext_s * context = (XMutableHashTableRemoveAllContext_s *)_context;
    uint8_t * dst = context->elements + context->elementType->size * context->count;
    memcpy(dst, element, context->elementType->size);
    memset(element, 0, context->elementType->size);
    context->count += 1;
}
XImmutableHashTable_s * _Nonnull XMutableHashTableRemoveAll(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t allowReduceCapacity, XObjectOption option) {
    ssize_t count = XMutableHashTableGetCount(table);

    size_t bucketIndexShift = 0;
    size_t bucketCount = XImmutableHashTableBucketCount(count, &bucketIndexShift);
    size_t size = sizeof(XImmutableHashTable_s) + sizeof(ssize_t) * bucketCount + elementType->size * count;
    XImmutableHashTable_s * result = (XImmutableHashTable_s *)XObjectAllocate(XObjectGetClass(table), option, size, __XCollectionLayoutImmutable);
    *(ssize_t *)&(result->count) = count;
    result->bucketCount = bucketCount;
    result->bucketIndexShift = bucketIndexShift;
    atomic_store(&(result->_hashCode), 0);
    
    uint8_t * elements = (uint8_t *)((ssize_t *)result->payload + bucketCount);

    XMutableHashTableRemoveAllContext_s context = {
        .bucketIndexs = (ssize_t *)result->payload,
        .elements = (uint8_t *)((ssize_t *)result->payload + bucketCount),
        .elementType = elementType,
        .count = 0,
    };
    XMutableHashTableEnumerate(table, elementType, __XMutableHashTableRemoveAllEnumerate, NULL, &context);
    XAssert(context.count == count, "");
    
    size_t bucketIndex = 0;
    uint64_t endHashCode = (bucketIndex + 1) << bucketIndexShift;
    context.bucketIndexs[0] = 0;
    for (size_t idx = 0; idx < count; idx++) {
        size_t hashCode = elementType->getKeyHashCode(context.elements + idx * elementType->size);
        while (hashCode >= endHashCode) {
            context.bucketIndexs[bucketIndex] = idx;
            bucketIndex += 1;
            endHashCode = (bucketIndex + 1) << bucketIndexShift;
        }
    }
    for (; bucketIndex < bucketCount; bucketIndex++) {
        context.bucketIndexs[bucketIndex] = count;
    }
    
    ssize_t removedCount = 0;
    XDeque_s * storage = table->storage;
    for (size_t bucketIndex=0; bucketIndex<table->bucketCount; bucketIndex++) {
        XDeque_s * bucket = storage + bucketIndex;
        removedCount += XDequeRemoveAll(bucket, elementType->size, allowReduceCapacity, elements + removedCount * elementType->size);
    }
    table->count = 0;
    
    // rehashtable
    
    return result;
}

void XMutableHashTableEnumerate(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context) {
    XDeque_s * storage = table->storage;
    bool_t stop = false;
    ssize_t eIndex = 0;
    for (size_t bucketIndex=0; bucketIndex<table->bucketCount; bucketIndex++) {
        XDeque_s * bucket = storage + bucketIndex;
        size_t count = XDequeGetCount(bucket);
        for (ssize_t index=0; index<count; index++) {
            void * element = XDequeElementAtIndex(bucket, index);
            func(eIndex, element, subfunc, context, &stop);
            eIndex += 1;
            if (stop) {
                return;
            }
        }
    }
}

XImmutableHashTable_s * _Nonnull XMutableHashTableCopy(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XObjectOption option, _XHashElementElementCopy_f _Nonnull copy) {
    XAssert(copy, "");
    ssize_t count = XMutableHashTableGetCount(table);
    size_t elementSize = elementType->size;
    size_t bucketIndexShift = 0;
    size_t bucketCount = XImmutableHashTableBucketCount(count, &bucketIndexShift);
    size_t size = sizeof(XImmutableHashTable_s) + sizeof(ssize_t) * bucketCount + elementSize * count;
    XImmutableHashTable_s * result = (XImmutableHashTable_s *)XObjectAllocate(XObjectGetClass(table), option, size, __XCollectionLayoutImmutable);
    *(ssize_t *)&(result->count) = count;
    result->bucketCount = bucketCount;
    result->bucketIndexShift = bucketIndexShift;
    atomic_store(&(result->_hashCode), 0);
    
    // 先存个数， 再转化成开始的index
    ssize_t * bucketIndexs = (ssize_t *)result->payload;
    uint8_t * elements = (uint8_t *)(bucketIndexs + bucketCount);

    for (ssize_t bucketIndex=0; bucketIndex < bucketCount; bucketIndex++) {
        bucketIndexs[bucketIndex] = 0;
    }
    
    ssize_t eIndex = 0;
    for (size_t chuckId=0; chuckId<table->bucketCount; chuckId++) {
        XDeque_s * bucket = table->storage + chuckId;
        size_t count = XDequeGetCount(bucket);
        for (ssize_t index=0; index<count; index++) {
            void * item = XDequeElementAtIndex(bucket, index);
            copy(elements + elementType->size * eIndex, item);
            eIndex += 1;
            size_t hashCode = elementType->getKeyHashCode(item);
            bucketIndexs[(hashCode >> bucketIndexShift)] += 1;
        }
    }
    
    ssize_t endIndex = 0;
    for (ssize_t bucketIndex=0; bucketIndex < bucketCount; bucketIndex++) {
        ssize_t itemCount = bucketIndexs[bucketIndex];
        bucketIndexs[bucketIndex] = endIndex;
        endIndex = eIndex + itemCount;
    }
    return result;
}

void XMutableHashTableResize(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, ssize_t minCapacity) {
    size_t pageCapacityExponent = __XHashTablePageCapacityExponentRoundUp(minCapacity);
    if (table->bucketCount == 0 || table->pageCapacityExponent < pageCapacityExponent) {
        // resize
        __XMutableHashTableResize(table, elementType, pageCapacityExponent);
    }
}
































//
//#include "XRCollectionInternal.h"
//#include "XClassInternal.h"
//#include "XRuntimeInternal.h"
//#include "XMemory.h"
//
//const _XRBuffer _XRBufferByteEmpty = {
//    ._runtime = _XConstantRefBaseMake(X_BUILD_TypeId_XRBuffer),
//    .content = {
//        .elementSize = 1,
//        .capacity = 0,
//        .count = 0,
//    },
//};
//
//const XRBuffer XRBufferByteEmpty = (XRBuffer)&_XRBufferByteEmpty;
//
//size_t XRBufferHeaderSize(void) {
//    return sizeof(_XRBuffer);
//}
//
//XBufferSlice _XRBufferGetSliceWithRange(XBufferContent_s * _Nonnull content, XRange_s range) {
//    XBufferSlice result = {};
//    if (content->capacity > 0) {
//        XIndex location = range.location;
//        XBufferSlice * s0 = &result;
//        XAssert(content->capacity >= content->count, "");
//        s0->baseIndex = range.location;
//        s0->count = range.length;
//        s0->payload = content->payload + (content->elementSize * location);
//        s0->capacity = s0->count;
//    }
//    return result;
//}
//
//XBufferSlice _XRBufferGetSlice(XBufferContent_s * _Nonnull content) {
//    return _XRBufferGetSliceWithRange(content, XRangeMake(0, content->count));
//}
//
//XBufferSlice XRBufferGetSlice(XRef _Nonnull ref) {
//    _XRBuffer * buffer = _XHeapObjectAs(ref, XRTypeRBuffer, __func__);
//    XBufferContent_s * content = &(buffer->content);
//    return _XRBufferGetSlice(content);
//}
//
//XBufferContent_s * _Nonnull _XRBufferGetContent(XRef _Nonnull ref) {
//    _XRBuffer * buffer = _XHeapObjectAs(ref, XRTypeRBuffer, __func__);
//    return &(buffer->content);
//}
//
//XRBuffer _Nonnull XRBufferCreate(XObjectOption flag, size_t capacity, size_t elementSize) {
//    XAssert(elementSize > 0, "");
//    XAssert(elementSize <= UINT32_MAX, "too large");
//    XAssert(capacity <= UINT32_MAX, "too large");
//    XAssert(UINT_MAX / elementSize > capacity, "");
//    size_t payloadSize = capacity * elementSize;
//    _XRBuffer * buffer = (_XRBuffer *)_XRAllocate(XClassIdRBuffer, sizeof(_XRBuffer) + payloadSize, flag);
//    buffer->content.elementSize = elementSize;
//    buffer->content.capacity = capacity;
//    buffer->content.count = 0;
//    return buffer;
//}
//XRBuffer _Nonnull XRBufferCreateWithBytes(XObjectOption flag, size_t capacity, const uint8_t * _Nullable byte, size_t count) {
//    XAssert(capacity <= UINT32_MAX, "too large");
//    if (capacity == 0) {
//        return XRBufferByteEmpty;
//    }
//    XAssert(capacity >= count, "");
//    if (count > 0) {
//        XAssert(byte, "");
//    }
//    _XRBuffer * buffer = (_XRBuffer *)_XRAllocate(XClassIdRBuffer, sizeof(_XRBuffer) + capacity, flag);
//    buffer->content.elementSize = 1;
//    buffer->content.capacity = capacity;
//    buffer->content.count = count;
//    if (count > 0) {
//        memcpy(buffer->content.payload, byte, count);
//    }
//    return buffer;
//}
//
//XRBuffer _Nonnull XRBufferRecapacity(XRBuffer _Nonnull ref, XObjectOption flag, size_t capacity) {
//    XBufferContent_s * content = _XRBufferGetContent(ref);
//    size_t elementSize = content->elementSize;
//    XAssert(elementSize > 0, "");
//    XAssert(elementSize <= UINT32_MAX, "too large");
//    XAssert(capacity <= UINT32_MAX, "too large");
//    XAssert(UINT_MAX / elementSize > capacity, "");
//    size_t payloadSize = capacity * elementSize;
//    _XRBuffer * buffer = (_XRBuffer *)_XRAllocate(XClassIdRBuffer, sizeof(_XRBuffer) + payloadSize, flag);
//    buffer->content.elementSize = elementSize;
//    buffer->content.capacity = capacity;
//    buffer->content.count = content->count;
//    memcpy(buffer->content.payload, content->payload, content->count * elementSize);
//    return buffer;
//}
//size_t XRBufferGetElementSize(XRef _Nonnull ref) {
//    _XRBuffer * buffer = _XHeapObjectAs(ref, XRTypeRBuffer, __func__);
//    return buffer->content.elementSize;
//}
//size_t XRBufferGetCount(XRef _Nonnull ref) {
//    _XRBuffer * buffer = _XHeapObjectAs(ref, XRTypeRBuffer, __func__);
//    return buffer->content.count;
//}
//void XRBufferSetCount(XRef _Nonnull ref, size_t count) {
//    _XRBuffer * buffer = _XHeapObjectAs(ref, XRTypeRBuffer, __func__);
//    buffer->content.count = count;
//}
//
//size_t XRBufferGetCapacity(XRef _Nonnull ref) {
//    _XRBuffer * buffer = _XHeapObjectAs(ref, XRTypeRBuffer, __func__);
//    return buffer->content.capacity;
//}
//
//XBuffer XRBufferGetContent(XRef _Nonnull ref) {
//    XBuffer rb = {};
//    _XRBuffer * buffer = _XHeapObjectAs(ref, XRTypeRBuffer, __func__);
//    rb.capacity = buffer->content.capacity;
//    rb.count = buffer->content.count;
//    if (rb.capacity == 0) {
//        rb.payload = NULL;
//    } else {
//        rb.payload = buffer->content.payload;
//    }
//    return rb;
//}
//
//XRef _Nonnull _XRBufferCopy(XRef _Nonnull ref) {
//    _XRBuffer * vector = (_XRBuffer *)ref;
//    size_fast_t _xinfo = atomic_load(&(vector->_runtime._xinfo));
//    XObjectOption flag = 0;
//    size_t payloadSize = vector->content.elementSize * vector->content.capacity;
//    _XRBuffer * buffer = (_XRBuffer *)_XRAllocate(XClassIdRBuffer, sizeof(_XRBuffer) + payloadSize, flag);
//    memcpy(&(buffer->content), &(vector->content), sizeof(XBufferContent_s));
//    if (payloadSize > 0) {
//        memcpy(buffer->content.payload, vector->content.payload, payloadSize);
//    }
//    return buffer;
//}
//
//void _XRBufferHash(XRef _Nonnull ref, XHasher _Nonnull hasher) {
//    XBufferContent_s * content = _XRBufferGetContent(ref);
//    XBufferSlice slice = _XRBufferGetSlice(content);
//    XHasherCombineBytes(hasher, slice.payload, slice.count * content->elementSize);
//}
//
//bool_t _XRBufferEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
//    if (lhs == rhs) {
//        return true;
//    } else {
//        XBufferContent_s * lv = _XRBufferGetContent(lhs);
//        XBufferContent_s * rv = _XRBufferGetContent(rhs);
//        if (lv->count == rv->count && lv->elementSize == rv->elementSize) {
//            if (lv->count == 0) {
//                return true;
//            }
//            XBufferSlice ls = _XRBufferGetSlice(lv);
//            XBufferSlice rs = _XRBufferGetSlice(rv);
//
//            if (XMemoryCompare(ls.payload, rs.payload, ls.count * lv->elementSize) != XCompareEqualTo) {
//                return false;
//            }
//            return true;
//        } else {
//            return false;
//        }
//    }
//};
//size_t _XRBufferDeinit(XRef _Nonnull ref, XRType _Nonnull type) {
//    _XRBuffer * vector = (_XRBuffer *)ref;
//    size_fast_t _xinfo = atomic_load(&(vector->_runtime._xinfo));
//    //    if ((_xinfo & X_BUILD_RC_Flag_ClearOnDealloc) == X_BUILD_RC_Flag_ClearOnDealloc) {
//    //        size_t payloadSize = vector->content.elementSize * vector->content.capacity;
//    //        memset(vector->content.payload, 0, payloadSize);
//    //    }
//    memset(&(vector->content), 0, sizeof(XBufferContent_s));
//
//    /// TODO: FIX
//    ///
//    abort();
//}
//void _XRBufferDescribe(XRef _Nonnull ref, _XDescriptionBuffer _Nonnull buffer) {}
//void _XRBufferDebugDescribe(XRef _Nonnull ref, _XDescriptionBuffer _Nonnull buffer) {}
//
//
//
//
////
////#include "XRBuffer.h"
////
////void XRBufferInit(XRBuffer _Nonnull ringBuffer, XElementType _Nonnull itemType, size_t capacity) {
////    XAssert(ringBuffer, "");
////    XAssert(itemType, "");
////    XAssert(capacity > 0, "");
////    ringBuffer->offset = 0;
////    ringBuffer->count = 0;
////    ringBuffer->capacity = capacity;
////    ringBuffer->itemType = itemType;
////
////
////
////}
////
////bool_t XRBufferIsFull(XRBuffer _Nonnull ringBuffer) {
////    XAssert(ringBuffer, "");
////    return ringBuffer->count >= ringBuffer->capacity;
////}
////bool_t XRBufferIsEmpty(XRBuffer _Nonnull ringBuffer) {
////    XAssert(ringBuffer, "");
////    return ringBuffer->count == 0;
////}
////size_t XRBufferGetCount(const XRBuffer _Nonnull ringBuffer) {
////    XAssert(ringBuffer, "");
////    return ringBuffer->count;
////}
////void XRBufferGetItem(const XRBuffer _Nonnull ringBuffer, XIndex index, XPtr _Nonnull item) {
////    XAssert(ringBuffer, "");
////    XAssert(item, "");
////    XAssert(index < ringBuffer->count, "");
////    size_t location = (ringBuffer->offset + index) % ringBuffer->capacity;
////    XPtr p = (XPtr)(ringBuffer->payload + location * ringBuffer->itemType->size);
////    memcpy(item, p, ringBuffer->itemType->size);
////}
////static inline void _XRBufferGetItems(const XRBuffer _Nonnull ringBuffer, XRange_s range, XPtr _Nonnull item) {
////    size_t location = (ringBuffer->offset + range.location) % ringBuffer->capacity;
////    XPtr p = (XPtr)(ringBuffer->payload + location * ringBuffer->itemType->size);
////    memcpy(item, p, ringBuffer->itemType->size);
////
////    // TODO : FIX memcpy
////}
////void XRBufferGetItems(const XRBuffer _Nonnull ringBuffer, XRange_s range, XPtr _Nonnull items) {
////    XAssert(ringBuffer, "");
////    XAssert(items, "");
////    XAssert(XRangeIsValid(range), "");
////    XAssert(range.location + range.length < ringBuffer->count, "");
////    _XRBufferGetItems(ringBuffer, range, items);
////}
////
////static inline void _XRBufferMoveForward(XRBuffer _Nonnull ringBuffer, XIndex startIndex, XIndex endIndex, XIndex count) {
////
////
////}
////static inline void _XRBufferMoveBackwards(XRBuffer _Nonnull ringBuffer, XIndex startIndex, XIndex endIndex, XIndex count) {
////
////
////}
////
////static inline void __XRBufferSetItems(XRBuffer _Nonnull ringBuffer, XIndex index, XPtr _Nonnull items, XIndex count) {
////
////
//////    if (newCount > 0) {
//////        XAssert(new, "");
//////    }
//////    size_t location = (ringBuffer->offset + index) % ringBuffer->capacity;
//////    XPtr p = (XPtr)(ringBuffer->payload + location * ringBuffer->itemType->size);
//////    if (old) {
//////        memcpy(old, p, ringBuffer->itemType->size);
//////    }
//////    memcpy(p, new, ringBuffer->itemType->size);
////}
////static inline void _XRBufferReplaceItems(XRBuffer _Nonnull ringBuffer, XRange_s range, XPtr _Nullable new, XIndex newCount, XPtr _Nullable old) {
////    if (NULL != old && range.length > 0) {
////        // copy old
////        _XRBufferGetItems(ringBuffer, range, old);
////    }
////    size_t oldCount = ringBuffer->count;
////    if (range.location >= oldCount / 2) {
////        // 移动后半部分
////        size_t ncount = oldCount - range.length + newCount;
////        size_t index = range.location + range.length;
////        if (ringBuffer->count < ncount) {
////            // 移动后半部分
////            ringBuffer->count = ncount;
////            _XRBufferMoveBackwards(ringBuffer, index, ringBuffer->count - index, ncount - ringBuffer->count);
////        } else if (ringBuffer->count > ncount) {
////            // 移动后半部分
////            _XRBufferMoveForward(ringBuffer, index, ringBuffer->count - index, ringBuffer->count - ncount);
////            ringBuffer->count = ncount;
////        }
////    } else {
////        // 移动前部分
////        size_t ncount = oldCount - range.length + newCount;
////        if (ringBuffer->count < ncount) {
////            // 移动前半部分
////            ringBuffer->count = ncount;
////            size_t deltaCount = ncount - ringBuffer->count;
////            ringBuffer->offset = ringBuffer->offset >= deltaCount ? (ringBuffer->offset - deltaCount) : (ringBuffer->capacity - deltaCount + ringBuffer->offset);
////
////            _XRBufferMoveForward(ringBuffer, deltaCount, deltaCount + range.location, deltaCount);
////        } else if (ringBuffer->count > ncount) {
////            // 移动前半部分
////            size_t deltaCount = ringBuffer->count - ncount;
////            _XRBufferMoveBackwards(ringBuffer, 0, range.location, ringBuffer->count - ncount);
////            ringBuffer->count = ncount;
////            ringBuffer->offset = (ringBuffer->offset + deltaCount) % ringBuffer->capacity;
////        }
////    }
////    __XRBufferSetItems(ringBuffer, range.location, new, newCount);
////}
////void XRBufferReplaceItem(XRBuffer _Nonnull ringBuffer, XIndex index, XPtr _Nonnull new, XPtr _Nullable old) {
////    XAssert(ringBuffer, "");
////    XAssert(new, "");
////    XAssert(index < ringBuffer->count, "");
////
////    _XRBufferReplaceItems(ringBuffer, XRangeMake(index, 1), new, 1, old);
////    size_t location = (ringBuffer->offset + index) % ringBuffer->capacity;
////    XPtr p = (XPtr)(ringBuffer->payload + location * ringBuffer->itemType->size);
////    if (old) {
////        memcpy(old, p, ringBuffer->itemType->size);
////    }
////    memcpy(p, new, ringBuffer->itemType->size);
////}
////void XRBufferReplaceItems(XRBuffer _Nonnull ringBuffer, XRange_s range, XPtr _Nullable new, XIndex newCount, XPtr _Nullable old) {
////    XAssert(ringBuffer, "");
////    XAssert(XRangeIsValid(range), "");
////    XAssert(range.location + range.length < ringBuffer->count, "");
////    XAssert(newCount <= ringBuffer->capacity, "");
////    XAssert(ringBuffer->count - range.length <= ringBuffer->capacity - newCount, "");
////    _XRBufferReplaceItems(ringBuffer, range, new, newCount, old);
////}
////void XRBufferRemoveItem(const XRBuffer _Nonnull ringBuffer, XIndex index, XPtr _Nullable old) {
////    XAssert(ringBuffer, "");
////    XAssert(index < ringBuffer->count, "");
////    _XRBufferReplaceItems(ringBuffer, XRangeMake(index, 1), NULL, 0, old);
////}
////void XRBufferRemoveItems(const XRBuffer _Nonnull ringBuffer, XRange_s range, XPtr _Nullable old) {
////    XAssert(ringBuffer, "");
////    XAssert(XRangeIsValid(range), "");
////    XAssert(range.location + range.length < ringBuffer->count, "");
////    _XRBufferReplaceItems(ringBuffer, range, NULL, 0, old);
////}
////
////void XRBufferInsertItems(XRBuffer _Nonnull ringBuffer, XIndex index, XPtr _Nonnull items, XIndex count) {
////    XAssert(ringBuffer, "");
////    XAssert(items, "");
////    XAssert(count <= ringBuffer->capacity, "");
////    XAssert(ringBuffer->count <= ringBuffer->capacity - count, "");
////    XAssert(index <= ringBuffer->count, "");
////    _XRBufferReplaceItems(ringBuffer, XRangeMake(index, 0), items, count, NULL);
////}
////void XRBufferInsertItem(XRBuffer _Nonnull ringBuffer, XIndex index, XPtr _Nonnull item) {
////    XAssert(ringBuffer, "");
////    XAssert(item, "");
////    XAssert(index <= ringBuffer->count, "");
////    XAssert(ringBuffer->count < ringBuffer->capacity, "");
////    _XRBufferReplaceItems(ringBuffer, XRangeMake(index, 0), item, 1, NULL);
////}
////void XRBufferAppendItem(XRBuffer _Nonnull ringBuffer, XPtr _Nonnull item) {
////    XAssert(ringBuffer, "");
////    XAssert(item, "");
////    XAssert(ringBuffer->count < ringBuffer->capacity, "");
////    _XRBufferReplaceItems(ringBuffer, XRangeMake(0, 0), item, 1, NULL);
////}
////void XRBufferPrependItem(XRBuffer _Nonnull ringBuffer, XPtr _Nonnull item) {
////    XAssert(ringBuffer, "");
////    XAssert(item, "");
////    XAssert(ringBuffer->count < ringBuffer->capacity, "");
////    _XRBufferReplaceItems(ringBuffer, XRangeMake(ringBuffer->count, 0), item, 1, NULL);
////}
//
