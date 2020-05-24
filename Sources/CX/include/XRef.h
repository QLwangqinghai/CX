//
//  XRef.h
//  
//
//  Created by vector on 2020/4/4.
//

#ifndef XRef_h
#define XRef_h


#if defined(__cplusplus)
extern "C" {
#endif

#include "XRuntime.h"

#pragma mark - XClass



#pragma mark - XNull

extern const XNull _Nonnull XNullShared;
extern XNull _Nonnull XNullCreate(void);

#pragma mark - XBoolean

extern const XBoolean _Nonnull XBooleanTrue;
extern const XBoolean _Nonnull XBooleanFalse;
extern XBoolean _Nonnull XBooleanCreate(XBool value);
extern XBool XBooleanGetValue(XBoolean _Nonnull ref);

#pragma mark - XNumber

extern const XNumberType XNumberTypeSInt8;
extern const XNumberType XNumberTypeUInt8;

extern const XNumberType XNumberTypeSInt16;
extern const XNumberType XNumberTypeUInt16;

extern const XNumberType XNumberTypeSInt32;
extern const XNumberType XNumberTypeUInt32;
extern const XNumberType XNumberTypeFloat32;

extern const XNumberType XNumberTypeSInt64;
extern const XNumberType XNumberTypeUInt64;
extern const XNumberType XNumberTypeFloat64;

extern XNumber _Nonnull XNumberCreate(XNumberType theType, const void * _Nonnull valuePtr);

extern XComparisonResult XNumberCompare(XNumber _Nonnull lhs, XNumber _Nonnull rhs);

extern XBool XNumberGetValue(XNumber _Nonnull ref, XNumberType theType, void * _Nonnull valuePtr);
extern XNumberType XNumberGetType(XNumber _Nonnull ref);
extern XBool XNumberIsFloatType(XNumber _Nonnull ref);
extern XBool XNumberIsSignedType(XNumber _Nonnull ref);

typedef union {
    XSInt64 s;
    XUInt64 u;
    XFloat64 f;
} XNumberBits64_u;

typedef struct {
    XUInt64 type;
    XNumberBits64_u bits;
} XNumberUnpacked_t;
    
extern void XNumberUnpack(XNumber _Nonnull number, XNumberUnpacked_t * _Nonnull contentPtr);
    
#pragma mark - XString


    
#pragma mark - XData


#pragma mark - XDate

extern const XDate _Nonnull XDateMin;
extern const XDate _Nonnull XDateMax;

//time 是以 2020年1月1日00:00 作为原点的时间
extern XDate _Nonnull XDateCreate(XUInt flag, XTimeInterval time);
extern XComparisonResult XDateCompare(XDate _Nonnull lhs, XDate _Nonnull rhs);
extern XTimeInterval XDateGetValue(XDate _Nonnull ref);

#pragma mark - XValue

//16mb
#define X_BUILD_ValueSizeMax X_BUILD_UInt(0x1000000)
extern const XSize XValueSizeMax;


extern const XValue _Nonnull XValueEmpty;

//通过copy content
extern XValue _Nonnull XValueCreate(XUInt flag, XPtr _Nullable content, XSize contentSize);
extern XSize XValueGetSize(XValue _Nonnull ref);
extern void XValueCopyContent(XValue _Nonnull ref, XPtr _Nonnull buffer, XSize offset, XSize length);

#pragma mark - XPackageRef

//16mb
#define X_BUILD_PackageSizeMax X_BUILD_UInt(0x1000000)

extern const XSize XPackageSizeMax;

typedef void (*XPackageDeinit_f)(XU8Char * _Nonnull typeName, XUInt8 * _Nullable content, XSize size);

typedef struct {
    XU8Char * _Nonnull typeName;
    XSize contentSize;
    void * _Nonnull content;
} XPackageContent_t;

//size 必须 > 0
extern XPackageRef _Nonnull XPackageCreate(XUInt flag, XU8Char * _Nonnull typeName, XSize size, XPackageDeinit_f _Nullable deinit);

extern XSize XPackageGetSize(XPackageRef _Nonnull ref);
extern XPtr _Nonnull XPackageGetContent(XPackageRef _Nonnull ref);

extern void XPackageUnpack(XPackageRef _Nonnull ref, XPackageContent_t * _Nonnull contentPtr);

#pragma mark - XWeakPackageRef

//size 必须 > 0
extern XWeakPackageRef _Nonnull XWeakPackageCreate(XObject _Nonnull object);

extern XObject _Nullable XWeakPackageTakeRetainedValue(XWeakPackageRef _Nonnull ref);


#pragma mark - XArrayRef


#pragma mark - XMapRef


#pragma mark - XSetRef




#pragma mark - XRef


extern XRef _Nonnull XRefRetain(XRef _Nonnull ref);
extern void XRefRelease(XRef _Nonnull ref);


#pragma mark - equalTo

extern XBool XClassEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern XBool XNullEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern XBool XBooleanEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern XBool XNumberEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern XBool XStringEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern XBool XDataEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern XBool XDateEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);
extern XBool XValueEqual(XRef _Nonnull lhs, XRef _Nonnull rhs);

#pragma mark - hash

extern XHashCode XClassHash(XRef _Nonnull ref);
extern XHashCode XNullHash(XRef _Nonnull ref);
extern XHashCode XBooleanHash(XRef _Nonnull ref);
extern XHashCode XNumberHash(XRef _Nonnull ref);
extern XHashCode XStringHash(XRef _Nonnull ref);
extern XHashCode XDataHash(XRef _Nonnull ref);
extern XHashCode XDateHash(XRef _Nonnull ref);
extern XHashCode XValueHash(XRef _Nonnull ref);

#if defined(__cplusplus)

}  // extern C
#endif

#endif /* XRef_h */
