//
//  XRuntime.c
//  
//
//  Created by vector on 2020/4/4.
//

#include "include/XRuntime.h"
#include "internal/XRuntimeInternal.h"
#include <stdatomic.h>

#include "XRef.h"
#include "XObject.h"
#include "XClass.h"

#pragma mark - layout

_Static_assert(sizeof(_XByteStorageContentLarge_t) == sizeof(XUInt32) * 2 + sizeof(_Atomic(XFastUInt)) + sizeof(_XBuffer *), "unknown error");
_Static_assert(sizeof(XUInt) == sizeof(size_t), "unknown error");
_Static_assert(sizeof(_Atomic(uintptr_t)) == sizeof(XUInt), "unknown error");
_Static_assert(sizeof(_Atomic(XFastUInt32)) == sizeof(XUInt32), "unknown error");
_Static_assert(sizeof(_Atomic(XFastUInt64)) == sizeof(XUInt64), "unknown error");

_Static_assert(BUILD_TARGET_RT_64_BIT || BUILD_TARGET_RT_32_BIT, "unknown rt");

_Static_assert(X_BUILD_ObjectRcFlagReadOnly == 1, "X_BUILD_ObjectRcFlagReadOnly must be 1");

const XObjectRcFlag XObjectRcFlagReadOnly = 1;
const XObjectRcFlag XObjectRcFlagStatic = 1 << 1;

//对象释放时clear内存
const XObjectFlag XObjectFlagClearWhenDealloc = 1;

const XObjectFlag XObjectFlagStatic = 1 << 1;


const XTypeKind XTypeKindValue = X_BUILD_TypeKindValue;
const XTypeKind XTypeKindObject = X_BUILD_TypeKindObject;
const XTypeKind XTypeKindWeakableObject = X_BUILD_TypeKindWeakableObject;
const XTypeKind XTypeKindMetaClass = X_BUILD_TypeKindMetaClass;

//const XRefKind XRefKindUnknown = 0;
const XRefKind XRefKindInstance = 1;
const XRefKind XRefKindClass = 2;
const XRefKind XRefKindMetaClass = 3;


const XTaggedType XTaggedTypeNumber = 0;
const XTaggedType XTaggedTypeString = 1;
const XTaggedType XTaggedTypeData = 2;
const XTaggedType XTaggedTypeDate = 3;
const XTaggedType XTaggedTypeMax = XTaggedTypeDate;


XBool XStringEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
XBool XDataEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
XBool XValueEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};



//64bit 压缩的头
 /* flagBegin:3 type:6 (rcInfo54(flag:4 count:18+32)) flagEnd:1  */

//32bit rc info
/* flag:4 count:18+32 */

XRefKind XRefGetKind(XRef _Nonnull ref) {
    XAssert(NULL != ref, __func__, "ref is NULL");

    XCompressedType compressedType = _XRefGetTaggedObjectTaggedType(ref);
    if (XCompressedTypeNone != compressedType) {
        return XRefKindInstance;
    }
    const _XType_s * type = _XHeapRefGetClass(ref, &compressedType, __func__);
    assert(type);
    if (XTypeKindMetaClass == type->base.kind) {
        //ref 是一个类对象
        const _XType_s * cls = (const _XType_s *)ref;
        if (XTypeKindMetaClass == cls->base.kind) {
            return XRefKindMetaClass;
        } else {//ref 是个普通的类
            return XRefKindClass;
        }
    } else if (XTypeKindValue == type->base.kind || XTypeKindObject == type->base.kind || XTypeKindWeakableObject == type->base.kind) {
        return XRefKindInstance;
    } else {
        XAssert(false, __func__, "unknown error");
    }
}

XClassIdentifier _Nullable XRefGetIdentfierIfIsClass(XRef _Nonnull ref) {
    assert(ref);
    const _XType_s * type = (const _XType_s *)XRefGetClass(ref);
    if (XTypeKindMetaClass == type->base.kind) {
        const _XType_s * cls = (const _XType_s *)ref;
        return (XClassIdentifier)(cls->base.identifier);
    } else {
        return NULL;
    }
}

XBool XRefIsMetaClass(XRef _Nonnull ref) {
    assert(ref);
    const _XType_s * type = (const _XType_s *)XRefGetClass(ref);
    if (XTypeKindMetaClass == type->base.kind) {
        //is a class
        const _XType_s * cls = (const _XType_s *)ref;
        if (XTypeKindMetaClass == cls->base.kind) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


XUInt _XRefGetRcInfo(XRef _Nonnull ref) {
    _XObjectCompressedBase * obj = (_XObjectCompressedBase *)ref;
    _Atomic(XFastUInt) * tmp = &(obj->rcInfo);
    XFastUInt info = atomic_load(tmp);
    return info;
}

const _XType_s * _Nullable _XRefGetTaggedObjectClass(XRef _Nonnull ref) {
    XUInt v = (XUInt)((uintptr_t)ref);
    if ((v & X_BUILD_TaggedMask) == X_BUILD_TaggedObjectFlag) {
        XUInt id = ((X_BUILD_TaggedObjectClassMask & v) >> X_BUILD_TaggedObjectClassShift);
        //id 只有4个值
        return _XRefTaggedObjectClassTable[id];
    } else {
        return NULL;
    }
}


XTaggedType _XRefGetTaggedObjectTaggedType(XRef _Nonnull ref) {
    XUInt v = (XUInt)((uintptr_t)ref);
    if ((v & X_BUILD_TaggedMask) == X_BUILD_TaggedObjectFlag) {
        XUInt id = ((X_BUILD_TaggedObjectClassMask & v) >> X_BUILD_TaggedObjectClassShift);
        //id 只有4个值
        return (XTaggedType)id;
    } else {
        return XUInt32Max;
    }
}

const _XType_s * _Nonnull _XHeapRefGetClass(XHeapRef _Nonnull ref, XCompressedType * _Nullable compressedType, const char * _Nonnull func) {
    XUInt info = _XRefGetRcInfo(ref);
    if((info & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
        XCompressedType clsId = (XCompressedType)((info & X_BUILD_CompressedRcTypeMask) >> X_BUILD_CompressedRcTypeShift);
        const _XType_s * type = _XRefGetClassWithCompressedType(clsId);
        XAssert(NULL != type, func, "not ref");
        if (NULL != compressedType) {
            *compressedType = clsId;
        }
        return type;
    } else {
        _XObjectBase * obj = (_XObjectBase *)ref;
        uintptr_t info = atomic_load(&(obj->typeInfo));
        return (const _XType_s *)info;
    }
}


/*
 32:
 bitcount: 6 .. 25 .. 1
 bitcount: 6 .. 57 .. 1
 */
const _XType_s * _Nonnull _XRefGetClass(XRef _Nonnull ref, const char * _Nonnull func) {
    XTaggedType taggedType = _XRefGetTaggedObjectTaggedType(ref);
    const _XType_s * result = NULL;
    if (taggedType <= XTaggedTypeMax) {
        result = _XRefTaggedObjectClassTable[taggedType];
        XAssert(NULL != result, func, "unknown error");
        return result;
    }
    return _XHeapRefGetClass(ref, NULL, func);
}

XClass _Nonnull XRefGetClass(XRef _Nonnull ref) {
    assert(ref);
    XClass info = (XClass)_XRefGetClass(ref, __func__);
    return info;
}





#define HASHFACTOR 2654435761U

XHashCode _XHashUInt64(XUInt64 i) {
    return (XHashCode)(i);
}
XHashCode _XHashSInt64(XSInt64 i) {
    XUInt64 u = 0;
    if (i < 0) {
        u = (XUInt64)(i * -1);
    } else {
        u = (XUInt64)i;
    }
    return _XHashUInt64(u);
}
XHashCode _XHashFloat64(XFloat64 d) {
    //转化成正数
    const XFloat64 positive = (d < 0) ? -d : d;
    
    //四舍五入
    const XFloat64 positiveInt = floor(positive + 0.5);
    
    //小数部分
    const XFloat64 fractional = (positive - positiveInt) * 18446744073709551616.0L;

    XUInt64 result = (XUInt64)fmod(positiveInt, 18446744073709551616.0L);
    if (fractional < 0) {
        result += -((XUInt64)(fabs(fractional)));
    } else if (fractional > 0) {
        result += (XUInt64)fractional;
    }
    return (XUInt32)result;
}

#define ELF_STEP32(B) T1 = (H << 4) + B; T2 = T1 & 0xF0000000; if (T2) T1 ^= (T2 >> 24); T1 &= (~T2); H = T1;
#define ELF_STEP64(B) T1 = (H << 4) + B; T2 = T1 & 0xF000000000000000ULL; if (T2) T1 ^= (T2 >> 56); T1 &= (~T2); H = T1;

#if BUILD_TARGET_RT_64_BIT
    #define ELF_STEP ELF_STEP64
#else
    #define ELF_STEP ELF_STEP32
#endif


XUInt32 _XELFHashBytes(XUInt8 * _Nullable bytes, XUInt32 length) {
    if (length > 0) {
        assert(bytes);
    }
    XUInt32 H = 0, T1, T2;
    XUInt32 rem = length;
    while (3 < rem) {
    ELF_STEP32(bytes[length - rem]);
    ELF_STEP32(bytes[length - rem + 1]);
    ELF_STEP32(bytes[length - rem + 2]);
    ELF_STEP32(bytes[length - rem + 3]);
    rem -= 4;
    }
    switch (rem) {
    case 3:  ELF_STEP32(bytes[length - 3]);
    case 2:  ELF_STEP32(bytes[length - 2]);
    case 1:  ELF_STEP32(bytes[length - 1]);
    case 0:  ;
    }
    return H;
}

XHashCode XHash(XUInt8 * _Nullable bytes, XUInt length) {
    if (length > 0) {
        assert(bytes);
    } else {
        return 0;
    }
    XUInt H = 0, T1, T2;
    XUInt rem = MIN(256, length);
    
    XUInt8 * lengthBytes = (XUInt8 *)(&length);
    ELF_STEP(lengthBytes[0]);
    ELF_STEP(lengthBytes[1]);
    ELF_STEP(lengthBytes[2]);
    ELF_STEP(lengthBytes[3]);

#if BUILD_TARGET_RT_64_BIT
    ELF_STEP(lengthBytes[4]);
    ELF_STEP(lengthBytes[5]);
    ELF_STEP(lengthBytes[6]);
    ELF_STEP(lengthBytes[7]);
#endif
    
    while (3 < rem) {
        ELF_STEP(bytes[length - rem]);
        ELF_STEP(bytes[length - rem + 1]);
        ELF_STEP(bytes[length - rem + 2]);
        ELF_STEP(bytes[length - rem + 3]);
        rem -= 4;
    }
    switch (rem) {
        case 3:  ELF_STEP(bytes[length - 3]);
        case 2:  ELF_STEP(bytes[length - 2]);
        case 1:  ELF_STEP(bytes[length - 1]);
        case 0:  ;
    }
    return H;
}

#undef ELF_STEP32
#undef ELF_STEP64
#undef ELF_STEP





extern XTaggedType XRefGetTaggedType(XRef _Nonnull ref) {
#if BUILD_TARGET_RT_64_BIT
    XUInt64 v = (XUInt64)((uintptr_t)ref);
    if ((v & X_BUILD_TaggedMask) == X_BUILD_TaggedObjectFlag) {
        XUInt64 clsId = (v & X_BUILD_TaggedObjectClassMask) >> X_BUILD_TaggedObjectClassShift;
        return (XTaggedType)clsId;
    }
#else
    XUInt32 v = (XUInt32)((uintptr_t)ref);
    if ((v & X_BUILD_TaggedMask) == X_BUILD_TaggedObjectFlag) {
        XUInt32 clsId = (v & X_BUILD_TaggedObjectClassMask) >> X_BUILD_TaggedObjectClassShift;
        return (XTaggedType)clsId;
    }
#endif
    return XUInt32Max;
}
