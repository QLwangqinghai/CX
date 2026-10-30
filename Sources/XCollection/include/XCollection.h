
#ifndef XCollection_h
#define XCollection_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "CXBase.h"

#pragma mark - XHashTable

typedef struct {
    XObjectRef _Nullable key;
    XObjectRef _Nullable value;
} XMapElement_s;

typedef struct {
    XObjectRef _Nullable key;
} XSetElement_s;

typedef void (*XMapEnumerate_f)(ssize_t index, XObjectRef _Nullable key, XObjectRef _Nullable value, void * _Nullable context, bool_t * _Nonnull stop);
typedef void (*XSetEnumerate_f)(ssize_t index, XObjectRef _Nullable key, void * _Nullable context, bool_t * _Nonnull stop);

#pragma mark - XMap
// 添加到XMap的Key&Value都会执行copy操作

extern ssize_t XMapGetCount(XMapRef _Nonnull map);

/// return unretained object
extern XObjectRef _Nullable XMapGetAssignValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain);

/// return retained object
extern XObjectRef _Nullable XMapGetValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t * _Nullable isContain);

extern void XMapEnumerate(XMapRef _Nonnull map, XMapEnumerate_f _Nonnull func, void * _Nullable context);

// -----------------Immutable---------------

/// create immutable map,
extern XMapRef _Nonnull XMapCreateWithValueKeys(XObjectOption option, ssize_t count, ...);

extern XMapRef _Nonnull XMapCreateWithValuesAndKeys(XObjectOption option, XArrayRef _Nonnull values, XArrayRef _Nonnull keys);


// ------------------- Mutable ----------------------------

extern XMapRef _Nonnull XMutableMapCreateWithValueKeys(XObjectOption option, ssize_t count, ...);
extern XMapRef _Nonnull XMutableMapCreate(XObjectOption option, ssize_t capacity);

extern XMapRef _Nonnull XMutableMapCreateWithValuesAndKeys(XObjectOption option, XArrayRef _Nonnull values, XArrayRef _Nonnull keys);

extern XMapRef _Nonnull XMutableMapCreateWithMap(XObjectOption option, XMapRef _Nonnull map);


/// 返回retainedobject, 如果有旧object， 返回true
extern bool_t XMutableMapSetValue(XMapRef _Nonnull map, XObjectRef _Nullable object, XObjectRef _Nullable key, XMapElement_s * _Nullable old);

/// 返回retainedobject, 如果有旧object， 返回true
extern bool_t XMutableMapRemoveValue(XMapRef _Nonnull map, XObjectRef _Nullable key, bool_t allowReduceCapacity, XMapElement_s * _Nullable old);

extern void XMutableMapRemoveAll(XMapRef _Nonnull map, bool_t allowReduceCapacity, XMapRef _Nonnull * _Nullable old);
extern void XMutableMapResize(XMapRef _Nonnull map, ssize_t minCapacity);


#pragma mark - XSet
// 添加到XSet的Key都会执行copy操作

extern ssize_t XSetGetCount(XSetRef _Nonnull set);

/// return unretained object
extern bool_t XSetContains(XSetRef _Nonnull set, XObjectRef _Nullable key);

extern void XSetEnumerate(XSetRef _Nonnull set, XSetEnumerate_f _Nonnull func, void * _Nullable context);

// -----------------Immutable---------------

/// create immutable map,
extern XSetRef _Nonnull XSetCreateWithKeys(XObjectOption option, ssize_t count, ...);
extern XSetRef _Nonnull XSetCreateWithArray(XObjectOption option, XArrayRef _Nonnull keys);

// ------------------- Mutable ----------------------------

/// create mutable array

extern XSetRef _Nonnull XMutableSetCreateWithValueKeys(XObjectOption option, ssize_t count, ...);

extern XSetRef _Nonnull XMutableSetCreate(XObjectOption option, ssize_t capacity);
extern XSetRef _Nonnull XMutableSetCreateWithKeys(XObjectOption option, XArrayRef _Nonnull keys);

extern XSetRef _Nonnull XMutableSetCreateWithSet(XObjectOption option, XSetRef _Nonnull set);

/// 返回retainedobject, 如果有旧object， 返回true
extern bool_t XMutableSetInsert(XSetRef _Nonnull set, XObjectRef _Nullable key, XSetElement_s * _Nullable old);

/// 返回retainedobject, 如果有旧object， 返回true
extern bool_t XMutableSetRemove(XSetRef _Nonnull set, XObjectRef _Nullable key, bool_t allowReduceCapacity, XSetElement_s * _Nullable old);
extern void XMutableSetRemoveAll(XSetRef _Nonnull set, bool_t allowReduceCapacity, XSetRef _Nonnull * _Nullable old);
extern void XMutableSetResize(XSetRef _Nonnull set, ssize_t minCapacity);

#pragma mark - XOrderedSet
extern void XOrderedSetEnumerate(XSetRef _Nonnull set, bool_t reverse, XSetEnumerate_f _Nonnull func, void * _Nullable context);

#pragma mark - XOrderedMap
extern void XOrderedMapEnumerate(XOrderedMapRef _Nonnull map, bool_t reverse, XMapEnumerate_f _Nonnull func, void * _Nullable context);



#if defined(__cplusplus)

}  // extern C
#endif

#endif /* XCollection_h */
