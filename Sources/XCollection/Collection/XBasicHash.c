#include "XBasicHash.h"

size_t _XSetElementGetKeyHashCode(void * _Nonnull element) {
    XSetElement_s * e = (XSetElement_s *)element;
    return XObjectGetHashCode(e->key);
}
bool_t _XSetElementIsKeyMatch(void * _Nonnull element, void * _Nonnull keyBuffer) {
    XSetElement_s * e = (XSetElement_s *)element;
    XObjectRef key = *(XObjectRef *)keyBuffer;
    return XObjectEqual(e->key, key);
}
void _XSetElementCopy(void * _Nonnull _dst, const void * _Nonnull _src) {
    XSetElement_s * dst = (XSetElement_s *)_dst;
    XSetElement_s * src = (XSetElement_s *)_src;
    dst->key = XObjectCopy(src->key);
}
void _XSetElementDeinit(void * _Nonnull element) {
    XSetElement_s * e = (XSetElement_s *)element;
    XObjectRelease(e->key);
    e->key = NULL;
}

const XHashElementType_s __XSetElementType = {
    .size = sizeof(XSetElement_s),
    .getKeyHashCode = _XSetElementGetKeyHashCode,
    .isKeyMatch = _XSetElementIsKeyMatch,
};



size_t _XMapElementGetKeyHashCode(void * _Nonnull element) {
    XMapElement_s * e = (XMapElement_s *)element;
    return XObjectGetHashCode(e->key);
}
bool_t _XMapElementIsKeyMatch(void * _Nonnull element, void * _Nonnull keyBuffer) {
    XMapElement_s * e = (XMapElement_s *)element;
    XObjectRef key = *(XObjectRef *)keyBuffer;
    return XObjectEqual(e->key, key);
}
void _XMapElementCopy(void * _Nonnull _dst, const void * _Nonnull _src) {
    XMapElement_s * dst = (XMapElement_s *)_dst;
    XMapElement_s * src = (XMapElement_s *)_src;
    dst->key = XObjectCopy(src->key);
    dst->value = XObjectCopy(src->value);
}
void _XMapElementDeinit(void * _Nonnull element) {
    XMapElement_s * e = (XMapElement_s *)element;
    XObjectRelease(e->key);
    XObjectRelease(e->value);
    e->key = NULL;
    e->value = NULL;
}
const XHashElementType_s __XMapElementType = {
    .size = sizeof(XMapElement_s),
    .getKeyHashCode = _XMapElementGetKeyHashCode,
    .isKeyMatch = _XMapElementIsKeyMatch,
};


bool_t XSetElementEqual(XSetElement_s * _Nonnull lhs, XSetElement_s * _Nonnull rhs) {
    return XObjectEqual(lhs->key, rhs->key);
}

bool_t XMapElementEqual(XMapElement_s * _Nonnull lhs, XMapElement_s * _Nonnull rhs) {
    return XObjectEqual(lhs->key, rhs->key) && XObjectEqual(lhs->value, rhs->value);
}
