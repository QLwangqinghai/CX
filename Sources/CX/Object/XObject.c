
#include "XRuntimeInternal.h"
#include "XObjectInternal.h"
#include "XAtomicInternal.h"

#define XRuntimeErrorCall XAssert(false, "XRuntimeErrorCall")

//对象释放时clear内存
const XObjectOption XObjectOptionStatic = 0x1;

const XStringOption XStringOptionClearWhenDealloc = 0x2;
const XDataOption XDataOptionClearWhenDealloc = 0x2;

#pragma mark - tool

//static inline int __XRCompareAddress(XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
//    if (lhs == rhs) {
//        return 0;
//    } else if (lhs < rhs) {
//        return -1;
//    } else {
//        return 1;
//    }
//};

#pragma mark - _XClass

void _XClassDeinit(XObjectRef _Nonnull self)  {
    XRuntimeErrorCall;
}
size_t _XClassGetHashCode(XObjectRef _Nonnull self) {
    return __XObjectGetHashCodeWithAddress(self);
}
bool_t _XClassEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    return lhs == rhs;
};
//int _XClassCompare(XClass _Nonnull self, XClass _Nonnull super, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
//    return __XRCompareAddress(lhs, rhs);
//};
void _XClassDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XClassDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

#pragma mark - XObjectDefault
void _XObjectDefaultDeinit(XObjectRef _Nonnull self)  {
    
}
XObjectRef _XObjectDefaultCopy(XObjectRef _Nonnull self) {
    return XObjectRetain(self);
}
XObjectRef _Nonnull _XObjectDefaultCopyAndRelease(XObjectRef _Nonnull self) {
    return self;
}

size_t _XObjectDefaultGetHashCode(XObjectRef _Nonnull self) {
    return __XObjectGetHashCodeWithAddress(self);
}
bool_t _XObjectDefaultEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    return lhs == rhs;
};
//int _XObjectCompare(XClass _Nonnull self, XClass _Nonnull super, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
//    return __XRCompareAddress(lhs, rhs);
//};
void _XObjectDefaultDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XObjectDefaultDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

#pragma mark - XBool

void _XBoolDeinit(XObjectRef _Nonnull self)  {
    XRuntimeErrorCall;
}
size_t _XBoolGetHashCode(XObjectRef _Nonnull self) {
    return __XHashSInt(XBoolGetValue(self) ? 2 : 1);
}
bool_t _XBoolEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    return XBoolGetValue(lhs) == XBoolGetValue(rhs);
}
void _XBoolDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XBoolDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

#pragma mark - XWeakStorage

/// imp
//void _XWeakStorageDeinit(XObjectRef _Nonnull self, XClass _Nonnull super);
size_t _XWeakStorageGetHashCode(XObjectRef _Nonnull self) {
    return __XObjectGetHashCodeWithAddress(self);
}
bool_t _XWeakStorageEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    return lhs == rhs;
};
void _XWeakStorageDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XWeakStorageDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}


#pragma mark - XValue

void _XValueDeinit(XObjectRef _Nonnull self) {
    _XValue_o * obj = (_XValue_o *)self;
    const XValueContentType_s * cls = obj->type;
    XAssert(cls, "type error");
}
size_t _XValueGetHashCode(XObjectRef _Nonnull self) {
    _XValue_o * obj = (_XValue_o *)self;
    size_t code = atomic_load(&(obj->_hashCode));
    if (0 == code) {
        const XValueContentType_s * cls = obj->type;
        XAssert(cls, "type error");
        XAssert(cls->getHashCode, "type.hash error");
        code = cls->getHashCode(cls, obj->bytes);
        if (0 == code) {
            code = 1;
        }
        __XImmutableCollectionUpdateHashCode(&(obj->_hashCode), code, __func__);
    }
    return code;
}

//static inline bool_t __XValueContentTypeNameEqual(const char * _Nonnull lhs, const char * _Nonnull rhs) {
//    if (lhs == rhs) {
//        return true;
//    }
//    return strcmp(lhs, rhs) == 0;
//}
//static inline bool_t __XValueContentTypeEqual(const XValueContentType_s * _Nonnull lhs, const XValueContentType_s * _Nonnull rhs) {
//    if (lhs == rhs) {
//        return true;
//    }
//    return lhs->size == rhs->size && lhs->hash == rhs->hash && lhs->equal == rhs->equal && lhs->describe == rhs->describe && lhs->debugDescribe == rhs->debugDescribe && __XValueContentTypeNameEqual(lhs->name, rhs->name);
//}

bool_t _XValueEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    _XValue_o * lref = (_XValue_o *)lhs;
    _XValue_o * rref = (_XValue_o *)rhs;
    const XValueContentType_s * lcls = lref->type;
    const XValueContentType_s * rcls = rref->type;

    // 快速hash 比较

    XAssert(lcls, "lhs type error");
    XAssert(rcls, "rhs type error");

    if (lref->type != rref->type) {
        return false;
    }
    return lcls->equal(lcls, lref->bytes, rref->bytes);
}

void _XValueDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {
    _XValue_o * obj = (_XValue_o *)self;
    const XValueContentType_s * cls = obj->type;
    XAssert(cls, "type error");
    XAssert(cls->describe, "type describe error");
    cls->describe(cls, obj->bytes, buffer);
}
void _XValueDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {
    _XValue_o * obj = (_XValue_o *)self;
    const XValueContentType_s * cls = obj->type;
    XAssert(cls, "type error");
    XAssert(cls->debugDescribe, "type debugDescribe error");
    cls->debugDescribe(cls, obj->bytes, buffer);
}

#pragma mark - XMessage

void _XMessageDeinit(XObjectRef _Nonnull self);

size_t _XMessageGetHashCode(XObjectRef _Nonnull self);
bool_t _XMessageEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
void _XMessageDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
void _XMessageDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
XObjectRef _Nonnull _XMessageCopy(XObjectRef _Nonnull self);
XObjectRef _Nonnull _XMessageCopyAndRelease(XObjectRef _Nonnull self);

#pragma mark - XArray

ssize_t XArrayGetCount(XArrayRef _Nonnull array);
XObjectRef _Nullable XArrayGetAssignObject(XArrayRef _Nonnull array, ssize_t index);
XObjectRef _Nullable XArrayGetRetainedObject(XArrayRef _Nonnull array, ssize_t index);

void _XArrayDeinit(XObjectRef _Nonnull self);
size_t _XArrayGetHashCode(XObjectRef _Nonnull self);
bool_t _XArrayEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
void _XArrayDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
void _XArrayDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
XObjectRef _Nonnull _XArrayCopy(XObjectRef _Nonnull self);
XObjectRef _Nonnull _XArrayCopyAndRelease(XObjectRef _Nonnull self);

extern size_t _XNumberGetInstanceSize(XObjectRef _Nonnull self);
extern size_t _XDataGetInstanceSize(XObjectRef _Nonnull self);
extern size_t _XStringGetInstanceSize(XObjectRef _Nonnull self);
extern size_t _XValueGetInstanceSize(XObjectRef _Nonnull self);

#define XObjectLifeCycleMethods(Name) .copy = _##Name##Copy,\
.deinit = _##Name##Deinit,\
.getHashCode = _##Name##GetHashCode,\
.equal = _##Name##Equal,\
.describe = _##Name##Describe,\
.debugDescribe = _##Name##DebugDescribe,

#pragma mark - domain

#define __XClassMakeStrongOnly(Name) {\
._runtime = XObjectBaseMakeStaticStrongOnly(&_XMetaClass),\
.domain = &__XObjectDomainX,\
.allocator = &_XAllocatorDefault,\
.name = XUtf8StringMake(Name),\
.allowWeak = 0,\
.instanceSize = sizeof(_##Name##_o),\
XObjectLifeCycleMethods(Name)\
}

#define __XClassMakeBool(Name) {\
._runtime = XObjectBaseMakeStaticStrongOnly(&_XMetaClass),\
.domain = &__XObjectDomainX,\
.allocator = &_XAllocatorDefault,\
.name = XUtf8StringMake(Name),\
.allowWeak = 0,\
.instanceSize = 0,\
XObjectLifeCycleMethods(Name)\
}

#define _XClassCopy _XObjectDefaultCopy
#define _XWeakStorageCopy _XObjectDefaultCopy
#define _XBoolCopy _XObjectDefaultCopy
#define _XNumberCopy _XObjectDefaultCopy
#define _XDateCopy _XObjectDefaultCopy
#define _XStringCopy _XObjectDefaultCopy
#define _XDataCopy _XObjectDefaultCopy
#define _XValueCopy _XObjectDefaultCopy

#define _XClassCopyAndRelease _XObjectDefaultCopyAndRelease
#define _XWeakStorageCopyAndRelease _XObjectDefaultCopyAndRelease
#define _XBoolCopyAndRelease _XObjectDefaultCopyAndRelease
#define _XNumberCopyAndRelease _XObjectDefaultCopyAndRelease
#define _XDateCopyAndRelease _XObjectDefaultCopyAndRelease
#define _XStringCopyAndRelease _XObjectDefaultCopyAndRelease
#define _XDataCopyAndRelease _XObjectDefaultCopyAndRelease
#define _XValueCopyAndRelease _XObjectDefaultCopyAndRelease

const XObjectDomain_s __XObjectDomainX = XObjectDomainMake(X);

const XClass_o _XMetaClass __attribute__((aligned(sizeof(size_t) * 8))) = {
    ._runtime = XObjectBaseMakeStaticStrongOnly(&_XMetaClass),
    .domain = &__XObjectDomainX,
    .allocator = &_XAllocatorDefault,
    .name = XUtf8StringMake(XClass),
    .instanceSize = sizeof(XClass_o),
    XObjectLifeCycleMethods(XClass)
};

const XClass_o _XNumberClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeStrongOnly(XNumber);
const XClass_o _XDateClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeStrongOnly(XDate);
const XClass_o _XValueClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeStrongOnly(XValue);
const XClass_o _XStringClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeStrongOnly(XString);
const XClass_o _XDataClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeStrongOnly(XData);
const XClass_o _XMessageClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeStrongOnly(XMessage);
const XClass_o _XArrayClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeStrongOnly(XArray);
const XClass_o _XBoolClass __attribute__((aligned(sizeof(size_t) * 8))) = __XClassMakeBool(XBool);
const XClass_o _XWeakStorageClass __attribute__((aligned(sizeof(size_t) * 8))) = {
    ._runtime = XObjectBaseMakeStaticStrongOnly(&_XMetaClass),
    .domain = &__XObjectDomainX,
    .allocator = &_XAllocatorDefault,
    .name = XUtf8StringMake(XWeakStorage),
    .instanceSize = sizeof(XClass_o),
    XObjectLifeCycleMethods(XWeakStorage)
};
//const XClassCompressed_s __XClassCompressedTable[XClassIdCurrentMax] = {
//
//    __XClassCompressedMake(XNumber, _XNumberGetInstanceSize),
//    __XClassCompressedMake(XDate, NULL),
//    __XClassCompressedMake(XValue, _XValueGetInstanceSize),
//    __XClassCompressedMake(XData, _XDataGetInstanceSize),
//    __XClassCompressedMake(XString, _XStringGetInstanceSize),
//    __XClassCompressedMake(XMessage, NULL),
//    __XClassCompressedMake(XArray, NULL),
//};


//
//
//void _XOProxyDeinit(XClass _Nonnull cls, XObjectRef _Nonnull obj, XClass _Nonnull objClass) {
//    _XOProxy * proxy = obj;
//    XProxy_t * content = &(proxy->content);
//    if (content->type->release) {
//        content->type->release(content->type, content->ptr);
//    }
//    content->type = NULL;
//    content->ptr = NULL;
//}
//
//const XClass_o _XClassProxy = __XClassMakeFoundationRoot(Proxy);
//XClass _Nonnull XClassProxy = (XClass)(&_XClassProxy);
//
//
//_XOProxy * _XRefAsProxy(XOProxy _Nonnull proxy, const char * _Nonnull func) {
//    XAssert(XClassProxy == XObjectGetClass(proxy), "")
//    return (_XOProxy *)proxy;
//}
//
//XOProxy _Nonnull XOProxyCreate(XObjectOption option, const XProxyType_t * _Nonnull type, XPtr _Nonnull ptr) {
//    XAssert(ptr, "");
//    XAssert(type, "");
//    _XOProxy * proxy = XClassAllocateInstance(XClassProxy, option);
//    XProxy_t * content = &(proxy->content);
//    content->type = type;
//    content->ptr = ptr;
//    return proxy;
//}
//XProxy_t XOProxyGetContent(XOProxy _Nonnull ref) {
//    _XOProxy * proxy = _XRefAsProxy(ref, __func__);
//    return proxy->content;
//}


//id (*sendMsg)(id, SEL) = (void *)objc_msgSend;
//
//id (*sendMsgSuper)(void *, SEL) = (void *)objc_msgSendSuper;

//struct objc_super {
//    XObjectRef _Nonnull self;
//    
//    /// 当前方法所在class
//    XObjectRef _Nonnull class;
//};
//
//void XObjectCall(void * _Nullable result, XObjectRef _Nonnull self, XObjectRef _Nonnull super) {
//}

#pragma mark - XClass

XObjectRef _Nonnull XObjectAllocate(XClassRef _Nonnull cls, XObjectOption flag, size_t size, size_t layout) {
    XAssert(cls, "cls error");
    return cls->allocator->allocate(cls, flag, size, layout);
}

#pragma mark - XObjectRef

bool_t XObjectIsKindOf(XObjectRef _Nonnull object, XClassRef _Nonnull cls) {
    XAssert(cls, "");
    return cls == XObjectGetClass(object);
}

bool_t XObjectIsClass(XObjectRef _Nonnull object) {
    return XObjectIsKindOf(object, XMetaClass);
}

bool_t XObjectIsMemberOf(XObjectRef _Nonnull object, XClassRef _Nonnull cls) {
    return XObjectGetClass(object) == cls;
}

#define _XObjectFindLifeCycleMethod(MethodName, ClassReceiver, MethodReceiver) MethodReceiver=ClassReceiver->MethodName




//bool_t ___XObjectCompare(XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
//    if (lhs == rhs) {
//        return true;
//    }
//
//    XObjectBase_o * lobj = (XObjectBase_o *)lhs;
//    XObjectBase_o * robj = (XObjectBase_o *)rhs;
//    XClass lcls = lobj->isa;
//    XClass rcls = robj->isa;
//    XClass cls = NULL;
//    if (XObjectIsKindOf(lobj, rcls)) {
//        XObjectCompare_f method = NULL;
//        _XObjectFindLifeCycleMethod(compare, cls, method);
//        return method(cls, cls->super, lhs, rhs);
//    } else if (XObjectIsKindOf(robj, lcls)) {
//        XObjectCompare_f method = NULL;
//        _XObjectFindLifeCycleMethod(compare, cls, method);
//        return method(cls, cls->super, lhs, rhs);
//    } else {
//        // 寻找共同的父类
//
//
//        return false;
//    }
//}
void ___XObjectDeinit(XObjectRef _Nonnull ref) {
    XClassRef cls = XObjectGetClass(ref);
    XObjectDeinit_f method = NULL;
    _XObjectFindLifeCycleMethod(deinit, cls, method);
    XAssert(method, "cls error");
    method(ref);
}
size_t XObjectGetHashCode(XObjectRef _Nullable ref) {
    if (ref) {
        XClassRef cls = XObjectGetClass(ref);
        XObjectGetHashCode_f method = NULL;
        _XObjectFindLifeCycleMethod(getHashCode, cls, method);
        return method(ref);
    } else {
        return 0;
    }
}
bool_t XObjectEqual(XObjectRef _Nullable lhs, XObjectRef _Nullable rhs) {
    if (NULL == lhs && NULL != rhs) {
        return false;
    } else if(NULL != lhs && NULL == rhs) {
        return false;
    } else {
        if (lhs == rhs) {
            return true;
        }
        XClassRef lcls = XObjectGetClass(lhs);
        XClassRef rcls = XObjectGetClass(rhs);

        XClassRef cls = NULL;
        if (XObjectIsKindOf(lhs, rcls)) {
            cls = rcls;
        } else if (XObjectIsKindOf(rhs, lcls)) {
            cls = lcls;
        } else {
            return false;
        }
        XObjectEqual_f method = NULL;
        _XObjectFindLifeCycleMethod(equal, cls, method);
        return method(cls, lhs, rhs);
    }
}

void XObjectDescribe(XObjectRef _Nullable ref, _XDescriptionBuffer _Nonnull buffer) {
    XAssert(buffer, "buffer is null");
    if (ref) {
        XClassRef cls = XObjectGetClass(ref);
        XObjectDescribe_f method = NULL;
        _XObjectFindLifeCycleMethod(describe, cls, method);
        method(ref, buffer);
    }
    

}
void XObjectDebugDescribe(XObjectRef _Nullable ref, _XDescriptionBuffer _Nonnull buffer) {
//    XAssert(buffer, "buffer is null");
//    if (ref) {
//        XClassRef cls = XObjectGetClass(ref);
//        XObjectDescribe_f method = NULL;
//        _XObjectFindLifeCycleMethod(debugDescribe, cls, method);
//        method(ref, buffer);
//    }
    

}


#pragma mark - XValue

XValueRef _Nonnull XValueCreate(XObjectOption flag, const XValueContentType_s * _Nonnull type, const void * _Nonnull content) {
    _XValue_o * result = XObjectAllocate(XValueClass, flag, sizeof(_XValue_o) + type->size, 0);
    result->type = type;
    memcpy(result->bytes, content, type->size);
    return result;
}
const XValueContentType_s * _Nonnull XValueGetType(XValueRef _Nonnull _ref) {
    _XValue_o * ref = _XHeapObjectAs(_ref, XValueClass, __func__);
    return ref->type;
}
void XValueGetContent(XValueRef _Nonnull _ref, void * _Nonnull receiver) {
    _XValue_o * ref = _XHeapObjectAs(_ref, XValueClass, __func__);
    memcpy(receiver, ref->bytes, ref->type->size);
}

size_t _XValueGetInstanceSize(XObjectRef _Nonnull self) {
    _XValue_o * ref = _XHeapObjectAs(self, XValueClass, __func__);
    return XAllocatorAlignedSize(sizeof(_XValue_o) + ref->type->size);
}

#pragma mark - XNumber

//XNumber.c

#pragma mark - XDateRef
//XDateRef.c

#pragma mark - XBoolRef

bool_t XBoolGetValue(XBoolRef _Nonnull ref) {
    return __XBoolDecode(ref, __func__);
}
XBoolRef _Nonnull XBoolWithValue(bool_t v) {
    return __XBoolEncode(v, __func__);
}
XBoolRef _Nonnull XBoolTrue(void) {
    return __XBoolEncode(true, __func__);
}
XBoolRef _Nonnull XBoolFalse(void) {
    return __XBoolEncode(false, __func__);
}

#pragma mark - XPointerType

void * _Nonnull _XPointerTypeXObjectRetain(void * _Nullable pointer) {
    XObjectRef object = (XObjectRef)pointer;
    return XObjectRetain(object);
}
void _XPointerTypeXObjectRelease(void * _Nullable pointer) {
    XObjectRef object = (XObjectRef)pointer;
    XObjectRelease(object);
}
const XPointerType_s __XPointerTypeXObject = XPointerTypeMake(XObject, _XPointerTypeXObjectRetain, _XPointerTypeXObjectRelease);
