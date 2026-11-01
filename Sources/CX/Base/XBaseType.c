

#include "XCoreBase.h"
#include "XProcess.h"

#pragma mark - Integer

uint32_t UInt32Random(void) {
    uint32_t result = 0;
    XRandomBytes(&result, sizeof(uint32_t));
    return result;
}
uint64_t UInt64Random(void) {
    uint32_t result = 0;
    XRandomBytes(&result, sizeof(uint32_t));
    return result;
    
}
size_t UIntRandom(void) {
    size_t result = 0;
    XRandomBytes(&result, sizeof(size_t));
    return result;
}


int UInt64VarintEncodeSize(uint64_t value) {
    if (value < (UINT64_C(0x1) << UINT64_C(28))) {
        if (value < (UINT64_C(0x1) << UINT64_C(14))) {
            if (value < (UINT64_C(0x1) << UINT64_C(7))) {
                return 1;
            } else {
                return 2;
            }
        } else {
            if (value < (UINT64_C(0x1) << UINT64_C(21))) {
                return 3;
            } else {
                return 4;
            }
        }
    } else if (value < (UINT64_C(0x1) << UINT64_C(56))) {
        if (value < (UINT64_C(0x1) << UINT64_C(42))) {
            if (value < (UINT64_C(0x1) << UINT64_C(35))) {
                return 5;
            } else {
                return 6;
            }
        } else {
            if (value < (UINT64_C(0x1) << UINT64_C(49))) {
                return 7;
            } else {
                return 8;
            }
        }
    } else {
        if (value < (UINT64_C(0x1) << UINT64_C(63))) {
            return 9;
        } else {
            return 10;
        }
    }
}
int UInt32VarintEncodeSize(uint32_t value) {
    if (value < (UINT32_C(0x1) << UINT32_C(14))) {
        if (value < (UINT32_C(0x1) << UINT32_C(7))) {
            return 1;
        } else {
            return 2;
        }
    } else if (value < (UINT32_C(0x1) << UINT32_C(28))) {
        if (value < (UINT32_C(0x1) << UINT32_C(21))) {
            return 3;
        } else {
            return 4;
        }
    } else {
        return 5;
    }
}

int UInt64VarintEncode(uint64_t value, uint8_t * _Nonnull bytes, size_t capacity) {
    XAssert(bytes, "");
    int32_t length = 0;
    uint64_t tmp = value;
    uint8_t byte = 0;
    if (capacity < 1) {
        return 0;
    }
    
    byte = (tmp >> 63) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 10) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 56) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 9) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 49) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 8) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 42) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 7) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 35) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 6) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 28) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 5) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 21) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 4) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 14) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 3) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 7) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 2) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 0) & 0x7f;
    bytes[length] = byte;
    length += 1;
    return length;
}


int UInt64VarintDecode(uint64_t * _Nonnull value, const uint8_t * _Nonnull bytes, size_t length) {
    XAssert(value, "");
    XAssert(bytes, "");
    int32_t used = 0;
    bool_t isFinished = false;
    uint64_t tmp = 0;
    if (length <= 0) {
        return 0;
    }

    while (!isFinished) {
        if (used >= 10) {
            return -1;
        }
        if (length <= used) {
            return 0;
        }
        
        uint8_t byte = bytes[used];
        used += 1;
        if (used == 1) {
            if (byte == 0x80) {
                return -1;
            }
        }
        
        tmp = tmp << 7;
        tmp += (byte & 0x7f);
        isFinished = ((byte & 0x80) != 0x80);
    }
    if (used == 10) {
        if (bytes[0] != 0x81) {
            return -1;
        }
    }
    *value = tmp;
    return used;
}

int UInt32VarintEncode(uint32_t value, uint8_t * _Nonnull bytes, size_t capacity) {
    XAssert(bytes, "");
    int32_t length = 0;
    int32_t tmp = value;
    uint8_t byte = 0;
    if (capacity < 1) {
        return 0;
    }
    
    byte = (tmp >> 28) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 5) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 21) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 4) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 14) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 3) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 7) & 0x7f;
    if (length > 0 || 0 != byte) {
        if (capacity < 2) {
            return 0;
        }
        byte = byte | 0x80;
        bytes[length] = byte;
        length += 1;
    }
    byte = (tmp >> 0) & 0x7f;
    bytes[length] = byte;
    length += 1;
    return length;
}
int UInt32VarintDecode(uint32_t * _Nonnull value, const uint8_t * _Nonnull bytes, size_t length) {
    XAssert(value, "");
    XAssert(bytes, "");
    int32_t used = 0;
    bool_t isFinished = false;
    uint32_t tmp = 0;
    if (length <= 0) {
        return 0;
    }
    while (!isFinished) {
        if (used >= 5) {
            return -1;
        }
        if (length <= used) {
            return 0;
        }
        
        uint8_t byte = bytes[used];
        used += 1;
        if (used == 1) {
            if (byte == 0x80) {
                return -1;
            }
        }
        
        tmp = tmp << 7;
        tmp += (byte & 0x7f);
        isFinished = ((byte & 0x80) != 0x80);
    }
    if (used == 5) {
        if ((bytes[0] & 0x7f) > 0xf) {
            return -1;
        }
    }
    *value = tmp;
    return used;
}


#pragma mark - Float
// https://c.biancheng.net/view/314.html

const XCFloat144_s __XCFloat144DefaultNotANumber = {
    .se = 0x7FFF,
    .fractionHigh = 0xC000000000000000,
    .fractionLow = 0
};

/// +0
const XCFloat144_s __XCFloat144PositiveZero = {
    .se = 0,
    .fractionHigh = 0,
    .fractionLow = 0
};

/// -0
const XCFloat144_s __XCFloat144NegativeZero = {
    .se = 0x8000,
    .fractionHigh = 0,
    .fractionLow = 0
};

/// 正无穷
const XCFloat144_s __XCFloat144PositiveInfinity = {
    .se = 0x7FFF,
    .fractionHigh = 0x8000000000000000,
    .fractionLow = 0
};

/// 负无穷
const XCFloat144_s __XCFloat144NegativeInfinity = {
    .se = 0xFFFF,
    .fractionHigh = 0x8000000000000000,
    .fractionLow = 0
};

const XCFloat144_s * _Nonnull XCFloat144DefaultNotANumber = &__XCFloat144DefaultNotANumber;

const XCFloat144_s * _Nonnull XCFloat144DefaultZero = &__XCFloat144PositiveZero;
const XCFloat144_s * _Nonnull XCFloat144PositiveZero = &__XCFloat144PositiveZero;
const XCFloat144_s * _Nonnull XCFloat144NegativeZero = &__XCFloat144NegativeZero;


const XCFloat144_s * _Nonnull XCFloat144PositiveInfinity = &__XCFloat144PositiveInfinity;
const XCFloat144_s * _Nonnull XCFloat144NegativeInfinity = &__XCFloat144NegativeInfinity;


/// 负无穷
bool_t XCFloat144IsNegativeInfinity(const XCFloat144_s * _Nonnull f) {
    abort();
    return false;
}

/// 正无穷
bool_t XCFloat144IsPositiveInfinity(const XCFloat144_s * _Nonnull f) {
    abort();
    return false;
}



int64_t XCFloat144GetSInt64(const XCFloat144_s * _Nonnull f);
uint64_t XCFloat144GetUInt64(const XCFloat144_s * _Nonnull f);


float64_t XCFloat144GetFloat64(const XCFloat144_s * _Nonnull f);
float32_t XCFloat144GetFloat32(const XCFloat144_s * _Nonnull f);

/// Nan 不是一个特值， 是两个区间， 无理数， 不能参与比较相等,  指数为最大值(全1)， 尾数非0
bool_t XCFloat144IsNotANumber(const XCFloat144_s * _Nonnull f) {
    return false;
}

///
bool_t XCFloat144IsNormal(const XCFloat144_s * _Nonnull f) {
    return false;
}

/// 是否是有限数字，如果参数是 NaN（非数字），或者是正、负无穷大的数，则返回 false。
bool_t XCFloat144IsFinite(const XCFloat144_s * _Nonnull f) {
    return false;
}

/// 是否是无穷 ,  指数为最大值(全1)， 尾数为0
bool_t XCFloat144IsInfinite(const XCFloat144_s * _Nonnull f) {
    return false;
}

