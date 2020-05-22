//
//  XWeakStorage.c
//  X
//
//  Created by clf on 2020/5/21.
//  Copyright © 2020 haoqi. All rights reserved.
//

#include "internal/XRuntimeInternal.h"
#include <pthread.h>


typedef struct {
    XUInt addressMask;
    _XWeakTable tables[0];
} _XWeakTableManager;

static _XWeakTableManager * _Nullable __XWeakTableManagerShared = NULL;
void __XWeakTableManagerOnceBlockFunc(void) {
    
}
_XWeakTableManager * _Nonnull _XWeakTableManagerShared(void) {
    static pthread_once_t token = PTHREAD_ONCE_INIT;
    pthread_once(&token, &__XWeakTableManagerOnceBlockFunc);
    assert(__XWeakTableManagerShared);
    return __XWeakTableManagerShared;
}

_XWeakTable * _Nonnull _XWeakTableGet(uintptr_t address) {
    _XWeakTableManager * manager = _XWeakTableManagerShared();
    uintptr_t v = address;
#if BUILD_TARGET_RT_64_BIT
    v = address >> X_BUILD_UInt(3);
#else
    v = address >> X_BUILD_UInt(2);
#endif
    v = (v & manager->addressMask);
    return &(manager->tables[v]);
}

static XBool _XWeakStorageSetObjectWeakFlag(_XObject * _Nonnull object, const char * _Nonnull func) {
    _Atomic(XFastUInt) * rcInfoPtr = &(object->_runtime.rcInfo);
    XFastUInt rcInfo = atomic_load(rcInfoPtr);
    XFastUInt newRcInfo = 0;
    
    static const char * releaseError = "ref";
    do {
        rcInfo = atomic_load(rcInfoPtr);
        XAssert(((rcInfo & X_BUILD_CompressedRcMask) != X_BUILD_CompressedRcFlag), func, releaseError);
        
        if (rcInfo < X_BUILD_RcBase) {
            XAssert(false, func, releaseError);
        }
        newRcInfo = rcInfo | X_BUILD_RcHasWeakFlag;

        if (newRcInfo == rcInfo) {
            return false;
        }
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return true;
}


static XBool _XWeakStorageClearObjectWeakFlag(_XObject * _Nonnull object, const char * _Nonnull func) {
    _Atomic(XFastUInt) * rcInfoPtr = &(object->_runtime.rcInfo);
    XFastUInt rcInfo = atomic_load(rcInfoPtr);
    XFastUInt newRcInfo = 0;
    
    static const char * releaseError = "ref";
    do {
        rcInfo = atomic_load(rcInfoPtr);
        XAssert(((rcInfo & X_BUILD_CompressedRcMask) != X_BUILD_CompressedRcFlag), func, releaseError);
        
        if (rcInfo < X_BUILD_RcDeallocing) {
            XAssert(false, func, releaseError);
        }
        newRcInfo = rcInfo & (~X_BUILD_RcHasWeakMask);

        if (newRcInfo == rcInfo) {
            return false;
        }
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return true;
}


/*
 if ((uintptr_t)NULL == table) {
 newRcInfo -= X_BUILD_CompressedRcOne;
 }
 */

void _XWeakTableLock(_XWeakTable * _Nonnull table) {

}
void _XWeakTableUnlock(_XWeakTable * _Nonnull table) {
    
}

static _WeakStorage * _XWeakTableGetItem(_XWeakTable * _Nonnull table, uintptr_t key) {
    
    return NULL;
}

static void _XWeakTableAdd(_XWeakTable * _Nonnull table, _WeakStorage * _Nonnull item, const char * _Nonnull func) {
    XAssert(_XWeakStorageSetObjectWeakFlag((_XObject *)item->content.value, func), func, "");
    //必须找不到value

    //添加

    
    //最后执行
    atomic_store(&(item->content.table), (uintptr_t)table);
}

static void _XWeakTableRemove(_XWeakTable * _Nonnull table, _WeakStorage * _Nonnull item, const char * _Nonnull func) {
    //必须找到item
    
    
    XAssert(_XWeakStorageClearObjectWeakFlag((_XObject *)item->content.value, func), func, "");
    //从map中移除
    

    //最后执行
    atomic_store(&(item->content.table), (uintptr_t)NULL);
}

static void _XWeakTableTryRemoveItem(_XWeakTable * _Nonnull table, _WeakStorage * _Nonnull item, const char * _Nonnull func) {
    uintptr_t tableAddress = atomic_load(&(item->content.table));
    if ((_XWeakTable *)tableAddress != table) {
        return;
    }
    _XWeakTableRemove(table, item, func);
}


_WeakStorage * _Nonnull _XWeakStorageCreate(_XObject * _Nonnull value) {
    uintptr_t key = (uintptr_t)value;

    _XWeakTable * table = _XWeakTableGet(key);
    _XWeakTableLock(table);
    _WeakStorage * item = _XWeakTableGetItem(table, key);
    if (NULL != item) {
        item = XRefRetain(item);
    } else {

    }
    _XWeakTableUnlock(table);
    return item;
}
XWeakStorageRef _Nonnull XWeakStorageCreate(XObject _Nonnull object) {
    _XObject * value = NULL;
    return _XWeakStorageCreate(value);
}


XObject _Nullable _XWeakStorageTakeRetainedValue(_WeakStorage * _Nonnull weakStorage, const char * _Nonnull func) {
    uintptr_t tableAddress = atomic_load(&(weakStorage->content.table));
    _XWeakTable * table = (_XWeakTable *)tableAddress;
    if (NULL == table) {
        return NULL;
    }
    XObject result = NULL;
    uintptr_t key = weakStorage->content.value;
    _XWeakTableLock(table);
    if (weakStorage == _XWeakTableGetItem(table, key)) {
        result = _XRefRetain((XRef)(key), func);
    }
    _XWeakTableUnlock(table);
    return result;
}


void _XWeakPackageRelease(_WeakStorage * _Nonnull weakStorage) {
    _Atomic(XFastUInt) * rcInfoPtr = &(weakStorage->_runtime.rcInfo);
    XFastUInt rcInfo = 0;
    XFastUInt newRcInfo = 0;
    static const char * releaseError = "ref";

    uintptr_t tableAddress = atomic_load(&(weakStorage->content.table));
    _XWeakTable * table = (_XWeakTable *)tableAddress;
    //normal -> to dealloc 需要加锁
    XBool locked = false;
    
    do {
        rcInfo = atomic_load(rcInfoPtr);
        if (rcInfo < X_BUILD_RcBase) {
            if (locked) {
                _XWeakTableUnlock(table);
                locked = false;
            }
            XAssert(false, __func__, releaseError);
        } else if (rcInfo >= X_BUILD_RcMax) {
            if (locked) {
                _XWeakTableUnlock(table);
                locked = false;
            }
            return;
        }
        newRcInfo = rcInfo - X_BUILD_RcOne;

        if (newRcInfo < X_BUILD_RcBase) {
            if (NULL != table && !locked) {
                _XWeakTableLock(table);
                locked = true;
            }
        } else {
            if (locked) {
                _XWeakTableUnlock(table);
                locked = false;
            }
        }
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    
    if (locked) {
        _XWeakTableTryRemoveItem(table, weakStorage, __func__);
        _XWeakTableUnlock(table);
        goto dealloc;
    } else if (newRcInfo < X_BUILD_RcBase) {
        goto dealloc;
    }
    
dealloc:;
}


_WeakStorage * _Nonnull _XWeakPackageRetain(_WeakStorage * _Nonnull weakStorage) {
//    if (rcInfo < X_BUILD_RcBase + X_BUILD_RcOne) {
//        XAssert(false, __func__, releaseError);
//    }

    
    
    return weakStorage;
//    _Atomic(XFastUInt) * rcInfoPtr = &(weakStorage->_runtime.rcInfo);
//    XFastUInt rcInfo = 0;
//    XFastUInt newRcInfo = 0;
//    static const char * releaseError = "ref";
//
//    do {
//        rcInfo = atomic_load(rcInfoPtr);
//        if (rcInfo < X_BUILD_RcBase + X_BUILD_RcOne) {
//            XAssert(false, __func__, releaseError);
//        }
//        if (rcInfo >= X_BUILD_RcMax) {
//            return;
//        } else {
//            newRcInfo = rcInfo - X_BUILD_RcOne;
//        }
//    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
//
//    if (rcInfo < X_BUILD_CompressedRcBase + X_BUILD_CompressedRcOne) {
//        //will dealloc
//        uintptr_t table = atomic_load(&(weakStorage->content.table));
//
//        if ((uintptr_t)NULL != table) {
//            newRcInfo -= X_BUILD_CompressedRcOne;
//        }
//    }
//    if (rcInfo < X_BUILD_RcWillDealloc) {
//        //do dealloc
//
//    } else if (rcInfo < X_BUILD_CompressedRcBase + X_BUILD_RcOne) {
//        //will dealloc
//        uintptr_t value = atomic_load(&(weakStorage->content.value));
//        if ((uintptr_t)NULL == value) {
//
//        }
//    }
}



void _XWeakTableTryRemove(_XWeakTable * _Nonnull table, XObject _Nonnull value) {
    _WeakStorage * weakStorage = _XWeakTableGetItem(table, (uintptr_t)value);
    if (weakStorage) {
        _XWeakTableTryRemoveItem(table, weakStorage, __func__);
    }
}
