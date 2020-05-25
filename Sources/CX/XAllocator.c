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


#pragma mark - rc


void _XCompressedDispatchDeinit(XHeapRef _Nonnull ref, XCompressedType type, const char * _Nonnull func) {

}


void _XObjectDispatchDeinit(_XObject * _Nonnull ref, const XObjectType_s * type, const char * _Nonnull func) {
    
}




XRef _Nonnull _XRefRetain(XHeapRef _Nonnull ref, const char * _Nonnull func) {
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

void _XRefRelease(XHeapRef _Nonnull ref, const char * _Nonnull func) {
    _XObjectCompressedBase * cbase = (_XObjectCompressedBase *)ref;
    _Atomic(XFastUInt) * rcInfoPtr = &(cbase->rcInfo);
    XFastUInt rcInfo = atomic_load(rcInfoPtr);
    XFastUInt newRcInfo = 0;
    
    static const char * releaseError = "ref";
    if ((rcInfo & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
        if ((rcInfo & X_BUILD_CompressedRcTypeMask) == X_BUILD_CompressedTypeWeakPackageRcFlag) {
            return _XWeakPackageRelease(ref);
        }
        do {
            rcInfo = atomic_load(rcInfoPtr);
            XAssert(((rcInfo & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag), func, releaseError);
            
            if (rcInfo < X_BUILD_CompressedRcBase) {
                XAssert(false, func, releaseError);
            }
            if (rcInfo >= X_BUILD_CompressedRcMax) {
                return;
            } else {
                newRcInfo = rcInfo - X_BUILD_CompressedRcOne;
            }
        } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
        
        if (rcInfo < X_BUILD_CompressedRcBase) {
            //do dealloc
            XCompressedType type = ((newRcInfo & X_BUILD_CompressedRcTypeMask) >> X_BUILD_CompressedRcTypeShift);
            _XCompressedDispatchDeinit(ref, type, func);
        }
    } else {
        const XObjectType_s * type = NULL;
        XBool locked = false;
        _XWeakTable * table = _XWeakTableGet((uintptr_t)ref);
        do {
            rcInfo = atomic_load(rcInfoPtr);
            XAssert(((rcInfo & X_BUILD_CompressedRcMask) != X_BUILD_CompressedRcFlag), func, releaseError);
            
            if (rcInfo < X_BUILD_RcBase) {
                XAssert(false, func, releaseError);
            }
            if (rcInfo >= X_BUILD_RcMax) {
                if (locked) {
                    _XWeakTableUnlock(table);
                    locked = false;
                }
                return;
            } else {
                newRcInfo = rcInfo - X_BUILD_RcOne;
                if (newRcInfo < X_BUILD_RcBase) {
                    if ((newRcInfo & X_BUILD_RcHasWeakMask) == X_BUILD_RcHasWeakFlag) {
                        //clearWeak
                        if (!locked) {
                            _XWeakTableLock(table);
                            locked = true;
                        }
                    } else {
                        if (locked) {
                            _XWeakTableUnlock(table);
                            locked = false;
                        }
                    }
                } else {
                    if (locked) {
                      _XWeakTableUnlock(table);
                        locked = false;
                    }
                }
            }
        } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
        if (locked) {
            //clear weak
            _XWeakTableTryRemove(table, (XObject)ref);
            _XWeakTableUnlock(table);
            type = _XObjectGetClass((_XObject *)ref, func);
            _XObjectDispatchDeinit((_XObject *)ref, type, func);
        } else if (rcInfo < X_BUILD_RcBase) {
            type = _XObjectGetClass((_XObject *)ref, func);
            _XObjectDispatchDeinit((_XObject *)ref, type, func);
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

    
    XObjectBase_s * ref = _XAllocatorMemoryAllocate(contentSize + sizeof(XObjectBase_s), __func__);

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


XPtr _Nonnull _XAllocatorCompressedMemoryAllocate(_XAllocatorPtr _Nonnull allocator, XSize size) {
    XAssert(allocator == &_XCollectionAllocator, __func__, "");
    return _XAllocatorMemoryAllocate(size, __func__);
}
void _XAllocatorCompressedMemoryDeallocate(_XAllocatorPtr _Nonnull allocator, XPtr _Nonnull ptr) {
    XAssert(allocator == &_XCollectionAllocator, __func__, "");
    return _XAllocatorMemoryDeallocate(ptr, __func__);
}

typedef XRef _Nonnull (*XRefAllocate11_f)(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag);

XRef _Nonnull _XAllocatorCompressedAllocate(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag) {
    XAssert(allocator == &_XCollectionAllocator, __func__, "");
    _XObjectCompressedBase * ref = _XAllocatorMemoryAllocate(contentSize + sizeof(_XObjectCompressedBase), __func__);

    XUInt type = XCompressedTypeOfClass(cls);
    XAssert(type <= XCompressedTypeMax, __func__, "class error");
    
    /* compressed == true
     counter
     type: 6
     compressed: 1
     */
    
    type = type << X_BUILD_CompressedRcTypeShift;
    XUInt rc = 0;
    if ((XObjectRcFlagStatic | flag) == XObjectRcFlagStatic) {
        rc = X_BUILD_CompressedRcMax;
    } else {
        rc = X_BUILD_RcBase;
    }
    uintptr_t t = X_BUILD_CompressedRcFlag | type | rc;
    atomic_store(&(ref->rcInfo), t);
    
    return ref;
}
void _XAllocatorCollectionDeallocate(_XAllocatorPtr _Nonnull allocator, XObject _Nonnull obj) {
    XAssert(allocator == &_XCollectionAllocator, __func__, "");

    
}


const _XAllocator_s _XCollectionAllocator = {
    .context = NULL,
    .headerSize = sizeof(_XObjectCompressedBase),
    .allocate = _XAllocatorCompressedMemoryAllocate,
    .deallocate = _XAllocatorCompressedMemoryDeallocate,
    .allocateRef = _XAllocatorCompressedAllocate,
    .deallocateRef = _XAllocatorCollectionDeallocate,
};

const _XAllocator_s _XValueAllocator = {
    .context = NULL,
    .headerSize = sizeof(_XObjectCompressedBase),
    .allocate = _XAllocatorCompressedMemoryAllocate,
    .deallocate = _XAllocatorCompressedMemoryDeallocate,
    .allocateRef = _XAllocatorCompressedAllocate,
    .deallocateRef = _XAllocatorCollectionDeallocate,
};

const _XAllocator_s _XObjectAllocator = {
    .context = NULL,
    .headerSize = sizeof(XObjectBase_s),
    .allocate = _XAllocatorDefaultAllocate,
    .deallocate = _XAllocatorDefaultDeallocate,
    .allocateRef = _XAllocatorDefaultObjectAllocate,
    .deallocateRef = _XAllocatorDefaultObjectDeallocate,
};


//const _XAllocator_s _XClassAllocator = {
//    .context = NULL,
//    .headerSize = sizeof(XObjectBase_s),
//    .allocate = _XAllocatorDefaultAllocate,
//    .deallocate = _XAllocatorDefaultDeallocate,
//    .allocateRef = _XAllocatorDefaultObjectAllocate,
//    .deallocateRef = _XAllocatorDefaultObjectDeallocate,
//};



const _XAllocator_s _XWeakPackageAllocator = {
    .context = NULL,
    .headerSize = sizeof(_XObjectCompressedBase),
    .allocate = _XAllocatorCompressedMemoryAllocate,
    .deallocate = _XAllocatorCompressedMemoryDeallocate,
    .allocateRef = _XAllocatorCompressedAllocate,
    .deallocateRef = _XAllocatorCollectionDeallocate,
};
