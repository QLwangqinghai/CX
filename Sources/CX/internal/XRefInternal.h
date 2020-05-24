//
//  XRefInternal.h
//  X
//
//  Created by clf on 2020/5/24.
//  Copyright © 2020 haoqi. All rights reserved.
//

#ifndef XRefInternal_h
#define XRefInternal_h

#include "XRef.h"
#include "XRuntimeInternal.h"



XHashCode _XNullHash(_XNull * _Nonnull obj);
XBool _XNullEqual(_XNull * _Nonnull lhs, _XNull * _Nonnull rhs);

void _XNullDescribe(_XNull * _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);

XHashCode _XBooleanHash(_XBoolean * _Nonnull obj);
XBool _XBooleanEqual(_XBoolean * _Nonnull lhs, _XBoolean * _Nonnull rhs);
void _XBooleanDescribe(_XBoolean * _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);


XHashCode _XNumberUnpackedHash(_XNumber * _Nonnull obj);
XBool _XNumberUnpackedEqual(XNumberUnpacked_t * _Nonnull lhs, XNumberUnpacked_t * _Nonnull rhs);
void _XNumberUnpackedDescribe(XNumberUnpacked_t * _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);


XHashCode _XByteStorageUnpackedHash(XByteStorageUnpacked_t * _Nonnull obj);
XBool _XByteStorageUnpackedEqual(XByteStorageUnpacked_t * _Nonnull lhs, XByteStorageUnpacked_t * _Nonnull rhs);
void _XStringDescribe(XByteStorageUnpacked_t * _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);
void _XDataDescribe(XByteStorageUnpacked_t * _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);

XHashCode _XValueHash(_XValue * _Nonnull obj);
XBool _XValueEqual(_XValue * _Nonnull lhs, _XValue * _Nonnull rhs);
void _XValueDescribe(_XValue * _Nonnull obj, _XDescriptionBuffer _Nonnull buffer);




#endif /* XRefInternal_h */
