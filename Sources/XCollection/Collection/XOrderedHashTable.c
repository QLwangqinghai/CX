
#include "XOrderedHashTable.h"
#include "XHashTable.h"

static inline XMutableOrderedHashTableNode_s * _Nonnull __XMutableOrderedHashTableNodeCreate(size_t size) {
    size_t zoneInfo = 0;
    XMutableOrderedHashTableNode_s * node = XInstanceAllocate(0, size, &zoneInfo);
    node->zoneInfo = zoneInfo;
    node->id = 0;
    node->pagePrev = NULL;
    node->pageNext = NULL;
    node->chuckNext = NULL;
    node->dprev = NULL;
    node->dnext = NULL;
    return node;
}
static inline XMutableOrderedHashTableNode_s * _Nonnull XMutableOrderedHashTableNodeCreatePage(size_t pageIndex, void * _Nonnull element, size_t elementSize) {
    size_t size = sizeof(XMutableOrderedHashTableNode_s) + elementSize;
    XMutableOrderedHashTableNode_s * node = __XMutableOrderedHashTableNodeCreate(size);
    node->id = pageIndex;
    memcpy(node->element, element, elementSize);
    return node;
}
static inline XMutableOrderedHashTableNode_s * _Nonnull XMutableOrderedHashTableNodeCreateChuck(size_t chuckId, void * _Nonnull element, size_t elementSize) {
    size_t size = sizeof(XMutableOrderedHashTableNode_s) + elementSize;
    XMutableOrderedHashTableNode_s * node = __XMutableOrderedHashTableNodeCreate(size);
    node->id = chuckId;
    memcpy(node->element, element, elementSize);
    return node;
}
static inline void XMutableOrderedHashTableNodeDestroy(XMutableOrderedHashTableNode_s * _Nonnull node) {
    XInstanceDeallocate(node, node->zoneInfo);
}

static inline size_t __XOrderedHashTableBucketCapacityExponent(size_t count) {
    if (count == 0) {
        return 3;
    }
    const size_t one = 1;
    size_t e = SIZE_BITS_COUNT - USizeLeadingZerosCount(count);
    size_t shift = (count == (one << e)) ? e : (e + 1);
    return shift;
}

size_t __XOrderedHashTableBucketCapacityExponentRoundUp(size_t count) {
    size_t e = __XOrderedHashTableBucketCapacityExponent(count);
    e = MAX(3, e);
    e = MIN(SIZE_BITS_COUNT - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT, e);
    return e;
}

size_t __XOrderedHashTableBucketCapacityExponentRoundDown(size_t count) {
    size_t e = __XOrderedHashTableBucketCapacityExponent(count) - 1;
    e = MAX(3, e);
    e = MIN(SIZE_BITS_COUNT - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT, e);
    return e;
}

void XImmutableOrderedHashTableDeinit(XImmutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit) {
    XAssert(deinit, "");
    XImmutableOrderedHashTableContent_s content = XImmutableOrderedHashTableUnpack(table);
    for (ssize_t index=0; index<table->count; index++) {
        uint8_t * element = content.array[index].element;
        deinit(element);
    }
    *(ssize_t *)&(table->count) = 0;
}

ssize_t XImmutableOrderedHashTableGetCount(XImmutableOrderedHashTable_s * _Nonnull table) {
    return table->count;
}

/// return unretained object
ssize_t __XImmutableOrderedHashTableGetLocation(XImmutableOrderedHashTable_s * _Nonnull table, XImmutableOrderedHashTableContent_s * _Nonnull content, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer) {
    size_t elementSize = elementType->size;
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    ssize_t bucketIndex = hashCode >> table->bucketIndexShift;
    ssize_t start = content->bucketIndexs[bucketIndex];
    ssize_t end = table->count;
    if (bucketIndex != table->bucketCount - 1) {
        end = content->bucketIndexs[bucketIndex + 1];
    }
    
    ssize_t low = start;
    ssize_t high = end - 1;
    ssize_t location = -1;
    
    while (low <= high) {
        ssize_t mid = low + (high - low) / 2;
        uint8_t * element = content->elements + mid * elementSize;
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode > hashCode) {
            high = mid - 1;
        } else if (elementHashCode < hashCode) {
            low = mid + 1;
        } else {
            location = mid;
            if (elementType->isKeyMatch(element, keyBuffer)) {
                return mid;
            }
            break;
        }
    }
    if (location < 0) {
        return -1;
    }
    
    // hash(node[location]) == hash(key)
    
    // location-1 -> low
    for (ssize_t index=location-1; index>=low; index--) {
        uint8_t * element = content->elements + index * elementSize;
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(element, keyBuffer)) {
                return index;
            }
        } else {
            break;
        }
    }
    
    // location+1 -> high
    for (ssize_t index=location+1; index<=high; index++) {
        uint8_t * element = content->elements + index * elementSize;
        size_t elementHashCode = elementType->getKeyHashCode(element);
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(element, keyBuffer)) {
                return index;
            }
        } else {
            break;
        }
    }
    return -1;
}

/// return unretained object
bool_t XImmutableOrderedHashTableGetElement(XImmutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer) {
    XAssert(keyBuffer, "");
    XAssert(elementBuffer, "");
    
    if (table->count <= 0) {
        return false;
    }
    XImmutableOrderedHashTableContent_s content = XImmutableOrderedHashTableUnpack(table);
    ssize_t location = __XImmutableOrderedHashTableGetLocation(table, &content, elementType, keyBuffer);
    if (location < 0) {
        return false;
    }
    uint8_t * element = content.elements + location * elementType->size;
    memcpy(elementBuffer, element, elementType->size);
    return true;
}

void XImmutableOrderedHashTableEnumerate(XImmutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t reverse, XOrderedHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context) {
    XAssert(func, "");
    
    XImmutableOrderedHashTableContent_s content = XImmutableOrderedHashTableUnpack(table);
    bool_t stop = false;
    
    if (reverse) {
        for (ssize_t index=table->count-1; index>=0; index--) {
            uint8_t * element = content.array[index].element;
            func(index, element, subfunc, context, &stop);
            if (stop) {
                return;
            }
        }
    } else {
        for (ssize_t index=0; index<table->count; index++) {
            uint8_t * element = content.array[index].element;
            func(index, element, subfunc, context, &stop);
            if (stop) {
                return;
            }
        }
    }
}
void * _Nullable _XImmutableOrderedHashTableIterNext(XOrderedHashTableIter_s * _Nonnull iter) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)iter->table;
    ssize_t index = (ssize_t)(iter->context);
    XImmutableOrderedHashTableContent_s content = XImmutableOrderedHashTableUnpack(table);
    if (index >= table->count || index < 0) {
        return NULL;
    } else {
        if (iter->reverse) {
            iter->context = (intptr_t)(index - 1);
        } else {
            iter->context = (intptr_t)(index + 1);
        }
        void * element = content.array[index].element;
        iter->context = (intptr_t)(index + 1);
        return element;
    }
}
XOrderedHashTableIter_s XImmutableOrderedHashTableMakeIter(XImmutableOrderedHashTable_s * _Nonnull table, bool_t reverse) {
    XOrderedHashTableIter_s iter = {
        .reverse = reverse,
        .table = table,
        .next = _XImmutableOrderedHashTableIterNext,
        .context = reverse ? table->count - 1 : 0,
    };
    
    return iter;
}

ssize_t XMutableOrderedHashTableGetCount(XMutableOrderedHashTable_s * _Nonnull table) {
    return table->count;
}

bool_t XMutableOrderedHashTableGetElement(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer) {
    if (table->count <= 0) {
        return false;
    }
    XAssert(keyBuffer, "");
    XAssert(elementBuffer, "");
    XAssert(table->buckets, "");
    
    size_t elementSize = elementType->size;
    XMutableOrderedHashTableBucket_s * buckets = table->buckets;
    
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    size_t pageIndex = hashCode >> ORDERED_HASH_TABLE_CHUCK_BITS_COUNT;
    ssize_t bucketIndex = hashCode >> table->bucketIndexShift;
    
    XMutableOrderedHashTableBucket_s * bucket = buckets + bucketIndex;

    XMutableOrderedHashTableNode_s * page = bucket->head;
    while (NULL != page) {
        if (page->id == pageIndex) {
            break;
        } else if (page->id > pageIndex) {
            page = NULL;
        } else {
            XAssert(page->pageNext, "");
            // pages 是个环形接结构，需要找下一个pageId大于当前pageId的page
            if (page->pageNext->id > page->id) {
                page = page->pageNext;
            } else {
                page = NULL;
            }
        }
    }
    XMutableOrderedHashTableNode_s * node = NULL;
    if (page) {
        size_t elementHashCode = elementType->getKeyHashCode(page->element);
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(page->element, keyBuffer)) {
                memcpy(elementBuffer, page->element, elementSize);
                return true;
            }
            node = node->chuckNext;
        } else if (elementHashCode > hashCode) {
            node = NULL;
        } else {
            node = node->chuckNext;
        }
    }
    
    while (NULL != node) {
        size_t elementHashCode = (pageIndex << ORDERED_HASH_TABLE_CHUCK_BITS_COUNT) + node->id;
        if (elementHashCode == hashCode) {
            if (elementType->isKeyMatch(node->element, keyBuffer)) {
                memcpy(elementBuffer, node->element, elementSize);
                return true;
            }
            node = node->chuckNext;
        } else if (elementHashCode > hashCode) {
            node = NULL;
        } else {
            node = node->chuckNext;
        }
    }
    return false;
}

void __XMutableOrderedHashTableResize(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, size_t bucketCapacityExponent) {
    const size_t one = 1;
    size_t bucketCount = one << bucketCapacityExponent;
    size_t bucketIndexShift = SIZE_BITS_COUNT - bucketCapacityExponent;
    if (0 == table->bucketCount) {
        XAssert(NULL == table->buckets, "");
        XMutableOrderedHashTableBucket_s * _Nullable buckets = XAllocate(sizeof(XMutableOrderedHashTableBucket_s) * bucketCount);
        for (ssize_t i=0; i<bucketCount; i++) {
            XMutableOrderedHashTableBucket_s * target = buckets + i;
            target->head = NULL;
        }
        table->bucketCount = bucketCount;
        table->bucketIndexShift = bucketIndexShift;
        table->buckets = buckets;
        return;
    }
    if (bucketCount == table->bucketCount) {
        return;
    }
    XMutableOrderedHashTableBucket_s * _Nullable buckets = XAllocate(sizeof(XMutableOrderedHashTableBucket_s) * bucketCount);
    if (bucketCount < table->bucketCount) {
        // 合并
        size_t stepLength = table->bucketCount / bucketCount;
        for (ssize_t i=0; i<bucketCount; i++) {
            XMutableOrderedHashTableBucket_s * target = buckets + i;
            target->head = NULL;
            for (ssize_t sidx=0; sidx<stepLength; sidx++) {
                XMutableOrderedHashTableBucket_s * src = table->buckets + (i * stepLength) + sidx;
                target->head = src->head;
                if (target->head) {
                    break;
                }
            }
        }
    } else {
        for (ssize_t i=0; i<bucketCount; i++) {
            XMutableOrderedHashTableBucket_s * target = buckets + i;
            target->head = NULL;
        }
        // 分裂
        for (ssize_t sbi=0; sbi<table->bucketCount; sbi++) {
            XMutableOrderedHashTableBucket_s * src = table->buckets + sbi;
            
            size_t startPageIndex = (size_t)sbi << (table->bucketIndexShift - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT);
            size_t endPageIndex = (size_t)(sbi + 1) << (table->bucketIndexShift - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT);
            
            XMutableOrderedHashTableNode_s * node = src->head;
            while (node) {
                size_t targetBucketIndex = node->id >> (table->bucketIndexShift - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT);
                XMutableOrderedHashTableBucket_s * target = buckets + targetBucketIndex;
                if (target->head == NULL) {
                    target->head = node;
                } else {
                    if (target->head->id > node->id) {
                        target->head = node;
                    }
                }
                if (node->pageNext->id >= startPageIndex && node->pageNext->id < endPageIndex && node->pageNext->id > node->id) {
                    node = node->pageNext;
                } else {
                    node = NULL;
                }
            }
        }
    }
    
    XMutableOrderedHashTableBucket_s * oldStorage = table->buckets;
    table->bucketCount = bucketCount;
    table->bucketIndexShift = bucketIndexShift;
    table->buckets = buckets;
    XDeallocate(oldStorage);
}

void __XMutableOrderedHashTableInitBucket(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, size_t bucketCapacityExponent) {
    XAssert(NULL == table->buckets, "");
    const size_t one = 1;
    size_t bucketCount = one << bucketCapacityExponent;
    size_t bucketIndexShift = SIZE_BITS_COUNT - bucketCapacityExponent;
    XMutableOrderedHashTableBucket_s * _Nullable buckets = XAllocate(sizeof(XMutableOrderedHashTableBucket_s) * bucketCount);
    for (ssize_t i=0; i<bucketCount; i++) {
        XMutableOrderedHashTableBucket_s * target = buckets + i;
        target->head = NULL;
    }
    table->bucketCount = bucketCount;
    table->bucketIndexShift = bucketIndexShift;
    table->buckets = buckets;
}

void __XMutableOrderedHashTableOnInsert(XMutableOrderedHashTable_s * _Nonnull table, XMutableOrderedHashTableNode_s * _Nonnull node) {
    if (table->count == 0) {
        table->head = node;
        table->tail = node;
    } else {
        XAssert(table->tail, "");
        node->dprev = table->tail;
        table->tail->dnext = node;
        table->tail = node;
    }
}

void __XMutableOrderedHashTableOnRemove(XMutableOrderedHashTable_s * _Nonnull table, XMutableOrderedHashTableNode_s * _Nonnull node) {
    if (NULL == node->dprev) {
        XAssert(table->head == node, "");
        table->head = node->dnext;
    } else {
        node->dprev->dnext = node->dnext;
    }
    if (node->dnext) {
        node->dnext->dprev = node->dprev;
    }
    if (NULL == node->dnext) {
        XAssert(table->tail == node, "");
        table->tail = node->dprev;
    } else {
        node->dnext->dprev = node->dprev;
    }
    if (node->dprev) {
        node->dprev->dnext = node->dnext;
    }
    node->dprev = NULL;
    node->dnext = NULL;
}
void __XMutableOrderedHashTableOnUpdate(XMutableOrderedHashTable_s * _Nonnull table, XMutableOrderedHashTableNode_s * _Nonnull node) {

}

// 在
void __XMutableOrderedHashTableInsertPageAfter(XMutableOrderedHashTable_s * _Nonnull table, XMutableOrderedHashTableNode_s * _Nonnull newNode, XMutableOrderedHashTableNode_s * _Nullable pagePrev) {
    if (pagePrev) {
        XMutableOrderedHashTableNode_s * pageNext = pagePrev->pageNext;
        XAssert(pageNext, "");
        newNode->pagePrev = pagePrev;
        newNode->pageNext = pageNext;
        pagePrev->pageNext = newNode;
        pageNext->pagePrev = newNode;
    } else {
        newNode->pagePrev = newNode;
        newNode->pageNext = newNode;
    }
}

// 在
void __XMutableOrderedHashTableInsertPageBefore(XMutableOrderedHashTable_s * _Nonnull table, XMutableOrderedHashTableNode_s * _Nonnull newNode, XMutableOrderedHashTableNode_s * _Nullable pageNext) {
    if (pageNext) {
        XMutableOrderedHashTableNode_s * pagePrev = pageNext->pagePrev;
        XAssert(pagePrev, "");
        newNode->pagePrev = pagePrev;
        newNode->pageNext = pageNext;
        pagePrev->pageNext = newNode;
        pageNext->pagePrev = newNode;
    } else {
        newNode->pagePrev = newNode;
        newNode->pageNext = newNode;
    }
}

void __XMutableOrderedHashTableReplacePage(XMutableOrderedHashTable_s * _Nonnull table, XMutableOrderedHashTableNode_s * _Nonnull newNode, XMutableOrderedHashTableNode_s * _Nonnull old) {
    // 防止old 是唯一的page
    if (old->pagePrev == old && old->pageNext == old) {
        newNode->pagePrev = newNode;
        newNode->pageNext = newNode;
    } else {
        XAssert(old->pageNext != old, "");
        XAssert(old->pagePrev != old, "");
        old->pagePrev->pageNext = newNode;
        old->pageNext->pagePrev = newNode;
        newNode->pagePrev = old->pagePrev;
        newNode->pageNext = old->pageNext;
    }
    old->pagePrev = NULL;
    old->pageNext = NULL;
}

void __XMutableOrderedHashTableRemovePage(XMutableOrderedHashTable_s * _Nonnull table, XMutableOrderedHashTableNode_s * _Nonnull page) {
    // 防止page 是唯一的page
    if (page->pagePrev == page && page->pageNext == page) {
        page->pagePrev = NULL;
        page->pageNext = NULL;
    } else {
        XAssert(page->pageNext != page, "");
        XAssert(page->pagePrev != page, "");
        page->pagePrev->pageNext = page->pageNext;
        page->pageNext->pagePrev = page->pagePrev;
        page->pagePrev = NULL;
        page->pageNext = NULL;
    }
}

// pagePrev page pageNext: insertPage
// page 内插入: insertChuck
// newPage<->page: replacePage

// update value, 如果有oldElement， 返回true
bool_t XMutableOrderedHashTableReplace(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull elementBuffer, void * _Nullable oldElementBuffer) {
    XAssert(elementBuffer, "");
    XAssert(oldElementBuffer, "");
    
    if (0 == table->bucketCount) {
        XAssert(0 == table->count, "");
        size_t bucketCapacityExponent = __XOrderedHashTableBucketCapacityExponent(1);
        __XMutableOrderedHashTableInitBucket(table, elementType, bucketCapacityExponent);
    } else {
        XAssert(table->buckets, "");
    }
    void * keyBuffer = elementBuffer;
    size_t elementSize = elementType->size;
    XMutableOrderedHashTableBucket_s * buckets = table->buckets;
    
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    size_t pageIndex = hashCode >> ORDERED_HASH_TABLE_CHUCK_BITS_COUNT;
    size_t chuckIndex = hashCode & ORDERED_HASH_TABLE_CHUCK_MASK;

    size_t bucketIndex = hashCode >> table->bucketIndexShift;
    XMutableOrderedHashTableBucket_s * bucket = buckets + bucketIndex;
    
    // 是否需要插入新的page
    // 是否会成为新的page
    
    // 再reset bucket
    // 找到page，则page内插入，插入完成后检查node是否是page的head， 如果是，则用node 替换old page
    // 找到page， page 割离出来。 然后在page内插入，
    
    // bucket 内插入
    // 找到page 或者 pagenext
    
    if (NULL == bucket->head) {
        XMutableOrderedHashTableNode_s * headPrev = NULL;
        XMutableOrderedHashTableNode_s * pageNext = NULL;
        for (size_t offset=bucketIndex+1; offset<table->bucketCount; offset++) {
            pageNext = (buckets + (bucketIndex + offset) % table->bucketCount)->head;
            if (pageNext) {
                break;
            }
        }
        if (pageNext) {
            headPrev = pageNext->pagePrev;
        }
        if (NULL == headPrev) {
            XAssert(table->count == 0, "");
        }
        XMutableOrderedHashTableNode_s * node = XMutableOrderedHashTableNodeCreatePage(pageIndex, elementBuffer, elementType->size);
        __XMutableOrderedHashTableInsertPageAfter(table, node, headPrev);
        bucket->head = node;
        table->count += 1;
        __XMutableOrderedHashTableOnInsert(table, node);
        return false;
    }
    
    /*
     找page， 如果找不到page， 那么一定有pageNext
     pageIter一定是page 或者pageNext
    // 找page， 找不到就创建， 然后插入
    // 找到page page内插入， 判断page的head是否发生变更
     */
    
    XMutableOrderedHashTableNode_s * pageIter = bucket->head;
    while (pageIter->id < pageIndex) {
        XAssert(pageIter->pageNext, "");
        // pages 是个环形接结构，需要找下一个pageId大于当前pageId的page
        if (pageIter->pageNext->id < pageIter->id) {
            // pageNext
            pageIter = pageIter->pageNext;
            break;
        } else {
            pageIter = pageIter->pageNext;
        }
    }
    
    if (pageIter->id == pageIndex) { // 找到page
        XMutableOrderedHashTableNode_s * page = pageIter;
        
        // page 内插入
        size_t elementHashCode = elementType->getKeyHashCode(page->element);
        if (elementHashCode > hashCode) {
            // 新node成为page的head
            XMutableOrderedHashTableNode_s * node = XMutableOrderedHashTableNodeCreatePage(pageIndex, elementBuffer, elementType->size);
            node->chuckNext = page;
            __XMutableOrderedHashTableReplacePage(table, node, page);
            page->id = elementHashCode & ORDERED_HASH_TABLE_CHUCK_MASK;
            table->count += 1;
            
            if (node->id < bucket->head->id) {
                bucket->head = node;
            }
            
            __XMutableOrderedHashTableOnInsert(table, node);
            return false;
        } else {
            if (elementHashCode == hashCode && elementType->isKeyMatch(page->element, keyBuffer)) {
                memcpy(oldElementBuffer, page->element, elementSize);
                memcpy(page->element, elementBuffer, elementSize);
                __XMutableOrderedHashTableOnUpdate(table, page);
                return true;
            } else {
                // 找chuck
                XMutableOrderedHashTableNode_s * chuckPrev = page;
                while (NULL != chuckPrev->chuckNext) {
                    if (chuckPrev->chuckNext->id < chuckIndex) {
                        chuckPrev = chuckPrev->chuckNext;
                    } else if (chuckPrev->chuckNext->id == chuckIndex) {
                        if (elementType->isKeyMatch(chuckPrev->chuckNext->element, keyBuffer)) {
                            memcpy(oldElementBuffer, chuckPrev->chuckNext->element, elementSize);
                            memcpy(chuckPrev->chuckNext->element, elementBuffer, elementSize);
                            __XMutableOrderedHashTableOnUpdate(table, chuckPrev->chuckNext);
                            return true;
                        } else {
                            chuckPrev = chuckPrev->chuckNext;
                        }
                    } else {
                        break;
                    }
                }

                XMutableOrderedHashTableNode_s * node = XMutableOrderedHashTableNodeCreateChuck(chuckIndex, elementBuffer, elementSize);
                node->chuckNext = chuckPrev->chuckNext;
                chuckPrev->chuckNext = node;
                table->count += 1;
                __XMutableOrderedHashTableOnInsert(table, node);
            }
        }
    } else { // page 不存在此时page 为 pageNext
        XMutableOrderedHashTableNode_s * pageNext = pageIter;

        // 不存在page， 创建page，插入
        XMutableOrderedHashTableNode_s * page = XMutableOrderedHashTableNodeCreatePage(pageIndex, elementBuffer, elementType->size);
        __XMutableOrderedHashTableInsertPageBefore(table, page, pageNext);
        table->count += 1;
        
        if (page->id < bucket->head->id) {
            bucket->head = page;
        }
        __XMutableOrderedHashTableOnInsert(table, page);
    }
    return false;
}

// 如果有oldElement， 返回true
bool_t XMutableOrderedHashTableRemove(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, bool_t allowReduceCapacity, void * _Nullable oldElementBuffer) {
    if (table->count <= 0) {
        return false;
    }
    
    XAssert(keyBuffer, "");
    XAssert(oldElementBuffer, "");
    size_t elementSize = elementType->size;
    XMutableOrderedHashTableBucket_s * buckets = table->buckets;
    
    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
    size_t pageIndex = hashCode >> ORDERED_HASH_TABLE_CHUCK_BITS_COUNT;
    size_t chuckIndex = hashCode & ORDERED_HASH_TABLE_CHUCK_MASK;

    size_t bucketIndex = hashCode >> table->bucketIndexShift;
    XMutableOrderedHashTableBucket_s * bucket = buckets + bucketIndex;
    
    // 是否需要插入新的page
    // 是否会成为新的page
    
    // 再reset bucket
    // 找到page，则page内插入，插入完成后检查node是否是page的head， 如果是，则用node 替换old page
    
    // 找到page， page 割离出来。 然后在page内插入，
    
    if (NULL == bucket->head) {
        return false;
    }

    XMutableOrderedHashTableNode_s * page = bucket->head;
    while (NULL != page) {
        if (page->id == pageIndex) {
            break;
        } else if (page->id > pageIndex) {
            page = NULL;
        } else {
            page = page->pageNext;
        }
    }
    if (NULL == page) {
        return false;
    }
    
    // page 内删除
    size_t elementHashCode = elementType->getKeyHashCode(page->element);
    if (elementHashCode > hashCode) {
        return false;
    } else {
        if (elementHashCode == hashCode && elementType->isKeyMatch(page->element, keyBuffer)) {
            // page.head 被删除

            memcpy(oldElementBuffer, page->element, elementSize);

            XMutableOrderedHashTableNode_s * node = page->chuckNext;
            if (node) {
                node->id = pageIndex;
                page->chuckNext = NULL;
                __XMutableOrderedHashTableReplacePage(table, node, page);
                table->count -= 1;
                if (page == bucket->head) {
                    bucket->head = node;
                }
            } else {
                // page 中没有其他元素， page被删除， 如果page是bucket中的唯一元素，那么bucket也需要清空
                XMutableOrderedHashTableNode_s * pageNext = page->pageNext;
                __XMutableOrderedHashTableRemovePage(table, page);
                table->count -= 1;
                
                if (page == bucket->head) {
                    // pageNext 是否在桶里
                    if (pageNext != page && (pageNext->id >> (table->bucketIndexShift - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT)) == bucketIndex) {
                        bucket->head = pageNext;
                    } else {
                        bucket->head = NULL;
                    }
                }
            }
            __XMutableOrderedHashTableOnRemove(table, page);
            XMutableOrderedHashTableNodeDestroy(page);
            return true;
        } else {
            // 找chuck
            XMutableOrderedHashTableNode_s * chuckPrev = page;
            while (NULL != chuckPrev->chuckNext) {
                XMutableOrderedHashTableNode_s * node = chuckPrev->chuckNext;
                if (node->id < chuckIndex) {
                    chuckPrev = node;
                } else if (node->id == chuckIndex) {
                    if (elementType->isKeyMatch(node->element, keyBuffer)) {
                        memcpy(oldElementBuffer, node->element, elementSize);
                        chuckPrev->chuckNext = node->chuckNext;
                        node->chuckNext = NULL;
                        table->count -= 1;
                        __XMutableOrderedHashTableOnRemove(table, node);
                        XMutableOrderedHashTableNodeDestroy(node);
                        return true;
                    } else {
                        chuckPrev = node;
                    }
                } else {
                    break;
                }
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
} XMutableOrderedHashTableRemoveAllContext_s;

void __XMutableOrderedHashTableRemoveAllEnumerate(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable _context, bool_t * _Nonnull stop) {
    XMutableOrderedHashTableRemoveAllContext_s * context = (XMutableOrderedHashTableRemoveAllContext_s *)_context;
    uint8_t * dst = context->elements + context->elementType->size * context->count;
    memcpy(dst, element, context->elementType->size);
    memset(element, 0, context->elementType->size);
    context->count += 1;
}
XImmutableOrderedHashTable_s * _Nonnull XMutableOrderedHashTableRemoveAll(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t allowReduceCapacity, XObjectOption option) {
    
    ssize_t count = XMutableOrderedHashTableGetCount(table);
    XAssert(count > 0, "");
    
    size_t elementSize = elementType->size;
    size_t one = 1;
    size_t bucketCapacityExponent = __XOrderedHashTableBucketCapacityExponentRoundUp(count);
    size_t bucketCount = one << bucketCapacityExponent;
    size_t bucketIndexShift = SIZE_BITS_COUNT - bucketCapacityExponent;
    
    size_t size = sizeof(XImmutableOrderedHashTable_s) + sizeof(XCollectionElementContainer_s) * count + sizeof(ssize_t) * bucketCount + elementSize * count;
    XImmutableOrderedHashTable_s * result = (XImmutableOrderedHashTable_s *)XObjectAllocate(XObjectGetClass(table), option, size, __XCollectionLayoutImmutable);
    *(ssize_t *)&(result->count) = count;
    result->bucketCount = bucketCount;
    result->bucketIndexShift = bucketIndexShift;
    atomic_store(&(result->_hashCode), 0);

    XImmutableOrderedHashTableContent_s content = XImmutableOrderedHashTableUnpack(result);
    
    // bucket中的个数清0
    for (ssize_t bucketIndex=0; bucketIndex < bucketCount; bucketIndex++) {
        content.bucketIndexs[bucketIndex] = 0;
    }
    
    // 按照hashcode排序  从小到大， 遍历table， 并且放入result的elements中， 同时记录bucket中的个数
    ssize_t eIndex = 0;
    XMutableOrderedHashTableNode_s * page = NULL;
    for (size_t idx = 0; idx < table->bucketCount; idx++) {
        page = (table->buckets + idx)->head;
        if (page) {
            break;
        }
    }
    while (page) {
        size_t bidx = page->id >> (table->bucketIndexShift - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT);
        XMutableOrderedHashTableNode_s * chuck = page;
        while (chuck) {
            uint8_t * dst = content.elements + eIndex * elementSize;
            memcpy(dst, chuck->element, elementSize);
            content.bucketIndexs[bidx] += 1;
            eIndex += 1;
            chuck = chuck->chuckNext;
        }
        if (page->pageNext->id > page->id) {
            page = page->pageNext;
        } else {
            break;
        }
    }
    XAssert(eIndex == count, "");
    
    // bucket的个数转化成bucket中元素的起始index
    ssize_t bucketEndIndex = 0;
    for (ssize_t bucketIndex=0; bucketIndex < bucketCount; bucketIndex++) {
        ssize_t itemCount = content.bucketIndexs[bucketIndex];
        content.bucketIndexs[bucketIndex] = bucketEndIndex;
        bucketEndIndex += itemCount;
    }
    
    // 按照table中元素放入顺序，初始化array
    eIndex = 0;
    
    XMutableOrderedHashTableNode_s * node = table->head;
    eIndex = 0;
    while (node) {
        ssize_t location = __XImmutableOrderedHashTableGetLocation(result, &content, elementType, node->element);
        XAssert(location >= 0, "");
        content.array[eIndex].element = content.elements + location * elementSize;
        eIndex += 1;
        node = node->dnext;
    }
    XAssert(eIndex == count, "");
    
    // remove
    node = table->head;
    table->head = NULL;
    table->tail = NULL;
    eIndex = 0;
    while (node) {
        XMutableOrderedHashTableNode_s * next = node->dnext;
        XMutableOrderedHashTableNodeDestroy(node);
        eIndex += 1;
        node = next;
    }
    if (allowReduceCapacity) {
        XMutableOrderedHashTableBucket_s * buckets = table->buckets;
        table->bucketCount = 0;
        table->buckets = NULL;
        XDeallocate(buckets);
    } else {
        for (ssize_t i=0; i<table->bucketCount; i++) {
            XMutableOrderedHashTableBucket_s * target = table->buckets + i;
            target->head = NULL;
        }
    }
    
    return result;
}

void XMutableOrderedHashTableEnumerate(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t reverse, XOrderedHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context) {
    bool_t stop = false;
    if (reverse) {
        ssize_t eIndex = table->count;
        XMutableOrderedHashTableNode_s * node = table->tail;
        while (node) {
            eIndex -= 1;
            func(eIndex, node->element, subfunc, context, &stop);
            node = node->dprev;
        }
        XAssert(eIndex == 0, "");
    } else {
        ssize_t eIndex = 0;
        XMutableOrderedHashTableNode_s * node = table->head;
        while (node) {
            func(eIndex, node->element, subfunc, context, &stop);
            eIndex += 1;
            node = node->dnext;
        }
        XAssert(eIndex == table->count, "");
    }
}

void * _Nullable _XMutableOrderedHashTableIterNext(XOrderedHashTableIter_s * _Nonnull iter) {
    XMutableOrderedHashTableNode_s * node = (XMutableOrderedHashTableNode_s *)iter->context;
    if (node) {
        XMutableOrderedHashTableNode_s * next = iter->reverse ? node->dprev : node->dnext;
        iter->context = (intptr_t)next;
        return node->element;
    } else {
        return NULL;
    }
}
XOrderedHashTableIter_s XMutableOrderedHashTableMakeIter(XMutableOrderedHashTable_s * _Nonnull table, bool_t reverse) {
    XOrderedHashTableIter_s iter = {
        .reverse = reverse,
        .table = table,
        .next = _XMutableOrderedHashTableIterNext,
        .context = reverse ? (intptr_t)table->tail : (intptr_t)table->head,
    };
    
    return iter;
}

void __XMutableOrderedHashTableCopyEnumerate(XMutableOrderedHashTable_s * _Nonnull table, bool_t reverse, const XHashElementType_s * _Nonnull elementType, XOrderedHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context) {
    bool_t stop = false;
    if (reverse) {
        ssize_t eIndex = table->count;
        XMutableOrderedHashTableNode_s * node = table->tail;
        while (node) {
            eIndex -= 1;
            func(eIndex, node->element, subfunc, context, &stop);
            node = node->dprev;
        }
        XAssert(eIndex == 0, "");
    } else {
        ssize_t eIndex = 0;
        XMutableOrderedHashTableNode_s * node = table->head;
        while (node) {
            func(eIndex, node->element, subfunc, context, &stop);
            eIndex += 1;
            node = node->dnext;
        }
        XAssert(eIndex == table->count, "");
    }
}

XImmutableOrderedHashTable_s * _Nonnull XMutableOrderedHashTableCopy(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XObjectOption option, _XHashElementElementCopy_f _Nonnull copy) {
    XAssert(copy, "");
    ssize_t count = XMutableOrderedHashTableGetCount(table);
    XAssert(count > 0, "");
    
    size_t elementSize = elementType->size;
    size_t one = 1;
    size_t bucketCapacityExponent = __XOrderedHashTableBucketCapacityExponentRoundUp(count);
    size_t bucketCount = one << bucketCapacityExponent;
    size_t bucketIndexShift = SIZE_BITS_COUNT - bucketCapacityExponent;
    
    size_t size = sizeof(XImmutableOrderedHashTable_s) + sizeof(XCollectionElementContainer_s) * count + sizeof(ssize_t) * bucketCount + elementSize * count;
    XImmutableOrderedHashTable_s * result = (XImmutableOrderedHashTable_s *)XObjectAllocate(XObjectGetClass(table), option, size, __XCollectionLayoutImmutable);
    *(ssize_t *)&(result->count) = count;
    result->bucketCount = bucketCount;
    result->bucketIndexShift = bucketIndexShift;
    atomic_store(&(result->_hashCode), 0);

    XImmutableOrderedHashTableContent_s content = XImmutableOrderedHashTableUnpack(result);
    
    // bucket中的个数清0
    for (ssize_t bucketIndex=0; bucketIndex < bucketCount; bucketIndex++) {
        content.bucketIndexs[bucketIndex] = 0;
    }
    
    // 按照hashcode排序  从小到大， 遍历table， 并且放入result的elements中， 同时记录bucket中的个数
    ssize_t eIndex = 0;
    XMutableOrderedHashTableNode_s * page = NULL;
    for (size_t idx = 0; idx < table->bucketCount; idx++) {
        page = (table->buckets + idx)->head;
        if (page) {
            break;
        }
    }
    while (page) {
        size_t bidx = page->id >> (table->bucketIndexShift - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT);
        XMutableOrderedHashTableNode_s * chuck = page;
        while (chuck) {
            uint8_t * dst = content.elements + eIndex * elementSize;
            copy(dst, chuck->element);
            content.bucketIndexs[bidx] += 1;
            eIndex += 1;
            chuck = chuck->chuckNext;
        }
        if (page->pageNext->id > page->id) {
            page = page->pageNext;
        } else {
            break;
        }
    }
    XAssert(eIndex == count, "");
    
    // bucket的个数转化成bucket中元素的起始index
    ssize_t bucketEndIndex = 0;
    for (ssize_t bucketIndex=0; bucketIndex < bucketCount; bucketIndex++) {
        ssize_t itemCount = content.bucketIndexs[bucketIndex];
        content.bucketIndexs[bucketIndex] = bucketEndIndex;
        bucketEndIndex += itemCount;
    }
    
    // 按照table中元素放入顺序，初始化array
    eIndex = 0;
    XMutableOrderedHashTableNode_s * node = table->head;
    while (node) {
        ssize_t location = __XImmutableOrderedHashTableGetLocation(result, &content, elementType, node->element);
        XAssert(location >= 0, "");
        content.array[eIndex].element = content.elements + location * elementSize;
        eIndex += 1;
        node = node->dnext;
    }
    XAssert(eIndex == count, "");
    return result;
}
void XMutableOrderedHashTableResize(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, ssize_t minCapacity) {
    size_t bucketCapacityExponent = __XOrderedHashTableBucketCapacityExponentRoundUp(minCapacity);
    size_t one = 1;
    size_t bucketCount = one << bucketCapacityExponent;
    if (table->bucketCount == 0 || table->bucketCount < bucketCount) {
        // resize
        __XMutableOrderedHashTableResize(table, elementType, bucketCapacityExponent);
    }
}
void * _Nullable XOrderedHashTableIterNext(XOrderedHashTableIter_s * _Nonnull iter) {
    return iter->next(iter);
}

XMutableOrderedHashTable_s * _Nonnull XMutableOrderedHashTableCreate(XClassRef _Nonnull class, XObjectOption option, const XHashElementType_s * _Nonnull elementType, ssize_t capacity) {
    XMutableOrderedHashTable_s * result = (XMutableOrderedHashTable_s *)XObjectAllocate(class, option, sizeof(XMutableOrderedHashTable_s), __XCollectionLayoutMutable);
    result->count = 0;
    size_t pageCapacityExponent = 3;
    size_t bucketIndexShift = SIZE_BITS_COUNT - pageCapacityExponent;
    result->bucketCount = 0;
    result->bucketIndexShift = bucketIndexShift;
    result->buckets = NULL;
    result->head = NULL;
    result->tail = NULL;
    if (capacity > 0) {
        size_t bucketCapacityExponent = __XOrderedHashTableBucketCapacityExponent(capacity);
        __XMutableOrderedHashTableInitBucket(result, elementType, bucketCapacityExponent);
    }
    return result;
}
void XMutableOrderedHashTableDeinit(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit) {
    XAssert(deinit, "");
    XMutableOrderedHashTableNode_s * node = table->head;
    table->head = NULL;
    table->tail = NULL;
    table->count = 0;

    XMutableOrderedHashTableBucket_s * buckets = table->buckets;
    table->bucketCount = 0;
    table->buckets = NULL;
    XDeallocate(buckets);
    
    while (node) {
        XMutableOrderedHashTableNode_s * next = node->dnext;
        deinit(node->element);
        XMutableOrderedHashTableNodeDestroy(node);
        node = next;
    }
}

