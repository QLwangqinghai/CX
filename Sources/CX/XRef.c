//
//  XRef.c
//  X
//
//  Created by vector on 2020/4/3.
//  Copyright © 2020 haoqi. All rights reserved.
//

#include "include/XRef.h"
#include "internal/XRuntimeInternal.h"
#include "internal/XAllocator.h"
#include "internal/XClass.h"

//XBool XStringEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
//XBool XDataEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
//XBool XDateEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
//XBool XValueEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
//XBool XObjectEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
//
//
//XHashCode XStringHash(XRef _Nonnull obj) {return 0;};
//XHashCode XDataHash(XRef _Nonnull obj) {return 0;};
//XHashCode XDateHash(XRef _Nonnull obj) {return 0;};
//XHashCode XObjectHash(XRef _Nonnull obj) {return 0;};

void _XDisableDeinit(XRef _Nonnull obj, const char * _Nonnull func) {
    XAssert(false, func, "");
};



#pragma mark - XClass

XBool XClassEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    assert(lhs);
    assert(rhs);
    return false;

//    XClassIdentifier lclsId = XRefGetIdentfierIfIsClass(lhs);
//    XClassIdentifier rclsId = XRefGetIdentfierIfIsClass(rhs);
//    if (lclsId && rclsId) {
//        return lclsId == rclsId;
//    } else {
//        return false;
//    }
};

XHashCode XClassHash(XRef _Nonnull cls) {
//    XClassIdentifier clsId = XRefGetIdentfierIfIsClass(cls);
//    assert(clsId);
//
//    return (XHashCode)(((uintptr_t)clsId) >> 4);
    return 0;
}

#pragma mark - XNull

const _XNull _XNullShared = {
    ._runtime = _XConstantObjectBaseMake(XClassOf(Null)),
};
const XNull _Nonnull XNullShared() {
    return (XNull)&_XNullShared;
}

XBool XNullEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    //XNull 不允许自己构建， 只可以使用 XNullShared;
    assert(lhs == XNullShared);
    assert(rhs == XNullShared);
    return true;
};

XHashCode XNullHash(XRef _Nonnull ref) {
    assert(ref == XNullShared);
    return 0;
}
extern XNull _Nonnull XNullCreate(void) {
    return XNullShared;
}

#pragma mark - XBoolean

const _XBoolean _XBooleanTrue = {
    ._runtime = _XConstantObjectBaseMake(XClassOf(Boolean)),
    .content = {.value = true},
};
const _XBoolean _XBooleanFalse = {
    ._runtime = _XConstantObjectBaseMake(XClassOf(Boolean)),
    .content = {.value = false},
};

const XBoolean _Nonnull XBooleanTrue() {
    return (XBoolean)&_XBooleanTrue;
};
const XBoolean _Nonnull XBooleanFalse() {
    return (XBoolean)&_XBooleanFalse;
}

XBool XBooleanEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    //XBoolean 不允许自己构建， 只可以使用 XBooleanTrue、XBooleanFalse;
    XAssert((lhs == XBooleanTrue || lhs == XBooleanFalse), __func__, "lhs error");
    XAssert((rhs == XBooleanTrue || rhs == XBooleanFalse), __func__, "rhs error");
    return lhs == rhs;
};

XHashCode XBooleanHash(XRef _Nonnull ref) {
    XAssert((ref == XBooleanTrue || ref == XBooleanFalse), __func__, "ref error");
    return ((const _XBoolean *)ref)->content.value ? 1 : 0;
}

XBoolean _Nonnull XBooleanCreate(XBool value) {
    return value ? XBooleanTrue : XBooleanFalse;
}

XBool XBooleanGetValue(XBoolean _Nonnull ref) {
    if (ref == XBooleanTrue) {
        return true;
    } else if (ref == XBooleanFalse) {
        return false;
    } else {
        XAssert(false, __func__, "ref error");
    }
}

#pragma mark - XNumber

//XNumber.c


#pragma mark - private _XByteStorage

extern _XBuffer * _Nonnull _XBufferAllocate(XPtr _Nonnull buffer, XUInt size, XBool clearWhenDealloc);
extern _XBuffer * _Nonnull _XBufferRetain(_XBuffer * _Nonnull buffer);
extern void _XBufferRelease(_XBuffer * _Nonnull buffer);
extern void _XBufferSetClearWhenDealloc(_XBuffer * _Nonnull buffer);

//XByteStorage.c


/*
(8 + 4 + 4 + opt16 = 16 or 32)
16 48 (128-16) (256-16)
*/
//typedef struct {
//    _XExtendedLayout layout: 4;
//    XUInt32 hasHashCode: 1;
//    XUInt32 clearWhenDealloc: 1;
//    XUInt32 __unuse: 10;
//    XUInt32 inlineLength: 16;//layout == _XStringLayoutInline 时有效
//    XUInt32 hashCode;
//    XUInt8 extended[0];/* 可能有0、16、48、112、 240 5种可能 */
//} _XByteContent_t;
//
//typedef struct {
//    XUInt offset: 32;
//    XUInt length: 32;
//    _XBuffer * _Nonnull buffer;
//} _XByteBufferContent_t;
//
//typedef struct {
//    _XObjectCompressedBase _runtime;
//    _XByteBufferContent_t content;
//} _XByteStorage;


#pragma mark - XString

#pragma mark - XData



#pragma mark - XDate

//XDate.c


#pragma mark - XValue

#define XValueHashLimit 128
#define XValueHashNoneFlag 0x80000000UL
#define XValueHashMask 0x7FFFFFFFUL

const XSize XValueSizeMax = X_BUILD_ValueSizeMax;

const _XValue _XValueEmpty = {
    ._runtime = _XConstantObjectCompressedBaseMake(X_BUILD_CompressedType_Value),
    .content = {
        .clearWhenDealloc = 0,
        .contentSize = 0,
        .hashCode = ATOMIC_VAR_INIT(0),
    },
};
const XValue _Nonnull XValueEmpty = (XValue)&_XValueEmpty;

static inline XSize __XValueSizeAligned(XSize size) {
    #if BUILD_TARGET_RT_64_BIT
        XSize s = (size + 7) & (~X_BUILD_UInt(0x7));
    #else
        XSize s = (size + 3) & (~X_BUILD_UInt(0x3));
    #endif
    return s;
};
//通过copy content
XValue _Nonnull XValueCreate(XUInt flag, XPtr _Nullable content, XSize contentSize) {
    if (contentSize > 0) {
        XAssert(NULL != content, __func__, "contentSize>0, but content is NULL");
        XAssert(contentSize <= X_BUILD_ValueSizeMax, __func__, "contentSize too large");
    } else {
        XAssert(contentSize == 0, __func__, "contentSize < 0");
        return XValueEmpty;
    }
    const _XAllocator_s * allocator = &_XValueAllocator;
//    typedef XRef _Nonnull (*XRefAllocate_f)(_XAllocatorPtr _Nonnull allocator, XClass _Nonnull cls, XSize contentSize, XObjectRcFlag flag);

    XObjectRcFlag rcFlag = 0;
    
    XRef ref = allocator->allocateRef((_XAllocatorPtr)allocator, XClassValue, __XValueSizeAligned(contentSize), rcFlag);
    _XValue * valueRef = (_XValue *)(ref);

    valueRef->content.clearWhenDealloc = ((flag & XObjectFlagClearWhenDealloc) == XObjectFlagClearWhenDealloc) ? 1 : 0;
    valueRef->content.contentSize = (XUInt32)contentSize;
    atomic_store(&(valueRef->content.hashCode), XValueHashNoneFlag);
    return ref;
}
static _XValue * _Nonnull __XRefAsValue(XValue _Nonnull ref, const char * _Nonnull func) {
    XCompressedType compressedType = XCompressedTypeNone;
    
#if BUILD_TARGET_RT_64_BIT
    __unused
#endif
    XClass info = _XHeapRefGetClass(ref, &compressedType, func);
    
#if BUILD_TARGET_RT_64_BIT
    XAssert(XCompressedTypeValue == compressedType, func, "not Value instance");
    return (_XValue *)ref;
#else
    const XType_s * type = (const XType_s *)info;
    XAssert(type->base.identifier == _XClassTable[X_BUILD_CompressedType_Value - 1].base.identifier, func, "not Value instance");
    return (_XValue *)ref;
#endif
}
XSize XValueGetSize(XValue _Nonnull ref) {
    XAssert(NULL != ref, __func__, "require ref != NULL");
    _XValue * valueRef = __XRefAsValue(ref, __func__);
    return valueRef->content.contentSize;
}
void XValueCopyContent(XValue _Nonnull ref, XPtr _Nonnull buffer, XSize offset, XSize length) {
    XAssert(NULL != ref, __func__, "require ref != NULL");
    XAssert(NULL != buffer, __func__, "require buffer != NULL");

    _XValue * valueRef = __XRefAsValue(ref, __func__);
    if (length == 0) {
        return;
    }
    XAssert(length >= 0, __func__, "require length>=0");
    XAssert(offset >= 0, __func__, "require offset>=0");
    XAssert(length <= valueRef->content.contentSize, __func__, "range error");
    XAssert(offset <= valueRef->content.contentSize - length, __func__, "range error");
    
    memcpy(buffer, &(valueRef->content.extended[offset]), length);
}
XHashCode XValueHash(XValue _Nonnull ref) {
    XAssert(NULL != ref, __func__, "require ref != NULL");

    _XValue * valueRef = __XRefAsValue(ref, __func__);
    XFastUInt32 code = atomic_load(&(valueRef->content.hashCode));
    if (code >= XValueHashNoneFlag) {
        code = _XELFHashBytes(&(valueRef->content.extended[0]), MIN(valueRef->content.contentSize, XValueHashLimit)) & XValueHashMask;
        atomic_store(&(valueRef->content.hashCode), code);
    }
    
#if BUILD_TARGET_RT_64_BIT
    XHashCode hashCode = valueRef->content.contentSize;
    hashCode = (hashCode << 31ULL) + code;    
    return hashCode;
#else
    return code;
#endif
}

#pragma mark - XPackageRef

const XSize XPackageSizeMax = X_BUILD_PackageSizeMax;


static inline XSize __XPackageContentSizeAligned(XSize size) {
#if BUILD_TARGET_RT_64_BIT
    XSize s = (size + 7) & (~X_BUILD_UInt(0x7));
#else
    XSize s = (size + 3) & (~X_BUILD_UInt(0x3));
#endif
    return s;
};


XPackageRef _Nonnull XPackageCreate(XUInt flag, XU8Char * _Nonnull typeName, XSize size, XPackageDeinit_f _Nullable deinit) {
    XAssert(size <= X_BUILD_PackageSizeMax, __func__, "");
    XAssert(size > 0, __func__, "size == 0");

    XAssert(NULL != typeName, __func__, "typeName NULL");
    const _XAllocator_s * allocator = &_XCollectionAllocator;
    XObjectRcFlag rcFlag = XObjectRcFlagFromObjectFlag(flag);
    XSize contentSize = __XPackageContentSizeAligned(size);
    XSize s = contentSize + sizeof(_XPackageContent_t);
    XRef ref = allocator->allocateRef((_XAllocatorPtr)allocator, XClassPackage, s, rcFlag);
    _XPackageContent_t * content = &(((_XPackage *)ref)->content);
    content->typeName = typeName;
    content->deinit = deinit;
    content->clearWhenDealloc = ((flag & XObjectFlagClearWhenDealloc) == XObjectFlagClearWhenDealloc) ? 1 : 0;
    content->contentSize = size;
    content->paddingSize = contentSize - size;
    bzero(&(content->extended[0]), contentSize);
    return ref;
}

static _XPackage * _Nonnull __XRefAsPackage(XPackageRef _Nonnull ref, const char * _Nonnull func) {
    XCompressedType compressedType = XCompressedTypeNone;
    
#if BUILD_TARGET_RT_64_BIT
    __unused
#endif
    XClass info = _XHeapRefGetClass(ref, &compressedType, func);
    
#if BUILD_TARGET_RT_64_BIT
    XAssert(XCompressedTypePackage == compressedType, func, "not Object instance");
    return (_XPackage *)ref;
#else
    const XType_s * type = (const XType_s *)info;
    XAssert(type->base.identifier == _XClassTable[X_BUILD_CompressedType_Package - 1].base.identifier, func, "not Object instance");
    return (_XPackage *)ref;
#endif
}

XSize XPackageGetSize(XPackageRef _Nonnull ref) {
    XAssert(NULL != ref, __func__, "require ref != NULL");
    _XPackage * storageRef = __XRefAsPackage(ref, __func__);
    return storageRef->content.contentSize;
}

XPtr _Nonnull XPackageGetContent(XPackageRef _Nonnull ref) {
    XAssert(NULL != ref, __func__, "require ref != NULL");
    _XPackage * storageRef = __XRefAsPackage(ref, __func__);
    return &(storageRef->content.extended[0]);
}
void XPackageUnpack(XPackageRef _Nonnull ref, XPackageContent_t * _Nonnull contentPtr) {
    XAssert(NULL != ref, __func__, "require ref != NULL");
    XAssert(NULL != contentPtr, __func__, "require contentPtr != NULL");

    _XPackage * storageRef = __XRefAsPackage(ref, __func__);
    _XPackageContent_t * content = &(storageRef->content);
    XPackageContent_t result = {
        .typeName = content->typeName,
        .contentSize = content->contentSize,
        .content = &(content->extended[0]),
    };
    memcpy(contentPtr, &result, sizeof(XPackageContent_t));
}


#pragma mark - XArrayRef
#pragma mark - XMapRef
#pragma mark - XSetRef




//typedef struct {
//    XObjectBase_s _runtime;
//} _XNull;
//
//typedef struct {
//    XObjectBase_s _runtime;
//    XBool value;
//} _XBoolean;
//
//typedef struct {
//    _XObjectCompressedBase _runtime;
//    XSize size;
//    XUInt8 content[0];
//} _XNumber;
//
//typedef struct {
//    _XObjectCompressedBase _runtime;
//    XSize size;
//    XUInt8 content[0];
//} _XValue;


#pragma mark - XRef

XRef _Nonnull XRefRetain(XRef _Nonnull ref) {
    XAssert(NULL != ref, __func__, "ref is Null");
    XTaggedType type = XRefGetTaggedType(ref);
    if (type < XTaggedTypeMax) {
        return ref;
    }
    return _XRefRetain(ref, __func__);
}
void XRefRelease(XRef _Nonnull ref) {
    XAssert(NULL != ref, __func__, "ref is Null");
    XTaggedType type = XRefGetTaggedType(ref);
    if (type < XTaggedTypeMax) {
        return;
    }
    _XRefRelease(ref, __func__);
}


