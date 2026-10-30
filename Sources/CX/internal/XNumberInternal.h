
#ifndef XNumberInternal_h
#define XNumberInternal_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XNumber.h"
#include "XCoreBase.h"
#include "XObjectInternal.h"
#include "XRuntimeInternal.h"

#define X_Tagged_NumberLargeContentBitsCount (X_TaggedObjectScopeAContentBitCount - 2)
#define X_Tagged_NumberMainTypeMask (SIZE_C(0x3) << X_Tagged_NumberLargeContentBitsCount)
#define X_BUILD_TaggedNumberLargeContentMask  ((SIZE_C(1) << X_Tagged_NumberLargeContentBitsCount) - 1)

/// 取值范围最大7
typedef enum {
    XNumberLayoutNone = 0,
    XNumberLayoutSInt64,
    XNumberLayoutUInt64,
    XNumberLayoutFloat64,
#if CX_TARGET_RT_64_BIT
    XNumberLayoutSInt128,
    XNumberLayoutUInt128,
    XNumberLayoutFloat128,
#endif
    XNumberLayoutCustom = 0x7,
} XNumberLayout_e;

static inline XNumberRef _Nonnull ___XNumberMakeTagged(XNumberStorageType_e _type, size_t content, const char * _Nonnull func) {
    size_t type = _type;
    size_t numberContent = (type << X_Tagged_NumberLargeContentBitsCount) | content;
    return __XTaggedObjectEncodeScopeA(X_TaggedObjectTypeBits_XNumber, numberContent, func);
}

#if CX_TARGET_RT_64_BIT
static inline XNumberRef _Nullable __XNumberTryMakeTaggedSInt128(int128_t _value, const char * _Nonnull func) {
    uint128_t value = SInt128ZigzagEncode(_value);
    if (0 != (value >> X_Tagged_NumberLargeContentBitsCount)) {
        return NULL;
    }
    return ___XNumberMakeTagged(XNumberStorageTypeSInt, (size_t)value, func);
}

static inline XNumberRef _Nullable __XNumberTryMakeTaggedUInt128(uint128_t value, const char * _Nonnull func) {
    if (0 != (value >> X_Tagged_NumberLargeContentBitsCount)) {
        return NULL;
    }
    return ___XNumberMakeTagged(XNumberStorageTypeUInt, (size_t)value, func);
}
#endif

static inline XNumberRef _Nullable __XNumberTryMakeTaggedSInt64(int64_t _value, const char * _Nonnull func) {
    uint64_t value = SInt64ZigzagEncode(_value);
    if (0 != (value >> X_Tagged_NumberLargeContentBitsCount)) {
        return NULL;
    }
    return ___XNumberMakeTagged(XNumberStorageTypeSInt, (size_t)value, func);
}

static inline XNumberRef _Nullable __XNumberTryMakeTaggedUInt64(uint64_t value, const char * _Nonnull func) {
    if (0 != (value >> X_Tagged_NumberLargeContentBitsCount)) {
        return NULL;
    }
    return ___XNumberMakeTagged(XNumberStorageTypeUInt, (size_t)value, func);
}

static inline XNumberRef _Nullable ___XNumberTryMakeTaggedFloat64(float64_t _value, const char * _Nonnull func) {
    uint64_t value = *(uint64_t *)(&_value);
    if (0 == (value << X_Tagged_NumberLargeContentBitsCount)) {
        uint64_t content64 = value >> (64 - X_Tagged_NumberLargeContentBitsCount);
        return ___XNumberMakeTagged(XNumberStorageTypeFloat, (size_t)content64, func);
    } else {
        return NULL;
    }
}

#if CX_TARGET_SUPPORT_FLOAT128
static inline XNumberRef _Nullable ___XNumberTryMakeTaggedFloat128(float128_t _value, const char * _Nonnull func) {
    uint128_t value = 0;
    memcpy(&value, &_value, sizeof(uint128_t));
    if (0 == (value << X_Tagged_NumberLargeContentBitsCount)) {
        uint128_t tmp = value >> (128 - X_Tagged_NumberLargeContentBitsCount)
        size_t content = (uint64_t)tmp;
        return ___XNumberMakeTagged(XNumberStorageTypeFloat128, content, func);
    } else {
        return NULL;
    }
}
#endif


/// 用来做比较大小
extern void __XNumberUnpackToExpandFloat(XNumberRef _Nonnull ref, XExpandFloat64_t * _Nonnull ptr, const char * _Nonnull func);

/// 用来提取值
extern void __XNumberUnpack(XNumberRef _Nonnull ref, XNumberValue_s * _Nonnull ptr, const char * _Nonnull func);


extern XObjectRef _Nonnull __XNumberAllocate(XObjectOption flag, XNumberLayout_e layout, void * _Nonnull valuePtr, size_t size);


static inline XNumberRef _Nonnull __XNumberCreateSInt64(XObjectOption flag, int64_t value, const char * _Nonnull func) {
    XNumberRef result = __XNumberTryMakeTaggedSInt64(value, func);
    if (NULL == result) {
        result = __XNumberAllocate(flag, XNumberLayoutSInt64, &value, sizeof(value));
    }
    return result;
}
static inline XNumberRef _Nonnull __XNumberCreateUInt64(XObjectOption flag, uint64_t value, const char * _Nonnull func) {
    XNumberRef result = __XNumberTryMakeTaggedUInt64(value, func);
    if (NULL == result) {
        result = __XNumberAllocate(flag, XNumberLayoutUInt64, &value, sizeof(value));
    }
    return result;
}
static inline XNumberRef _Nullable __XNumberCreateFloat64(XObjectOption flag, float64_t value, const char * _Nonnull func) {
    XNumberRef result = ___XNumberTryMakeTaggedFloat64(value, func);
    if (NULL == result) {
        result = __XNumberAllocate(flag, XNumberLayoutFloat64, &value, sizeof(value));
    }
    return result;
}
static inline XNumberRef _Nullable __XNumberCreateFloat32(XObjectOption flag, float32_t _value, const char * _Nonnull func) {
    float64_t value = (float64_t)_value;
    XNumberRef result = ___XNumberTryMakeTaggedFloat64(value, func);
    if (NULL == result) {
        result = __XNumberAllocate(flag, XNumberLayoutFloat64, &value, sizeof(value));
    }
    return result;
}

#if CX_TARGET_RT_64_BIT
static inline XNumberRef _Nonnull __XNumberCreateSInt128(XObjectOption flag, int128_t value, const char * _Nonnull func) {
    XNumberRef result = __XNumberTryMakeTaggedSInt128(value, func);
    if (NULL == result) {
        result = __XNumberAllocate(flag, XNumberLayoutSInt128, &value, sizeof(value));
    }
    return result;
}
static inline XNumberRef _Nonnull __XNumberCreateUInt128(XObjectOption flag, uint128_t value, const char * _Nonnull func) {
    XNumberRef result = __XNumberTryMakeTaggedUInt128(value, func);
    if (NULL == result) {
        result = __XNumberAllocate(flag, XNumberLayoutUInt128, &value, sizeof(value));
    }
    return result;
}
#endif

#if CX_TARGET_SUPPORT_FLOAT128
static inline XNumberRef _Nonnull __XNumberCreateFloat128(XObjectOption flag, float128_t value, const char * _Nonnull func) {
    XNumberRef result = ___XNumberTryMakeTaggedFloat128(value, func);
    if (NULL == result) {
        result = __XNumberAllocate(flag, XNumberLayoutFloat128, &value, sizeof(value));
    }
    return result;
}
#endif


static inline _XNumber_o * _Nonnull __XHeapObjectAsNumber(XNumberRef _Nonnull ref, const char * _Nonnull func) {
    return (_XNumber_o *)_XHeapObjectAs(ref, XNumberClass, func);
}

static inline XNumberLayout_e _XHeapNumberGetLayout(_XNumber_o * _Nonnull ref, const char * _Nonnull func) {
    return (XNumberLayout_e)XObjectGetLayout(ref);
}

extern void __XHeapNumberUnpack(XNumberRef _Nonnull ref, XNumberValue_s * _Nonnull ptr, const char * _Nonnull func);

static inline bool_t __XNumberCheckIsTaggedNumber(uintptr_t v) {
    return (v & X_TaggedObjectFlag) == X_TaggedObjectFlag;
}

#pragma mark - hash


/*
 HeapNumebr 超大数：统一转化成同一种类型
 */

//const uint64_t m = 0xc6a4a7935bd1e995ULL;
//const uint32_t c2 = 0x1b873593;

#if CX_TARGET_RT_64_BIT
#define HASHFACTOR 0xc6a4a7935bd1e995ULL
#else
#define HASHFACTOR 0x1b873593
#endif

//#define HASHFACTOR 2654435761U
#define FLOAT_POSITIVE_2_TO_THE_64    Float64Positive2ToThe64

// hash的逻辑 (uint)(abs(number))

static inline size_t __XNumberHashUInt(size_t i) {
    return i * HASHFACTOR;
}
static inline size_t __XNumberHashSInt(ssize_t i) {
    return __XNumberHashUInt((size_t)((i > 0) ? (size_t)(i) : (size_t)(-i)));
}
static inline size_t __XNumberHashUInt64(uint64_t i) {
    return __XNumberHashUInt((size_t)(i & SIZE_MAX));
}
static inline size_t __XNumberHashSInt64(int64_t i) {
    return __XNumberHashUInt64((size_t)((i > 0) ? (uint64_t)(i) : (uint64_t)(-i)));
}
static inline size_t __XNumberHashFloat64(float64_t d) {
    if (isnan(d)) {
        return __XNumberHashUInt(SIZE_MAX-1);
    } else if (isinf(d)) {
        if (d < 0) {
            return __XNumberHashUInt(SIZE_MAX);
        } else {
            return __XNumberHashUInt(SIZE_MAX >> SIZE_C(1));
        }
    } else {
        const double positive = (d < 0) ? -d : d;
        
        //如果截取， 0 附近的数据会比较多
        const double positiveInt = floor(positive + 0.5);
        
        const double fractional = (positive - positiveInt);
        uint64_t content = (uint64_t)fmod(positiveInt, FLOAT_POSITIVE_2_TO_THE_64);
        
        const double absfractional = fabs(fractional);
        uint64_t content2 = *((uint64_t *)&(absfractional));
        if (fractional < 0) {
            content -= content2;
        } else if (fractional > 0) {
            content += content2;
        }
        return __XNumberHashUInt64(content);
    }
}

#if CX_TARGET_RT_64_BIT
static inline size_t __XNumberHashBigUInt(uint128_t i) {
    return __XNumberHashUInt64((uint64_t)(i & UINT64_MAX));
}
static inline size_t __XNumberHashBigSInt(int128_t i) {
    return __XNumberHashBigUInt((uint128_t)((i > 0) ? (uint128_t)(i) : (uint128_t)(-i)));
}
static inline size_t __XNumberHashBigFloat(float64_t f) {
    return __XNumberHashFloat64(f);
}
#else
static inline size_t __XNumberHashBigUInt(uint64_t i) {
    return __XNumberHashUInt64(i);
}
static inline size_t __XNumberHashBigSInt(int64_t i) {
    return __XNumberHashSInt64(i);
}
static inline size_t __XNumberHashBigFloat(float64_t f) {
    return __XNumberHashFloat64(f);
}
#endif


#if defined(__cplusplus)

}  // extern C
#endif

#endif /* XNumberInternal_h */
