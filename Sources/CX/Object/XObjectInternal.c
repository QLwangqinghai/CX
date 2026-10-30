#include "XObjectInternal.h"
#include "XRuntimeInternal.h"

//typedef XObjectRef _Nonnull (*XAllocatorAllocate_f)(XClass _Nonnull cls, XObjectOption option);
//typedef void (*XAllocatorDeallocate_f)(XObjectRef _Nonnull object, XClass _Nonnull cls, size_t minfo);


XObjectRef _Nonnull __XClassDataAllocateInstance(XObjectOption option, size_t layout, size_t minSize) {
    return XObjectAllocate(XDataClass, option, minSize, layout);
}
XObjectRef _Nonnull __XClassStringAllocateInstance(XObjectOption option, size_t layout, size_t minSize) {
    return XObjectAllocate(XStringClass, option, minSize, layout);
}

size_t __XHeapStringGetLayout(XObjectRef _Nonnull object) {
    return __XHeapObjectGetLayout(object);
}


#define    ROTL32(x,y)    UInt32RotateLeft(x,y)
#define ROTL64(x,y)    UInt64RotateLeft(x,y)

// OC 最大hash 长度 192 字节
// 3 + 1 + 4 + 8

// __XStringDataByteHash 最大hash长度 200字节
// __XStringDataByteHash 最大hash长度 25 * sizeof(size_t)字节

// 49

//seed：种子，最好用一个质数，比如：0xEE6B27EB(一个40亿内的质数); 返回值非0(内部实现是如果为0， 返回SIZE_MAX)， key必须内存上sizeof(size_t)对齐，结尾用0填充， 对于超过25 * sizeof(size_t)字节长度的数据， hash len按照sizeof(size_t)对齐(不能截断)，之后 hash前 13*sizeof(size_t)字节 中间4*sizeof(size_t)字节 最后8*sizeof(size_t)字节
size_t __XStringDataByteHash(const void * _Nonnull _byte, ssize_t len, size_t seed) {
    XAssert(len >= 0, "");
#if CX_TARGET_RT_64_BIT
    uint64_t blockCount = (len + sizeof(uint64_t) - 1) / sizeof(uint64_t);

    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int64_t r = 47;

    uint64_t h = seed ^ (len * m);
    const uint64_t * blocks = (const uint64_t *)_byte;

    if (blockCount <= 25) {
        const uint64_t * data = blocks;
        const uint64_t * end = blocks + blockCount;

        while (data != end) {
            uint64_t k = *data++;
            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }
    } else {
        const uint64_t * data = blocks;
        const uint64_t * end = blocks + 13;

        while (data != end) {
            uint64_t k = *data++;
            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        // 25 - 21 = 4
        // 4 / 2 = 2

        data += (blockCount - 21) / 2 - 2;
        end = data + 4;
        while (data != end) {
            uint64_t k = *data++;
            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        data = blocks + blockCount - 8;
        end = data + 8;
        while (data != end) {
            uint64_t k = *data++;
            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }
    }

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h % 0xc3a5c85c97cb3127ULL + 1ULL;
//    return h == 0 ? SIZE_MAX : h;
#else
    uint32_t blockCount = (len + sizeof(uint32_t) - 1) / sizeof(uint32_t);
    uint32_t h = seed;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    //----------
    // body
    const uint32_t * blocks = (const uint32_t *)_byte;
    if (blockCount <= 25) {
        const uint32_t * data = blocks;
        const uint32_t * end = blocks + blockCount;

        while (data != end) {
            uint32_t k1 = *data++;
            k1 *= c1;
            k1 = ROTL32(k1,15);
            k1 *= c2;

            h ^= k1;
            h = ROTL32(h,13);
            h = h * 5 + 0xe6546b64;
        }
    } else {
        const uint32_t * data = blocks;
        const uint32_t * end = blocks + 13;
        while (data != end) {
            uint32_t k1 = *data++;
            k1 *= c1;
            k1 = ROTL32(k1,15);
            k1 *= c2;

            h ^= k1;
            h = ROTL32(h,13);
            h = h * 5 + 0xe6546b64;
        }

        // 25 - 21 = 4
        // 4 / 2 = 2
        data += (blockCount - 21) / 2 - 2;
        end = data + 4;
        while (data != end) {
            uint32_t k1 = *data++;
            k1 *= c1;
            k1 = ROTL32(k1,15);
            k1 *= c2;

            h ^= k1;
            h = ROTL32(h,13);
            h = h * 5 + 0xe6546b64;
        }


        data = blocks + blockCount - 8;
        end = data + 8;
        while (data != end) {
            uint32_t k1 = *data++;
            k1 *= c1;
            k1 = ROTL32(k1,15);
            k1 *= c2;

            h ^= k1;
            h = ROTL32(h,13);
            h = h * 5 + 0xe6546b64;
        }
    }
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h % 2147483647UL + 1ULL;
#endif
}

//seed：种子，最好用一个质数，比如：0xEE6B27EB(一个40亿内的质数); 返回值非0(内部实现是如果为0， 返回SIZE_MAX)， key必须内存上sizeof(size_t)对齐，结尾用0填充， 对于超过25 * sizeof(size_t)字节长度的数据， hash len按照sizeof(size_t)对齐(不能截断)，之后 hash前 13*sizeof(size_t)字节 中间4*sizeof(size_t)字节 最后8*sizeof(size_t)字节
void XCollectionHasherInit(XCollectionHasher_s * _Nonnull context, ssize_t count) {
    size_t seed = 0xEE6B27EB;
    XAssert(context, "");
    context->key = 0;
    context->pendingHashCode = 0;
#if CX_TARGET_RT_64_BIT
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    uint64_t h = seed ^ (count * m);
    context->h = h;
#else
    uint32_t h = seed;
    context->h = h;
#endif
    context->count = count;
    context->currentCount = 0;
}

static inline void __XCollectionHasherCombineBlock(XCollectionHasher_s * _Nonnull hasher, size_t block) {
#if CX_TARGET_RT_64_BIT
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int64_t r = 47;
    uint64_t h = hasher->h;
    uint64_t k = block;
    k *= m;
    k ^= k >> r;
    k *= m;
    h ^= k;
    h *= m;
    hasher->h = h;
#else
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    uint32_t k1 = block;
    k1 *= c1;
    k1 = ROTL32(k1,15);
    k1 *= c2;
    h ^= k1;
    h = ROTL32(h,13);
    h = h * 5 + 0xe6546b64;
    hasher->h = h;
#endif
}
static inline void __XCollectionHasherProgress(XCollectionHasher_s * _Nonnull hasher) {
    __XCollectionHasherCombineBlock(hasher, hasher->pendingHashCode);
}

void XCollectionHasherCombine(XCollectionHasher_s * _Nonnull hasher, size_t key, size_t hashCode) {
    if (hasher->currentCount > 0) {
        if (hasher->key == key) {
            hasher->pendingHashCode = hasher->pendingHashCode ^ hashCode;
        } else {
            __XCollectionHasherProgress(hasher);
            hasher->key = key;
            hasher->pendingHashCode = hashCode;
        }
        hasher->currentCount += 1;
    } else {
        hasher->key = key;
        hasher->pendingHashCode = hashCode;
        hasher->currentCount += 1;
    }
}

static inline size_t __XCollectionHasherFinalize(const XCollectionHasher_s * _Nonnull hasher) {
#if CX_TARGET_RT_64_BIT
    uint64_t h = hasher->h;
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    const int64_t r = 47;
    h ^= h >> r;
    h *= m;
    h ^= h >> r;
    return h;
#else
    uint32_t h = hasher->h;
    h ^= hasher->length;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
#endif
}

size_t XCollectionHasherFinalize(XCollectionHasher_s * _Nonnull hasher) {
    if (hasher->currentCount > 0) {
        __XCollectionHasherProgress(hasher);
    }
    size_t h = __XCollectionHasherFinalize(hasher);
#if CX_TARGET_RT_64_BIT
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    return h % m + 1ULL;
#else
    const uint32_t m = 0xcc9e2d51;
    return h % m + 1ULL;
#endif
}



//void XCollectionHasherCombine(XCollectionHasher_s * _Nonnull hasher, const size_t * _Nullable blocks, size_t blockCount) {
//#if CX_TARGET_RT_64_BIT
//    const uint64_t m = 0xc6a4a7935bd1e995ULL;
//    const int64_t r = 47;
//    uint64_t h = hasher->h;
//    const uint64_t * data = blocks;
//    const uint64_t * end = blocks + blockCount;
//
//    while (data != end) {
//        uint64_t k = *data++;
//        k *= m;
//        k ^= k >> r;
//        k *= m;
//
//        h ^= k;
//        h *= m;
//    }
//    hasher->h = h;
//#else
//    const uint32_t c1 = 0xcc9e2d51;
//    const uint32_t c2 = 0x1b873593;
//    const uint32_t * data = blocks;
//    const uint32_t * end = blocks + blockCount;
//
//    while (data != end) {
//        uint32_t k1 = *data++;
//        k1 *= c1;
//        k1 = ROTL32(k1,15);
//        k1 *= c2;
//
//        h ^= k1;
//        h = ROTL32(h,13);
//        h = h * 5 + 0xe6546b64;
//    }
//    hasher->h = h;
//#endif
//}

//size_t XCollectionHasherFinalize(const XCollectionHasher_s * _Nonnull hasher) {
//#if CX_TARGET_RT_64_BIT
//    uint64_t h = hasher->h;
//    const uint64_t m = 0xc6a4a7935bd1e995ULL;
//    const int64_t r = 47;
//    h ^= h >> r;
//    h *= m;
//    h ^= h >> r;
//    return h;
//#else
//    uint32_t h = hasher->h;
//    h ^= hasher->length;
//    h ^= h >> 16;
//    h *= 0x85ebca6b;
//    h ^= h >> 13;
//    h *= 0xc2b2ae35;
//    h ^= h >> 16;
//    return h;
//#endif
//}
#undef ROTL32
#undef ROTL64

size_t XCollectionHasherFix(size_t h) {
#if CX_TARGET_RT_64_BIT
    const uint64_t m = 0xc6a4a7935bd1e995ULL;
    return h % m + 1ULL;
#else
    const uint32_t m = 0xcc9e2d51;
    return h % m + 1ULL;
#endif
}

//seed：种子，最好用一个质数，比如：0xEE6B27EB(一个40亿内的质数); 返回值非0(内部实现是如果为0， 返回SIZE_MAX)， key必须内存上sizeof(size_t)对齐，结尾用0填充， 对于超过25 * sizeof(size_t)字节长度的数据， hash len按照sizeof(size_t)对齐(不能截断)，之后 hash前 13*sizeof(size_t)字节 中间4*sizeof(size_t)字节 最后8*sizeof(size_t)字节
//size_t __XStringDataByteHash22(const void * _Nonnull _byte, ssize_t len, size_t seed) {
//    XAssert(len >= 0, "");
//
//    XCollectionHasher_s hasher = {};
//    XCollectionHasherInit(&hasher, len, seed);
//
//    const size_t * blocks = (const size_t *)_byte;
//    size_t blockCount = (len + sizeof(size_t) - 1) / sizeof(size_t);
//    if (blockCount <= 25) {
//        XCollectionHasherCombine(&hasher, blocks, blockCount);
//    } else {
//        XCollectionHasherCombine(&hasher, blocks, 13);
//
//        size_t offset = (blockCount - 21) / 2 - 2;
//        XCollectionHasherCombine(&hasher, blocks + offset, 4);
//
//        offset = blockCount - 8;
//        XCollectionHasherCombine(&hasher, blocks + offset, 8);
//    }
//
//    size_t result = XCollectionHasherFinalize(&hasher);
//    return XCollectionHasherFix(result);
//}


//seed：种子，最好用一个质数，比如：0xEE6B27EB(一个40亿内的质数); 返回值非0(内部实现是如果为0， 返回SIZE_MAX)， key必须内存上sizeof(size_t)对齐，结尾用0填充， 对于超过25 * sizeof(size_t)字节长度的数据， hash len按照sizeof(size_t)对齐(不能截断)，之后 hash前 13*sizeof(size_t)字节 中间4*sizeof(size_t)字节 最后8*sizeof(size_t)字节
size_t _XStringDataByteHash(const void * _Nonnull _byte, ssize_t len) {
    return __XStringDataByteHash(_byte, len, 0xEE6B27EB);
}
