
#ifndef XObjectInternal_h
#define XObjectInternal_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XObject.h"
#include "XHash.h"
#include "XAtomicInternal.h"


static inline size_t __XObjectGetHashCodeWithAddress(void * _Nullable p) {
    uintptr_t v = (uintptr_t)p;
    return __XHashSInt(v / sizeof(void *));
}

// size <= SINT_MAX
extern XObjectRef _Nonnull __XClassDataAllocateInstance(XObjectOption option, size_t layout, size_t minSize);
///// 返回的size >= minSize
//extern size_t __XClassDataGetObjectSize(XObjectRef _Nonnull object);
//
//extern size_t __XHeapDataGetLayout(XObjectRef _Nonnull object);
//
//// size <= SINT_MAX
extern XObjectRef _Nonnull __XClassStringAllocateInstance(XObjectOption option, size_t layout, size_t minSize);
///// 返回的size >= minSize
//extern size_t __XClassStringGetObjectSize(XObjectRef _Nonnull object);
extern size_t __XHeapStringGetLayout(XObjectRef _Nonnull object);

#pragma mark - runtime

#pragma mark - XValue

#pragma mark - XDataRef
extern void _XDataDeinit(XObjectRef _Nonnull self);
extern size_t _XDataGetHashCode(XObjectRef _Nonnull self);
extern bool_t _XDataEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
extern void _XDataDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
extern void _XDataDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);

#pragma mark - _XString

extern void _XStringDeinit(XObjectRef _Nonnull self);
extern size_t _XStringGetHashCode(XObjectRef _Nonnull self);
extern bool_t _XStringEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
extern void _XStringDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
extern void _XStringDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);

#pragma mark - _XNumber
extern void _XNumberDeinit(XObjectRef _Nonnull self);
extern size_t _XNumberGetHashCode(XObjectRef _Nonnull self);
extern bool_t _XNumberEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
extern void _XNumberDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
extern void _XNumberDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);

#pragma mark - _XDate
extern void _XDateDeinit(XObjectRef _Nonnull self);
extern size_t _XDateGetHashCode(XObjectRef _Nonnull self);
extern bool_t _XDateEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs);
extern void _XDateDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);
extern void _XDateDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer);

#pragma mark - XWeakStorage

extern void _XWeakStorageDeinit(XObjectRef _Nonnull self);


#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XObjectInternal_h */
