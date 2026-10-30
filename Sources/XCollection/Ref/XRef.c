
#include "XRefInternal.h"
#include "XHash.h"
#include "XAllocator.h"

XROption XROptionStatic = 1;
typedef uint XRTypeId;


void __XRInitCounter(_Atomic(size_fast_t) * _Nonnull ptr, XRTypeId ctype, XROption flag) {
    XAssert(ctype <= 15, "");
    size_t t = ctype;
    size_t count = 0;
    if ((XROptionStatic & flag) == XROptionStatic) {
        count = X_BUILD_REF_RC_Max;
    } else {
        count = X_BUILD_REF_RC_Three;
    }
    size_t _xinfo = t | count;
    atomic_store(ptr, _xinfo);
}

/// size 为总size
extern XRef _Nonnull _XRAllocate(XRTypeId typeId, size_t size, XObjectOption flag);
extern void _XRDeallocate(XRef _Nonnull ref);

XPtr _Nonnull __XRMemoryAllocate(size_t size) {
    XAssert(size >= sizeof(size_t) * 2, "");
    size_t s = XAllocatorAlignedSize(size);
    XPtr r = XAlignedAllocate(s, sizeof(void *));
    XAssert(NULL != r, "");
    return r;
}
void __XRMemoryDeallocate(XPtr _Nonnull ptr) {
    XAssert(NULL != ptr, "");
    XDeallocate(ptr);
}

XRef _Nonnull _XRAllocate(XRTypeId typeId, size_t size, XObjectOption flag) {
    XAssert(size >= sizeof(size_t) * 2, "");
    _XRBase * ref = (_XRBase *)__XRMemoryAllocate(size);
    __XRInitCounter(&(ref->_xrinfo), typeId, flag);
    XLog("alloc[%p:%llu]", ref, typeId);
    return ref;
}
void _XRDeallocate(XRef _Nonnull ref) {
    __XRMemoryDeallocate(ref);
    XLog("dealloc[%p]", ref);
}


#define XRefErrorCall XAssert(false, "XRefErrorCall")

void __XRNotRefDealloc(XRef _Nonnull ref, XRType _Nonnull type, size_t mid) {
    XRefErrorCall;
}
void __XRNotRefDeinit(XRef _Nonnull ref, XRType _Nonnull type, size_t mid) {
    XRefErrorCall;
}
void __XRTypeDealloc(XRef _Nonnull ref, XRType _Nonnull type, size_t mid) {
    XRefErrorCall;
}
void __XRTypeDeinit(XRef _Nonnull ref, XRType _Nonnull type, size_t mid) {
    XRefErrorCall;
}


void __XRRetain(_XRBase * _Nonnull ref) {
    _XRBase * cbase = (_XRBase *)ref;
    _Atomic(size_fast_t) * rcInfoPtr = &(cbase->_xrinfo);
    size_fast_t rcInfo = atomic_load(rcInfoPtr);
    XAssert(X_BUILD_REF_RC_ScopeRef == (rcInfo & X_BUILD_REF_RC_ScopeMask), "not ref");
    size_fast_t tid = (rcInfo & X_BUILD_REF_RC_TypeMask) >> X_BUILD_REF_RC_TypeShift;
    XAssert(0 != tid, "");
    if (1 == tid) {
        return;
    }
    size_fast_t newRcInfo = 0;
    
    do {
        rcInfo = atomic_load(rcInfoPtr);
        size_fast_t oldCount = rcInfo & X_BUILD_REF_RC_Mask;
        if (oldCount < X_BUILD_REF_RC_Three) {
            XAssertFunc(false, __func__, "ref is deiniting");
        }
        if (oldCount >= X_BUILD_REF_RC_NoStaticMax) {
            return;
        }
        newRcInfo = (rcInfo & (~X_BUILD_REF_RC_Mask)) | (oldCount + X_BUILD_REF_RC_One);
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
}

void __XRRelease(_XRBase * _Nonnull ref) {
    _XRBase * cbase = (_XRBase *)ref;
    _Atomic(size_fast_t) * rcInfoPtr = &(cbase->_xrinfo);
    size_fast_t rcInfo = atomic_load(rcInfoPtr);
    XAssert(X_BUILD_REF_RC_ScopeRef == (rcInfo & X_BUILD_REF_RC_ScopeMask), "not ref");
    size_fast_t tid = (rcInfo & X_BUILD_REF_RC_TypeMask) >> X_BUILD_REF_RC_TypeShift;
    XAssert(0 != tid, "");
    if (1 == tid) {
        return;
    }
    size_fast_t newRcInfo = 0;
    size_fast_t newCount = 0;

    do {
        rcInfo = atomic_load(rcInfoPtr);
        size_fast_t oldCount = rcInfo & X_BUILD_REF_RC_Mask;
        if (oldCount < X_BUILD_REF_RC_Three) {
            XAssertFunc(false, __func__, "ref is deiniting");
        }
        if (oldCount >= X_BUILD_REF_RC_NoStaticMax) {
            return;
        }
        if (oldCount == X_BUILD_REF_RC_Three) {
            newCount = X_BUILD_REF_RC_One;
        } else {
            newCount = oldCount - X_BUILD_REF_RC_One;
        }
        
        newRcInfo = (rcInfo & (~X_BUILD_REF_RC_Mask)) | newCount;
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    
    /// 进行析构
    if (newCount == X_BUILD_REF_RC_One) {
        //do dealloc
        
//        UInt instanceSize = ___XRDeinit(ref, type);
//        ___XRDeallocate(ref, type, __XInfoGetMinfo(newRcInfo), instanceSize);
    }
}

void XRRetain(XRef _Nonnull ref) {
    XAssert(ref, "");
    __XRRetain((_XRBase *)ref);
}

void XRRelease(XRef _Nonnull ref) {
    XAssert(ref, "");
    __XRRelease((_XRBase *)ref);
}

// 分发函数
void __XRDefaultDealloc(XRef _Nonnull ref, XRType _Nonnull type, size_t mid) {
//    XRObjectBase_s * obj = (XRObjectBase_s *)ref;
//    XRClass cls = obj->isa;
//    XAssert(cls, "cls error");
//    XOAllocator allocator = cls->allocator;
//    __XOAllocatorDeallocate(allocator, obj, cls);
    
    
    
}

