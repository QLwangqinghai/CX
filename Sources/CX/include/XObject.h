
#ifndef XObject_h
#define XObject_h


#if defined(__cplusplus)
extern "C" {
#endif

#include "XCoreBase.h"
#include "XAllocator.h"

/*
 ABI:
 对象对齐字节： sizeof(size_t) * 2， 减少runtime运行消耗
 对象头信息字节：sizeof(size_t) * 2， 字节对齐，加快内存访问
 
 typedef struct {
     size_fast_t refcount: SIZE_BITS_COUNT - 8;
     size_fast_t zoneInfo: 3;
     size_fast_t layout: 3;
     size_fast_t mark2: 2; // 0: error, 1: weakable; 2:unweakable 3: weakstore;
 } XObjectXInfo_o __attribute__((aligned(sizeof(void *))));
 当xinfo.mark 为 XInfo_MarkObjectUsingWeakStorage 时，xinfo = weakstorageptr ｜ XInfo_MarkObjectUsingWeakStorage，xinfo中的其他数据放入WeakStorage
 
 typedef struct {
     size_fast_t refcount: SIZE_BITS_COUNT - 16;
     size_fast_t zoneInfo: 7;
     size_fast_t layout: 7;
     size_fast_t mark2: 2; // 0: error, 1: weakable; 2:unweakable 3: weakstore;
 } XObjectXInfo_o __attribute__((aligned(sizeof(void *))));
 */

// isweakable  isrc
// 0 object value weakstorage


#define XOBJECT_ALIGNMENT (2 * SIZE_BYTE_COUNT)
#define XOBJECT_BLOCK_SIZE (2 * SIZE_BYTE_COUNT)
#define XOBJECT_BLOCK_SIZE_SHIFT (SIZE_BYTE_COUNT_SHIFT + 1)

#pragma mark - XInfo

#define XInfo_LayoutMax SIZE_C(0x7)
#define XInfo_ZoneInfoMax SIZE_C(0x7)
#define XInfo_LayoutCount SIZE_C(0x8)

#define XInfo_MarkMask SIZE_C(0x3)
#define XInfo_MarkObjectStrongOnly SIZE_C(0x2)
#define XInfo_MarkObject SIZE_C(0x1)
#define XInfo_MarkObjectUsingWeakStorage SIZE_C(0x3)
#define XInfo_MarkNotXObject SIZE_C(0x0)

#define XInfo_LayoutMask SIZE_C(0x1C)
#define XInfo_LayoutShift SIZE_C(2)
#define XInfo_LayoutBitCount SIZE_C(3)

#define XInfo_ZoneInfoBitCount SIZE_C(3)
#define XInfo_ZoneInfoMask SIZE_C(0xE0)
#define XInfo_ZoneInfoShift SIZE_C(5)

#if CX_TARGET_RT_64_BIT
#define XInfo_ObjectCountMask SIZE_C(0xFFFFFFFFFFFFFF00)
#else
#define XInfo_ObjectCountMask SIZE_C(0xFFFFFF00)
#endif

#define XInfo_ObjectCountShift SIZE_C(8)
#define XInfo_ObjectCountStaticConst XInfo_ObjectCountMask

_Static_assert(XInfo_ZoneInfoBitCount == XZoneInfoBitCount, "error");

struct __XClass;
typedef struct __XClass XClass_o;
typedef const XClass_o * XClassRef;

typedef struct {
    // refcount/zoneInfo/layout/mark
    _Atomic(size_fast_t) _xinfo;
    XClassRef _Nonnull _cls;
} XObjectBase_o __attribute__((aligned(sizeof(void *) * 2)));

#define XObjectBaseMakeStaticStrongOnly(Class) {\
    ._xinfo = ATOMIC_VAR_INIT((XInfo_ObjectCountStaticConst) | (XInfo_MarkObjectStrongOnly)),\
    ._cls = Class,\
}
#define XObjectBaseMakeStaticStrongOnlyWithLayout(Class, Layout) {\
    ._xinfo = ATOMIC_VAR_INIT((XInfo_ObjectCountStaticConst | (((Layout) << XInfo_LayoutShift) & XInfo_LayoutMask) | XInfo_MarkObjectStrongOnly)),\
    ._cls = Class,\
}

typedef void * XObjectRef;
typedef XObjectRef XWeakStorageRef;
typedef XObjectRef XNumberRef;
typedef XObjectRef XStringRef;
typedef XObjectRef XDataRef;
typedef XObjectRef XDateRef;
typedef XObjectRef XBoolRef;
typedef XObjectRef XValueRef;
typedef XObjectRef XMessageRef;
typedef XObjectRef XArrayRef;

#pragma mark - Type & Const

typedef XPtr _XDescriptionBuffer;

typedef size_t XObjectOption;

//初始化单例对象， 不进行引用计数、一直不释放
extern const XObjectOption XObjectOptionStatic;

typedef size_t XStringOption;
extern const XStringOption XStringOptionClearWhenDealloc;

typedef size_t XDataOption;
extern const XDataOption XDataOptionClearWhenDealloc;


typedef uint32_t XStringEncoding;
extern const XStringEncoding XStringEncodingUtf8;

typedef uint32_t XStringDecodeOption;
extern const XStringDecodeOption XStringDecodeOptionAllowEndWith0;
extern const XStringDecodeOption XStringDecodeOptionAllowEndWithIllegalCharacters;
extern const XStringDecodeOption XStringDecodeOptionAllowStartWithBom;
extern const XStringDecodeOption XStringDecodeOptionAllowMultiBom;

#pragma mark - XObject & XClass

struct __XAllocator;
typedef struct __XAllocator XAllocator_s;

typedef struct __XObjectDomain {
    XUtf8String_s name;
} XObjectDomain_s;

// Name 不要带 ""
#define XObjectDomainMake(Name) {\
    .name = XUtf8StringMake(Name),\
}

typedef void (*XObjectInit_f)(XObjectRef _Nonnull self, void * _Nullable params);
typedef XObjectRef _Nonnull (*XObjectCopy_f)(XObjectRef _Nonnull self);
typedef void (*XObjectDeinit_f)(XObjectRef _Nonnull self);
typedef size_t (*XObjectGetHashCode_f)(XObjectRef _Nonnull self);
typedef bool_t (*XObjectEqual_f)(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
//typedef int (*XObjectCompare_f)(XClass _Nonnull self, XClass _Nonnull super, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
typedef void (*XObjectDescribe_f)(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);

//typedef void (*XObjectEncode_f)(XObjectRef _Nonnull self, XEncodeBuffer_s _Nonnull buffer);

typedef XObjectRef _Nonnull (*XAllocatorRetain_f)(XClassRef _Nonnull cls, XObjectRef _Nonnull cbase);
typedef void (*XAllocatorRelease_f)(XClassRef _Nonnull cls, XObjectRef _Nonnull cbase);
typedef XObjectRef _Nonnull (*XAllocatorAllocate_f)(XClassRef _Nonnull cls, XObjectOption option, size_t size, size_t layout);
typedef void (*XAllocatorDeallocate_f)(XClassRef _Nonnull cls, XObjectRef _Nonnull object, size_t zoneInfo);
typedef size_t (*XAllocatorGetSize_f)(XClassRef _Nonnull cls, XObjectRef _Nonnull object);

struct __XAllocator {
    void * _Nullable context;
    XAllocatorAllocate_f _Nonnull allocate;
    XAllocatorDeallocate_f _Nonnull deallocate;
    XAllocatorRetain_f _Nonnull retain;
    XAllocatorRelease_f _Nonnull release;
    XAllocatorGetSize_f _Nonnull getInstanceSize;
};

struct __XClass {
    XObjectBase_o _runtime;
    const XObjectDomain_s * _Nonnull domain;
    const XAllocator_s * _Nonnull allocator;
    XUtf8String_s name;
    size_t allowWeak: 1;
    size_t instanceSize: SIZE_BITS_COUNT - 1;//sizeof object（包含头信息）
    size_t flags;
    // 8
    
    XObjectDeinit_f _Nonnull deinit;
    
    XObjectCopy_f _Nonnull copy;
    XObjectGetHashCode_f _Nonnull getHashCode;
    XObjectEqual_f _Nonnull equal;
    XObjectDescribe_f _Nonnull describe;
    XObjectDescribe_f _Nonnull debugDescribe;
    void * _Nullable vtable;
    void * _Nullable __unuse;
};

struct __XValueContentType;
typedef struct __XValueContentType XValueContentType_s;
typedef size_t (*XValueGetHashCode_f)(const XValueContentType_s * _Nonnull type, const void * _Nonnull value);
typedef bool_t (*XValueEqual_f)(const XValueContentType_s * _Nonnull type, const void * _Nonnull lhs, const void * _Nonnull rhs);
typedef void (*XValueDescribe_f)(const XValueContentType_s * _Nonnull type, const void * _Nonnull content, _XDescriptionBuffer _Nonnull buffer);

struct __XValueContentType {
    size_t size;// 结构体size， 如果size=0，则为动态size类型的struct
    const char * _Nonnull name;
    XValueGetHashCode_f _Nonnull getHashCode;
    XValueEqual_f _Nonnull equal;
    XValueDescribe_f _Nonnull describe;
    XValueDescribe_f _Nonnull debugDescribe;
};

#pragma mark - XPointerType (Description of pointer types)

struct __XPointerType;
typedef struct __XPointerType XPointerType_s;
typedef void * _Nullable (*XPointerRetain_f)(void * _Nullable pointer);
typedef void (*XPointerRelease_f)(void * _Nullable pointer);
struct __XPointerType {
    const char * _Nonnull name;
    XPointerRetain_f _Nullable retain;
    XPointerRelease_f _Nullable release;
};
#define XPointerTypeMake(Type, Retain, Release) {\
    .name = #Type,\
    .retain = Retain,\
    .release = Release,\
}

static inline void * _Nullable XPointerRetain(const XPointerType_s * _Nonnull type, void * _Nullable pointer) {
    if (type->retain) {
        return type->retain(pointer);
    } else {
        return pointer;
    }
}
static inline void XPointerRelease(const XPointerType_s * _Nonnull type, void * _Nullable pointer) {
    if (type->release) {
        type->release(pointer);
    }
}

extern const XPointerType_s __XPointerTypeXObject;
extern void * _Nonnull _XPointerTypeXObjectRetain(void * _Nullable context);
extern void _XPointerTypeXObjectRelease(void * _Nullable context);

#pragma mark - Allocator

extern const XAllocator_s _XAllocatorDefault;

#pragma mark - class

extern const XObjectDomain_s __XObjectDomainX;
#define XObjectDomainXPtr (&__XObjectDomainX)

extern const XClass_o _XMetaClass;
extern const XClass_o _XNumberClass;
extern const XClass_o _XDateClass;
extern const XClass_o _XValueClass;
extern const XClass_o _XStringClass;
extern const XClass_o _XDataClass;
extern const XClass_o _XMessageClass;
extern const XClass_o _XArrayClass;
extern const XClass_o _XBoolClass;
extern const XClass_o _XBoolClass;
extern const XClass_o _XWeakStorageClass;

#define XMetaClass (&_XMetaClass)
#define XNumberClass (&_XNumberClass)
#define XDateClass (&_XDateClass)
#define XValueClass (&_XValueClass)
#define XDataClass (&_XDataClass)
#define XStringClass (&_XStringClass)
#define XMessageClass (&_XMessageClass)
#define XArrayClass (&_XArrayClass)
#define XBoolClass (&_XBoolClass)
#define XWeakStorageClass (&_XWeakStorageClass)

typedef struct {
    XObjectBase_o _runtime;
    uint8_t content[0];
} XRootObject_o;

// 可变对象&不可变对象
// 不可变对象: 内存中的关键数据不可以改变，hashcode 是对内容的hash; Bool, Date, Number, String, Data, Array, Map, Set, OrderedMap, OrderedSet都是不可变对象
// 可变对象: 内存中的数据可以改变，hashcode 是对对象地址的hash; WeakStorage, StringStorage, DataStorage, ArrayStorage, MapStorage, SetStorage, OrderedMapStorage, OrderedSetStorage 都是可变对象
extern XObjectRef _Nonnull _XObjectDefaultCopy(XObjectRef _Nonnull self);
extern XObjectRef _Nonnull _XObjectDefaultCopyAndRelease(XObjectRef _Nonnull self);
extern void _XObjectDefaultDeinit(XObjectRef _Nonnull self);
extern size_t _XObjectDefaultGetHashCode(XObjectRef _Nonnull self);
extern bool_t _XObjectDefaultEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
extern void _XObjectDefaultDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
extern void _XObjectDefaultDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);

#define XClassMakeXDefault(Name, AllowWeak) {\
._runtime = XObjectBaseMakeStaticStrongOnly(XMetaClass),\
.domain = &__XObjectDomainX,\
.allocator = &_XAllocatorDefault,\
.name = XUtf8StringMake(Name),\
.allowWeak = AllowWeak,\
.instanceSize = sizeof(_##Name##_s),\
.copy = _##Name##Copy,\
.deinit = _##Name##Deinit,\
.getHashCode = _##Name##GetHashCode,\
.equal = _##Name##Equal,\
.describe = _##Name##Describe,\
.debugDescribe = _##Name##DebugDescribe,\
}

/// 结构体名为 _[Name]_o
#define XClassMakeNameDeinit(Name, AllowWeak, DeinitFunc) {\
._runtime = XObjectBaseMakeStaticStrongOnly(XMetaClass),\
.domain = &__XObjectDomainX,\
.allocator = &_XAllocatorDefault,\
.name = XUtf8StringMake(Name),\
.allowWeak = AllowWeak,\
.instanceSize = sizeof(_##Name##_o),\
.copy = _XObjectDefaultCopy,\
.deinit = DeinitFunc,\
.getHashCode = _XObjectDefaultGetHashCode,\
.equal = _XObjectDefaultEqual,\
.describe = _XObjectDefaultDescribe,\
.debugDescribe = _XObjectDefaultDebugDescribe,\
}

#pragma mark - XObject & runtime

extern bool_t XObjectIsTaggedObject(XObjectRef _Nonnull obj);
extern void XObjectResetLayout(XObjectRef _Nonnull object, size_t layout);

extern XClassRef _Nonnull XObjectGetClass(XObjectRef _Nonnull obj);
extern size_t XObjectGetLayout(XObjectRef _Nonnull obj);

extern size_t XObjectCheckGetLayout(XObjectRef _Nonnull obj, XClassRef _Nonnull cls);

extern XObjectRef _Nullable XObjectCopy(void * /*XObjectRef*/ _Nullable obj);
extern XObjectRef _Nullable XObjectRetain(void * /*XObjectRef*/ _Nullable obj);
extern void XObjectRelease(void * /*XObjectRef*/ _Nullable ref);

extern bool_t XObjectIsKindOf(XObjectRef _Nonnull object, XClassRef _Nonnull cls);
extern bool_t XObjectIsClass(XObjectRef _Nonnull object);
extern bool_t XObjectIsMemberOf(XObjectRef _Nonnull object, XClassRef _Nonnull cls);

extern size_t XObjectGetHashCode(XObjectRef _Nullable object);
extern bool_t XObjectEqual(XObjectRef _Nullable lhs, XObjectRef _Nullable rhs);
extern void XObjectDescribe(XObjectRef _Nullable object, _XDescriptionBuffer _Nonnull buffer);
extern void XObjectDebugDescribe(XObjectRef _Nullable object, _XDescriptionBuffer _Nonnull buffer);

#pragma mark - XClass

extern XObjectRef _Nonnull XObjectAllocate(XClassRef _Nonnull cls, XObjectOption flag, size_t size, size_t layout);

#pragma mark - XWeakStorage

// object require not XWeakStorageRef
extern XWeakStorageRef _Nonnull XWeakStorageCreate(XObjectRef _Nonnull object);
extern XObjectRef _Nullable XWeakStorageTakeRetainedObject(XWeakStorageRef _Nonnull weakStorage);

#pragma mark - XValue

/// value 会被copy 到XValue 中，copy 执行后会调用retaindata
extern XValueRef _Nonnull XValueCreate(XObjectOption flag, const XValueContentType_s * _Nonnull type, const void * _Nonnull content);
extern const XValueContentType_s * _Nonnull XValueGetType(XValueRef _Nonnull ref);
extern void XValueGetContent(XValueRef _Nonnull ref, void * _Nonnull receiver);

#pragma mark - XNumber

#include "XNumber.h"

#pragma mark - XDate

typedef enum {
    XDateTypeDistantPast = 0,
    XDateTypeInvalid = 1,
    XDateTypeNormal = 2,
    XDateTypeDistantFuture = 3,
} XDateType_e;

typedef struct {
    XDateType_e type;
    microsecond_t microsecond;
} XDateContent_s;

extern XDateRef _Nonnull XDateInvalid;
extern XDateRef _Nonnull XDateDistantPast;
extern XDateRef _Nonnull XDateDistantFuture;


//time 是以 1970 作为原点的时间
extern XDateRef _Nonnull XDateCreate(XObjectOption flag, microsecond_t time);
extern XComparisonResult XDateCompare(XDateRef _Nonnull lhs, XDateRef _Nonnull rhs);
extern microsecond_t XDateGetTimevalSince1970(XDateRef _Nonnull ref);

#pragma mark - XDataRef

extern XDataRef _Nonnull XDataCreate(XObjectOption flag, const uint8_t * _Nullable bytes, ssize_t count);
extern XDataRef _Nonnull XDataCreateWithStringUtf8Encoding(XObjectOption flag, XStringRef _Nonnull string);
extern ssize_t XDataGetLength(XObjectRef _Nonnull ref);
extern void XDataGetBytes(XObjectRef _Nonnull ref, ssize_t location, ssize_t length, void * _Nonnull buffer);

#pragma mark - XString

extern XStringRef _Nullable XStringCreateWithCString(XObjectOption flag, const char * _Nonnull cString, XStringEncoding encode);
extern XStringRef _Nullable XStringCreateWithBytes(XObjectOption flag, const uint8_t * _Nonnull bytes, size_t length, XStringEncoding encode, XStringDecodeOption decodeOption);
extern XStringRef _Nullable XStringCreateWithData(XObjectOption flag, XDataRef _Nonnull data, XStringEncoding encode, XStringDecodeOption decodeOption);
extern XStringRef _Nullable XStringCreateWithDataRange(XObjectOption flag, XDataRef _Nonnull _data, XRange_s range, XStringEncoding encode, XStringDecodeOption decodeOption);

extern ssize_t XStringGetUnicodeCount(XObjectRef _Nonnull ref);
typedef void (*XStringEnumerateUnicode_f)(ssize_t index, uint32_t unicodeChar, void * _Nullable context, bool_t * _Nonnull stop);
extern void XStringEnumerateUnicode(XStringRef _Nonnull self, XStringEnumerateUnicode_f _Nonnull func, void * _Nullable context);

extern ssize_t XStringGetUtf8Length(XObjectRef _Nonnull ref);
extern void XStringGetBytes(XObjectRef _Nonnull ref, ssize_t location, ssize_t length, void * _Nonnull buffer);


#pragma mark - XBool

extern XBoolRef _Nonnull XBoolWithValue(bool_t v);
extern XBoolRef _Nonnull XBoolTrue(void);
extern XBoolRef _Nonnull XBoolFalse(void);
extern bool_t XBoolGetValue(XBoolRef _Nonnull ref);

#pragma mark - XCollections

#define __XCollectionLayoutImmutable SIZE_C(1)
#define __XCollectionLayoutMutable SIZE_C(2)
#define __XCollectionLayoutImmutableBuilder SIZE_C(3)

#pragma mark - XMessage

typedef struct {
    int32_t key;
    XObjectRef _Nullable value;
} XMessageElement_s;

typedef void (*XMessageEnumerate_f)(int32_t key, XObjectRef _Nullable value, void * _Nullable context, bool_t * _Nonnull stop);

extern ssize_t XMessageGetCount(XMessageRef _Nonnull self);

/// return unretained object
extern XObjectRef _Nullable XMessageGetAssignObject(XMessageRef _Nonnull msg, int32_t key, bool_t * _Nullable isContain);
extern XObjectRef _Nullable XMessageGetObject(XMessageRef _Nonnull self, int32_t key, bool_t * _Nullable isContain);

extern XMessageElement_s XMessageGetAssignElement(XMessageRef _Nonnull msg, ssize_t index);
extern XMessageElement_s XMessageGetElement(XMessageRef _Nonnull self, ssize_t index);

extern void XMessageEnumerate(XMessageRef _Nonnull self, XMessageEnumerate_f _Nonnull func, void * _Nullable context);


// -----------------Immutable---------------

/// create immutable XMessage   (ssize_t count, int32_t key, XObjectRef _Nullable value, int32_t key, XObjectRef _Nullable value, ...) XMessageCreate(2, 1, obj1, 4, obj4), 不可以有重复的key， 可以乱序
extern XMessageRef _Nonnull XMessageCreate(ssize_t count, ...);

// ------------------- Mutable ----------------------------

/// create mutable message
extern XMessageRef _Nonnull XMutableMessageCreate(ssize_t count, ...);
extern XMessageRef _Nonnull XMutableMessageCreateWithCapacity(ssize_t capacity);

extern void XMutableMessageSetObject(XMessageRef _Nonnull self, int32_t key, XObjectRef _Nullable object, XObjectRef _Nullable * _Nullable old);
extern void XMutableMessageRemoveObject(XMessageRef _Nonnull self, int32_t key, XObjectRef _Nullable * _Nullable old);


// ------------------- Immutable builder ----------------------------

extern XMessageRef _Nonnull XMessageBuilderCreateWithCount(XObjectOption option, ssize_t count);

/// object的所有权转移到message, 调用顺序key从小到大
extern XMessageElement_s XMessageBuilderReplaceWithRetainedValue(XObjectRef _Nonnull self, ssize_t index, int32_t key, XObjectRef _Nullable value);

/// XMessageBuilder -> XMessage
extern void XMessageBuilderComplete(XObjectRef _Nonnull self);


#pragma mark - XArray

typedef struct {
    XObjectRef _Nullable item;
} XArrayElement_s;

// 添加到XArray的Object都会执行copy操作

typedef void (*XArrayEnumerate_f)(size_t index, XObjectRef _Nullable object, void * _Nullable context, bool_t * _Nonnull stop);

extern ssize_t XArrayGetCount(XArrayRef _Nonnull array);

/// return unretained object
extern XObjectRef _Nullable XArrayGetAssignObject(XArrayRef _Nonnull array, ssize_t index);

/// return retained object
extern XObjectRef _Nullable XArrayGetObject(XArrayRef _Nonnull array, ssize_t index);

extern void XArrayEnumerate(XArrayRef _Nonnull array, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context);

extern void XArrayEnumerateWithRange(XArrayRef _Nonnull array, ssize_t index, ssize_t count, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context);


/// return ImmutableArray,  retainedobject
extern XObjectRef _Nullable XArraySubarray(XObjectRef _Nonnull array, ssize_t index, ssize_t count);

// -----------------Immutable---------------

/// create immutable array
extern XArrayRef _Nonnull XArrayCreateWithValues(XObjectOption option, ssize_t count, ...);
extern XArrayRef _Nonnull XArrayEmpty(void);


// ------------------- Mutable ----------------------------

/// create mutable array
extern XArrayRef _Nonnull XMutableArrayCreateWithValues(XObjectOption option, ssize_t count, ...);

extern XArrayRef _Nonnull XMutableArrayCreateWithArray(XObjectOption option, XArrayRef _Nonnull array);

extern XArrayRef _Nonnull XMutableArrayCreate(XObjectOption option, ssize_t capacity);

extern void XMutableArrayInsert(XObjectRef _Nonnull array, XObjectRef _Nullable object, ssize_t index);

extern void XMutableArrayAppend(XObjectRef _Nonnull array, XObjectRef _Nullable object);
extern void XMutableArrayPrepend(XObjectRef _Nonnull array, XObjectRef _Nullable object);

/// 返回retainedobject
extern void XMutableArrayRemove(XObjectRef _Nonnull array, ssize_t index, XArrayElement_s * _Nullable old);

/// 返回retainedobject
extern void XMutableArrayReplace(XObjectRef _Nonnull array, XObjectRef _Nullable object, ssize_t index, XArrayElement_s * _Nullable old);

/// 返回retainedobject
extern void XMutableArrayReplaceObjects(XObjectRef _Nonnull array, ssize_t index, ssize_t count, XArrayRef _Nullable _objects, size_t objectsStartIndex, size_t objectsCount, bool_t allowReduceCapacity, XArrayRef _Nonnull * _Nullable old);

extern void XMutableArrayRemoveAll(XObjectRef _Nonnull array, bool_t allowReduceCapacity, XArrayRef _Nonnull * _Nullable old);

// ------------------- ImmutableBuilder ----------------------------

/// create immutable array
extern XArrayRef _Nonnull XArrayBuilderCreateWithCount(XObjectOption option, ssize_t count);

/// object的所有权转移到array
extern XObjectRef _Nullable XArrayBuilderReplaceWithRetainedValue(XArrayRef _Nonnull array, ssize_t index, XObjectRef _Nullable object);

/// XArrayBuilder -> XArray
extern void XArrayBuilderComplete(XArrayRef _Nonnull array);

#pragma mark - collection hash

typedef struct _XCollectionHasher {
    size_t h;
    uint64_t key;
    size_t pendingHashCode;
    
    ssize_t currentCount;
    ssize_t count;
} XCollectionHasher_s;

//seed：种子，最好用一个质数，比如：0xEE6B27EB(一个40亿内的质数); 返回值非0(内部实现是如果为0， 返回SIZE_MAX)， key必须内存上sizeof(size_t)对齐，结尾用0填充， 对于超过25 * sizeof(size_t)字节长度的数据， hash len按照sizeof(size_t)对齐(不能截断)，之后 hash前 13*sizeof(size_t)字节 中间4*sizeof(size_t)字节 最后8*sizeof(size_t)字节
extern void XCollectionHasherInit(XCollectionHasher_s * _Nonnull context, ssize_t count);

// key 可以是index， 可以是key的hashcode
extern void XCollectionHasherCombine(XCollectionHasher_s * _Nonnull hasher, size_t key, size_t hashCode);
extern size_t XCollectionHasherFinalize(XCollectionHasher_s * _Nonnull hasher);

/// infoRef 只有2种值， 默认值 和新值
static inline void __XImmutableCollectionUpdateHashCode(_Atomic(size_fast_t) * _Nonnull ptr, size_fast_t newValue, const char * _Nonnull func) {
    XAssertFunc(newValue != 0, func, "");
    size_fast_t oldValue = 0;
    do {
        oldValue = atomic_load(ptr);
        
        if (oldValue == newValue) {
            return;
        } else {
            XAssertFunc(oldValue == 0, func, "");
        }
    } while (!atomic_compare_exchange_strong(ptr, &oldValue, newValue));
}


#if defined(__cplusplus)

}  // extern C
#endif

#endif /* XObject_h */
