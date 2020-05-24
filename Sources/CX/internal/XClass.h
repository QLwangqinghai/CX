//
//  XClass.h
//  X
//
//  Created by clf on 2020/5/19.
//  Copyright © 2020 haoqi. All rights reserved.
//

#ifndef XClass_h
#define XClass_h

#include "XType.h"
#include "XRuntimeInternal.h"


#define X_BUILD_TypeId_Class X_BUILD_UInt(0)
#define X_BUILD_TypeId_Null X_BUILD_UInt(1)
#define X_BUILD_TypeId_Boolean X_BUILD_UInt(2)
#define X_BUILD_TypeId_Number X_BUILD_UInt(3)
#define X_BUILD_TypeId_String X_BUILD_UInt(4)
#define X_BUILD_TypeId_Data X_BUILD_UInt(5)
#define X_BUILD_TypeId_Date X_BUILD_UInt(6)
#define X_BUILD_TypeId_Value X_BUILD_UInt(7)
#define X_BUILD_TypeId_Package X_BUILD_UInt(8)
#define X_BUILD_TypeId_WeakPackage X_BUILD_UInt(9)
#define X_BUILD_TypeId_Array X_BUILD_UInt(10)
#define X_BUILD_TypeId_Storage X_BUILD_UInt(11)
#define X_BUILD_TypeId_Map X_BUILD_UInt(12)
#define X_BUILD_TypeId_Set X_BUILD_UInt(13)

#define X_BUILD_TypeId_CompressedTypeMin X_BUILD_TypeId_Number
#define X_BUILD_TypeId_CompressedTypeCount 11


#define X_BUILD_CompressedType(Name) (X_BUILD_TypeId_##Name - X_BUILD_TypeId_CompressedTypeMin)

//X_BUILD_CompressedType()
#define X_BUILD_CompressedType_Number X_BUILD_CompressedType(Number)
#define X_BUILD_CompressedType_String X_BUILD_CompressedType(String)
#define X_BUILD_CompressedType_Data X_BUILD_CompressedType(Data)
#define X_BUILD_CompressedType_Date X_BUILD_CompressedType(Date)
#define X_BUILD_CompressedType_Value X_BUILD_CompressedType(Value)
#define X_BUILD_CompressedType_Package X_BUILD_CompressedType(Package)
#define X_BUILD_CompressedType_WeakPackage X_BUILD_CompressedType(WeakPackage)
#define X_BUILD_CompressedType_Array X_BUILD_CompressedType(Array)
#define X_BUILD_CompressedType_Storage X_BUILD_CompressedType(Storage)
#define X_BUILD_CompressedType_Map X_BUILD_CompressedType(Map)
#define X_BUILD_CompressedType_Set X_BUILD_CompressedType(Set)

#define XCompressedTypeNone XUIntMax

extern const XCompressedType XCompressedTypeNumber;//0
extern const XCompressedType XCompressedTypeString;
extern const XCompressedType XCompressedTypeData;
extern const XCompressedType XCompressedTypeDate;
extern const XCompressedType XCompressedTypeValue;
extern const XCompressedType XCompressedTypePackage;
extern const XCompressedType XCompressedTypeWeakPackage;
extern const XCompressedType XCompressedTypeArray;
extern const XCompressedType XCompressedTypeStorage;
extern const XCompressedType XCompressedTypeMap;
extern const XCompressedType XCompressedTypeSet;//10

//还可以加5个

extern const XCompressedType XCompressedTypeMax;

extern const XType_s _XClassTable[];


#define _XClassOf(Type) (&(_XClassTable[X_BUILD_TypeId_##Type]))

#define XClassOf(Type) ((XClass)_XClassOf(Type))


static inline const XType_s * _Nullable _XRefGetClassWithCompressedType(XCompressedType id) {
    if (id <= 0 || id > XCompressedTypeMax) {
        return NULL;
    } else {
        return &(_XClassTable[id + X_BUILD_TypeId_CompressedTypeMin - 1]);
    }
}
extern const XObjectType_s XObjectTypeRootObject;
extern const XClass _Nonnull XClassObject;// = (const XClass)&XObjectTypeRootObject;

extern const XType_s * const _Nonnull _XRefTaggedObjectClassTable[4];
extern const XCompressedType _XRefTaggedObjectTypeTable[4];


#endif /* XClass_h */
