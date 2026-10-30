#include "XRuntimeInternal.h"

#define _XArrayElementSize sizeof(XArrayElement_s)


typedef struct {
    ssize_t (*_Nonnull getCount)(XArrayRef _Nonnull array);
    XObjectRef _Nullable (*_Nonnull getObject)(XArrayRef _Nonnull array, size_t index);
    XObjectRef _Nullable (*_Nonnull getSubarray)(XObjectRef _Nonnull self, size_t index, size_t count);
    
    //
    void (*_Nonnull enumerate)(XObjectRef _Nonnull self, ssize_t index, ssize_t count, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context);
    void (*_Nullable replace)(XArrayRef _Nonnull array, size_t index, size_t count, XArrayElement_s * _Nullable items, size_t itemsCount, bool_t allowReduceCapacity, XArrayElement_s * _Nullable removedItems);
    XObjectRef _Nonnull (*_Nonnull copy)(XArrayRef _Nonnull array);
    void (*_Nonnull deinit)(XObjectRef _Nonnull array);
    size_t (*_Nonnull getHashCode)(XObjectRef _Nonnull array);
    size_t (*_Nonnull getQuickHashCode)(XObjectRef _Nonnull array);
    void (*_Nonnull resize)(XObjectRef _Nonnull array, ssize_t minCapacity);

} _XArrayApi_s;

extern const _XArrayApi_s _XArrayApiImmutable;
extern const _XArrayApi_s _XArrayApiMutable;
extern const _XArrayApi_s _XArrayApiImmutableBuilder;

const _XArrayApi_s * _Nullable _XArrayApiTable[XInfo_LayoutCount] = {
    NULL,
    &_XArrayApiImmutable,
    &_XArrayApiMutable,
    &_XArrayApiImmutableBuilder,
};


_XImmutableArray_o * _Nonnull __XImmutableArrayCreateInternal(XObjectOption option, size_t count);

void _XMutableArrayReplaceObjects(XArrayRef _Nonnull self, size_t index, size_t count, XArrayElement_s * _Nullable items, size_t itemsCount, bool_t allowReduceCapacity, XArrayElement_s * _Nullable removedItems);

const _XArrayApi_s * _Nonnull __XArrayGetApi(XArrayRef _Nonnull array) {
    size_t layout = XObjectGetLayout(array);
    const _XArrayApi_s * api = _XArrayApiTable[layout];
    XAssert(api, "");
    return api;
}

void __XArrayEnumerateHash(size_t index, XObjectRef _Nullable object, void * _Nullable context, bool_t * _Nonnull stop) {
    XCollectionHasher_s * hasher = (XCollectionHasher_s *)context;
    XCollectionHasherCombine(hasher, index, XObjectGetHashCode(object));
}

size_t __XArrayHash(const _XArrayApi_s * _Nonnull api, XArrayRef _Nonnull array) {
    XCollectionHasher_s hasher = {};
    ssize_t count = api->getCount(array);
    XCollectionHasherInit(&hasher, count);
    api->enumerate(array, 0, count, false, __XArrayEnumerateHash, &hasher);
    return XCollectionHasherFinalize(&hasher);
}

ssize_t XArrayGetCount(XArrayRef _Nonnull array) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    return api->getCount(array);
}
XObjectRef _Nullable XArrayGetAssignObject(XArrayRef _Nonnull array, ssize_t index) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index >= 0 && index < api->getCount(array), "out of bounds");
    return api->getObject(array, index);
}
XObjectRef _Nullable XArrayGetObject(XArrayRef _Nonnull array, ssize_t index) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index >= 0 && index < api->getCount(array), "out of bounds");
    return XObjectRetain(api->getObject(array, index));
}

void XArrayEnumerate(XArrayRef _Nonnull array, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    XAssert(func, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    api->enumerate(array, 0, api->getCount(array), reverse, func, context);
}

void XArrayEnumerateWithRange(XArrayRef _Nonnull array, ssize_t index, ssize_t count, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    XAssert(func, "");
    XAssert(index >= 0, "");
    XAssert(count >= 0, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index + count <= api->getCount(array), "");
    api->enumerate(array, index, count, false, func, context);
}

/// 返回retainedobject
XObjectRef _Nullable XArraySubarray(XArrayRef _Nonnull array, ssize_t index, ssize_t count) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index >= 0 && count >= 0 && index + count <= api->getCount(array), "out of bounds");
    return api->getSubarray(array, (size_t)index, (size_t)count);
}

void XMutableArrayInsert(XArrayRef _Nonnull array, XObjectRef _Nullable object, ssize_t index) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index >= 0 && index <= api->getCount(array), "out of bounds");
    XArrayElement_s item = {
        .item = XObjectCopy(object),
    };
    api->replace(array, (size_t)index, 0, &item, 1, true, NULL);
}
void XMutableArrayAppend(XObjectRef _Nonnull array, XObjectRef _Nullable object) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XArrayElement_s item = {
        .item = XObjectCopy(object),
    };
    api->replace(array, (size_t)(api->getCount(array)), 0, &item, 1, true, NULL);
}
void XMutableArrayPrepend(XObjectRef _Nonnull array, XObjectRef _Nullable object) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XArrayElement_s item = {
        .item = XObjectCopy(object),
    };
    api->replace(array, 0, 0, &item, 1, true, NULL);
}

/// 返回retainedobject
void XMutableArrayRemove(XArrayRef _Nonnull array, ssize_t index, XArrayElement_s * _Nullable old) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index >= 0 && index < api->getCount(array), "out of bounds");
    XArrayElement_s removed = {};
    api->replace(array, (size_t)index, 1, NULL, 0, true, &removed);
    if (old) {
        old->item = removed.item;
    } else {
        XObjectRelease(removed.item);
    }
}

/// 返回retainedobject
void XMutableArrayReplace(XArrayRef _Nonnull array, XObjectRef _Nullable object, ssize_t index, XArrayElement_s * _Nullable old) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index >= 0 && index < api->getCount(array), "out of bounds");
    XArrayElement_s removed = {};
    XArrayElement_s item = {
        .item = XObjectCopy(object),
    };
    api->replace(array, (size_t)index, 1, &item, 1, true, &removed);
    if (old) {
        old->item = removed.item;
    } else {
        XObjectRelease(removed.item);
    }
}

void XMutableArrayRemoveAll(XObjectRef _Nonnull array, bool_t allowReduceCapacity, XArrayRef _Nonnull * _Nullable old) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    XMutableArrayReplaceObjects(array, 0, XArrayGetCount(array), NULL, 0, 0, allowReduceCapacity, old);
}
void XMutableArrayResize(XObjectRef _Nonnull array, ssize_t minCapacity) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    api->resize(array, minCapacity);
}

void (*_Nullable replace)(XArrayRef _Nonnull array, size_t index, size_t count, XArrayElement_s * _Nullable items, size_t itemsCount, XArrayElement_s * _Nullable removedItems);


///// 返回retainedobject
//XArrayRef _Nonnull _XMutableArrayReplaceObjects(XArrayRef _Nonnull array, ssize_t index, ssize_t count, _XImmutableArray_o * _Nullable _objects, size_t objectsStartIndex, size_t objectsCount) {
//    XAssert(XObjectGetClass(array) == XArrayClass, "");
//    const _XArrayApi_s * api = __XArrayGetApi(array);
//    XAssert(index >= 0 && count >= 0 && index + count <= api->getCount(array), "out of bounds");
//
//    if (array == _objects) {
//        XArrayRef tmp = XArraySubarray(_objects, objectsStartIndex, objectsCount);
//        XArrayRef result = XMutableArrayReplaceObjects(array, index, count, tmp, 0, objectsCount);
//        XObjectRelease(tmp);
//        return result;
//    }
//
//    XVector_s buffers[2] = { 0 };
//    if (_objects) {
//        XAssert(XObjectGetClass(_objects) == XArrayClass, "");
//        size_t layout = XObjectGetLayout(_objects);
//        if (layout == __XCollectionLayoutImmutable) {
//            _XImmutableArray_o * objects = (_XImmutableArray_o *)_objects;
//            const XArrayElement_s * buckets = (const XArrayElement_s *)objects->items;
//
//            XAssert(objectsStartIndex + objectsCount <= objects->count, "");
//            buffers[0].count = objectsCount;
//            buffers[0].items = (uint8_t *)(buckets + objectsStartIndex);
//
//            for (size_t i=objectsStartIndex; i<objectsStartIndex + objectsCount; i++) {
//                XObjectRetain(objects->items[i].item);
//            }
//        } else if (layout == __XCollectionLayoutMutable) {
//            _XMutableArray_o * objects = (_XMutableArray_o *)_objects;
//            XAssert(objectsStartIndex + objectsCount <= objects->deque.count, "");
//            if (objects->deque.count > 0) {
//                XAssert(objects->deque.buffer, "");
//                size_t location = (objects->deque.buffer->offset + objectsStartIndex) % objects->deque.buffer->capacity;
//                if (objectsCount > objects->deque.buffer->capacity - location) {
//                    buffers[0].count = objects->deque.buffer->capacity - location;
//                    buffers[0].items = XDequeElementAtIndex(objects->deque.buffer, _XArrayElementSize, objectsStartIndex);
//                    buffers[1].count = objectsCount - buffers[0].count;
//                    buffers[1].items = XDequeElementAtIndex(objects->deque.buffer, _XArrayElementSize, objectsStartIndex + buffers[0].count);;
//                } else {
//                    buffers[0].count = objectsCount;
//                    buffers[0].items = XDequeElementAtIndex(objects->deque.buffer, _XArrayElementSize, objectsStartIndex);
//                }
//                for (size_t i=0; i<objects->deque.count; i++) {
//                    XObjectRetain(_XMutableArrayGetObject(objects, i));
//                }
//
//                for (size_t j=0; j<2; j++) {
//                    for (size_t i=0; i<buffers[j].count; i++) {
//                        XObjectRetain(buffers[j].items[i].item);
//                    }
//                }
//
//            }
//        } else {
//            abort();
//        }
//    }
//    for (size_t j=0; j<2; j++) {
//        for (size_t i=0; i<buffers[j].count; i++) {
//            XObjectRetain(buffers[j].items[i].item);
//        }
//    }
//    _XImmutableArray_o * result = __XImmutableArrayCreateInternal(count);
//    api->replace(array, (size_t)index, (size_t)count, buffers, 2, (XArrayElement_s *)result->items);
//    return result;
//}

//void (*_Nullable replace)(XArrayRef _Nonnull array, size_t index, size_t count, XArrayElement_s * _Nullable items, size_t itemsCount, XArrayElement_s * _Nullable removedItems);

/// 返回retainedobject
void XMutableArrayReplaceObjects(XArrayRef _Nonnull array, ssize_t index, ssize_t count, XArrayRef _Nullable _objects, size_t objectsStartIndex, size_t objectsCount, bool_t allowReduceCapacity, XArrayRef * _Nullable old) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    XAssert(index >= 0 && count >= 0 && index + count <= api->getCount(array), "out of bounds");
    
    XArrayElement_s * items = NULL;
    if (objectsCount > 0) {
        XAssert(_objects, "");
        items  = XAllocate(_XArrayElementSize * objectsCount);
        XAssert(XObjectGetClass(_objects) == XArrayClass, "");
        const _XArrayApi_s * api = __XArrayGetApi(array);
        XAssert(objectsStartIndex + objectsCount <= api->getCount(_objects), "");
        for (size_t i=0; i<objectsCount; i++) {
            items[i].item = XObjectCopy(api->getObject(_objects, objectsStartIndex + i));
        }
    }
    _XImmutableArray_o * result = __XImmutableArrayCreateInternal(0, count);
    api->replace(array, (size_t)index, (size_t)count, items, objectsCount, allowReduceCapacity, (XArrayElement_s *)result->items);
    
    if (items) {
        XDeallocate(items);
        items = NULL;
    }
    if (old) {
        *old = result;
    } else {
        XObjectRelease(result);
    }
}

void _XArrayDeinit(XObjectRef _Nonnull self)  {
    const _XArrayApi_s * api = __XArrayGetApi(self);
    api->deinit(self);
}

size_t _XArrayGetHashCode(XObjectRef _Nonnull self) {
    const _XArrayApi_s * api = __XArrayGetApi(self);
    return api->getHashCode(self);
}

bool_t _XArrayEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    const _XArrayApi_s * lapi = __XArrayGetApi(lhs);
    const _XArrayApi_s * rapi = __XArrayGetApi(rhs);
    size_t lhashcode = lapi->getQuickHashCode(lhs);
    size_t rhashcode = rapi->getQuickHashCode(rhs);
    if (0 != lhashcode && 0 != rhashcode && lhashcode != rhashcode) {
        return false;
    }
    
    ssize_t count = lapi->getCount(lhs);
    if (count != rapi->getCount(rhs)) {
        return false;
    }
    for (ssize_t i=0; i<count; i++) {
        XObjectRef lhsobj = lapi->getObject(lhs, i);
        XObjectRef rhsobj = rapi->getObject(rhs, i);
        if (!XObjectEqual(lhsobj, rhsobj)) {
            return false;
        }
    }
    return true;
}

void _XArrayDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XArrayDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
XObjectRef _Nonnull _XArrayCopy(XObjectRef _Nonnull self) {
    const _XArrayApi_s * api = __XArrayGetApi(self);
    return api->copy(self);
}






_XImmutableArray_o __XImmutableArrayEmpty = {
    ._runtime = XObjectBaseMakeStaticStrongOnlyWithLayout(XArrayClass, (size_t)__XCollectionLayoutImmutable),
    ._hashCode = ATOMIC_VAR_INIT(0),
    .count = 0,
};

XArrayRef _Nonnull XArrayEmpty(void) {
    return &__XImmutableArrayEmpty;
}

_XImmutableArray_o * _Nonnull __XImmutableArrayCreateInternal(XObjectOption option, size_t count) {
    if (0 == count) {
        return &__XImmutableArrayEmpty;
    }
    XAssert(count < SINT_MAX, "");
    size_t size = sizeof(_XImmutableArray_o) + sizeof(XArrayElement_s) * count;
    _XImmutableArray_o * array = XObjectAllocate(XArrayClass, option, size, __XCollectionLayoutImmutable);
    *(ssize_t *)&(array->count) = (ssize_t)count;
    atomic_store(&(array->_hashCode), 0);
    return array;
}
/// create immutable array
XArrayRef _Nonnull XArrayCreateWithValues(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    
    _XImmutableArray_o * result = __XImmutableArrayCreateInternal(option, count);
    XArrayElement_s * buckets = (XArrayElement_s *)result->items;
    va_list ap;
    va_start(ap, count);
    for (ssize_t i=0; i<count; i++) {
        XObjectRef obj = va_arg(ap, XObjectRef);
        buckets[i].item = XObjectCopy(obj);
    }
    va_end(ap);
    return result;
}

void _XImmutableArrayDeinit(XObjectRef _Nonnull self)  {
    _XImmutableArray_o * obj = (_XImmutableArray_o *)self;
    XArrayElement_s * buckets = (XArrayElement_s *)obj->items;
    for (size_t i=0; i<obj->count; i++) {
        XObjectRelease(buckets[i].item);
        buckets[i].item = NULL;
    }
    *(ssize_t *)&(obj->count) = 0;
}

ssize_t _XImmutableArrayGetCount(XArrayRef _Nonnull self) {
    _XImmutableArray_o * obj = (_XImmutableArray_o *)self;
    return obj->count;
}

size_t _XImmutableArrayGetHashCode(XObjectRef _Nonnull self) {
    _XImmutableArray_o * obj = (_XImmutableArray_o *)self;
    size_t code = atomic_load(&(obj->_hashCode));
    if (0 == code) {
        code = __XArrayHash(&_XArrayApiImmutable, obj);
        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
    }
    return code;
}
size_t _XImmutableArrayGetQuickHashCode(XObjectRef _Nonnull self) {
    _XImmutableArray_o * obj = (_XImmutableArray_o *)self;
    return atomic_load(&(obj->_hashCode));
}

XObjectRef _Nullable _XImmutableArrayGetObject(XObjectRef _Nonnull self, size_t index) {
    _XImmutableArray_o * obj = (_XImmutableArray_o *)self;
    XAssert(index < obj->count, "out of bounds");
    return obj->items[index].item;
}
XObjectRef _Nullable _XImmutableArraySubarray(XObjectRef _Nonnull self, size_t index, size_t count) {
    _XImmutableArray_o * obj = (_XImmutableArray_o *)self;
    XAssert(index + count <= obj->count, "out of bounds");
    if (index + count == obj->count) {
        return XObjectRetain(self);
    } else {
        _XImmutableArray_o * result = __XImmutableArrayCreateInternal(0, count);
        XArrayElement_s * buckets = (XArrayElement_s *)result->items;
        for (size_t i=0; i<count; i++) {
            buckets[i].item = XObjectRetain(obj->items[i + index].item);
        }
        return result;
    }
}

void _XImmutableArrayEnumerate(XObjectRef _Nonnull self, ssize_t index, ssize_t count, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context) {
    _XImmutableArray_o * array = (_XImmutableArray_o *)self;
    bool_t stop = false;
    
    if (reverse) {
        for (ssize_t i=index+count - 1; i>=index; i--) {
            func(i, array->items[i].item, context, &stop);
            if (stop) {
                return;
            }
        }
    } else {
        for (ssize_t i=index; i<index+count; i++) {
            func(i, array->items[i].item, context, &stop);
            if (stop) {
                return;
            }
        }
    }
}

XObjectRef _Nullable _XImmutableArrayCopy(XObjectRef _Nonnull self) {
    return XObjectRetain(self);
}

XObjectRef _Nullable _XImmutableArrayCopyAndRelease(XObjectRef _Nonnull self) {
    return self;
}
#pragma mark - builder

/// create immutable array
XArrayRef _Nonnull XArrayBuilderCreateWithCount(XObjectOption option, ssize_t count) {
    XAssert(count >= 0, "");
    size_t size = sizeof(_XImmutableArray_o) + sizeof(XArrayElement_s) * count;
    _XImmutableArray_o * array = XObjectAllocate(XArrayClass, option, size, __XCollectionLayoutImmutableBuilder);
    *(ssize_t *)&(array->count) = (ssize_t)count;
    atomic_store(&(array->_hashCode), 0);
    bzero((void *)array->items, sizeof(XArrayElement_s) * count);
    return array;
}

XObjectRef _Nullable _XArrayBuilderCopy(XObjectRef _Nonnull self) {
    abort();
}
XObjectRef _Nullable _XArrayBuilderSubarray(XObjectRef _Nonnull self, size_t index, size_t count) {
    abort();
}
void _XArrayBuilderEnumerate(XObjectRef _Nonnull self, ssize_t index, ssize_t count, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context) {
    abort();
}
size_t _XArrayBuilderGetHashCode(XObjectRef _Nonnull self) {
    abort();
}
size_t _XArrayBuilderGetQuickHashCode(XObjectRef _Nonnull self) {
    abort();
}

XObjectRef _Nullable XArrayBuilderReplaceWithRetainedValue(XArrayRef _Nonnull array, ssize_t index, XObjectRef _Nullable object) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    XAssert(XObjectGetLayout(array) == __XCollectionLayoutImmutableBuilder, "");
    _XImmutableArray_o * obj = (_XImmutableArray_o *)array;
    XAssert(index < obj->count, "out of bounds");
    XAssert(index >= 0, "out of bounds");
    XArrayElement_s * element = (XArrayElement_s *)&(obj->items[index]);
    XObjectRef old = element->item;
    element->item = XObjectCopy(object);
    XObjectRelease(object);
    return old;
}

void XArrayBuilderFinich(XArrayRef _Nonnull array) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    XAssert(XObjectGetLayout(array) == __XCollectionLayoutImmutableBuilder, "");
    XObjectResetLayout(array, __XCollectionLayoutImmutable);
}


/* ------------------------------------------------------------------------------------------------------ */

size_t __XArrayRingBufferCapacityAlign(size_t capacity) {
    if (capacity < 6) return 6;
    size_t r = capacity + (capacity >> 1);
    const size_t max = (size_t)SINT_MAX;
    if (r > max) {
        return max;
    }
    return r;
}

static inline XArrayElement_s * _Nonnull __XMutableArrayGetBucket(_XMutableArray_o * _Nonnull array, size_t index) {
    return (XArrayElement_s *)XDequeElementAtIndex(&(array->deque), index);
}

_XMutableArray_o * _Nonnull __XMutableArrayCreate(XObjectOption option, size_t capacity) {
    size_t size = sizeof(_XMutableArray_o);
    _XMutableArray_o * array = XObjectAllocate(XArrayClass, option, size, __XCollectionLayoutMutable);
    XDequeInit(&(array->deque), _XArrayElementSize, capacity);
    return array;
}

/// create mutable array
XArrayRef _Nonnull XMutableArrayCreateWithValues(XObjectOption option, ssize_t count, ...) {
    XAssert(count >= 0, "");
    _XMutableArray_o * result = __XMutableArrayCreate(option, count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef object = va_arg(ap, XObjectRef);
        XArrayElement_s item = {
            .item = XObjectCopy(object),
        };
        _XMutableArrayReplaceObjects(result, i, 0, &item, 1, true, NULL);
    }
    va_end(ap);
    return result;
}

XArrayRef _Nonnull XMutableArrayCreateWithArray(XObjectOption option, XArrayRef _Nonnull array) {
    XAssert(XObjectGetClass(array) == XArrayClass, "");
    const _XArrayApi_s * api = __XArrayGetApi(array);
    ssize_t count = api->getCount(array);
    _XMutableArray_o * result = __XMutableArrayCreate(option, count);
    for (ssize_t i = 0; i < count; i++) {
        XObjectRef object = api->getObject(array, i);
        XArrayElement_s item = {
            .item = XObjectCopy(object),
        };
        _XMutableArrayReplaceObjects(result, i, 0, &item, 1, true, NULL);
    }
    return result;
}

XArrayRef _Nonnull XMutableArrayCreate(XObjectOption option, ssize_t capacity) {
    return __XMutableArrayCreate(option, capacity >= 0 ? capacity : 0);
}
ssize_t _XMutableArrayGetCount(XArrayRef _Nonnull self) {
    _XMutableArray_o * obj = (_XMutableArray_o *)self;
    return XDequeGetCount(&(obj->deque));
}

void _XMutableArrayDeinit(XObjectRef _Nonnull self)  {
    _XMutableArray_o * array = (_XMutableArray_o *)self;
    ssize_t count = _XMutableArrayGetCount(self);
    for (size_t i=0; i<count; i++) {
        XArrayElement_s * bucket = __XMutableArrayGetBucket(array, i);
        XObjectRelease(bucket->item);
        bucket->item = NULL;
    }
    XDequeDeinit(&(array->deque));
}

size_t _XMutableArrayGetHashCode(XObjectRef _Nonnull self) {
    return __XArrayHash(&_XArrayApiMutable, self);
}
size_t _XMutableArrayGetQuickHashCode(XObjectRef _Nonnull self) {
    return 0;
}
XObjectRef _Nullable _XMutableArrayGetObject(XObjectRef _Nonnull self, size_t index) {
    _XMutableArray_o * obj = (_XMutableArray_o *)self;
    return __XMutableArrayGetBucket(obj, index)->item;
}



// 把array的 从index到index+count， 替换成newcount个NULL
//void __XMutableArrayReplace(XArrayRef _Nonnull self, size_t index, size_t count, XVector_s * _Nullable buffers, size_t buffersCount, XArrayElement_s * _Nullable removedItems) {
//    _XMutableArray_o * array = (_XMutableArray_o *)self;
//    if (count > 0) {
//        XAssert(removedItems, "");
//    }
//    size_t ncount = 0;
//    for (size_t i=0; i<buffersCount; i++) {
//        ncount += buffers[i].count;
//    }
//
//    XAssert(index + count <= array->deque.count, "");
//    size_t newTotalCount = array->deque.count - count + ncount;
//    if (NULL == array->buffer) {
//        XAssert(0 == array->count, "");
//        XAssert(0 == index, "");
//        XAssert(0 == count, "");
//        XDeque_s * buffer = XDequeAllocate(_XArrayElementSize, newTotalCount);
//        buffer->offset = (buffer->capacity - newTotalCount)/ 2;
//        array->count = newTotalCount;
//        array->buffer = buffer;
//        XDequeClear(buffer, _XArrayElementSize, newTotalCount, buffer->capacity - newTotalCount);
//    } else if (array->buffer->capacity < newTotalCount) {
//        XDeque_s * old = array->buffer;
//        XDeque_s * buffer = XDequeAllocate(_XArrayElementSize, newTotalCount);
//        buffer->offset = (buffer->capacity - count)/ 2;
//        XDequeCopyElements(buffer, _XArrayElementSize, index, count, removedItems);
//        XDequeCopyFrom(buffer, _XArrayElementSize, 0, index, old, 0);
//        XDequeCopyFrom(buffer, _XArrayElementSize, index + ncount, array->count - (index + count), old, index + count);
//        XDequeClear(buffer, _XArrayElementSize, newTotalCount, buffer->capacity - newTotalCount);
//        array->buffer = buffer;
//        array->count = newTotalCount;
//        XDequeDealloc(old, _XArrayElementSize);
//    } else {
//        size_t leftCount = index;
//        size_t rightCount = array->count - (index + count);
//
//        XDeque_s * buffer = array->buffer;
//        XDequeCopyElements(buffer, _XArrayElementSize, index, count, removedItems);
//
//        if (leftCount < rightCount) {
//            // 前半部分移动
//            if (ncount > count) {
//                //  head <<<
//
//                // insert
//                ssize_t insertedCount = ncount - count;
//                // offset <<<
//                buffer->offset = (buffer->offset + (buffer->capacity - insertedCount)) % buffer->capacity;
//                // data <<<
//                XDequeMove(buffer, _XArrayElementSize, insertedCount, index, -insertedCount);
//                array->count = newTotalCount;
//            } else if (ncount < count) {
//                //  head >>>
//
//                // remove
//                ssize_t removedCount = count - ncount;
//
//                XDequeMove(buffer, _XArrayElementSize, 0, index, removedCount);
//                XDequeClear(buffer, _XArrayElementSize, 0, removedCount);
//                buffer->offset = (buffer->offset + removedCount) % buffer->capacity;
//                array->count = newTotalCount;
//            }
//        } else {
//            // 后半部分移动
//
//            if (ncount > count) {
//                // insert
//                ssize_t insertedCount = ncount - count;
//                // tail >>>
//                XDequeMove(buffer, _XArrayElementSize, index+count, array->count - (index+count), insertedCount);
//                array->count = newTotalCount;
//            } else if (ncount < count) {
//                // remove
//                ssize_t removedCount = count - ncount;
//                // tail <<<
//                XDequeMove(buffer, _XArrayElementSize, index+count, array->count - (index+count), -removedCount);
//                XDequeClear(buffer, _XArrayElementSize, array->count-removedCount, removedCount);
//                array->count = newTotalCount;
//            }
//        }
//    }
//
//    size_t cindex = index;
//    for (size_t j=0; j<buffersCount; j++) {
//        for (size_t i=0; i<buffers[j].count; i++) {
//            __XMutableArrayGetBucket(array, i)->item = buffers[j].items[i].item;
//            cindex += 1;
//        }
//    }
//}

//// 在指定位置插入几个NULL
//void __XMutableArrayInsert(_XMutableArray_o * _Nonnull array, size_t index, size_t count) {
//    if (count <= 0) {
//        return;
//    }
//    XAssert(index <= array->count, "");
//    size_t newCount = array->count + count;
//    if (NULL == array->buffer) {
//        XAssert(0 == array->count, "");
//        XAssert(0 == index, "");
//        size_t capacity = __XMutableArrayCapacityAlign(newCount);
//        size_t size = sizeof(XDeque_s) + capacity * sizeof(XArrayElement_s);
//        XDeque_s * buffer = XAllocate(size);
//        buffer->capacity = capacity;
//        buffer->offset = (buffer->capacity - count)/ 2;
//        array->count = count;
//        array->buffer = buffer;
//        for (size_t i=0; i<count; i++) {
//            __XMutableArrayGetBucket(array, i)->item = NULL;
//        }
//    } else if (array->buffer->capacity < array->count + count) {
//        XDeque_s * old = array->buffer;
//        size_t capacity = __XMutableArrayCapacityAlign(newCount);
//        size_t size = sizeof(XDeque_s) + capacity * sizeof(XArrayElement_s);
//        XDeque_s * buffer = XAllocate(size);
//        buffer->capacity = capacity;
//        buffer->offset = (buffer->capacity - count)/ 2;
//
//        for (size_t i=0; i<index; i++) {
//            __XArrayRingBufferGetBucket(buffer, i)->item = __XArrayRingBufferGetBucket(old, i);
//        }
//        for (size_t i=index; i<index + count; i++) {
//            __XArrayRingBufferGetBucket(buffer, i)->item = NULL;
//        }
//        for (size_t i=index; i<array->count; i++) {
//            __XArrayRingBufferGetBucket(buffer, i + count)->item = __XArrayRingBufferGetBucket(old, i);
//        }
//        array->buffer = buffer;
//        array->count = newCount;
//        XDeallocate(old);
//    } else {
//        XDeque_s * buffer = array->buffer;
//        if (index < array->count / 2) {
//            // 前半部分移动
//            buffer->offset = (buffer->offset + (buffer->capacity - count)) % buffer->capacity;
//            for (size_t i=0; i<index; i++) {
//                __XArrayRingBufferGetBucket(buffer, i)->item = __XArrayRingBufferGetBucket(buffer, i+count);
//            }
//            for (size_t i=index; i<index + count; i++) {
//                __XArrayRingBufferGetBucket(buffer, i)->item = NULL;
//            }
//            array->count = newCount;
//        } else {
//            // 后半部分移动
//            for (size_t i=array->count-1; i>=index+count; i--) {
//                __XArrayRingBufferGetBucket(buffer, i+count)->item = __XArrayRingBufferGetBucket(buffer, i);
//            }
//            for (size_t i=index; i<index + count; i++) {
//                __XArrayRingBufferGetBucket(buffer, i)->item = NULL;
//            }
//            array->count = newCount;
//        }
//    }
//}
//
//// 在指定位置移除
//void __XMutableArrayRemove(_XMutableArray_o * _Nonnull array, size_t index, size_t count) {
//    if (count <= 0) {
//        return;
//    }
//    XAssert(index + count <= array->count, "");
//    size_t newCount = array->count - count;
//    XDeque_s * buffer = array->buffer;
//    if (index < array->count - (index + count)) {
//        // 前半部分移动
//        if (index > 0) {
//            for (size_t i=index+count-1; i>=count; i--) {
//                __XArrayRingBufferGetBucket(buffer, i)->item = __XArrayRingBufferGetBucket(buffer, i-count);
//            }
//        }
//        for (size_t i=0; i<count; i++) {
//            __XArrayRingBufferGetBucket(buffer, i)->item = NULL;
//        }
//        buffer->offset = (buffer->offset + count) % buffer->capacity;
//        array->count = newCount;
//    } else {
//        // 后半部分移动
//
//        for (size_t i=index; i<array->count - count; i++) {
//            __XArrayRingBufferGetBucket(buffer, i)->item = __XArrayRingBufferGetBucket(buffer, i+count);
//        }
//        for (size_t i=array->count-count; i<array->count; i++) {
//            __XArrayRingBufferGetBucket(buffer, i)->item = NULL;
//        }
//        array->count = newCount;
//    }
//
//}

void (*_Nullable replace)(XArrayRef _Nonnull array, size_t index, size_t count, XArrayElement_s * _Nullable items, size_t itemsCount, XArrayElement_s * _Nullable removedItems);

/// 返回retainedobject
void _XMutableArrayReplaceObjects(XArrayRef _Nonnull self, size_t index, size_t count, XArrayElement_s * _Nullable items, size_t itemsCount, bool_t allowReduceCapacity, XArrayElement_s * _Nullable removedItems) {
    _XMutableArray_o * array = (_XMutableArray_o *)self;
    XDeque_s * deque = _XMutableArrayGetDeque(array);
    XDequeReplaceElements(deque, _XArrayElementSize, index, count, items, itemsCount, allowReduceCapacity, removedItems);
}
XObjectRef _Nullable _XMutableArraySubarray(XObjectRef _Nonnull self, size_t index, size_t count) {
    _XMutableArray_o * array = (_XMutableArray_o *)self;
    ssize_t tcount = _XMutableArrayGetCount(self);

    XAssert(index + count <= tcount, "out of bounds");
    _XImmutableArray_o * result = __XImmutableArrayCreateInternal(0, count);
    XArrayElement_s * buckets = (XArrayElement_s *)result->items;

    for (size_t i=0; i<count; i++) {
        buckets[i].item = XObjectRetain(__XMutableArrayGetBucket(array, i + index)->item);
    }
    return result;
}
void _XMutableArrayEnumerate(XObjectRef _Nonnull self, ssize_t index, ssize_t count, bool_t reverse, XArrayEnumerate_f _Nonnull func, void * _Nullable context) {
    _XMutableArray_o * array = (_XMutableArray_o *)self;
    bool_t stop = false;
    if (reverse) {
        for (ssize_t i=index+count - 1; i>=index; i--) {
            func(i, __XMutableArrayGetBucket(array, i)->item, context, &stop);
            if (stop) {
                return;
            }
        }
    } else {
        for (ssize_t i=index; i<index+count; i++) {
            func(i, __XMutableArrayGetBucket(array, i)->item, context, &stop);
            if (stop) {
                return;
            }
        }
    }
}
XObjectRef _Nullable _XMutableArrayCopy(XObjectRef _Nonnull self) {
    return _XMutableArraySubarray(self, 0, _XMutableArrayGetCount(self));
}
XObjectRef _Nullable _XMutableArrayCopyAndRelease(XObjectRef _Nonnull self) {
    XObjectRef result = _XMutableArraySubarray(self, 0, _XMutableArrayGetCount(self));
    XObjectRelease(self);
    return result;
}
void _XMutableArrayResize(XObjectRef _Nonnull self, ssize_t minCapacity) {
    _XMutableArray_o * array = (_XMutableArray_o *)self;
    XDeque_s * deque = _XMutableArrayGetDeque(array);
    XDequeResize(deque, _XArrayElementSize, minCapacity);
}

const _XArrayApi_s _XArrayApiImmutable = {
    .getCount = _XImmutableArrayGetCount,
    .getObject = _XImmutableArrayGetObject,
    .copy = _XImmutableArrayCopy,
    .getSubarray = _XImmutableArraySubarray,
    .enumerate = _XImmutableArrayEnumerate,
    .deinit = _XImmutableArrayDeinit,
    .getHashCode = _XImmutableArrayGetHashCode,
    .getQuickHashCode = _XImmutableArrayGetQuickHashCode,
};

const _XArrayApi_s _XArrayApiMutable = {
    .getCount = _XMutableArrayGetCount,
    .getObject = _XMutableArrayGetObject,
    .replace = _XMutableArrayReplaceObjects,
    .copy = _XMutableArrayCopy,
    .getSubarray = _XMutableArraySubarray,
    .enumerate = _XMutableArrayEnumerate,
    .deinit = _XMutableArrayDeinit,
    .getHashCode = _XMutableArrayGetHashCode,
    .getQuickHashCode = _XMutableArrayGetQuickHashCode,
    .resize = _XMutableArrayResize,
};

const _XArrayApi_s _XArrayApiImmutableBuilder = {
    .getCount = _XImmutableArrayGetCount,
    .getObject = _XImmutableArrayGetObject,
    .copy = _XArrayBuilderCopy,
    .getSubarray = _XArrayBuilderSubarray,
    .enumerate = _XArrayBuilderEnumerate,
    .deinit = _XImmutableArrayDeinit,
    .getHashCode = _XArrayBuilderGetHashCode,
    .getQuickHashCode = _XArrayBuilderGetQuickHashCode,
};
