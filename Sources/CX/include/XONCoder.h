

#ifndef XONCoder_h
#define XONCoder_h

#include "XCoreBase.h"
#include "XONCore.h"

/// object
extern XDataRef _Nullable XONEncode(XObjectRef _Nullable object, XONError_e * _Nullable error);
extern XObjectRef _Nullable XONDecodeBufferRead(XDecodeBuffer_s * _Nonnull buffer);
extern XObjectRef _Nullable XONDecodeWithData(XDataRef _Nonnull data, XONError_e * _Nullable error);
extern XObjectRef _Nullable XONDecode(const void * _Nonnull bytes, ssize_t length, XONError_e * _Nullable error);

//extern XObjectRef _Nullable XONDecodeBufferRead(XDecodeBuffer_s * _Nonnull buffer);



#endif /* XONCoder_h */
