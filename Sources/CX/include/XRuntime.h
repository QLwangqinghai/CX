//
//  XRuntime.h
//  
//
//  Created by vector on 2020/4/4.
//

#ifndef XRuntime_h
#define XRuntime_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XType.h"

typedef XPtr _XDescriptionBuffer;
typedef XComparisonResult (*XRefCompare_f)(XRef _Nonnull lhs, XRef _Nonnull rhs);

typedef XHashCode (*XRefHashCode_f)(XRef _Nonnull obj);
typedef XBool (*XRefEqual_f)(XRef _Nonnull lhs, XRef _Nonnull rhs);
typedef void (*XRefDeinit_f)(XRef _Nonnull obj);
typedef void (*XRefDescribe_f)(XRef _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);

typedef XUInt XRefKind;

//struct __XRefKind;
//typedef struct __XRefKind _XRefKind_t;
//typedef const _XRefKind_t * XRefKind;
    
struct _XAllocator;
typedef const struct _XAllocator * _XAllocatorPtr;

    
#if defined(__cplusplus)

typedef struct {
    XFastUInt rcInfo;
    uintptr_t typeInfo;
} XObjectBase_s;
#else
#include "XAtomic.h"
typedef struct {
    _Atomic(XFastUInt) rcInfo;
    _Atomic(uintptr_t) typeInfo;
} XObjectBase_s;
#endif
    
typedef struct _XTypeBase {
    XRefKind kind;
    const char * _Nonnull name;
} XTypeBase_s;

typedef struct {
    XObjectBase_s _runtime;
    XTypeBase_s base;
} XType_s;


typedef struct {
    XObjectBase_s _runtime;
    XTypeBase_s base;
    uintptr_t super;
    _XAllocatorPtr _Nonnull allocator;
    XRefDeinit_f _Nonnull deinit;
    XRefDescribe_f _Nonnull describe;
} XObjectType_s;

//extern XRefKind _Nonnull XRefKindClass;
//extern XRefKind _Nonnull XRefKindConstantValue;
//extern XRefKind _Nonnull XRefKindValue;
//extern XRefKind _Nonnull XRefKindCollection;
//extern XRefKind _Nonnull XRefKindObject;


extern XHashCode XRefHash(XRef _Nonnull obj);
extern XBool XRefEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern void XRefDescribe(XRef _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);

    
typedef XUInt32 XNumberType;


#define X_BUILD_ObjectRcFlagReadOnly ((XUInt)1)

#if BUILD_TARGET_RT_64_BIT
    #define X_BUILD_UInt(value) value##ULL
#else
    #define X_BUILD_UInt(value) value##UL

#endif

typedef XUInt XCompressedType;


extern XCompressedType XCompressedTypeOfClass(XClass _Nonnull cls);

typedef XUInt XObjectRcFlag;
extern const XObjectRcFlag XObjectRcFlagReadOnly;
extern const XObjectRcFlag XObjectRcFlagStatic;

typedef XUInt XObjectFlag;

//初始化单例对象， 不进行引用计数、一直不释放
extern const XObjectFlag XObjectFlagStatic;

//对象释放时clear内存, XString、XData、XValue、XObject 支持
extern const XObjectFlag XObjectFlagClearWhenDealloc;

static inline XObjectRcFlag XObjectRcFlagFromObjectFlag(XObjectFlag flag) {
    XObjectRcFlag rcFlag = 0;
    if ((flag & XObjectFlagStatic) == XObjectFlagStatic) {
        rcFlag |= XObjectRcFlagStatic;
    }
    return rcFlag;
}



extern const XClass _Nonnull XClassType;//0
extern const XClass _Nonnull XClassNull;//1
extern const XClass _Nonnull XClassBoolean;//2

extern const XClass _Nonnull XClassNumber;//3
extern const XClass _Nonnull XClassString;//4
extern const XClass _Nonnull XClassData;//5
extern const XClass _Nonnull XClassDate;//6
extern const XClass _Nonnull XClassValue;//7
extern const XClass _Nonnull XClassPackage;//8

extern const XClass _Nonnull XClassArray;//9
extern const XClass _Nonnull XClassMap;//10
extern const XClass _Nonnull XClassSet;//11

struct _XAllocator;
typedef const struct _XAllocator * _XAllocatorPtr;

typedef XRef _Nonnull (*XRefAllocate_f)(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag);
typedef void (*XRefDeallocate_f)(_XAllocatorPtr _Nonnull allocator, XObject _Nonnull obj);


extern XRefKind XRefGetKind(XRef _Nonnull ref);
extern XClass _Nonnull XRefGetClass(XRef _Nonnull ref);
extern XBool XRefIsMetaType(XRef _Nonnull ref);

    
typedef XUInt XTaggedType;

extern const XTaggedType XTaggedTypeConstantValue;
extern const XTaggedType XTaggedTypeNumber;
extern const XTaggedType XTaggedTypeDate;
extern const XTaggedType XTaggedTypeByteStorage;
extern const XTaggedType XTaggedTypeMax;
//others error

extern XTaggedType XRefGetTaggedType(XRef _Nonnull ref);
extern XIndex XRefGetTypeId(XRef _Nonnull ref);
extern XIndex XHeapRefGetTypeId(XHeapRef _Nonnull ref);
/// TODO: delete
extern XCompressedType XHeapRefGetCompressedType(XHeapRef _Nonnull ref);


extern XHashCode XHash(XUInt8 * _Nullable bytes, XUInt length);

#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XRuntime_h */
