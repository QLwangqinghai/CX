

#ifndef XDeque_h
#define XDeque_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XRingBuffer.h"


/// HashTable 使用
typedef struct {
    // 元素容量， 需要搭配元素个数、elemetnSize 使用
    XRingBuffer_s * _Nullable buffer;
} XDeque_s;

#pragma mark - XDeque_s

// 每次加大2/3 或者 1/3倍
extern size_t XCollectionSizeRoundUp(size_t size);
extern size_t XCollectionSizeRoundDown(size_t size);

extern size_t XDequeCapacityRoundUp(size_t elementSize, size_t count);
extern size_t XDequeCapacityRoundDown(size_t elementSize, size_t count);

#pragma mark - XDeque

extern void XDequeInit(XDeque_s * _Nonnull deque, size_t elementSize, size_t capacity);
extern void XDequeInitWithElements(XDeque_s * _Nonnull deque, size_t elementSize, const void * _Nullable elements, size_t elementCount);
extern void XDequeDeinit(XDeque_s * _Nonnull deque);

static inline ssize_t XDequeGetCount(XDeque_s * _Nonnull deque) {
    return NULL == deque->buffer ? 0 : deque->buffer->count;
}
static inline ssize_t XDequeGetCapacity(XDeque_s * _Nonnull deque) {
    return NULL == deque->buffer ? 0 : deque->buffer->capacity;
}
extern void XDequeResize(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t minCapacity);

extern void * _Nonnull XDequeElementAtIndex(XDeque_s * _Nonnull deque, ssize_t index);

extern void XDequeReplaceElements(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t index, ssize_t count, const void * _Nullable items, ssize_t itemCount, bool_t allowReduceCapacity, void * _Nullable removedItems);

static inline void XDequeInsertElement(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t index, const void * _Nonnull item) {
    XDequeReplaceElements(deque, elementSize, index, 0, item, 1, true, NULL);
}
static inline void XDequeAppendElement(XDeque_s * _Nonnull deque, size_t elementSize, const void * _Nonnull item) {
    XDequeReplaceElements(deque, elementSize, XDequeGetCount(deque), 0, item, 1, true, NULL);
}
static inline void XDequePrependElement(XDeque_s * _Nonnull deque, size_t elementSize, const void * _Nonnull item) {
    XDequeReplaceElements(deque, elementSize, 0, 0, item, 1, true, NULL);
}
static inline void XDequeRemoveElement(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t index, bool_t allowReduceCapacity, void * _Nonnull item) {
    XDequeReplaceElements(deque, elementSize, index, 1, NULL, 0, allowReduceCapacity, item);
}
static inline void XDequeReplaceElement(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t index, const void * _Nonnull item, void * _Nonnull old) {
    XDequeReplaceElements(deque, elementSize, index, 1, item, 1, false, old);
}
static inline ssize_t XDequeRemoveAll(XDeque_s * _Nonnull deque, size_t elementSize, bool_t allowReduceCapacity, void * _Nonnull items) {
    ssize_t count = XDequeGetCount(deque);
    XDequeReplaceElements(deque, elementSize, 0, count, NULL, 0, allowReduceCapacity, items);
    return count;
}

#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XDeque_h */
