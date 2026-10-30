
#include "XDeque.h"
#include "XRuntimeInternal.h"


#if CX_TARGET_RT_64_BIT
// 2M
static const size_t XCollectionPageSize = 0x200000;
#else
// 4k
static const size_t XCollectionPageSize = 0x1000;
#endif


// 每次加大 1/2 2/3 或者 1/3倍
size_t XCollectionSizeRoundUp(size_t size) {
    const size_t one = 1;
    size_t e = SIZE_BITS_COUNT - USizeLeadingZerosCount(size);
    size_t shift = size >= XCollectionPageSize ? (e - 2) : (e - 1);
    size_t page = one << shift;
    return (size + page - 1) >> shift << shift;
}

size_t XCollectionSizeRoundDown(size_t size) {
    size_t e = SIZE_BITS_COUNT - USizeLeadingZerosCount(size);
    size_t shift = size >= XCollectionPageSize ? (e - 2) : (e - 1);
    return size >> shift << shift;
}

size_t XDequeCapacityRoundUp(size_t elementSize, size_t count) {
    XAssert(count > 0, "");
    size_t base = sizeof(XRingBuffer_s);
    size_t size = MAX(elementSize * MAX(count, 2), sizeof(size_t) * 4);
    if (size > 128) {
        base += sizeof(size_t) * 2;
    }
    size += base;
    size_t result = (XCollectionSizeRoundUp(size) - base) / elementSize;
    XAssert(result >= count, "");
    return result;
}

size_t XDequeCapacityRoundDown(size_t elementSize, size_t count) {
    XAssert(count > 0, "");
    size_t base = sizeof(XRingBuffer_s);
    size_t size = base + MAX(elementSize * MAX(count, 2), sizeof(size_t) * 4);
    if (size > 128) {
        base += sizeof(size_t) * 2;
    }
    size += base;
    size_t result = (XCollectionSizeRoundDown(size) - base) / elementSize;
    return result;
}

void XDequeInit(XDeque_s * _Nonnull deque, size_t elementSize, size_t _capacity) {
    if (_capacity > 0) {
        size_t capacity = XDequeCapacityRoundUp(elementSize, _capacity);
        deque->buffer = XRingBufferCreate(elementSize, capacity, capacity / 2);
    } else {
        deque->buffer = NULL;
    }
}

void XDequeInitWithElements(XDeque_s * _Nonnull deque, size_t elementSize, const void * _Nullable elements, size_t elementCount) {
    if (elementCount > 0) {
        size_t capacity = XDequeCapacityRoundUp(elementSize, elementCount);
        deque->buffer = XRingBufferCreateWithElements(elementSize, capacity, (capacity - elementCount) / 2, elements, elementCount);
    } else {
        deque->buffer = NULL;
    }
}

void XDequeDeinit(XDeque_s * _Nonnull deque) {
    if (deque->buffer) {
        XRingBufferDestroy(deque->buffer);
        deque->buffer = NULL;
    }
}

void XDequeResize(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t minCapacity) {
    if (NULL == deque->buffer) {
        if (minCapacity > 0) {
            size_t capacity = XDequeCapacityRoundUp(elementSize, minCapacity);
            deque->buffer = XRingBufferCreate(elementSize, capacity, 0);
        }
    } else {
        XRingBuffer_s * buffer = deque->buffer;
        if (minCapacity > buffer->capacity) {
            size_t capacity = XDequeCapacityRoundUp(elementSize, minCapacity);
            XRingBuffer_s * newBuffer = XRingBufferCreate(elementSize, capacity, (capacity - buffer->count) / 2);
            XRingBufferReplaceElements(buffer, 0, buffer->count, NULL, 0, XRingBufferElementAtIndex(newBuffer, 0));
            newBuffer->count = buffer->count;
            deque->buffer = newBuffer;
            XRingBufferDestroy(buffer);
        }
    }
}

void * _Nonnull XDequeElementAtIndex(XDeque_s * _Nonnull deque, ssize_t index) {
    XAssert(deque->buffer, "");
    return XRingBufferElementAtIndex(deque->buffer, index);
}

void XDequeReplaceElements(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t index, ssize_t count, const void * _Nullable items, ssize_t itemCount, bool_t allowReduceCapacity, void * _Nullable removedItems) {
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    XAssert(itemCount >= 0, "");
    if (itemCount == 0 && count == 0) {
        return;
    }
    
    if (itemCount > 0) {
        XAssert(items, "");
    }
    if (count > 0) {
        XAssert(removedItems, "");
    }
    if (NULL == deque->buffer) {
        XAssert(count == 0 && index == 0, "");
        if (itemCount > 0) {
            size_t capacity = XDequeCapacityRoundUp(elementSize, itemCount);
            deque->buffer = XRingBufferCreateWithElements(elementSize, capacity, (capacity - itemCount) / 2, items, itemCount);
        }
    } else {
        XRingBuffer_s * buffer = deque->buffer;
        
        size_t newTotalCount = buffer->count - count + itemCount;
        if (itemCount >= count) { // 增加或者数量不变
            if (newTotalCount <= buffer->capacity) {
                XRingBufferReplaceElements(buffer, index, count, items, itemCount, removedItems);
            } else {
                size_t capacity = XDequeCapacityRoundUp(elementSize, newTotalCount);
                deque->buffer = XRingBufferReplacingElements(buffer, capacity, (capacity - newTotalCount)/2, index, count, items, itemCount, removedItems);
                XRingBufferDestroy(buffer);
            }
        } else { // 减少数量
            XAssert(deque->buffer, "");
            size_t capacity = XDequeCapacityRoundUp(elementSize, newTotalCount);
            if (allowReduceCapacity && newTotalCount == 0) {
                deque->buffer = NULL;
                XRingBufferDestroy(buffer);
            } else if (allowReduceCapacity && capacity != buffer->capacity && newTotalCount < (capacity + XDequeCapacityRoundUp(elementSize, newTotalCount)) / 2) {
                // resize
                deque->buffer = XRingBufferReplacingElements(buffer, capacity, (capacity - newTotalCount)/2, index, count, items, itemCount, removedItems);
                XRingBufferDestroy(buffer);
            } else {
                XRingBufferReplaceElements(buffer, index, count, items, itemCount, removedItems);
            }
        }
    }
}
