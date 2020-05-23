//
//  XClass.c
//  X
//
//  Created by clf on 2020/5/19.
//  Copyright © 2020 haoqi. All rights reserved.
//

#include "XClass.h"
#include "XRef.h"
#include "XObject.h"

//
//typedef XHashCode (*XRefHashCode_f)(XRef _Nonnull obj);
//typedef XBool (*XRefEqual_f)(XRef _Nonnull lhs, XRef _Nonnull rhs);
//typedef void (*XRefDeinit_f)(XRef _Nonnull obj);
//typedef void (*XRefDescribe_f)(XRef _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);


XHashCode _XClassHash(XRef _Nonnull obj) {
    
    return 0;
}

XBool _XClassEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
    return 0;
}
void _XClassDeinit(XRef _Nonnull obj) {
    
}
void _XClassDescribe(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
}

XHashCode _XConstantValueHash(XRef _Nonnull obj) {
    
    return 0;
}

XBool _XConstantValueEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
    return 0;
}
void _XConstantValueDeinit(XRef _Nonnull obj) {
    
}
void _XConstantValueDescribe(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
}

XHashCode _XValueHash(XRef _Nonnull obj) {
    
    return 0;
}
XBool _XValueEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
    return 0;
}
void _XValueDeinit(XRef _Nonnull obj) {
    
}
void _XValueDescribe(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
}

XHashCode _XCollectionHash(XRef _Nonnull obj) {
    
    return 0;
}
XBool _XCollectionEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
    return 0;
}
void _XCollectionDeinit(XRef _Nonnull obj) {
    
}
void _XCollectionDescribe(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
}

XHashCode _XObjectHash(XRef _Nonnull obj) {
    
    return 0;
}
XBool _XObjectEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
    return 0;
}
void _XObjectDeinit(XRef _Nonnull obj) {
    
}
void _XObjectDescribe(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    
}

#define _XRefKindMake(Type) \
{\
.hashCode = _X##Type##Hash,\
.equal = _X##Type##Equal,\
.deinit = _X##Type##Deinit,\
.describe = _X##Type##Describe,\
}

const _XRefKind_t _XRefKindTable[] __attribute__((aligned(64))) = {
    _XRefKindMake(Class),
    _XRefKindMake(ConstantValue),
    _XRefKindMake(Value),
    _XRefKindMake(Collection),
    _XRefKindMake(Object),
};

#define X_BUILD_RefKindId_Class X_BUILD_UInt(0)
#define X_BUILD_RefKindId_ConstantValue X_BUILD_UInt(1)
#define X_BUILD_RefKindId_Value X_BUILD_UInt(2)
#define X_BUILD_RefKindId_Collection X_BUILD_UInt(3)
#define X_BUILD_RefKindId_Object X_BUILD_UInt(4)


#define XRefKindOf(Kind) (&(_XRefKindTable[X_BUILD_RefKindId_##Kind]))

XRefKind _Nonnull XRefKindClass = XRefKindOf(Class);
XRefKind _Nonnull XRefKindConstantValue = XRefKindOf(ConstantValue);
XRefKind _Nonnull XRefKindValue = XRefKindOf(Value);
XRefKind _Nonnull XRefKindCollection = XRefKindOf(Collection);
XRefKind _Nonnull XRefKindObject = XRefKindOf(Object);


const XCompressedType XCompressedTypeNumber = X_BUILD_CompressedType_Number;
const XCompressedType XCompressedTypeString = X_BUILD_CompressedType_String;
const XCompressedType XCompressedTypeData = X_BUILD_CompressedType_Data;
const XCompressedType XCompressedTypeDate = X_BUILD_CompressedType_Date;
const XCompressedType XCompressedTypeValue = X_BUILD_CompressedType_Value;
const XCompressedType XCompressedTypePackage = X_BUILD_CompressedType_Package;
const XCompressedType XCompressedTypeWeakPackage = X_BUILD_CompressedType_WeakPackage;
const XCompressedType XCompressedTypeArray = X_BUILD_CompressedType_Array;
const XCompressedType XCompressedTypeStorage = X_BUILD_CompressedType_Storage;
const XCompressedType XCompressedTypeMap = X_BUILD_CompressedType_Map;
const XCompressedType XCompressedTypeSet = X_BUILD_CompressedType_Set;
const XCompressedType XCompressedTypeMax = XCompressedTypeSet;


//这是一个常量
const XType_s _XRootMetaClassStorage __attribute__((aligned(8))) = {
    ._runtime = {
        .rcInfo = ATOMIC_VAR_INIT(X_BUILD_RcMax),
        .typeInfo = ATOMIC_VAR_INIT((uintptr_t)&_XRootMetaClassStorage),
    },
    .base = {
        .name = "MetaClass",
        .kind = XRefKindOf(Class),
    },
};

//const XType_s _XObjectClass __attribute__((aligned(8))) = {
//    ._runtime = {
//        .typeInfo = ATOMIC_VAR_INIT((uintptr_t)&_XRootMetaClassStorage),
//        .rcInfo = ATOMIC_VAR_INIT(X_BUILD_RcMax),
//    },
//    .base = {
//        .identifier = &_XTypeIdentifierObject,
//        .kind = X_BUILD_TypeObjectKindObject,
//        .domain = 0,
//        .tableSize = 0,
//        .super = (uintptr_t)NULL,
//        .allocator = &_XObjectAllocator,
//        .deinit = NULL,
//        .describe = NULL,
//    },
//};

#define _XClassMake(Kind, Name) \
{\
._runtime = {\
.rcInfo = ATOMIC_VAR_INIT(X_BUILD_RcMax),\
.typeInfo = (uintptr_t)_XClassTable,\
},\
.base = {\
.name = #Name,\
.kind = XRefKindOf(Kind),\
},\
}

#define _XClassMakeConstantValue(Name) _XClassMake(ConstantValue, Name)

#define _XClassMakeValue(Name) _XClassMake(Value, Name)


#define _XClassMakeCollection(Name) _XClassMake(Collection, Name)


#define _XClassMakeObject(Name) _XClassMake(Object, Name)

const XType_s _XClassTable[] __attribute__((aligned(64))) = {
    //ConstantType
    _XClassMake(Class, MetaClass),
    _XClassMakeConstantValue(Null),
    _XClassMakeConstantValue(Boolean),
    
    //CompressedType
    _XClassMakeValue(Number),
    _XClassMakeValue(String),
    _XClassMakeValue(Data),
    _XClassMakeValue(Date),
    _XClassMakeValue(Value),
    
    _XClassMakeCollection(Package),
    _XClassMakeCollection(WeakPackage),
    _XClassMakeCollection(Array),
    _XClassMakeCollection(Storage),
    _XClassMakeCollection(Map),
    _XClassMakeCollection(Set),
    //NormalType

};

const XObjectType_s XObjectTypeRootObject = _XClassMake(Object, Object);


extern XCompressedType XCompressedTypeOfClass(XClass _Nonnull cls) {
    uintptr_t base = (uintptr_t)(&(_XClassTable[0]));
    uintptr_t end = base + sizeof(XType_s);
    uintptr_t c = (uintptr_t)cls;
    if (c < base || c >= end) {
        return XUIntMax;
    } else {
        uintptr_t offset = c - base;
        if (offset % sizeof(XType_s) == 0) {
            XIndex id = offset / sizeof(XType_s);
            if (id < X_BUILD_TypeId_CompressedTypeMin + X_BUILD_TypeId_CompressedTypeCount && id >= X_BUILD_TypeId_CompressedTypeMin) {
                return id - X_BUILD_TypeId_CompressedTypeMin;
            } else {
                return XUIntMax;
            }
        } else {
            return XUIntMax;
        }
    }
}



const XClass _Nonnull XClassType = XClassOf(Class);
const XClass _Nonnull XClassNull = XClassOf(Null);
const XClass _Nonnull XClassBoolean = XClassOf(Boolean);
const XClass _Nonnull XClassNumber = XClassOf(Number);
const XClass _Nonnull XClassString = XClassOf(String);
const XClass _Nonnull XClassData = XClassOf(Data);
const XClass _Nonnull XClassDate = XClassOf(Date);
const XClass _Nonnull XClassValue = XClassOf(Value);
const XClass _Nonnull XClassPackage = XClassOf(Package);
const XClass _Nonnull XClassWeakPackage = XClassOf(WeakPackage);
const XClass _Nonnull XClassArray = XClassOf(Array);
const XClass _Nonnull XClassStorage = XClassOf(Storage);
const XClass _Nonnull XClassMap = XClassOf(Map);
const XClass _Nonnull XClassSet = XClassOf(Set);

const XClass _Nonnull XClassObject = (const XClass)&XObjectTypeRootObject;



//const XClass _Nonnull XClassObject = XClassOf(Object);

const XType_s * const _Nonnull _XRefTaggedObjectClassTable[4] = {
    &(_XClassTable[X_BUILD_TypeId_Number]),
    &(_XClassTable[X_BUILD_TypeId_String]),
    &(_XClassTable[X_BUILD_TypeId_Data]),
    &(_XClassTable[X_BUILD_TypeId_Date]),
};
