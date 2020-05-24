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
 refType: 1, value = 1
 taggedContent: 62 {
    class: 2
    objectContent: 60
 }
 flag: 1, value = 1
*/


#if BUILD_TARGET_RT_64_BIT

#define X_BUILD_TaggedMask 0x8000000000000001ULL
#define X_BUILD_TaggedObjectFlag 0x8000000000000001ULL

#define X_BUILD_TaggedObjectClassMask    0x6000000000000000ULL
#define X_BUILD_TaggedObjectClassShift    61ULL
#define X_BUILD_TaggedObjectClassNumber   0x0ULL
#define X_BUILD_TaggedObjectClassString  0x2000000000000000ULL
#define X_BUILD_TaggedObjectClassData    0x4000000000000000ULL
#define X_BUILD_TaggedObjectClassDate    0x6000000000000000ULL
#define X_BUILD_TaggedObjectContentShift 1ULL

#else

#define X_BUILD_TaggedMask 0x80000001UL
#define X_BUILD_TaggedObjectFlag 0x80000001UL

#define X_BUILD_TaggedObjectClassMask    0x60000000UL
#define X_BUILD_TaggedObjectClassShift   29UL
#define X_BUILD_TaggedObjectClassNumber  0x0UL
#define X_BUILD_TaggedObjectClassString  0x20000000UL
#define X_BUILD_TaggedObjectClassData    0x40000000UL
#define X_BUILD_TaggedObjectClassDate    0x60000000UL
#define X_BUILD_TaggedObjectContentShift 1UL

#endif



typedef struct {
    _Atomic(XFastUInt) rcInfo;
} _XObjectCompressedBase;

#define X_BUILD_RcInfoConstantCompressed (X_BUILD_RcMax | X_BUILD_CompressedRcFlag)

#define _XConstantObjectCompressedBaseMake(typeId) {\
    .rcInfo = ATOMIC_VAR_INIT((uintptr_t)(X_BUILD_RcInfoConstantCompressed | (typeId << X_BUILD_CompressedRcTypeShift))),\
}

#define _XConstantObjectBaseMake(type) {\
    .rcInfo = ATOMIC_VAR_INIT(X_BUILD_RcMax),\
    .typeInfo = ATOMIC_VAR_INIT((uintptr_t)(type)),\
}


struct _XTypeIdentifier;
typedef struct _XTypeIdentifier _XTypeIdentifier_s;
typedef const struct _XTypeIdentifier * _XTypeIdentifierPtr;

struct _XTypeIdentifier {
    const char * _Nonnull name;
    XRefHashCode_f _Nullable hashCode;
    XRefEqual_f _Nonnull equalTo;
    XRefCompare_f _Nullable compare;
};





#pragma mark - XNull

typedef struct {
    XUInt __;
} _XNullContent_t;

typedef struct {
    XObjectBase_s _runtime;
    _XNullContent_t content;
} _XNull;

#pragma mark - XBoolean

typedef struct {
    XBool value;
} _XBooleanContent_t;

typedef struct {
    XObjectBase_s _runtime;
    _XBooleanContent_t content;
} _XBoolean;

#pragma mark - XNumber

typedef union {
    XSInt32 s;
    XUInt32 u;
    XFloat32 f;
} _XNumberBits32_u;

typedef union {
    _XNumberBits32_u bits32;
    XNumberBits64_u bits64;
} _XNumberBits_u;


#if BUILD_TARGET_RT_64_BIT
typedef struct {
    XUInt32 type;
    _XNumberBits32_u bits32;
    XUInt8 extended[0];/* 可能有0、8、16 3种可能 */
} _XNumberContent_t;
#else
typedef struct {
    XUInt32 type;
    _XNumberBits_u bits;
} _XNumberContent_t;
#endif

typedef struct {
    _XObjectCompressedBase _runtime;
    _XNumberContent_t content;
} _XNumber;


#pragma mark - XString
    
typedef struct {
    _Atomic(XFastUInt) _refCount;
    XUInt size;
    XUInt8 content[0];
} _XBuffer;

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

extern XBool _XByteStorageUnpackedEqual(XByteStorageUnpacked_t * _Nonnull lhs, XByteStorageUnpacked_t * _Nonnull rhs, const char * _Nonnull func);
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
32: (4 + 4 + 4 = 12)
4 20 52
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

struct __WeakPackage;
    
typedef struct {
    uintptr_t value;//value 不可变
    _Atomic(uintptr_t) table;
    struct __WeakPackage * _Nullable next;
} _WeakPackageContent_t;

typedef struct __WeakPackage {
    _XObjectCompressedBase _runtime;
    _WeakPackageContent_t content;
} _WeakPackage;


#pragma mark - XCollection
typedef struct {
    _XObjectCompressedBase _runtime;
    XPtr _Nonnull content;
} _XCollection;

#pragma mark - XArray
typedef _XCollection _XArray;

#pragma mark - XStorage
typedef _XCollection _XStorage;

#pragma mark - XMap
typedef _XCollection _XMap;

#pragma mark - XSet
typedef _XCollection _XSet;

#pragma mark - XObject

typedef struct {
    XObjectBase_s _runtime;
    XUInt8 content[0];
} _XObject;



#pragma pack(pop)

extern void _XWeakPackageRelease(_WeakPackage * _Nonnull WeakPackage);

    
    
    
#pragma mark - runtime


//如果ref是个 TaggedObject 返回值有效，否则返回 XCompressedTypeNone
extern XTaggedType _XRefGetTaggedObjectTaggedType(XRef _Nonnull ref);

extern const XType_s * _Nullable _XRefGetTaggedObjectClass(XRef _Nonnull ref);

extern const XType_s * _Nonnull _XObjectGetClass(_XObject * _Nonnull object, const char * _Nonnull func);
extern const XType_s * _Nonnull _XHeapRefGetClass(XHeapRef _Nonnull ref, XCompressedType * _Nullable compressedType, const char * _Nonnull func);
    
extern const XType_s * _Nonnull _XRefGetClass(XRef _Nonnull ref, XCompressedType * _Nullable compressedType, const char * _Nonnull func);

    
#pragma mark - hash
    
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
