
#include "XObjectInternal.h"
#include "XRuntimeInternal.h"
#include "XCoreBase.h"


/*
Tagged object
Date
32位：
header: 1
kind: 2
taggedContent:28
 tail: 1
 
64位：
header: 1
kind: 2
taggedContent:60
 tail: 1
*/


_XDate_o _XDateInvalid = {
    ._runtime = XObjectBaseMakeStaticStrongOnlyWithLayout(XDateClass, 0),
    .microsecond = MICROSECOND_INVALID,
};
_XDate_o _XDateDistantPast = {
    ._runtime = XObjectBaseMakeStaticStrongOnlyWithLayout(XDateClass, 0),
    .microsecond = MICROSECOND_DISTANT_PAST,
};
_XDate_o _XDateDistantFuture = {
    ._runtime = XObjectBaseMakeStaticStrongOnlyWithLayout(XDateClass, 0),
    .microsecond = MICROSECOND_DISTANT_FUTURE,
};

_XDate_o _XDateNormalMin = {
    ._runtime = XObjectBaseMakeStaticStrongOnlyWithLayout(XDateClass, 0),
    .microsecond = MICROSECOND_NORMAL_MIN,
};
_XDate_o _XDateNormalMax = {
    ._runtime = XObjectBaseMakeStaticStrongOnlyWithLayout(XDateClass, 0),
    .microsecond = MICROSECOND_NORMAL_MAX,
};

XDateRef _Nonnull XDateInvalid = (XDateRef)(&_XDateInvalid);
XDateRef _Nonnull XDateDistantPast = (XDateRef)(&_XDateDistantPast);
XDateRef _Nonnull XDateDistantFuture = (XDateRef)(&_XDateDistantFuture);
XDateRef _Nonnull XDateNormalMin = (XDateRef)(&_XDateNormalMin);
XDateRef _Nonnull XDateNormalMax = (XDateRef)(&_XDateNormalMax);

static XDateRef _Nonnull _XDateCreateHeap(size_t flag, microsecond_t time) {
    _XDate_o * date = (_XDate_o *)XObjectAllocate(XDateClass, flag, sizeof(_XDate_o), 0);
    date->microsecond = time;
    return date;
}

//2bit type, 有效位数 64(32) - 6 = 58(26), type = 0 标识微妙、 type = 1标识毫秒 type=2标识秒
XDateRef _Nonnull XDateCreate(size_t flag, microsecond_t time) {
    if (MICROSECOND_NORMAL_MIN == time) {
        return XDateNormalMin;
    } else if (MICROSECOND_NORMAL_MAX == time) {
        return XDateNormalMax;
    } else if (MICROSECOND_DISTANT_PAST == time) {
        return XDateDistantPast;
    } else if (MICROSECOND_DISTANT_FUTURE == time) {
        return XDateDistantFuture;
    }
    uint64_t tmp = SInt64ZigzagEncode(time);
    if (tmp < (UINT64_C(0x1) << X_TaggedObjectScopeAContentBitCount)) {
        return __XTaggedObjectEncodeScopeA(X_TaggedObjectTypeBits_XDate, (size_t)tmp, __func__);
    }
    return _XDateCreateHeap(flag, time);
}

static _XDate_o * _Nonnull __XRHeapDateAsDate(XDateRef _Nonnull ref, const char * _Nonnull func) {
    return (_XDate_o *)_XHeapObjectAs(ref, XDateClass, func);
}

void __XDateUnpack(XDateRef _Nonnull ref, microsecond_t * _Nonnull valuePtr, const char * _Nonnull func) {
    uintptr_t refv = (uintptr_t)ref;
    if (XObjectIsTaggedObject(ref)) {
        size_t content = __XTaggedObjectDecodeContentScopeA(refv, X_TaggedObjectTypeBits_XDate, __func__);
        uint64_t tmp = (uint64_t)content;
        microsecond_t number = SInt64ZigzagDecode(tmp);
        *valuePtr = number;
    } else {
        _XDate_o * date = __XRHeapDateAsDate(ref, func);
        *valuePtr = date->microsecond;
    }
}

microsecond_t XDateGetTimevalSince1970(XDateRef _Nonnull ref) {
    XAssert(NULL != ref, "ref is NULL");
    microsecond_t content = { 0 };
    __XDateUnpack(ref, &content, __func__);
    return content;
}

XComparisonResult XDateCompare(XDateRef _Nonnull lhs, XDateRef _Nonnull rhs) {
    microsecond_t contentOfLhs = { 0 };
    microsecond_t contentOfRhs = { 0 };
    __XDateUnpack(lhs, &contentOfLhs, __func__);
    __XDateUnpack(rhs, &contentOfRhs, __func__);
    if (contentOfLhs == contentOfRhs) {
        return XCompareEqualTo;
    } else if (contentOfLhs < contentOfRhs) {
        return XCompareLessThan;
    } else {
        return XCompareGreaterThan;
    }
}

void _XDateDeinit(XObjectRef _Nonnull self) {
    _XDate_o * date = (_XDate_o *)self;
    date->microsecond = 0;
}
size_t _XDateGetHashCode(XObjectRef _Nonnull self) {
    XAssert(NULL != self, "ref is NULL");
    microsecond_t content = { 0 };
    __XDateUnpack(self, &content, __func__);
    XByte16 h16;
    h16 = XNumberHashSInt64(content);
    return XHash((uint8_t *)&h16, 16);
}
bool_t _XDateEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    XAssert(NULL != lhs, "lhs is NULL");
    XAssert(NULL != rhs, "rhs is NULL");

    microsecond_t contentOfLhs = { 0 };
    microsecond_t contentOfRhs = { 0 };
    __XDateUnpack(lhs, &contentOfLhs, __func__);
    __XDateUnpack(rhs, &contentOfRhs, __func__);
    return contentOfLhs == contentOfRhs;
}
void _XDateDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XDateDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

