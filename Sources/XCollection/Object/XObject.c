
#include "CXBaseInternal.h"

#define XRuntimeErrorCall XAssert(false, "XRuntimeErrorCall")

#pragma mark - _XParameterBuffer

void _XParameterBufferDeinit(XObjectRef _Nonnull self) {
    _XParameterBuffer_o * obj = (_XParameterBuffer_o *)self;
    XParameterBufferRelease(obj->type, obj->buffer);
}
size_t _XParameterBufferGetHashCode(XObjectRef _Nonnull self) { return _XObjectDefaultGetHashCode(self); }
bool_t _XParameterBufferEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) { return lhs == rhs; }
void _XParameterBufferDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XParameterBufferDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

#pragma mark - XClosure

static inline _XClosure_o * _Nonnull _XRefAsClosure(XClosureRef _Nonnull item, const char * _Nonnull func) {
    XAssert(item, "");
    XAssert(XClosureClass == XObjectGetClass(item), "");
    return (_XClosure_o *)item;
}

void _XClosureDeinit(XObjectRef _Nonnull self) {
    _XClosure_o * item = _XRefAsClosure(self, __func__);
    XPointerRelease(item->method->handlerType, &(item->handler));
    item->handler = NULL;
}
size_t _XClosureGetHashCode(XObjectRef _Nonnull self) {
    return _XObjectDefaultGetHashCode(self);
}

bool_t _XClosureEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    return lhs == rhs;
}

void _XClosureDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {
//    _XClosure_o * obj = (_XClosure_o *)self;
    
}
void _XClosureDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {
//    _XClosure_o * obj = (_XClosure_o *)self;
    
}

#pragma mark - XMap

void _XMapDeinit(XObjectRef _Nonnull self);
size_t _XMapGetHashCode(XObjectRef _Nonnull self);
bool_t _XMapEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
void _XMapDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
void _XMapDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
XObjectRef _Nonnull _XMapCopy(XObjectRef _Nonnull self);

#pragma mark - XSet

void _XSetDeinit(XObjectRef _Nonnull self);
size_t _XSetGetHashCode(XObjectRef _Nonnull self);
bool_t _XSetEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
void _XSetDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
void _XSetDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
extern XObjectRef _Nonnull _XSetCopy(XObjectRef _Nonnull self);

#pragma mark - XOrderedMap

void _XOrderedMapDeinit(XObjectRef _Nonnull self);
size_t _XOrderedMapGetHashCode(XObjectRef _Nonnull self);
bool_t _XOrderedMapEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
void _XOrderedMapDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
void _XOrderedMapDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
XObjectRef _Nonnull _XOrderedMapCopy(XObjectRef _Nonnull self);

#pragma mark - XOrderedSet

void _XOrderedSetDeinit(XObjectRef _Nonnull self);
size_t _XOrderedSetGetHashCode(XObjectRef _Nonnull self);
bool_t _XOrderedSetEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
void _XOrderedSetDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
void _XOrderedSetDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
extern XObjectRef _Nonnull _XOrderedSetCopy(XObjectRef _Nonnull self);

extern size_t _XParameterBufferGetInstanceSize(XObjectRef _Nonnull self);


//#define _XClosureCopy _XObjectDefaultCopy
//#define _XParameterBufferCopy _XObjectDefaultCopy

#pragma mark - XParameterBuffer

void _XParameterBufferTypeXObjectRetain(const XParameterBufferType_s * _Nonnull type, void * _Nonnull buffer) {
    XAssert(type, "type null");
    XAssert(buffer, "buffer null");
    XObjectRef object = *((XObjectRef *)buffer);
    XObjectRetain(object);
}
void _XParameterBufferTypeXObjectRelease(const XParameterBufferType_s * _Nonnull type, void * _Nonnull buffer) {
    XAssert(type, "type null");
    XAssert(buffer, "buffer null");
    XObjectRef object = *((XObjectRef *)buffer);
    XObjectRelease(object);
}
const XParameterBufferType_s __XParameterBufferTypeXObject = XParameterBufferTypeMake(sizeof(XObjectRef), XObject, _XParameterBufferTypeXObjectRetain, _XParameterBufferTypeXObjectRelease);

/// value 会被copy 到XValue 中，copy 执行后会调用retaindata,
XParameterBufferRef _Nonnull XParameterBufferCreate(XObjectOption flag, const XParameterBufferType_s * _Nonnull type, const void * _Nonnull content) {
    XAssert(type, "type error");
    XAssert(type->size > 0, "require type->size > 0");
    _XParameterBuffer_o * item = (_XParameterBuffer_o *)XObjectAllocate(XParameterBufferClass, flag, sizeof(_XParameterBuffer_o) + type->size, 0);
    item->type = type;
    memcpy(item->buffer, content, type->size);
    XParameterBufferRetain(type, item->buffer);
    return item;
}
const XParameterBufferType_s * _Nonnull XParameterBufferGetType(XParameterBufferRef _Nonnull ref) {
    XAssert(XParameterBufferClass == XObjectGetClass(ref), "");
    _XParameterBuffer_o * item = (_XParameterBuffer_o *)ref;
    return item->type;
}
void * _Nonnull XParameterBufferGetContent(XParameterBufferRef _Nonnull ref) {
    XAssert(XParameterBufferClass == XObjectGetClass(ref), "");
    _XParameterBuffer_o * item = (_XParameterBuffer_o *)ref;
    return item->buffer;
}

size_t _XParameterBufferGetInstanceSize(XObjectRef _Nonnull self) {
    XAssert(XObjectGetClass(self) == XParameterBufferClass, "");
    _XParameterBuffer_o * ref = (_XParameterBuffer_o *)self;
    return XAllocatorAlignedSize(sizeof(_XParameterBuffer_o) + ref->type->size);
}

#pragma mark - XClosure

XClosureRef _Nonnull XClosureCreate(XObjectOption option, const XMethod_s * _Nonnull method, XObjectRef _Nullable handler) {
    XAssert(method, "method null");
    XAssert(method->handlerType == &__XPointerTypeXObject, "method handlerType error");
    XAssert(method->targetType == &__XPointerTypeXObject, "method targetType error");
    
    _XClosure_o * item = XObjectAllocate(XClosureClass, option, sizeof(_XClosure_o), 0);
    item->method = method;
    XPointerRetain(method->handlerType, handler);
    item->handler = handler;
    return item;
}
const XMethod_s * _Nonnull XClosureGetMethod(XClosureRef _Nonnull object) {
    XAssert(XClosureClass == XObjectGetClass(object), "");
    return ((_XClosure_o *)object)->method;
}
void XClosurePerform(XClosureRef _Nonnull ref, XObjectRef _Nullable target, XClosureInputBuffer_t _Nullable inputBuffer, XClosureOutputBuffer_t _Nullable outputBuffer) {
    _XClosure_o * item = _XRefAsClosure(ref, __func__);
    item->method->dispatchFunc(item->method, item->handler, target, inputBuffer, outputBuffer);
}

void _XClosureDispatchFunction(const XMethod_s * _Nonnull sel, void * _Nullable context, void * _Nullable target, void * _Nullable inputBuffer, void * _Nullable outputBuffer) {
    XClosureExecute_f func = (XClosureExecute_f)(sel->method);
    func(context, target, inputBuffer, outputBuffer);
}

#pragma mark - classes

const XClass_o _XClosureClass = XClassMakeNameDeinit(XClosure, 0, _XClosureDeinit);
XClassRef _Nonnull XClosureClass = &_XClosureClass;

const XClass_o _XParameterBufferClass = XClassMakeNameDeinit(XParameterBuffer, 0, _XParameterBufferDeinit);
XClassRef _Nonnull XParameterBufferClass = &_XParameterBufferClass;
