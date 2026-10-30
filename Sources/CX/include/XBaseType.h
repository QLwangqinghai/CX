
#ifndef XBaseType_h
#define XBaseType_h

#include "XTargetConditionals.h"
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <wchar.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <sys/uio.h>

#if defined(__GNUC__)
#include <stdbool.h>
#endif

// Intger Float
#pragma mark - macros

#if __GNUC__
    #define _XValueAIsLikelyB(a, b) __builtin_expect((a), (b))
    #define _XMemoryBarrier()  __asm__ __volatile__("" ::: "memory")
    #define _XLikely(x) __builtin_expect(!!(x), 1)
    #define _XUnlikely(x) __builtin_expect(!!(x), 0)
#else
    #define _XValueAIsLikelyB(a, b) (x)
    #define _XMemoryBarrier()  do { } while (0)
    #define _XLikely(x) (!!(x))
    #define _XUnlikely(x) (!!(x))
#endif // __GNUC__

/// 优化分支预测 表达式expression的值大概率是真
#define XLikely(expression) _XLikely(expression)

/// 优化分支预测 表达式expression的值大概率是加
#define XUnlikely(expression) _XUnlikely(expression)

/// 优化分支预测 a 的值绝大多是是b，用来优化编译
#define XValueAIsLikelyB(a, b) _XValueAIsLikelyB(a, b)


/// 防止cpu乱序，防止内存、高速缓存、寄存器数据不一致，保证读写操作都是有序的， mb() 和 smp_mb()
#define XMemoryBarrier() _XMemoryBarrier()

/// 写操作 barrier，仅保证写操作有序的，wmb() 和 smp_wmb()
#define XMemoryReadBarrier()

/// 读操作 barrier，仅保证读操作有序的，rmb() 和 smp_rmb()
#define XMemoryWriteBarrier()

#define XAssertFunc(cond, func, desc) {\
    if (XUnlikely(!(cond))) {\
        fprintf(stderr, "[%s error] %s\n", func, desc);\
        abort();\
    }\
}

#define XAssert(cond, desc) {\
    if (XUnlikely(!(cond))) {\
        fprintf(stderr, "[%s error] %s\n", __func__, desc);\
        abort();\
    }\
}
#if DEBUG
#define XDebugAssert(cond, desc) {\
    if (XUnlikely(!(cond))) {\
        fprintf(stderr, "[%s error] %s\n", __func__, desc);\
        abort();\
    }\
}
#else
#define XDebugAssert(cond, desc)
#endif


#define XAbort(desc) {\
    fprintf(stderr, "[%s error] %s\n", __func__, desc);\
    abort();\
}

#define XAssertError(cond, desc) {\
    if (!(cond)) {\
        fprintf(stderr, "[%s error] %s, systenError:%s\n", __func__, desc, strerror(errno));\
        abort();\
    }\
}

#pragma mark - types

typedef float float32_t;
typedef double float64_t;
typedef _Bool bool_t;

//typedef unsigned int uint;
//typedef double float64_t;
//typedef _Bool bool_t;


#if CX_TARGET_RT_64_BIT
typedef uint32_t size_half_t;
typedef uint64_t uint_t;
typedef int64_t int_t;

#define SIZE_HALF_MAX UINT32_MAX
typedef int32_t ssize_half_t;
#define SSIZE_HALF_MAX INT32_MAX
#else
typedef uint32_t uint_t;
typedef int32_t int_t;
typedef uint16_t size_half_t;
#define SIZE_HALF_MAX UINT16_MAX
typedef int16_t ssize_half_t;
#define SSIZE_HALF_MAX INT16_MAX
#endif

#if CX_TARGET_RT_64_BIT

#ifndef _INT128_T
#define _INT128_T
typedef __int128_t  int128_t;
#endif

#ifndef _UINT128_T
#define _UINT128_T
typedef __uint128_t uint128_t;
#endif

#if CX_TARGET_SUPPORT_FLOAT128
typedef long double float128_t;
_Static_assert(sizeof(float128_t) == sizeof(uint128_t), "error");
#endif

#define SINT128_MIN  ((__int128_t)0 - ((__int128_t)1 << 126) - ((__int128_t)1 << 126))
#define SINT128_MAX  ((__int128_t)-1 + ((__int128_t)1 << 126) + ((__int128_t)1 << 126))
#define UINT128_MAX (((__uint128_t)1 << 127) - (__uint128_t)1 + ((__uint128_t)1 << 127))

#endif

#define SINT8_MAX INT8_MAX
#define SINT16_MAX INT16_MAX
#define SINT32_MAX INT32_MAX
#define SINT64_MAX INT64_MAX

#define SINT8_MIN INT8_MIN
#define SINT16_MIN INT16_MIN
#define SINT32_MIN INT32_MIN
#define SINT64_MIN INT64_MIN
    
#define sint32_fast_t int_fast32_t
#define uint32_fast_t uint_fast32_t
#define sint64_fast_t int_fast64_t
#define uint64_fast_t uint_fast64_t
    
#if CX_TARGET_RT_64_BIT
#define SINT_MAX INT64_MAX
#define SINT_MIN INT64_MIN

#define SSIZE_MIN INT64_MIN

#define ssize_fast_t int_fast64_t
#define size_fast_t uint_fast64_t

#define SINT_FAST_MIN INT_FAST64_MIN
#define SINT_FAST_MAX INT_FAST64_MAX
#define UINT_FAST_MAX UINT_FAST64_MAX

#else
#define SINT_MAX INT32_MAX
#define SINT_MIN INT32_MIN

#define SSIZE_MIN INT32_MIN

#define ssize_fast_t int_fast32_t
#define size_fast_t uint_fast32_t
    
#define SINT_FAST_MIN INT_FAST32_MIN
#define SINT_FAST_MAX INT_FAST32_MAX
#define UINT_FAST_MAX UINT_FAST32_MAX

#endif

#define SINT64_MIN INT64_MIN
#define SINT64_MAX INT64_MAX

#if CX_TARGET_RT_64_BIT
    #define SSIZE_BITS_COUNT 64
    #define SIZE_BITS_COUNT 64
    #define SIZE_BITS_COUNT_SHIFT 6
    #define SSIZE_BYTE_COUNT 8
    #define SIZE_BYTE_COUNT 8
    #define SIZE_BYTE_COUNT_SHIFT 3
    #define SIZE_HALF_BITS_COUNT 32
    #define SIZE_C(value) UINT64_C(value)
#else
    #define SSIZE_BITS_COUNT 32
    #define SIZE_BITS_COUNT 32
    #define SIZE_BITS_COUNT_SHIFT 5
    #define SSIZE_BYTE_COUNT 4
    #define SIZE_BYTE_COUNT 4
    #define SIZE_BYTE_COUNT_SHIFT 2
    #define SIZE_HALF_BITS_COUNT 16
    #define SIZE_C(value) UINT32_C(value)
#endif


typedef ssize_t XIndex;

typedef struct {
    uint16_t major;
    uint16_t minor;
    uint16_t revision;
    uint16_t build;
} XVersion;

static inline uint64_t XVersionToUInt64(XVersion v) {
    uint64_t result = v.major;
    result = result << 16;
    result += v.minor;
    result = result << 16;
    result += v.revision;
    result = result << 16;
    result += v.build;
    return result;
}

//#define XIndexNotFound SIZE_MAX
static const ssize_t XIndexNotFound = -1;

// lowerBound ..< upperBound
typedef struct {
    ssize_t lowerBound;
    ssize_t upperBound;
} XRange_s;

#define XRange_C(LowerBound, UpperBound) {\
.lowerBound = LowerBound,\
.upperBound = UpperBound,\
}

static inline XRange_s XRangeMake(ssize_t lowerBound, ssize_t upperBound) {
    XRange_s range = {
        .lowerBound = lowerBound,
        .upperBound = upperBound,
    };
    return range;
}
static inline bool_t XRangeIsEmpty(XRange_s range) {
    return range.lowerBound >= range.upperBound;
}
static inline bool_t XRangeIsValid(XRange_s range) {
    return range.lowerBound >= 0 && range.upperBound >= 0;
}
typedef struct _XRange16 {
    uint16_t location;
    uint16_t length;
} XRange16 __attribute__((aligned(2)));
#if CX_TARGET_RT_64_BIT
typedef struct _XRange32 {
    uint32_t location;
    uint32_t length;
} XRange32 __attribute__((aligned(4)));
typedef XRange_s XRange64;
#else
typedef XRange_s XRange32;
typedef struct _XRange64 {
    uint64_t location;
    uint64_t length;
} XRange64;
#endif

/*
 应该优先判断
 (XIndexNotFound != location)
 */


//static inline XRange_s XRangeMake(ssize_t location, ssize_t length) {
//    XRange_s r = {
//        .location = location,
//        .length = length,
//    };
//    return r;
//}
//
////向前移动
//static inline XRange_s XRangeMoveForward(XRange_s range, ssize_t n) {
//    XAssert(range.location >= n, "");
//    XRange_s r = {
//        .location = range.location - n,
//        .length = range.length,
//    };
//    return r;
//}
////向后移动
//static inline XRange_s XRangeMoveBackward(XRange_s range, ssize_t n) {
//    XAssert(range.location + n >= range.location, "");
//    XRange_s r = {
//        .location = range.location + n,
//        .length = range.length,
//    };
//    return r;
//}
//static inline XRange_s XRangeMove(XRange_s range, ssize_t n) {
//    if (n < 0) {
//        return XRangeMoveForward(range, - n);
//    } else {
//        return XRangeMoveBackward(range, n);
//    }
//}


#pragma mark - byte

typedef struct {
    uint8_t content[2];
} XByte2 __attribute((aligned(1)));
typedef struct {
    uint8_t content[4];
} XByte4 __attribute((aligned(1)));
typedef struct {
    uint8_t content[8];
} XByte8 __attribute((aligned(1)));
//used for uuid、md5、ipAddress
typedef struct {
    uint8_t content[16];
} XByte16 __attribute((aligned(1)));
typedef struct {
    uint8_t content[20];
} XByte20 __attribute((aligned(1)));
typedef struct {
    uint8_t content[28];
} XByte28 __attribute((aligned(1)));
typedef struct {
    uint8_t content[32];
} XByte32 __attribute((aligned(1)));
typedef struct {
    uint8_t content[48];
} XByte48 __attribute((aligned(1)));
typedef struct {
    uint8_t content[64];
} XByte64 __attribute((aligned(1)));

#pragma mark - pointer

typedef void * XPtr;

#pragma mark - XHashCode

typedef size_t XHashCode;

typedef XByte16 XHashByte16_t;

typedef XPtr XHasher;

#pragma mark - Integer

extern uint32_t UInt32Random(void);
extern uint64_t UInt64Random(void);
extern size_t UIntRandom(void);

static inline uint64_t UInt64MakeBitPattern(int64_t value) {
    return *((uint64_t *)(&value));
}
static inline int64_t SInt64MakeBitPattern(uint64_t value) {
    return *((int64_t *)(&value));
}
static inline uint32_t UInt32MakeBitPattern(int32_t value) {
    return *((uint32_t *)(&value));
}
static inline int32_t SInt32MakeBitPattern(uint32_t value) {
    return *((int32_t *)(&value));
}
static inline uint16_t UInt16MakeBitPattern(int16_t value) {
    return *((uint16_t *)(&value));
}
static inline int16_t SInt16MakeBitPattern(uint16_t value) {
    return *((int16_t *)(&value));
}

static inline uint16_t UInt16ByteSwap(uint16_t data) {
    return (uint16_t)(data << 8 | data >> 8);
}

static inline uint32_t UInt32ByteSwap(uint32_t data) {
#if defined(__llvm__)
    data = __builtin_bswap32(data);
#else
    data = (((data ^ (data >> 16 | (data << 16))) & 0xFF00FFFF) >> 8) ^ (data >> 8 | data << 24);
#endif
    return data;
}

static inline uint64_t UInt64ByteSwap(uint64_t data) {
#if defined(__llvm__)
    return __builtin_bswap64(data);
#else
    union {
        uint64_t ull;
        uint32_t ul[2];
    } u;
    u.ull = data;
    uint32_t t = u.ul[0];
    u.ul[0] = UInt32ByteSwap(u.ul[1]);
    u.ul[1] = UInt32ByteSwap(t);
    return u.ull;
#endif
}

static inline void UInt48ToBigEndianBytes(uint64_t value, uint8_t block[_Nonnull 6]) {
    block[0] = (uint8_t)(value >> 40);
    block[1] = (uint8_t)(value >> 32);
    block[2] = (uint8_t)(value >> 24);
    block[3] = (uint8_t)(value >> 16);
    block[4] = (uint8_t)(value >> 8);
    block[5] = (uint8_t)(value);
}
static inline uint64_t UInt48MakeWithBigEndianBytes(uint8_t const block[_Nonnull 6]) {
    uint64_t value = 0;
    value += block[0];
    value <<= 8;
    value += block[1];
    value <<= 8;
    value += block[2];
    value <<= 8;
    value += block[3];
    value <<= 8;
    value += block[4];
    value <<= 8;
    value += block[5];
    return value;
}


#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static inline uint64_t UInt64MakeWithBigEndianBytes(uint8_t const block[_Nonnull 8]) {
    uint64_t value = *((uint64_t *)block);
    return UInt64ByteSwap(value);
}
static inline uint32_t UInt32MakeWithBigEndianBytes(uint8_t const block[_Nonnull 4]) {
    uint32_t value = *((uint32_t *)block);
    return UInt32ByteSwap(value);
}
static inline uint16_t UInt16MakeWithBigEndianBytes(uint8_t const block[_Nonnull 2]) {
    uint16_t value = *((uint16_t *)block);
    return UInt16ByteSwap(value);
}
static inline uint64_t UInt64MakeWithLittleEndianBytes(uint8_t const block[_Nonnull 8]) {
    return *((uint64_t *)block);
}
static inline uint32_t UInt32MakeWithLittleEndianBytes(uint8_t const block[_Nonnull 4]) {
    return *((uint32_t *)block);
}
static inline uint16_t UInt16MakeWithLittleEndianBytes(uint8_t const block[_Nonnull 2]) {
    return *((uint16_t *)block);
}

static inline void UInt64ToBigEndianBytes(uint64_t value, uint8_t block[_Nonnull 8]) {
    uint64_t v = UInt64ByteSwap(value);
    *((uint64_t *)block) = v;
}
static inline void UInt32ToBigEndianBytes(uint32_t value, uint8_t block[_Nonnull 4]) {
    uint32_t v = UInt32ByteSwap(value);
    *((uint32_t *)block) = v;
}
static inline void UInt16ToBigEndianBytes(uint16_t value, uint8_t block[_Nonnull 2]) {
    uint16_t v = UInt16ByteSwap(value);
    *((uint16_t *)block) = v;
}

static inline void UInt64ToLittleEndianBytes(uint64_t value, uint8_t block[_Nonnull 8]) {
    *((uint64_t *)block) = value;
}
static inline void UInt32ToLittleEndianBytes(uint32_t value, uint8_t block[_Nonnull 4]) {
    *((uint32_t *)block) = value;
}
static inline void UInt16ToLittleEndianBytes(uint16_t value, uint8_t block[_Nonnull 2]) {
    *((uint16_t *)block) = value;
}

#elif __BYTE_ORDER__== __ORDER_BIG_ENDIAN__
static inline uint64_t UInt64MakeWithBigEndianBytes(uint8_t const block[_Nonnull 8]) {
    return *((uint64_t *)block);
}
static inline uint32_t UInt32MakeWithBigEndianBytes(uint8_t const block[_Nonnull 4]) {
    return *((uint32_t *)block);
}
static inline uint16_t UInt16MakeWithBigEndianBytes(uint8_t const block[_Nonnull 2]) {
    return *((uint16_t *)block);
}

static inline uint64_t UInt64MakeWithLittleEndianBytes(uint8_t const block[_Nonnull 8]) {
    uint64_t value = *((uint64_t *)block);
    return UInt64ByteSwap(value);
}
static inline uint32_t UInt32MakeWithLittleEndianBytes(uint8_t const block[_Nonnull 4]) {
    uint32_t value = *((uint32_t *)block);
    return UInt32ByteSwap(value);
}
static inline uint16_t UInt16MakeWithLittleEndianBytes(uint8_t const block[_Nonnull 2]) {
    uint16_t value = *((uint16_t *)block);
    return UInt16ByteSwap(value);
}

static inline void UInt64ToBigEndianBytes(uint64_t value, uint8_t block[_Nonnull 8]) {
    *((uint64_t *)block) = value;
}
static inline void UInt32ToBigEndianBytes(uint32_t value, uint8_t block[_Nonnull 4]) {
    *((uint32_t *)block) = value;
}
static inline void UInt16ToBigEndianBytes(uint16_t value, uint8_t block[_Nonnull 2]) {
    *((uint16_t *)block) = value;
}

static inline void UInt64ToLittleEndianBytes(uint64_t value, uint8_t block[_Nonnull 8]) {
    uint64_t v = UInt64ByteSwap(value);
    *((uint64_t *)block) = v;
}
static inline void UInt32ToLittleEndianBytes(uint32_t value, uint8_t block[_Nonnull 4]) {
    uint32_t v = UInt32ByteSwap(value);
    *((uint32_t *)block) = v;
}
static inline void UInt16ToLittleEndianBytes(uint16_t value, uint8_t block[_Nonnull 2]) {
    uint16_t v = UInt16ByteSwap(value);
    *((uint16_t *)block) = v;
}

#else
#error "DEFINE BIG_ENDIAN OR LITTLE_ENDIAN"
#endif


#if defined(__x86_64__) && !defined(_MSC_VER) //clang _MSVC doesn't support GNU-style inline assembly
// MARK: -- intel 64 asm version

static inline uint64_t UInt64RotateLeft(uint64_t word, unsigned int offset) {
    __asm__("rolq %%cl,%0"
            :"=r" (word)
            :"0" (word),"c" (offset));
    return word;
}

static inline uint64_t UInt64RotateRight(uint64_t word, unsigned int offset) {
    __asm__("rorq %%cl,%0"
            :"=r" (word)
            :"0" (word),"c" (offset));
    return word;
}

#else /* Not x86_64  */

// MARK: -- default C version

static inline uint64_t UInt64RotateLeft(uint64_t word, uint64_t offset) {
    offset = offset & 63;
    return ( word << offset) | (word >> (64-offset));
}

static inline uint64_t UInt64RotateRight(uint64_t word, uint64_t offset) {
    offset = offset & 63;
    return ( word >> offset) | (word << (64-offset));
}

#endif

// MARK: - 32-bit Rotates

#if defined(_MSC_VER)
// MARK: -- MSVC version

#include <stdlib.h>
#if !defined(__clang__)
#pragma intrinsic(_lrotr,_lrotl)
#endif
#define    UInt32RotateRight(x,n) _lrotr(x,n)
#define    UInt32RotateLeft(x,n) _lrotl(x,n)

#elif (defined(__i386__) || defined(__x86_64__))
// MARK: -- intel asm version

static inline uint32_t UInt32RotateLeft(uint32_t word, unsigned int offset) {
    __asm__ ("roll %%cl,%0"
             :"=r" (word)
             :"0" (word),"c" (offset));
    return word;
}

static inline uint32_t UInt32RotateRight(uint32_t word, unsigned int offset) {
    __asm__ ("rorl %%cl,%0"
             :"=r" (word)
             :"0" (word),"c" (offset));
    return word;
}

#else

static inline uint32_t UInt32RotateLeft(uint32_t word, uint32_t offset) {
    offset = offset & 31;
    return ( word << offset) | (word >> (32-offset));
}

static inline uint32_t UInt32RotateRight(uint32_t word, uint32_t offset) {
    offset = offset & 31;
    return ( word >> offset) | (word << (32-offset));
}

#endif


static inline uint64_t zigzag(int64_t value) {
    if(value < 0) {
        return ((uint64_t)(-value)) * 2 - 1;
    } else {
        return value * 2;
    }
}

/*
 ZigZag: 位数x: encode= (n << 1) ^ (n >> (x-1)), 带符号的位移
 ZigZag: 位数x: decode= (n >> 1) ^ (0 - (n & 0x1)) 不带符号的位移

 ZigZag encode to uint:
 正数：左循环位移1
 负数：左移1位，符号位放最后1位，除了最后一位按位取反
 ZigZag decode from uint:
 右移1位，符号位放最高1位，如果最高位位1 其他位取反
 */
#if CX_TARGET_RT_64_BIT

/// 输入一定要是sint64 类型
static inline uint128_t SInt128ZigzagEncode(int128_t value) {
    const uint128_t one = 1;
    const uint128_t shift = 127;
    uint128_t tmp = *((uint128_t *)&value);
    return (tmp << one) ^ (0 - (tmp >> shift));
}
static inline int128_t SInt128ZigzagDecode(uint128_t data) {
    const uint128_t one = 1;
    return (int128_t)((data >> one) ^ (0 - (data & one)));
}

#endif

/// 输入一定要是sint64 类型
static inline uint64_t SInt64ZigzagEncode(int64_t value) {
    uint64_t tmp = *((uint64_t *)&value);
    return (tmp << UINT64_C(1)) ^ (0 - (tmp >> UINT64_C(63)));
}
static inline int64_t SInt64ZigzagDecode(uint64_t data) {
    return (int64_t)((data >> UINT64_C(1)) ^ (0 - (data & UINT64_C(1))));
}

static inline uint32_t SInt32ZigzagEncode(int32_t value) {
    uint32_t tmp = *((uint32_t *)&value);
    return (tmp << UINT32_C(1)) ^ (0 - (tmp >> UINT32_C(31)));
}
static inline int32_t SInt32ZigzagDecode(uint32_t data) {
    return (int32_t)((data >> UINT32_C(1)) ^ (0 - (data & UINT32_C(1))));
}
static inline size_t SSizeZigzagEncode(ssize_t value) {
#if CX_TARGET_RT_64_BIT
    return SInt64ZigzagEncode(value);
#else
    return SInt32ZigzagEncode(value);
#endif
}
static inline ssize_t SSizeZigzagDecode(size_t data) {
#if CX_TARGET_RT_64_BIT
    return SInt64ZigzagDecode(data);
#else
    return SInt32ZigzagDecode(data);
#endif
}

extern int UInt64VarintEncodeSize(uint64_t value);
extern int UInt32VarintEncodeSize(uint32_t value);


// 返回0标识数据不足， 负数表示错误， 正式表示使用的字节数
extern int UInt64VarintEncode(uint64_t value, uint8_t * _Nonnull bytes, size_t capacity);

// 返回0标识数据不足， 负数表示错误， 正式表示使用的字节数， 未做严格的字节数使用校验(只限制最大长度10字节，且如果长度是10字节，校验首字节==0x81)
extern int UInt64VarintDecode(uint64_t * _Nonnull value, const uint8_t * _Nonnull bytes, size_t length);

// 返回0标识数据不足， 负数表示错误， 正式表示使用的字节数
extern int UInt32VarintEncode(uint32_t value, uint8_t * _Nonnull bytes, size_t capacity);

// 返回0标识数据不足， 负数表示错误， 正式表示使用的字节数， 未做严格的字节数使用校验(只限制最大长度5字节，且如果长度是5字节，校验首字节 (byte & 0x7f)<=0xf)
extern int UInt32VarintDecode(uint32_t * _Nonnull value, const uint8_t * _Nonnull bytes, size_t length);


// 返回输入参数的最高有效bit位（从低位往左数最后的有效bit位）的序号, 没有有效位时返回XIndexNotFound
static inline XIndex UInt32FindLastBitSet(uint32_t x) {
    if (0 == x) {
        return XIndexNotFound;
    }
    XIndex r = 31;
    if (!(x & 0xffff0000u)) {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u)) {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u)) {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u)) {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u)) {
        x <<= 1;
        r -= 1;
    }
    return r;
}

static inline XIndex UInt32FindFirstBitSet(uint32_t x) {
    if (0 == x) {
        return XIndexNotFound;
    }
    XIndex r = 0;
    if (!(x & 0xffffu)) {
        x >>= 16;
        r += 16;
    }
    if (!(x & 0xffu)) {
        x >>= 8;
        r += 8;
    }
    if (!(x & 0xfu)) {
        x >>= 4;
        r += 4;
    }
    if (!(x & 0x3u)) {
        x >>= 2;
        r += 2;
    }
    if (!(x & 0x1u)) {
        x >>= 1;
        r += 1;
    }
    return r;
}

// 返回输入参数的最高有效bit位（从低位往高位最后的有效bit位）的序号, 没有有效位时返回XIndexNotFound
static inline XIndex UInt64FindLastBitSet(uint64_t x) {
    if (0 == x) {
        return XIndexNotFound;
    }
    XIndex r = 63;
    if (!(x & 0xffffffff00000000ull)) {
        x <<= 32;
        r -= 32;
    }
    if (!(x & 0xffff0000ull)) {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000ull)) {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000ull)) {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000ull)) {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000ull)) {
        x <<= 1;
        r -= 1;
    }
    return r;
}

static inline XIndex UInt64FindFirstBitSet(uint64_t x) {
    if (0 == x) {
        return XIndexNotFound;
    }
    XIndex r = 0;
    if (!(x & 0xffffffffull)) {
        x >>= 32;
        r += 32;
    }
    if (!(x & 0xffffull)) {
        x >>= 16;
        r += 16;
    }
    if (!(x & 0xffull)) {
        x >>= 8;
        r += 8;
    }
    if (!(x & 0xfull)) {
        x >>= 4;
        r += 4;
    }
    if (!(x & 0x3ull)) {
        x >>= 2;
        r += 2;
    }
    if (!(x & 0x1ull)) {
        x >>= 1;
        r += 1;
    }
    return r;
}

//#if CX_TARGET_RT_64_BIT
//  前导0个数
//static inline XIndex UInt128FindLastBitSet(uint128_t x) {
//    if (0 == x) {
//        return XIndexNotFound;
//    }
//    XIndex r = 63;
//    if (!(x & 0xffffffff00000000ull)) {
//        x <<= 32;
//        r -= 32;
//    }
//    if (!(x & 0xffff0000ull)) {
//        x <<= 16;
//        r -= 16;
//    }
//    if (!(x & 0xff000000ull)) {
//        x <<= 8;
//        r -= 8;
//    }
//    if (!(x & 0xf0000000ull)) {
//        x <<= 4;
//        r -= 4;
//    }
//    if (!(x & 0xc0000000ull)) {
//        x <<= 2;
//        r -= 2;
//    }
//    if (!(x & 0x80000000ull)) {
//        x <<= 1;
//        r -= 1;
//    }
//    return r;
//}
//后导0个数
//static inline XIndex UInt128FindFirstBitSet(uint128_t x) {
//    if (0 == x) {
//        return XIndexNotFound;
//    }
//    XIndex r = 0;
//    if (!(x & 0xffffffffull)) {
//        x >>= 32;
//        r += 32;
//    }
//    if (!(x & 0xffffull)) {
//        x >>= 16;
//        r += 16;
//    }
//    if (!(x & 0xffull)) {
//        x >>= 8;
//        r += 8;
//    }
//    if (!(x & 0xfull)) {
//        x >>= 4;
//        r += 4;
//    }
//    if (!(x & 0x3ull)) {
//        x >>= 2;
//        r += 2;
//    }
//    if (!(x & 0x1ull)) {
//        x >>= 1;
//        r += 1;
//    }
//    return r;
//}
//
//#endif

static inline XIndex USizeFindFirstBitSet(size_t x) {
#if CX_TARGET_RT_64_BIT
    return UInt64FindFirstBitSet(x);
#else
    return UInt32FindFirstBitSet(x);
#endif
}

static inline XIndex USizeFindLastBitSet(size_t x) {
#if CX_TARGET_RT_64_BIT
    return UInt64FindLastBitSet(x);
#else
    return UInt32FindLastBitSet(x);
#endif
}

// 高位前导0的个数
static inline uint16_t XUInt8LeadingZerosCount(uint8_t x) {
    if (0 == x) {
        return 8;
    }
    uint8_t r = 0;
    if (0 == (x & UINT8_C(0xF0))) {
        x <<= 4;
        r += 4;
    }
    if (0 == (x & UINT8_C(0xC0))) {
        x <<= 2;
        r += 2;
    }
    if (0 == (x & UINT8_C(0x80))) {
        x <<= 1;
        r += 1;
    }
    return r;
}
static inline uint8_t XUInt8TrailingZerosCount(uint8_t x) {
    if (0 == x) {
        return 8;
    }
    uint8_t r = 0;
    if (0 == (x & UINT8_C(0xF))) {
        x >>= 4;
        r += 4;
    }
    if (0 == (x & UINT8_C(0x3))) {
        x >>= 2;
        r += 2;
    }
    if (0 == (x & UINT8_C(0x1))) {
        x >>= 1;
        r += 1;
    }
    return r;
}
// 高位前导0的个数
static inline uint16_t XUInt16LeadingZerosCount(uint16_t x) {
    if (0 == x) {
        return 16;
    }
    uint16_t r = 0;
    if (0 == (x & UINT16_C(0xFF00))) {
        x <<= 8;
        r += 8;
    }
    if (0 == (x & UINT16_C(0xF000))) {
        x <<= 4;
        r += 4;
    }
    if (0 == (x & UINT16_C(0xC000))) {
        x <<= 2;
        r += 2;
    }
    if (0 == (x & UINT16_C(0x8000))) {
        x <<= 1;
        r += 1;
    }
    return r;
}
static inline uint16_t XUInt16TrailingZerosCount(uint16_t x) {
    if (0 == x) {
        return 16;
    }
    uint16_t r = 0;
    if (0 == (x & UINT16_C(0xFF))) {
        x >>= 8;
        r += 8;
    }
    if (0 == (x & UINT16_C(0xF))) {
        x >>= 4;
        r += 4;
    }
    if (0 == (x & UINT16_C(0x3))) {
        x >>= 2;
        r += 2;
    }
    if (0 == (x & UINT16_C(0x1))) {
        x >>= 1;
        r += 1;
    }
    return r;
}

// 高位前导0的个数
static inline uint32_t XUInt32LeadingZerosCount(uint32_t x) {
    if (0 == x) {
        return 32;
    }
    uint32_t r = 0;
    if (0 == (x & UINT32_C(0xFFFF0000))) {
        x <<= 16;
        r += 16;
    }
    if (0 == (x & UINT32_C(0xFF000000))) {
        x <<= 8;
        r += 8;
    }
    if (0 == (x & UINT32_C(0xF0000000))) {
        x <<= 4;
        r += 4;
    }
    if (0 == (x & UINT32_C(0xC0000000))) {
        x <<= 2;
        r += 2;
    }
    if (0 == (x & UINT32_C(0x80000000))) {
        x <<= 1;
        r += 1;
    }
    return r;
}
static inline uint32_t XUInt32TrailingZerosCount(uint32_t x) {
    if (0 == x) {
        return 32;
    }
    uint32_t r = 0;
    if (0 == (x & UINT32_C(0xFFFF))) {
        x >>= 16;
        r += 16;
    }
    if (0 == (x & UINT32_C(0xFF))) {
        x >>= 8;
        r += 8;
    }
    if (0 == (x & UINT32_C(0xF))) {
        x >>= 4;
        r += 4;
    }
    if (0 == (x & UINT32_C(0x3))) {
        x >>= 2;
        r += 2;
    }
    if (0 == (x & UINT32_C(0x1))) {
        x >>= 1;
        r += 1;
    }
    return r;
}

// 高位前导0字节的个数
static inline uint64_t UInt64LeadingZeroBytesCount(uint64_t x) {
    if (0 == x) {
        return 8;
    }
    uint64_t r = 0;
    if (0 == (x & UINT64_C(0xFFFFFFFF00000000))) {
        x <<= 32;
        r += 4;
    }
    if (0 == (x & UINT64_C(0xFFFF000000000000))) {
        x <<= 16;
        r += 2;
    }
    if (0 == (x & UINT64_C(0xFF00000000000000))) {
        x <<= 8;
        r += 1;
    }
    if (0 == (x & UINT64_C(0xFF00000000000000))) {
        x <<= 8;
        r += 1;
    }
    return r;
}


// 高位前导0的个数
static inline uint64_t XUInt64LeadingZerosCount(uint64_t x) {
    if (0 == x) {
        return 64;
    }
    uint64_t r = 0;
    if (0 == (x & UINT64_C(0xFFFFFFFF00000000))) {
        x <<= 32;
        r += 32;
    }
    if (0 == (x & UINT64_C(0xFFFF000000000000))) {
        x <<= 16;
        r += 16;
    }
    if (0 == (x & UINT64_C(0xFF00000000000000))) {
        x <<= 8;
        r += 8;
    }
    if (0 == (x & UINT64_C(0xF000000000000000))) {
        x <<= 4;
        r += 4;
    }
    if (0 == (x & UINT64_C(0xC000000000000000))) {
        x <<= 2;
        r += 2;
    }
    if (0 == (x & UINT64_C(0x8000000000000000))) {
        x <<= 1;
        r += 1;
    }
    return r;
}
static inline uint64_t XUInt64TrailingZerosCount(uint64_t x) {
    if (0 == x) {
        return 64;
    }
    uint64_t r = 0;
    if (0 == (x & UINT64_C(0xFFFFFFFF))) {
        x >>= 32;
        r += 32;
    }
    if (0 == (x & UINT64_C(0xFFFF))) {
        x >>= 16;
        r += 16;
    }
    if (0 == (x & UINT64_C(0xFF))) {
        x >>= 8;
        r += 8;
    }
    if (0 == (x & UINT64_C(0xF))) {
        x >>= 4;
        r += 4;
    }
    if (0 == (x & UINT64_C(0x3))) {
        x >>= 2;
        r += 2;
    }
    if (0 == (x & UINT64_C(0x1))) {
        x >>= 1;
        r += 1;
    }
    return r;
}

#if CX_TARGET_RT_64_BIT
static inline uint128_t XUInt128LeadingZerosCount(uint128_t x) {
    if (0 == x) {
        return 128;
    }
    if ((x >> 64) == 0) {
        return 64 + XUInt64LeadingZerosCount((uint64_t)x);
    } else {
        return 64 + XUInt64LeadingZerosCount((uint64_t)(x >> 64));
    }
}
static inline uint128_t XUInt128TrailingZerosCount(uint128_t x) {
    if (0 == x) {
        return 128;
    }
    if ((x & UINT64_MAX) == 0) {
        return 64 + XUInt64TrailingZerosCount((uint64_t)(x >> 64));
    } else {
        return XUInt64TrailingZerosCount((uint64_t)x);
    }
}
#endif

static inline size_t USizeLeadingZerosCount(size_t x) {
#if CX_TARGET_RT_64_BIT
    return XUInt64LeadingZerosCount(x);
#else
    return XUInt32LeadingZerosCount(x);
#endif
}
static inline size_t USizeTrailingZerosCount(size_t x) {
#if CX_TARGET_RT_64_BIT
    return XUInt64TrailingZerosCount(x);
#else
    return XUInt32TrailingZerosCount(x);
#endif
}

// 从低位向高位第一个为0的位的index, 找不到就返回32
static inline uint32_t XUInt32FindFirstZero(uint32_t x) {
    if (0 == x) {
        return 0;
    } else if (UINT32_MAX == x) {
        return 32;
    }
    uint32_t r = 0;
    if (UINT32_C(0xFFFF) == (x & UINT32_C(0xFFFF))) {
        x >>= 16;
        r += 16;
    }
    if (UINT32_C(0xFF) == (x & UINT32_C(0xFF))) {
        x >>= 8;
        r += 8;
    }
    if (UINT32_C(0xF) == (x & UINT32_C(0xF))) {
        x >>= 4;
        r += 4;
    }
    if (UINT32_C(0x3) == (x & UINT32_C(0x3))) {
        x >>= 2;
        r += 2;
    }
    if (UINT32_C(0x1) == (x & UINT32_C(0x1))) {
        x >>= 1;
        r += 1;
    }
    return r;
}
// 从低位向高位第一个为0的位的index, 找不到就返回64
static inline uint64_t XUInt64FindFirstZero(uint64_t x) {
    if (0 == x) {
        return 0;
    } else if (UINT64_MAX == x) {
        return 64;
    }
    uint64_t r = 0;
    if (UINT64_C(0xFFFFFFFF) == (x & UINT64_C(0xFFFFFFFF))) {
        x >>= 32;
        r += 32;
    }
    if (UINT64_C(0xFFFF) == (x & UINT64_C(0xFFFF))) {
        x >>= 16;
        r += 16;
    }
    if (UINT64_C(0xFF) == (x & UINT64_C(0xFF))) {
        x >>= 8;
        r += 8;
    }
    if (UINT64_C(0xF) == (x & UINT64_C(0xF))) {
        x >>= 4;
        r += 4;
    }
    if (UINT64_C(0x3) == (x & UINT64_C(0x3))) {
        x >>= 2;
        r += 2;
    }
    if (UINT64_C(0x1) == (x & UINT64_C(0x1))) {
        x >>= 1;
        r += 1;
    }
    return r;
}
static inline size_t USizeFindFirstZero(size_t x) {
#if CX_TARGET_RT_64_BIT
    return XUInt64FindFirstZero(x);
#else
    return XUInt32FindFirstZero(x);
#endif
}

static inline XByte8 UInt64ToBigEndianByte8(uint64_t value) {
    XByte8 result = { 0 };
    UInt64ToBigEndianBytes(value, result.content);
    return result;
}
static inline XByte4 UInt32ToBigEndianByte4(uint32_t value) {
    XByte4 result = { 0 };
    UInt32ToBigEndianBytes(value, result.content);
    return result;
}
static inline XByte2 UInt16ToBigEndianByte2(uint16_t value) {
    XByte2 result = { 0 };
    UInt16ToBigEndianBytes(value, result.content);
    return result;
}
static inline uint64_t UInt64MakeWithByte8(XByte8 bytes) {
    return UInt64MakeWithBigEndianBytes(bytes.content);
}
static inline uint32_t UInt32MakeWithByte4(XByte4 bytes) {
    return UInt32MakeWithBigEndianBytes(bytes.content);
}
static inline uint16_t UInt16MakeWithByte2(XByte2 bytes) {
    return UInt16MakeWithBigEndianBytes(bytes.content);
}

#pragma mark - Float

static inline double Float64MakeBitPatternSInt64(int64_t value) {
    return *((double *)(&value));
}
static inline float Float32MakeBitPatternSInt32(int32_t value) {
    return *((float *)(&value));
}
static inline double Float64MakeBitPatternUInt64(uint64_t value) {
    return *((double *)(&value));
}
static inline float Float32MakeBitPatternUInt32(uint32_t value) {
    return *((float *)(&value));
}

static inline int64_t SInt64MakeBitPatternFloat64(double value) {
    return *((double *)(&value));
}
static inline int32_t SInt32MakeBitPatternFloat32(float value) {
    return *((float *)(&value));
}
static inline uint64_t UInt64MakeBitPatternFloat64(double value) {
    return *((double *)(&value));
}
static inline uint32_t UInt32MakeBitPatternFloat32(float value) {
    return *((float *)(&value));
}


// 返回是否是无损转换
static inline bool_t XSInt64ToFloat64(int64_t v, double * _Nonnull num) {
    double result = (double)v;
    *num = result;
    if (0 == v) {
        return true;
    } else {
        uint64_t bits;
        memcpy(&bits, &result, sizeof(result));
        uint64_t exponent_mask = 0x7ff0000000000000ULL;
        int64_t exponent = (int64_t)(((bits & exponent_mask) >> 52) - 1023);
        int64_t m = (int64_t)(((bits & 0xFFFFFFFFFFFFFULL) | 0x10000000000000ULL) << 11 >> (63 - exponent));
        if (result < 0) {
            m = m * -1;
        }
        return m == v;
    }
}

// 返回是否是无损转换
static inline bool_t XUInt64ToFloat64(uint64_t v, double * _Nonnull num) {
    double result = (double)v;
    *num = result;
    if (0 == v) {
        return true;
    } else {
        uint64_t bits;
        memcpy(&bits, &result, sizeof(result));
        uint64_t exponent_mask = 0x7ff0000000000000ULL;
        int64_t exponent = (int64_t)(((bits & exponent_mask) >> 52) - 1023);
        if (exponent == 64) {
            return false;
        }
        uint64_t m = (uint64_t)(((bits & 0xFFFFFFFFFFFFFULL) | 0x10000000000000ULL) << 11 >> (63 - exponent));
        return m == v;
    }
}

#if CX_TARGET_RT_64_BIT

// 返回是否是无损转换
static inline bool_t XSInt128ToFloat64(int128_t v, double * _Nonnull num) {
    double result = (double)v;
    *num = result;
    if (0 == v) {
        return true;
    } else {
        uint64_t bits;
        memcpy(&bits, &result, sizeof(result));
        uint64_t exponent_mask = 0x7ff0000000000000ULL;
        int128_t exponent = (int128_t)(((bits & exponent_mask) >> 52) - 1023);
        uint128_t tmp = (uint128_t)((bits & 0xFFFFFFFFFFFFFULL) | 0x10000000000000ULL);
        tmp = tmp << 75;
        int128_t m = (int128_t)(tmp >> (127 - exponent));
        if (result < 0) {
            m = m * -1;
        }
        return m == v;
    }
}

// 返回是否是无损转换
static inline bool_t XUInt128ToFloat64(uint128_t v, double * _Nonnull num) {
    double result = (double)v;
    *num = result;
    if (0 == v) {
        return true;
    } else {
        uint64_t bits;
        memcpy(&bits, &result, sizeof(result));
        uint64_t exponent_mask = 0x7ff0000000000000ULL;
        uint128_t exponent = (uint128_t)(((bits & exponent_mask) >> 52) - 1023);
        if (exponent == 128) {
            return false;
        }
        uint128_t tmp = (uint128_t)((bits & 0xFFFFFFFFFFFFFULL) | 0x10000000000000ULL);
        tmp = tmp << 75;
        uint128_t m = (uint128_t)(tmp >> (127 - exponent));
        return m == v;
    }
}
#endif


/// 比float128 多16位尾数
typedef struct {
    uint16_t se;// sign: 1 exponent:15
    uint64_t fractionHigh;
    uint64_t fractionLow;
} XCFloat144_s;

extern const XCFloat144_s * _Nonnull XCFloat144DefaultNotANumber;

extern const XCFloat144_s * _Nonnull XCFloat144DefaultZero;
extern const XCFloat144_s * _Nonnull XCFloat144PositiveZero;
extern const XCFloat144_s * _Nonnull XCFloat144NegativeZero;

/// 负无穷
extern const XCFloat144_s * _Nonnull XCFloat144NegativeInfinity;

/// 正无穷
extern const XCFloat144_s * _Nonnull XCFloat144PositiveInfinity;

#endif /* XBaseType_h */
