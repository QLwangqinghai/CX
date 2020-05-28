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

#if CX_TARGET_RT_64_BIT
#define X_BUILD_TypeKindObject 0x7FFFFFFFFFFFFFFFULL
#define X_BUILD_TypeKindNotObjectMask 0x8000000000000000ULL
#define X_BUILD_TypeKindNotObjectFlag 0x8000000000000000ULL

#define X_BUILD_TypeKindNotObjectIdMask 0x7FFFFFFFFFFFFFFFULL

#else
#define X_BUILD_TypeKindObject 0x7FFFFFFFUL
#define X_BUILD_TypeKindNotObjectMask 0x80000000UL
#define X_BUILD_TypeKindNotObjectFlag 0x80000000UL

#define X_BUILD_TypeKindNotObjectIdMask 0x7FFFFFFFUL

#endif

#define X_BUILD_TypeId_MetaType X_BUILD_UInt(0)

#define X_BUILD_TypeId_Class X_BUILD_UInt(0)
#define X_BUILD_TypeId_Null X_BUILD_UInt(1)
#define X_BUILD_TypeId_Boolean X_BUILD_UInt(2)
#define X_BUILD_TypeId_Number X_BUILD_UInt(3)
#define X_BUILD_TypeId_Date X_BUILD_UInt(4)
#define X_BUILD_TypeId_String X_BUILD_UInt(5)
#define X_BUILD_TypeId_Data X_BUILD_UInt(6)
#define X_BUILD_TypeId_Value X_BUILD_UInt(7)
#define X_BUILD_TypeId_Package X_BUILD_UInt(8)
#define X_BUILD_TypeId_WeakPackage X_BUILD_UInt(9)
#define X_BUILD_TypeId_Array X_BUILD_UInt(10)
#define X_BUILD_TypeId_Storage X_BUILD_UInt(11)
#define X_BUILD_TypeId_Map X_BUILD_UInt(12)
#define X_BUILD_TypeId_Set X_BUILD_UInt(13)

#define X_BUILD_TypeId_Max X_BUILD_TypeId_Set

#define X_BUILD_TypeId_CollectionMin X_BUILD_TypeId_Package


#define X_BUILD_TypeId_CompressedTypeMin X_BUILD_TypeId_Number
#define X_BUILD_TypeId_CompressedTypeCount 11


#define X_BUILD_CompressedType(Name) (X_BUILD_TypeId_##Name - X_BUILD_TypeId_CompressedTypeMin)

//X_BUILD_CompressedType()
#define X_BUILD_CompressedType_Number X_BUILD_CompressedType(Number)
#define X_BUILD_CompressedType_Date X_BUILD_CompressedType(Date)
#define X_BUILD_CompressedType_String X_BUILD_CompressedType(String)
#define X_BUILD_CompressedType_Data X_BUILD_CompressedType(Data)
#define X_BUILD_CompressedType_Value X_BUILD_CompressedType(Value)
#define X_BUILD_CompressedType_Package X_BUILD_CompressedType(Package)
#define X_BUILD_CompressedType_WeakPackage X_BUILD_CompressedType(WeakPackage)
#define X_BUILD_CompressedType_Array X_BUILD_CompressedType(Array)
#define X_BUILD_CompressedType_Storage X_BUILD_CompressedType(Storage)
#define X_BUILD_CompressedType_Map X_BUILD_CompressedType(Map)
#define X_BUILD_CompressedType_Set X_BUILD_CompressedType(Set)

#define XCompressedTypeNone XIndexNotFound

extern const XCompressedType XCompressedTypeNumber;//0
extern const XCompressedType XCompressedTypeDate;
extern const XCompressedType XCompressedTypeString;
extern const XCompressedType XCompressedTypeData;
extern const XCompressedType XCompressedTypeValue;
extern const XCompressedType XCompressedTypePackage;
extern const XCompressedType XCompressedTypeWeakPackage;
extern const XCompressedType XCompressedTypeArray;
extern const XCompressedType XCompressedTypeStorage;
extern const XCompressedType XCompressedTypeMap;
extern const XCompressedType XCompressedTypeSet;//10

//还可以加5个

extern const XCompressedType XCompressedTypeMax;


#define XRefKindOfNormal(Name) (X_BUILD_TypeKindNotObjectFlag | X_BUILD_TypeId_##Name)


extern const XType_s _XClassTable[];


#define _XClassOf(Type) (&(_XClassTable[X_BUILD_TypeId_##Type]))

#define XClassOf(Type) ((XClass)_XClassOf(Type))

extern const XObjectType_s XObjectTypeRootObject;
extern const XClass _Nonnull XClassObject;// = (const XClass)&XObjectTypeRootObject;


extern XHashCode _XObjectHash(XRef _Nonnull obj);
extern XBool _XObjectEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern void _XObjectDeinit(XRef _Nonnull obj);
extern void _XObjectDescribe(XRef _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);

extern XHashCode _XClassHash(XRef _Nonnull obj);
extern XBool _XClassEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern void _XClassDescribe(XRef _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);

#endif /* XClass_h */
