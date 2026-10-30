
#ifndef XONCore_h
#define XONCore_h

#include <stdlib.h>
#include <stdbool.h>

#define XONTypeLength 1

extern char * _Nonnull const XONErrorDomain;

typedef enum {
    XONWireTypeSimpleValue = 0,
    
    /// Type - Count - Value 9
    XONWireTypeString = 1,

    /// Type - Count - Value 9
    XONWireTypeData,

    /// Type - Count - Value[(offst, Item)] 9
    XONWireTypeMessage,

    /// Type - Count - Value[Item] 9
    XONWireTypeArray,
} XONWireType_e;

typedef enum {
    XONSimpleValueError = 0,
    XONSimpleValueNil = 1,
    
    XONSimpleValueBoolFalse = 2,
    /// Type - Value 2
    XONSimpleValueBoolTrue = 3,
    
    // Microsecond
    XONSimpleValueTimeInvalid = 4,
    XONSimpleValueTime0 = 5,
    XONSimpleValueTime1,
    XONSimpleValueTime2,
    XONSimpleValueTime3,
    XONSimpleValueTime4,
    XONSimpleValueTime5,
    XONSimpleValueTime6,
    XONSimpleValueTime7,
    XONSimpleValueTime8 = 13,
    
    XONSimpleValueUndefine14,

    XONSimpleValueNumberLarge = 15,
    XONSimpleValueNumberNAN = 16,
    XONSimpleValueNumberPositiveInfinity = 17,
    XONSimpleValueNumberNegativeInfinity = 18,
    XONSimpleValueNumberZero = 19,
    // number 12个 [20, 31]
    
    // number（sint128, uint128, float128） 最长只需要18字节
    // number 18个 [14, 31]
} XONSimpleValue_e;


typedef enum {
    XONErrorNone = 0,
    
    XONErrorContent = -1,
    XONErrorCount = -2,
    XONErrorNotEnough = -3,
    XONErrorNotSupport = -4,
    XONErrorArgumentError = -0x20,
    XONErrorDeepError = -0x21,

    
    XONErrorNotImplemented = -0xa,
    
        
    /// 非法编码
    XONErrorType = -0x6,
    XONErrorLayout = -0x7,

    XONErrorMessageFieldKeyOffset = -0x8,
    XONErrorNumberOutOfRange = -0x9,
    
    XONErrorTimeContent = -0x12,
    XONErrorNumberContent = -0x13,
    XONErrorMessageIndexOffset = -0x14,
    XONErrorStringContent = -0x15,
    XONErrorArrayContent = -0x16,
    XONErrorMessageContent = -0x17,
    XONErrorVarInt = -0x18,

    XONErrorFieldNotFound = -0x1a
} XONError_e;

typedef enum {
    XONNumberTypeNone = 0x0,
    XONNumberTypeSInt,
    XONNumberTypeUInt,
    XONNumberTypeFloat64,
} XONNumberType_e;

static inline double __XONDoubleNan(void) {
    uint64_t v = ((uint64_t)0x7ff8000000000000ULL);
    return *(double *)(&v);
}
static inline double __XONDoublePositiveInfinity(void) {
    uint64_t v = ((uint64_t)0x7ff0000000000000ULL);
    return *(double *)(&v);
}
static inline double __XONDoubleNegativeInfinity(void) {
    uint64_t v = ((uint64_t)0xfff0000000000000ULL);
    return *(double *)(&v);
}
static inline double __XONDoubleZero(void) {
    double v = 0.0;
    return v;
}

typedef struct {
    ssize_t type;
    union {
        int64_t s;
        uint64_t u;
        double f;
    } value;
} XONNumberValue_s;

typedef struct {
    ssize_t format;
    ssize_t length;
} XONNumberHeader_s;

typedef struct {
    int32_t exponent;
    uint32_t sign;
    uint64_t significandHigh;
    uint64_t significandLow;
} XONNumberNormalContent_s;


// microsecond
typedef int64_t XTimestamp;

static inline bool XTimestampIsInvalid(XTimestamp timestamp) {
    return timestamp == INT64_MAX;
}

static inline XTimestamp XTimestampInvalidDefault(void) {
    return INT64_MIN;
}

static inline XTimestamp XTimestampMin(void) {
    return INT64_MIN + 1;
}

static inline XTimestamp XTimestampMax(void) {
    return INT64_MAX;
}

static inline XTimestamp XTimestampDistantPast(void) {
    return INT64_MIN + 1;
}

static inline XTimestamp XTimestampDistantFuture(void) {
    return INT64_MAX;
}

static inline XTimestamp XTimestampZero(void) {
    return 0;
}

typedef struct {
    ssize_t format;
    ssize_t length;
} XTimestampHeader_s;

typedef struct {
    XONWireType_e type;
    unsigned int layout;
} XONValueHeader_s;

static inline XONValueHeader_s XONValueHeaderMake(void) {
    XONValueHeader_s h = { 0 };
    return h;
}

extern ssize_t XONHeaderMaxLength(void);

extern XONError_e XONDecodeHeader(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, XONValueHeader_s * _Nonnull header);
extern XONError_e XONDecodeNormalNumber(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, ssize_t len, XONNumberNormalContent_s * _Nonnull content);
extern XONError_e XONDecodeTime(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, ssize_t count, XTimestamp * _Nonnull time);
extern XONError_e XONDecodeCount(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, unsigned int layout, ssize_t * _Nonnull receiver);

extern XONError_e XONDecodeFieldKeyOffset(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, uint32_t * _Nonnull offset);

extern XONError_e XONNumberToFloat64(const XONNumberNormalContent_s * _Nonnull content, double * _Nonnull value);
extern XONError_e XONNumberToSInt64(const XONNumberNormalContent_s * _Nonnull content, int64_t * _Nonnull value);
extern XONError_e XONNumberToUInt64(const XONNumberNormalContent_s * _Nonnull content, uint64_t * _Nonnull value);

extern void test(void);
//extern XONError_e XONDecodeNumber64(const uint8_t * _Nonnull bytes, ssize_t capacity, ssize_t * _Nonnull location, ssize_t format, ssize_t count, XONNumberValue_s * _Nonnull number);


//#pragma mark - XONBuffer
//
////open var hasBytesAvailable: Bool { get }
////ssize_t (* _Nonnull read)(XONOuputBuffer_s * _Nonnull buffer, uint8_t * _Nonnull bytes, ssize_t length);
//
////open var hasSpaceAvailable: Bool { get }
////ssize_t (* _Nonnull write)(XONOuputBuffer_s * _Nonnull buffer, const uint8_t * _Nonnull bytes, ssize_t length);
//
//struct __XONBuffer;
//typedef struct __XONBuffer XONBuffer_s;
//struct __XONBuffer {
//    void * _Nonnull context;
//
//    // read
//    ssize_t (* _Nonnull write)(void * _Nonnull context, const void * _Nonnull bytes, ssize_t length);
//    ssize_t (* _Nonnull read)(void * _Nonnull context, void * _Nonnull bytes, ssize_t length);
//};
//
//#pragma mark - XONOuputBuffer
//
//struct __XONOuputBuffer;
//typedef struct __XONOuputBuffer XONOuputBuffer_s;
//struct __XONOuputBuffer {
//    void * _Nullable context;
//    uint8_t * _Nullable bytes;
//    ssize_t capacity;
//    ssize_t location;
//    // read
//    void (* _Nonnull write)(XONOuputBuffer_s * _Nonnull buffer, uint8_t * _Nonnull bytes, ssize_t length);
//    void (* _Nonnull fitSize)(XONOuputBuffer_s * _Nonnull buffer);
//    void (* _Nonnull deallocator)(XONOuputBuffer_s * _Nonnull buffer);
//};
//
//static inline void XONEncodeBufferReserveCapacity(XONEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity) {
//    buffer->reserveCapacity(buffer, minCapacity);
//}
//static inline void XONEncodeBufferFitSize(XONEncodeBuffer_s * _Nonnull buffer) {
//    buffer->fitSize(buffer);
//}
//static inline void XONEncodeBufferDeallocate(XONEncodeBuffer_s * _Nonnull buffer) {
//    buffer->deallocator(buffer);
//}
//
//// TODO: 预算长度
//extern void _XONEncodeBufferDefaultRealloc(XONEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity);
//extern void _XONEncodeBufferDefaultDealloc(XONEncodeBuffer_s * _Nonnull buffer);
//extern void _XONEncodeBufferDefaultFitSize(XONEncodeBuffer_s * _Nonnull buffer);
//
//static inline XONEncodeBuffer_s XONEncodeBufferMakeDefault(void) {
//    XONEncodeBuffer_s buffer = {
//        .context = NULL,
//        .bytes = NULL,
//        .capacity = 0,
//        .location = 0,
//        .reserveCapacity = _XONEncodeBufferDefaultRealloc,
//        .fitSize = _XONEncodeBufferDefaultFitSize,
//        .deallocator = _XONEncodeBufferDefaultDealloc,
//    };
//    return buffer;
//}

#pragma mark - EncodeBuffer

struct __XONEncodeBuffer;
typedef struct __XONEncodeBuffer XONEncodeBuffer_s;
struct __XONEncodeBuffer {
    void * _Nullable context;
    uint8_t * _Nullable bytes;
    ssize_t capacity;
    ssize_t location;
    void (* _Nonnull reserveCapacity)(XONEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity);
    void (* _Nonnull fitSize)(XONEncodeBuffer_s * _Nonnull buffer);
    void (* _Nonnull deallocator)(XONEncodeBuffer_s * _Nonnull buffer);
};

static inline void XONEncodeBufferReserveCapacity(XONEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity) {
    buffer->reserveCapacity(buffer, minCapacity);
}
static inline void XONEncodeBufferFitSize(XONEncodeBuffer_s * _Nonnull buffer) {
    buffer->fitSize(buffer);
}
static inline void XONEncodeBufferDeallocate(XONEncodeBuffer_s * _Nonnull buffer) {
    buffer->deallocator(buffer);
}

// TODO: 预算长度
extern void _XONEncodeBufferDefaultRealloc(XONEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity);
extern void _XONEncodeBufferDefaultDealloc(XONEncodeBuffer_s * _Nonnull buffer);
extern void _XONEncodeBufferDefaultFitSize(XONEncodeBuffer_s * _Nonnull buffer);

static inline XONEncodeBuffer_s XONEncodeBufferMakeDefault(void) {
    XONEncodeBuffer_s buffer = {
        .context = NULL,
        .bytes = NULL,
        .capacity = 0,
        .location = 0,
        .reserveCapacity = _XONEncodeBufferDefaultRealloc,
        .fitSize = _XONEncodeBufferDefaultFitSize,
        .deallocator = _XONEncodeBufferDefaultDealloc,
    };
    return buffer;
}

#pragma mark - Encode

extern XONError_e XONEncodeNull(XONEncodeBuffer_s * _Nonnull buffer);
extern XONError_e XONEncodeBool(XONEncodeBuffer_s * _Nonnull buffer, _Bool value);

extern XONError_e XONEncodeNumberUInt64(XONEncodeBuffer_s * _Nonnull buffer, uint64_t value);
extern XONError_e XONEncodeNumberSInt64(XONEncodeBuffer_s * _Nonnull buffer, int64_t value);
extern XONError_e XONEncodeNumberDouble(XONEncodeBuffer_s * _Nonnull buffer, double value);

extern XONError_e XONEncodeTime(XONEncodeBuffer_s * _Nonnull buffer, XTimestamp microsecond);

extern XONError_e XONEncodeFieldKeyOffset(XONEncodeBuffer_s * _Nonnull buffer, uint32_t offset);
extern XONError_e XONEncodeMessageHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count);
extern XONError_e XONEncodeArrayHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count);
extern XONError_e XONEncodeDataHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count);
extern XONError_e XONEncodeStringHeader(XONEncodeBuffer_s * _Nonnull buffer, ssize_t count);
extern XONError_e XONEncodeBody(XONEncodeBuffer_s * _Nonnull buffer, const void * _Nonnull data, ssize_t count);
extern XONError_e XONEncodeData(XONEncodeBuffer_s * _Nonnull buffer, const void * _Nullable data, ssize_t count);
extern XONError_e XONEncodeString(XONEncodeBuffer_s * _Nonnull buffer, const void * _Nullable cString, ssize_t count);

#endif /* XONCore_h */
