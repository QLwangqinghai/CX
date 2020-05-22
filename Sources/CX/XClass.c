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
#if BUILD_TARGET_RT_64_BIT
const XCompressedType XCompressedTypeDate = X_BUILD_CompressedType_Date;
const XCompressedType XCompressedTypeValue = X_BUILD_CompressedType_Value;
#endif
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


#if BUILD_TARGET_RT_64_BIT
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

#else

//_XPackage _XArray _XMap _XSet

const _XTypeIdentifier_s _XTypeIdentifierTable[] __attribute__((aligned(64))) = {
    //ConstantType
    _XTypeIdentifierMakeValue(Class),
    _XTypeIdentifierMakeValue(Null),
    _XTypeIdentifierMakeValue(Boolean),
    
    //CompressedType (Compressed·Value, Compressed·Object)
    _XTypeIdentifierMakeValue(Number),
    _XTypeIdentifierMakeValue(String),
    _XTypeIdentifierMakeValue(Data),
    _XTypeIdentifierMakeRootObject(Package),
    _XTypeIdentifierMakeRootObject(WeakStorage),
    _XTypeIdentifierMakeRootObject(Array),
    _XTypeIdentifierMakeRootObject(Storage),
    _XTypeIdentifierMakeRootObject(Map),
    _XTypeIdentifierMakeRootObject(Set),
    
    //NormalType
    _XTypeIdentifierMakeValue(Date),
    _XTypeIdentifierMakeValue(Value),
    
    _XTypeIdentifierMakeRootObject(Object),
};


#endif


const XClassIdentifier _Nonnull XMateClassIdentifier = (XClassIdentifier)&(_XTypeIdentifierTable[X_BUILD_TypeId_Class]);

//这是一个常量
const _XType_s _XRootMetaClassStorage __attribute__((aligned(8))) = {
    ._runtime = {
        .typeInfo = ATOMIC_VAR_INIT((uintptr_t)&_XRootMetaClassStorage),
        .rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),
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
        .rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),
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

//#define _XClassMakeConstant(kind, Type) \
//{\
//._runtime = {\
//.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
//.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
//},\
//.base = {\
//.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
//.kind = X_BUILD_TypeKind ##kind,\
//.xx = 0,\
//.domain = 0,\
//.tableSize = 0,\
//.super = (uintptr_t)NULL,\
//.allocator = &_XConstantValueAllocator,\
//.deinit = NULL,\
//.describe = NULL,\
//},\
//}

#define _XClassMake(Type, allocatorKind, typeKind) \
{\
._runtime = {\
.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
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


//#define _XClassMakeConstantValue(Type) \
//{\
//._runtime = {\
//.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
//.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
//},\
//.base = {\
//.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
//.kind = X_BUILD_TypeKindValue,\
//.xx = 0,\
//.domain = 0,\
//.tableSize = 0,\
//.super = (uintptr_t)NULL,\
//.allocator = &_XConstantValueAllocator,\
//.deinit = NULL,\
//.describe = NULL,\
//},\
//}

#define _XClassMakeCompressedValue(Type) _XClassMake(Type, CompressedValue, Value)


//#define _XClassMakeCompressedValue(Type) \
//{\
//._runtime = {\
//.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
//.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
//},\
//.base = {\
//.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
//.kind = X_BUILD_TypeKindValue,\
//.xx = 0,\
//.domain = 0,\
//.tableSize = 0,\
//.super = (uintptr_t)NULL,\
//.allocator = &_XCompressedObjectAllocator,\
//.deinit = NULL,\
//.describe = NULL,\
//},\
//}

#define _XClassMakeCompressedObject(Type) _XClassMake(Type, CompressedObject, Object)

//#define _XClassMakeCompressedObject(Type) \
//{\
//._runtime = {\
//.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
//.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
//},\
//.base = {\
//.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
//.kind = X_BUILD_TypeKindObject,\
//.xx = 0,\
//.domain = 0,\
//.tableSize = 0,\
//.super = (uintptr_t)NULL,\
//.allocator = &_XCompressedObjectAllocator,\
//.deinit = NULL,\
//.describe = NULL,\
//},\
//}


#define _XClassMakeValue(Type) _XClassMake(Type, Object, Value)

#define _XClassMakeObject(Type) _XClassMake(Type, Object, Object)

//#define _XClassMakeValue(Type) \
//{\
//._runtime = {\
//.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
//.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
//},\
//.base = {\
//.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
//.kind = X_BUILD_TypeKindValue,\
//.xx = 0,\
//.domain = 0,\
//.tableSize = 0,\
//.super = (uintptr_t)NULL,\
//.allocator = &_XObjectAllocator,\
//.deinit = NULL,\
//.describe = NULL,\
//},\
//}

//#define _XClassMakeObject(Type) \
//{\
//._runtime = {\
//.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
//.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
//},\
//.base = {\
//.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
//.kind = X_BUILD_TypeKindObject,\
//.xx = 0,\
//.domain = 0,\
//.tableSize = 0,\
//.super = (uintptr_t)NULL,\
//.allocator = &_XObjectAllocator,\
//.deinit = NULL,\
//.describe = NULL,\
//},\
//}





#define _XConstantValueClassMakeWithKind(Type, kind) \
{\
._runtime = {\
.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
},\
.base = {\
.identifier = &_XTypeIdentifierTable[X_BUILD_TypeIdentifier_##Type],\
.kind = X_BUILD_TypeKind##kind,\
.xx = 0,\
.domain = 0,\
.tableSize = 0,\
.super = (uintptr_t)NULL,\
.allocator = &_XConstantValueAllocator,\
.deinit = NULL,\
.describe = NULL,\
},\
}

#define _XConstantValueClassMake(Type) \
{\
._runtime = {\
.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
},\
.base = {\
.identifier = &_XTypeIdentifierTable[X_BUILD_TypeIdentifier_##Type],\
.kind = X_BUILD_TypeKindValue,\
.xx = 0,\
.domain = 0,\
.tableSize = 0,\
.super = (uintptr_t)NULL,\
.allocator = &_XConstantValueAllocator,\
.deinit = NULL,\
.describe = NULL,\
},\
}

#define _XValueClassMake(kind, Type) \
{\
._runtime = {\
.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
},\
.base = {\
.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
.kind = X_BUILD_TypeKind##kind,\
.domain = 0,\
.tableSize = 0,\
.super = NULL,\
.allocator = &_XObjectAllocator,\
.deinit = NULL,\
.describe = NULL,\
},\
}

#define _XCompressedValueClassMake(Type) \
{\
._runtime = {\
.typeInfo = (uintptr_t)&_XRootMetaClassStorage,\
.rcInfo = ATOMIC_VAR_INIT((X_BUILD_ObjectRcMax | X_BUILD_ObjectRcFlagReadOnly)),\
},\
.base = {\
.identifier = &_XTypeIdentifierTable[X_BUILD_TypeId_##Type],\
.kind = X_BUILD_TypeKindValue,\
.xx = 0,\
.domain = 0,\
.tableSize = 0,\
.super = (uintptr_t)NULL,\
.allocator = &_XCompressedObjectAllocator,\
.deinit = NULL,\
.describe = NULL,\
},\
}

//Value = 1;
//Object = 2;
//WeakableObject = 3;
//MetaClass = 0xf;



#if BUILD_TARGET_RT_64_BIT
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
};
#else

//_XPackage _XArray _XMap _XSet

const _XType_s _XClassTable[] __attribute__((aligned(64))) = {
    //ConstantType
    _XClassMakeConstantMetaClass(Class),
    _XClassMakeConstantValue(Null),
    _XClassMakeConstantValue(Boolean),

    //CompressedType
    _XClassMakeCompressedValue(Number),
    _XClassMakeCompressedValue(String),
    _XClassMakeCompressedValue(Data),
    _XClassMakeCompressedObject(Package),
    _XClassMakeCompressedObject(WeakStorage),
    _XClassMakeCompressedObject(Array),
    _XClassMakeCompressedObject(Storage),
    _XClassMakeCompressedObject(Map),
    _XClassMakeCompressedObject(Set),
    
    //NormalType
    _XClassMakeValue(Date),
    _XClassMakeValue(Value),
};


#endif

extern XCompressedType XCompressedTypeOfClass(XClass _Nonnull cls) {
    uintptr_t base = (uintptr_t)(&(_XClassTable[0]));
    uintptr_t end = base + sizeof(_XClassType);
    uintptr_t c = (uintptr_t)cls;
    if (c < base || c >= end) {
        return XUIntMax;
    } else {
        uintptr_t offset = c - base;
        if (offset % sizeof(_XType_s) == 0) {
            return offset / sizeof(_XType_s);
        } else {
            return XUIntMax;
        }
    }
}


#define XClassOf(Type) ((XClass)&(_XClassTable[X_BUILD_TypeId_##Type]))

const XClass _Nonnull XClassType = XClassOf(Class);//0
const XClass _Nonnull XClassNull = XClassOf(Null);//1
const XClass _Nonnull XClassBoolean = (XClass)&(_XClassTable[X_BUILD_CompressedType_Number - 1]);//2

const XClass _Nonnull XClassNumber = (XClass)&(_XClassTable[X_BUILD_CompressedType_Number - 1]);//3
const XClass _Nonnull XClassString = (XClass)&(_XClassTable[X_BUILD_CompressedType_String - 1]);//4
const XClass _Nonnull XClassData = (XClass)&(_XClassTable[X_BUILD_CompressedType_Data - 1]);//5
const XClass _Nonnull XClassDate = (XClass)&(_XClassTable[X_BUILD_CompressedType_Date - 1]);//6
const XClass _Nonnull XClassValue = (XClass)&(_XClassTable[X_BUILD_CompressedType_Value - 1]);//7
const XClass _Nonnull XClassPackage = (XClass)&(_XClassTable[X_BUILD_CompressedType_Package - 1]);//8

const XClass _Nonnull XClassArray = (XClass)&(_XClassTable[X_BUILD_CompressedType_Array - 1]);//9
const XClass _Nonnull XClassMap = (XClass)&(_XClassTable[X_BUILD_CompressedType_Map - 1]);//10
const XClass _Nonnull XClassSet = (XClass)&(_XClassTable[X_BUILD_CompressedType_Set - 1]);//11



const _XType_s * _Nonnull _XClassNull = &_XClassNullStorage;//1
const _XType_s * _Nonnull _XClassBoolean = &_XClassBooleanStorage;//2

const _XType_s * _Nonnull _XClassNumber = &(_XClassTable[X_BUILD_CompressedType_Number - 1]);//3
const _XType_s * _Nonnull _XClassString = &(_XClassTable[X_BUILD_CompressedType_String - 1]);//4
const _XType_s * _Nonnull _XClassData = &(_XClassTable[X_BUILD_CompressedType_Data - 1]);//5
const _XType_s * _Nonnull _XClassDate = &(_XClassTable[X_BUILD_CompressedType_Date - 1]);//6
const _XType_s * _Nonnull _XClassValue = &(_XClassTable[X_BUILD_CompressedType_Value - 1]);//7
const _XType_s * _Nonnull _XClassPackage = &(_XClassTable[X_BUILD_CompressedType_Package - 1]);//8

const _XType_s * _Nonnull _XClassArray = &(_XClassTable[X_BUILD_CompressedType_Array - 1]);//9
const _XType_s * _Nonnull _XClassMap = &(_XClassTable[X_BUILD_CompressedType_Map - 1]);//10
const _XType_s * _Nonnull _XClassSet = &(_XClassTable[X_BUILD_CompressedType_Set - 1]);//11




const _XType_s * const _Nonnull _XRefTaggedObjectClassTable[4] = {
    &(_XClassTable[X_BUILD_TypeId_Number]),
    &(_XClassTable[X_BUILD_TypeId_String]),
    &(_XClassTable[X_BUILD_TypeId_Data]),
    &(_XClassTable[X_BUILD_TypeId_Date]),
};
