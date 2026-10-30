
#include "XRuntimeInternal.h"
#include <stdatomic.h>
#include "XObject.h"

_Static_assert(sizeof(size_t) == sizeof(size_t), "unknown error");
_Static_assert(sizeof(_Atomic(uintptr_t)) == sizeof(size_t), "unknown error");
_Static_assert(sizeof(_Atomic(uint32_fast_t)) == sizeof(uint32_t), "unknown error");
_Static_assert(sizeof(_Atomic(uint64_fast_t)) == sizeof(uint64_t), "unknown error");

_Static_assert(CX_TARGET_RT_64_BIT || CX_TARGET_RT_32_BIT, "unknown rt");

#pragma mark - layout

XObjectRef _Nonnull _XHeapObjectAs(XObjectRef _Nonnull ref, XClassRef _Nonnull cls, const char * _Nonnull func) {
    XAssert(!XObjectIsTaggedObject(ref), "not heap object");
    XAssert(__XHeapObjectGetClass(ref) == cls, "");
    return ref;
}

XClassRef _Nonnull __XTaggedObjectGetClass(uintptr_t ref) {
    static XClassRef _Nullable __XRTaggedTypeClassTable[7] = {
        XNumberClass,
        XDateClass,
        XDataClass,
        XStringClass,
        NULL,
        NULL,
    };
    
    static XClassRef _Nullable __XRTaggedTypeScopeBClassTable[30] = {
        NULL,
    };
    static XClassRef _Nullable __XRTaggedTypeScopeCClassTable[64] = {
        XBoolClass,
        NULL,
    };
    
    size_t v = __XTaggedDecode(ref);
    size_t offset = (v & X_TaggedObject_ScopeATypeMask) >> X_TaggedObject_ScopeATypeShift;
    
    switch (offset) {
        case X_TaggedObject_ScopeATypeReadB: {
            size_t scopeBOffset = (v & X_TaggedObject_ScopeBTypeMask) >> X_TaggedObject_ScopeBTypeShift;
            switch (scopeBOffset) {
                case 0: {
                    abort();
                }
                    break;
                case X_TaggedObject_ScopeBTypeReadC: {
                    size_t scopeCOffset = (v & X_TaggedObject_ScopeCTypeMask) >> X_TaggedObject_ScopeCTypeShift;
                    XClassRef cls = __XRTaggedTypeScopeCClassTable[scopeCOffset];
                    XAssert(cls, "");
                    return cls;
                }
                default: {
                    XClassRef cls = __XRTaggedTypeScopeBClassTable[scopeBOffset-1];
                    XAssert(cls, "");
                    return cls;
                }
            }
        }
        default: {
            XClassRef cls = __XRTaggedTypeClassTable[offset-1];
            XAssert(cls, "");
            return cls;
        }
    }
}

XClassRef _Nonnull XObjectGetClass(XObjectRef _Nonnull obj) {
    if (XObjectIsTaggedObject(obj)) {
        return __XTaggedObjectGetClass((uintptr_t)obj);
    } else {
        return __XHeapObjectGetClass(obj);
    }
}
size_t XObjectGetLayout(XObjectRef _Nonnull obj) {
    if (XObjectIsTaggedObject(obj)) {
        return 0;
    } else {
        return __XHeapObjectGetLayout(obj);
    }
}

size_t XObjectCheckGetLayout(XObjectRef _Nonnull obj, XClassRef _Nonnull cls) {
    XAssert(cls, "");
    if (XObjectIsTaggedObject(obj)) {
        XAssert(cls == __XTaggedObjectGetClass((uintptr_t)obj), "");
        return 0;
    } else {
        size_fast_t _xinfo = atomic_load(&(((XObjectBase_o *)obj)->_xinfo));
        XAssert(XInfo_MarkNotXObject != (_xinfo & XInfo_MarkMask), "");
        XAssert(cls == ((XObjectBase_o *)obj)->_cls, "");
        return (_xinfo & XInfo_LayoutMask) >> XInfo_LayoutShift;
    }
}

void XObjectResetLayout(XObjectRef _Nonnull obj, size_t layout) {
    XAssert(layout <= XInfo_LayoutMax, "layout error");
    if (XObjectIsTaggedObject(obj)) {
        abort();
    } else {
        size_t layoutBits = layout << XInfo_LayoutShift;
        _Atomic(size_fast_t) * xinfoPtr = &(((XObjectBase_o *)obj)->_xinfo);
        size_fast_t xinfo = atomic_load(xinfoPtr);
        XAssert(XInfo_MarkNotXObject != (xinfo & XInfo_MarkMask), "");
        size_fast_t newXinfo = 0;
        do {
            xinfo = atomic_load(xinfoPtr);
            if ((xinfo & XInfo_LayoutMask) == layoutBits) {
                return;
            }
            newXinfo = (xinfo & (~XInfo_LayoutMask)) | layoutBits;
        } while (!atomic_compare_exchange_strong(xinfoPtr, &xinfo, newXinfo));
    }
}

size_t XObjectGetInstanceSize(XObjectRef _Nonnull object) {
    if (XObjectIsTaggedObject(object)) {
        return 0;
    } else {
        XClassRef cls = __XHeapObjectGetClass(object);
        return cls->allocator->getInstanceSize(cls, object);
    }
}

bool_t XObjectIsTaggedObject(XObjectRef _Nonnull obj) {
    XAssert(obj, "");
    return ((uintptr_t)obj & X_TaggedObjectFlag) == X_TaggedObjectFlag;
}

#pragma mark - Hasher

void XHasherCombineByte16(XHasher _Nonnull hasher, const XByte16 * _Nonnull v) {
    XAssert(v, "");
    ((_XHasher *)hasher)->combine(hasher, v->content, 16);
}

void XHasherCombineAddress(XHasher _Nonnull hasher, XPtr _Nullable v) {
    uint64_t tmp = (uint64_t)(uintptr_t)v;
    ((_XHasher *)hasher)->combine(hasher, (const uint8_t *)&tmp, 8);
}
void XHasherCombineUInt32(XHasher _Nonnull hasher, uint32_t v) {
    ((_XHasher *)hasher)->combine(hasher, (const uint8_t *)&v, 4);
}


void XHasherCombineBytes(XHasher _Nonnull hasher, uint8_t * _Nullable buffer, size_t size) {
    ((_XHasher *)hasher)->combine(hasher, buffer, size);
}
XHashCode XHasherFinalize(XHasher _Nonnull hasher) {
    return ((_XHasher *)hasher)->finalize(hasher);
}


#pragma mark - Life

XObjectRef _Nullable XObjectCopy(void * _Nullable obj) {
    if (NULL == obj) {
        return obj;
    }
    if (XObjectIsTaggedObject(obj)) {
        return obj;
    } else {
        XClassRef type = __XHeapObjectGetClass(obj);
        return type->copy(obj);
    }
}

static inline XObjectRef _Nullable __XHeapObjectRetain(XObjectRef _Nonnull ref) {
    XClassRef type = __XHeapObjectGetClass(ref);
    return type->allocator->retain(type, ref);
}

static inline void __XHeapObjectRelease(XObjectRef _Nonnull ref) {
    XClassRef type = __XHeapObjectGetClass(ref);
    type->allocator->release(type, ref);
}

XObjectRef _Nullable XObjectRetain(void * _Nullable obj) {
    if (NULL == obj) {
        return obj;
    }
    if (XObjectIsTaggedObject(obj)) {
        return obj;
    } else {
        return __XHeapObjectRetain(obj);
    }
}

void XObjectRelease(void * _Nullable obj) {
    if (NULL == obj) {
        return;
    }
    if (!XObjectIsTaggedObject(obj)) {
        __XHeapObjectRelease(obj);
    }
}

XHashByte16_t __XBytesHashContent(const unsigned char * _Nullable content, size_t length) {
    return XMurmur3Hash128((const XPtr)(content), length, 0xEE6B27EB);
}

#pragma mark - XWeakStorage

extern _XWeakStorage_o * _Nonnull _XWeakStorageCreateWithHeapObject(_XObject_o * _Nonnull object);

XWeakStorageRef _Nonnull XWeakStorageCreate(XObjectRef _Nonnull object) {
    XAssert(!XObjectIsTaggedObject(object), "object error");
    return _XWeakStorageCreateWithHeapObject((_XObject_o *)object);
}

extern XObjectRef _Nullable _XWeakStorageTakeRetainedObject(_XWeakStorage_o * _Nonnull weakStorage, const char * _Nonnull func);

XObjectRef _Nullable XWeakStorageTakeRetainedObject(XWeakStorageRef _Nonnull weakStorage) {
    XAssert(!XObjectIsTaggedObject(weakStorage), "weakStorage error");
    _XWeakStorage_o * _weakStorage = _XHeapObjectAs(weakStorage, XWeakStorageClass, __func__);
    return _XWeakStorageTakeRetainedObject(_weakStorage, __func__);
}

void _XWeakStorageDeinit(XObjectRef _Nonnull self) {
    _XWeakStorage_o * weakStorage = (_XWeakStorage_o *)self;
    size_fast_t rcInfo = atomic_load(&(weakStorage->_originalXinfoe));
    XAssert(XInfo_MarkObjectUsingWeakStorage != (rcInfo & XInfo_MarkMask), "");
    XAssert((uintptr_t)NULL == atomic_load(&(weakStorage->original)), "");
}


#pragma mark - ------------------------------------------------Init---------------------------------------------------------

#pragma mark - Init

void __XRuntimeInit(void) {
}
