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


const XTaggedType XTaggedTypeConstantValue = X_BUILD_TaggedConstantValue;
const XTaggedType XTaggedTypeNumber = X_BUILD_TaggedObjectClassNumber;
const XTaggedType XTaggedTypeDate = X_BUILD_TaggedObjectClassDate;
const XTaggedType XTaggedTypeByteStorage = X_BUILD_TaggedObjectByteStorage;
const XTaggedType XTaggedTypeMax = XTaggedTypeByteStorage;

XBool XStringEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
XBool XDataEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};
XBool XValueEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {return false;};



//64bit 压缩的头
 /* flagBegin:3 type:6 (rcInfo54(flag:4 count:18+32)) flagEnd:1  */

//32bit rc info
/* flag:4 count:18+32 */

XRefKind XRefGetKind(XRef _Nonnull ref) {
    XAssert(NULL != ref, __func__, "ref is NULL");

    XIndex typeId = XRefGetTypeId(ref);
    if (typeId <= X_BUILD_TypeId_Max) {//values
        return _XClassTable[typeId].base.kind;
    } else {
        //Object
        const XObjectType_s * type = _XObjectGetClass(ref, __func__);
        assert(type);
        return type->base.kind;
    }
    return 0;
}

XBool XRefIsMetaType(XRef _Nonnull ref) {
    assert(ref);
    const XType_s * type = (const XType_s *)XRefGetClass(ref);
    if (XRefKindOfNormal(MetaType) == type->base.kind) {
        //is a class
        const XType_s * cls = (const XType_s *)ref;
        if (XRefKindOfNormal(MetaType) == cls->base.kind) {
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

XClass _Nonnull XRefGetClass(XRef _Nonnull ref) {
    XIndex typeId = XRefGetTypeId(ref);
    if (typeId <= X_BUILD_TypeId_Max) {
        return (XClass)(&(_XClassTable[typeId]));
        //values
    } else {
        //Object
        const XObjectType_s * type = _XObjectGetClass(ref, __func__);
        assert(type);
        return (XClass)type;
    }
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


XCompressedType XHeapRefGetCompressedType(XHeapRef _Nonnull ref) {
    XUInt info = _XRefGetRcInfo(ref);
    if((info & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
        return (XCompressedType)((info & X_BUILD_CompressedRcTypeMask) >> X_BUILD_CompressedRcTypeShift);
    } else {
        return XCompressedTypeNone;
    }
}

XTaggedType _XRefGetTaggedType(XRef _Nonnull ref) {
    XUInt v = (XUInt)((uintptr_t)ref);
    if ((v & X_BUILD_TaggedMask) == X_BUILD_TaggedObjectFlag) {
        XUInt taggedType = ((X_BUILD_TaggedObjectClassMask & v) >> X_BUILD_TaggedObjectClassShift);
        return (XTaggedType)taggedType;
    } else {
        return XIndexNotFound;
    }
}

XIndex XRefGetTypeId(XRef _Nonnull ref) {
    XUInt v = (XUInt)((uintptr_t)ref);
    if ((v & X_BUILD_TaggedMask) == X_BUILD_TaggedObjectFlag) {
        XUInt taggedType = ((X_BUILD_TaggedObjectClassMask & v) >> X_BUILD_TaggedObjectClassShift);
        switch (taggedType) {
            case X_BUILD_TaggedConstantValue: {
                XAssert((v >= X_BUILD_TaggedConstantValueMin && v <= X_BUILD_TaggedConstantValueMax), __func__, "")
                return XTaggedConstantValueTable[(uintptr_t)ref - X_BUILD_TaggedConstantValueMin].typeId;
            }
                break;
            case X_BUILD_TaggedObjectClassNumber: {
                return X_BUILD_TypeId_Number;
            }
                break;
            case X_BUILD_TaggedObjectClassDate: {
                return X_BUILD_TypeId_Date;
            }
                break;
            case X_BUILD_TaggedObjectByteStorage: {
                if ((X_BUILD_TaggedObjectByteStorageDataFlag & (XUInt)ref) == X_BUILD_TaggedObjectByteStorageDataFlag) {
                    return X_BUILD_TypeId_Data;
                } else {
                    return X_BUILD_TypeId_String;
                }
            }
                break;
            default: {
                abort();
            }
                break;
        }
    } else {
        XAssert(NULL != ref, __func__, "");
        XUInt info = _XRefGetRcInfo(ref);
        if((info & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
            return ((info & X_BUILD_CompressedRcTypeMask) >> X_BUILD_CompressedRcTypeShift) + X_BUILD_TypeId_CompressedTypeMin;
        } else {
            return XIndexNotFound;
        }
    }
}


XIndex _XHeapRefGetTypeId(XHeapRef _Nonnull ref) {
    XUInt info = _XRefGetRcInfo(ref);
    if((info & X_BUILD_CompressedRcMask) == X_BUILD_CompressedRcFlag) {
        return ((info & X_BUILD_CompressedRcTypeMask) >> X_BUILD_CompressedRcTypeShift) + X_BUILD_TypeId_CompressedTypeMin;
    } else {
        return XIndexNotFound;
    }
}


const XObjectType_s * _Nonnull _XObjectGetClass(_XObject * _Nonnull object, const char * _Nonnull func) {
    uintptr_t info = atomic_load(&(object->_runtime.typeInfo));
    const XType_s * type = (const XType_s *)info;
    XAssert(NULL != type, func, "");
    XAssert(X_BUILD_TypeKindObject == type->base.kind, func, "");
    return (const XObjectType_s *)type;
}

static inline XBool XRefKindIsObject(XRefKind kind) {
    return (X_BUILD_TypeKindObject == kind);
}

static inline XIndex XRefKindIndex(XRefKind kind) {
    return (X_BUILD_TypeKindNotObjectIdMask & kind);
}

//Class Null Boolean Object
static const XType_s * _Nonnull _XHeapRefGetNoncompressedType(XHeapRef _Nonnull ref, const char * _Nonnull func) {
    XObjectBase_s * obj = (XObjectBase_s *)ref;
    uintptr_t info = atomic_load(&(obj->typeInfo));
    const XType_s * type = (const XType_s *)info;
    return type;
}


XHashCode XRefHash(XRef _Nonnull obj) {
    XAssert(NULL != obj, __func__, "");
    XIndex typeId = XRefGetTypeId(obj);
    if (typeId == 0) {
        return _XClassHash(obj);
    } else if (typeId < X_BUILD_TypeId_CompressedTypeMin) {
        //常量
        return XTaggedConstantValueTable[(uintptr_t)obj - X_BUILD_TaggedConstantValueMin].hashCode;
    } if (typeId <= X_BUILD_TypeId_Max) {
        switch (typeId) {
            case X_BUILD_TypeId_Number: {
                return false;
            }
                break;
            case X_BUILD_TypeId_Date: {
                return false;
                
            }
                break;
            case X_BUILD_TypeId_String: {
                return false;
                
            }
                break;
            case X_BUILD_TypeId_Data: {
                return false;
                
            }
                break;
            case X_BUILD_TypeId_Value: {
                return false;
                
            }
                break;
            default: {
                return _XAddressHash(obj);
            }
                break;
        }

    } else {
        //Object
        return _XObjectHash(obj);
    }
}
XBool XRefEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    XAssert(NULL != lhs, __func__, "");
    XAssert(NULL != rhs, __func__, "");
    XIndex typeId = XRefGetTypeId(lhs);
    XIndex rtypeId = XRefGetTypeId(rhs);
    if (typeId != rtypeId) {
        return false;
    }
    if (typeId == 0) {
        return _XClassEqual(lhs, rhs);
    } else if (typeId < X_BUILD_TypeId_CompressedTypeMin) {
        //常量
        return lhs == rhs;
    } else if (typeId < X_BUILD_TypeId_CollectionMin) {
        //TODO: FIX

        switch (typeId) {
            case X_BUILD_TypeId_Number: {
                return false;
            }
                break;
            case X_BUILD_TypeId_Date: {
                return false;

            }
                break;
            case X_BUILD_TypeId_String: {
                return false;

            }
                break;
            case X_BUILD_TypeId_Data: {
                return false;

            }
                break;
            case X_BUILD_TypeId_Value: {
                return false;

            }
                break;
            default: {
                return lhs == rhs;
            }
                break;
        }
    } else if (typeId <= X_BUILD_TypeId_Max) {
        return lhs == rhs;
    } else {
        //Object
        return _XObjectEqual(lhs, rhs);
    }
}
void _XRefDeinit(XRef _Nonnull obj) {
    XAssert(NULL != obj, __func__, "");
    XIndex typeId = XRefGetTypeId(obj);
    if (typeId == 0) {
        XAssert(false, __func__, "");
    } else if (typeId < X_BUILD_TypeId_CompressedTypeMin) {
        //常量
        XAssert(false, __func__, "");
    } else if (typeId <= X_BUILD_TypeId_Max) {
        //values

        //Collection
        switch (typeId) {
            case X_BUILD_TypeId_Number: {

            }
                break;
            case X_BUILD_TypeId_Date: {

                
            }
                break;
            case X_BUILD_TypeId_String: {

                
            }
                break;
            case X_BUILD_TypeId_Data: {

                
            }
                break;
            case X_BUILD_TypeId_Value: {

                
            }
                break;
            default: {

            }
                break;
        }
    } else {
        //Object
        _XObjectDeinit(obj);
    }
}
void XRefDescribe(XRef _Nonnull obj, _XDescriptionBuffer _Nonnull buffer) {
    XAssert(NULL != obj, __func__, "");
    XAssert(NULL != buffer, __func__, "");

    XIndex typeId = XRefGetTypeId(obj);
    if (typeId == 0) {

    } else if (typeId < X_BUILD_TypeId_CompressedTypeMin) {
        //常量
        const XTaggedConstantValue * value = &(XTaggedConstantValueTable[(uintptr_t)obj - X_BUILD_TaggedConstantValueMin]);
    } else if (typeId <= X_BUILD_TypeId_Max) {
        //values
        switch (typeId) {
            case X_BUILD_TypeId_Number: {

            }
                break;
            case X_BUILD_TypeId_Date: {

                
            }
                break;
            case X_BUILD_TypeId_String: {

                
            }
                break;
            case X_BUILD_TypeId_Data: {

                
            }
                break;
            case X_BUILD_TypeId_Value: {

                
            }
                break;
            default: {

            }
                break;
        }
    } else {
        //Object
        _XObjectDescribe(obj, buffer);
    }
}




