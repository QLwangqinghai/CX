
#include "XOrderedHashTable.h"

#pragma mark - XOrderedMap

extern const XClass_o _XOrderedMapClass;

XImmutableOrderedHashTable_s __XImmutableOrderedMapEmpty = {
    ._runtime = XObjectBaseMakeStaticStrongOnly(&_XOrderedMapClass),
    ._hashCode = ATOMIC_VAR_INIT(0),
    .count = 0,
    .bucketCount = 0,
    .bucketIndexShift = SIZE_BITS_COUNT - 1,
};

typedef struct {
    ssize_t (*_Nonnull getCount)(XOrderedHashTableRef _Nonnull table);
    XObjectRef _Nullable (*_Nonnull getValue)(XOrderedMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain);
    bool_t (*_Nonnull setValue)(XOrderedHashTableRef _Nonnull table, XMapElement_s * _Nonnull element, XMapElement_s * _Nonnull oldElementBuffer);
    bool_t (*_Nonnull remove)(XOrderedHashTableRef _Nonnull table, XObjectRef _Nullable key, bool_t allowReduceCapacity, XMapElement_s * _Nonnull oldElementBuffer);
    XOrderedHashTableRef _Nonnull (*_Nonnull removeAll)(XOrderedHashTableRef _Nonnull table, bool_t allowReduceCapacity);
    void (*resize)(XOrderedMapRef _Nonnull map, ssize_t minCapacity);
    void (*_Nonnull enumerate)(XOrderedHashTableRef _Nonnull table, bool_t reverse, XMapEnumerate_f _Nonnull func, void * _Nullable context);
    XOrderedHashTableIter_s (*_Nonnull makeIter)(XOrderedHashTableRef _Nonnull table, bool_t reverse);

    XObjectRef _Nonnull (*_Nonnull copy)(XOrderedHashTableRef _Nonnull table);
    void (*_Nonnull deinit)(XOrderedHashTableRef _Nonnull table);
    size_t (*_Nonnull getHashCode)(XOrderedHashTableRef _Nonnull table);
    size_t (*_Nonnull getQuickHashCode)(XOrderedHashTableRef _Nonnull table);
} _XOrderedMapApi_s;

void _XOrderedHashTableEnumerateOrderedMap(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable context, bool_t * _Nonnull stop) {
    XMapEnumerate_f func = (XMapEnumerate_f)subfunc;
    XMapElement_s * e = (XMapElement_s *)element;
    func(index, e->key, e->value, context, stop);
}

const _XOrderedMapApi_s _XOrderedHashTableApiImmutableOrderedMap;
const _XOrderedMapApi_s _XOrderedHashTableApiMutableOrderedMap;

const _XOrderedMapApi_s * _Nullable _XOrderedMapApiTable[XInfo_LayoutCount] = {
    NULL,
    &_XOrderedHashTableApiImmutableOrderedMap,
    &_XOrderedHashTableApiMutableOrderedMap,
};


const _XOrderedMapApi_s * _Nonnull __XOrderedMapGetApi(XOrderedMapRef _Nonnull map) {
    const  _XOrderedMapApi_s * api = _XOrderedMapApiTable[XObjectGetLayout(map)];
    XAssert(api, "");
    return api;
}

void __XOrderedMapEnumerateHash(ssize_t index, XObjectRef _Nullable key, XObjectRef _Nullable value, void * _Nullable context, bool_t * _Nonnull stop) {
    XCollectionHasher_s * hasher = (XCollectionHasher_s *)context;
    size_t hashCode = XObjectGetHashCode(key);
    XCollectionHasherCombine(hasher, index, hashCode ^ XObjectGetHashCode(value));
}

size_t __XOrderedMapHash(const _XOrderedMapApi_s * _Nonnull api, XObjectRef _Nonnull obj) {
    XCollectionHasher_s hasher = {};
    ssize_t count = api->getCount(obj);
    XCollectionHasherInit(&hasher, (size_t)count);
    XOrderedMapEnumerate(obj, false, __XOrderedMapEnumerateHash, &hasher);
    return XCollectionHasherFinalize(&hasher);
}

ssize_t XOrderedMapGetCount(XOrderedMapRef _Nonnull map) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    return __XOrderedMapGetApi(map)->getCount(map);
}

/// return unretained object
XObjectRef _Nullable XOrderedMapGetAssignValue(XOrderedMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    return api->getValue(map, key, isContain);
}

/// return retained object
XObjectRef _Nullable XOrderedMapGetValue(XOrderedMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    XObjectRef result = api->getValue(map, key, isContain);
    return XObjectRetain(result);
}

void XOrderedMapEnumerate(XOrderedMapRef _Nonnull map, bool_t reverse, XMapEnumerate_f _Nonnull func, void * _Nullable context) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    api->enumerate(map, reverse, func, context);
}
XOrderedHashTableIter_s XOrderedMapMakeIter(XOrderedMapRef _Nonnull map, bool_t reverse) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    return api->makeIter(map, reverse);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t XMutableOrderedMapSetValue(XOrderedMapRef _Nonnull map, XObjectRef _Nullable value, XObjectRef _Nullable key, XMapElement_s * _Nullable old) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    XMapElement_s element = {};
    XMapElement_s newElement = {
        .value = XObjectCopy(value),
        .key = XObjectCopy(key)
    };

    bool_t hasOld = api->setValue(map, &newElement, &element);
    if (hasOld) {
        if (old) {
            memcpy(old, &element, sizeof(XMapElement_s));
        } else {
            XObjectRelease(element.key);
            XObjectRelease(element.value);
        }
    } else {
        if (old) {
            memset(old, 0, sizeof(XMapElement_s));
        }
    }
    return hasOld;
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t XMutableOrderedMapRemoveValue(XOrderedMapRef _Nonnull map, XObjectRef _Nullable key, bool_t allowReduceCapacity, XMapElement_s * _Nullable old) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    XMapElement_s element = {};
    bool_t hasOld = api->remove(map, key, allowReduceCapacity, &element);
    if (hasOld) {
        if (old) {
            memcpy(old, &element, sizeof(XMapElement_s));
        } else {
            XObjectRelease(element.key);
            XObjectRelease(element.value);
        }
    } else {
        if (old) {
            memset(old, 0, sizeof(XMapElement_s));
        }
    }
    return hasOld;
}

void XMutableOrderedMapRemoveAll(XOrderedMapRef _Nonnull map, bool_t allowReduceCapacity, XOrderedMapRef _Nonnull * _Nullable old) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    XOrderedMapRef removed = api->removeAll(map, allowReduceCapacity);
    if (old) {
        *old = removed;
    } else {
        XObjectRelease(removed);
    }
}
void XMutableOrderedMapResize(XOrderedMapRef _Nonnull map, ssize_t minCapacity) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    api->resize(map, minCapacity);
}


size_t _XOrderedMapGetHashCode(XObjectRef _Nonnull map) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    return api->getHashCode(map);
}
void _XOrderedMapDeinit(XObjectRef _Nonnull map)  {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    api->deinit(map);
}

bool_t _XOrderedMapEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    const _XOrderedMapApi_s * lapi = __XOrderedMapGetApi(lhs);
    const _XOrderedMapApi_s * rapi = __XOrderedMapGetApi(rhs);
    size_t lhashcode = lapi->getQuickHashCode(lhs);
    size_t rhashcode = rapi->getQuickHashCode(rhs);
    if (0 != lhashcode && 0 != rhashcode && lhashcode != rhashcode) {
        return false;
    }
    
    ssize_t count = lapi->getCount(lhs);
    if (count != rapi->getCount(rhs)) {
        return false;
    }
    
    XOrderedHashTableIter_s liter = lapi->makeIter(lhs, false);
    XOrderedHashTableIter_s riter = rapi->makeIter(rhs, false);
    
    for (ssize_t i=0; i<count; i++) {
        XMapElement_s * le = XOrderedHashTableIterNext(&liter);
        XMapElement_s * re = XOrderedHashTableIterNext(&riter);
        XAssert(le, "");
        XAssert(re, "");
        if (!XMapElementEqual(le, re)) {
            return false;
        }
    }
    
    XAssert(NULL == XOrderedHashTableIterNext(&liter), "");
    XAssert(NULL == XOrderedHashTableIterNext(&riter), "");
    return true;
}

void _XOrderedMapDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XOrderedMapDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

XObjectRef _Nonnull _XOrderedMapCopy(XObjectRef _Nonnull map) {
    XAssert(XObjectGetClass(map) == XOrderedMapClass, "");
    const _XOrderedMapApi_s * api = __XOrderedMapGetApi(map);
    return api->copy(map);
}

#pragma mark - immutable

ssize_t _XImmutableOrderedMapGetCount(XOrderedMapRef _Nonnull map) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)map;
    return table->count;
}

/// return unretained object
XObjectRef _Nullable _XImmutableOrderedMapGetValue(XOrderedMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)map;
    XMapElement_s element = {};
    bool_t contains = XImmutableOrderedHashTableGetElement(table, &__XMapElementType, &key, &element);
    if (isContain) {
        *isContain = contains;
    }
    return element.value;
}

void _XImmutableOrderedMapEnumerate(XOrderedMapRef _Nonnull map, bool_t reverse, XMapEnumerate_f _Nonnull func, void * _Nullable context) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)map;
    XImmutableOrderedHashTableEnumerate(table, &__XMapElementType, reverse, _XOrderedHashTableEnumerateOrderedMap, func, context);
}

XObjectRef _Nonnull _XImmutableOrderedMapCopy(XOrderedMapRef _Nonnull map) {
    return XObjectRetain(map);
}
XObjectRef _Nonnull _XImmutableOrderedMapCopyAndRelease(XObjectRef _Nonnull map) {
    return map;
}

void _XImmutableOrderedMapDeinit(XOrderedMapRef _Nonnull map) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)map;
    XImmutableOrderedHashTableDeinit(table, &__XMapElementType, _XMapElementDeinit);
}
size_t _XImmutableOrderedMapGetHashCode(XObjectRef _Nonnull self) {
    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
    size_t code = atomic_load(&(obj->_hashCode));
    if (0 == code) {
        code = __XOrderedMapHash(&_XOrderedHashTableApiImmutableOrderedMap, obj);
        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
    }
    return code;
}
size_t _XImmutableOrderedMapGetQuickHashCode(XObjectRef _Nonnull self) {
    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
    return atomic_load(&(obj->_hashCode));
}
XOrderedHashTableIter_s _XImmutableOrderedMapMakeIter(XOrderedMapRef _Nonnull self, bool_t reverse) {
    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
    return XImmutableOrderedHashTableMakeIter(obj, reverse);
}
#pragma mark - mutable

ssize_t _XMutableOrderedMapGetCount(XOrderedMapRef _Nonnull map) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    return table->count;
}
/// return unretained object
XObjectRef _Nullable _XMutableOrderedMapGetValue(XOrderedMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    XMapElement_s element = {};
    bool_t contains = XMutableOrderedHashTableGetElement(table, &__XMapElementType, &key, &element);
    if (isContain) {
        *isContain = contains;
    }
    return element.value;
}
/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableOrderedMapSetValue(XOrderedMapRef _Nonnull map, XMapElement_s * _Nonnull element, XMapElement_s * _Nonnull old) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    return XMutableOrderedHashTableReplace(table, &__XMapElementType, element, old);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableOrderedMapRemoveValue(XOrderedMapRef _Nonnull map, XObjectRef _Nullable key, bool_t allowReduceCapacity, XMapElement_s * _Nonnull old) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    return XMutableOrderedHashTableRemove(table, &__XMapElementType, &key, allowReduceCapacity, old);
}

XOrderedMapRef _Nonnull _XMutableOrderedMapRemoveAll(XOrderedMapRef _Nonnull map, bool_t allowReduceCapacity) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    return (XOrderedMapRef)XMutableOrderedHashTableRemoveAll(table, &__XMapElementType, allowReduceCapacity, 0);
}
void _XMutableOrderedMapResize(XOrderedMapRef _Nonnull map, ssize_t minCapacity) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    XMutableOrderedHashTableResize(table, &__XMapElementType, minCapacity);
}
void _XMutableOrderedMapEnumerate(XOrderedMapRef _Nonnull map, bool_t reverse, XMapEnumerate_f _Nonnull func, void * _Nullable context) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    XMutableOrderedHashTableEnumerate(table, &__XMapElementType, reverse, _XOrderedHashTableEnumerateOrderedMap, func, context);
}

XObjectRef _Nonnull _XMutableOrderedMapCopy(XOrderedMapRef _Nonnull map) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    if (XMutableOrderedHashTableGetCount(table) > 0) {
        return XMutableOrderedHashTableCopy(table, &__XMapElementType, 0, _XMapElementCopy);
    } else {
        return &__XImmutableOrderedMapEmpty;
    }
}
XObjectRef _Nonnull _XMutableOrderedMapCopyAndRelease(XOrderedMapRef _Nonnull map) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    if (XMutableOrderedHashTableGetCount(table) > 0) {
        XObjectRef r = XMutableOrderedHashTableCopy(table, &__XMapElementType, 0, _XMapElementCopy);
        XObjectRelease(map);
        return r;
    } else {
        XObjectRelease(map);
        return &__XImmutableOrderedMapEmpty;
    }
}

void _XMutableOrderedMapDeinit(XOrderedMapRef _Nonnull map) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    XMutableOrderedHashTableDeinit(table, &__XMapElementType, _XMapElementDeinit);
}

size_t _XMutableOrderedMapGetHashCode(XObjectRef _Nonnull self) {
    return __XOrderedMapHash(&_XOrderedHashTableApiMutableOrderedMap, self);
}
size_t _XMutableOrderedMapGetQuickHashCode(XObjectRef _Nonnull self) {
    return 0;
}
XOrderedHashTableIter_s _XMutableOrderedMapMakeIter(XOrderedMapRef _Nonnull self, bool_t reverse) {
    XMutableOrderedHashTable_s * obj = (XMutableOrderedHashTable_s *)self;
    return XMutableOrderedHashTableMakeIter(obj, reverse);
}
const _XOrderedMapApi_s _XOrderedHashTableApiImmutableOrderedMap = {
    .getCount = _XImmutableOrderedMapGetCount,
    .getValue = _XImmutableOrderedMapGetValue,
    .enumerate = _XImmutableOrderedMapEnumerate,
    .makeIter = _XImmutableOrderedMapMakeIter,
    .copy = _XImmutableOrderedMapCopy,
    .deinit = _XImmutableOrderedMapDeinit,
    .getHashCode = _XImmutableOrderedMapGetHashCode,
    .getQuickHashCode = _XImmutableOrderedMapGetQuickHashCode,
};
const _XOrderedMapApi_s _XOrderedHashTableApiMutableOrderedMap = {
    .getCount = _XMutableOrderedMapGetCount,
    .getValue = _XMutableOrderedMapGetValue,
    .setValue = _XMutableOrderedMapSetValue,
    .remove = _XMutableOrderedMapRemoveValue,
    .removeAll = _XMutableOrderedMapRemoveAll,
    .enumerate = _XMutableOrderedMapEnumerate,
    .makeIter = _XMutableOrderedMapMakeIter,
    .copy = _XMutableOrderedMapCopy,
    .deinit = _XMutableOrderedMapDeinit,
    .getHashCode = _XMutableOrderedMapGetHashCode,
    .getQuickHashCode = _XMutableOrderedMapGetQuickHashCode,
    .resize = _XMutableOrderedMapResize,
};








// -----------------Immutable---------------

/// create immutable map,
XOrderedMapRef _Nonnull XOrderedMapCreateWithValueKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableOrderedMapEmpty;
    }
    
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedMapClass, 0, &__XMapElementType, count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef value = va_arg(ap, XObjectRef);
        XObjectRef key = va_arg(ap, XObjectRef);
        XMapElement_s item = {
            .value = XObjectCopy(value),
            .key = XObjectCopy(key),
        };
        XMapElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    
    XImmutableOrderedHashTable_s * result = XMutableOrderedHashTableRemoveAll(table, &__XMapElementType, false, option);
    XObjectRelease(table);
    return result;
}

XOrderedMapRef _Nonnull XOrderedMapCreateWithValuesAndKeys(XObjectOption option, XArrayRef _Nonnull values, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(values);
    XAssert(count == XArrayGetCount(keys), "");
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableOrderedMapEmpty;
    }
    
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedMapClass, 0, &__XMapElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XMapElement_s item = {
            .value = XObjectCopy(XArrayGetObject(values, i)),
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XMapElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    
    XImmutableOrderedHashTable_s * result = XMutableOrderedHashTableRemoveAll(table, &__XMapElementType, false, option);
    XObjectRelease(table);
    return result;
}

// ------------------- Mutable ----------------------------

/// create mutable array

XOrderedMapRef _Nonnull XMutableOrderedMapCreateWithValueKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedMapClass, option, &__XMapElementType, count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef value = va_arg(ap, XObjectRef);
        XObjectRef key = va_arg(ap, XObjectRef);
        XMapElement_s item = {
            .value = XObjectCopy(value),
            .key = XObjectCopy(key),
        };
        XMapElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    return table;
}

XOrderedMapRef _Nonnull XMutableOrderedMapCreate(XObjectOption option, ssize_t capacity) {
    return XMutableOrderedHashTableCreate(XOrderedMapClass, option, &__XMapElementType, capacity);
}

XOrderedMapRef _Nonnull XMutableOrderedMapCreateWithValuesAndKeys(XObjectOption option, XArrayRef _Nonnull values, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(values);
    XAssert(count == XArrayGetCount(keys), "");
    XAssert(count >= 0, "");
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedMapClass, option, &__XMapElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XMapElement_s item = {
            .value = XObjectCopy(XArrayGetObject(values, i)),
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XMapElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    return table;
}

void __XMutableOrderedMapCreateWithOrderedMapEnumerate(ssize_t index, XObjectRef _Nullable key, XObjectRef _Nullable value, void * _Nullable context, bool_t * _Nonnull stop) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)context;
    XMapElement_s item = {
        .value = XObjectCopy(value),
        .key = XObjectCopy(key),
    };
    XMapElement_s tmp = {};
    bool_t existed = XMutableOrderedHashTableReplace(table, &__XMapElementType, &item, &tmp);
    XAssert(!existed, "");
}

XOrderedMapRef _Nonnull XMutableOrderedMapCreateWithOrderedMap(XObjectOption option, XOrderedMapRef _Nonnull map) {
    XAssert(map, "");
    ssize_t count = XOrderedMapGetCount(map);
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedMapClass, option, &__XMapElementType, count);
    XOrderedMapEnumerate(map, false, __XMutableOrderedMapCreateWithOrderedMapEnumerate, table);
    return table;
}











































//
//typedef struct {
//    size_t hashCode;
//    size_t index;
//    size_t count;
//    XMapElement_s * _Nonnull entities;
//} _XOrderedMapPage_s;
//typedef struct {
//    size_t count;
//    size_t offset;
//    size_t nextHashCode;
//
//    /// 分法查找， hash+二分查找
//    XMapElement_s * _Nonnull entities;
//} _XOrderedMapPageIter_s;
//
//void _XOrderedMapPageIterInit(_XOrderedMapPageIter_s * _Nonnull iter, _XOrderedMap_s * _Nonnull map) {
//    iter->count = map->count;
////    iter->entities = __XOrderedMapGetItems(map);
//    iter->offset = 0;
//    if (map->count > 0) {
//        iter->nextHashCode = XObjectGetHashCode(iter->entities[0].key);
//    }
//}
//
//bool_t _XOrderedMapPageIterNext(_XOrderedMapPageIter_s * _Nonnull iter, _XOrderedMapPage_s * _Nonnull page) {
//    if (iter->count > iter->offset) {
//        page->entities = iter->entities + iter->offset;
//        page->index = iter->offset;
//        page->hashCode = iter->nextHashCode;
//        for (size_t idx=iter->offset+1; idx<iter->count; idx++) {
//            size_t hashCode = XObjectGetHashCode(iter->entities[idx].key);
//            XAssert(hashCode >= page->hashCode, "");
//            if (hashCode != page->hashCode) {
//                iter->offset = idx;
//                iter->nextHashCode = hashCode;
//                page->count = iter->offset - page->index;
//                return true;
//            }
//        }
//        iter->offset = iter->count;
//        iter->nextHashCode = 0;
//        page->count = iter->offset - page->index;
//        return true;
//    } else {
//        page->count = 0;
//        page->index = iter->count;
//        page->hashCode = 0;
//        page->entities = NULL;
//        return false;
//    }
//}
//
//bool_t _XOrderedMapEntitiesEqual(XMapElement_s * _Nonnull lhs, XMapElement_s * _Nonnull rhs, size_t count) {
//    // 单向链表
//    for (size_t idx=0; idx<count; idx++) {
//        XObjectRef rvalue = NULL;
//        bool_t found = false;
//        for (size_t ridx=0; ridx<count; ridx++) {
//            if (XObjectEqual(lhs[idx].key, rhs[ridx].key)) {
//                rvalue = rhs[ridx].value;
//                found = true;
//                break;
//            }
//        }
//        if (found) {
//            if (!XObjectEqual(lhs[idx].value, rvalue)) {
//                return false;
//            }
//        } else {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool_t _XOrderedMapPageEqual(_XOrderedMapPage_s * _Nonnull lhs, _XOrderedMapPage_s * _Nonnull rhs) {
//    XAssert(lhs->count > 0, "");
//    XAssert(rhs->count > 0, "");
//    if (lhs->count != rhs->count || lhs->hashCode != rhs->hashCode || lhs->index != rhs->index) {
//        return false;
//    }
//    size_t count = lhs->count;
//    if (count == 1) {
//        return XObjectEqual(lhs->entities[0].key, rhs->entities[0].key) && XObjectEqual(lhs->entities[0].value, rhs->entities[0].value);
//    } else if (count == 2) {
//        if (XObjectEqual(lhs->entities[0].key, rhs->entities[0].key)) {
//            return XObjectEqual(lhs->entities[1].key, rhs->entities[1].key) && XObjectEqual(lhs->entities[0].value, rhs->entities[0].value) && XObjectEqual(lhs->entities[1].value, rhs->entities[1].value);
//        } else if (XObjectEqual(lhs->entities[0].key, rhs->entities[1].key)) {
//            return XObjectEqual(lhs->entities[1].key, rhs->entities[0].key) && XObjectEqual(lhs->entities[0].value, rhs->entities[1].value) && XObjectEqual(lhs->entities[1].value, rhs->entities[0].value);
//        } else {
//            return false;
//        }
//    } else {
//        return _XOrderedMapEntitiesEqual(lhs->entities, rhs->entities, count);
//    }
//}
//
//

//#pragma mark - XSet
//
//typedef struct {
//    size_t hashCode;
//    size_t index;
//    size_t count;
//    XObjectRef _Nullable * _Nonnull entities;
//} _XBaseHashPage_s;
//typedef struct {
//    size_t count;
//    size_t offset;
//    size_t nextHashCode;
//
//    /// 分法查找， hash+二分查找
//    XObjectRef _Nullable * _Nonnull entities;
//} _XBaseHashPageIter_s;
//
//void _XSetPageIterInit(_XBaseHashPageIter_s * _Nonnull iter, _XSet_s * _Nonnull map) {
//    iter->count = map->count;
////    iter->entities = __XSetGetItems(map);
//    iter->offset = 0;
//    if (map->count > 0) {
//        iter->nextHashCode = XObjectGetHashCode(iter->entities);
//    }
//}
//
//bool_t _XSetPageIterNext(_XBaseHashPageIter_s * _Nonnull iter, _XBaseHashPage_s * _Nonnull page) {
//    if (iter->count > iter->offset) {
//        page->entities = iter->entities + iter->offset;
//        page->index = iter->offset;
//        page->hashCode = iter->nextHashCode;
//        for (size_t idx=iter->offset+1; idx<iter->count; idx++) {
//            size_t hashCode = XObjectGetHashCode(iter->entities);
//            XAssert(hashCode >= page->hashCode, "");
//            if (hashCode != page->hashCode) {
//                iter->offset = idx;
//                iter->nextHashCode = hashCode;
//                page->count = iter->offset - page->index;
//                return true;
//            }
//        }
//
//        iter->offset = iter->count;
//        iter->nextHashCode = 0;
//        page->count = iter->offset - page->index;
//        return true;
//    } else {
//        page->count = 0;
//        page->index = iter->count;
//        page->hashCode = 0;
//        page->entities = NULL;
//        return false;
//    }
//}
//
//bool_t _XSetEntitiesEqual(XObjectRef * _Nonnull lhs, XObjectRef * _Nonnull rhs, size_t count) {
//    // 单向链表
//    for (size_t idx=0; idx<count; idx++) {
//        bool_t found = false;
//        for (size_t ridx=0; ridx<count; ridx++) {
//            if (XObjectEqual(lhs[idx], rhs[ridx])) {
//                found = true;
//                break;
//            }
//        }
//        if (!found) {
//            return false;
//        }
//    }
//    return true;
//}
//
//bool_t _XSetPageEqual(_XBaseHashPage_s * _Nonnull lhs, _XBaseHashPage_s * _Nonnull rhs) {
//    XAssert(lhs->count > 0, "");
//    XAssert(rhs->count > 0, "");
//    if (lhs->count != rhs->count || lhs->hashCode != rhs->hashCode || lhs->index != rhs->index) {
//        return false;
//    }
//    size_t count = lhs->count;
//    if (count == 1) {
//        return XObjectEqual(lhs->entities[0], rhs->entities[0]);
//    } else if (count == 2) {
//        if (XObjectEqual(lhs->entities[0], rhs->entities[0])) {
//            return XObjectEqual(lhs->entities[1], rhs->entities[1]);
//        } else if (XObjectEqual(lhs->entities[0], rhs->entities[1])) {
//            return XObjectEqual(lhs->entities[1], rhs->entities[0]);
//        } else {
//            return false;
//        }
//    } else {
//        return _XSetEntitiesEqual(lhs->entities, rhs->entities, count);
//    }
//}
//
//void _XSetDeinit(XObjectRef _Nonnull self)  {
//    _XSet_s * obj = (_XSet_s *)self;
////    XObjectRef * entities = __XSetGetItems(obj);
////    for (size_t i=0; i<obj->count; i++) {
////        XObjectRelease(entities[i]);
////        entities[i] = NULL;
////    }
//    obj->count = 0;
//}
//
//void __XSetEnumerateHash(ssize_t index, XObjectRef _Nullable key, void * _Nullable context, bool_t * _Nonnull stop) {
//    XCollectionHasher_s * hasher = (XCollectionHasher_s *)context;
//    size_t hashCode = XObjectGetHashCode(key);
//    XCollectionHasherCombine(hasher, hashCode, hashCode);
//}
//
//size_t __XSetHash(const _XOrderedMapApi_s * _Nonnull api, XObjectRef _Nonnull obj) {
//    XCollectionHasher_s hasher = {};
//    ssize_t count = api->getCount(obj);
//    XCollectionHasherInit(&hasher, (size_t)count);
//    XOrderedMapEnumerate(obj, __XOrderedMapEnumerateHash, &hasher);
//    return XCollectionHasherFinalize(&hasher);
//}
//
//size_t _XImmutableSetGetHashCode(XObjectRef _Nonnull self) {
//    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
//    size_t code = atomic_load(&(obj->_hashCode));
//    if (0 == code) {
//        code = __XSetHash(&_XOrderedHashTableApiImmutableSet, self);
//        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
//    }
//    return code;
//}
//size_t _XImmutableSetGetQuickHashCode(XObjectRef _Nonnull self) {
//    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
//    return atomic_load(&(obj->_hashCode));
//}
//
//size_t _XMutableSetGetHashCode(XObjectRef _Nonnull self) {
//    return __XSetHash(&_XOrderedHashTableApiMutableSet, self);
//}
//size_t _XMutableSetGetQuickHashCode(XObjectRef _Nonnull self) {
//    return 0;
//}
//bool_t _XSetEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
//    const _XOrderedMapApi_s * lapi = __XSetGetApi(lhs);
//    const _XOrderedMapApi_s * rapi = __XSetGetApi(rhs);
//    size_t lhashcode = lapi->getQuickHashCode(lhs);
//    size_t rhashcode = rapi->getQuickHashCode(rhs);
//    if (0 != lhashcode && 0 != rhashcode && lhashcode != rhashcode) {
//        return false;
//    }
//
//    ssize_t count = lapi->getCount(lhs);
//    if (count != rapi->getCount(rhs)) {
//        return false;
//    }
//    for (ssize_t i=0; i<count; i++) {
////        XObjectRef lhsobj = lapi->getObject(lhs, i);
////        XObjectRef rhsobj = rapi->getObject(rhs, i);
////        if (!XObjectEqual(lhsobj, rhsobj)) {
////            return false;
////        }
//    }
//    return true;
//}
//void _XSetDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
//void _XSetDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
//
//
//
//
//
//
//



const XClass_o _XOrderedMapClass = XClassMakeXDefault(XOrderedMap, 0);
XClassRef _Nonnull XOrderedMapClass = &_XOrderedMapClass;
