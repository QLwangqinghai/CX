
#ifndef XAllocator_h
#define XAllocator_h

#include "XCoreBase.h"

/// 不需要太大， 有context， context下区分zoneinfo
#define XZoneInfoMax SIZE_C(0x7)
#define XZoneInfoCount SIZE_C(0x8)
#define XZoneInfoBitCount SIZE_C(3)

static inline size_t XAllocatorAlignedSize(size_t size) {
    size_t tmp = sizeof(void *);
    if (size == 0) {
        return tmp;
    }
    tmp -= 1;
    size_t s = (size + tmp) & (~tmp);
    XAssert(s >= size, "");
    return s;
}

typedef size_t XAllocatorOption;
extern const XAllocatorOption XAllocatorOptionStatic;

// size 中的scope 可能会被修改，注意
extern void * _Nonnull XInstanceAllocate(XAllocatorOption option, size_t size, size_t * _Nonnull zoneInfo);
extern void XInstanceDeallocate(void * _Nonnull ptr, size_t zoneInfo);

extern void * _Nullable XAllocateFastWord4(void);
extern void XDeallocateFastWord4(void * _Nonnull ptr);

void testZone(void);

#pragma mark - base

#if CX_TARGET_OS_WINDOWS
#include <malloc.h>
static inline XPtr _Nonnull XAlignedAllocate(size_t size, size_t alignment) {
    assert(size > 0);
    XPtr ptr = _aligned_malloc(size, alignment);
    return ptr;
}
#else
static inline XPtr _Nonnull XAlignedAllocate(size_t size, size_t alignment) {
    assert(size > 0);
    XPtr result = NULL;
    posix_memalign(&result, alignment, size);
    return result;
}
#endif

static inline XPtr _Nullable XTryAllocate(size_t size) {
    if (size < 0) {
        return NULL;
    }
    XPtr ptr = malloc(size);
    return ptr;
}

static inline XPtr _Nonnull XAllocate(size_t size) {
    XPtr ptr = XTryAllocate(size);
    assert(ptr);
    return ptr;
}
static inline void XDeallocate(XPtr _Nonnull ptr) {
    free(ptr);
}

#pragma mark - _XMappedSize

typedef struct _XMappedSize {
    size_t size;
    size_t scope: 6;// 取值范围： [0, 63]， [0, 8]: blockCount<=0x3f,blockSizeShift=3; [9, 63]:0x3f<blockCount<=0x7f, blockSizeShift=e-6;
    size_t blockSizeShift: 6;// 取值范围： [3, 55]=>[11, 63]， blockSize = 0x1 << blockSizeShift;
    size_t blockCount: SIZE_BITS_COUNT - 12;
} XMappedSize_s;


#if CX_TARGET_RT_64_BIT
// 6 + 8
#define MInfo_BlockCountMax SIZE_C(0x1ff)
#define MInfo_BlockCountLargeBase SIZE_C(0x100)
#define MInfo_BlockCountSmallMax SIZE_C(0xff)
#define MInfo_ScopeShift SIZE_C(8)
#define MInfo_SizeMax SIZE_C(0xF000000000000000)
#define MInfo_ScopeMax SIZE_C(63)
#define MInfo_ScopeOffset SIZE_C(8)
#define MInfo_BlockSizeShiftMin SIZE_C(3)
#define MInfo_BlockSizeShiftMax SIZE_C(55)
// [3, 55]=>[11, 63]
#else
// 5 + 9
#define MInfo_BlockCountMax SIZE_C(0x3ff)
#define MInfo_BlockCountLargeBase SIZE_C(0x200)
#define MInfo_BlockCountSmallMax SIZE_C(0x1ff)
#define MInfo_ScopeShift SIZE_C(9)
#define MInfo_SizeMax SIZE_C(0xF0000000)
#define MInfo_ScopeMax SIZE_C(31)
#define MInfo_ScopeOffset SIZE_C(9)
#define MInfo_BlockSizeShiftMin SIZE_C(2)
#define MInfo_BlockSizeShiftMax SIZE_C(22)
// [2, 22]=>[11, 31]
#endif

#define MInfo_BITS_COUNT 14
#define MInfo_CustomScopeMax SIZE_C(10)

static inline XMappedSize_s XMappedSizeWithSize(size_t size) {
    XMappedSize_s info = {};
    XAssert(size <= MInfo_SizeMax, "size too large");
    size_t tmp = (size + (1 << MInfo_BlockSizeShiftMin) - 1) >> MInfo_BlockSizeShiftMin;
    if (tmp <= MInfo_BlockCountSmallMax) {
        info.blockSizeShift = MInfo_BlockSizeShiftMin;
        info.scope = 0;
        info.blockCount = tmp;
        info.size = tmp * (SIZE_C(1) << MInfo_BlockSizeShiftMin);
        return info;
    } else if (tmp <= MInfo_BlockCountMax) {
        info.blockSizeShift = MInfo_BlockSizeShiftMin;
        info.scope = MInfo_BlockSizeShiftMin + MInfo_ScopeOffset;
        info.blockCount = tmp;
        info.size = tmp * (SIZE_C(1) << MInfo_BlockSizeShiftMin);
        return info;
    } else {
        for (size_t e=MInfo_BlockSizeShiftMin+1; e<=MInfo_BlockSizeShiftMax; e++) {
            tmp = (tmp + 1) >> 1;
            size_t blockSize = SIZE_C(1) << e;
            size_t blockCount = (size + blockSize - 1) / blockSize;
            if (tmp <= MInfo_BlockCountMax && tmp > MInfo_BlockCountSmallMax) {
                // good
                info.scope = e + MInfo_ScopeOffset;
                info.blockSizeShift = e;
                info.blockCount = blockCount;
                info.size = blockCount * blockSize;
                return info;
            }
        }
    }
    XAssert(false, "size too large");
}

static inline size_t XMappedSizeEncode(const XMappedSize_s * _Nonnull size) {
    size_t result = 0;
    
    if (size->scope > MInfo_CustomScopeMax) {
        XAssert(size->blockCount <= MInfo_BlockCountMax && size->blockCount > MInfo_BlockCountSmallMax, "");
        XAssert(size->blockSizeShift == size->scope - MInfo_ScopeOffset, "");
    } else {
        XAssert(size->blockCount <= MInfo_BlockCountSmallMax, "");
        XAssert(size->blockSizeShift == MInfo_BlockSizeShiftMin, "");
    }
    XAssert(size->scope <= MInfo_ScopeMax, "");
    result += size->scope;
    result = result << MInfo_ScopeShift;
    result += size->blockCount & MInfo_BlockCountSmallMax;
    return result;
}

static inline XMappedSize_s XMappedSizeDecode(size_t mappedSize) {
    XMappedSize_s info = {};
    info.scope = (mappedSize >> MInfo_ScopeShift) & MInfo_ScopeMax;
    
    if (info.scope > MInfo_CustomScopeMax) {
        info.blockSizeShift = info.scope - MInfo_ScopeOffset;
        info.blockCount = MInfo_BlockCountLargeBase + (mappedSize & MInfo_BlockCountSmallMax);
    } else {
        info.blockSizeShift = MInfo_BlockSizeShiftMin;
        info.blockCount = mappedSize & MInfo_BlockCountSmallMax;
    }
    info.size = info.blockCount * (0x1 << info.blockSizeShift);
    return info;
}

typedef struct __XHeapEntity {
    _Atomic(size_fast_t) _info;
    _Atomic(uintptr_t) next;
} XHeapEntity_s;


#endif /* XFloat_h */
