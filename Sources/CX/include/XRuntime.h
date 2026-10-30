
#ifndef XRuntime_h
#define XRuntime_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XObject.h"

#pragma mark - XHasher

extern void XHasherCombineByte16(XHasher _Nonnull hasher, const XByte16 * _Nonnull v);
extern void XHasherCombineAddress(XHasher _Nonnull hasher, XPtr _Nullable v);
extern void XHasherCombineUInt32(XHasher _Nonnull hasher, uint32_t v);

extern void XHasherCombineBytes(XHasher _Nonnull hasher, uint8_t * _Nullable buffer, size_t size);
extern XHashCode XHasherFinalize(XHasher _Nonnull hasher);

extern XHashCode XHash(uint8_t * _Nullable bytes, size_t length);

#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XRuntime_h */
