
#include "XRingBuffer.h"
#include "XRuntimeInternal.h"


// 从前往后 reverse=0； 否则reverse=1, sum(src.item) = sum(dst.item)
void XVectorBufferMove(XVector_s * _Nonnull dst, size_t dstVectorCount, size_t elementSize, XVector_s * _Nonnull src, size_t srcVectorCount, bool_t reverse) {
    size_t srcItemCount = 0;
    size_t dstItemCount = 0;
    for (ssize_t i=0; i<dstVectorCount; i++) {
        dstItemCount += dst[i].count;
    }
    for (ssize_t i=0; i<srcVectorCount; i++) {
        srcItemCount += src[i].count;
    }
    XAssert(dstItemCount == srcItemCount, "");
    
    size_t dstUsed = 0;
    
    if (0 == reverse) {
        XVector_s * d = dst;
        for (ssize_t i=0; i<srcVectorCount; i++) {
            XVector_s * s = src + i;
            size_t sendCount = 0;
            while (sendCount < s->count) {
                while (d->count <= dstUsed) {
                    d = d + 1;
                    dstUsed = 0;
                }
                size_t cpCount = MIN(s->count - sendCount, d->count - dstUsed);
                memmove(d->items + dstUsed, s->items + sendCount, cpCount * elementSize);
                sendCount += cpCount;
                dstUsed += cpCount;
            }
        }
    } else {
        XVector_s * d = dst + (dstVectorCount - 1);
        for (ssize_t i=srcVectorCount-1; i>=0; i--) {
            XVector_s * s = src + i;
            size_t sendCount = 0;
            while (sendCount < s->count) {
                while (d->count <= dstUsed) {
                    d = d - 1;
                    dstUsed = 0;
                }
                size_t cpCount = MIN(s->count - sendCount, d->count - dstUsed);
                memmove(d->items + (d->count - dstUsed - cpCount), s->items + (s->count - sendCount - cpCount), cpCount * elementSize);
                sendCount += cpCount;
                dstUsed += cpCount;
            }
        }
    }
}


// 从前往后 reverse=0； 否则reverse=1, sum(src.item) = sum(dst.item)
void XVectorBufferCopy(XVector_s * _Nonnull dst, size_t dstVectorCount, size_t elementSize, const void * _Nonnull src) {
    const uint8_t * buffer = src;
    for (ssize_t i=0; i<dstVectorCount; i++) {
        XVector_s * d = dst + i;
        size_t size = d->count * elementSize;
        memcpy(d->items, buffer, size);
        buffer += size;
    }
}

size_t XVectorBufferGetContent(const XVector_s * _Nonnull vectors, size_t vectorCount, size_t elementSize, uint8_t * _Nonnull buffer) {
    size_t count = 0;
    uint8_t * data = buffer;
    for (ssize_t i=0; i<vectorCount; i++) {
        XVector_s vector = vectors[i];
        size_t size = vector.count * elementSize;
        memcpy(data, vector.items, size);
        count += vector.count;
        data += vector.count * elementSize;
    }
    return count;
}
size_t XVectorBufferSetContent(const XVector_s * _Nonnull vectors, size_t vectorCount, size_t elementSize, const uint8_t * _Nonnull buffer) {
    size_t count = 0;
    const uint8_t * data = buffer;
    for (ssize_t i=0; i<vectorCount; i++) {
        XVector_s vector = vectors[i];
        size_t size = vector.count * elementSize;
        memcpy(vector.items, data, size);
        count += vector.count;
        data += vector.count * elementSize;
    }
    return count;
}
void XVectorBufferClear(XVector_s * _Nonnull vectors, size_t vectorCount, size_t elementSize) {
    for (ssize_t i=0; i<vectorCount; i++) {
        XVector_s * s = vectors + i;
        if (s->count <= 0) {
            continue;
        }
        memset(s, 0, s->count * elementSize);
    }
}


XRingBuffer_s * _Nonnull XRingBufferAllocate(size_t elementSize, size_t capacity) {
    XAssert((elementSize >> (SIZE_BITS_COUNT - XZoneInfoBitCount)) == 0, "");
    XAssert(capacity > 0, "");
    size_t contentSize = capacity * elementSize;
    XAssert(contentSize / capacity == elementSize, "");
    size_t size = sizeof(XRingBuffer_s) + contentSize;
    XAssert(size > contentSize, "");
    XRingBuffer_s * buffer = (XRingBuffer_s *)XAllocate(size);
    XRingBuffer_s tmp = {
        .zoneInfo = 0,
        .elementSize = elementSize,
        .capacity = capacity,
        .count = 0,
        .offset = 0,
    };
    memcpy(buffer, &tmp, sizeof(XRingBuffer_s));
    return buffer;
}

void XRingBufferDealloc(XRingBuffer_s * _Nonnull buffer) {
    XDeallocate(buffer);
}


static inline uint8_t * _Nonnull __XRingBufferGetElement(const XRingBuffer_s * _Nonnull buffer, size_t elementSize, size_t index) {
    return (uint8_t *)(buffer->items + elementSize * ((buffer->offset + index) % buffer->capacity));
}

void * _Nonnull _XRingBufferElementAtLocation(XRingBuffer_s * _Nonnull array, size_t elementSize, ssize_t location) {
    XAssert(location >= 0, "");
    return array->items + elementSize * location;
}

uint8_t * _Nonnull XRingBufferElementAtIndex(const XRingBuffer_s * _Nonnull array, ssize_t index) {
    XAssert(index >= 0, "");
    XAssert(index < array->count, "");
    return __XRingBufferGetElement(array, array->elementSize, index);
}

/// 不对index， count 做教研
void __XRingBufferGetVectors(const XRingBuffer_s * _Nonnull buffer, size_t elementSize, size_t index, size_t count, XVector_s vectors[_Nonnull 2]) {
    size_t rightCount = buffer->capacity - (buffer->offset + index) % buffer->capacity;
    if (rightCount >= count) {
        vectors[0].count = count;
        vectors[0].items = __XRingBufferGetElement(buffer, elementSize, index);
        vectors[1].count = 0;
        vectors[1].items = NULL;
    } else {
        vectors[0].count = rightCount;
        vectors[0].items = __XRingBufferGetElement(buffer, elementSize, index);
        vectors[1].count = (count - rightCount);
        vectors[1].items = __XRingBufferGetElement(buffer, elementSize, index + rightCount);
    }
}

void __XRingBufferClear(XRingBuffer_s * _Nonnull buffer, size_t elementSize, ssize_t index, ssize_t count) {
    XVector_s src[2] = { 0 };
    __XRingBufferGetVectors(buffer, elementSize, index, count, src);
    XVectorBufferClear(src, 2, elementSize);
}
void XRingBufferClear(XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count) {
    size_t elementSize = buffer->elementSize;
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(index + count <= buffer->capacity, "");
    __XRingBufferClear(buffer, elementSize, index, count);
}


void __XRingBufferMove(XRingBuffer_s * _Nonnull buffer, size_t elementSize, ssize_t index, ssize_t count, ssize_t distance) {
    // 向后移动 reverse=  true
    bool_t reverse = distance > 0;
    XVector_s srcBuffer[2] = { 0 };
    XVector_s dstBuffer[2] = { 0 };
    __XRingBufferGetVectors(buffer, elementSize, index, count, srcBuffer);
    __XRingBufferGetVectors(buffer, elementSize, index + distance, count, dstBuffer);
    XVectorBufferMove(dstBuffer, 2, elementSize, srcBuffer, 2, reverse);
}

// 把array的 从index到index+count， 替换成newcount个NULL
void XRingBufferMove(XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, ssize_t distance) {
    size_t elementSize = buffer->elementSize;
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(index + count <= buffer->capacity, "");
    XAssert(index + distance >= 0, "");
    XAssert(index + distance + count <= buffer->capacity, "");
    
    if (distance == 0) {
        return;
    } else {
        __XRingBufferMove(buffer, elementSize, index, count, distance);
    }
}

#pragma mark - XRingBuffer


static inline bool_t __XRingBufferCheckMemory(XRingBuffer_s * _Nonnull buffer, size_t elementSize, const void * _Nullable _ptr) {
   uintptr_t ptr = (uintptr_t)_ptr;
   return ptr < (uintptr_t)buffer || (uintptr_t)(buffer->items + buffer->capacity * elementSize) <= ptr;
}

/// capacity == 0 时， 返回NULL
XRingBuffer_s * _Nonnull XRingBufferCreate(size_t elementSize, size_t capacity, size_t offset) {
    XAssert(elementSize > 0, "");
    XAssert(capacity > 0, "");

    XRingBuffer_s * buffer = XRingBufferAllocate(elementSize, capacity);
    buffer->offset = offset % capacity;
    buffer->count = 0;
    memset(buffer->items, 0, elementSize * buffer->capacity);
    return buffer;
}

/// itemCount == 0 时， 返回NULL
XRingBuffer_s * _Nonnull XRingBufferCreateWithElements(size_t elementSize, size_t capacity, size_t offset, const void * _Nullable items, size_t itemCount) {
    XAssert(elementSize > 0, "");
    XAssert(capacity > 0, "");
    XRingBuffer_s * buffer = XRingBufferAllocate(elementSize, capacity);
    buffer->offset = offset % capacity;
    buffer->count = itemCount;
    
    XVector_s dst[2] = {};
    __XRingBufferGetVectors(buffer, elementSize, 0, itemCount, dst);
    XVectorBufferCopy(dst, 2, elementSize, items);
    
    __XRingBufferGetVectors(buffer, elementSize, itemCount, buffer->capacity - itemCount, dst);
    XVectorBufferClear(dst, 2, elementSize);

    return buffer;
}

XRingBuffer_s * _Nullable XRingBufferCreateWithVectors(size_t elementSize, size_t capacity, size_t offset, XVector_s * _Nonnull vectors, size_t vectorCount) {
    XAssert(elementSize > 0, "");
    XAssert(capacity > 0, "");
    XRingBuffer_s * buffer = XRingBufferAllocate(elementSize, capacity);
    buffer->offset = offset % capacity;
    size_t itemCount = 0;
    for (size_t i=0; i<vectorCount; i++) {
        XVector_s vector = vectors[i];
        XAssert(itemCount + vector.count <= buffer->capacity, "");
        XVector_s dst[2] = {};
        __XRingBufferGetVectors(buffer, elementSize, itemCount, vector.count, dst);
        XVectorBufferCopy(dst, 2, elementSize, vector.items);
        itemCount += vector.count;
    }
    buffer->count = itemCount;
    
    XVector_s dst[2] = {};
    __XRingBufferGetVectors(buffer, elementSize, itemCount, buffer->capacity - itemCount, dst);
    XVectorBufferClear(dst, 2, elementSize);
    return buffer;
}

void XRingBufferDestroy(XRingBuffer_s * _Nullable deque) {
    if (deque) {
        XRingBufferDealloc(deque);
    }
}

void XRingBufferGetVectors(const XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, XVector_s vectors[_Nonnull 2]) {
    XAssert(buffer, "");
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(index + count <= buffer->count, "");
    __XRingBufferGetVectors(buffer, buffer->elementSize, index, count, vectors);
}

void __XRingBufferGetElements(const XRingBuffer_s * _Nonnull buffer, size_t elementSize, ssize_t index, ssize_t count, void * _Nonnull elements) {
    XVector_s src[2] = { 0 };
    __XRingBufferGetVectors(buffer, elementSize, index, count, src);
    XVectorBufferGetContent(src, 2, elementSize, elements);
}

void XRingBufferGetElements(const XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, void * _Nonnull elements) {
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(index + count <= buffer->count, "");
    __XRingBufferGetElements(buffer, buffer->elementSize, index, count, elements);
}

void __XRingBufferSetElements(const XRingBuffer_s * _Nonnull buffer, size_t elementSize, ssize_t index, ssize_t count, const void * _Nonnull elements) {
    XVector_s src[2] = { 0 };
    __XRingBufferGetVectors(buffer, elementSize, index, count, src);
    XVectorBufferSetContent(src, 2, elementSize, elements);
}

void XRingBufferSetElements(const XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, const void * _Nonnull elements) {
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(index + count <= buffer->count, "");
    __XRingBufferSetElements(buffer, buffer->elementSize, index, count, elements);
}

void XRingBufferReplaceElements(XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, const void * _Nullable items, ssize_t itemCount, void * _Nullable removedItems) {
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(itemCount >= 0, "");
    XAssert(index + count <= buffer->count, "");
    XAssert(buffer->count + itemCount - count <= buffer->capacity, "");
    size_t elementSize = buffer->elementSize;
    XAssert(__XRingBufferCheckMemory(buffer, elementSize, items), "");
    XAssert(__XRingBufferCheckMemory(buffer, elementSize, removedItems), "");
    
    if (itemCount > 0) {
        XAssert(items, "");
    }
    if (count > 0) {
        XAssert(removedItems, "");
    }
    size_t newTotalCount = buffer->count + itemCount - count;
    XAssert(newTotalCount <= buffer->capacity, "");
    size_t leftCount = index;
    size_t rightCount = buffer->count - (index + count);
    __XRingBufferGetElements(buffer, elementSize, index, count, removedItems);
    
    if (leftCount < rightCount) {
        // 前半部分移动
        if (itemCount > count) {
            //  head <<<
            
            // insert
            ssize_t increaseCount = itemCount - count;
            // offset <<<
            buffer->offset = (buffer->offset + (buffer->capacity - increaseCount)) % buffer->capacity;
            buffer->count = newTotalCount;

            // data <<<
            XRingBufferMove(buffer, increaseCount, leftCount, -increaseCount);
        } else if (itemCount < count) {
            //  head >>>
            
            // remove
            ssize_t reduceCount = count - itemCount;
            XRingBufferMove(buffer, 0, leftCount, reduceCount);
            XRingBufferClear(buffer, 0, reduceCount);
            buffer->offset = (buffer->offset + reduceCount) % buffer->capacity;
            buffer->count = newTotalCount;
        }
    } else {
        // 后半部分移动
        
        if (itemCount > count) {
            // insert
            ssize_t increaseCount = itemCount - count;
            // tail >>>
            buffer->count = newTotalCount;
            XRingBufferMove(buffer, index+count, rightCount, increaseCount);
        } else if (itemCount < count) {
            // remove
            ssize_t reduceCount = count - itemCount;
            // tail <<<
            XRingBufferMove(buffer, index+count, rightCount, -reduceCount);
            XRingBufferClear(buffer, buffer->count-reduceCount, reduceCount);
            buffer->count = newTotalCount;
        }
    }
    __XRingBufferSetElements(buffer, elementSize, index, itemCount, items);
}

XRingBuffer_s * _Nonnull XRingBufferReplacingElements(XRingBuffer_s * _Nonnull buffer, size_t capacity, size_t offset, ssize_t index, ssize_t count, const void * _Nullable items, ssize_t itemCount, void * _Nullable removedItems) {
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(itemCount >= 0, "");
    XAssert(buffer, "");
    XAssert(index + count <= buffer->count, "");
    XAssert(buffer->count + itemCount - count <= capacity, "");
    XAssert(capacity > 0, "");
    if (itemCount > 0) {
        XAssert(items, "");
    }
    if (count > 0) {
        XAssert(removedItems, "");
    }
    size_t elementSize = buffer->elementSize;
    __XRingBufferGetElements(buffer, elementSize, index, count, removedItems);
    
    XRingBuffer_s * result = XRingBufferAllocate(elementSize, capacity);
    result->offset = offset % capacity;
    result->count = buffer->count + itemCount - count;
    
    //    XVector_s dst[2] = {};
    //    __XRingBufferGetVectors(buffer, elementSize, itemCount, buffer->capacity - itemCount, dst);
    //    XVectorBufferClear(dst, 2, elementSize);
    uint8_t * dst = __XRingBufferGetElement(result, elementSize, 0);
    
    
    XVector_s src[2] = { 0 };
    
    // 0, index
    __XRingBufferGetVectors(buffer, elementSize, 0, index, src);
    XVectorBufferGetContent(src, 2, elementSize, dst);
    
    // index, index+itemCount
    memcpy(dst + index * elementSize, items, itemCount * elementSize);
    
    // index+itemCount, end
    __XRingBufferGetVectors(buffer, elementSize, index + count, buffer->count - index - count, src);
    XVectorBufferGetContent(src, 2, elementSize, dst + (index + itemCount) * elementSize);
    
    __XRingBufferGetVectors(result, elementSize, result->count, result->capacity - result->count, src);
    XVectorBufferClear(src, 2, elementSize);
    return result;
}


bool_t XRingBufferBSearch(XRingBuffer_s * _Nonnull buffer, bool_t reverse, void * _Nonnull target, XRingBufferCompare_f _Nonnull compare, void * _Nullable context, ssize_t * _Nonnull location) {
    int fix = reverse ? -1 : 1;
    if (buffer->count == 0) {
        *location = 0;
        return false;
    } else if (buffer->count == 1) {
        uint8_t * element = XRingBufferElementAtIndex(buffer, 0);
        int cr = compare(element, target, context) * fix;
        
        if (cr < 0) {
            // element 在 target 的左边
            *location = 0;
            return false;
        } else if (cr > 0) {
            // element 在 target 的右边
            *location = 1;
            return false;
        } else {
            *location = 0;
            return true;
        }
    } else {
        ssize_t low = 0;
        ssize_t high = buffer->count - 1;
        while (low < high) {
            ssize_t mid = low + (high - low) / 2;
            void * element = XRingBufferElementAtIndex(buffer, mid);
            int cr = compare(element, target, context) * fix;
            if (mid == low) {
                // (4)3, (5)5   insert 4, location=5
                // (4)5, (5)3   insert 4, location=5

                *location = mid + 1;
                return false;
            }
            if (cr < 0) {
                // element 在 target 的左边
                low = mid;
            } else if (cr > 0) {
                // element 在 target 的右边
                high = mid;
            } else {
                *location = mid;
                return true;
            }
        }
    }
    abort();
}


