
#ifndef XRef_h
#define XRef_h


#if defined(__cplusplus)
extern "C" {
#endif

#include "CXBaseInternal.h"

typedef void * XRef;

typedef struct {
    _Atomic(size_fast_t) _xrinfo;//XRType_s
} _XRBase;

typedef struct {
    _XRBase _runtime;
    uint8_t content[0];
} _XAnyHeapRef;

typedef size_t XROption;

extern XROption XROptionStatic;

#pragma mark - XRType_s

struct __XRType;
typedef struct __XRType XRType_s;
typedef const XRType_s * XRType;

typedef void (*XRLifeCycle_f)(XRef _Nonnull ref, XRType _Nonnull type);
typedef void (*XRLifeCycleDealloc_f)(XRef _Nonnull ref, XRType _Nonnull type, size_t mid, size_t size);

typedef size_t (*XRDeinit_f)(XRef _Nonnull ref, XRType _Nonnull type);



struct __XRType {
    _Atomic(size_fast_t) _xrinfo;
    size_t id;
    XUtf8String_s instanceName;
    
    size_t instanceSize;
    XRDeinit_f _Nonnull instanceDeinit;
    XRLifeCycleDealloc_f _Nonnull instanceDealloc;
};


#define X_BUILD_REF_RC_ScopeMask SIZE_C(0x3)
#define X_BUILD_REF_RC_ScopeRef SIZE_C(0x2)

//析构中， 不允许retain
#define X_BUILD_REF_RC_One SIZE_C(0x100)

// 非正常的对象，REF不应该出现
#define X_BUILD_REF_RC_Two SIZE_C(0x200)

// 正常的对象，此时如果release， 则直接跳到 X_BUILD_REF_RC_One， 进入析构流程；
#define X_BUILD_REF_RC_Three SIZE_C(0x300)
#if CX_TARGET_RT_64_BIT
#define X_BUILD_REF_RC_Mask SIZE_C(0xFFFFFFFFFFFFFF00)
#define X_BUILD_REF_RC_NoStaticMax SIZE_C(0xFFFFFFFFFFFFFE00)
#else
#define X_BUILD_REF_RC_Mask SIZE_C(0xFFFFFF00)
#define X_BUILD_REF_RC_NoStaticMax SIZE_C(0xFFFFFE00)
#endif

#define X_BUILD_REF_RC_Max X_BUILD_REF_RC_Mask
#define X_BUILD_REF_RC_Static X_BUILD_REF_RC_Max

#define X_BUILD_REF_RC_TypeMask SIZE_C(0x1F)
#define X_BUILD_REF_RC_TypeShift SIZE_C(2)

#define X_BUILD_REF_RC_ManagerIdMask SIZE_C(0x78)
#define X_BUILD_REF_RC_ManagerIdShift SIZE_C(3)



#define X_BUILD_REF_TypeId_XRNotRef SIZE_C(0)
#define X_BUILD_REF_TypeId_XRType SIZE_C(1)



#if defined(__cplusplus)

}  // extern C
#endif

#endif /* XRef_h */
