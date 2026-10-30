
#ifndef XNumber_h
#define XNumber_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XObject.h"

// sign: 1, shift:  bits
// 整数部分， 小数部分
// 整数部分 = number << n
// 小数部分 = number >> n

typedef union {
    int32_t s;
    uint32_t u;
    float32_t f;
} XNumberBits32_u;

typedef union {
    int64_t s;
    uint64_t u;
    float64_t f;
} XNumberBits64_u;

#if CX_TARGET_RT_64_BIT

typedef union {
    int128_t s;
    uint128_t u;
#if CX_TARGET_SUPPORT_FLOAT128
    float128_t f;
#endif
} XNumberBits128_u;
#endif

typedef union {
#if CX_TARGET_RT_64_BIT
    int128_t s;
    uint128_t u;
    float64_t f;
#else
    int64_t s;
    uint64_t u;
    float64_t f;
#endif
} XNumberStorage_u;

typedef union {
    int64_t s;
    uint64_t u;
    float64_t f;
} XNumberStorage64_u;

/// 取值范围最大63
typedef enum {
    XNumberStorageTypeNone = 0x0,
    XNumberStorageTypeSInt,
    XNumberStorageTypeUInt,
    XNumberStorageTypeFloat,
} XNumberStorageType_e;

typedef struct {
    XNumberStorageType_e storageType;
    XNumberStorage_u storage;
} XNumberValue_s;

typedef struct {
    XNumberStorageType_e storageType;
    XNumberStorage64_u storage;
} XNumberValue64_s;

typedef struct {
    // 当f是0/nan/inf时，expand 必须为0, 当f是0时，指数为0，是个特殊值，指数为0，尾数为0才表示1， 尾数不为0 表示一个很小很小的浮点数， 这里的expand 是正常浮点数的尾数拓展， 即此时指数不是最大值也不是最小值
    float64_t f;
#if CX_TARGET_RT_64_BIT
    uint128_t expand;
#else
    uint64_t expand;
#endif
} XExpandFloat64_t;


typedef struct {
    int64_t e;
    // signAndSignificand
    uint64_t ss;
} XCNumber_s;

static inline XCNumber_s XCNumberMake(int64_t e, uint64_t ss) {
    XCNumber_s number = {
        .e = e,
        .ss = ss,
    };
    return number;
}

static inline bool_t XCNumberIsNan(XCNumber_s number) {
    return number.e == INT64_MAX && (number.ss & (UINT64_MAX >> 1)) != 0;
}
static inline bool_t XCNumberIsInfinity(XCNumber_s number) {
    return number.e == INT64_MAX && (number.ss & (UINT64_MAX >> 1)) == 0;
}
static inline bool_t XCNumberIsZero(XCNumber_s number) {
    return number.e == INT64_MIN && (number.ss & (UINT64_MAX >> 1)) == 0;
}
/// -inf
static inline bool_t XCNumberIsNegativeInfinity(XCNumber_s number) {
    return number.e == INT64_MAX && number.ss == (UINT64_C(1) << 63);
}
/// +inf
static inline bool_t XCNumberIsPositiveInfinity(XCNumber_s number) {
    return number.e == INT64_MAX && number.ss == 0;
}

/// 正常的数 （去掉nan、+inf、-inf）
static inline bool_t XCNumberIsFinite(XCNumber_s number) {
    return number.e != INT64_MAX;
}

/// isnormal 是否是规格数

#define BITS_FOR_DOUBLE_NAN    ((uint64_t)0x7ff8000000000000ULL)
#define BITS_FOR_DOUBLE_POSINF    ((uint64_t)0x7ff0000000000000ULL)
#define BITS_FOR_DOUBLE_NEGINF    ((uint64_t)0xfff0000000000000ULL)

static inline XNumberValue64_s XCNumberGetValue(XCNumber_s number) {
    XNumberValue64_s result = {};
    if (XCNumberIsNan(number)) {
        uint64_t bits = BITS_FOR_DOUBLE_NAN;
        result.storageType = XNumberStorageTypeFloat;
        result.storage.f = *(float64_t *)&(bits);
    } else if (XCNumberIsInfinity(number)) {
        uint64_t bits = XCNumberIsPositiveInfinity(number) ? BITS_FOR_DOUBLE_POSINF : BITS_FOR_DOUBLE_NEGINF;
        result.storageType = XNumberStorageTypeFloat;
        result.storage.f = *(float64_t *)&(bits);
    } else if (XCNumberIsZero(number)) {
        result.storageType = XNumberStorageTypeFloat;
        result.storage.f = 0.0;
    } else {
        uint64_t sign = number.ss & (UINT64_C(1) << 63);
        uint64_t m = number.ss & (UINT64_MAX >> 1);
        if (number.e > -1023 && number.e < 1024) {
            uint64_t e = number.e + 1023;
            uint64_t bits = sign | (e << 52) | (m >> 11);
            uint64_t trailingZerosCount = XUInt64TrailingZerosCount(m);
            if (trailingZerosCount >= 11) {
                result.storageType = XNumberStorageTypeFloat;
                result.storage.f = *(float64_t *)&(bits);
            } else {
                uint64_t m2 = (UINT64_C(1) << 63) | m;
                int64_t trailingZerosCount = XUInt64TrailingZerosCount(m2);
                if (number.e >= 0 && number.e <= 63 && 63 - number.e <= trailingZerosCount) {
                    uint64_t value = m2 >> (63 - number.e);
                    uint64_t sint64Min = UINT64_C(1) << 63;
                    if (sign) {// 负数
                        if (value == sint64Min) {
                            result.storageType = XNumberStorageTypeSInt;
                            result.storage.s = INT64_MIN;
                        } else if (value < sint64Min) {
                            int64_t sv = value;
                            result.storageType = XNumberStorageTypeSInt;
                            result.storage.s = sv;
                        } else {
                            result.storageType = XNumberStorageTypeNone;
                            result.storage.u = 0;
                        }
                    } else {
                        if (value < sint64Min) {
                            int64_t sv = value;
                            result.storageType = XNumberStorageTypeSInt;
                            result.storage.s = sv;
                        } else {
                            result.storageType = XNumberStorageTypeUInt;
                            result.storage.u = value;
                        }
                    }
                } else {
                    result.storageType = XNumberStorageTypeNone;
                    result.storage.u = 0;
                }
            }
        } else if (number.e >= 1024) {
            result.storageType = XNumberStorageTypeNone;
            result.storage.u = 0;
        } else { // number.e <= -1023
            m = (UINT64_C(1) << 63) | m;
            int64_t trailingZerosCount = XUInt64TrailingZerosCount(m);
            int64_t eoffset = -1023 - number.e + 12;
            if (trailingZerosCount >= eoffset) {
                uint64_t bits = sign | (m >> eoffset);
                result.storageType = XNumberStorageTypeFloat;
                result.storage.f = *(float64_t *)&(bits);
            } else {
                result.storageType = XNumberStorageTypeNone;
                result.storage.u = 0;
            }
        }
    }
    return result;
}

static inline XCNumber_s XCNumberMakeWithFloat64(float64_t f) {
    XCNumber_s number = {};
    uint64_t bits = *(uint64_t *)&(f);
    uint64_t sign = bits & (UINT64_C(1) << 63);
    uint64_t te = (bits & UINT64_C(0x7FF0000000000000)) >> 52;
    uint64_t m = (bits & UINT64_C(0xFFFFFFFFFFFFF)) << UINT64_C(12);
    int64_t e = (int64_t)te - 1023;

    // 2047 - 1023 = 1024, // nan +inf -inf
    // 0 - 1023 = -1023, 非规约数 / 0
    if (e == 1024) {// nan inf
        if (0 != m) {
            // nan
            number.e = INT64_MAX;
            number.ss = UINT64_C(1) << UINT64_C(62);
        } else {
            // inf
            number.e = INT64_MAX;
            number.ss = sign;
        }
    } else if (e == -1023) {
        // 非规约数
        if (0 == m) {
            //0
            number.e = INT64_MIN;
            number.ss = 0;
        } else {
            // 非0
            // [1, 52], bit为1的最高位要移除
            uint64_t shift = XUInt64LeadingZerosCount(m) + 1;
            XAssert(shift <= 52, "");
            m = m << shift;
            e -= shift;
            
            number.e = e;
            number.ss = sign | (m >> 1);
        }
    } else {
        // e: [1, 2046]
        number.e = e;
        number.ss = sign | (m >> 1);
    }
    return number;
}

static inline XCNumber_s __XCNumberMakeWithInt64(uint64_t v, uint64_t sign) {
    XCNumber_s number = {};
    if (v == 0) {
        number.e = INT64_MIN;
        number.ss = 0;
    } else {
        // 高位->低位 前导0个数
        uint64_t leadingZeroCount = XUInt64LeadingZerosCount(v);
        int64_t e = leadingZeroCount + 1;
        uint64_t m = v << e;
        
        number.e = 64 - e;
        number.ss = sign | (m >> 1);
    }
    return number;
}

static inline XCNumber_s XCNumberMakeWithSInt64(int64_t value) {
    uint64_t v = value > 0 ? value : value * (-1);
    uint64_t sign = value > 0 ? 0 : UINT64_C(1) << UINT64_C(63);;
    return __XCNumberMakeWithInt64(v, sign);
}

static inline XCNumber_s XCNumberMakeWithUInt64(uint64_t v) {
    return __XCNumberMakeWithInt64(v, 0);
}

/*
 encode zigzagEncode(e) + replaceTopMostWithSign(m, sign)
 decode zigzagDecode(byte) + decode(sign, m)
 */
typedef struct {
    // nan +inf -inf 0 formal
    uint32_t scope: 3;
    uint32_t length: 28;
    uint32_t sign: 1;
    int32_t e;
    // 尾数最高位不隐藏， 编码时需要用符号位替换最高位
    uint8_t m[64];
} XLargeFloat_t;

typedef struct {
    // 当f是0/nan/inf时，expand 必须为0, 当f是0时，指数为0，是个特殊值，指数为0，尾数为0才表示1， 尾数不为0 表示一个很小很小的浮点数， 这里的expand 是正常浮点数的尾数拓展， 即此时指数不是最大值也不是最小值
    float64_t f;
#if CX_TARGET_RT_64_BIT
    uint128_t expand;
#else
    uint64_t expand;
#endif
} XLargeFloat64_t;

#if CX_TARGET_RT_64_BIT
static inline void __XInt128ToExpandFloat64(uint128_t v, uint64_t sign, XExpandFloat64_t * _Nonnull num) {
    XAssert(0 != v, "");
    uint64_t bits = sign;
    
    // 高位->低位 前导0个数
    uint64_t leadingZeroCount = XUInt128LeadingZerosCount(v);
    uint64_t e = leadingZeroCount + 1;
    uint128_t tmp = v << e;
    
    // 把tmp的高53位放到float中， 剩余放expand中
    num->expand = tmp << 53;
    uint64_t m = (uint64_t)(tmp >> 75);
    
    uint64_t te = 1023 + 128 - e;

    bits = bits | (te << 52) | (m & 0xFFFFFFFFFFFFFULL);
    memcpy(&(num->f), &bits, sizeof(double));
}

static inline void XSInt128ToExpandFloat64(int128_t v, XExpandFloat64_t * _Nonnull num) {
    if (0 == v) {
        num->f = 0;
        num->expand = 0;
    } else {
        if (v < 0) {
            __XInt128ToExpandFloat64((uint128_t)(-v), 0x8000000000000000ULL, num);
        } else {
            __XInt128ToExpandFloat64((uint128_t)v, 0, num);
        }
    }
}

static inline void XUInt128ToExpandFloat64(uint128_t v, XExpandFloat64_t * _Nonnull num) {
    if (0 == v) {
        num->f = 0;
        num->expand = 0;
    } else {
        __XInt128ToExpandFloat64(v, 0, num);
    }
}
static inline void __XInt64ToExpandFloat64(uint64_t v, uint64_t sign, XExpandFloat64_t * _Nonnull num) {
    return __XInt128ToExpandFloat64((uint128_t)v, sign, num);
}
#else
static inline void __XInt64ToExpandFloat64(uint64_t v, uint64_t sign, XExpandFloat64_t * _Nonnull num) {
    XAssert(0 != v, "");
    uint64_t bits = sign;
    
    // 高位->低位 前导0个数
    uint64_t leadingZeroCount = XUInt64LeadingZerosCount(v);
    uint64_t e = leadingZeroCount + 1;
    uint64_t tmp = v << e;
    
    // 把tmp的高53位放到float中， 剩余放expand中
    num->expand = tmp << 53;
    uint64_t m = (uint64_t)(tmp >> 11);
    uint64_t te = 1023 + 64 - e;

    bits = bits | (te << 52) | (m & 0xFFFFFFFFFFFFFULL);
    memcpy(&(num->f), &bits, sizeof(double));
}
#endif




static inline void XSInt64ToExpandFloat64(int64_t v, XExpandFloat64_t * _Nonnull num) {
    if (0 == v) {
        num->f = 0;
        num->expand = 0;
    } else {
        if (v < 0) {
            __XInt64ToExpandFloat64((uint64_t)(-v), 0x8000000000000000ULL, num);
        } else {
            __XInt64ToExpandFloat64((uint64_t)v, 0, num);
        }
    }
}

static inline void XUInt64ToExpandFloat64(uint64_t v, XExpandFloat64_t * _Nonnull num) {
    if (0 == v) {
        num->f = 0;
        num->expand = 0;
    } else {
        __XInt64ToExpandFloat64(v, 0, num);
    }
}
static inline void XSInt32ToExpandFloat64(int32_t v, XExpandFloat64_t * _Nonnull num) {
    XSInt64ToExpandFloat64((int64_t)v, num);
}
static inline void XUInt32ToExpandFloat64(uint32_t v, XExpandFloat64_t * _Nonnull num) {
    XUInt64ToExpandFloat64((uint64_t)v, num);
}
static inline void XSIntToExpandFloat64(ssize_t v, XExpandFloat64_t * _Nonnull num) {
    XSInt64ToExpandFloat64((int64_t)v, num);
}
static inline void XUIntToExpandFloat64(size_t v, XExpandFloat64_t * _Nonnull num) {
    XUInt64ToExpandFloat64((uint64_t)v, num);
}


//正无穷
extern const XNumberBits32_u XNumberBits32PositiveInfinity;
extern const XNumberBits32_u XNumberBits32Nan;
//负无穷
extern const XNumberBits32_u XNumberBits32NegativeInfinity;

/// 正无穷
extern const XNumberBits64_u XNumberBits64PositiveInfinity;
extern const XNumberBits64_u XNumberBits64Nan;

/// 负无穷
extern const XNumberBits64_u XNumberBits64NegativeInfinity;

extern XNumberRef _Nonnull XNumberCreateWithUInt8(XObjectOption flag, uint8_t value);
extern XNumberRef _Nonnull XNumberCreateWithSInt8(XObjectOption flag, int8_t value);
extern XNumberRef _Nonnull XNumberCreateWithUInt16(XObjectOption flag, uint16_t value);
extern XNumberRef _Nonnull XNumberCreateWithSInt16(XObjectOption flag, int16_t value);
extern XNumberRef _Nonnull XNumberCreateWithUInt32(XObjectOption flag, uint32_t value);
extern XNumberRef _Nonnull XNumberCreateWithSInt32(XObjectOption flag, int32_t value);
extern XNumberRef _Nonnull XNumberCreateWithUInt64(XObjectOption flag, uint64_t value);
extern XNumberRef _Nonnull XNumberCreateWithSInt64(XObjectOption flag, int64_t value);

//#if CX_TARGET_RT_64_BIT
//extern XNumberRef _Nonnull XNumberCreateWithUInt128(XObjectOption flag, uint128_t value);
//extern XNumberRef _Nonnull XNumberCreateWithSInt128(XObjectOption flag, int128_t value);
//#endif
//
//#if CX_TARGET_SUPPORT_FLOAT128
//extern XNumberRef _Nonnull XNumberCreateWithFloat128(XObjectOption flag, float128_t value);
//#endif

extern XNumberRef _Nonnull XNumberCreateWithFloat64(XObjectOption flag, float64_t value);
extern XNumberRef _Nonnull XNumberCreateWithFloat32(XObjectOption flag, float32_t value);

extern XComparisonResult XNumberCompare(XNumberRef _Nonnull lhs, XNumberRef _Nonnull rhs);

extern XNumberValue_s XNumberGetValue(XNumberRef _Nonnull ref);

#if defined(__cplusplus)

}  // extern C
#endif



#endif /* XNumber_h */
