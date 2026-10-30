#include "XHashTable.h"

#pragma mark - XSet

// 放到数组时 是否发生copy
extern const XClass_o _XSetClass;

XImmutableHashTable_s __XImmutableSetEmpty = {
    ._runtime = XObjectBaseMakeStaticStrongOnly(&_XSetClass),
    ._hashCode = ATOMIC_VAR_INIT(0),
    .count = 0,
    .bucketCount = 0,
    .bucketIndexShift = SIZE_BITS_COUNT - 1,
};

typedef struct {
    ssize_t (*_Nonnull getCount)(XHashTableRef _Nonnull table);
    bool_t (*_Nonnull contains)(XSetRef _Nonnull set, XObjectRef _Nullable key);
    bool_t (*_Nonnull insert)(XHashTableRef _Nonnull table, XSetElement_s * _Nonnull element, XSetElement_s * _Nonnull oldElementBuffer);
    bool_t (*_Nonnull remove)(XHashTableRef _Nonnull table, XObjectRef _Nullable key, bool_t allowReduceCapacity, XSetElement_s * _Nonnull oldElementBuffer);
    XHashTableRef _Nonnull (*_Nonnull removeAll)(XHashTableRef _Nonnull table, bool_t allowReduceCapacity);
    void (*resize)(XMapRef _Nonnull map, ssize_t minCapacity);

    void (*_Nonnull enumerate)(XHashTableRef _Nonnull table, XSetEnumerate_f _Nonnull func, void * _Nullable context);
    XObjectRef _Nonnull (*_Nonnull copy)(XHashTableRef _Nonnull table);
    void (*_Nonnull deinit)(XHashTableRef _Nonnull table);
    size_t (*_Nonnull getHashCode)(XHashTableRef _Nonnull table);
    size_t (*_Nonnull getQuickHashCode)(XHashTableRef _Nonnull table);
} _XSetApi_s;


const _XSetApi_s _XHashTableApiImmutableSet;
const _XSetApi_s _XHashTableApiMutableSet;

const _XSetApi_s * _Nullable _XSetApiTable[XInfo_LayoutCount] = {
    NULL,
    &_XHashTableApiImmutableSet,
    &_XHashTableApiMutableSet,
};

const _XSetApi_s * _Nonnull __XSetGetApi(XSetRef _Nonnull set) {
    const _XSetApi_s * api = _XSetApiTable[XObjectGetLayout(set)];
    XAssert(api, "");
    return api;
}


void _XHashTableEnumerateSet(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable context, bool_t * _Nonnull stop) {
    XSetEnumerate_f func = (XSetEnumerate_f)subfunc;
    XSetElement_s * e = (XSetElement_s *)element;
    func(index, e->key, context, stop);
}

void __XSetEnumerateHash(ssize_t index, XObjectRef _Nullable key, void * _Nullable context, bool_t * _Nonnull stop) {
    XCollectionHasher_s * hasher = (XCollectionHasher_s *)context;
    size_t hashCode = XObjectGetHashCode(key);
    XCollectionHasherCombine(hasher, hashCode, hashCode);
}

size_t __XSetHash(const _XSetApi_s * _Nonnull api, XObjectRef _Nonnull obj) {
    XCollectionHasher_s hasher = {};
    ssize_t count = api->getCount(obj);
    XCollectionHasherInit(&hasher, (size_t)count);
    XSetEnumerate(obj, __XSetEnumerateHash, &hasher);
    return XCollectionHasherFinalize(&hasher);
}

ssize_t XSetGetCount(XSetRef _Nonnull set) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    return __XSetGetApi(set)->getCount(set);
}

/// return unretained object
bool_t XSetContains(XSetRef _Nonnull set, XObjectRef _Nullable key) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    return api->contains(set, key);
}

void XSetEnumerate(XSetRef _Nonnull set, XSetEnumerate_f _Nonnull func, void * _Nullable context) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    api->enumerate(set, func, context);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t XMutableSetInsert(XSetRef _Nonnull set, XObjectRef _Nullable key, XSetElement_s * _Nullable old) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    XSetElement_s element = {};
    XSetElement_s newElement = {
        .key = XObjectCopy(key)
    };

    bool_t hasOld = api->insert(set, &newElement, &element);
    if (hasOld) {
        if (old) {
            old->key = element.key;
        } else {
            XObjectRelease(element.key);
        }
    } else {
        if (old) {
            old->key = element.key;
        }
    }
    return hasOld;
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t XMutableSetRemove(XSetRef _Nonnull set, XObjectRef _Nullable key, bool_t allowReduceCapacity, XSetElement_s * _Nullable old) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    XSetElement_s element = {};
    bool_t hasOld = api->remove(set, key, allowReduceCapacity, &element);
    if (hasOld) {
        if (old) {
            memcpy(old, &element, sizeof(XSetElement_s));
        } else {
            XObjectRelease(element.key);
        }
    } else {
        if (old) {
            memset(old, 0, sizeof(XSetElement_s));
        }
    }
    return hasOld;
}

void XMutableSetRemoveAll(XSetRef _Nonnull set, bool_t allowReduceCapacity, XSetRef _Nonnull * _Nullable old) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    XSetRef removed = api->removeAll(set, allowReduceCapacity);
    if (old) {
        *old = removed;
    } else {
        XObjectRelease(removed);
    }
}
void XMutableSetResize(XMapRef _Nonnull map, ssize_t minCapacity) {
    const _XSetApi_s * api = __XSetGetApi(map);
    api->resize(map, minCapacity);
}
size_t _XSetGetHashCode(XObjectRef _Nonnull set) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    return api->getHashCode(set);
}
void _XSetDeinit(XObjectRef _Nonnull set)  {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    api->deinit(set);
}


typedef struct {
    ssize_t equalCount;
    XObjectRef _Nonnull set;
} _XSetEqualContext_s;

void _XSetEqualEnumerate(ssize_t index, XObjectRef _Nullable key, void * _Nullable context, bool_t * _Nonnull stop) {
    _XSetEqualContext_s * ctx = (_XSetEqualContext_s *)context;
    if (!XSetContains(ctx->set, key)) {
        *stop = true;
    } else {
        ctx->equalCount += 1;
    }
}

bool_t _XSetEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    const _XSetApi_s * lapi = __XSetGetApi(lhs);
    const _XSetApi_s * rapi = __XSetGetApi(rhs);
    size_t lhashcode = lapi->getQuickHashCode(lhs);
    size_t rhashcode = rapi->getQuickHashCode(rhs);
    if (0 != lhashcode && 0 != rhashcode && lhashcode != rhashcode) {
        return false;
    }
    
    ssize_t count = lapi->getCount(lhs);
    if (count != rapi->getCount(rhs)) {
        return false;
    }
    _XSetEqualContext_s context = {
        .equalCount = 0,
        .set = rhs,
    };
    lapi->enumerate(lhs, _XSetEqualEnumerate, &context);
    return context.equalCount == count;
}
void _XSetDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XSetDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

XObjectRef _Nonnull _XSetCopy(XObjectRef _Nonnull set) {
    XAssert(XObjectGetClass(set) == XSetClass, "");
    const _XSetApi_s * api = __XSetGetApi(set);
    return api->copy(set);
}
#pragma mark - immutable

ssize_t _XImmutableSetGetCount(XSetRef _Nonnull set) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)set;
    return table->count;
}

/// return unretained object
bool_t _XImmutableSetContains(XSetRef _Nonnull set, XObjectRef _Nullable key) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)set;
    XSetElement_s element = {};
    return XImmutableHashTableGetElement(table, &__XSetElementType, &key, &element);
}

void _XImmutableSetEnumerate(XSetRef _Nonnull set, XSetEnumerate_f _Nonnull func, void * _Nullable context) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)set;
    XImmutableHashTableEnumerate(table, &__XSetElementType, _XHashTableEnumerateSet, func, context);
}

XObjectRef _Nonnull _XImmutableSetCopy(XSetRef _Nonnull set) {
    return XObjectRetain(set);
}
XObjectRef _Nonnull _XImmutableSetCopyAndRelease(XSetRef _Nonnull set) {
    return set;
}
void _XImmutableSetDeinit(XSetRef _Nonnull set) {
    XImmutableHashTable_s * table = (XImmutableHashTable_s *)set;
    XImmutableHashTableDeinit(table, &__XSetElementType, _XSetElementDeinit);
}
size_t _XImmutableSetGetHashCode(XObjectRef _Nonnull self) {
    XImmutableHashTable_s * obj = (XImmutableHashTable_s *)self;
    size_t code = atomic_load(&(obj->_hashCode));
    if (0 == code) {
        code = __XSetHash(&_XHashTableApiImmutableSet, obj);
        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
    }
    return code;
}
size_t _XImmutableSetGetQuickHashCode(XObjectRef _Nonnull self) {
    XImmutableHashTable_s * obj = (XImmutableHashTable_s *)self;
    return atomic_load(&(obj->_hashCode));
}

#pragma mark - mutable

ssize_t _XMutableSetGetCount(XSetRef _Nonnull set) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    return table->count;
}
/// return unretained object
bool_t _XMutableSetContains(XSetRef _Nonnull set, XObjectRef _Nullable key) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    XSetElement_s element = {};
    return XMutableHashTableGetElement(table, &__XSetElementType, &key, &element);
}
/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableSetInsert(XSetRef _Nonnull set, XSetElement_s * _Nonnull element, XSetElement_s * _Nonnull old) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    return XMutableHashTableReplace(table,  &__XSetElementType, element, old);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableSetRemoveValue(XSetRef _Nonnull set, XObjectRef _Nullable key, bool_t allowReduceCapacity, XSetElement_s * _Nonnull old) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    return XMutableHashTableRemove(table, &__XSetElementType, &key, allowReduceCapacity, old);
}

XHashTableRef _Nonnull _XMutableSetRemoveAll(XSetRef _Nonnull set, bool_t allowReduceCapacity) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    return XMutableHashTableRemoveAll(table, &__XSetElementType, allowReduceCapacity, 0);
}
void _XMutableSetEnumerate(XSetRef _Nonnull set, XSetEnumerate_f _Nonnull func, void * _Nullable context) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    XMutableHashTableEnumerate(table, &__XSetElementType, _XHashTableEnumerateSet, func, context);
}
void _XMutableSetResize(XMapRef _Nonnull map, ssize_t minCapacity) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)map;
    XMutableHashTableResize(table, &__XSetElementType, minCapacity);
}
XObjectRef _Nonnull _XMutableSetCopy(XSetRef _Nonnull set) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    if (XMutableHashTableGetCount(table) > 0) {
        return XMutableHashTableCopy(table, &__XSetElementType, 0, _XSetElementCopy);
    } else {
        return &__XImmutableSetEmpty;
    }
}
XObjectRef _Nonnull _XMutableSetCopyAndRelease(XSetRef _Nonnull set) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    if (XMutableHashTableGetCount(table) > 0) {
        XObjectRef r = XMutableHashTableCopy(table, &__XSetElementType, 0, _XSetElementCopy);
        XObjectRelease(set);
        return r;
    } else {
        XObjectRelease(set);
        return &__XImmutableSetEmpty;
    }
}
void _XMutableSetDeinit(XSetRef _Nonnull set) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)set;
    XMutableHashTableDeinit(table, &__XSetElementType, _XSetElementDeinit);
}

size_t _XMutableSetGetHashCode(XObjectRef _Nonnull self) {
    return __XSetHash(&_XHashTableApiMutableSet, self);
}
size_t _XMutableSetGetQuickHashCode(XObjectRef _Nonnull self) {
    return 0;
}

const _XSetApi_s _XHashTableApiImmutableSet = {
    .getCount = _XImmutableSetGetCount,
    .contains = _XImmutableSetContains,
    .enumerate = _XImmutableSetEnumerate,
    .copy = _XImmutableSetCopy,
    .deinit = _XImmutableSetDeinit,
    .getHashCode = _XImmutableSetGetHashCode,
    .getQuickHashCode = _XImmutableSetGetQuickHashCode,
};
const _XSetApi_s _XHashTableApiMutableSet = {
    .getCount = _XMutableSetGetCount,
    .contains = _XMutableSetContains,
    .insert = _XMutableSetInsert,
    .remove = _XMutableSetRemoveValue,
    .removeAll = _XMutableSetRemoveAll,
    .enumerate = _XMutableSetEnumerate,
    .copy = _XMutableSetCopy,
    .deinit = _XMutableSetDeinit,
    .getHashCode = _XMutableSetGetHashCode,
    .getQuickHashCode = _XMutableSetGetQuickHashCode,
    .resize = _XMutableSetResize,
};


// -----------------Immutable---------------

/// create immutable map,
XSetRef _Nonnull XSetCreateWithKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableSetEmpty;
    }
    
    XMutableHashTable_s * table = XMutableHashTableCreate(XSetClass, 0, &__XSetElementType, count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef key = va_arg(ap, XObjectRef);
        XSetElement_s item = {
            .key = XObjectCopy(key),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    
    XImmutableHashTable_s * result = XMutableHashTableRemoveAll(table, &__XSetElementType, false, option);
    XObjectRelease(table);
    return result;
}

XSetRef _Nonnull XSetCreateWithArray(XObjectOption option, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(keys);
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableSetEmpty;
    }
    
    XMutableHashTable_s * table = XMutableHashTableCreate(XSetClass, 0, &__XSetElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XSetElement_s item = {
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    
    XImmutableHashTable_s * result = XMutableHashTableRemoveAll(table, &__XSetElementType, false, option);
    XObjectRelease(table);
    return result;
}

// ------------------- Mutable ----------------------------

/// create mutable array

XSetRef _Nonnull XMutableSetCreateWithValueKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    XMutableHashTable_s * table = XMutableHashTableCreate(XSetClass, option, &__XSetElementType, count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef key = va_arg(ap, XObjectRef);
        XSetElement_s item = {
            .key = XObjectCopy(key),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    return table;
}

XSetRef _Nonnull XMutableSetCreate(XObjectOption option, ssize_t capacity) {
    return XMutableHashTableCreate(XSetClass, option, &__XSetElementType, capacity);
}

XSetRef _Nonnull XMutableSetCreateWithKeys(XObjectOption option, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(keys);
    XAssert(count >= 0, "");
    XMutableHashTable_s * table = XMutableHashTableCreate(XSetClass, option, &__XSetElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XSetElement_s item = {
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    return table;
}

void __XMutableSetCreateWithSetEnumerate(ssize_t index, XObjectRef _Nullable key, void * _Nullable context, bool_t * _Nonnull stop) {
    XMutableHashTable_s * table = (XMutableHashTable_s *)context;
    XSetElement_s item = {
        .key = XObjectCopy(key),
    };
    XSetElement_s tmp = {};
    bool_t existed = XMutableHashTableReplace(table, &__XSetElementType, &item, &tmp);
    XAssert(!existed, "");
}

XSetRef _Nonnull XMutableSetCreateWithSet(XObjectOption option, XSetRef _Nonnull set) {
    XAssert(set, "");
    ssize_t count = XSetGetCount(set);
    XMutableHashTable_s * table = XMutableHashTableCreate(XSetClass, option, &__XSetElementType, count);
    XSetEnumerate(set, __XMutableSetCreateWithSetEnumerate, table);
    return table;
}

const XClass_o _XSetClass = XClassMakeXDefault(XSet, 0);
XClassRef _Nonnull XSetClass = &_XSetClass;
