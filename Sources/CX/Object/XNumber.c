
#include "XRuntime.h"
#include "XObjectInternal.h"
#include "XRuntimeInternal.h"

#include "XCoreBase.h"
#include "XNumberInternal.h"

/*
 符号位(Sign) : 0代表正，1代表为负
 指数位（Exponent）:用于存储科学计数法中的指数数据，并且采用移位存储 float(8) double(11)
 尾数部分（Mantissa）：尾数部分 float(23) double(52)
 */

/*
 TaggedNumber32
 class: 3
 numberType: 2
 content: 26
 footer:1
*/

/*
 TaggedNumber64
 class: 3
 numberType: 2
 content: 58
 footer:1
*/


#if CX_TARGET_OS_WINDOWS
#define copysign(A, B) _copysign(A, B)
#endif


/* The IEEE bit patterns... Also have:
0x7f800000        float +Inf
0x7fc00000        float NaN
0xff800000        float -Inf
*/
#define BITSFORDOUBLEPOSINF32     ((uint32_t)0x7f800000UL)
#define BITSFORDOUBLENAN32   ((uint32_t)0x7fc00000UL)
#define BITSFORDOUBLENEGINF32    ((uint32_t)0xff800000UL)

#define BITSFORDOUBLENAN    ((uint64_t)0x7ff8000000000000ULL)
#define BITSFORDOUBLEPOSINF    ((uint64_t)0x7ff0000000000000ULL)
#define BITSFORDOUBLENEGINF    ((uint64_t)0xfff0000000000000ULL)

// The union dance is to avoid needing hard coded values for different floating point ABIs, technically would be safe to hardcode values, but this way is future proofed
typedef union {
    float32_t floatValue;
    int32_t bits;
} Float32Bits;

typedef union {
    float64_t floatValue;
    int64_t bits;
} Float64Bits;


//正无穷
const XNumberBits32_u XNumberBits32PositiveInfinity = {.u = BITSFORDOUBLEPOSINF32};
const XNumberBits32_u XNumberBits32Nan = {.u = BITSFORDOUBLENAN32};
//负无穷
const XNumberBits32_u XNumberBits32NegativeInfinity = {.u = BITSFORDOUBLENEGINF32};

/// 正无穷
const XNumberBits64_u XNumberBits64PositiveInfinity = {.u = BITSFORDOUBLEPOSINF};
const XNumberBits64_u XNumberBits64Nan = {.u = BITSFORDOUBLENAN};

/// 负无穷
const XNumberBits64_u XNumberBits64NegativeInfinity = {.u = BITSFORDOUBLENEGINF};


#define BITSFORFLOATZERO floatZeroBits.bits
#define BITSFORFLOATONE  floatOneBits.bits

#define BITSFORDOUBLEZERO doubleZeroBits.bits
#define BITSFORDOUBLEONE  doubleOneBits.bits

#if CX_TARGET_OS_DARWIN || CX_TARGET_OS_LINUX || CX_TARGET_OS_ANDROID || CX_TARGET_OS_BSD
#define FLOAT_NEGATIVE_2_TO_THE_127    -0x1.0p+127L
#define FLOAT_POSITIVE_2_TO_THE_127    0x1.0p+127L
#elif CX_TARGET_OS_WINDOWS
#define FLOAT_NEGATIVE_2_TO_THE_127    -170141183460469231731687303715884105728.0
#define FLOAT_POSITIVE_2_TO_THE_127    170141183460469231731687303715884105728.0
#else
#error Unknown or unspecified DEPLOYMENT_TARGET
#endif

XObjectRef _Nonnull __XNumberAllocate(XObjectOption flag, XNumberLayout_e layout, void * _Nonnull valuePtr, size_t size) {
    _XNumber_o * number = XObjectAllocate(XNumberClass, flag, sizeof(_XNumber_o) + size, layout);
    memcpy(number->bits, valuePtr, size);
    return number;
}

XNumberRef _Nonnull XNumberCreateWithUInt8(XObjectOption flag, uint8_t value) {
    return __XNumberCreateUInt64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithSInt8(XObjectOption flag, int8_t value) {
    return __XNumberCreateSInt64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithUInt16(XObjectOption flag, uint16_t value) {
    return __XNumberCreateUInt64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithSInt16(XObjectOption flag, int16_t value) {
    return __XNumberCreateSInt64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithUInt32(XObjectOption flag, uint32_t value) {
    return __XNumberCreateUInt64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithSInt32(XObjectOption flag, int32_t value) {
    return __XNumberCreateSInt64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithUInt64(XObjectOption flag, uint64_t value) {
    return __XNumberCreateUInt64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithSInt64(XObjectOption flag, int64_t value) {
    return __XNumberCreateSInt64(flag, value, __func__);
}

XNumberRef _Nonnull XNumberCreateWithFloat64(XObjectOption flag, float64_t value) {
    return __XNumberCreateFloat64(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithFloat32(XObjectOption flag, float32_t value) {
    return __XNumberCreateFloat32(flag, value, __func__);
}

#if CX_TARGET_RT_64_BIT
XNumberRef _Nonnull XNumberCreateWithUInt128(XObjectOption flag, uint128_t value) {
    return __XNumberCreateUInt128(flag, value, __func__);
}
XNumberRef _Nonnull XNumberCreateWithSInt128(XObjectOption flag, int128_t value) {
    return __XNumberCreateSInt128(flag, value, __func__);
}
#endif
#if CX_TARGET_SUPPORT_FLOAT128
extern XNumberRef _Nonnull XNumberCreateWithFloat128(XObjectOption flag, float128_t value);
#endif

XNumberValue_s XNumberGetValue(XNumberRef _Nonnull number) {
    XAssert(NULL != number, "number connot be NULL");
    XNumberValue_s value = {};
    __XNumberUnpack(number, &value, __func__);
    return value;
}

XComparisonResult __XExpandFloatCompare(XExpandFloat64_t * _Nonnull lhs, XExpandFloat64_t * _Nonnull rhs) {
    // 特殊处理 x? < nan < 0, nan 只小与0， 大于任何负数
    if (isnan(lhs->f) && isnan(rhs->f)) {
        return XCompareEqualTo;
    } else if (isnan(lhs->f)) {
        return rhs->f < 0 ? XCompareGreaterThan : XCompareLessThan;
    } else if (isnan(rhs->f)) {
        return lhs->f < 0 ? XCompareLessThan : XCompareGreaterThan;
    } else {
        // at this point, we know we don't have any NaNs
        if (isinf(lhs->f) | isinf(rhs->f)) {
            // 两个数中有无穷, 只比较float部分
            double s1 = copysign(1.0, lhs->f);
            double s2 = copysign(1.0, rhs->f);
            if (s1 < s2) return XCompareLessThan;
            if (s2 < s1) return XCompareGreaterThan;
            // at this point, we know the signs are the same; do not combine these tests
            if (lhs->f < rhs->f) return XCompareLessThan;
            if (lhs->f < rhs->f) return XCompareGreaterThan;
            return XCompareEqualTo;
        } else {
            // 正常的数
            if (lhs->f == 0 && rhs->f == 0) {
                return XCompareEqualTo;
            } else {
                double s1 = copysign(1.0, lhs->f);
                double s2 = copysign(1.0, rhs->f);
                if (s1 < s2) return XCompareLessThan;
                if (s2 < s1) return XCompareGreaterThan;
                // at this point, we know the signs are the same; do not combine these tests
                if (lhs->f < rhs->f) return XCompareLessThan;
                if (rhs->f < lhs->f) return XCompareGreaterThan;
                
                // 浮点部分相等
                if (s1 < 0) {
                    if (lhs->expand < rhs->expand) return XCompareGreaterThan;
                    if (rhs->expand < lhs->expand) return XCompareLessThan;
                } else {
                    if (lhs->expand < rhs->expand) return XCompareLessThan;
                    if (rhs->expand < lhs->expand) return XCompareGreaterThan;
                }
                return XCompareEqualTo;
            }
        }
    }
}

XComparisonResult XNumberCompare(XNumberRef _Nonnull lhs, XNumberRef _Nonnull rhs) {
    XExpandFloat64_t contentOfLhs = {};
    XExpandFloat64_t contentOfRhs = {};
    __XNumberUnpackToExpandFloat(lhs, &contentOfLhs, __func__);
    __XNumberUnpackToExpandFloat(rhs, &contentOfRhs, __func__);
    return __XExpandFloatCompare(&contentOfLhs, &contentOfRhs);
}

#undef BITSFORDOUBLENAN
#undef BITSFORDOUBLEPOSINF
#undef BITSFORDOUBLENEGINF

void _XNumberDeinit(XObjectRef _Nonnull self) {
    
    
}
XObjectRef _Nonnull _XNumberCopy(XObjectRef _Nonnull self) {
    XObjectRetain(self);
    return self;
}

size_t _XNumberGetHashCode(XObjectRef _Nonnull self) {
    XAssert(NULL != self, "ref is NULL");
    XNumberValue_s content = {};
    __XNumberUnpack(self, &content, __func__);
    switch (content.storageType) {
        case XNumberStorageTypeSInt: {
            return __XNumberHashBigSInt(content.storage.s);
        }
        case XNumberStorageTypeUInt: {
            return __XNumberHashBigUInt(content.storage.u);
        }
        case XNumberStorageTypeFloat: {
            return __XNumberHashBigFloat(content.storage.f);
        }
        default: abort();
    }
}
bool_t _XNumberEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    XExpandFloat64_t contentOfLhs = {};
    XExpandFloat64_t contentOfRhs = {};
    __XNumberUnpackToExpandFloat(lhs, &contentOfLhs, __func__);
    __XNumberUnpackToExpandFloat(rhs, &contentOfRhs, __func__);
    return __XExpandFloatCompare(&contentOfLhs, &contentOfRhs) == XCompareEqualTo;
}
void _XNumberDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XNumberDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}


/* ========================================================================================================================= */

void __XHeapNumberUnpack(XNumberRef _Nonnull ref, XNumberValue_s * _Nonnull ptr, const char * _Nonnull func) {
    XAssert(XNumberClass == XObjectGetClass(ref), "");
    _XNumber_o * number = (_XNumber_o *)ref;
    XNumberLayout_e layout = _XHeapNumberGetLayout(number, func);
    switch (layout) {
        case XNumberLayoutSInt64: {
            int64_t value = 0;
            memcpy(&value, number->bits, sizeof(int64_t));
            ptr->storageType = XNumberStorageTypeSInt;
            ptr->storage.s = value;
        }
            break;
        case XNumberLayoutUInt64: {
            uint64_t value = 0;
            memcpy(&value, number->bits, sizeof(uint64_t));
            ptr->storageType = XNumberStorageTypeUInt;
            ptr->storage.u = value;
        }
            break;
        case XNumberLayoutFloat64: {
            float64_t value = 0;
            memcpy(&value, number->bits, sizeof(float64_t));
            ptr->storageType = XNumberStorageTypeFloat;
            ptr->storage.f = (float64_t)value;
        }
            break;
//#if CX_TARGET_RT_64_BIT
//        case XNumberLayoutSInt128: {
//            int128_t value = 0;
//            memcpy(&value, number->bits, sizeof(int128_t));
//            ptr->storageType = XNumberStorageTypeSInt;
//            ptr->storage.s = value;
//        }
//
//            break;
//        case XNumberLayoutUInt128: {
//            uint128_t value = 0;
//            memcpy(&value, number->bits, sizeof(uint128_t));
//            ptr->storageType = XNumberStorageTypeUInt;
//            ptr->storage.u = value;
//        }
//            break;
//#endif
//        case XNumberLayoutCustom:
//
//            break;
        default: abort();
    }
}

size_t _XNumberGetInstanceSize(XObjectRef _Nonnull self) {
#if CX_TARGET_RT_64_BIT
    XNumberLayout_e layout = _XHeapNumberGetLayout(self, __func__);
    switch (layout) {
        case XNumberLayoutSInt128:
        case XNumberLayoutUInt128:
        case XNumberLayoutFloat128: {
            return sizeof(_XNumber_o) + sizeof(XNumberBits128_u);
        }
        default: return sizeof(_XNumber_o) + sizeof(XNumberBits64_u);
    }
#else
    return sizeof(_XNumber_o) + sizeof(XNumberBits64_u);
#endif
}

void __XNumberUnpack(XNumberRef _Nonnull ref, XNumberValue_s * _Nonnull ptr, const char * _Nonnull func) {
    size_t v = (size_t)((uintptr_t)ref);
    if (__XNumberCheckIsTaggedNumber(v))  {
        size_t numberContent = __XTaggedObjectDecodeContentScopeA((uintptr_t)ref, X_TaggedObjectTypeBits_XNumber, func);
        XNumberStorageType_e mainType = (XNumberStorageType_e)((numberContent & X_Tagged_NumberMainTypeMask) >> X_Tagged_NumberLargeContentBitsCount);
        size_t largeContent = (numberContent & X_BUILD_TaggedNumberLargeContentMask);
        switch (mainType) {
            case XNumberStorageTypeSInt: {
                ptr->storageType = XNumberStorageTypeSInt;
                ptr->storage.s = SInt64ZigzagDecode(largeContent);
            }
                break;
            case XNumberStorageTypeUInt: {
                ptr->storageType = XNumberStorageTypeUInt;
                ptr->storage.u = largeContent;
            }
                break;
            case XNumberStorageTypeFloat: {
                uint64_t fcontent = ((uint64_t)largeContent) << (64 - X_Tagged_NumberLargeContentBitsCount);
                float64_t value = *(float64_t *)(&fcontent);
                ptr->storageType = XNumberStorageTypeFloat;
                ptr->storage.f = value;
            }
                break;
            default: abort();
        }
    } else {
        __XHeapNumberUnpack(ref, ptr, func);
    }
}

void __XHeapNumberUnpackToExpandFloat(XNumberRef _Nonnull ref, XExpandFloat64_t * _Nonnull ptr, const char * _Nonnull func) {
    XAssert(XNumberClass == XObjectGetClass(ref), "");
    _XNumber_o * number = (_XNumber_o *)ref;
    XNumberLayout_e layout = _XHeapNumberGetLayout(number, func);
    switch (layout) {
        case XNumberLayoutSInt64: {
            int64_t value = 0;
            memcpy(&value, number->bits, sizeof(int64_t));
            XSInt64ToExpandFloat64(value, ptr);
        }
            break;
        case XNumberLayoutUInt64: {
            uint64_t value = 0;
            memcpy(&value, number->bits, sizeof(uint64_t));
            XUInt64ToExpandFloat64(value, ptr);
        }
            break;
        case XNumberLayoutFloat64: {
            float64_t value = 0;
            memcpy(&value, number->bits, sizeof(float64_t));
            ptr->f = value;
            ptr->expand = 0;
        }
            break;
        case XNumberLayoutSInt128: {
            int128_t value = 0;
            memcpy(&value, number->bits, sizeof(int128_t));
            XSInt128ToExpandFloat64(value, ptr);
        }
            break;
        case XNumberLayoutUInt128: {
            uint128_t value = 0;
            memcpy(&value, number->bits, sizeof(uint128_t));
            XUInt128ToExpandFloat64(value, ptr);
        }
            break;
        case XNumberLayoutFloat128: {
            abort();
        }
            break;
//        case XNumberLayoutCustom:
//
//            break;
        default: abort();
    }
    
}

void __XNumberUnpackToExpandFloat(XNumberRef _Nonnull ref, XExpandFloat64_t * _Nonnull ptr, const char * _Nonnull func) {
    size_t v = (size_t)((uintptr_t)ref);
    if (__XNumberCheckIsTaggedNumber(v))  {
        size_t numberContent = __XTaggedObjectDecodeContentScopeA((uintptr_t)ref, X_TaggedObjectTypeBits_XNumber, func);

        XNumberStorageType_e mainType = (XNumberStorageType_e)((numberContent & X_Tagged_NumberMainTypeMask) >> X_Tagged_NumberLargeContentBitsCount);
        size_t largeContent = (numberContent & X_BUILD_TaggedNumberLargeContentMask);
        switch (mainType) {
            case XNumberStorageTypeSInt:
                XSInt64ToExpandFloat64(SInt64ZigzagDecode(largeContent), ptr);
                break;
            case XNumberStorageTypeUInt:
                XUInt64ToExpandFloat64(largeContent, ptr);
                break;
            case XNumberStorageTypeFloat: {
                uint64_t fcontent = ((uint64_t)largeContent) << (64 - X_Tagged_NumberLargeContentBitsCount);
                float64_t value = *(float64_t *)(&fcontent);
                ptr->f = value;
                ptr->expand = 0;
            }
                break;
            default: abort();
        }
    } else {
        __XHeapNumberUnpackToExpandFloat(ref, ptr, func);
    }
}
