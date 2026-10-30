
#include "XOrderedHashTable.h"

#pragma mark - XOrderedSet
extern const XClass_o _XOrderedSetClass;

XImmutableOrderedHashTable_s __XImmutableOrderedSetEmpty = {
    ._runtime = XObjectBaseMakeStaticStrongOnly(&_XOrderedSetClass),
    ._hashCode = ATOMIC_VAR_INIT(0),
    .count = 0,
    .bucketCount = 0,
    .bucketIndexShift = SIZE_BITS_COUNT - 1,
};

typedef struct {
    ssize_t (*_Nonnull getCount)(XOrderedHashTableRef _Nonnull table);
    bool_t (*_Nonnull contains)(XOrderedSetRef _Nonnull set, XObjectRef _Nullable key);
    bool_t (*_Nonnull insert)(XOrderedHashTableRef _Nonnull table, XSetElement_s * _Nonnull element, XSetElement_s * _Nonnull oldElementBuffer);
    bool_t (*_Nonnull remove)(XOrderedHashTableRef _Nonnull table, XObjectRef _Nullable key, bool_t allowReduceCapacity, XSetElement_s * _Nonnull oldElementBuffer);
    XOrderedHashTableRef _Nonnull (*_Nonnull removeAll)(XOrderedHashTableRef _Nonnull table, bool_t allowReduceCapacity);
    void (*resize)(XMapRef _Nonnull map, ssize_t minCapacity);
    XOrderedHashTableIter_s (* _Nonnull makeIter)(XOrderedHashTableRef _Nonnull table, bool_t reverse);
    
    void (*_Nonnull enumerate)(XOrderedHashTableRef _Nonnull table, bool_t reverse, XSetEnumerate_f _Nonnull func, void * _Nullable context);
    XObjectRef _Nonnull (*_Nonnull copy)(XOrderedHashTableRef _Nonnull table);
    void (*_Nonnull deinit)(XOrderedHashTableRef _Nonnull table);
    size_t (*_Nonnull getHashCode)(XOrderedHashTableRef _Nonnull table);
    size_t (*_Nonnull getQuickHashCode)(XOrderedHashTableRef _Nonnull table);
} _XOrderedSetApi_s;


const _XOrderedSetApi_s _XOrderedHashTableApiImmutableOrderedSet;
const _XOrderedSetApi_s _XOrderedHashTableApiMutableOrderedSet;

const _XOrderedSetApi_s * _Nullable _XOrderedSetApiTable[XInfo_LayoutCount] = {
    NULL,
    &_XOrderedHashTableApiImmutableOrderedSet,
    &_XOrderedHashTableApiMutableOrderedSet,
};

const _XOrderedSetApi_s * _Nonnull __XOrderedSetGetApi(XOrderedSetRef _Nonnull set) {
    const _XOrderedSetApi_s * api = _XOrderedSetApiTable[XObjectGetLayout(set)];
    XAssert(api, "");
    return api;
}


void _XOrderedHashTableEnumerateOrderedSet(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable context, bool_t * _Nonnull stop) {
    XSetEnumerate_f func = (XSetEnumerate_f)subfunc;
    XSetElement_s * e = (XSetElement_s *)element;
    func(index, e->key, context, stop);
}

void __XOrderedSetEnumerateHash(ssize_t index, XObjectRef _Nullable key, void * _Nullable context, bool_t * _Nonnull stop) {
    XCollectionHasher_s * hasher = (XCollectionHasher_s *)context;
    size_t hashCode = XObjectGetHashCode(key);
    XCollectionHasherCombine(hasher, index, hashCode);
}

size_t __XOrderedSetHash(const _XOrderedSetApi_s * _Nonnull api, XObjectRef _Nonnull obj) {
    XCollectionHasher_s hasher = {};
    ssize_t count = api->getCount(obj);
    XCollectionHasherInit(&hasher, (size_t)count);
    XOrderedSetEnumerate(obj, false, __XOrderedSetEnumerateHash, &hasher);
    return XCollectionHasherFinalize(&hasher);
}

ssize_t XOrderedSetGetCount(XOrderedSetRef _Nonnull set) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    return __XOrderedSetGetApi(set)->getCount(set);
}

/// return unretained object
bool_t XOrderedSetContains(XOrderedSetRef _Nonnull set, XObjectRef _Nullable key) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
    return api->contains(set, key);
}

void XOrderedSetEnumerate(XOrderedSetRef _Nonnull set, bool_t reverse, XSetEnumerate_f _Nonnull func, void * _Nullable context) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
    api->enumerate(set, reverse, func, context);
}

XOrderedHashTableIter_s XOrderedSetMakeIter(XOrderedSetRef _Nonnull set, bool_t reverse) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
    return api->makeIter(set, reverse);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t XMutableOrderedSetInsert(XOrderedSetRef _Nonnull set, XObjectRef _Nullable key, XSetElement_s * _Nullable old) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
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
bool_t XMutableOrderedSetRemove(XOrderedSetRef _Nonnull set, XObjectRef _Nullable key, bool_t allowReduceCapacity, XSetElement_s * _Nullable old) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
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

void XMutableOrderedSetRemoveAll(XOrderedSetRef _Nonnull set, bool_t allowReduceCapacity, XOrderedSetRef _Nonnull * _Nullable old) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
    XOrderedSetRef removed = api->removeAll(set, allowReduceCapacity);
    if (old) {
        *old = removed;
    } else {
        XObjectRelease(removed);
    }
}
void XMutableOrderedSetResize(XMapRef _Nonnull map, ssize_t minCapacity) {
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(map);
    api->resize(map, minCapacity);
}
size_t _XOrderedSetGetHashCode(XObjectRef _Nonnull set) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
    return api->getHashCode(set);
}
void _XOrderedSetDeinit(XObjectRef _Nonnull set)  {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
    api->deinit(set);
}

bool_t _XOrderedSetEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    const _XOrderedSetApi_s * lapi = __XOrderedSetGetApi(lhs);
    const _XOrderedSetApi_s * rapi = __XOrderedSetGetApi(rhs);
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
        XSetElement_s * le = XOrderedHashTableIterNext(&liter);
        XSetElement_s * re = XOrderedHashTableIterNext(&riter);
        XAssert(le, "");
        XAssert(re, "");
        if (!XSetElementEqual(le, re)) {
            return false;
        }
    }
    
    XAssert(NULL == XOrderedHashTableIterNext(&liter), "");
    XAssert(NULL == XOrderedHashTableIterNext(&riter), "");
    return true;
}
void _XOrderedSetDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XOrderedSetDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

XObjectRef _Nonnull _XOrderedSetCopy(XObjectRef _Nonnull set) {
    XAssert(XObjectGetClass(set) == XOrderedSetClass, "");
    const _XOrderedSetApi_s * api = __XOrderedSetGetApi(set);
    return api->copy(set);
}

#pragma mark - immutable

ssize_t _XImmutableOrderedSetGetCount(XOrderedSetRef _Nonnull set) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)set;
    return table->count;
}

/// return unretained object
bool_t _XImmutableOrderedSetContains(XOrderedSetRef _Nonnull set, XObjectRef _Nullable key) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)set;
    XSetElement_s element = {};
    return XImmutableOrderedHashTableGetElement(table, &__XSetElementType, &key, &element);
}

void _XImmutableOrderedSetEnumerate(XOrderedSetRef _Nonnull set, bool_t reverse, XSetEnumerate_f _Nonnull func, void * _Nullable context) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)set;
    XImmutableOrderedHashTableEnumerate(table, &__XSetElementType, reverse, _XOrderedHashTableEnumerateOrderedSet, func, context);
}

XObjectRef _Nonnull _XImmutableOrderedSetCopy(XOrderedSetRef _Nonnull set) {
    return XObjectRetain(set);
}
XObjectRef _Nonnull _XImmutableOrderedSetCopyAndRelease(XOrderedSetRef _Nonnull set) {
    return set;
}

void _XImmutableOrderedSetDeinit(XOrderedSetRef _Nonnull set) {
    XImmutableOrderedHashTable_s * table = (XImmutableOrderedHashTable_s *)set;
    XImmutableOrderedHashTableDeinit(table, &__XSetElementType, _XSetElementDeinit);
}
size_t _XImmutableOrderedSetGetHashCode(XObjectRef _Nonnull self) {
    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
    size_t code = atomic_load(&(obj->_hashCode));
    if (0 == code) {
        code = __XOrderedSetHash(&_XOrderedHashTableApiImmutableOrderedSet, obj);
        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
    }
    return code;
}
size_t _XImmutableOrderedSetGetQuickHashCode(XObjectRef _Nonnull self) {
    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
    return atomic_load(&(obj->_hashCode));
}
XOrderedHashTableIter_s _XImmutableOrderedSetMakeIter(XOrderedSetRef _Nonnull self, bool_t reverse) {
    XImmutableOrderedHashTable_s * obj = (XImmutableOrderedHashTable_s *)self;
    return XImmutableOrderedHashTableMakeIter(obj, reverse);
}

#pragma mark - mutable

ssize_t _XMutableOrderedSetGetCount(XOrderedSetRef _Nonnull set) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    return table->count;
}
/// return unretained object
bool_t _XMutableOrderedSetContains(XOrderedSetRef _Nonnull set, XObjectRef _Nullable key) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    XSetElement_s element = {};
    return XMutableOrderedHashTableGetElement(table, &__XSetElementType, &key, &element);
}
/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableOrderedSetInsert(XOrderedSetRef _Nonnull set, XSetElement_s * _Nonnull element, XSetElement_s * _Nonnull old) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    return XMutableOrderedHashTableReplace(table, &__XSetElementType, element, old);
}

/// 返回retainedobject, 如果有旧object， 返回true
bool_t _XMutableOrderedSetRemoveValue(XOrderedSetRef _Nonnull set, XObjectRef _Nullable key, bool_t allowReduceCapacity, XSetElement_s * _Nonnull old) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    return XMutableOrderedHashTableRemove(table, &__XSetElementType, &key, allowReduceCapacity, old);
}

XOrderedHashTableRef _Nonnull _XMutableOrderedSetRemoveAll(XOrderedSetRef _Nonnull set, bool_t allowReduceCapacity) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    return XMutableOrderedHashTableRemoveAll(table, &__XSetElementType, allowReduceCapacity, 0);
}
void _XMutableOrderedSetEnumerate(XOrderedSetRef _Nonnull set, bool_t reverse, XSetEnumerate_f _Nonnull func, void * _Nullable context) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    XMutableOrderedHashTableEnumerate(table, &__XSetElementType, reverse, _XOrderedHashTableEnumerateOrderedSet, func, context);
}
void _XMutableOrderedSetResize(XMapRef _Nonnull map, ssize_t minCapacity) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)map;
    XMutableOrderedHashTableResize(table, &__XSetElementType, minCapacity);
}
XObjectRef _Nonnull _XMutableOrderedSetCopy(XOrderedSetRef _Nonnull set) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    if (XMutableOrderedHashTableGetCount(table) > 0) {
        return XMutableOrderedHashTableCopy(table, &__XSetElementType, 0, _XSetElementCopy);
    } else {
        return &__XImmutableOrderedSetEmpty;
    }
}
XObjectRef _Nonnull _XMutableOrderedSetCopyAndRelease(XOrderedSetRef _Nonnull set) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    if (XMutableOrderedHashTableGetCount(table) > 0) {
        XObjectRef r = XMutableOrderedHashTableCopy(table, &__XSetElementType, 0, _XSetElementCopy);
        XObjectRelease(set);
        return r;
    } else {
        XObjectRelease(set);
        return &__XImmutableOrderedSetEmpty;
    }
}


void _XMutableOrderedSetDeinit(XOrderedSetRef _Nonnull set) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)set;
    XMutableOrderedHashTableDeinit(table, &__XSetElementType, _XSetElementDeinit);
}

size_t _XMutableOrderedSetGetHashCode(XObjectRef _Nonnull self) {
    return __XOrderedSetHash(&_XOrderedHashTableApiMutableOrderedSet, self);
}
size_t _XMutableOrderedSetGetQuickHashCode(XObjectRef _Nonnull self) {
    return 0;
}
XOrderedHashTableIter_s _XMutableOrderedSetMakeIter(XOrderedSetRef _Nonnull self, bool_t reverse) {
    XMutableOrderedHashTable_s * obj = (XMutableOrderedHashTable_s *)self;
    return XMutableOrderedHashTableMakeIter(obj, reverse);
}
const _XOrderedSetApi_s _XOrderedHashTableApiImmutableOrderedSet = {
    .getCount = _XImmutableOrderedSetGetCount,
    .contains = _XImmutableOrderedSetContains,
    .enumerate = _XImmutableOrderedSetEnumerate,
    .makeIter = _XImmutableOrderedSetMakeIter,
    .copy = _XImmutableOrderedSetCopy,
    .deinit = _XImmutableOrderedSetDeinit,
    .getHashCode = _XImmutableOrderedSetGetHashCode,
    .getQuickHashCode = _XImmutableOrderedSetGetQuickHashCode,
};
const _XOrderedSetApi_s _XOrderedHashTableApiMutableOrderedSet = {
    .getCount = _XMutableOrderedSetGetCount,
    .contains = _XMutableOrderedSetContains,
    .insert = _XMutableOrderedSetInsert,
    .remove = _XMutableOrderedSetRemoveValue,
    .removeAll = _XMutableOrderedSetRemoveAll,
    .enumerate = _XMutableOrderedSetEnumerate,
    .makeIter = _XMutableOrderedSetMakeIter,
    .copy = _XMutableOrderedSetCopy,
    .deinit = _XMutableOrderedSetDeinit,
    .getHashCode = _XMutableOrderedSetGetHashCode,
    .getQuickHashCode = _XMutableOrderedSetGetQuickHashCode,
    .resize = _XMutableOrderedSetResize,
};



// -----------------Immutable---------------

/// create immutable map,
XOrderedSetRef _Nonnull XOrderedSetCreateWithKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableOrderedSetEmpty;
    }
    
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedSetClass, 0, &__XSetElementType, count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef key = va_arg(ap, XObjectRef);
        XSetElement_s item = {
            .key = XObjectCopy(key),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    
    XImmutableOrderedHashTable_s * result = XMutableOrderedHashTableRemoveAll(table, &__XSetElementType, false, option);
    XObjectRelease(table);
    return result;
}

XOrderedSetRef _Nonnull XOrderedSetCreateWithArray(XObjectOption option, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(keys);
    XAssert(count >= 0, "");
    if (count <= 0) {
        return &__XImmutableOrderedSetEmpty;
    }
    
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedSetClass, 0, &__XSetElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XSetElement_s item = {
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    
    XImmutableOrderedHashTable_s * result = XMutableOrderedHashTableRemoveAll(table, &__XSetElementType, false, option);
    XObjectRelease(table);
    return result;
}

// ------------------- Mutable ----------------------------

/// create mutable array

XOrderedSetRef _Nonnull XMutableOrderedSetCreateWithValueKeys(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedSetClass, option, &__XSetElementType, count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef key = va_arg(ap, XObjectRef);
        XSetElement_s item = {
            .key = XObjectCopy(key),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    va_end(ap);
    XAssert(table->count == count, "");
    return table;
}

XOrderedSetRef _Nonnull XMutableOrderedSetCreate(XObjectOption option, ssize_t capacity) {
    return XMutableOrderedHashTableCreate(XOrderedSetClass, option, &__XSetElementType, capacity);
}

XOrderedSetRef _Nonnull XMutableOrderedSetCreateWithKeys(XObjectOption option, XArrayRef _Nonnull keys) {
    ssize_t count = XArrayGetCount(keys);
    XAssert(count >= 0, "");
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedSetClass, option, &__XSetElementType, count);
    for (ssize_t i = 0; i < count; i++) {
        XSetElement_s item = {
            .key = XObjectCopy(XArrayGetObject(keys, i)),
        };
        XSetElement_s tmp = {};
        bool_t existed = XMutableOrderedHashTableReplace(table, &__XSetElementType, &item, &tmp);
        XAssert(!existed, "");
    }
    return table;
}

void __XMutableOrderedSetCreateWithOrderedSetEnumerate(ssize_t index, XObjectRef _Nullable key, void * _Nullable context, bool_t * _Nonnull stop) {
    XMutableOrderedHashTable_s * table = (XMutableOrderedHashTable_s *)context;
    XSetElement_s item = {
        .key = XObjectCopy(key),
    };
    XSetElement_s tmp = {};
    bool_t existed = XMutableOrderedHashTableReplace(table, &__XSetElementType, &item, &tmp);
    XAssert(!existed, "");
}

XOrderedSetRef _Nonnull XMutableOrderedSetCreateWithOrderedSet(XObjectOption option, XOrderedSetRef _Nonnull set) {
    XAssert(set, "");
    ssize_t count = XOrderedSetGetCount(set);
    XMutableOrderedHashTable_s * table = XMutableOrderedHashTableCreate(XOrderedSetClass, option, &__XSetElementType, count);
    XOrderedSetEnumerate(set, false, __XMutableOrderedSetCreateWithOrderedSetEnumerate, table);
    return table;
}

const XClass_o _XOrderedSetClass = XClassMakeXDefault(XOrderedSet, 0);
XClassRef _Nonnull XOrderedSetClass = &_XOrderedSetClass;
