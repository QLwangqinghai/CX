

#ifndef XCoreBase_h
#define XCoreBase_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XTargetConditionals.h"
#include "XBaseType.h"
#include <stdatomic.h>

// >= 0 表示成功， 否则是错误码
typedef int32_t XResult32;

// 非0表示错误
typedef int32_t XResultCode32;

// 非0表示错误

#pragma mark - microsecond_t

/// microsecond_t 应该改名成microsecond_t

//微秒时间
typedef int64_t microsecond_t;

#define MICROSECOND_INVALID INT64_MIN
#define MICROSECOND_DISTANT_PAST (INT64_MIN + 1)
#define MICROSECOND_DISTANT_FUTURE INT64_MAX

// 单位是纳秒，
typedef uint64_t xdispatch_time_t;

/// nanosecond， 不是系统启动时间，从第一次访问这个api计时
extern xdispatch_time_t xdispatch_time_now(void);


//#define XDISPATCH_TIME_NOW (0ull)
#define XDISPATCH_TIME_FOREVER (~0ull)

#define XNSEC_PER_SEC 1000000000ull

/// UTC 时间
extern microsecond_t XMicrosecondNow(void);

extern microsecond_t XMicrosecondGetDistantFuture(void);
extern microsecond_t XMicrosecondGetDistantPast(void);
extern microsecond_t XMicrosecondGetInvalid(void);

extern struct timespec XMicrosecondToTimespec(microsecond_t time);
extern struct timeval XMicrosecondToTimeval(microsecond_t time);
extern microsecond_t XMicrosecondFromTimespec(struct timespec time);
extern microsecond_t XMicrosecondFromTimeval(struct timeval time);

extern microsecond_t XMicrosecondWithSecond(double sec);
extern double XMicrosecondGetSecond(microsecond_t ti);

#define MICROSECOND_NORMAL_MIN (MICROSECOND_DISTANT_PAST + 1)
#define MICROSECOND_NORMAL_MAX (MICROSECOND_DISTANT_FUTURE - 1)

#if CX_TARGET_OS_DARWIN || CX_TARGET_OS_LINUX || CX_TARGET_OS_ANDROID || CX_TARGET_OS_BSD
#define Float64Positive2ToThe64    0x1.0p+64L
#elif CX_TARGET_OS_WINDOWS
#define Float64Positive2ToThe64    18446744073709551616.0
#else
#error Unknown or unspecified DEPLOYMENT_TARGET
#endif

typedef int32_t XComparisonResult;

// < 0
extern const XComparisonResult XCompareLessThan;

// = 0
extern const XComparisonResult XCompareEqualTo;

// > 0
extern const XComparisonResult XCompareGreaterThan;

#pragma mark - uint8_t

static inline bool_t XByte2Equal(const XByte2 * _Nonnull lhs, const XByte2 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte2)) == 0;
}
static inline void XByte2ToBytes(const XByte2 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 2);
}
static inline void XByte2Reset(XByte2 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 2);
}


static inline bool_t XByte4Equal(const XByte4 * _Nonnull lhs, const XByte4 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte4)) == 0;
}
static inline void XByte4ToBytes(const XByte4 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 4);
}
static inline void XByte4Reset(XByte4 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 4);
}


static inline bool_t XByte8Equal(const XByte8 * _Nonnull lhs, const XByte8 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte8)) == 0;
}
static inline void XByte8ToBytes(const XByte8 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 8);
}
static inline void XByte8Reset(XByte8 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 8);
}


static inline bool_t XByte16Equal(const XByte16 * _Nonnull lhs, const XByte16 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte16)) == 0;
}
static inline bool_t XByte16EqualSwift(XByte16 lhs, XByte16 rhs) {
    return memcmp(lhs.content, rhs.content, 16) == 0;
}
static inline void XByte16ToBytes(const XByte16 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 16);
}
static inline void XByte16Reset(XByte16 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 16);
}

static inline bool_t XByte20Equal(const XByte20 * _Nonnull lhs, const XByte20 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte20)) == 0;
}
static inline void XByte20ToBytes(const XByte20 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 20);
}
static inline void XByte20Reset(XByte20 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 20);
}

static inline bool_t XByte28Equal(const XByte28 * _Nonnull lhs, const XByte28 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte28)) == 0;
}
static inline void XByte28ToBytes(const XByte28 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 28);
}
static inline void XByte28Reset(XByte28 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 28);
}

static inline bool_t XByte32Equal(const XByte32 * _Nonnull lhs, const XByte32 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte32)) == 0;
}
static inline void XByte32ToBytes(const XByte32 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 32);
}
static inline void XByte32Reset(XByte32 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 32);
}


static inline bool_t XByte48Equal(const XByte48 * _Nonnull lhs, const XByte48 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte48)) == 0;
}
static inline void XByte48ToBytes(const XByte48 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 48);
}
static inline void XByte48Reset(XByte48 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 48);
}


static inline bool_t XByte64Equal(const XByte64 * _Nonnull lhs, const XByte64 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte64)) == 0;
}
static inline bool_t XByte64EqualSwift(XByte64 lhs, XByte64 rhs) {
    return memcmp(lhs.content, rhs.content, 64) == 0;
}
static inline void XByte64ToBytes(const XByte64 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 64);
}
static inline void XByte64Reset(XByte64 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 64);
}

typedef struct {
    uint8_t content[128];
} XByte128;
static inline bool_t XByte128Equal(const XByte128 * _Nonnull lhs, const XByte128 * _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return memcmp(lhs, rhs, sizeof(XByte128)) == 0;
}
static inline void XByte128ToBytes(const XByte128 * _Nonnull bytes, uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(buffer, bytes->content, 128);
}
static inline void XByte128Reset(XByte128 * _Nonnull bytes, const uint8_t * _Nonnull buffer) {
    assert(bytes);
    memcpy(bytes->content, buffer, 128);
}

typedef struct {
    size_t count;
    const uint8_t * _Nullable bytes;
} XConstByteVector;

typedef struct {
    size_t count;
    uint8_t * _Nullable bytes;
} XByteVector;

static inline XByteVector XByteVectorMake(uint8_t * _Nullable bytes, size_t count) {
    if (count > 0) {
        XAssert(bytes, "");
    }
    XByteVector result = {
        .count = count,
        .bytes = bytes
    };
    return result;
}

typedef struct {
    size_t capacity: 32;
    size_t count: 32;
    uint8_t * _Nullable payload;
} XBuffer;

static inline XBuffer XBufferMake(size_t capacity, size_t count, uint8_t * _Nullable payload) {
    if (capacity > 0) {
        XAssert(payload, "");
    }
    XAssert(capacity <= UINT32_MAX, "");
    XAssert(count <= capacity, "");
    XBuffer result = {
        .capacity = capacity,
        .count = count,
        .payload = payload
    };
    return result;
}

static inline size_t XBufferGetRemain(const XBuffer * _Nonnull buffer) {
    XAssert(buffer, "");
    return buffer->capacity - buffer->count;
}

static inline void XBufferSetCount(XBuffer * _Nonnull buffer, size_t count) {
    XAssert(buffer, "");
    XAssert(buffer->capacity >= count, "");
    buffer->count = count;
}

typedef struct {
    size_t baseIndex;
    size_t capacity: 32;
    size_t count: 32;
    uint8_t * _Nullable payload;
} XBufferSlice;

static inline XBufferSlice XBufferSliceMake(size_t baseIndex, size_t capacity, size_t count, uint8_t * _Nullable payload) {
    if (capacity > 0) {
        XAssert(payload, "");
    }
    XAssert(capacity <= UINT32_MAX, "");
    XAssert(baseIndex <= SIZE_MAX - count, "");
    XAssert(count <= capacity, "");
    
    XBufferSlice result = {
        .capacity = capacity,
        .baseIndex = baseIndex,
        .count = count,
        .payload = payload,
    };
    return result;
}


#pragma mark - XUtf8String_s

typedef struct __XUtf8String {
    /// length, not unicodeLength
    size_t length;
    const char * _Nonnull content;
} XUtf8String_s;

// Name 不要带 ""
#define XUtf8StringMake(Name) {\
    .length = sizeof(#Name) - 1,\
    .content = #Name,\
}

#pragma mark - ElementType

typedef struct __XElementType {
    const char * _Nonnull name;
    size_t size;// size=0 意味着是动态长度
} XSElementType;
typedef const XSElementType * XTElementType;

struct __XSliceListElement;
typedef struct __XSliceListElement XSliceListElement_s;

struct __XSliceListElement {
    XPtr _Nullable owner;
    XSliceListElement_s * _Nullable prev;
    XSliceListElement_s * _Nullable next;
    size_t offset: 32;// 跳过多少个元素， range(offset, count) 是有效数据区，offset + count <= capacity
    size_t count: 32;
    size_t capacity: 32;
    size_t itemSize: 32;
    uint8_t payload[0];// size = itemSize * capacity + sizeof(XSliceListElement_s)
};

static inline bool_t XSliceListElementIsFull(XSliceListElement_s * _Nonnull element) {
    return element->count == element->capacity;
}
static inline bool_t XSliceListElementIsEmpty(XSliceListElement_s * _Nonnull element) {
    return element->count == 0;
}
static inline void XSliceListElementAppendItem(XSliceListElement_s * _Nonnull element, XPtr _Nonnull entity) {
    XAssert(element->count < element->capacity, "");
    size_t location = (element->offset + element->count) % element->capacity;
    element->count += 1;
    XPtr p = (XPtr)(element->payload + location * element->itemSize);;
    memcpy(p, entity, element->itemSize);
}

static inline XPtr _Nonnull XSliceListElementGetItem(const XSliceListElement_s * _Nonnull element, size_t index) {
    XAssert(index < element->count, "");
    size_t location = (element->offset + index) % element->capacity;
    return (XPtr)(element->payload + location * element->itemSize);
}

typedef struct __XSliceList {
    XSliceListElement_s * _Nullable head;
    XSliceListElement_s * _Nullable tail;
    size_t itemSize;
} XSliceList_s;

void XSliceListElementInit(XSliceListElement_s * _Nonnull element, size_t capacity, size_t itemSize);


XSliceListElement_s * _Nonnull XSliceListElementCreate(size_t itemSize, size_t capacity);

void XSliceListElementReset(XSliceListElement_s * _Nonnull element);

void XSliceListElementDestroy(XSliceListElement_s * _Nonnull element);

void XSliceListInit(XSliceList_s * _Nonnull queue, size_t itemSize);

void XSliceListAppendSlice(XSliceList_s * _Nonnull queue, XSliceListElement_s * _Nonnull element);

void XSliceListPrependSlice(XSliceList_s * _Nonnull queue, XSliceListElement_s * _Nonnull element);

XSliceListElement_s *_Nullable XSliceListRemoveFirstSlice(XSliceList_s * _Nonnull queue);
XSliceListElement_s *_Nullable XSliceListRemoveLastSlice(XSliceList_s * _Nonnull queue);


extern void XPrint(FILE * __restrict _Nonnull stream, const void * __restrict _Nonnull ptr, size_t size);

extern void XLog(const char *__restrict _Nonnull format, ...);
extern void XLogBegin(const char *__restrict _Nonnull format, ...);
extern void XLogAppend(const char *__restrict _Nonnull format, ...);
extern void XLogFinish(const char *__restrict _Nonnull format, ...);


typedef enum {
    XByteEncodeOptionNone = 0,
    XByteEncodeOptionToUppercase = 0x1,//默认小写，有该选项时大写
} XByteEncodeOption_es;

typedef enum {
    XByteDecodeOptionNone = 0,
    XByteEncodeOptionIgnoreUnknownCharacters = 0x1,//忽略不认识的字符
} XByteDecodeOption_es;

extern ssize_t XByteEncodeToHexString(const uint8_t * _Nonnull bytes, size_t byteLength, char * _Nonnull buffer, size_t capacity, uint32_t options);
extern ssize_t XByteDecodeFromHexString(uint8_t * _Nonnull bytes, size_t capacity, const char * _Nonnull str, uint32_t options);



typedef struct {
    size_t location;
    size_t length;
    size_t unicodeCount;
} XStringUtf8Layout_s;

static inline XStringUtf8Layout_s XStringUtf8LayoutMake(size_t location, size_t length, size_t unicodeCount) {
    XStringUtf8Layout_s result = {
        .location = location,
        .length = length,
        .unicodeCount = unicodeCount,
    };
    return result;
}

#define _XStringUtf8BomLength 3

/// 发生错误时 errorIndex != XIndexNotFound
extern XStringUtf8Layout_s _XUtf8StringLayoutMakeWithBytes(const uint8_t * _Nonnull bytes, size_t length);
extern XStringUtf8Layout_s _XUtf8StringLayoutMakeWithBytes2(const uint8_t * _Nonnull bytes, size_t length);
extern XStringUtf8Layout_s _XUtf8StringLayoutMakeWithBytes3(const uint8_t * _Nonnull bytes, size_t length);

/// 发生错误时 errorIndex != XIndexNotFound
extern XStringUtf8Layout_s _XUtf8StringLayoutMakeWithCString(const char * _Nonnull str);

extern XIndex _XScanUtf8Bom(const uint8_t * _Nonnull bytes, size_t length);


#pragma mark - Basic

extern const uint8_t XBase64Table[64];
extern const uint8_t XBase64Spacing;
// normal:[0, 63] spacing:64 error:255

// 排序 从小到大， 保证 data 排序 和 XUrlBase64编码排序规则一致
extern const uint8_t XUrlBase64Table[64];
extern const uint8_t XUrlBase64Spacing;
extern uint8_t XUrlBase64Decode(uint32_t c);

//abcdefghjkmnprstuvwxyz0123456789（移除了o、i、l、q )
extern const uint8_t XBase32Table[32];
extern const uint8_t XHexTable[16];
extern uint8_t XBase64Decode(uint32_t c);


#if CX_TARGET_OS_DARWIN

static inline int tm_gmtoff(struct tm * _Nonnull t) {
    return (int)t->tm_gmtoff;
}
static inline const char * _Nullable tm_zone(struct tm * _Nonnull t) {
    return t->tm_zone;
}

#else

#ifdef __USE_BSD
static inline int tm_gmtoff(struct tm * _Nonnull t) {
    return t->tm_gmtoff;
}
static inline const char * _Nullable tm_zone(struct tm * _Nonnull t) {
    return t->tm_zone;
}
#else
static inline int tm_gmtoff(struct tm * _Nonnull t) {
    return t->__tm_gmtoff;
}
static inline const char * _Nullable tm_zone(struct tm * _Nonnull t) {
    return t->__tm_zone;
}
#endif

#endif

#pragma mark - crc

extern void XCrc16Init(uint16_t * _Nonnull context);
extern void XCrc16Compress(uint16_t * _Nonnull context, const unsigned char * _Nullable buf, uint32_t size);
extern void XCrc16Final(uint16_t * _Nonnull context);

extern void XCrc32Init(uint32_t * _Nonnull context);
extern void XCrc32Compress(uint32_t * _Nonnull context, const unsigned char * _Nullable buf, uint32_t size);
extern void XCrc32Final(uint32_t * _Nonnull context);

#pragma mark - XBuffer

typedef struct {
    ssize_t info;
    ssize_t count;
    ssize_t length;
    ssize_t capacity;
    uint8_t payload[0];
} XBuffer_s;

extern XBuffer_s * _Nonnull XBufferCreate(ssize_t info, ssize_t minCapacity);
extern void XBufferDestroy(XBuffer_s * _Nonnull buffer);
extern XBuffer_s * _Nonnull XBufferRealloc(XBuffer_s * _Nonnull buffer, ssize_t minCapacity);

#pragma mark - XEncodeBuffer

struct __XEncodeBuffer;
typedef struct __XEncodeBuffer XEncodeBuffer_s;
struct __XEncodeBuffer {
    void * _Nullable context;
    uint8_t * _Nullable bytes;
    ssize_t capacity;
    ssize_t location;
    
    // replace
    // append
    // finish
    
    void (* _Nonnull reserveSize)(XEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity);
    void (* _Nonnull fitSize)(XEncodeBuffer_s * _Nonnull buffer);
    void (* _Nonnull deallocator)(XEncodeBuffer_s * _Nonnull buffer);
    ssize_t error;
};

static inline void XEncodeBufferReserveSize(XEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity) {
    buffer->reserveSize(buffer, minCapacity);
}
static inline void XEncodeBufferFitSize(XEncodeBuffer_s * _Nonnull buffer) {
    buffer->fitSize(buffer);
}
static inline void XEncodeBufferDeinit(XEncodeBuffer_s * _Nonnull buffer) {
    buffer->deallocator(buffer);
    bzero(buffer, sizeof(XEncodeBuffer_s));
}

extern void _XEncodeBufferDefaultRealloc(XEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity);
extern void _XEncodeBufferDefaultDealloc(XEncodeBuffer_s * _Nonnull buffer);
extern void _XEncodeBufferDefaultFitSize(XEncodeBuffer_s * _Nonnull buffer);

static inline XEncodeBuffer_s XEncodeBufferMakeDefault(void) {
    XEncodeBuffer_s buffer = {
        .context = NULL,
        .bytes = NULL,
        .capacity = 0,
        .location = 0,
        .reserveSize = _XEncodeBufferDefaultRealloc,
        .fitSize = _XEncodeBufferDefaultFitSize,
        .deallocator = _XEncodeBufferDefaultDealloc,
        .error = 0,
    };
    return buffer;
}


#pragma mark - XDecodeBuffer

struct __XDecodeBuffer;
typedef struct __XDecodeBuffer XDecodeBuffer_s;
struct __XDecodeBuffer {
    void * _Nullable context;
    const uint8_t * _Nonnull bytes;
    ssize_t capacity;
    ssize_t location;
    void (* _Nullable deallocator)(void * _Nullable context, const uint8_t * _Nonnull bytes, ssize_t length);
    ssize_t error;
};

static inline void XDecodeBufferInit(XDecodeBuffer_s * _Nonnull buffer, const uint8_t * _Nonnull bytes, ssize_t length, void * _Nullable context, void (* _Nullable deallocator)(void * _Nullable context, const uint8_t * _Nonnull bytes, ssize_t length), ssize_t location) {
    XAssert(length >= 0, "");
    XAssert(location >= 0, "");
    if (length > 0) {
        XAssert(bytes, "");
    }
    buffer->context = context;
    buffer->bytes = bytes;
    buffer->capacity = length;
    buffer->location = location;
    buffer->deallocator = deallocator;
    buffer->error = 0;
}


static inline XDecodeBuffer_s XDecodeBufferMakeDefault(void * _Nullable context, const uint8_t * _Nonnull bytes, ssize_t length) {
    XAssert(length >= 0, "");
    XDecodeBuffer_s buffer = {
        .context = context,
        .bytes = bytes,
        .capacity = length,
        .location = 0,
        .deallocator = NULL,
        .error = 0,
    };
    return buffer;
}

static inline void XDecodeBufferDeinit(XDecodeBuffer_s * _Nonnull buffer) {
    if (buffer->deallocator) {
        buffer->deallocator(buffer->context, buffer->bytes, buffer->capacity);
    }
    bzero(buffer, sizeof(XDecodeBuffer_s));
}

/// require: buffer size >= 4
static inline int XUnicodeToUtf8(uint32_t unic, uint8_t * _Nonnull buffer) {
   if (unic <= 0x0000007F) {
       *buffer = (uint8_t)(unic & 0x7F);
       return 1;
   } else if (unic >= 0x00000080 && unic <= 0x000007FF) {
       // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
       *(buffer+1) = (uint8_t)(unic & 0x3F) | 0x80;
       *buffer     = (uint8_t)((unic >> 6) & 0x1F) | 0xC0;
       return 2;
   } else if ( unic >= 0x00000800 && unic <= 0x0000FFFF ) {
       // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
       *(buffer+2) = (uint8_t)(unic & 0x3F) | 0x80;
       *(buffer+1) = (uint8_t)((unic >>  6) & 0x3F) | 0x80;
       *buffer     = (uint8_t)((unic >> 12) & 0x0F) | 0xE0;
       return 3;
   } else if ( unic >= 0x00010000 && unic <= 0x001FFFFF ) {
       // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
       *(buffer+3) = (uint8_t)(unic & 0x3F) | 0x80;
       *(buffer+2) = (uint8_t)((unic >>  6) & 0x3F) | 0x80;
       *(buffer+1) = (uint8_t)((unic >> 12) & 0x3F) | 0x80;
       *buffer     = (uint8_t)((unic >> 18) & 0x07) | 0xF0;
       return 4;
   } else {
       return 0;
   }
}

#pragma mark - memcmp

extern XComparisonResult XMemoryCompare(const XPtr _Nonnull lhs, const XPtr _Nonnull rhs, size_t size);

#pragma mark - string

// 获取utf8 字符串的range
extern XRange_s XMemoryGetRangeOfNonbomUtfString(const uint8_t * _Nonnull bytes, size_t length);

#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XCoreBase_h */
