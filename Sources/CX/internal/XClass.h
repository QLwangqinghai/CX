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

#define X_BUILD_TypeId_Class 0
#define X_BUILD_TypeId_Null 1
#define X_BUILD_TypeId_Boolean 2

#if BUILD_TARGET_RT_64_BIT

#define X_BUILD_TypeId_Number 3
#define X_BUILD_TypeId_String 4
#define X_BUILD_TypeId_Data 5
#define X_BUILD_TypeId_Date 6
#define X_BUILD_TypeId_Value 7
#define X_BUILD_TypeId_Package 8
#define X_BUILD_TypeId_WeakStorage 9
#define X_BUILD_TypeId_Array 10
#define X_BUILD_TypeId_Storage 11
#define X_BUILD_TypeId_Map 12
#define X_BUILD_TypeId_Set 13

#define X_BUILD_CompressedTypeIdMin X_BUILD_TypeId_Number
#define X_BUILD_CompressedTypeIdMax X_BUILD_TypeId_Set

#else

#define X_BUILD_TypeId_Number 3
#define X_BUILD_TypeId_String 4
#define X_BUILD_TypeId_Data 5
#define X_BUILD_TypeId_Package 6
#define X_BUILD_TypeId_WeakStorage 7
#define X_BUILD_TypeId_Array 8
#define X_BUILD_TypeId_Storage 9
#define X_BUILD_TypeId_Map 10
#define X_BUILD_TypeId_Set 11

#define X_BUILD_TypeId_Date 12
#define X_BUILD_TypeId_Value 13

#define X_BUILD_CompressedTypeIdMin X_BUILD_TypeId_Number
#define X_BUILD_CompressedTypeIdMax X_BUILD_TypeId_Set

#endif


#define X_BUILD_CompressedType(Name) (X_BUILD_TypeId_##Name - X_BUILD_CompressedTypeIdMin + 1)

//X_BUILD_CompressedType()
#define X_BUILD_CompressedType_Number X_BUILD_CompressedType(Number)
#define X_BUILD_CompressedType_String X_BUILD_CompressedType(String)
#define X_BUILD_CompressedType_Data X_BUILD_CompressedType(Data)
#if BUILD_TARGET_RT_64_BIT
#define X_BUILD_CompressedType_Date X_BUILD_CompressedType(Date)
#define X_BUILD_CompressedType_Value X_BUILD_CompressedType(Value)
#endif
#define X_BUILD_CompressedType_Package X_BUILD_CompressedType(Package)
#define X_BUILD_CompressedType_WeakStorage X_BUILD_CompressedType(WeakStorage)
#define X_BUILD_CompressedType_Array X_BUILD_CompressedType(Array)
#define X_BUILD_CompressedType_Storage X_BUILD_CompressedType(Storage)
#define X_BUILD_CompressedType_Map X_BUILD_CompressedType(Map)
#define X_BUILD_CompressedType_Set X_BUILD_CompressedType(Set)


//0
extern const XCompressedType XCompressedTypeNone;
extern const XCompressedType XCompressedTypeNumber;
extern const XCompressedType XCompressedTypeString;
extern const XCompressedType XCompressedTypeData;
#if BUILD_TARGET_RT_64_BIT
extern const XCompressedType XCompressedTypeDate;
extern const XCompressedType XCompressedTypeValue;
#endif
extern const XCompressedType XCompressedTypePackage;
extern const XCompressedType XCompressedTypeWeakStorage;
extern const XCompressedType XCompressedTypeArray;
extern const XCompressedType XCompressedTypeStorage;
extern const XCompressedType XCompressedTypeMap;
extern const XCompressedType XCompressedTypeSet;
extern const XCompressedType XCompressedTypeMax;

extern const XClassIdentifier _Nonnull XMateClassIdentifier;
extern const _XType_s _XClassTable[];
extern const _XType_s _XClassNullStorage;
extern const _XType_s _XClassBooleanStorage;

static inline XClass _Nullable _XRefGetClassWithCompressedType(XCompressedType id) {
    if (id <= 0 || id > XCompressedTypeMax) {
        return NULL;
    } else {
        return (XClass)&(_XClassTable[id - 1]);
    }
}

extern const _XType_s * const _Nonnull _XRefTaggedObjectClassTable[4];


#endif /* XClass_h */
