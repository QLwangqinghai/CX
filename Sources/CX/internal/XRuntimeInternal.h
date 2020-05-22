//
//  XRuntimeInternal.h
//  
//
//  Created by vector on 2020/4/4.
//

#ifndef XRuntimeInternal_h
#define XRuntimeInternal_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XRuntime.h"
#include "XAllocator.h"
#include "XAtomic.h"
#include "XRef.h"

typedef XPtr _XDescriptionBuffer;

typedef void (*XObjectDeinit_f)(XObject _Nonnull obj);
typedef void (*XObjectDescribe_f)(XObject _Nonnull obj, _XDescriptionBuffer _Nullable buffer);
typedef XObject _Nonnull (*XObjectCopy_f)(XObject _Nonnull obj);


#if BUILD_TARGET_RT_64_BIT
    #pragma pack(push, 8)
#else
    #pragma pack(push, 4)
#endif


/*
 Tagged32
 refType: 1
 taggedContent: 30
 flag: 1, value = 1
 */

/*
Tagged64
refType: 2
taggedContent: 61
flag: 1, value = 1
*/


/*
 TaggedObject32
 refType: 1, value = 1
 taggedContent: {
    class: 2
    objectContent: 28
 }
 flag: 1, value = 1
*/

/*
 TaggedObject64
 refType: 2, value = 1
 taggedContent: 61 {
    class: 2
    objectContent: 59
 }
 flag: 1, value = 1
*/


/*
 TaggedIsa64
 refType: 2, value = 2
 taggedContent: 61 {
    isa: 6
    counter: 55
 }
 flag: 1, value = 1
 */


/*
 XObjectFlagclearWhenDealloc
 XObjectFlagNoRc
 */


//64bit 压缩的ObjectHeader flagBegin = 2
 /* flagBegin:2 type:6 rcInfo:55 flagEnd:1  */

//64bit 压缩的StackObject flagBegin = 1
/* flagBegin:2 type:6 rcInfo:55 flagEnd:1  */

//32bit StackObject flagBegin = 1
/* flagBegin:1 type:6 rcInfo:55 flagEnd:1  */


// rc info
/*
 count://其余高位
 flags: 低4位
 flag1:hasWeak
 */

#define X_BUILD_TypeKindValue 0x1UL
#define X_BUILD_TypeKindObject 0x2UL
#define X_BUILD_TypeKindWeakableObject 0x3UL
#define X_BUILD_TypeKindMetaClass 0xFUL

    

#if BUILD_TARGET_RT_64_BIT

#define X_BUILD_ObjectRcMax 0xFFFFFFFFFFFFFFF0ULL

#define X_BUILD_TaggedMask 0xC000000000000001ULL
#define X_BUILD_TaggedObjectFlag 0x8000000000000001ULL

#define X_BUILD_TaggedObjectClassMask    0x3000000000000000ULL
#define X_BUILD_TaggedObjectClassShift    60ULL
#define X_BUILD_TaggedObjectClassNumber   0x0ULL
#define X_BUILD_TaggedObjectClassString  0x1000000000000000ULL
#define X_BUILD_TaggedObjectClassData    0x2000000000000000ULL
#define X_BUILD_TaggedObjectClassDate    0x3000000000000000ULL

#define X_BUILD_TaggedObjectHeaderFlag  0x4000000000000001ULL
#define X_BUILD_TaggedObjectHeaderClassMask    0x3F00000000000000ULL
#define X_BUILD_TaggedObjectHeaderClassShift   56ULL

#else

#define X_BUILD_ObjectRcMax 0xFFFFFFF0UL

#define X_BUILD_TaggedMask 0x80000001UL
#define X_BUILD_TaggedObjectFlag 0x80000001UL

#define X_BUILD_TaggedObjectClassMask    0x60000000UL
#define X_BUILD_TaggedObjectClassShift   29UL
#define X_BUILD_TaggedObjectClassNumber  0X0UL
#define X_BUILD_TaggedObjectClassString  0x20000000UL
#define X_BUILD_TaggedObjectClassData    0x40000000UL
#define X_BUILD_TaggedObjectClassDate    0x60000000UL


#endif

#define X_BUILD_TaggedObjectClassMax    X_BUILD_TaggedObjectClassDate

#if BUILD_TARGET_RT_64_BIT

typedef struct {
    _Atomic(XFastUInt) rcInfo;
} _XObjectCompressedBase;

typedef struct {
    _Atomic(XFastUInt) rcInfo;
    _Atomic(uintptr_t) typeInfo;
} _XObjectBase;

//
#define X_BUILD_TypeInfoConstantCompressed (uintptr_t)(0xC0FFFFFFFFFFFFE1ULL)

/* flagBegin:2 type:6 rcInfo:55 flagEnd:1  */
#define _XConstantObjectCompressedBaseMake(type) {\
    .rcInfo = ATOMIC_VAR_INIT((uintptr_t)(X_BUILD_TypeInfoConstantCompressed | (((type) & 0x3f) << 56))),\
}

#else

typedef struct {
    _Atomic(uintptr_t) typeInfo;
    _Atomic(XFastUInt) rcInfo;
} _XObjectCompressedBase;

typedef _XObjectCompressedBase _XObjectBase;

#define _XConstantObjectCompressedBaseMake(type) {\
    .typeInfo = ATOMIC_VAR_INIT((uintptr_t)(type)),\
    .rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
}

#endif

#define _XConstantObjectBaseMake(type) {\
    .typeInfo = ATOMIC_VAR_INIT((uintptr_t)(type)),\
    .rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
}



struct _XTypeIdentifier;
typedef struct _XTypeIdentifier _XTypeIdentifier_s;
typedef const struct _XTypeIdentifier * _XTypeIdentifierPtr;

struct _XTypeIdentifier {
    const char * _Nonnull name;
    XRefHashCode_f _Nullable hashCode;
    XRefEqualTo_f _Nonnull equalTo;
    XRefCompare_f _Nullable compare;
};



struct _XTypeBase;
typedef struct _XTypeBase XTypeBase_s;

struct _XTypeBase {
    _XTypeIdentifierPtr _Nonnull identifier;

#if BUILD_TARGET_RT_64_BIT
    XUInt64 kind: 4;
    XUInt64 xx: 4;
    XUInt64 domain: 8;
    XUInt64 tableSize: 48;
#else
    XUInt32 kind: 4;
    XUInt32 xx: 4;
    XUInt32 domain: 8;
    XUInt32 tableSize: 16;

#endif
    uintptr_t /* _XType_s * _Nullable */ super;
    _XAllocatorPtr _Nonnull allocator;

    //对象方法
    XObjectDeinit_f _Nullable deinit;
    XObjectDescribe_f _Nonnull describe;
};


typedef struct {
    _XObjectBase _runtime;
    XTypeBase_s base;
    
    //动态方法列表
    uintptr_t table[0];
} _XType_s;

#pragma mark - XNull

typedef struct {
    XUInt __;
} _XNullContent_t;

typedef struct {
    _XObjectBase _runtime;
    _XNullContent_t content;
} _XNull;

#pragma mark - XBoolean

typedef struct {
    XBool value;
} _XBooleanContent_t;

typedef struct {
    _XObjectBase _runtime;
    _XBooleanContent_t content;
} _XBoolean;

#pragma mark - XNumber

typedef union {
    XSInt32 s;
    XUInt32 u;
    XFloat32 f;
} _XNumberBits32_u;

typedef union {
    XSInt64 s;
    XUInt64 u;
    XFloat64 f;
} _XNumberBits64_u;

typedef struct {
    XUInt32 type;
    _XNumberBits32_u bits32;
    XUInt8 extended[0];/* 可能有0、8、16 3种可能 */
} _XNumberContent_t;


typedef struct {
    _XObjectCompressedBase _runtime;
    _XNumberContent_t content;
} _XNumber;

#pragma mark - XString
/*
 
 */

//inline buffer

typedef struct {
    _Atomic(XFastUInt) _refCount;
    XUInt size;
    XUInt8 content[0];
} _XBuffer;

/*
(8 + 4 + 4 + opt16 = 16 or 32)
16 32 48 64 80 96 112(128-16) (256-16)
*/
//typedef struct {
//    _XExtendedLayout layout: 4;
//    XUInt32 hasHashCode: 1;
//    XUInt32 __unuse: 3;
//    XUInt32 clearWhenDealloc: 1;
//    XUInt32 __unusedFlags: 7;
//    XUInt32 inlineLength: 16;//layout == _XStringLayoutInline时有效 取值范围(0、16、48、112、 240), 其他情况必须设置为UInt16Max
//    XUInt32 hashCode;
//    XUInt8 extended[0];/* 可能有0、16、48、112、 240 5种可能 */
//} _XByteStorageContent_t;

typedef struct {
    XUInt32 length;
    XUInt32 __xx;
} _XByteStorageContent_t;

typedef struct {
    XUInt32 length;
    XUInt32 offset;
    _Atomic(XFastUInt) hashCode;
    _XBuffer * _Nonnull buffer;
} _XByteStorageContentLarge_t;

typedef struct {
    XUInt32 length;
    XUInt8 extended[4];/* 可能有0、16、48、112、 240 5种可能 */
} _XByteStorageContentSmall_t;

typedef struct {
    XUInt8 content[sizeof(XUInt)];//content[0] 标识长度
} _XByteStorageNano_t;
    
#define _XByteStorageContentBufferSizeMin X_BUILD_UInt(245)

typedef struct {
    XUInt isString: 1;
    XUInt contentType: (XUIntBitsCount - 1);//0 tagged; 1 small; 2 large
    union XByteStorageUnpackedContent_u {
        _XByteStorageContentLarge_t * _Nonnull large;
        _XByteStorageContentSmall_t * _Nonnull small;
        _XByteStorageNano_t nano;
        XUInt __nano;
    } content;
} XByteStorageUnpacked_t;

typedef struct {
    _XObjectCompressedBase _runtime;
    _XByteStorageContent_t content;
} _XByteStorage;

//typedef void (*XCustomRelease_f)(XPtr _Nullable context, XPtr _Nonnull content, XUInt length);
//typedef struct {
//    XPtr _Nullable context;
//    XUInt length;
//    XCustomRelease_f _Nullable customRelease;
//    XPtr _Nonnull content;
//} _XByteCustomContent_t;

typedef _XByteStorage _XString;

#pragma mark - XData

typedef _XByteStorage _XData;

#pragma mark - XDate

typedef struct {
    XTimeInterval time;
} _XDateContent_t;

typedef struct {
    _XObjectCompressedBase _runtime;
    _XDateContent_t content;
} _XDate;

#pragma mark - XValue

/*
32: (8 + 4 + 4 = 16)
16 48
64: (8 + 4 + 4 = 16)
16 48
*/

typedef struct {
    XUInt32 clearWhenDealloc: 1;
    XUInt32 contentSize: 31;
    _Atomic(XFastUInt32) hashCode;
    XUInt8 extended[0];
} _XValueContent_t;

typedef struct {
    _XObjectCompressedBase _runtime;
    _XValueContent_t content;
} _XValue;


#pragma mark - XPackage

typedef struct {
    XU8Char * _Nonnull typeName;
    XSize clearWhenDealloc: 1;
    XSize paddingSize: 6;
    XSize contentSize: (XUIntBitsCount - 7);
    XPackageDeinit_f _Nullable deinit;
    XUInt8 extended[0];
} _XPackageContent_t;

typedef struct {
    _XObjectCompressedBase _runtime;
    _XPackageContent_t content;
} _XPackage;

#pragma mark - XWeakPackage

struct __WeakStorage;
    
typedef struct {
    uintptr_t value;//value 不可变
    _Atomic(uintptr_t) table;
    struct __WeakStorage * _Nullable next;
} _WeakStorageContent_t;

typedef struct __WeakStorage {
    _XObjectCompressedBase _runtime;
    _WeakStorageContent_t content;
} _WeakStorage;


#pragma mark - XCollection
typedef struct {
    _XObjectCompressedBase _runtime;
    XPtr _Nonnull content;
} _XCollection;

#pragma mark - XArray
typedef _XCollection _XArray;

#pragma mark - XMap
typedef _XCollection _XMap;

#pragma mark - XSet
typedef _XCollection _XSet;

#pragma mark - XObject

typedef struct {
    _XObjectBase _runtime;
    XUInt8 content[0];
} _XObject;



#pragma pack(pop)

extern void _XWeakPackageRelease(_WeakStorage * _Nonnull weakStorage);


//如果ref是个 TaggedObject 返回值有效，否则返回 XCompressedTypeNone
extern XCompressedType _XRefGetTaggedObjectCompressedType(XRef _Nonnull ref);

extern const _XType_s * _Nullable _XRefGetTaggedObjectClass(XRef _Nonnull ref);

//如果ref是个 CompressedObject 返回值有效，否则返回 XCompressedTypeNone
extern _XType_s * _Nonnull _XRefGetUnpackedType(XRef _Nonnull ref, XCompressedType * _Nullable compressedType, const char * _Nonnull func);

//如果ref是个 CompressedObject 返回值有效，否则返回 XCompressedTypeNone
extern _XType_s * _Nonnull _XRefUnpackType(uintptr_t type, XCompressedType * _Nullable compressedType, const char * _Nonnull func);

extern uintptr_t _XRefGetType(XRef _Nonnull ref);
extern _XType_s * _Nonnull _XRefGetClass(XRef _Nonnull ref, const char * _Nonnull func);

extern XHashCode _XHashUInt64(XUInt64 i);
extern XHashCode _XHashSInt64(XSInt64 i);
extern XHashCode _XHashFloat64(XFloat64 d);
extern XUInt32 _XELFHashBytes(XUInt8 * _Nullable bytes, XUInt32 length);


#pragma mark - weak

typedef struct {
    XIndex id;
    XUInt lock;
    
} _XWeakTable;
extern void _XWeakTableTryRemove(_XWeakTable * _Nonnull table, XObject _Nonnull value);
extern _XWeakTable * _Nonnull _XWeakTableGet(uintptr_t address);
extern void _XWeakTableLock(_XWeakTable * _Nonnull table);
extern void _XWeakTableUnlock(_XWeakTable * _Nonnull table);



#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XRuntime_h */
