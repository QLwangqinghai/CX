//
//  XAllocator.c
//  
//
//  Created by vector on 2020/4/4.
//

#include "internal/XAllocator.h"
#include "internal/XRuntimeInternal.h"
#include "XMemory.h"
#include "internal/XClass.h"

/*
流传状态

>= rcBase 的才可以retain

0  -> rcBase -> hasWeak -> retain -> release -> release ->


*/

/* compressed == 1
 counter
 type: 6
 compressed: 1
 */

#define X_BUILD_CompressedRcMask X_BUILD_UInt(0x1)
#define X_BUILD_CompressedRcFlag X_BUILD_UInt(0x1)

#define X_BUILD_CompressedRcTypeMask X_BUILD_UInt(0x7E)
#define X_BUILD_CompressedRcTypeShift X_BUILD_UInt(0x1)
#define X_BUILD_CompressedTypeWeakStorageRcFlag (X_BUILD_CompressedType_WeakStorage << X_BUILD_CompressedRcTypeShift)

#define X_BUILD_CompressedRcOne X_BUILD_UInt(0x80)
#define X_BUILD_CompressedRcTwo X_BUILD_UInt(0x100)
#define X_BUILD_CompressedRcBase X_BUILD_CompressedRcTwo
#define X_BUILD_CompressedRcDeallocing X_BUILD_CompressedRcOne
#define X_BUILD_CompressedRcMax (XUIntMax - X_BUILD_UInt(0x7F))



/* compressed == 0
 counter
 weak: 1
 compressed: 1
 */

#define X_BUILD_RcHasWeakMask X_BUILD_UInt(0x2)
#define X_BUILD_RcHasWeakFlag X_BUILD_UInt(0x2)

#define X_BUILD_RcOne X_BUILD_UInt(0x4)
#define X_BUILD_RcTwo X_BUILD_UInt(0x8)
#define X_BUILD_RcThree X_BUILD_UInt(0xC)

#define X_BUILD_RcBase X_BUILD_RcThree

//将要dealloc， 可以tryRetain
#define X_BUILD_RcWillDealloc X_BUILD_RcTwo

//析构中， 不允许retain
#define X_BUILD_RcDeallocing X_BUILD_RcOne


#define X_BUILD_RcMax (XUIntMax - X_BUILD_UInt(0x3))

#pragma mark - rc

XRef _Nonnull _XRefRetain(XRef _Nonnull ref, const char * _Nonnull func) {
    _XObjectCompressedBase * cbase = (_XObjectCompressedBase *)ref;
    _Atomic(XFastUInt) * rcInfoPtr = &(cbase->rcInfo);
    XFastUInt rcInfo = 0;
    XFastUInt newRcInfo = 0;
    
    do {
        rcInfo = atomic_load(rcInfoPtr);
        if ((rcInfo & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
            if (rcInfo < X_BUILD_CompressedRcBase) {
                XAssert(false, func, "ref");
            }
            if (rcInfo >= X_BUILD_CompressedRcMax) {
                return ref;
            } else {
                newRcInfo = rcInfo + X_BUILD_CompressedRcOne;
            }
        } else {
            if (rcInfo < X_BUILD_RcBase) {
                XAssert(false, func, "ref");
            }
            if (rcInfo >= X_BUILD_RcMax) {
                return ref;
            } else {
                newRcInfo = rcInfo + X_BUILD_RcOne;
            }
        }
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return ref;
}


XRef _Nullable _XRefTryRetain(XRef _Nonnull ref, const char * _Nonnull func) {
    _XObjectCompressedBase * cbase = (_XObjectCompressedBase *)ref;
    _Atomic(XFastUInt) * rcInfoPtr = &(cbase->rcInfo);
    XFastUInt rcInfo = 0;
    XFastUInt newRcInfo = 0;
    
    do {
        rcInfo = atomic_load(rcInfoPtr);
        if ((rcInfo & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
            XAssert(false, func, "not support");
        }
        if (rcInfo < X_BUILD_RcWillDealloc) {
            XAssert(false, func, "ref");
        }
        if (rcInfo >= X_BUILD_RcMax) {
            return ref;
        } else {
            newRcInfo = rcInfo + X_BUILD_RcOne;
        }
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return ref;
}

void _XRefRelease(XRef _Nonnull ref, const char * _Nonnull func) {
    _XObjectCompressedBase * cbase = (_XObjectCompressedBase *)ref;
    _Atomic(XFastUInt) * rcInfoPtr = &(cbase->rcInfo);
    XFastUInt rcInfo = atomic_load(rcInfoPtr);
    XFastUInt newRcInfo = 0;
    
    static const char * releaseError = "ref";
    
    if ((rcInfo & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
        if ((rcInfo & X_BUILD_CompressedRcTypeMask) == X_BUILD_CompressedTypeWeakStorageRcFlag) {
            return _XWeakPackageRelease(ref);
        }
        do {
            rcInfo = atomic_load(rcInfoPtr);
            XAssert(((rcInfo & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag), func, releaseError);
            
            if (rcInfo < X_BUILD_RcBase) {
                XAssert(false, func, releaseError);
            }
            if (rcInfo >= X_BUILD_RcMax) {
                return;
            } else {
                newRcInfo = rcInfo - X_BUILD_RcOne;
            }
        } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
        
        if (rcInfo < X_BUILD_CompressedRcBase) {
            //do dealloc

        }
    } else {
        do {
            rcInfo = atomic_load(rcInfoPtr);
            XAssert(((rcInfo & X_BUILD_CompressedRcMask) != X_BUILD_CompressedRcFlag), func, releaseError);
            
            if (rcInfo < X_BUILD_RcBase) {
                XAssert(false, func, releaseError);
            }
            if (rcInfo >= X_BUILD_RcMax) {
                return;
            } else {
                newRcInfo = rcInfo - X_BUILD_RcOne;
                if (newRcInfo < X_BUILD_RcBase) {
                    if ((rcInfo & X_BUILD_RcHasWeakMask) != X_BUILD_RcHasWeakFlag) {
                        //noWeak, 跳过X_BUILD_RcWillDealloc
                        newRcInfo -= X_BUILD_RcOne;
                    }
                }
            }
        } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
        
        if (rcInfo < X_BUILD_RcWillDealloc) {
            //do dealloc

        } else if (rcInfo < X_BUILD_RcBase) {
            //will dealloc
            
        }
    }
}


#pragma mark - Allocator

XSize XAllocatorAlignedSize(XSize size) {
    XSize s = (size + 15) & (~X_BUILD_UInt(0xf));
    XAssert(s >= size, __func__, "");
    return s;
}

XPtr _Nonnull _XAllocatorMemoryAllocate(XSize size, const char * _Nonnull func) {
    XSize s = XAllocatorAlignedSize(size);
    XAssert(s >= size, func, "");
    XPtr r = XAlignedAllocate(size, 16);
    XAssert(NULL != r, func, "");
    return r;
}
void _XAllocatorMemoryDeallocate(XPtr _Nonnull ptr, const char * _Nonnull func) {
    XAssert(NULL != ptr, func, "");
    XDeallocate(ptr);
}

XPtr _Nonnull _XAllocatorConstantAllocate(_XAllocatorPtr _Nonnull allocator, XSize size) {
    abort();
}
void _XAllocatorConstantDeallocate(_XAllocatorPtr _Nonnull allocator, XPtr _Nonnull ptr) {
    abort();
}

XObject _Nonnull _XAllocatorConstantObjectAllocate(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag) {
    abort();
}
void _XAllocatorConstantObjectDeallocate(_XAllocatorPtr _Nonnull allocator, XObject _Nonnull obj) {
    abort();
}



XPtr _Nonnull _XAllocatorDefaultAllocate(_XAllocatorPtr _Nonnull allocator, XSize size) {
    assert(allocator);
    return _XAllocatorMemoryAllocate(size, __func__);
}
void _XAllocatorDefaultDeallocate(_XAllocatorPtr _Nonnull allocator, XPtr _Nonnull ptr) {
    assert(allocator);
    return _XAllocatorMemoryDeallocate(ptr, __func__);
}

XObject _Nonnull _XAllocatorDefaultObjectAllocate(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag) {
    XAssert(allocator != NULL, __func__, "");
    
    XUInt type = XCompressedTypeOfClass(cls);
    XAssert(type > XCompressedTypeMax, __func__, "class error");

    
    _XObjectBase * ref = _XAllocatorMemoryAllocate(contentSize + sizeof(_XObjectBase), __func__);

    atomic_store(&(ref->typeInfo), (uintptr_t)cls);
    atomic_store(&(ref->rcInfo), X_BUILD_RcBase);
    /*
    TaggedIsa64
    refType: 2, value = 2
    taggedContent: 61 {
       isa: 6
       counter: 55
    }
    flag: 1, value = 1
    */
    return ref;
}
void _XAllocatorDefaultObjectDeallocate(_XAllocatorPtr _Nonnull allocator, XObject _Nonnull obj) {
    
    
}


XPtr _Nonnull _XAllocatorCompressedAllocate(_XAllocatorPtr _Nonnull allocator, XSize size) {
    XAssert(allocator == &_XCompressedObjectAllocator, __func__, "");
    return _XAllocatorMemoryAllocate(size, __func__);
}
void _XAllocatorCompressedDeallocate(_XAllocatorPtr _Nonnull allocator, XPtr _Nonnull ptr) {
    XAssert(allocator == &_XCompressedObjectAllocator, __func__, "");
    return _XAllocatorMemoryDeallocate(ptr, __func__);
}

typedef XRef _Nonnull (*XRefAllocate11_f)(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag);

XRef _Nonnull _XAllocatorCompressedObjectAllocate(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag) {
    XAssert(allocator == &_XCompressedObjectAllocator, __func__, "");
    _XObjectCompressedBase * ref = _XAllocatorMemoryAllocate(contentSize + sizeof(_XObjectCompressedBase), __func__);

    XUInt type = XCompressedTypeOfClass(cls);
    XAssert(type <= XCompressedTypeMax, __func__, "class error");

#if BUILD_TARGET_RT_64_BIT
    
    /*
    TaggedIsa64
    refType: 2, value = 2
    taggedContent: 61 {
       isa: 6
       counter: 55
    }
    flag: 1, value = 1
    */
    
    type = type << X_BUILD_TaggedObjectHeaderClassShift;
    XUInt rc = 0;
    if ((XObjectRcFlagStatic | flag) == XObjectRcFlagStatic) {
        rc = X_BUILD_RcMax;
    } else {
        rc = X_BUILD_RcBase;
    }
    uintptr_t t = X_BUILD_TaggedObjectHeaderFlag | type | rc;
    atomic_store(&(ref->rcInfo), t);
#else
    atomic_store(&(ref->typeInfo), (uintptr_t)cls);
    atomic_store(&(ref->rcInfo), XCompressedRcBase);
#endif
    
    return ref;
}
void _XAllocatorCompressedObjectDeallocate(_XAllocatorPtr _Nonnull allocator, XObject _Nonnull obj) {
    XAssert(allocator == &_XCompressedObjectAllocator, __func__, "");

    
}




const _XAllocator_s _XCompressedObjectAllocator = {
    .context = NULL,
    .headerSize = sizeof(_XObjectCompressedBase),
    .allocate = _XAllocatorCompressedAllocate,
    .deallocate = _XAllocatorCompressedDeallocate,
    .allocateRef = _XAllocatorCompressedObjectAllocate,
    .deallocateRef = _XAllocatorCompressedObjectDeallocate,
};


const _XAllocator_s _XObjectAllocator = {
    .context = NULL,
    .headerSize = sizeof(_XObjectBase),
    .allocate = _XAllocatorDefaultAllocate,
    .deallocate = _XAllocatorDefaultDeallocate,
    .allocateRef = _XAllocatorDefaultObjectAllocate,
    .deallocateRef = _XAllocatorDefaultObjectDeallocate,
};


//const _XAllocator_s _XClassAllocator = {
//    .context = NULL,
//    .headerSize = sizeof(_XObjectBase),
//    .allocate = _XAllocatorDefaultAllocate,
//    .deallocate = _XAllocatorDefaultDeallocate,
//    .allocateRef = _XAllocatorDefaultObjectAllocate,
//    .deallocateRef = _XAllocatorDefaultObjectDeallocate,
//};

const _XAllocator_s _XConstantClassAllocator = {
    .context = NULL,
    .headerSize = sizeof(_XObjectBase),
    .allocate = _XAllocatorConstantAllocate,
    .deallocate = _XAllocatorConstantDeallocate,
    .allocateRef = _XAllocatorConstantObjectAllocate,
    .deallocateRef = _XAllocatorConstantObjectDeallocate,
};

const _XAllocator_s _XConstantAllocator = {
    .context = NULL,
    .headerSize = sizeof(_XObjectBase),
    .allocate = _XAllocatorConstantAllocate,
    .deallocate = _XAllocatorConstantDeallocate,
    .allocateRef = _XAllocatorConstantObjectAllocate,
    .deallocateRef = _XAllocatorConstantObjectDeallocate,
};
