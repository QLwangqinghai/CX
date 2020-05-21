//
//  XWeakStorage.c
//  X
//
//  Created by clf on 2020/5/21.
//  Copyright © 2020 haoqi. All rights reserved.
//

#include "internal/XRuntimeInternal.h"

typedef struct {
    
    
    
} _XWeakTable;

/*
 if ((uintptr_t)NULL == table) {
 newRcInfo -= X_BUILD_CompressedRcOne;
 }
 */

void _XWeakTableLock(_XWeakTable * _Nonnull table) {

}
void _XWeakTableUnlock(_XWeakTable * _Nonnull table) {
    
}

static XBool _XWeakTableFind(_XWeakTable * _Nonnull table, _WeakStorage * _Nonnull item) {
    
    return true;
}

static void _XWeakTableRemove(_XWeakTable * _Nonnull table, _WeakStorage * _Nonnull item, const char * _Nonnull func) {
    uintptr_t tableAddress = atomic_load(&(item->content.table));
    if ((_XWeakTable *)tableAddress != table) {
        return;
    }
    
    //必须找到item
    
    
    //从map中移除
    

    //最后执行
    atomic_store(&(item->content.value), (uintptr_t)NULL);
    atomic_store(&(item->content.table), (uintptr_t)NULL);
}


XObject _Nullable _XWeakStorageTakeRetainedValue(_WeakStorage * _Nonnull weakStorage, const char * _Nonnull func) {
    uintptr_t tableAddress = atomic_load(&(weakStorage->content.table));
    _XWeakTable * table = (_XWeakTable *)tableAddress;
    if (NULL == table) {
        return NULL;
    }
    uintptr_t valueAddress = atomic_load(&(weakStorage->content.value));
    if ((uintptr_t)NULL == valueAddress) {
        return NULL;
    }
    XObject result = NULL;
    _XWeakTableLock(table);
    if (_XWeakTableFind(table, weakStorage)) {
        valueAddress = atomic_load(&(weakStorage->content.value));
        result = _XRefRetain((XRef)valueAddress, func);
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
            XAssert(false, __func__, releaseError);
        } else if (rcInfo < X_BUILD_RcBase + X_BUILD_RcOne) {
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
       
        if (rcInfo >= X_BUILD_RcMax) {
            if (locked) {
                _XWeakTableUnlock(table);
                locked = false;
            }
            return;
        } else {
            newRcInfo = rcInfo - X_BUILD_RcOne;
        }
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    
    if (locked) {
        _XWeakTableRemove(table, weakStorage, __func__);
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
