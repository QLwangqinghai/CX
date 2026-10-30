

#ifndef XRingBuffer_h
#define XRingBuffer_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XCoreBase.h"
#include "XAllocator.h"


//extern XResultCode32 XRingBufferWriteBytes(XRingBuffer2_s * _Nonnull buffer, const uint8_t * _Nonnull bytes, size_t length);
//extern XResultCode32 XRingBufferReadBytes(XRingBuffer2_s * _Nonnull buffer, uint8_t * _Nonnull bytes, size_t length);
//extern XResultCode32 XRingBufferSeek(XRingBuffer2_s * _Nonnull buffer, size_t length);

//64 96  128  zoneInfo
// map: 2 4 6
// set: 4 8 12

// using node or array

typedef struct {
    // headerLength = sizeof(size_t) * 4
    // 元素容量， 需要搭配元素个数、elemetnSize 使用
    const size_t zoneInfo: XZoneInfoBitCount;
    const size_t elementSize: SIZE_BITS_COUNT - XZoneInfoBitCount;
    const size_t capacity;
    ssize_t count;
    size_t offset;
    
    uint8_t items[0];
} XRingBuffer_s;

typedef struct {
    // 元素个数， 需要搭配elemetnSize 使用
    ssize_t count;
    uint8_t * _Nullable items;
} XVector_s;

static inline XVector_s XVectorMake(ssize_t count, uint8_t * _Nullable items) {
    if (count > 0) {
        XAssert(items, "");
    }
    XVector_s result = {
        .count = count,
        .items = items,
    };
    return result;
}

// 从前往后 reverse=0； 否则reverse=1, sum(src.item) = sum(dst.item)
extern void XVectorBufferMove(XVector_s * _Nonnull dst, size_t dstVectorCount, size_t elementSize, XVector_s * _Nonnull src, size_t srcVectorCount, bool_t reverse);
extern void XVectorBufferClear(XVector_s * _Nonnull vectors, size_t vectorCount, size_t elementSize);
extern size_t XVectorBufferGetContent(const XVector_s * _Nonnull vectors, size_t vectorCount, size_t elementSize, uint8_t * _Nonnull buffer);
extern size_t XVectorBufferSetContent(const XVector_s * _Nonnull vectors, size_t vectorCount, size_t elementSize, const uint8_t * _Nonnull buffer);

#pragma mark - XRingBuffer_s

extern void XRingBufferClear(XRingBuffer_s * _Nonnull array, ssize_t index, ssize_t count);
// 把array的 从index到index+count， 替换成newcount个NULL
extern void XRingBufferMove(XRingBuffer_s * _Nonnull array, ssize_t index, ssize_t count, ssize_t distance);

#pragma mark - XRingBuffer

/// capacity == 0 时， 返回NULL
extern XRingBuffer_s * _Nonnull XRingBufferCreate(size_t elementSize, size_t capacity, size_t offset);

/// itemCount == 0 时， 返回NULL
extern XRingBuffer_s * _Nonnull XRingBufferCreateWithElements(size_t elementSize, size_t capacity, size_t offset, const void * _Nullable items, size_t itemCount);

extern XRingBuffer_s * _Nullable XRingBufferCreateWithVectors(size_t elementSize, size_t capacity, size_t offset, XVector_s * _Nonnull vectors, size_t vectorCount);

extern void XRingBufferDestroy(XRingBuffer_s * _Nullable deque);

extern uint8_t * _Nonnull XRingBufferElementAtIndex(const XRingBuffer_s * _Nonnull buffer, ssize_t index);

extern void XRingBufferGetVectors(const XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, XVector_s vectors[_Nonnull 2]);
extern void XRingBufferGetElements(const XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, void * _Nonnull elements);
extern void XRingBufferSetElements(const XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, const void * _Nonnull elements);

extern void XRingBufferReplaceElements(XRingBuffer_s * _Nonnull buffer, ssize_t index, ssize_t count, const void * _Nullable items, ssize_t itemCount, void * _Nullable removedItems);
extern XRingBuffer_s * _Nonnull XRingBufferReplacingElements(XRingBuffer_s * _Nonnull buffer, size_t capacity, size_t offset, ssize_t index, ssize_t count, const void * _Nullable items, ssize_t itemCount, void * _Nullable removedItems);
static inline void XRingBufferInsertElement(XRingBuffer_s * _Nonnull buffer, ssize_t index, const void * _Nonnull item) {
    XRingBufferReplaceElements(buffer, index, 0, item, 1, NULL);
}
static inline void XRingBufferRemoveElement(XRingBuffer_s * _Nonnull buffer, ssize_t index, void * _Nonnull item) {
    XRingBufferReplaceElements(buffer, index, 1, NULL, 0, item);
}
static inline void XRingBufferReplaceElement(XRingBuffer_s * _Nonnull buffer, ssize_t index, const void * _Nonnull item, void * _Nonnull old) {
    XRingBufferReplaceElements(buffer, index, 1, item, 1, old);
}

typedef int (*XRingBufferCompare_f)(void * _Nonnull element, void * _Nonnull target, void * _Nullable context);

/// 如果buffer的顺序是降序，则reverse 需要=true,  返回true时，location 为匹配的位置， 如果返回false，location 为插入的位置
extern bool_t XRingBufferBSearch(XRingBuffer_s * _Nonnull buffer, bool_t reverse, void * _Nonnull target, XRingBufferCompare_f _Nonnull compare, void * _Nullable context, ssize_t * _Nonnull location);

#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XRingBuffer_h */
