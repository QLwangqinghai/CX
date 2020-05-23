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

const XCompressedType XCompressedTypeNone = 0;
const XCompressedType XCompressedTypeNumber = X_BUILD_CompressedType_Number;
const XCompressedType XCompressedTypeString = X_BUILD_CompressedType_String;
const XCompressedType XCompressedTypeData = X_BUILD_CompressedType_Data;
const XCompressedType XCompressedTypeDate = X_BUILD_CompressedType_Date;
const XCompressedType XCompressedTypeValue = X_BUILD_CompressedType_Value;
const XCompressedType XCompressedTypePackage = X_BUILD_CompressedType_Package;
const XCompressedType XCompressedTypeWeakStorage = X_BUILD_CompressedType_WeakStorage;
const XCompressedType XCompressedTypeArray = X_BUILD_CompressedType_Array;
const XCompressedType XCompressedTypeStorage = X_BUILD_CompressedType_Storage;
const XCompressedType XCompressedTypeMap = X_BUILD_CompressedType_Map;
const XCompressedType XCompressedTypeSet = X_BUILD_CompressedType_Set;
const XCompressedType XCompressedTypeMax = X_BUILD_CompressedTypeIdMax - X_BUILD_CompressedTypeIdMin + 1;


#define _XTypeIdentifierMakeValue(Type) \
{\
.name = #Type,\
.hashCode = X##Type##Hash,\
.equalTo = X##Type##Equal,\
.compare = NULL,\
}

#define _XTypeIdentifierMakeValue1(Type) \
{\
.name = #Type,\
.hashCode = X##Type##Hash,\
.equalTo = X##Type##Equal,\
.compare = X##Type##Compare,\
}

#define _XTypeIdentifierMakeRootObject(Type) \
{\
.name = #Type,\
.hashCode = XObjectHash,\
.equalTo = XObjectEqual,\
.compare = NULL,\
}


const _XTypeIdentifier_s _XTypeIdentifierTable[] __attribute__((aligned(64))) = {
    //ConstantType
    _XTypeIdentifierMakeValue(Class),
    _XTypeIdentifierMakeValue(Null),
    _XTypeIdentifierMakeValue(Boolean),
    
    //CompressedType
    _XTypeIdentifierMakeValue(Number),
    _XTypeIdentifierMakeValue(String),
    _XTypeIdentifierMakeValue(Data),
    _XTypeIdentifierMakeValue(Date),
    _XTypeIdentifierMakeValue(Value),
    _XTypeIdentifierMakeRootObject(Package),
    _XTypeIdentifierMakeRootObject(WeakStorage),
    _XTypeIdentifierMakeRootObject(Array),
    _XTypeIdentifierMakeRootObject(Storage),
    _XTypeIdentifierMakeRootObject(Map),
    _XTypeIdentifierMakeRootObject(Set),
    //NormalType
    _XTypeIdentifierMakeRootObject(Object),
};


const XClassIdentifier _Nonnull XMateClassIdentifier = (XClassIdentifier)&(_XTypeIdentifierTable[X_BUILD_TypeId_Class]);

//这是一个常量
const _XType_s _XRootMetaClassStorage __attribute__((aligned(8))) = {
    ._runtime = {
        .rcInfo = ATOMIC_VAR_INIT(X_BUILD_RcMax),
        .typeInfo = ATOMIC_VAR_INIT((uintptr_t)&_XRootMetaClassStorage),
    },
    .base = {
        .identifier = &_XTypeIdentifierTable[0],
        .kind = X_BUILD_TypeKindMetaClass,
        .domain = 0,
        .tableSize = 0,
        .super = (uintptr_t)NULL,
        .allocator = &_XConstantClassAllocator,
        .deinit = NULL,
        .describe = NULL,
    },
};

const _XType_s _XMetaClassStorage __attribute__((aligned(8))) = {
    ._runtime = {
        .typeInfo = ATOMIC_VAR_INIT((uintptr_t)&_XRootMetaClassStorage),
        .rcInfo = ATOMIC_VAR_INIT(X_BUILD_RcMax),
    },
    .base = {
        .identifier = &_XTypeIdentifierTable[0],
        .kind = X_BUILD_TypeKindMetaClass,
        .domain = 0,
        .tableSize = 0,
        .super = (uintptr_t)NULL,
        .allocator = &_XConstantClassAllocator,
        .deinit = NULL,
        .describe = NULL,
    },
};

#define _XClassMake(Type, allocatorKind, typeKind) \
{\
._runtime = {\
.rcInfo = ATOMIC_VAR_INIT(X_BUILD_RcMax),\
.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
},\
.base = {\
.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
.kind = X_BUILD_TypeKind##typeKind,\
.xx = 0,\
.domain = 0,\
.tableSize = 0,\
.super = (uintptr_t)NULL,\
.allocator = &_X##allocatorKind##Allocator,\
.deinit = NULL,\
.describe = NULL,\
},\
}

#define _XClassMakeConstantMetaClass(Type) _XClassMake(Type, ConstantClass, MetaClass)
#define _XClassMakeConstantValue(Type) _XClassMake(Type, ConstantValue, Value)


#define _XClassMakeCompressedValue(Type) _XClassMake(Type, CompressedValue, Value)


#define _XClassMakeCompressedObject(Type) _XClassMake(Type, CompressedObject, Object)


#define _XClassMakeValue(Type) _XClassMake(Type, Object, Value)

#define _XClassMakeObject(Type) _XClassMake(Type, Object, Object)

//Value = 1;
//Object = 2;
//WeakableObject = 3;
//MetaClass = 0xf;



const _XType_s _XClassTable[] __attribute__((aligned(64))) = {
    //ConstantType
    _XClassMakeConstantMetaClass(Class),
    _XClassMakeConstantValue(Null),
    _XClassMakeConstantValue(Boolean),
    
    //CompressedType
    _XClassMakeCompressedValue(Number),
    _XClassMakeCompressedValue(String),
    _XClassMakeCompressedValue(Data),
    _XClassMakeCompressedValue(Date),
    _XClassMakeCompressedValue(Value),
    _XClassMakeCompressedObject(Package),
    _XClassMakeCompressedObject(WeakStorage),
    _XClassMakeCompressedObject(Array),
    _XClassMakeCompressedObject(Storage),
    _XClassMakeCompressedObject(Map),
    _XClassMakeCompressedObject(Set),
    //NormalType

    _XClassMakeCompressedObject(Object),
};


extern XCompressedType XCompressedTypeOfClass(XClass _Nonnull cls) {
    uintptr_t base = (uintptr_t)(&(_XClassTable[0]));
    uintptr_t end = base + sizeof(_XType_s);
    uintptr_t c = (uintptr_t)cls;
    if (c < base || c >= end) {
        return XUIntMax;
    } else {
        uintptr_t offset = c - base;
        if (offset % sizeof(_XType_s) == 0) {
            XIndex id = offset / sizeof(_XType_s);
            if (id <= X_BUILD_CompressedTypeIdMax && id >= X_BUILD_CompressedTypeIdMin) {
                return id - X_BUILD_CompressedTypeIdMin;
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
const XClass _Nonnull XClassWeakStorage = XClassOf(WeakStorage);
const XClass _Nonnull XClassArray = XClassOf(Array);
const XClass _Nonnull XClassStorage = XClassOf(Storage);
const XClass _Nonnull XClassMap = XClassOf(Map);
const XClass _Nonnull XClassSet = XClassOf(Set);
const XClass _Nonnull XClassObject = XClassOf(Object);

const _XType_s * const _Nonnull _XRefTaggedObjectClassTable[4] = {
    &(_XClassTable[X_BUILD_TypeId_Number]),
    &(_XClassTable[X_BUILD_TypeId_String]),
    &(_XClassTable[X_BUILD_TypeId_Data]),
    &(_XClassTable[X_BUILD_TypeId_Date]),
};
