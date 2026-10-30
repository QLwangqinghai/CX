
#include "XRuntimeInternal.h"

//析构中， 不允许retain
#define XInfo_CountOne (SIZE_C(0x1) << XInfo_ObjectCountShift)

// 非正常的对象，还未析构，只可以在weaktable锁中 tryretain，不可以retain， rc==XInfo_CountTwo时， 不可以设置weak标记， 只可以清除
// 正常的对象，此时如果release，直接跳到 XInfo_CountOne， 进入析构流程； weakstorage中清除XObject_UsingWeakStorageFlag标记，并且设置NUll
#define XInfo_CountTwo (SIZE_C(0x2) << XInfo_ObjectCountShift)

/// 静态区/堆区 可变对象，
#define XInfo_CountStatic (XInfo_ObjectCountMask - XInfo_CountOne)
#define XInfo_CountNonRelease (XInfo_ObjectCountMask - XInfo_CountTwo)

static inline size_t ___XAllocatorDefaultGetZoneInfo(size_fast_t rc) {
    return (rc & XInfo_ZoneInfoMask) >> XInfo_ZoneInfoShift;
}

void _XObjectDispatchDeinitAndDealloc(XClassRef _Nonnull cls, XObjectBase_o * _Nonnull base, size_t zoneInfo) {
    XAssert(cls->deinit, "");
    cls->deinit(base);
    cls->allocator->deallocate(cls, base, zoneInfo);
}

/// 分发函数
void __XObjectDeallocate(XClassRef _Nonnull cls, XObjectRef _Nonnull ref, size_t zoneInfo) {
    XAssert(cls->allocator == (XAllocator_s *)&_XAllocatorDefault, "");
    XInstanceDeallocate(ref, zoneInfo);
#if XAllocator_Log_Verbose
    XLog("dealloc.obj[%p] ", ref);
#endif
}

static void __XObjectBaseInit(XObjectBase_o * _Nonnull base, XClassRef _Nonnull cls, XObjectOption flag, size_t layout, size_t zoneInfo) {
    XAssert(zoneInfo <= XZoneInfoMax, "");
    size_t count = 0;
    if ((XObjectOptionStatic & flag) == XObjectOptionStatic) {
        count = XInfo_CountStatic;
    } else {
        count = XInfo_CountTwo;
    }
    
    base->_cls = cls;
    size_t mark = cls->allowWeak ? XInfo_MarkObject : XInfo_MarkObjectStrongOnly;
    size_t _xinfo = (zoneInfo << XInfo_ZoneInfoShift) | (layout << XInfo_LayoutShift) | count | mark;
    atomic_store(&(base->_xinfo), _xinfo);
}

/// 分发函数
XObjectRef _Nonnull __XClassAllocateInstance(XClassRef _Nonnull cls, XObjectOption flag, size_t size, size_t layout) {
    XAssert(cls, "cls null");
    XAssert(layout <= XInfo_LayoutMax, "layout error");
    XAssert(cls->allocator == (XAllocator_s *)&_XAllocatorDefault, "");
    XAssert(size >= cls->instanceSize, "");
    XAssert(size > 0, "");
    
    XAllocatorOption option = 0;
    if (flag & XObjectOptionStatic) {
        option |= XAllocatorOptionStatic;
    }
    
    size_t zoneInfo = 0;
    XRootObject_o * object = (XRootObject_o *)XInstanceAllocate(option, size, &zoneInfo);
    __XObjectBaseInit(&(object->_runtime), cls, flag, layout, zoneInfo);
    if (size > sizeof(XObjectBase_o)) {
        memset(object->content, 0, size - sizeof(XObjectBase_o));
    }
#if XAllocator_Log_Verbose
    XLog("alloc.obj[%p:%s]  size: %lu", object, cls->name, size);
#endif
    return (XObjectRef)object;
}

XObjectRef _Nullable _XWeakStorageRetainObject(XClassRef _Nonnull cls, XObjectRef _Nonnull obj, _XWeakStorage_o * _Nonnull weakStorage) {
    _Atomic(size_fast_t) * rcInfoPtr = &(weakStorage->_originalXinfoe);
    size_fast_t rcInfo = atomic_load(rcInfoPtr);
    size_fast_t newRcInfo = 0;

    do {
        rcInfo = atomic_load(rcInfoPtr);
        XAssert(XInfo_MarkObjectUsingWeakStorage == (rcInfo & XInfo_MarkMask), "");
        size_fast_t oldCount = rcInfo & XInfo_ObjectCountMask;
        XAssertFunc(oldCount >= XInfo_CountTwo, __func__, "object is deiniting");
        if (oldCount >= XInfo_CountNonRelease) {
            return obj;
        }
        newRcInfo = (rcInfo & (~XInfo_ObjectCountMask)) | (oldCount + XInfo_CountOne);
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return obj;
}

void _XWeakStorageReleaseObject(XClassRef _Nonnull cls, XObjectRef _Nonnull obj, _XWeakStorage_o * _Nonnull weakStorage) {
    _Atomic(size_fast_t) * rcInfoPtr = &(weakStorage->_originalXinfoe);
    size_fast_t rcInfo = atomic_load(rcInfoPtr);
    size_fast_t newRcInfo = 0;
    size_fast_t newCount = 0;
    do {
        rcInfo = atomic_load(rcInfoPtr);
        XAssert(XInfo_MarkObjectUsingWeakStorage == (rcInfo & XInfo_MarkMask), "");
        
        size_fast_t oldCount = rcInfo & XInfo_ObjectCountMask;
        XAssertFunc(oldCount >= XInfo_CountTwo, __func__, "object is deiniting");

        if (oldCount >= XInfo_CountNonRelease) {
            return;
        }
        newCount = oldCount - XInfo_CountOne;
        newRcInfo = (rcInfo & (~XInfo_ObjectCountMask)) | newCount;
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    
    /// 对象在_xinfo < 2 && hasWeak == false时， 进行析构
    if (newCount == XInfo_CountOne) {
        do {
            rcInfo = atomic_load(rcInfoPtr);
            XAssert(XInfo_MarkObjectUsingWeakStorage == (rcInfo & XInfo_MarkMask), "");
            size_fast_t oldCount = rcInfo & XInfo_ObjectCountMask;
            XAssert(oldCount == XInfo_CountOne, "object must be deiniting");
            newRcInfo = (rcInfo & (~XInfo_MarkMask)) | XInfo_MarkObject;
        } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));

        uintptr_t original = (uintptr_t)NULL;
        do {
            original = atomic_load(&(weakStorage->original));
            XAssert(original == (uintptr_t)obj, "");
        } while (!atomic_compare_exchange_strong(&(weakStorage->original), &original, (uintptr_t)NULL));
        
        XObjectBase_o * originalObj = (XObjectBase_o *)obj;
        size_fast_t originalObjXinfoe = 0;
        do {
            originalObjXinfoe = atomic_load(&(originalObj->_xinfo));
            XAssert(originalObjXinfoe == ((uintptr_t)weakStorage | XInfo_MarkObjectUsingWeakStorage), "");
        } while (!atomic_compare_exchange_strong(&(originalObj->_xinfo), &originalObjXinfoe, newRcInfo));
        
        
        //do dealloc
        _XObjectDispatchDeinitAndDealloc(cls, obj, ___XAllocatorDefaultGetZoneInfo(newRcInfo));
        
        // obj 解除 对 weakStorage 的引用
        XObjectRelease(weakStorage);
    }
}

XObjectRef _Nullable _XAllocatorRetainObject(XClassRef _Nonnull cls, XObjectRef _Nonnull _cbase) {
    XObjectBase_o * cbase = (XObjectBase_o *)_cbase;
    _Atomic(size_fast_t) * rcInfoPtr = &(cbase->_xinfo);
    
    size_fast_t rcInfo = atomic_load(rcInfoPtr);
    size_fast_t newRcInfo = 0;
    do {
        rcInfo = atomic_load(rcInfoPtr);
        if (XInfo_MarkObjectUsingWeakStorage == (rcInfo & XInfo_MarkMask)) {
            _XWeakStorage_o * weakStorage = (_XWeakStorage_o *)(uintptr_t)(rcInfo & (~XInfo_MarkMask));
            return _XWeakStorageRetainObject(cls, _cbase, weakStorage);
        }
        XAssert(XInfo_MarkNotXObject != (rcInfo & XInfo_MarkMask), "");
        size_fast_t oldCount = rcInfo & XInfo_ObjectCountMask;
        XAssertFunc(oldCount >= XInfo_CountTwo, __func__, "object is deiniting");
        
        if (oldCount >= XInfo_CountNonRelease) {
            return _cbase;
        }
        newRcInfo = (rcInfo & (~XInfo_ObjectCountMask)) | (oldCount + XInfo_CountOne);
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return _cbase;
}

void _XAllocatorReleaseObject(XClassRef _Nonnull cls, XObjectRef _Nonnull _cbase) {
    XObjectBase_o * cbase = (XObjectBase_o *)_cbase;
    _Atomic(size_fast_t) * rcInfoPtr = &(cbase->_xinfo);

    size_fast_t rcInfo = atomic_load(rcInfoPtr);
    size_fast_t newRcInfo = 0;
    size_fast_t newCount = 0;

    do {
        rcInfo = atomic_load(rcInfoPtr);
        if (XInfo_MarkObjectUsingWeakStorage == (rcInfo & XInfo_MarkMask)) {
            _XWeakStorage_o * weakStorage = (_XWeakStorage_o *)(uintptr_t)(rcInfo & (~XInfo_MarkMask));
            _XWeakStorageReleaseObject(cls, _cbase, weakStorage);
            return;
        }
        XAssert(XInfo_MarkNotXObject != (rcInfo & XInfo_MarkMask), "");
        size_fast_t oldCount = rcInfo & XInfo_ObjectCountMask;
        XAssertFunc(oldCount >= XInfo_CountTwo, __func__, "object is deiniting");
        if (oldCount >= XInfo_CountNonRelease) {
            return;
        }
        newCount = oldCount - XInfo_CountOne;
        newRcInfo = (rcInfo & (~XInfo_ObjectCountMask)) | newCount;
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    
    if (newCount == XInfo_CountOne) {
        //do dealloc
        _XObjectDispatchDeinitAndDealloc(cls, _cbase, ___XAllocatorDefaultGetZoneInfo(newRcInfo));
    }
}

_XWeakStorage_o * _Nonnull _XWeakStorageCreateWithHeapObject(_XObject_o * _Nonnull object) {
    _XWeakStorage_o * created = NULL;
    
    XObjectBase_o * cbase = (XObjectBase_o *)object;
    _Atomic(size_fast_t) * rcInfoPtr = &(cbase->_xinfo);

    size_fast_t rcInfo = 0;
    size_fast_t newRcInfo = 0;

    do {
        rcInfo = atomic_load(rcInfoPtr);
        if (XInfo_MarkObjectUsingWeakStorage == (rcInfo & XInfo_MarkMask)) {
            _XWeakStorage_o * weakStorage = (_XWeakStorage_o *)(uintptr_t)(rcInfo & (~XInfo_MarkMask));
            if (created) {
                atomic_store(&(created->original), (uintptr_t)NULL);
                atomic_store(&(created->_originalXinfoe), 0);
                XObjectRelease(created);
                created = NULL;
            }
            return XObjectRetain(weakStorage);
        }
        XAssert(XInfo_MarkObject == (rcInfo & XInfo_MarkMask), "");

        if (created == NULL) {
            created = __XClassAllocateInstance(XWeakStorageClass, 0, sizeof(_XWeakStorage_o), 0);
            XAssert(0 == ((uintptr_t)created & XInfo_MarkMask), "");
        }

        atomic_store(&(created->original), (uintptr_t)object);
        atomic_store(&(created->_originalXinfoe), (rcInfo & (~XInfo_MarkMask)) | XInfo_MarkObjectUsingWeakStorage);
        
        size_fast_t oldCount = rcInfo & XInfo_ObjectCountMask;
        XAssertFunc(oldCount >= XInfo_CountTwo, __func__, "object is deiniting");
        newRcInfo = (size_fast_t)(uintptr_t)created | XInfo_MarkObjectUsingWeakStorage;
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return XObjectRetain(created);
}

XObjectRef _Nullable _XWeakStorageTakeRetainedObject(_XWeakStorage_o * _Nonnull weakStorage, const char * _Nonnull func) {
    _Atomic(size_fast_t) * rcInfoPtr = &(weakStorage->_originalXinfoe);
    size_fast_t rcInfo = 0;
    size_fast_t newRcInfo = 0;
    do {
        rcInfo = atomic_load(rcInfoPtr);
        if (XInfo_MarkObjectUsingWeakStorage != (rcInfo & XInfo_MarkMask)) {
            return NULL;
        }
        size_fast_t oldCount = rcInfo & XInfo_ObjectCountMask;
        if (oldCount < XInfo_CountTwo) {
            return NULL;
        }
        if (oldCount >= XInfo_CountNonRelease) {
            return (XObjectRef)atomic_load(&(weakStorage->original));
        }
        newRcInfo = (rcInfo & (~XInfo_ObjectCountMask)) | (oldCount + XInfo_CountOne);
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return (XObjectRef)atomic_load(&(weakStorage->original));
}

size_t _XAllocatorDefaultGetInstanceSize(XClassRef _Nonnull cls, XObjectRef _Nonnull _cbase) {
    return cls->instanceSize;
}

const XAllocator_s _XAllocatorDefault = {
    .context = NULL,
    .allocate = __XClassAllocateInstance,
    .deallocate = __XObjectDeallocate,
    .retain = _XAllocatorRetainObject,
    .release = _XAllocatorReleaseObject,
    .getInstanceSize = _XAllocatorDefaultGetInstanceSize,
};

#undef XInfo_CountOne
#undef XInfo_CountTwo
#undef XInfo_CountThree
#undef XInfo_CountStatic
#undef XInfo_CountNonRelease
