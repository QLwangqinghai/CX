
#ifndef XHash_h
#define XHash_h


#if defined(__cplusplus)
extern "C" {
#endif

#include "XCoreBase.h"

extern size_t XPointerToUInt(void * _Nullable ptr);
extern uintptr_t XPointerToUIntptr(void * _Nullable ptr);

extern uint32_t _XELFHashBytes(uint8_t * _Nullable bytes, uint32_t length);

static inline XHashCode XAddressReduceHash(XPtr _Nonnull obj) {
#if CX_TARGET_RT_64_BIT
    return (XHashCode)(((uintptr_t)obj) >> 3);
#else
    return (XHashCode)(((uintptr_t)obj) >> 2);
#endif
};

extern uint32_t XMurmurHash32(const XPtr _Nullable key, uint32_t len, uint32_t seed);

// 64-bit hash for 64-bit platforms
extern uint64_t XMurmurHash64(const XPtr _Nullable key, size_t len, uint32_t seed);

extern XHashByte16_t XMurmur3Hash128(const XPtr _Nullable key, uint64_t len, uint32_t seed);


typedef struct {
    uint64_t v[4];
} XSipHashState;

typedef struct {
    XSipHashState state;
    uint64_t length;
    union {
      uint8_t bytes[8];
      uint64_t word;
    } pendingBlock;
} XSipHashContext;

extern void XSipHashStateInit(XSipHashState * _Nonnull state, uint64_t key[_Nonnull 2]);

extern uint64_t XSipHash(const XSipHashState * _Nonnull state, const uint8_t * _Nonnull bytes, uint64_t length);


extern void XSipHashInit(XSipHashContext * _Nonnull context, uint64_t key[_Nonnull 2]);
extern void XSipHashInitWithState(XSipHashContext * _Nonnull context, const XSipHashState * _Nonnull state);

extern void XSipHashCompress(XSipHashContext * _Nonnull context, const uint8_t * _Nonnull bytes, uint64_t length);
extern uint64_t XSipHashFinalize(XSipHashContext * _Nonnull context);


extern XHashByte16_t XNumberHashFloat32(float32_t value);
extern XHashByte16_t XNumberHashFloat64(float64_t value);

extern XHashByte16_t XNumberHashSInt64(int64_t v);
extern XHashByte16_t XNumberHashUInt64(uint64_t value);

extern XHashByte16_t XNumberHashSInt32(int32_t v);
extern XHashByte16_t XNumberHashUInt32(uint32_t value);


extern size_t __XHashSInt(ssize_t i);

extern size_t __XHashDouble(const double d);


#pragma mark - Hasher

typedef void (*XHasherCombineBytes_f)(XHasher _Nonnull hasher, const uint8_t * _Nullable buffer, size_t size);
typedef XHashCode (*XHasherFinalize_f)(XHasher _Nonnull hasher);

typedef struct __XSipHasher {
    XHasherCombineBytes_f _Nonnull combine;
    XHasherFinalize_f _Nonnull finalize;
    XSipHashContext context;
} XSipHasher;

extern void XSipHasherInit(XSipHasher * _Nonnull hasher, uint64_t key0, uint64_t key1);
extern void XSipHasherCombine(XHasher _Nonnull hasher, const uint8_t * _Nullable buffer, size_t size);
extern XHashCode XSipHasherFinalize(XHasher _Nonnull hasher);


#if defined(__cplusplus)
}  // extern C
#endif


#endif /* XHash_h */
