
#include "XONCore.h"
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <limits.h>
#include <arpa/inet.h>

#ifndef MIN
#define MIN(a, b) (((a)<(b))?(a):(b))
#endif /* MIN */
#ifndef MAX
#define MAX(a, b) (((a)>(b))?(a):(b))
#endif  /* MAX */

char * _Nonnull const XONErrorDomain = "XON";

#ifndef XAssert
#define XAssert(cond, desc) {\
    if (!(cond)) {\
        fprintf(stderr, "[%s error] %s\n", __func__, desc);\
        abort();\
    }\
}
#endif

#if DEBUG

#ifndef XDebugAssert
#define XDebugAssert(cond, desc) {\
    if (!(cond)) {\
        fprintf(stderr, "[%s error] %s\n", __func__, desc);\
        abort();\
    }\
}
#endif

#else

#ifndef XDebugAssert
#define XDebugAssert(cond, desc)
#endif

#endif

static inline uint64_t XONSInt64ZigzagEncode(int64_t value) {
    uint64_t tmp = *((uint64_t *)&value);
    return (tmp << UINT64_C(1)) ^ (0 - (tmp >> UINT64_C(63)));
}
static inline int64_t XONSInt64ZigzagDecode(uint64_t data) {
    return (int64_t)((data >> UINT64_C(1)) ^ (0 - (data & UINT64_C(1))));
}

/// require length >= 0 && length <= 8
static inline uint64_t __XONDecodeTrimLeadingZeroByteIntFromBuffer(const uint8_t * _Nonnull buffer, ssize_t length) {
    uint64_t v = 0;
    for (ssize_t i=0; i<length; i++) {
        v = (v << 8) + buffer[i];
    }
    return v;
}

/// require buffer.capacity >= 8
static inline ssize_t __XONEncodeTrimLeadingZeroByteIntToBuffer(uint8_t * _Nonnull buffer, uint64_t value) {
    // 63-7=56
    ssize_t used = 0;
    
    uint8_t byte = (uint8_t)(value >> 56);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)(value >> 48);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)(value >> 40);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)(value >> 32);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)(value >> 24);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)(value >> 16);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)(value >> 8);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)(value);
    if (used > 0 || 0 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    return used;
}

static inline ssize_t XONUInt64LeadingZeroBitCount(uint64_t x) {
    if (0 == x) {
        return 64;
    }
    int32_t r = 0;
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
static inline ssize_t XONUInt64TrailingZeroBitCount(uint64_t x) {
    if (0 == x) {
        return 64;
    }
    int32_t r = 0;
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
static inline ssize_t XONUInt64LeadingZeroByteCount(uint64_t x) {
    if (0 == x) {
        return 8;
    }
    int32_t r = 0;
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
    return r;
}
static inline ssize_t XONUInt64TrailingZeroByteCount(uint64_t x) {
    if (0 == x) {
        return 8;
    }
    int32_t r = 0;
    if (0 == (x & UINT64_C(0xFFFFFFFF))) {
        x >>= 32;
        r += 4;
    }
    if (0 == (x & UINT64_C(0xFFFF))) {
        x >>= 16;
        r += 2;
    }
    if (0 == (x & UINT64_C(0xFF))) {
        x >>= 8;
        r += 1;
    }
    return r;
}

static inline void XONDecodeTypeLayout(uint8_t byte, uint8_t * _Nonnull type, uint8_t * _Nonnull layout) {
    *layout = (byte & 0x1F);
    *type = (XONWireType_e)(byte >> 5);
}

static inline XONError_e __XONDecodeUInt63Varint(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint64_t * _Nonnull value) {
    ssize_t used = 0;
    uint64_t tmp = 0;
    if (*location >= capacity - used) {
        return XONErrorNotEnough;
    }
    uint8_t byte = bytes[*location + used];
    used += 1;
    tmp = byte & 0x7f;
    if (byte == 0x80) {
        return XONErrorVarInt;
    } else if (byte & 0x80) {
        while (*location < capacity - used) {
            if (used >= 9) {
                return XONErrorVarInt;
            }
            uint8_t byte = bytes[*location + used];
            used += 1;
            tmp = (tmp << 7) + (byte & 0x7f);
            if ((byte & 0x80) == 0) {
                *value = tmp;
                *location += used;
                return XONErrorNone;
            }
        }
        return XONErrorNotEnough;
    } else {
        *value = tmp;
        *location += 1;
        return XONErrorNone;
    }
}
static inline ssize_t __XONEncodeUInt63VarintLength(uint64_t value) {
    uint64_t x = (value >> 7) << 8;
    
    if (0 == x) {
        return 1;
    } else {
        ssize_t length = 9;
        if (0 == (x & UINT64_C(0xFFFFFFF000000000))) {
            x <<= 28;
            length -= 4;
        }
        if (0 == (x & UINT64_C(0xFFFC000000000000))) {
            x <<= 14;
            length -= 2;
        }
        if (0 == (x & UINT64_C(0xFE00000000000000))) {
            x <<= 7;
            length -= 1;
        }
        return length;
    }
}

static inline XONError_e __XONEncodeUInt63Varint(uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint64_t value) {
    ssize_t length = __XONEncodeUInt63VarintLength(value);
    if (*location + length > capacity) {
        return XONErrorNotEnough;
    }
    uint8_t * buffer = bytes + *location;
    *location += length;
    while (length > 1) {
        length -= 1;
        *buffer = (uint8_t)((value >> (7 * length)) | 0x80);
        buffer += 1;
    }
    *buffer = (uint8_t)(value & 0x7f);
    return XONErrorNone;
}

/// require buffer.capacity >= 9
static inline ssize_t __XONEncodeUInt63VarintToBuffer(uint8_t * _Nonnull buffer, uint64_t value) {
    // 63-7=56
    ssize_t used = 0;
    
    uint8_t byte = (uint8_t)((value >> 56) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 49) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 42) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 35) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 28) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 21) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 14) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 7) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }

    buffer[used] = (uint8_t)(value & 0x7f);
    used += 1;
    return used;
}

/// require buffer.capacity >= 5
static inline ssize_t __XONEncodeUInt32VarintToBuffer(uint8_t * _Nonnull buffer, uint32_t value) {
    ssize_t used = 0;
    
    uint8_t byte = (uint8_t)((value >> 28) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 21) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 14) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 7) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }

    buffer[used] = (uint8_t)(value & 0x7f);
    used += 1;
    return used;
}



//static inline XONError_e __XONEncodeUInt63Varint(uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint64_t value) {
//    XDebugAssert(bytes, "");
//
//    uint8_t buffer[8] = { 0 };
//    // 63-7=56
//    ssize_t used = 0;
//
//    uint8_t byte = (uint8_t)((value >> 56) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    byte = (uint8_t)((value >> 49) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    byte = (uint8_t)((value >> 42) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    byte = (uint8_t)((value >> 35) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    byte = (uint8_t)((value >> 28) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    byte = (uint8_t)((value >> 21) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    byte = (uint8_t)((value >> 14) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    byte = (uint8_t)((value >> 7) | 0x80);
//    if (used > 0 || 0x80 != byte) {
//        buffer[used] = byte;
//        used += 1;
//    }
//    if (*location >= capacity - used - 1) {
//        return XONErrorNotEnough;
//    }
//    memcpy(bytes + *location, buffer, used);
//    bytes[*location + used] = (uint8_t)(value & 0x7f);
//    *location += used + 1;
//    return XONErrorNone;
//}

XONError_e __XONEncodeUInt64Varint_old(uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint64_t value) {
    XDebugAssert(bytes, "");
    ssize_t length = (64 - XONUInt64LeadingZeroBitCount(value) + 6) / 7;
    if (length == 0) {
        length = 1;
    }
    if (*location + length > capacity) {
        return XONErrorNotEnough;
    }
    ssize_t lastOffset = length - 1;
    for (ssize_t offset=0; offset<lastOffset; offset++) {
        bytes[*location + offset] = (uint8_t)((value >> ((lastOffset - offset) * 7)) | 0x80);
    }
    bytes[*location + lastOffset] = (uint8_t)(value & 0x7f);
    *location += length;
    return XONErrorNone;
}

XONError_e __XONEncodeUInt64Varint_old2(uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint64_t value) {
    XDebugAssert(bytes, "");
    uint8_t buffer[16] = { 0 };
    ssize_t used = 0;
    for (ssize_t shift = 63; shift>0; shift-=7) {
        uint8_t byte = (uint8_t)((value >> shift) | 0x80);
        if (used > 0 || 0x80 != byte) {
            buffer[used] = byte;
            used += 1;
        }
    }
    buffer[used] = (uint8_t)(value & 0x7f);
    used += 1;
    
    if (*location >= capacity - used) {
        return XONErrorNotEnough;
    }
    memcpy(bytes + *location, buffer, used);
    *location += used;
    return XONErrorNone;
}

static inline ssize_t __XONEncodeUInt64VarintToBuffer(uint8_t * _Nonnull buffer, uint64_t value) {
    ssize_t used = 0;
    
    uint8_t byte = (uint8_t)((value >> 63) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 56) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 49) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 42) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 35) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 28) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 21) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 14) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 7) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    buffer[used] = (uint8_t)(value & 0x7f);
    used += 1;

    return used;
}

static inline XONError_e __XONEncodeUInt64Varint(uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint64_t value) {
    XDebugAssert(bytes, "");
    
    uint8_t buffer[16] = { 0 };
    // 63-7=56
    ssize_t used = 0;
    
    uint8_t byte = (uint8_t)((value >> 63) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 56) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 49) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 42) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 35) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 28) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 21) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 14) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    byte = (uint8_t)((value >> 7) | 0x80);
    if (used > 0 || 0x80 != byte) {
        buffer[used] = byte;
        used += 1;
    }
    buffer[used] = (uint8_t)(value & 0x7f);
    used += 1;

    if (*location >= capacity - used) {
        return XONErrorNotEnough;
    }
    memcpy(bytes + *location, buffer, used);
    *location += used;
    return XONErrorNone;
}

static inline XONError_e __XONDecodeUInt64Varint(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint64_t * _Nonnull value) {
    int32_t used = 0;
    uint64_t tmp = 0;
    if (*location >= capacity - used) {
        return XONErrorNotEnough;
    }
    uint8_t byte = bytes[*location + used];
    used += 1;
    tmp = byte & 0x7f;
    if (byte == 0x80) {
        return XONErrorVarInt;
    } else if (byte & 0x80) {
        while (*location < capacity - used) {
            if (used >= 10) {
                return XONErrorVarInt;
            }
            
            uint8_t byte = bytes[*location + used];
            used += 1;
            
            tmp = (tmp << 7) | (byte & 0x7f);
            if ((byte & 0x80) == 0) {
                if (used == 10 && bytes[*location] != 0x81) {
                    return XONErrorVarInt;
                }
                *value = tmp;
                *location += used;
                return XONErrorNone;
            }
        }
        return XONErrorNotEnough;
    } else {
        *value = tmp;
        *location += 1;
        return XONErrorNone;
    }
}

static inline XONError_e __XONDecodeHeaderCount(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint8_t layout, uint64_t * _Nonnull value) {
    uint64_t count = 0;
    if (layout == 31) {
        XONError_e result = __XONDecodeUInt64Varint(bytes, capacity, location, &count);
        if (result != XONErrorNone) {
            return result;
        }
        if (count > UINT64_MAX - 31) {
            return XONErrorCount;
        }
        count += 31;
    } else {
        count = layout;
    }
    *value = count;
    return XONErrorNone;
}

static inline ssize_t __XONEncodeSignAndSignificandToBuffer(uint8_t * _Nonnull buffer, uint64_t value) {
    ssize_t used = 0;
    uint64_t tmp = value;
    while (0 != tmp) {
        buffer[used] = (uint8_t)(tmp >> 56);
        used += 1;
        tmp = tmp << 8;
    }
    return used;
}

static inline XONError_e __XONDecodeSignAndSignificand(const uint8_t * _Nonnull bytes, ssize_t length, uint64_t * _Nonnull _value) {
    uint64_t value = 0;
    if (length > 0) {
        uint64_t v = 0;
        for (ssize_t i=0; i<length; i++) {
            v = bytes[i];
            value |= v << ((7 - i) * 8);
        }
        if (v == 0) {
            return XONErrorNumberContent;
        }
    }
    *_value = value;
    return XONErrorNone;
}


/// 返回值 [0, 16]
static inline ssize_t __XONEncodeSignificandToBuffer(uint8_t * _Nonnull buffer, uint64_t high, uint64_t low) {
    ssize_t used = sizeof(uint64_t) * 2;
    uint64_t h = ntohll(high);
    uint64_t l = ntohll(low);
    memcpy(buffer, &h, sizeof(uint64_t));
    if (low == 0) {
        used -= sizeof(uint64_t);
        used -= XONUInt64TrailingZeroByteCount(high);
    } else {
        memcpy(buffer + sizeof(uint64_t), &l, sizeof(uint64_t));
        used -= XONUInt64TrailingZeroByteCount(low);
    }
    return used;
}

// length <= 8 length > 0
static inline uint64_t __XONDecodeSignificandBytes(const uint8_t * _Nonnull bytes, ssize_t length) {
    uint64_t value = 0;
    if (length > 0) {
        uint64_t v = 0;
        for (ssize_t i=0; i<length; i++) {
            v = bytes[i];
            value |= v << ((7 - i) * 8);
        }
    }
    return value;
}
static inline XONError_e __XONDecodeSignificand(const uint8_t * _Nonnull bytes, ssize_t length, uint64_t * _Nonnull significandHigh, uint64_t * _Nonnull significandLow) {
    if (length > 16) {
        return XONErrorNumberContent;
    }
    uint64_t high = 0;
    uint64_t low = 0;
    if (length > 0) {
        if (bytes[length - 1] == 0) {
            return XONErrorNumberContent;
        }
        if (length > 8) {
            high = __XONDecodeSignificandBytes(bytes, 8);
            low = __XONDecodeSignificandBytes(bytes + 8, length - 8);
        } else {
            high = __XONDecodeSignificandBytes(bytes, length);
        }
    }
    *significandHigh = high;
    *significandLow = low;
    return XONErrorNone;
}


static inline XONNumberNormalContent_s __XONEncodeIntNumberInternal(uint32_t sign, uint64_t v) {
    XONNumberNormalContent_s content = {};
    // 高位->低位 前导0个数
    ssize_t leadingZeroBitCount = XONUInt64LeadingZeroBitCount(v);
    ssize_t exponent = 64 - leadingZeroBitCount;
    content.exponent = (int32_t)exponent;
    content.sign = sign;
    content.significandLow = 0;
    content.significandHigh = v << ((uint64_t)leadingZeroBitCount + 1);

    return content;
}

///// f: f != nan && f != inf && f != 0
//static inline XONNumberNormalContent_s _XONEncodeNumberFloat64(double f) {
//    XONNumberNormalContent_s number = {};
//    uint64_t bits = *(uint64_t *)&(f);
//    uint64_t sign = bits & (UINT64_C(1) << 63);
//    uint64_t te = (bits & UINT64_C(0x7FF0000000000000)) >> 52;
//    int64_t e = (int64_t)te - 1023;
//    
//    XDebugAssert(e < 1024, "");
//    XDebugAssert(e >= -1023, "");
//
//    if (e == 1024) {// nan inf
//        abort();
//    } else if (e == -1023) {
//        // subnormal numbers
//        uint64_t m = (bits & UINT64_C(0xFFFFFFFFFFFFF)) << UINT64_C(12);
//        XDebugAssert(0 != m, "");
//        uint64_t shift = XONUInt64LeadingZeroBitCount(m) + 1;
//        XDebugAssert(shift <= 52, "");
//        m = m << shift;
//        number.exponent = -1022 - shift;
//        number.signAndSignificand = sign | (m >> 1);
//    } else {
//        // e: [1, 2046]
//        uint64_t m = (bits & UINT64_C(0xFFFFFFFFFFFFF)) << UINT64_C(11);
//        number.exponent = e;
//        number.signAndSignificand = sign | m;
//    }
//    return number;
//}

/// number != 0
static inline XONNumberNormalContent_s _XONEncodeNumberUInt64(uint64_t number) {
    XDebugAssert(number != 0, "");
    return __XONEncodeIntNumberInternal(0, number);
}

/// number != 0
static inline XONNumberNormalContent_s _XONEncodeNumberSInt64(int64_t value) {
    XDebugAssert(value != 0, "");
    uint64_t v = value > 0 ? value : value * (-1);
    uint32_t sign = value > 0 ? 0 : UINT32_C(1);
    return __XONEncodeIntNumberInternal(sign, v);
}

static inline XONError_e __XONDecodeNumberValue(int64_t exponent, uint64_t signAndSignificand, XONNumberValue_s * _Nonnull number) {
    uint64_t sign = signAndSignificand & (UINT64_C(1) << 63);
    uint64_t m = signAndSignificand & (UINT64_MAX >> 1);
    uint64_t m2 = (UINT64_C(1) << 63) | m;
    int64_t trailingZerosCount = XONUInt64TrailingZeroBitCount(m2);
    if (exponent > -1023 && exponent < 1024) {
        if (trailingZerosCount >= 11) {
            uint64_t e = exponent + 1023;
            uint64_t bits = sign | (e << 52) | (m >> 11);
            number->type = XONNumberTypeFloat64;
            number->value.f = *(double *)&(bits);
            return XONErrorNone;
        } else {
            uint64_t m2 = (UINT64_C(1) << 63) | m;
            if (exponent >= 0 && exponent <= 63 && 63 - exponent <= trailingZerosCount) {
                uint64_t value = m2 >> (63 - exponent);
                // 1 exponent=0
                // 2 exponent=1 1
                uint64_t sint64Min = UINT64_C(1) << 63;
                if (sign) {// 负数
                    if (value == sint64Min) {
                        number->type = XONNumberTypeSInt;
                        number->value.s = INT64_MIN;
                        return XONErrorNone;
                    } else if (value < sint64Min) {
                        int64_t sv = value;
                        sv *= -1;
                        number->type = XONNumberTypeSInt;
                        number->value.s = sv;
                        return XONErrorNone;
                    } else {
                        number->type = XONNumberTypeNone;
                        number->value.u = 0;
                        return XONErrorNumberOutOfRange;
                    }
                } else {
                    if (value < sint64Min) {
                        int64_t sv = value;
                        number->type = XONNumberTypeSInt;
                        number->value.s = sv;
                    } else {
                        number->type = XONNumberTypeUInt;
                        number->value.u = value;
                    }
                    return XONErrorNone;
                }
            } else {
                number->type = XONNumberTypeNone;
                number->value.u = 0;
                return XONErrorNumberOutOfRange;
            }
        }
    } else if (exponent >= 1024) {
        number->type = XONNumberTypeNone;
        number->value.u = 0;
        return XONErrorNumberOutOfRange;
    } else { // number.e <= -1023
        int64_t shift = -1022 - exponent + 11;
        if (trailingZerosCount >= shift) {
            uint64_t bits = sign | (m2 >> shift);
            number->type = XONNumberTypeFloat64;
            number->value.f = *(double *)&(bits);
            return XONErrorNone;
        } else {
            number->type = XONNumberTypeNone;
            number->value.u = 0;
            return XONErrorNumberOutOfRange;
        }
    }
}

ssize_t XONHeaderMaxLength(void) {
    return 24;
}

XONError_e XONDecodeHeader(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, XONValueHeader_s * _Nonnull header) {
    XAssert(bytes, "");
    XAssert(header, "");
    XAssert(location, "");

    bzero(header, sizeof(XONValueHeader_s));
    if (*location >= capacity) {
        return XONErrorNotEnough;
    }
    uint8_t byte = bytes[*location];
    uint8_t type = 0;
    uint8_t layout = 0;
    XONDecodeTypeLayout(byte, &type, &layout);
    *location += 1;
    header->type = type;
    header->layout = layout;
    return XONErrorNone;
}

XONError_e XONDecodeNormalNumber(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, ssize_t len, XONNumberNormalContent_s * _Nonnull content) {
    XAssert(content, "");
    ssize_t startIndex = *location;
    if (*location > capacity - len) {
        return XONErrorNotEnough;
    }
    uint64_t signAndExponent = 0;
    
//    uint64_t signAndExponent = XONSInt64ZigzagEncode((int64_t)value.exponent) << 1;
//    if (value.sign != 0) {
//        signAndExponent += 1;
//    }

    
    XONError_e result = __XONDecodeUInt64Varint(bytes, *location + len, location, &signAndExponent);
    if (result != XONErrorNone) {
        return result;
    }
    uint32_t sign = signAndExponent & 0x1;

    ssize_t usingLength = *location - startIndex;
    int64_t exponent = XONSInt64ZigzagDecode((signAndExponent >> 1));
    uint64_t significandHigh = 0;
    uint64_t significandLow = 0;
    result = __XONDecodeSignificand(bytes + *location, len - usingLength, &significandHigh, &significandLow);
    if (result != XONErrorNone) {
        return result;
    }
    if (exponent > INT32_MAX || exponent < INT32_MIN) {
        return XONErrorNumberContent;
    }
    *location += len - usingLength;
    content->sign = sign;
    content->exponent = (int32_t)exponent;
    content->significandHigh = significandHigh;
    content->significandLow = significandLow;
    return XONErrorNone;
}


XONError_e XONNumberToFloat64(const XONNumberNormalContent_s * _Nonnull content, double * _Nonnull value) {
    if (content->significandLow != 0) {
        return XONErrorNumberOutOfRange;
    }
    if ((content->significandHigh & 0xfff) != 0) {
        return XONErrorNumberOutOfRange;
    }
    uint64_t bits = 0x3FE0000000000000ULL;
    if (content->sign != 0) {
        bits = bits | 0x8000000000000000ULL;
    }
    bits = bits | (content->significandHigh >> 12);
    double m = *(double *)&bits;
    double result = scalbn(m, content->exponent);
    int e2 = 0;
    double m2 = frexp(result, &e2);
    if (m2 != m) {
        return XONErrorNumberOutOfRange;
    }
    *value = result;
    return XONErrorNone;
}


XONError_e XONNumberToSInt64(const XONNumberNormalContent_s * _Nonnull content, int64_t * _Nonnull value) {
    if (content->significandLow != 0) {
        return XONErrorNumberOutOfRange;
    }
    if ((content->significandHigh & 0x1) != 0) {
        return XONErrorNumberOutOfRange;
    }
    // 1 e: 1, m: 0.500000,  e: 64, m: 0.750000, mbits: 3fe8000000000000
    // 0xC000000000000000ULL,  e: 1, m: 0.500000, mbits: 3fe0000000000000
    
    uint64_t bits = (UINT64_C(1) << UINT64_C(63)) | (content->significandHigh >> UINT64_C(1));
    int64_t trailingZerosCount = XONUInt64TrailingZeroBitCount(bits);
    
//    //    UINT64_C(1) << 63
    int exponent = content->exponent;
    if (exponent >= 1 && exponent <= 64 && 64 - exponent <= trailingZerosCount) {
        uint64_t n = bits >> ((uint64_t)(64 - exponent));
        
        if (content->sign != 0) {
            // * -1
            if (n == 0x8000000000000000ULL) {
                *value = INT64_MIN;
                return XONErrorNone;
            } else if (n < 0x8000000000000000ULL) {
                *value = (int64_t)n * (-1LL);
                return XONErrorNone;
            } else {
                return XONErrorNumberOutOfRange;
            }
        } else {
            if (n < 0x8000000000000000ULL) {
                *value = (int64_t)n;
                return XONErrorNone;
            } else {
                return XONErrorNumberOutOfRange;
            }
        }
    } else {
        return XONErrorNumberOutOfRange;
    }
//    uint64_t bits = 0x3FE0000000000000ULL;
//    if (content->sign != 0) {
//        bits = bits | 0x8000000000000000ULL;
//    }
//    bits = bits | (content->significandHigh >> 12);
//    double m = *(double *)&bits;
//    double result = scalbn(m, content->exponent);
//    int e2 = 0;
//    double m2 = frexp(result, &e2);
//    if (m2 != m) {
//        return XONErrorNumberOutOfRange;
//    }
//    *value = result;
    
//    uint64_t m2 = (UINT64_C(1) << 63) | m;
//    if (exponent >= 0 && exponent <= 63 && 63 - exponent <= trailingZerosCount) {
//        uint64_t value = m2 >> (63 - exponent);
//        // 1 exponent=0
//        // 2 exponent=1 1
//        uint64_t sint64Min = UINT64_C(1) << 63;
//        if (sign) {// 负数
//            if (value == sint64Min) {
//                number->type = XONNumberTypeSInt;
//                number->value.s = INT64_MIN;
//                return XONErrorNone;
//            } else if (value < sint64Min) {
//                int64_t sv = value;
//                sv *= -1;
//                number->type = XONNumberTypeSInt;
//                number->value.s = sv;
//                return XONErrorNone;
//            } else {
//                number->type = XONNumberTypeNone;
//                number->value.u = 0;
//                return XONErrorNumberOutOfRange;
//            }
//        } else {
//            if (value < sint64Min) {
//                int64_t sv = value;
//                number->type = XONNumberTypeSInt;
//                number->value.s = sv;
//            } else {
//                number->type = XONNumberTypeUInt;
//                number->value.u = value;
//            }
//            return XONErrorNone;
//        }
//    } else {
//        number->type = XONNumberTypeNone;
//        number->value.u = 0;
//        return XONErrorNumberOutOfRange;
//    }
    return XONErrorNone;
}
XONError_e XONNumberToUInt64(const XONNumberNormalContent_s * _Nonnull content, uint64_t * _Nonnull value) {
    if (content->significandLow != 0) {
        return XONErrorNumberOutOfRange;
    }
    if ((content->significandHigh & 0x1) != 0) {
        return XONErrorNumberOutOfRange;
    }
    if (content->sign != 0) {
        return XONErrorNumberOutOfRange;
    }
    // 1 e: 1, m: 0.500000,  e: 64, m: 0.750000, mbits: 3fe8000000000000
    // 0xC000000000000000ULL,  e: 1, m: 0.500000, mbits: 3fe0000000000000
    
    uint64_t bits = (UINT64_C(1) << UINT64_C(63)) | (content->significandHigh >> UINT64_C(1));
    int64_t trailingZerosCount = XONUInt64TrailingZeroBitCount(bits);
    
//    //    UINT64_C(1) << 63
    int exponent = content->exponent;
    if (exponent >= 1 && exponent <= 64 && 64 - exponent <= trailingZerosCount) {
        *value = bits >> ((uint64_t)(64 - exponent));
        return XONErrorNone;
    } else {
        return XONErrorNumberOutOfRange;
    }
//
//    uint64_t bits = (content->significandHigh >> UINT64_C(1)) | (UINT64_C(1) << UINT64_C(63));
//    if (content->sign != 0) {
//        bits = bits | 0x8000000000000000ULL;
//    }
//    bits = bits | (content->significandHigh >> 12);
//    double m = *(double *)&bits;
//    double result = scalbn(m, content->exponent);
//    int e2 = 0;
//    double m2 = frexp(result, &e2);
//    if (m2 != m) {
//        return XONErrorNumberOutOfRange;
//    }
//    *value = result;
    return XONErrorNone;
}

//XONError_e XONDecodeNumber64(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, ssize_t format, ssize_t count, XONNumberValue_s * _Nonnull number) {
//    switch (format) {
//        case XONNumberFormatZero: {
//            number->type = XONNumberTypeFloat64;
//            number->value.f = __XONDoubleZero();
//            return XONErrorNone;
//        }
//        case XONNumberFormatNan: {
//            number->type = XONNumberTypeFloat64;
//            number->value.f = __XONDoubleNan();
//            return XONErrorNone;
//        }
//        case XONNumberFormatPositiveInfinity: {
//            number->type = XONNumberTypeFloat64;
//            number->value.f = __XONDoublePositiveInfinity();
//            return XONErrorNone;
//        }
//        case XONNumberFormatNegativeInfinity: {
//            number->type = XONNumberTypeFloat64;
//            number->value.f = __XONDoubleNegativeInfinity();
//            return XONErrorNone;
//        }
//        case XONNumberFormatFloat: {
//            // e: varint64 ; signAndSignificand
//            ssize_t len = count;
//            ssize_t startIndex = *location;
//            if (*location > capacity - len) {
//                return XONErrorNotEnough;
//            }
//            uint64_t ev = 0;
//            XONError_e result = __XONDecodeUInt64Varint(bytes, *location + len, location, &ev);
//            if (result != XONErrorNone) {
//                return result;
//            }
//            ssize_t usingLength = *location - startIndex;
//            int64_t exponent = XONSInt64ZigzagDecode(ev);
//            uint64_t signAndSignificand = 0;
//            result = __XONDecodeSignAndSignificand(bytes + *location, len - usingLength, &signAndSignificand);
//            if (result != XONErrorNone) {
//                return result;
//            }
//            *location += len - usingLength;
//            return __XONDecodeNumberValue(exponent, signAndSignificand, number);
//        }
//        default: {
//            return XONErrorNumberContent;
//        }
//    }
//}
XONError_e XONDecodeCount(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, unsigned int layout, ssize_t * _Nonnull receiver) {
    XAssert(bytes, "");
    XAssert(receiver, "");
    XAssert(location, "");
    uint64_t count = 0;
    XONError_e result = __XONDecodeHeaderCount(bytes, capacity, location, layout, &count);
    if (result != XONErrorNone) {
        return result;
    }
    if (count > SSIZE_MAX) {
        return XONErrorCount;
    }
    *receiver = (ssize_t)count;
    return XONErrorNone;
}

XONError_e XONDecodeTime(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, ssize_t count, XTimestamp * _Nonnull time){
    XAssert(bytes, "");
    XAssert(time, "");
    XAssert(location, "");
    if (*location > capacity - count) {
        return XONErrorNotEnough;
    }
    uint64_t encodedValue = __XONDecodeTrimLeadingZeroByteIntFromBuffer(bytes + *location, count);
    *location += count;
    int64_t microsecond = XONSInt64ZigzagDecode(encodedValue);
    if (0 != microsecond && XTimestampInvalidDefault() != microsecond) {
        *time = microsecond;
        return XONErrorNone;
    } else {
        return XONErrorTimeContent;
    }
}

XONError_e XONDecodeFieldKeyOffset(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint32_t * _Nonnull offset) {
    XAssert(bytes, "");
    XAssert(location, "");
    XAssert(offset, "");
    uint64_t v = 0;
    XONError_e error = __XONDecodeUInt63Varint(bytes, capacity, location, &v);
    if (XONErrorNone != error) {
        return error;
    }
    if (v >= UINT32_MAX) {
        return XONErrorMessageFieldKeyOffset;
    }
    v += 1;
    *offset = (uint32_t)v;
    return XONErrorNone;
}

#pragma mark - encode


static inline void XONEncodeTypeLayout(uint8_t * _Nonnull byte, uint8_t type, uint8_t layout) {
    uint8_t v = (type << 5) | (layout & 0x1f);
    *byte = v;
}
static inline uint8_t XONNullByte(void) {
    uint8_t header = 0;
    XONEncodeTypeLayout(&header, XONWireTypeSimpleValue, XONSimpleValueNil);
    return header;
}
static inline uint8_t XONBoolByte(_Bool value) {
    uint8_t header = 0;
    XONEncodeTypeLayout(&header, XONWireTypeSimpleValue, value ? XONSimpleValueBoolTrue : XONSimpleValueBoolFalse);
    return header;
}

static inline void XONEncodeBufferExpandCapacity(XONEncodeBuffer_s * _Nonnull buffer, ssize_t size) {
    if (buffer->capacity < size) {
        XONEncodeBufferReserveCapacity(buffer, size);
    }
}

XONError_e XONEncodeFieldKeyOffset(XONEncodeBuffer_s * _Nonnull buffer, uint32_t offset) {
    if (offset <= 0) {
        return XONErrorMessageIndexOffset;
    }
    XONEncodeBufferExpandCapacity(buffer, buffer->location + 5);
    uint32_t value = offset - 1;
    ssize_t length = __XONEncodeUInt32VarintToBuffer(buffer->bytes + buffer->location, value);
    buffer->location += length;
    return XONErrorNone;
}

XONError_e XONEncodeNull(XONEncodeBuffer_s * _Nonnull buffer) {
    XONEncodeBufferExpandCapacity(buffer, buffer->location + 1);
    buffer->bytes[buffer->location] = XONNullByte();
    buffer->location += 1;
    return XONErrorNone;
}

XONError_e XONEncodeBool(XONEncodeBuffer_s * _Nonnull buffer, _Bool value) {
    XONEncodeBufferExpandCapacity(buffer, buffer->location + 1);
    buffer->bytes[buffer->location] = XONBoolByte(value);
    buffer->location += 1;
    return XONErrorNone;
}


/// TODO: FIX
static inline XONError_e __XONEncodeNumberByte(XONEncodeBuffer_s * _Nonnull buffer, XONNumberNormalContent_s value) {
    
    /// 暂不支持128位
    if (value.significandLow != 0) {
        return XONErrorNotSupport;
    }
    XONEncodeBufferExpandCapacity(buffer, buffer->location + 19);
    ssize_t length = 1;
    uint64_t signAndExponent = XONSInt64ZigzagEncode((int64_t)value.exponent) << 1;
    if (value.sign != 0) {
        signAndExponent += 1;
    }
    length += __XONEncodeUInt64VarintToBuffer(buffer->bytes + buffer->location + length, signAndExponent);
    length += __XONEncodeSignificandToBuffer(buffer->bytes + buffer->location + length, value.significandHigh, value.significandLow);
    uint8_t layout = length - 1 + XONSimpleValueNumberZero;
    if (layout >= 32) {
        return XONErrorLayout;
    }
    XONEncodeTypeLayout(buffer->bytes + buffer->location, XONWireTypeSimpleValue, layout);
    buffer->location += length;
    return XONErrorNone;
}

static inline XONError_e __XONEncodeSimpleNumberHeader(XONEncodeBuffer_s * _Nonnull buffer, uint32_t layout) {
    XONEncodeBufferExpandCapacity(buffer, buffer->location + 1);
    uint8_t header = 0;
    XONEncodeTypeLayout(&header, XONWireTypeSimpleValue, layout);
    buffer->bytes[buffer->location] = header;
    buffer->location += 1;
    return XONErrorNone;
}
XONError_e XONEncodeNumberUInt64(XONEncodeBuffer_s * _Nonnull buffer, uint64_t value) {
    if (0 == value) {
        return __XONEncodeSimpleNumberHeader(buffer, XONSimpleValueNumberZero);
    } else {
        XONNumberNormalContent_s data = _XONEncodeNumberUInt64(value);
        return __XONEncodeNumberByte(buffer, data);
    }
}
XONError_e XONEncodeNumberSInt64(XONEncodeBuffer_s * _Nonnull buffer, int64_t value) {
    if (0 == value) {
        return __XONEncodeSimpleNumberHeader(buffer, XONSimpleValueNumberZero);
    } else {
        XONNumberNormalContent_s data = _XONEncodeNumberSInt64(value);
        return __XONEncodeNumberByte(buffer, data);
    }
}
XONError_e XONEncodeNumberDouble(XONEncodeBuffer_s * _Nonnull buffer, double value) {
    if (value == __XONDoubleZero()) {
        return __XONEncodeSimpleNumberHeader(buffer, XONSimpleValueNumberZero);
    } else if (isnan(value)) {
        return __XONEncodeSimpleNumberHeader(buffer, XONSimpleValueNumberNAN);
    } else if (isinf(value)) {
        if (value < 0) {
            return __XONEncodeSimpleNumberHeader(buffer, XONSimpleValueNumberNegativeInfinity);
        } else {
            return __XONEncodeSimpleNumberHeader(buffer, XONSimpleValueNumberPositiveInfinity);
        }
    } else {
        int e = 0;
        double m = frexp(value, &e);
        uint64_t bits = *((uint64_t *)(&m));
        XONNumberNormalContent_s content = {};
        content.sign = (uint32_t)(bits >> 63);
        content.exponent = e;
        content.significandHigh = bits << UINT64_C(12);
        content.significandLow = 0;
        return __XONEncodeNumberByte(buffer, content);
    }
}

void test2(double value) {
    
    int e = 0;
    double m = frexp(value, &e);
    double v2 = scalbn(m, e);
    XAssert(v2 == value, "");
    uint64_t bits = *((uint64_t *)(&m));
    XONNumberNormalContent_s content = {};
    content.sign = (uint32_t)(bits >> 63);
    content.exponent = e;
    content.significandHigh = bits << 12;
    content.significandLow = 0;

    uint64_t vbits = *((uint64_t *)(&value));

    printf("v: %llx\n", vbits);
    printf("m: %llx\n", bits);

}
void test(void) {
    // 1 e: 1, m: 0.500000,  e: 64, m: 0.750000, mbits: 3fe8000000000000
    // 0xC000000000000000ULL,  e: 1, m: 0.500000, mbits: 3fe0000000000000

//    double value = (double)(0xC000000000000000ULL);
    double value = (double)(1);
    int e = 0;
    double m = frexp(value, &e);
    uint64_t b = *(uint64_t *)&m;
    printf("e: %d, m: %lf, mbits: %llx \n", e, m, b);
    
    
    test2(0.1);
    test2(12314124131);
    test2(1423534);
    test2(-0.1);
    test2(-12314124131);
    test2(-1423534);
}

XONError_e XONEncodeTimeInvalid(XONEncodeBuffer_s * _Nonnull buffer) {
    XONEncodeBufferExpandCapacity(buffer, buffer->location + 1);
    uint8_t header = 0;
    XONEncodeTypeLayout(&header, XONWireTypeSimpleValue, XONSimpleValueTimeInvalid);
    buffer->bytes[buffer->location] = header;
    buffer->location += 1;
    return XONErrorNone;
}
XONError_e XONEncodeTimeZero(XONEncodeBuffer_s * _Nonnull buffer) {
    XONEncodeBufferExpandCapacity(buffer, buffer->location + 1);
    uint8_t header = 0;
    XONEncodeTypeLayout(&header, XONWireTypeSimpleValue, XONSimpleValueTime0);
    buffer->bytes[buffer->location] = header;
    buffer->location += 1;
    return XONErrorNone;
}

XONError_e XONEncodeTime(XONEncodeBuffer_s * _Nonnull buffer, XTimestamp microsecond) {
    if (INT64_MIN == microsecond) {
        return XONEncodeTimeInvalid(buffer);
    } else if (0 == microsecond) {
        return XONEncodeTimeZero(buffer);
    } else {
        uint64_t encodedBytes = XONSInt64ZigzagEncode(microsecond);
        ssize_t count = 8 - XONUInt64LeadingZeroByteCount(encodedBytes);
        
        XONEncodeBufferExpandCapacity(buffer, buffer->location + 1 + count);
        uint8_t header = 0;

        XONEncodeTypeLayout(&header, XONWireTypeSimpleValue, XONSimpleValueTime0 + count);
        buffer->bytes[buffer->location] = header;
        buffer->location += 1;
        
        while (count > 0) {
            buffer->bytes[buffer->location] = (uint8_t)(encodedBytes >> ((count - 1) * 8));
            buffer->location += 1;
            count -= 1;
        }
        return XONErrorNone;
    }
}


static inline XONError_e __XONEncodeHeaderCount(XONEncodeBuffer_s * _Nonnull buffer, XONWireType_e type, ssize_t count) {
    if (count < 0) {
        return XONErrorCount;
    }
    if (count >= 31) {
        XONEncodeBufferExpandCapacity(buffer, buffer->location + 10 + count);
        uint8_t header = 0;
        XONEncodeTypeLayout(&header, type, 31);
        buffer->bytes[buffer->location] = header;
        uint64_t varint = count - 31;
        ssize_t length = 1 + __XONEncodeUInt63VarintToBuffer(buffer->bytes + buffer->location + 1, varint);
        buffer->location += length;
        return XONErrorNone;
    } else {
        XONEncodeBufferExpandCapacity(buffer, buffer->location + 1 + count);
        uint8_t layout = (uint8_t)count;
        uint8_t header = 0;
        XONEncodeTypeLayout(&header, type, layout);
        buffer->bytes[buffer->location] = header;
        buffer->location += 1;
        return XONErrorNone;
    }
}

XONError_e XONEncodeMessageHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count) {
    return __XONEncodeHeaderCount(buffer, XONWireTypeMessage, count);
}

XONError_e XONEncodeArrayHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count) {
    return __XONEncodeHeaderCount(buffer, XONWireTypeArray, count);
}

XONError_e XONEncodeDataHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count) {
    return __XONEncodeHeaderCount(buffer, XONWireTypeData, count);
}

XONError_e XONEncodeStringHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count) {
    return __XONEncodeHeaderCount(buffer, XONWireTypeString, count);
}

XONError_e XONEncodeBody(XONEncodeBuffer_s * _Nonnull buffer, const void * _Nonnull data, ssize_t count) {
    if (count < 0) {
        return XONErrorCount;
    }
    if (count > 0 && NULL == data) {
        return XONErrorArgumentError;
    }
    XONEncodeBufferExpandCapacity(buffer, buffer->location + count);
    memcpy(buffer->bytes + buffer->location, data, count);
    buffer->location += count;
    return XONErrorNone;
}
XONError_e XONEncodeData(XONEncodeBuffer_s * _Nonnull buffer, const void * _Nullable data, ssize_t count) {
    XONError_e error = __XONEncodeHeaderCount(buffer, XONWireTypeData, count);
    if (XONErrorNone != error) {
        return error;
    }
    if (count > 0 && NULL == data) {
        return XONErrorArgumentError;
    }
    XONEncodeBufferExpandCapacity(buffer, buffer->location + count);
    memcpy(buffer->bytes + buffer->location, data, count);
    buffer->location += count;
    return XONErrorNone;

}
XONError_e XONEncodeString(XONEncodeBuffer_s * _Nonnull buffer, const void * _Nullable cString, ssize_t count) {
    XONError_e error = __XONEncodeHeaderCount(buffer, XONWireTypeString, count);
    if (XONErrorNone != error) {
        return error;
    }
    if (count > 0 && NULL == cString) {
        return XONErrorArgumentError;
    }
    XONEncodeBufferExpandCapacity(buffer, buffer->location + count);
    memcpy(buffer->bytes + buffer->location, cString, count);
    buffer->location += count;
    return XONErrorNone;
}

#pragma mark - XONEncodeBuffer

static inline uint32_t clz32(uint32_t x) {
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

static inline uint64_t clz64(uint64_t x) {
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

size_t clz(size_t n) {
    if (sizeof(size_t) == 8) {
        return clz64((uint64_t)n);
    } else if (sizeof(size_t) == 4) {
        return clz32((uint32_t)n);
    } else {
        abort();
    }
}
ssize_t XONRoundUpSize(ssize_t minSize) {
    size_t size = MAX(0x1000, minSize);
    size_t leadingZeroBitCount = clz(size);
    size_t one = 1;
    if ((one << (sizeof(size_t) * 8 - 1 - leadingZeroBitCount)) != size) {
        size = one << (sizeof(size_t) * 8 - leadingZeroBitCount);
    }
    XAssert(size <= SSIZE_MAX, "");
    return size;
}

void _XONEncodeBufferDefaultRealloc(XONEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity) {
    XAssert(minCapacity >= 0, "");
    XAssert(buffer, "");
    ssize_t size = XONRoundUpSize(MAX(buffer->location, minCapacity));
    if (size != buffer->capacity) {
        void * ptr = realloc(buffer->context, size);
        XAssert(ptr, "");
        buffer->context = ptr;
        buffer->bytes = (uint8_t *)ptr;
        buffer->capacity = size;
    }
}
void _XONEncodeBufferDefaultDealloc(XONEncodeBuffer_s * _Nonnull buffer) {
    if (buffer->context) {
        free(buffer->context);
    }
    bzero(buffer, sizeof(XONEncodeBuffer_s));
}
void _XONEncodeBufferDefaultFitSize(XONEncodeBuffer_s * _Nonnull buffer) {
    XAssert(buffer, "");
    if (buffer->capacity > buffer->location) {
        void * ptr = realloc(buffer->context, buffer->location);
        XAssert(ptr, "");
        buffer->context = ptr;
        buffer->bytes = (uint8_t *)ptr;
        buffer->capacity = buffer->location;
    }
}
