#include "XHashTable.h"

#pragma mark - XMap

// 放到数组时 是否发生copy
extern const XClass_o _XMapClass;

XImmutableHashTable_s __XImmutableMapEmpty = {
    ._runtime = XObjectBaseMakeStaticStrongOnly(&_XMapClass),
    ._hashCode = ATOMIC_VAR_INIT(0),
    .count = 0,
    .bucketCount = 0,
    .bucketIndexShift = SIZE_BITS_COUNT - 1,
};

typedef struct {
    ssize_t (*_Nonnull getCount)(XHashTableRef _Nonnull table);
    XObjectRef _Nullable (*_Nonnull getValue)(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain);
    bool_t (*_Nonnull setValue)(XHashTableRef _Nonnull table, XMapElement_s * _Nonnull element, XMapElement_s * _Nonnull oldElementBuffer);
    bool_t (*_Nonnull remove)(XHashTableRef _Nonnull table, XObjectRef _Nullable key, bool_t allowReduceCapacity, XMapElement_s * _Nonnull oldElementBuffer);
    XHashTableRef _Nonnull (*_Nonnull removeAll)(XHashTableRef _Nonnull table, bool_t allowReduceCapacity);
    void (*resize)(XMapRef _Nonnull map, ssize_t minCapacity);

    void (*_Nonnull enumerate)(XHashTableRef _Nonnull table, XMapEnumerate_f _Nonnull func, void * _Nullable context);
    XObjectRef _Nonnull (*_Nonnull copy)(XHashTableRef _Nonnull table);
    void (*_Nonnull deinit)(XHashTableRef _Nonnull table);
    size_t (*_Nonnull getHashCode)(XHashTableRef _Nonnull table);
    size_t (*_Nonnull getQuickHashCode)(XHashTableRef _Nonnull table);
} _XMapApi_s;

void _XHashTableEnumerateMap(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable context, bool_t * _Nonnull stop) {
    XMapEnumerate_f func = (XMapEnumerate_f)subfunc;
    XMapElement_s * e = (XMapElement_s *)element;
    func(index, e->key, e->value, context, stop);
}


const _XMapApi_s _XHashTableApiImmutableMap;
const _XMapApi_s _XHashTableApiMutableMap;

const _XMapApi_s * _Nullable _XMapApiTable[XInfo_LayoutCount] = {
    NULL,
    &_XHashTableApiImmutableMap,
    &_XHashTableApiMutableMap,
};


const _XMapApi_s * _Nonnull __XMapGetApi(XMapRef _Nonnull map) {
    const  _XMapApi_s * api = _XMapApiTable[XObjectGetLayout(map)];
    XAssert(api, "");
    return api;
}

void __XMapEnumerateHash(ssize_t index, XObjectRef _Nullable key, XObjectRef _Nullable value, void * _Nullable context, bool_t * _Nonnull stop) {
    XCollectionHasher_s * hasher = (XCollectionHasher_s *)context;
    size_t hashCode = XObjectGetHashCode(key);
    XCollectionHasherCombine(hasher, hashCode, hashCode ^ XObjectGetHashCode(value));
}

size_t __XMapHash(const _XMapApi_s * _Nonnull api, XObjectRef _Nonnull obj) {
    XCollectionHasher_s hasher = {};
    ssize_t count = api->getCount(obj);
    XCollectionHasherInit(&hasher, (size_t)count);
    XMapEnumerate(obj, __XMapEnumerateHash, &hasher);
    return XCollectionHasherFinalize(&hasher);
}

ssize_t XMapGetCount(XMapRef _Nonnull map) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    return __XMapGetApi(map)->getCount(map);
}

/// return unretained object
XObjectRef _Nullable XMapGetAssignValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    return api->getValue(map, key, isContain);
}

/// return retained object
XObjectRef _Nullable XMapGetValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    XObjectRef result = api->getValue(map, key, isContain);
    return XObjectRetain(result);
}

void XMapEnumerate(XMapRef _Nonnull map, XMapEnumerate_f _Nonnull func, void * _Nullable context) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    api->enumerate(map, func, context);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t XMutableMapSetValue(XMapRef _Nonnull map, XObjectRef _Nullable value, XObjectRef _Nullable key, XMapElement_s * _Nullable old) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
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
bool_t XMutableMapRemoveValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t allowReduceCapacity, XMapElement_s * _Nullable old) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
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

void XMutableMapRemoveAll(XMapRef _Nonnull map, bool_t allowReduceCapacity, XMapRef _Nonnull * _Nullable old) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    XMapRef removed = api->removeAll(map, allowReduceCapacity);
    if (old) {
        *old = removed;
    } else {
        XObjectRelease(removed);
    }
}
void XMutableMapResize(XMapRef _Nonnull map, ssize_t minCapacity) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    api->resize(map, minCapacity);
}


size_t _XMapGetHashCode(XObjectRef _Nonnull map) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    return api->getHashCode(map);
}
void _XMapDeinit(XObjectRef _Nonnull map)  {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    api->deinit(map);
}

typedef struct {
    ssize_t equalCount;
    XObjectRef _Nonnull map;
} _XMapEqualContext_s;

void _XMapEqualEnumerate(ssize_t index, XObjectRef _Nullable key, XObjectRef _Nullable value, void * _Nullable context, bool_t * _Nonnull stop) {
    _XMapEqualContext_s * ctx = (_XMapEqualContext_s *)context;
    
    bool_t contain = false;
    XObjectRef v = XMapGetAssignValue(ctx->map, key, &contain);
    if (!contain || !XObjectEqual(value, v)) {
        *stop = true;
    } else {
        ctx->equalCount += 1;
    }
}


bool_t _XMapEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    const _XMapApi_s * lapi = __XMapGetApi(lhs);
    const _XMapApi_s * rapi = __XMapGetApi(rhs);
    size_t lhashcode = lapi->getQuickHashCode(lhs);
    size_t rhashcode = rapi->getQuickHashCode(rhs);
    if (0 != lhashcode && 0 != rhashcode && lhashcode != rhashcode) {
        return false;
    }
    
    ssize_t count = lapi->getCount(lhs);
    if (count != rapi->getCount(rhs)) {
        return false;
    }
    _XMapEqualContext_s context = {
        .equalCount = 0,
        .map = rhs,
    };
    lapi->enumerate(lhs, _XMapEqualEnumerate, &context);
    return context.equalCount == count;
}

void _XMapDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XMapDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

XObjectRef _Nonnull _XMapCopy(XObjectRef _Nonnull map) {
    XAssert(XObjectGetClass(map) == XMapClass, "");
    const _XMapApi_s * api = __XMapGetApi(map);
    return api->copy(map);
}

#pragma mark - immutable

ssize_t _XImmutableMapGetCount(XMapRef _Nonnull map) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)map;
    return table->count;
}

/// return unretained object
XObjectRef _Nullable _XImmutableMapGetValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)map;
    XMapElement_s element = {};
    bool_t contains = XImmutableHashTableGetElement(table, &__XMapElementType, &key, &element);
    if (isContain) {
        *isContain = contains;
    }
    return element.value;
}

void _XImmutableMapEnumerate(XMapRef _Nonnull map, XMapEnumerate_f _Nonnull func, void * _Nullable context) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)map;
    XImmutableHashTableEnumerate(table, &__XMapElementType, _XHashTableEnumerateMap, func, context);
}

XObjectRef _Nonnull _XImmutableMapCopy(XMapRef _Nonnull map) {
    return XObjectRetain(map);
}
XObjectRef _Nonnull _XImmutableMapCopyAndRelease(XMapRef _Nonnull map) {
    return map;
}
void _XImmutableMapDeinit(XMapRef _Nonnull map) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)map;
    XImmutableHashTableDeinit(table, &__XMapElementType, _XMapElementDeinit);
}
size_t _XImmutableMapGetHashCode(XObjectRef _Nonnull self) {
    XImmutableHashTable_s * obj = (XImmutableHashTable_s *)self;
    size_t code = atomic_load(&(obj->_hashCode));
    if (0 == code) {
        code = __XMapHash(&_XHashTableApiImmutableMap, obj);
        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
    }
    return code;
}
size_t _XImmutableMapGetQuickHashCode(XObjectRef _Nonnull self) {
    XImmutableHashTable_s * obj = (XImmutableHashTable_s *)self;
    return atomic_load(&(obj->_hashCode));
}

#pragma mark - mutable

ssize_t _XMutableMapGetCount(XMapRef _Nonnull map) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    return table->count;
}
/// return unretained object
XObjectRef _Nullable _XMutableMapGetValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    XMapElement_s element = {};
    bool_t contains = XMutableHashTableGetElement(table, &__XMapElementType, &key, &element);
    if (isContain) {
        *isContain = contains;
    }
    return element.value;
}
/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableMapSetValue(XMapRef _Nonnull map, XMapElement_s * _Nonnull element, XMapElement_s * _Nonnull old) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    return XMutableHashTableReplace(table, &__XMapElementType, element, old);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableMapRemoveValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t allowReduceCapacity, XMapElement_s * _Nonnull old) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    return XMutableHashTableRemove(table, &__XMapElementType, &key, allowReduceCapacity, old);
}

XMapRef _Nonnull _XMutableMapRemoveAll(XMapRef _Nonnull map, bool_t allowReduceCapacity) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    return (XMapRef)XMutableHashTableRemoveAll(table, &__XMapElementType, allowReduceCapacity, 0);
}
void _XMutableMapResize(XMapRef _Nonnull map, ssize_t minCapacity) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    XMutableHashTableResize(table, &__XMapElementType, minCapacity);
}
void _XMutableMapEnumerate(XMapRef _Nonnull map, XMapEnumerate_f _Nonnull func, void * _Nullable context) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    XMutableHashTableEnumerate(table, &__XMapElementType, _XHashTableEnumerateMap, func, context);
}

XObjectRef _Nonnull _XMutableMapCopy(XMapRef _Nonnull map) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    if (XMutableHashTableGetCount(table) > 0) {
        return XMutableHashTableCopy(table, &__XMapElementType, 0, _XMapElementCopy);
    } else {
        return &__XImmutableMapEmpty;
    }
}
XObjectRef _Nonnull _XMutableMapCopyAndRelease(XMapRef _Nonnull map) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    if (XMutableHashTableGetCount(table) > 0) {
        XObjectRef r = XMutableHashTableCopy(table, &__XMapElementType, 0, _XMapElementCopy);
        XObjectRelease(map);
        return r;
    } else {
        XObjectRelease(map);
        return &__XImmutableMapEmpty;
    }
}

void _XMutableMapDeinit(XMapRef _Nonnull map) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    XMutableHashTableDeinit(table, &__XMapElementType, _XMapElementDeinit);
}

size_t _XMutableMapGetHashCode(XObjectRef _Nonnull self) {
    return __XMapHash(&_XHashTableApiMutableMap, self);
}
size_t _XMutableMapGetQuickHashCode(XObjectRef _Nonnull self) {
    return 0;
}

const _XMapApi_s _XHashTableApiImmutableMap = {
    .getCount = _XImmutableMapGetCount,
    .getValue = _XImmutableMapGetValue,
    .enumerate = _XImmutableMapEnumerate,
    .copy = _XImmutableMapCopy,
    .deinit = _XImmutableMapDeinit,
    .getHashCode = _XImmutableMapGetHashCode,
    .getQuickHashCode = _XImmutableMapGetQuickHashCode,
};
const _XMapApi_s _XHashTableApiMutableMap = {
    .getCount = _XMutableMapGetCount,
    .getValue = _XMutableMapGetValue,
    .setValue = _XMutableMapSetValue,
    .remove = _XMutableMapRemoveValue,
    .removeAll = _XMutableMapRemoveAll,
    .enumerate = _XMutableMapEnumerate,
    .copy = _XMutableMapCopy,
    .deinit = _XMutableMapDeinit,
    .getHashCode = _XMutableMapGetHashCode,
    .getQuickHashCode = _XMutableMapGetQuickHashCode,
    .resize = _XMutableMapResize,
};








// -----------------Immutable---------------

/// create immutable map,
XMapRef _Nonnull XMapCreateWithValueKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableMapEmpty;
    }
    
    XMutableHashTable_s * table = XMutableHashTableCreate(XMapClass, 0, &__XMapElementType, count);
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
        bool_t existed = XMutableHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    
    XImmutableHashTable_s * result = XMutableHashTableRemoveAll(table, &__XMapElementType, false, option);
    XObjectRelease(table);
    return result;
}

XMapRef _Nonnull XMapCreateWithValuesAndKeys(XObjectOption option, XArrayRef _Nonnull values, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(values);
    XAssert(count == XArrayGetCount(keys), "");
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableMapEmpty;
    }
    
    XMutableHashTable_s * table = XMutableHashTableCreate(XMapClass, 0, &__XMapElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XMapElement_s item = {
            .value = XObjectCopy(XArrayGetObject(values, i)),
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XMapElement_s tmp = {};
        bool_t existed = XMutableHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    
    XImmutableHashTable_s * result = XMutableHashTableRemoveAll(table, &__XMapElementType, false, option);
    XObjectRelease(table);
    return result;
}

// ------------------- Mutable ----------------------------

/// create mutable array

XMapRef _Nonnull XMutableMapCreateWithValueKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    XMutableHashTable_s * table = XMutableHashTableCreate(XMapClass, option, &__XMapElementType, count);
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
        bool_t existed = XMutableHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    return table;
}

XMapRef _Nonnull XMutableMapCreate(XObjectOption option, ssize_t capacity) {
    return XMutableHashTableCreate(XMapClass, option, &__XMapElementType, capacity);
}

XMapRef _Nonnull XMutableMapCreateWithValuesAndKeys(XObjectOption option, XArrayRef _Nonnull values, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(values);
    XAssert(count == XArrayGetCount(keys), "");
    XAssert(count >= 0, "");
    XMutableHashTable_s * table = XMutableHashTableCreate(XMapClass, option, &__XMapElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XMapElement_s item = {
            .value = XObjectCopy(XArrayGetObject(values, i)),
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XMapElement_s tmp = {};
        bool_t existed = XMutableHashTableReplace(table, &__XMapElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    return table;
}

void __XMutableMapCreateWithMapEnumerate(ssize_t index, XObjectRef _Nullable key, XObjectRef _Nullable value, void * _Nullable context, bool_t * _Nonnull stop) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)context;
    XMapElement_s item = {
        .value = XObjectCopy(value),
        .key = XObjectCopy(key),
    };
    XMapElement_s tmp = {};
    bool_t existed = XMutableHashTableReplace(table, &__XMapElementType, &item, &tmp);
    XAssert(!existed, "");
}

XMapRef _Nonnull XMutableMapCreateWithMap(XObjectOption option, XMapRef _Nonnull map) {
    XAssert(map, "");
    ssize_t count = XMapGetCount(map);
    XMutableHashTable_s * table = XMutableHashTableCreate(XMapClass, option, &__XMapElementType, count);
    XMapEnumerate(map, __XMutableMapCreateWithMapEnumerate, table);
    return table;
}











































//
//typedef struct {
//    size_t hashCode;
//    size_t index;
//    size_t count;
//    XMapElement_s * _Nonnull entities;
//} _XMapPage_s;
//typedef struct {
//    size_t count;
//    size_t offset;
//    size_t nextHashCode;
//
//    /// 分法查找， hash+二分查找
//    XMapElement_s * _Nonnull entities;
//} _XMapPageIter_s;
//
//void _XMapPageIterInit(_XMapPageIter_s * _Nonnull iter, _XMap_s * _Nonnull map) {
//    iter->count = map->count;
////    iter->entities = __XMapGetItems(map);
//    iter->offset = 0;
//    if (map->count > 0) {
//        iter->nextHashCode = XObjectGetHashCode(iter->entities[0].key);
//    }
//}
//
//bool_t _XMapPageIterNext(_XMapPageIter_s * _Nonnull iter, _XMapPage_s * _Nonnull page) {
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
//bool_t _XMapEntitiesEqual(XMapElement_s * _Nonnull lhs, XMapElement_s * _Nonnull rhs, size_t count) {
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
//bool_t _XMapPageEqual(_XMapPage_s * _Nonnull lhs, _XMapPage_s * _Nonnull rhs) {
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
//        return _XMapEntitiesEqual(lhs->entities, rhs->entities, count);
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
//size_t __XSetHash(const _XMapApi_s * _Nonnull api, XObjectRef _Nonnull obj) {
//    XCollectionHasher_s hasher = {};
//    ssize_t count = api->getCount(obj);
//    XCollectionHasherInit(&hasher, (size_t)count);
//    XMapEnumerate(obj, __XMapEnumerateHash, &hasher);
//    return XCollectionHasherFinalize(&hasher);
//}
//
//size_t _XImmutableSetGetHashCode(XObjectRef _Nonnull self) {
//    XImmutableHashTable_s * obj = (XImmutableHashTable_s *)self;
//    size_t code = atomic_load(&(obj->_hashCode));
//    if (0 == code) {
//        code = __XSetHash(&_XHashTableApiImmutableSet, self);
//        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
//    }
//    return code;
//}
//size_t _XImmutableSetGetQuickHashCode(XObjectRef _Nonnull self) {
//    XImmutableHashTable_s * obj = (XImmutableHashTable_s *)self;
//    return atomic_load(&(obj->_hashCode));
//}
//
//size_t _XMutableSetGetHashCode(XObjectRef _Nonnull self) {
//    return __XSetHash(&_XHashTableApiMutableSet, self);
//}
//size_t _XMutableSetGetQuickHashCode(XObjectRef _Nonnull self) {
//    return 0;
//}
//bool_t _XSetEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
//    const _XMapApi_s * lapi = __XSetGetApi(lhs);
//    const _XMapApi_s * rapi = __XSetGetApi(rhs);
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





const XClass_o _XMapClass = XClassMakeXDefault(XMap, 0);
XClassRef _Nonnull XMapClass = &_XMapClass;
