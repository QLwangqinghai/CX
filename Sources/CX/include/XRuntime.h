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


typedef XUInt32 XRefKind;
typedef XUInt32 XTypeKind;

extern const XTypeKind XTypeKindValue;//1
extern const XTypeKind XTypeKindObject;//2
extern const XTypeKind XTypeKindWeakableObject;//3

//extern const XRefKind XRefKindUnknown;
extern const XRefKind XRefKindInstance;
extern const XRefKind XRefKindClass;
extern const XRefKind XRefKindMetaClass;


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

typedef XBool (*XRefEqualTo_f)(XRef _Nonnull lhs, XRef _Nonnull rhs);
typedef XHashCode (*XRefHashCode_f)(XObject _Nonnull obj);
typedef XComparisonResult (*XRefCompare_f)(XRef _Nonnull lhs, XRef _Nonnull rhs);

extern XRefKind XRefGetKind(XRef _Nonnull ref);
extern XClassIdentifier _Nullable XRefGetIdentfierIfIsClass(XRef _Nonnull ref);
extern XClass _Nonnull XRefGetClass(XRef _Nonnull ref);
extern XBool XRefIsMetaClass(XRef _Nonnull ref);




typedef XUInt32 XTaggedType;
extern const XTaggedType XTaggedTypeNumber;
extern const XTaggedType XTaggedTypeString;
extern const XTaggedType XTaggedTypeData;
extern const XTaggedType XTaggedTypeDate;
extern const XTaggedType XTaggedTypeMax;
//others error

extern XTaggedType XRefGetTaggedType(XRef _Nonnull ref);

extern XHashCode XHash(XUInt8 * _Nullable bytes, XUInt length);

#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XRuntime_h */
