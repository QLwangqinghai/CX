
#include "XRuntimeInternal.h"

typedef struct {
    ssize_t (*_Nonnull getCount)(XMessageRef _Nonnull message);
    XMessageElement_s (*_Nonnull getElement)(XMessageRef _Nonnull message, size_t index);
    XObjectRef _Nullable (*_Nonnull getObject)(XMessageRef _Nonnull message, int32_t key, bool_t * _Nullable isContain);
    void (*_Nonnull enumerate)(XMessageRef _Nonnull message, XMessageEnumerate_f _Nonnull func, void * _Nullable context);
    void (*_Nullable setObject)(XMessageRef _Nonnull message, int32_t key, XObjectRef _Nullable object, XObjectRef _Nullable * _Nullable old);
    void (*_Nullable removeObject)(XMessageRef _Nonnull message, int32_t key, XObjectRef _Nullable * _Nullable old);
    XObjectRef _Nonnull (*_Nonnull copy)(XMessageRef _Nonnull message);
    void (*_Nonnull deinit)(XMessageRef _Nonnull message);
    size_t (*_Nonnull getHashCode)(XMessageRef _Nonnull message);
    size_t (*_Nonnull getQuickHashCode)(XMessageRef _Nonnull message);
} _XMessageApi_s;

extern const _XMessageApi_s _XMessageApiImmutable;
extern const _XMessageApi_s _XMessageApiMutable;
extern const _XMessageApi_s _XMessageApiImmutableBuilder;

const _XMessageApi_s * _Nullable _XMessageApiTable[XInfo_LayoutCount] = {
    NULL,
    &_XMessageApiImmutable,
    &_XMessageApiMutable,
    &_XMessageApiImmutableBuilder,
};

const _XMessageApi_s * _Nonnull __XMessageGetApi(XMessageRef _Nonnull message) {
    size_t layout = XObjectGetLayout(message);
    const _XMessageApi_s * api = _XMessageApiTable[layout];
    XAssert(api, "");
    return api;
}

#define _XMessageElementSize sizeof(XMessageElement_s)

_XImmutableMessage_o _XMessageEmpty = {
    ._runtime = XObjectBaseMakeStaticStrongOnlyWithLayout(XMessageClass, __XCollectionLayoutImmutable),
    ._hashCode = ATOMIC_VAR_INIT(0),
    .count = 0,
    .stepLength = 1,
};

_XImmutableMessage_o * _Nonnull __XImmutableMessageCreateInternal(XObjectOption option, int32_t count, size_t layout, bool_t shouldClear) {
    size_t payloadSize = sizeof(int32_t) * count + sizeof(int32_t) * count + sizeof(XObjectRef) * count;
    size_t size = sizeof(_XImmutableMessage_o) + payloadSize;
    _XImmutableMessage_o * message = XObjectAllocate(XMessageClass, option, size, layout);
    *(int32_t *)&(message->count) = count;
    *(int32_t *)&(message->stepLength) = 0;
    atomic_store(&(message->_hashCode), 0);
    if (shouldClear) {
        bzero(message->payload, payloadSize);
    }
    return message;
}

ssize_t XMessageGetCount(XMessageRef _Nonnull self) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->getCount(self);
}

XObjectRef _Nullable XMessageGetAssignObject(XMessageRef _Nonnull self, int32_t key, bool_t * _Nullable isContain) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->getObject(self, key, isContain);
}
XObjectRef _Nullable XMessageGetObject(XMessageRef _Nonnull self, int32_t key, bool_t * _Nullable isContain) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    XObjectRef result = api->getObject(self, key, isContain);
    return XObjectRetain(result);
}
XMessageElement_s XMessageGetAssignElement(XMessageRef _Nonnull self, ssize_t index) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    XAssert(index >= 0, "");
    XAssert(index < api->getCount(self), "");
    return api->getElement(self, index);
}
XMessageElement_s XMessageGetElement(XMessageRef _Nonnull self, ssize_t index) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    XAssert(index >= 0, "");
    XAssert(index < api->getCount(self), "");
    XMessageElement_s result = api->getElement(self, index);
    XObjectRetain(result.value);
    return result;
}
void XMessageEnumerate(XMessageRef _Nonnull self, XMessageEnumerate_f _Nonnull func, void * _Nullable context) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->enumerate(self, func, context);
}
void XMutableMessageSetObject(XMessageRef _Nonnull self, int32_t key, XObjectRef _Nullable object, XObjectRef _Nullable * _Nullable old) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->setObject(self, key, object, old);
}
void XMutableMessageRemoveObject(XMessageRef _Nonnull self, int32_t key, XObjectRef _Nullable * _Nullable old) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->removeObject(self, key, old);
}

ssize_t _XImmutableMessageGetCount(XMessageRef _Nonnull self) {
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    return message->count;
}

/// return unretained object
XObjectRef _Nullable _XImmutableMessageGetObject(XMessageRef _Nonnull self, int32_t key, bool_t * _Nullable isContain) {
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    _XImmutableMessagePayload_s payload = _XImmutableMessageGetPayload(message);
    uint64_t bucketIndex = key / message->stepLength;
    if (bucketIndex >= message->count) {
        if (isContain) {
            *isContain = false;
        }
        return NULL;
    }
    
    int32_t start = payload.buckets[bucketIndex];
    int32_t end = message->count;

    if (bucketIndex < message->count - 1) {
        end = payload.buckets[bucketIndex + 1];
    }
    int32_t low = start;
    int32_t high = end - 1;
    
    while (low <= high) {
        int32_t mid = low + (high - low) / 2;
        int32_t elementKey = payload.keys[mid];
        if (elementKey > key) {
            high = mid - 1;
        } else if (elementKey < key) {
            low = mid + 1;
        } else {
            if (isContain) {
                *isContain = true;
            }
            return payload.values[mid];
        }
    }
    if (isContain) {
        *isContain = false;
    }
    return NULL;
}

XMessageElement_s _XImmutableMessageGetElement(XMessageRef _Nonnull self, size_t index) {
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    XAssert(index < message->count, "");
    _XImmutableMessagePayload_s payload = _XImmutableMessageGetPayload(message);
    XMessageElement_s result = {
        .key = payload.keys[index],
        .value = payload.values[index],
    };
    return result;
}
XMessageRef _Nonnull _XImmutableMessageCopy(XMessageRef _Nonnull message) {
    return XObjectRetain(message);
}
XMessageRef _Nonnull _XImmutableMessageCopyAndRelease(XMessageRef _Nonnull message) {
    return message;
}
void _XImmutableMessageEnumerate(XMessageRef _Nonnull self, XMessageEnumerate_f _Nonnull func, void * _Nullable context) {
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    XAssert(func, "");
    _XImmutableMessagePayload_s payload = _XImmutableMessageGetPayload(message);
    for (ssize_t index=0; index<message->count; index++) {
        bool_t stop = false;
        func(payload.keys[index], payload.values[index], context, &stop);
        if (stop) {
            return;
        }
    }
}
void _XImmutableMessageDeinit(XMessageRef _Nonnull self) {
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    _XImmutableMessagePayload_s payload = _XImmutableMessageGetPayload(message);
    for (ssize_t index=0; index<message->count; index++) {
        XObjectRelease(payload.values[index]);
        payload.values[index] = NULL;
    }
}

void __XMessageEnumerateHash(int32_t key, XObjectRef _Nullable object, void * _Nullable context, bool_t * _Nonnull stop) {
    XCollectionHasher_s * hasher = (XCollectionHasher_s *)context;
    XCollectionHasherCombine(hasher, key, ((size_t)key) ^ XObjectGetHashCode(object));
}

size_t __XMessageHash(const _XMessageApi_s * _Nonnull api, XMessageRef _Nonnull obj) {
    XCollectionHasher_s hasher = {};
    ssize_t count = api->getCount(obj);
    XCollectionHasherInit(&hasher, (size_t)count);
    api->enumerate(obj, __XMessageEnumerateHash, &hasher);
    return XCollectionHasherFinalize(&hasher);
}

size_t _XImmutableMessageGetHashCode(XMessageRef _Nonnull self) {
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    size_t code = atomic_load(&(message->_hashCode));
    if (0 == code) {
        code = __XMessageHash(&_XMessageApiImmutable, self);
        __XImmutableCollectionUpdateHashCode(&(message->_hashCode), code, __func__);
    }
    return code;
}

size_t _XImmutableMessageGetQuickHashCode(XMessageRef _Nonnull self) {
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    return atomic_load(&(message->_hashCode));
}

#pragma mark - builder

/// create immutable array
XMessageRef _Nonnull XMessageBuilderCreateWithCount(XObjectOption option, ssize_t count) {
    XAssert(count >= 0, "");
    _XImmutableMessage_o * message = __XImmutableMessageCreateInternal(option, (int32_t)count, __XCollectionLayoutImmutableBuilder, true);
    return message;
}

XObjectRef _Nullable _XMessageBuilderCopy(XObjectRef _Nonnull self) {
    abort();
}
XObjectRef _Nullable _XMessageBuilderGetObject(XMessageRef _Nonnull self, int32_t key, bool_t * _Nullable isContain) {
    abort();
}

void _XMessageBuilderEnumerate(XObjectRef _Nonnull self, XMessageEnumerate_f _Nonnull func, void * _Nullable context) {
    abort();
}
size_t _XMessageBuilderGetHashCode(XObjectRef _Nonnull self) {
    abort();
}
size_t _XMessageBuilderGetQuickHashCode(XObjectRef _Nonnull self) {
    abort();
}

XMessageElement_s XMessageBuilderReplaceWithRetainedValue(XObjectRef _Nonnull self, ssize_t index, int32_t key, XObjectRef _Nullable value) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    XAssert(XObjectGetLayout(self) == __XCollectionLayoutImmutableBuilder, "");
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    _XImmutableMessagePayload_s payload = _XImmutableMessageGetPayload(message);
    XMessageElement_s old = {
        .key = payload.keys[index],
        .value = payload.values[index],
    };
    payload.keys[index] = key;
    payload.values[index] = XObjectCopy(value);
    XObjectRelease(value);
    return old;
}
void XMessageBuilderComplete(XObjectRef _Nonnull self) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    XAssert(XObjectGetLayout(self) == __XCollectionLayoutImmutableBuilder, "");
    _XImmutableMessage_o * _Nonnull message = (_XImmutableMessage_o *)self;
    _XImmutableMessagePayload_s payload = _XImmutableMessageGetPayload(message);
    int32_t key = 0;
    for (ssize_t i = 0; i < message->count; i++) {
        int32_t ckey = payload.keys[i];
        XAssert(ckey > key, "");
        key = ckey;
    }
    
    if (message->count == 0) {
        *(int32_t *)(&(message->stepLength)) = 1;
    } else {
        *(int32_t *)(&(message->stepLength)) = key/(message->count) + 1;
    }
    
    int32_t idx = 0;
    for (int32_t i = 0; i < message->count; i++) {
        payload.buckets[i] = idx;
        int32_t start = message->stepLength * i;
        while (payload.keys[idx] < start) {
            idx += 1;
        }
    }

    XObjectResetLayout(self, __XCollectionLayoutImmutable);
}



#pragma mark - mutable
static inline XMessageElement_s * __XMutableMessageGetElement(_XMutableMessage_o * _Nonnull message, size_t index) {
    
    return (XMessageElement_s *)XDequeElementAtIndex(&(message->storage), index);
}

ssize_t _XMutableMessageGetCount(XMessageRef _Nonnull self) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    return XDequeGetCount(&(message->storage));
}

XMessageElement_s _XMutableMessageGetElement(XMessageRef _Nonnull self, size_t index) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    XMessageElement_s element = {};
    XMessageElement_s * tmp = __XMutableMessageGetElement(message, index);
    memcpy(&element, tmp, sizeof(XMessageElement_s));
    return element;
}

XObjectRef _Nullable _XMutableMessageGetObject(XMessageRef _Nonnull self, int32_t key, bool_t * _Nullable isContain) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    XDeque_s * bucket = &(message->storage);
    ssize_t start = 0;
    ssize_t end = XDequeGetCount(bucket);
    ssize_t low = start;
    ssize_t high = end - 1;
    
    while (low <= high) {
        ssize_t mid = low + (high - low) / 2;
        XMessageElement_s * element = __XMutableMessageGetElement(message, mid);
        if (element->key > key) {
            high = mid - 1;
        } else if (element->key < key) {
            low = mid + 1;
        } else {
            if (isContain) {
                *isContain = true;
            }
            return element->value;
        }
    }
    if (isContain) {
        *isContain = false;
    }
    return NULL;
}

void __XMutableMessageInsert(_XMutableMessage_o * _Nonnull message, size_t index, const XMessageElement_s * _Nonnull element) {
    XDequeInsertElement(&(message->storage), _XMessageElementSize, index, element);
}
void __XMutableMessageRemove(_XMutableMessage_o * _Nonnull message, size_t index, XMessageElement_s * _Nonnull element) {
    XDequeRemoveElement(&(message->storage), _XMessageElementSize, index, true, element);
}
XObjectRef _Nullable _XMutableMessageReplaceObject(XMessageRef _Nonnull self, int32_t key, XObjectRef _Nullable value) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    size_t count = _XMutableMessageGetCount(self);
    XMessageElement_s newElement = {
        .key = key,
        .value = value,
    };
    if (count <= 0) {
        __XMutableMessageInsert(message, 0, &newElement);
        return NULL;
    } else if (count == 1) {
        XMessageElement_s * element = __XMutableMessageGetElement(message, 0);
        if (element->key > key) {
            __XMutableMessageInsert(message, 0, &newElement);
            return NULL;
        } else if (element->key < key) {
            __XMutableMessageInsert(message, 1, &newElement);
            return NULL;
        } else {
            XObjectRef result = element->value;
            element->value = value;
            return result;
        }
    } else {
        ssize_t low = 0;
        ssize_t high = count - 1;
        {
            XMessageElement_s * element = __XMutableMessageGetElement(message, low);
            if (element->key > key) {
                __XMutableMessageInsert(message, 0, &newElement);
                return NULL;
            } else if (element->key == key) {
                XObjectRef result = element->value;
                element->value = value;
                return result;
            }
        }
        {
            XMessageElement_s * element = __XMutableMessageGetElement(message, high);
            if (element->key < key) {
                __XMutableMessageInsert(message, count, &newElement);
                return NULL;
            } else if (element->key == key) {
                XObjectRef result = element->value;
                element->value = value;
                return result;
            }
        }
        
        while (low < high) {
            ssize_t mid = low + (high - low) / 2;
            XMessageElement_s * element = __XMutableMessageGetElement(message, mid);
            if (mid == low) {
                XAssert(element->key < key, "");
                __XMutableMessageInsert(message, mid + 1, &newElement);
                return NULL;
            }
            
            if (element->key > key) {
                high = mid;
            } else if (element->key < key) {
                low = mid;
            } else {
                XObjectRef result = element->value;
                element->value = value;
                return result;
            }
        }
        return NULL;
    }
}

// update value, 如果有oldElement， 返回true
void _XMutableMessageSetObject(XMessageRef _Nonnull self, int32_t key, XObjectRef _Nullable value, XObjectRef _Nullable * _Nullable old) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    XObjectRef obj = _XMutableMessageReplaceObject(message, key, XObjectCopy(value));
    if (old) {
        *old = obj;
    } else {
        XObjectRelease(obj);
    }
}

// 如果有oldElement， 返回true
void _XMutableMessageRemove(XMessageRef _Nonnull self, int32_t key, XObjectRef _Nullable * _Nullable old) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    ssize_t low = 0;
    ssize_t high = _XMutableMessageGetCount(self) - 1;
    ssize_t location = -1;
    
    while (low <= high) {
        ssize_t mid = low + (high - low) / 2;
        XMessageElement_s * element = __XMutableMessageGetElement(message, mid);
        if (element->key > key) {
            high = mid - 1;
        } else if (element->key < key) {
            low = mid + 1;
        } else {
            location = mid;
            XObjectRef result = element->value;
            XMessageElement_s removed = {};
            __XMutableMessageRemove(message, location, &removed);
            if (old) {
                *old = result;
            } else {
                XObjectRelease(result);
            }
            return;
        }
    }
}

void _XMutableMessageEnumerate(XMessageRef _Nonnull self, XMessageEnumerate_f _Nonnull func, void * _Nullable context) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    ssize_t count = _XMutableMessageGetCount(self);
    bool_t stop = false;
    for (ssize_t index=0; index<count; index++) {
        XMessageElement_s * element = __XMutableMessageGetElement(message, index);
        func(element->key, element->value, context, &stop);
        if (stop) {
            return;
        }
    }
}
XMessageRef _Nonnull _XMutableMessageCopy(XMessageRef _Nonnull self) {
    _XMutableMessage_o * message = (_XMutableMessage_o *)self;
    ssize_t count = _XMutableMessageGetCount(message);
    if (count == 0) {
        return (XMessageRef)&_XMessageEmpty;
    }
    _XImmutableMessage_o * result = __XImmutableMessageCreateInternal(0, (int32_t)count, __XCollectionLayoutImmutable, false);
    _XImmutableMessagePayload_s payload = _XImmutableMessageGetPayload(result);
    
    int32_t key = 0;
    for (ssize_t i = 0; i < count; i++) {
        XMessageElement_s element = _XMutableMessageGetElement(message, i);
        payload.keys[i] = element.key;
        payload.values[i] = XObjectCopy(element.value);
        key = element.key;
    }
    
    if (count == 0) {
        *(int32_t *)(&(result->stepLength)) = 1;
    } else {
        *(int32_t *)(&(result->stepLength)) = key/count + 1;
    }
    
    int32_t idx = 0;
    for (int32_t i = 0; i < count; i++) {
        payload.buckets[i] = idx;
        int32_t start = result->stepLength * i;
        while (payload.keys[idx] < start) {
            idx += 1;
        }
    }
    return result;
}
XMessageRef _Nonnull _XMutableMessageCopyAndRelease(XMessageRef _Nonnull self) {
    XMessageRef result = _XMutableMessageCopy(self);
    XObjectRelease(self);
    return result;
}

void _XMutableMessageDeinit(XMessageRef _Nonnull self) {
    _XMutableMessage_o * _Nonnull message = (_XMutableMessage_o *)self;
    
    ssize_t count = _XMutableMessageGetCount(self);
    for (ssize_t index=0; index<count; index++) {
        XMessageElement_s * element = __XMutableMessageGetElement(message, index);
        XObjectRelease(element->value);
        element->value = NULL;
    }
    XDequeDeinit(&(message->storage));
}

size_t _XMutableMessageGetHashCode(XMessageRef _Nonnull self) {
    return __XMessageHash(&_XMessageApiMutable, self);
}
size_t _XMutableMessageGetQuickHashCode(XMessageRef _Nonnull self) {
    return 0;
}


void _XMessageDeinit(XObjectRef _Nonnull self)  {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->deinit(self);
}
size_t _XMessageGetHashCode(XObjectRef _Nonnull self) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->getHashCode(self);
}

bool_t _XMessageEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    const _XMessageApi_s * lapi = __XMessageGetApi(lhs);
    const _XMessageApi_s * rapi = __XMessageGetApi(rhs);
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
        XMessageElement_s lhsobj = lapi->getElement(lhs, i);
        XMessageElement_s rhsobj = rapi->getElement(rhs, i);
        if (lhsobj.key == rhsobj.key && !XObjectEqual(lhsobj.value, rhsobj.value)) {
            return false;
        }
    }
    return true;
}
void _XMessageDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XMessageDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
XObjectRef _Nonnull _XMessageCopy(XObjectRef _Nonnull self) {
    XAssert(XObjectGetClass(self) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(self);
    return api->copy(self);
}

const _XMessageApi_s _XMessageApiImmutable = {
    .getCount = _XImmutableMessageGetCount,
    .getObject = _XImmutableMessageGetObject,
    .getElement = _XImmutableMessageGetElement,
    .copy = _XImmutableMessageCopy,
    .enumerate = _XImmutableMessageEnumerate,
    .deinit = _XImmutableMessageDeinit,
    .getHashCode = _XImmutableMessageGetHashCode,
    .getQuickHashCode = _XImmutableMessageGetQuickHashCode,
};

const _XMessageApi_s _XMessageApiMutable = {
    .getCount = _XMutableMessageGetCount,
    .getElement = _XMutableMessageGetElement,
    .getObject = _XMutableMessageGetObject,
    .setObject = _XMutableMessageSetObject,
    .removeObject = _XMutableMessageRemove,
    .copy = _XMutableMessageCopy,
    .enumerate = _XMutableMessageEnumerate,
    .deinit = _XMutableMessageDeinit,
    .getHashCode = _XMutableMessageGetHashCode,
    .getQuickHashCode = _XMutableMessageGetQuickHashCode,
};

const _XMessageApi_s _XMessageApiImmutableBuilder = {
    .getCount = _XImmutableMessageGetCount,
    .getObject = _XMessageBuilderGetObject,
    .getElement = _XImmutableMessageGetElement,
    .copy = _XMessageBuilderCopy,
    .enumerate = _XMessageBuilderEnumerate,
    .deinit = _XImmutableMessageDeinit,
    .getHashCode = _XMessageBuilderGetHashCode,
    .getQuickHashCode = _XMessageBuilderGetQuickHashCode,
};





// -----------------Immutable---------------


_XMutableMessage_o * _Nonnull __XMutableMessageCreate(size_t capacity) {
    size_t size = sizeof(_XMutableMessage_o);
    _XMutableMessage_o * message = XObjectAllocate(XMessageClass, 0, size, __XCollectionLayoutMutable);
    XDequeInit(&(message->storage), _XMessageElementSize, capacity);
    return message;
}

/// create immutable XMessage XMessageCreate(2, 1, obj1, 4, obj4)
XMessageRef _Nonnull XMessageCreate(ssize_t count, ...) {
    _XMutableMessage_o * message = __XMutableMessageCreate(count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        int32_t key = va_arg(ap, int32_t);
        XObjectRef object = va_arg(ap, XObjectRef);
        _XMutableMessageSetObject(message, key, XObjectCopy(object), NULL);
    }
    va_end(ap);
    XAssert(_XMutableMessageGetCount(message) == count, "");
    XMessageRef result = _XMutableMessageCopy(message);
    XObjectRelease(message);
    return result;
}

// ------------------- Mutable ----------------------------

/// create mutable array
XMessageRef _Nonnull XMutableMessageCreate(ssize_t count, ...) {
    _XMutableMessage_o * message = __XMutableMessageCreate(count);
    va_list ap;
    va_start(ap, count);
    for (ssize_t i = 0; i < count; i++) {
        int32_t key = va_arg(ap, int32_t);
        XObjectRef object = va_arg(ap, XObjectRef);
        _XMutableMessageSetObject(message, key, XObjectCopy(object), NULL);
    }
    va_end(ap);
    XAssert(_XMutableMessageGetCount(message) == count, "");
    return message;
}
XMessageRef _Nonnull XMutableMessageCreateWithMessage(XMessageRef _Nonnull message) {
    XAssert(XObjectGetClass(message) == XMessageClass, "");
    const _XMessageApi_s * api = __XMessageGetApi(message);
    ssize_t count = api->getCount(message);
    _XMutableMessage_o * result = __XMutableMessageCreate(count);
    for (ssize_t i = 0; i < count; i++) {
        XMessageElement_s element = api->getElement(message, i);
        _XMutableMessageSetObject(result, element.key, XObjectCopy(element.value), NULL);
    }
    return result;
}
XMessageRef _Nonnull XMutableMessageCreateWithCapacity(ssize_t capacity) {
    return __XMutableMessageCreate(capacity);
}
