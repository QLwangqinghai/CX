
#ifndef XBasicHash_h
#define XBasicHash_h


#if defined(__cplusplus)
extern "C" {
#endif

#include "CXBaseInternal.h"
#include "XCollection.h"

struct __XHashElementType;
typedef struct __XHashElementType XHashElementType_s;

struct __XHashElementType {
    size_t size;
    
    // element.hashCode
    size_t (* _Nonnull getKeyHashCode)(void * _Nonnull element);
    
    // element.isKeyEqual(key)
    bool_t (* _Nonnull isKeyMatch)(void * _Nonnull element, void * _Nonnull keyBuffer);
    
};

typedef void (*_XHashElementElementCopy_f)(void * _Nonnull dst, const void * _Nonnull src);
typedef void (*_XHashElementElementDeinit_f)(void * _Nonnull element);

extern const XHashElementType_s __XSetElementType;

extern void _XSetElementCopy(void * _Nonnull _dst, const void * _Nonnull _src);
extern void _XSetElementDeinit(void * _Nonnull element);
extern bool_t XSetElementEqual(XSetElement_s * _Nonnull lhs, XSetElement_s * _Nonnull rhs);


extern const XHashElementType_s __XMapElementType;
extern void _XMapElementCopy(void * _Nonnull _dst, const void * _Nonnull _src);
extern void _XMapElementDeinit(void * _Nonnull element);
extern bool_t XMapElementEqual(XMapElement_s * _Nonnull lhs, XMapElement_s * _Nonnull rhs);


#if defined(__cplusplus)
}  // extern C
#endif


#endif /* XBasicHash_h */
