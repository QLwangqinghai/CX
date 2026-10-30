
#ifndef XRuntimeInternal_h
#define XRuntimeInternal_h

#if defined(__cplusplus)
extern "C" {
#endif

#if __has_include(<XCore/XRuntime.h>)
#include <XCore/XRuntime.h>
#else
#include "XRuntime.h"
#endif

#if __has_include(<XCore/XHash.h>)
#include <XCore/XHash.h>
#else
#include "XHash.h"
#endif

#if __has_include(<XCore/XProcess.h>)
#include <XCore/XProcess.h>
#else
#include "XProcess.h"
#endif

#if __has_include(<XCore/XDeque.h>)
#include <XCore/XDeque.h>
#else
#include "XDeque.h"
#endif

#include "XAtomicInternal.h"
#include "XObjectInternal.h"

// number date

// linux 内存分配算法 https://blog.csdn.net/weixin_45639450/article/details/121677527   https://blog.csdn.net/qq_40586164/article/details/115190494

// 64位下 分配块大小16

/*
 RC 中放 zoneInfo, 内存字节数
 // width: 1 ~ 16, padding: 1 ~ 8; hasSign: ; float or int
 // Date(32: 24B; 64: 32b;) Number(32: 16B/24B; 64: 24B/32B) Date(32: 16B/24B; 64: 24B) String(32: 8B~128B; 64: 16B~128B) Data(32: 12B~128B; 64: 24B~128B~...)
 // 内存池: 0， 对象进入内存池之前要清0
  [16(Date??, LargeString), 24(Date, Number, String), 32(Date, Number, Weak, String), 40、48、56(Data, String), 64(Data, String), static]
 16
 24
 32
 40
 48
 56
 64
 72
 80
 96
 112
 128
 
 static
 */

/*
 x位 _xinfo
 1位 weakFlag
 6位 typeId
 */

/*
 生命周期函数
 成员变量表
 静态方法表
 动态方法表
 类方法表
 */

//#include <mach/mach_vm.h>
//
//static inline void adfaewrw() {
//    mach_vm_allocate(<#vm_map_t target#>, <#mach_vm_address_t *address#>, <#mach_vm_size_t size#>, <#int flags#>)
//    int alloc_flags = VM_FLAGS_ANYWHERE | VM_MAKE_TAG(VM_MEMORY_MALLOC);
//
//}

#pragma mark - XWeakStorage

struct ___XWeakStorage;
typedef struct ___XWeakStorage _XWeakStorage_o;

// closure callback 模式下必须需要weakstorage的支持
// 只有特定的类才能支持weakstorage
// 特定的类支持weakstorage，XObjectBase_o _runtime 部分counter部分数据 类自行处理，isa部分不允许修改
struct ___XWeakStorage {
    XObjectBase_o _runtime;
    _Atomic(size_fast_t) _originalXinfoe;
    _Atomic(uintptr_t) original;
};

#pragma mark - Tagged

// 最低位放1是为了让人一眼看出来这不是个对象地址， Type非0且放高位是为了让高位有数据，做安全校验，armv9高16位有内存校验, 可以容纳的数据有 (sizeof(void *) * 8 - 4) bits
// 7 * 8 = 56, 9 * 6=54; 60/9=
/*
 ScopeA: 3bit，3个空余 当值为 X_TaggedObjectTypeBits_ScopeATypeReadB时 需要读scopeB
 ScopeB: 5bit，30个空余 必须设置为非0， 0表示错误， 当值为 X_TaggedObjectTypeBits_ScopeBTypeReadC时 需要读scopeC
 ScopeC: 6bit，63个空余
 */
// payload: 60 55 49

#define X_TaggedObjectFlag SIZE_C(0x1)

// ScopeA一定需要3位，用来拓展 IndexPath IndexSet Range等

#define X_TaggedObject_ScopeATypeReadB SIZE_C(0x0)
#define X_TaggedObject_ScopeBTypeReadC SIZE_C(31)

#define X_TaggedObjectTypeBits_ScopeATypeReadB (X_TaggedObject_ScopeATypeReadB << X_TaggedObject_ScopeATypeShift)
#define X_TaggedObjectTypeBits_ScopeBTypeReadC (X_TaggedObject_ScopeBTypeReadC << X_TaggedObject_ScopeBTypeShift)


#if CX_TARGET_RT_64_BIT
#define X_TaggedObject_ScopeATypeMask SIZE_C(0xE000000000000000)
#define X_TaggedObject_ScopeATypeShift SIZE_C(61)
#define X_TaggedObject_ScopeBTypeMask SIZE_C(0x1F00000000000000)
#define X_TaggedObject_ScopeBTypeShift SIZE_C(56)
#define X_TaggedObject_ScopeCTypeMask SIZE_C(0xFC000000000000)
#define X_TaggedObject_ScopeCTypeShift SIZE_C(50)
#define X_TaggedObjectTypeBits_XNumber SIZE_C(0x2000000000000000)
#define X_TaggedObjectTypeBits_XDate SIZE_C(0x4000000000000000)
#define X_TaggedObjectTypeBits_XData SIZE_C(0x6000000000000000)
#define X_TaggedObjectTypeBits_XString SIZE_C(0x8000000000000000)
#define X_BUILD_TaggedObjectCScopeTypeXBool SIZE_C(0)

#define X_TaggedObjectScopeAContentMask SIZE_C(0x1FFFFFFFFFFFFFFE)
#define X_TaggedObjectScopeAContentBitCount SIZE_C(60)
#define X_TaggedObjectScopeBContentMask SIZE_C(0xFFFFFFFFFFFFFE)
#define X_TaggedObjectScopeBContentBitCount SIZE_C(55)
#define X_TaggedObjectScopeCContentMask SIZE_C(0x3FFFFFFFFFFFE)
#define X_TaggedObjectScopeCContentBitCount SIZE_C(49)

#else
#define X_TaggedObject_ScopeATypeMask SIZE_C(0xE0000000)
#define X_TaggedObject_ScopeATypeShift SIZE_C(29)
#define X_TaggedObject_ScopeBTypeMask SIZE_C(0x1F000000)
#define X_TaggedObject_ScopeBTypeShift SIZE_C(24)
#define X_TaggedObject_ScopeCTypeMask SIZE_C(0xFC0000)
#define X_TaggedObject_ScopeCTypeShift SIZE_C(18)
#define X_TaggedObjectTypeBits_XNumber SIZE_C(0x20000000)
#define X_TaggedObjectTypeBits_XDate SIZE_C(0x40000000)
#define X_TaggedObjectTypeBits_XData SIZE_C(0x60000000)
#define X_TaggedObjectTypeBits_XString SIZE_C(0x80000000)
#define X_BUILD_TaggedObjectCScopeTypeXBool SIZE_C(0)

#define X_TaggedObjectScopeAContentMask SIZE_C(0x1FFFFFFE)
#define X_TaggedObjectScopeAContentBitCount SIZE_C(28)
#define X_TaggedObjectScopeBContentMask SIZE_C(0xFFFFFE)
#define X_TaggedObjectScopeBContentBitCount SIZE_C(23)
#define X_TaggedObjectScopeCContentMask SIZE_C(0x3FFFE)
#define X_TaggedObjectScopeCContentBitCount SIZE_C(17)

#endif

#if CX_TARGET_RT_64_BIT
#define X_TaggedData_ByteMask SIZE_C(0xFFFFFFFFFFFFFF)
#define X_TaggedString_ByteMask SIZE_C(0xFFFFFFFFFFFFFF)
#define X_BUILD_TaggedData_ByteBitCount SIZE_C(56)
#define X_BUILD_TaggedString_ByteBitCount SIZE_C(56)
#define X_BUILD_TaggedData_CountMax SIZE_C(7)
#define X_BUILD_TaggedString_CountMax SIZE_C(7)
#else
#define X_TaggedData_ByteMask SIZE_C(0xFFFFFF)
#define X_TaggedString_ByteMask SIZE_C(0xFFFFFF)
#define X_BUILD_TaggedData_ByteBitCount SIZE_C(24)
#define X_BUILD_TaggedString_ByteBitCount SIZE_C(24)
#define X_BUILD_TaggedData_CountMax SIZE_C(3)
#define X_BUILD_TaggedString_CountMax SIZE_C(3)
#endif

#define X_BUILD_TaggedObjectContentShift SIZE_C(0x1)

// 4个id， 0：默认， using malloc、free; 1: 固定长度、固定数量内存池；2：固定长度内存池， 总量会增加；3: 变长 4 5 6 7
typedef XComparisonResult (*XObjectCompare_f)(XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);


#if CX_TARGET_RT_64_BIT
    #pragma pack(push, 8)
#else
    #pragma pack(push, 4)
#endif

/*
 TaggedValue 布局:
 内存布局： 最低位1
 32[27, 29]/ 64[61, 63]: 高3位type， type放高位是为了让高位有数据，让指针可阅读性降低，armv9高16位有内存校验
 32[1, 26]/ 64[1, 60]: 内容
 */


#pragma mark - XObject

typedef struct {
    XObjectBase_o _runtime;
    uint8_t content[0];
} _XObject_o;

#pragma mark - XValue

typedef struct {
    XObjectBase_o _runtime;
    _Atomic(size_fast_t) _hashCode;
    /// type 必须是个静态数据，两个_XValue 判断 equal 时， 会判断 lhs->type == rhs->type, 是个地址比较
    const XValueContentType_s * _Nonnull type;
    uint8_t bytes[0];
} _XValue_o;

#pragma mark - XNumber size[sizeof(size_t) * 2, or: ]

typedef struct {
    XObjectBase_o _runtime;
    uint8_t bits[0];
} _XNumber_o;

#pragma mark - XByteBuffer

typedef struct {
    size_t length;
    uint8_t bytes[0];
} XByteBuffer_s;

#pragma mark - XDateRef

typedef struct {
    XObjectBase_o _runtime;
    microsecond_t microsecond;
} _XDate_o;

#pragma mark - XDataRef

typedef struct {
    XObjectBase_o _runtime;
    // 必须满足 utf8String 长度与Data长度一致， 必须无损转化时， data 才能持有这个 string
    uint8_t content[0];
} _XData_o;

typedef struct {
    _Atomic(size_fast_t) hashCode;
    size_t length;
    uint8_t bytes[0];
} _XDataByteContent_s;

//typedef struct {
//    XObjectBase_o _runtime;
//    _XDataByteContent_s content;
//} XDataBuffer_s;

struct __XDataBridgeString;
typedef struct __XDataBridgeString _XDataBridgeString_s;

typedef struct {
    size_t length;
    const uint8_t * _Nonnull bytes;
    size_t hashCode;
    size_t _nanoBytes;
} _XDataUnpacked_t;

#define _XDataLayoutByte 1
#define _XDataLayoutBridgeString 2

// 这个太危险了， 无法防止被修改
//#define _XDataLayoutBridgeByte 4

#pragma mark - XString

typedef struct {
    XObjectBase_o _runtime;
    uint8_t content[0];
} _XString_o;

struct __XDataBridgeString {
    _XString_o * _Nonnull string;
};

// XString 需要支持快速hash，不桥接到data， 由于string的不可变性，不允许桥接到char *
#define _XStringLayoutSmall 1
#define _XStringLayoutLarge 2

typedef struct {
    // 可能中途发生数据改变的数据要放到靠近header的部分
    _Atomic(size_fast_t) hashCode;
    size_t unicodeCount: SIZE_HALF_BITS_COUNT;
    size_t length: SIZE_HALF_BITS_COUNT;
    uint8_t bytes[0];
} _XStringInlineContent_s;

typedef struct {
    // 可能中途发生数据改变的数据要放到靠近header的部分
    _Atomic(size_fast_t) hashCode;
    size_t unicodeCount;
    size_t length;
    uint8_t bytes[0];
} _XStringLargeContent;

typedef struct {
    size_t length;
    const uint8_t * _Nonnull bytes;
    size_t hashCode;
    size_t _nanoBytes;
} _XStringUnpacked_t;

#pragma mark - XMessageRef

typedef struct {
    XObjectBase_o _runtime;
    _Atomic(size_fast_t) _hashCode;
    const int32_t count;
    const uint32_t stepLength;
    
    // uint32_t buckets[count];
    // uint32_t keys[count];
    // XObjectRef values[count];

    /// bucket + 二分查找-

    // bucketIndex = key / bucketCapacity; 异常bucketIndex>=bucketCount
    uint8_t payload[0];
} _XImmutableMessage_o;

typedef struct {
    // 装的是key的index
    int32_t * _Nonnull buckets;
    uint32_t * _Nonnull keys;
    XObjectRef _Nullable * _Nonnull values;
} _XImmutableMessagePayload_s;

static inline _XImmutableMessagePayload_s _XImmutableMessageGetPayload(_XImmutableMessage_o * _Nonnull message) {
    _XImmutableMessagePayload_s layout = {};
    uint8_t * payload = message->payload;
    layout.buckets = (int32_t *)payload;
    layout.keys = (uint32_t *)(layout.buckets + message->count);
    layout.values = (XObjectRef *)(layout.keys + message->count);
    return layout;
}

typedef struct {
    XObjectBase_o _runtime;
    XDeque_s storage;
    
    /// 二分查找
} _XMutableMessage_o;

typedef struct {
    XObjectBase_o _runtime;
} _XMessage_o;

#pragma mark - XArray

typedef struct {
    XObjectBase_o _runtime;
    uint8_t content[0];
} _XArray_o;

typedef struct {
    XObjectBase_o _runtime;
    _Atomic(size_fast_t) _hashCode;
    const ssize_t count;
    const XArrayElement_s items[0];
} _XImmutableArray_o;

typedef struct {
    XObjectBase_o _runtime;
    XDeque_s deque;
} _XMutableArray_o;

static inline XDeque_s * _Nonnull _XMutableArrayGetDeque(_XMutableArray_o * _Nonnull array) {
    return &(array->deque);
}
#pragma pack(pop)

#pragma mark - runtime

///  强制转换，转换不成功会abort()
extern XObjectRef _Nonnull _XHeapObjectAs(XObjectRef _Nonnull ref, XClassRef _Nonnull cls, const char * _Nonnull func);

XClassRef _Nonnull __XTaggedObjectGetClass(uintptr_t ref);

static inline size_t __XHeapObjectGetLayout(XObjectRef _Nonnull obj) {
    size_fast_t _xinfo = atomic_load(&(((XObjectBase_o *)obj)->_xinfo));
    XAssert(XInfo_MarkNotXObject != (_xinfo & XInfo_MarkMask), "");
    return (_xinfo & XInfo_LayoutMask) >> XInfo_LayoutShift;
}

#pragma mark - XHasher

typedef struct __XHasher {
    XHasherCombineBytes_f _Nonnull combine;
    XHasherFinalize_f _Nonnull finalize;
    uint8_t context[0];
} _XHasher;


#pragma mark - ------------------------------------------------------------------------------------

typedef int XIsTaggedObjectResultCode;
#define XIsTaggedObjectResultTrue 1


static inline XObjectRef _Nonnull __XTaggedEncode(uintptr_t v) {
    
    // do encode
    return (XObjectRef)v;
}
static inline uintptr_t __XTaggedDecode(uintptr_t ref) {
    uintptr_t v = (uintptr_t)ref; // decode step

    return v;
}

/// 60/28bit content
static inline XObjectRef _Nonnull __XTaggedObjectEncodeScopeA(size_t taggedType, size_t content, const char * _Nonnull func) {
    XAssert(0 == (taggedType & (~X_TaggedObject_ScopeATypeMask)), "type error");
    XAssert(content <= (SIZE_MAX >> (SIZE_BITS_COUNT - X_TaggedObjectScopeAContentBitCount)), "content error");
    size_t bits = taggedType | (content << X_BUILD_TaggedObjectContentShift) | X_TaggedObjectFlag;
    return __XTaggedEncode(bits);
}

//  60/28bit content
static inline size_t __XTaggedObjectDecodeContentScopeA(uintptr_t ref, size_t taggedType, const char * _Nonnull func) {
    XAssert((ref & X_TaggedObjectFlag) == X_TaggedObjectFlag, "");
    uintptr_t bits = __XTaggedDecode(ref);
    XAssert(taggedType == (bits & X_TaggedObject_ScopeATypeMask), "type error");
    return (bits & X_TaggedObjectScopeAContentMask) >> X_BUILD_TaggedObjectContentShift;
}

/// 55/23bit content
static inline XObjectRef _Nonnull __XTaggedObjectEncodeScopeB(size_t taggedType, size_t content, const char * _Nonnull func) {
    XAssert(0 == (taggedType & (~X_TaggedObject_ScopeBTypeMask)), "type error");
    // bscope type 不允许为0
    XAssert(taggedType != 0, "");
    XAssert(content <= (SIZE_MAX >> (SIZE_BITS_COUNT - X_TaggedObjectScopeBContentBitCount)), "content error");
    size_t bits = taggedType | X_TaggedObjectTypeBits_ScopeATypeReadB | (content << X_BUILD_TaggedObjectContentShift) | X_TaggedObjectFlag;
    return __XTaggedEncode(bits);
}

/// 55/23bit content
static inline size_t __XTaggedObjectDecodeContentScopeB(uintptr_t ref, size_t taggedType, const char * _Nonnull func) {
    XAssert((ref & X_TaggedObjectFlag) == X_TaggedObjectFlag, "");
    uintptr_t bits = __XTaggedDecode(ref);
    XAssert(X_TaggedObjectTypeBits_ScopeATypeReadB == (bits & X_TaggedObject_ScopeATypeMask), "type error");
    XAssert(taggedType == (bits & X_TaggedObject_ScopeBTypeMask), "type error");
    return (bits & X_TaggedObjectScopeBContentMask) >> X_BUILD_TaggedObjectContentShift;
}

/// 48/16bit content
static inline XObjectRef _Nonnull __XTaggedObjectEncodeScopeC(size_t taggedType, size_t content, const char * _Nonnull func) {
    XAssert(0 == (taggedType & (~X_TaggedObject_ScopeCTypeMask)), "type error");
    XAssert(content <= (SIZE_MAX >> (SIZE_BITS_COUNT - X_TaggedObjectScopeCContentBitCount)), "content error");
    size_t bits = taggedType | X_TaggedObjectTypeBits_ScopeATypeReadB | X_TaggedObjectTypeBits_ScopeBTypeReadC | (content << X_BUILD_TaggedObjectContentShift) | X_TaggedObjectFlag;
    return __XTaggedEncode(bits);
}

/// 48/16bit content
static inline size_t __XTaggedObjectDecodeContentScopeC(uintptr_t ref, size_t taggedType, const char * _Nonnull func) {
    XAssert((ref & X_TaggedObjectFlag) == X_TaggedObjectFlag, "");
    uintptr_t bits = __XTaggedDecode(ref);
    XAssert(X_TaggedObjectTypeBits_ScopeATypeReadB == (bits & X_TaggedObject_ScopeATypeMask), "type error");
    XAssert(X_TaggedObjectTypeBits_ScopeBTypeReadC == (bits & X_TaggedObject_ScopeBTypeMask), "type error");

    XAssert(taggedType == (bits & X_TaggedObject_ScopeCTypeMask), "type error");
    return (bits & X_TaggedObjectScopeCContentMask) >> X_BUILD_TaggedObjectContentShift;
}

static inline XClassRef _Nonnull __XHeapObjectGetClass(XObjectRef _Nonnull obj) {
    XObjectBase_o * base = (XObjectBase_o *)obj;
    size_t xinfo = atomic_load(&(base->_xinfo));
    XAssert(XInfo_MarkNotXObject != (xinfo & XInfo_MarkMask), "");
    XClassRef cls = ((XObjectBase_o *)obj)->_cls;
    XAssert(cls, "");
    return cls;
}

#pragma mark - --------------

extern XHashByte16_t __XBytesHashContent(const unsigned char * _Nullable content, size_t length);


#pragma mark - String & Data

#if CX_TARGET_RT_64_BIT
#define X_BUILD_StringInlineUnicodeCountMask SIZE_C(0xFFFFFFF000000000)
#define X_BUILD_StringInlineUnicodeCountShift 36
#define X_BUILD_StringInlineUtf8LengthMask SIZE_C(0xFFFFFFF00)
#else
#define X_BUILD_StringInlineUnicodeCountMask SIZE_C(0xFFF00000)
#define X_BUILD_StringInlineUnicodeCountShift 12
#define X_BUILD_StringInlineUtf8LengthMask SIZE_C(0xFFF00)
#endif

// 128 - sizeof(_XString) - sizeof(_XStringHashableInline_t)
#define X_BUILD_XStringDataSmallCapacityMax (SIZE_C(0x80) - sizeof(_XString_o) - sizeof(_XStringInlineContent_s))

/// 返回值 != 0
extern size_t _XStringDataByteHash(const void * _Nonnull _byte, ssize_t len);


// 调用之前需要data.length <= X_BUILD_TaggedData_CountMax
static inline XObjectRef _Nonnull __XRTaggedDataEncode(size_t data, size_t len, const char * _Nonnull func) {
    size_t bytes = data;
#if CX_TARGET_RT_BIG_ENDIAN
    bytes = bytes >> SIZE_C(8);
#endif
    size_t content = bytes | (len << X_BUILD_TaggedData_ByteBitCount);
    
    return __XTaggedObjectEncodeScopeA(X_TaggedObjectTypeBits_XData, content, func);
}

// 调用之前需要ref 非空， ref 是个taggedpointer, 并且是 Data 类型
static inline size_t __XRTaggedDataDecode(XObjectRef _Nonnull ref, size_t * _Nonnull count, const char * _Nonnull func) {
    size_t content = __XTaggedObjectDecodeContentScopeA((uintptr_t)ref, X_TaggedObjectTypeBits_XData, func);
    size_t len = content >> X_BUILD_TaggedData_ByteBitCount;
    XAssertFunc(len <= X_BUILD_TaggedData_CountMax, func, "tagged data length error");
    size_t result = content & X_TaggedData_ByteMask;

#if CX_TARGET_RT_BIG_ENDIAN
    result = result << 8;
#endif
    *count = len;
    return result;
}

// 调用之前需要data.length <= X_BUILD_TaggedString_CountMax
static inline XObjectRef _Nonnull __XRTaggedStringEncode(size_t data, size_t len, const char * _Nonnull func) {
    size_t bytes = data;
#if CX_TARGET_RT_BIG_ENDIAN
    bytes = bytes >> SIZE_C(8);
#endif
    size_t content = bytes | (len << X_BUILD_TaggedString_ByteBitCount);
    
    return __XTaggedObjectEncodeScopeA(X_TaggedObjectTypeBits_XString, content, func);
}

// 调用之前需要ref 非空， ref 是个taggedpointer, 并且是 String 类型
static inline size_t __XRTaggedStringDecode(XObjectRef _Nonnull ref, size_t * _Nonnull count, const char * _Nonnull func) {
    size_t content = __XTaggedObjectDecodeContentScopeA((uintptr_t)ref, X_TaggedObjectTypeBits_XString, func);
    size_t len = content >> X_BUILD_TaggedString_ByteBitCount;
    XAssertFunc(len <= X_BUILD_TaggedString_CountMax, func, "tagged data length error");
    size_t result = content & X_TaggedString_ByteMask;

#if CX_TARGET_RT_BIG_ENDIAN
    result = result << 8;
#endif
    *count = len;
    return result;
}

// 调用之前需要ref 非空， ref 是个taggedpointer, 并且是 String 类型
static inline bool_t __XBoolDecode(XObjectRef _Nonnull ref, const char * _Nonnull func) {
    size_t content = __XTaggedObjectDecodeContentScopeC((uintptr_t)ref, X_BUILD_TaggedObjectCScopeTypeXBool, func);
    return content != 0;
}

// 调用之前需要data.length <= X_BUILD_TaggedString_CountMax
static inline XObjectRef _Nonnull __XBoolEncode(bool_t data, const char * _Nonnull func) {
    const size_t t = X_BUILD_TaggedObjectCScopeTypeXBool;
    size_t content = data ? 1 : 0;
    size_t v = X_TaggedObjectFlag | t | ((content << X_BUILD_TaggedObjectContentShift) & X_TaggedObjectScopeCContentMask);
    return __XTaggedObjectEncodeScopeC(X_BUILD_TaggedObjectCScopeTypeXBool, v, func);
}

static inline _XString_o * _Nonnull __XHeapRefAsXString(XObjectRef _Nonnull ref, const char * _Nonnull func, const char * _Nonnull desc) {
    return _XHeapObjectAs(ref, XStringClass, func);
}

static inline _XData_o * _Nonnull _XHeapRefAsXData(XObjectRef _Nonnull ref, const char * _Nonnull func, const char * _Nonnull desc) {
    return _XHeapObjectAs(ref, XDataClass, func);
}

/// 需要确保ref nonnull
extern void _XDataUnpack(XPtr _Nonnull ref, _XDataUnpacked_t * _Nonnull receiver, const char * _Nonnull func, const char * _Nonnull desc);

/// 需要确保ref nonnull
extern void _XStringUnpack(XPtr _Nonnull ref, _XStringUnpacked_t * _Nonnull receiver, const char * _Nonnull func, const char * _Nonnull desc);

extern size_t __XDataGetHashCode(_XData_o * _Nonnull ref, const char * _Nonnull func);
extern size_t _XDataGetHashCodeIfExisted(_XData_o * _Nonnull ref, const char * _Nonnull func);

extern size_t __XStringGetHashCode(_XString_o * _Nonnull ref, const char * _Nonnull func);
extern size_t _XStringGetHashCodeIfExisted(_XString_o * _Nonnull ref, const char * _Nonnull func);
extern XStringUtf8Layout_s __XHeapStringGetUtf8StringLayout(_XString_o * _Nonnull ref, const char * _Nonnull func);
extern XStringUtf8Layout_s _XRHeapDataGetUtf8StringLayout(_XData_o * _Nonnull ref, const char * _Nonnull func);

extern size_t __XHeapDataGetLength(_XData_o * _Nonnull ref, const char * _Nonnull func);
extern size_t __XHeapStringGetLength(_XString_o * _Nonnull ref, const char * _Nonnull func);
extern size_t __XHeapDataGetLayout(_XData_o * _Nonnull ref);

static inline ssize_t __XDataGetUIntBlockCount(size_t _count) {
    size_t count = _count;
    count += sizeof(size_t) - 1;
    return count / sizeof(size_t);
}

extern XObjectRef _Nonnull _XDataCreateWithStringContentUtf8Bytes(XObjectOption flag, const uint8_t * _Nullable buffer, size_t length, size_t unicodeCount, size_t hashCode, const char * _Nonnull func);


#pragma mark - init

void __XRuntimeInit(void);


#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XRuntime_h */
