/* ====================================================================
 * Copyright (c) 1998-2001 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com). */

#ifndef OPENSSL_HEADER_BASE_H
#define OPENSSL_HEADER_BASE_H
#if defined(__APPLE__) && defined(__i386__)
#define XCRYPTO_NO_ASM
#endif

#define XCRYPTO_PREFIX XCrypto


// This file should be the first included by all BoringSSL headers.

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include "CXTargetConditionals.h"

#if defined(__MINGW32__)
// stdio.h is needed on MinGW for __MINGW_PRINTF_FORMAT.
#include <stdio.h>
#endif

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

// Include a BoringSSL-only header so consumers including this header without
// setting up include paths do not accidentally pick up the system
// opensslconf.h.

#if defined(XCRYPTO_PREFIX)
#include "XCrypto_prefix_symbols.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__GNUC__) && __GNUC__ >= 2
static inline uint16_t CRYPTO_bswap2(uint16_t x) {
  return __builtin_bswap16(x);
}

static inline uint32_t CRYPTO_bswap4(uint32_t x) {
  return __builtin_bswap32(x);
}

static inline uint64_t CRYPTO_bswap8(uint64_t x) {
  return __builtin_bswap64(x);
}
#elif defined(_MSC_VER)
OPENSSL_MSVC_PRAGMA(warning(push, 3))
#include <stdlib.h>
OPENSSL_MSVC_PRAGMA(warning(pop))
#pragma intrinsic(_byteswap_uint64, _byteswap_ulong, _byteswap_ushort)
static inline uint16_t CRYPTO_bswap2(uint16_t x) {
  return _byteswap_ushort(x);
}

static inline uint32_t CRYPTO_bswap4(uint32_t x) {
  return _byteswap_ulong(x);
}

static inline uint64_t CRYPTO_bswap8(uint64_t x) {
  return _byteswap_uint64(x);
}
#else
static inline uint16_t CRYPTO_bswap2(uint16_t x) {
  return (x >> 8) | (x << 8);
}

static inline uint32_t CRYPTO_bswap4(uint32_t x) {
  x = (x >> 16) | (x << 16);
  x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
  return x;
}

static inline uint64_t CRYPTO_bswap8(uint64_t x) {
  return CRYPTO_bswap4(x >> 32) | (((uint64_t)CRYPTO_bswap4(x)) << 32);
}
#endif


#if defined(__APPLE__)
#define XCRYPTO_APPLE
// Note |TARGET_OS_MAC| is set for all Apple OS variants. |TARGET_OS_OSX|
// targets macOS specifically.
#if defined(TARGET_OS_OSX) && TARGET_OS_OSX
#define XCRYPTO_MACOS
#endif
#if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE
#define XCRYPTO_IOS
#endif
#endif

#if defined(_WIN32)
#define XCRYPTO_WINDOWS
#endif

#if defined(__linux__)
#define XCRYPTO_LINUX
#endif

#if defined(__Fuchsia__)
#define XCRYPTO_FUCHSIA
#endif

#if defined(TRUSTY)
#define XCRYPTO_TRUSTY
#endif

#if defined(__ANDROID_API__)
#define XCRYPTO_ANDROID
#endif

#include <assert.h>
#include <string.h>

#define OPENSSL_memcpy memcpy
#define OPENSSL_memset memset

static inline void OPENSSL_cleanse(void *ptr, size_t len) {
    bzero(ptr, len);
}


// BORINGSSL_API_VERSION is a positive integer that increments as BoringSSL
// changes over time. The value itself is not meaningful. It will be incremented
// whenever is convenient to coordinate an API change with consumers. This will
// not denote any special point in development.
//
// A consumer may use this symbol in the preprocessor to temporarily build
// against multiple revisions of BoringSSL at the same time. It is not
// recommended to do so for longer than is necessary.
#define BORINGSSL_API_VERSION 10

#if defined(BORINGSSL_SHARED_LIBRARY)

#if defined(XCRYPTO_WINDOWS)

#if defined(BORINGSSL_IMPLEMENTATION)
#define OPENSSL_EXPORT __declspec(dllexport)
#else
#define OPENSSL_EXPORT __declspec(dllimport)
#endif

#else  // defined(XCRYPTO_WINDOWS)

#if defined(BORINGSSL_IMPLEMENTATION)
#define OPENSSL_EXPORT __attribute__((visibility("default")))
#else
#define OPENSSL_EXPORT
#endif

#endif  // defined(XCRYPTO_WINDOWS)

#else  // defined(BORINGSSL_SHARED_LIBRARY)

#define OPENSSL_EXPORT

#endif  // defined(BORINGSSL_SHARED_LIBRARY)


#if defined(__GNUC__) || defined(__clang__)
// MinGW has two different printf implementations. Ensure the format macro
// matches the selected implementation. See
// https://sourceforge.net/p/mingw-w64/wiki2/gnu%20printf/.
#if defined(__MINGW_PRINTF_FORMAT)
#define OPENSSL_PRINTF_FORMAT_FUNC(string_index, first_to_check) \
  __attribute__(                                                 \
      (__format__(__MINGW_PRINTF_FORMAT, string_index, first_to_check)))
#else
#define OPENSSL_PRINTF_FORMAT_FUNC(string_index, first_to_check) \
  __attribute__((__format__(__printf__, string_index, first_to_check)))
#endif
#else
#define OPENSSL_PRINTF_FORMAT_FUNC(string_index, first_to_check)
#endif

// OPENSSL_MSVC_PRAGMA emits a pragma on MSVC and nothing on other compilers.
#if defined(_MSC_VER)
#define OPENSSL_MSVC_PRAGMA(arg) __pragma(arg)
#else
#define OPENSSL_MSVC_PRAGMA(arg)
#endif

#if defined(__GNUC__) || defined(__clang__)
#define OPENSSL_UNUSED __attribute__((unused))
#else
#define OPENSSL_UNUSED
#endif

// C and C++ handle inline functions differently. In C++, an inline function is
// defined in just the header file, potentially emitted in multiple compilation
// units (in cases the compiler did not inline), but each copy must be identical
// to satsify ODR. In C, a non-static inline must be manually emitted in exactly
// one compilation unit with a separate extern inline declaration.
//
// In both languages, exported inline functions referencing file-local symbols
// are problematic. C forbids this altogether (though GCC and Clang seem not to
// enforce it). It works in C++, but ODR requires the definitions be identical,
// including all names in the definitions resolving to the "same entity". In
// practice, this is unlikely to be a problem, but an inline function that
// returns a pointer to a file-local symbol
// could compile oddly.
//
// Historically, we used static inline in headers. However, to satisfy ODR, use
// plain inline in C++, to allow inline consumer functions to call our header
// functions. Plain inline would also work better with C99 inline, but that is
// not used much in practice, extern inline is tedious, and there are conflicts
// with the old gnu89 model:
// https://stackoverflow.com/questions/216510/extern-inline
#if defined(__cplusplus)
#define OPENSSL_INLINE inline
#else
// Add OPENSSL_UNUSED so that, should an inline function be emitted via macro
// (e.g. a |STACK_OF(T)| implementation) in a source file without tripping
// clang's -Wunused-function.
#define OPENSSL_INLINE static inline OPENSSL_UNUSED
#endif

#if defined(BORINGSSL_UNSAFE_FUZZER_MODE) && \
    !defined(BORINGSSL_UNSAFE_DETERMINISTIC_MODE)
#define BORINGSSL_UNSAFE_DETERMINISTIC_MODE
#endif

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define OPENSSL_ASAN
#endif
#if __has_feature(thread_sanitizer)
#define OPENSSL_TSAN
#endif
#if __has_feature(memory_sanitizer)
#define OPENSSL_MSAN
#define OPENSSL_ASM_INCOMPATIBLE
#endif
#endif

#if defined(OPENSSL_ASM_INCOMPATIBLE)
#undef OPENSSL_ASM_INCOMPATIBLE
#if !defined(XCRYPTO_NO_ASM)
#define XCRYPTO_NO_ASM
#endif
#endif  // OPENSSL_ASM_INCOMPATIBLE

#if defined(__cplusplus)
// enums can be predeclared, but only in C++ and only if given an explicit type.
// C doesn't support setting an explicit type for enums thus a #define is used
// to do this only for C++. However, the ABI type between C and C++ need to have
// equal sizes, which is confirmed in a unittest.
#define BORINGSSL_ENUM_INT : int
enum ssl_early_data_reason_t BORINGSSL_ENUM_INT;
enum ssl_encryption_level_t BORINGSSL_ENUM_INT;
enum ssl_private_key_result_t BORINGSSL_ENUM_INT;
enum ssl_renegotiate_mode_t BORINGSSL_ENUM_INT;
enum ssl_select_cert_result_t BORINGSSL_ENUM_INT;
enum ssl_select_cert_result_t BORINGSSL_ENUM_INT;
enum ssl_ticket_aead_result_t BORINGSSL_ENUM_INT;
enum ssl_verify_result_t BORINGSSL_ENUM_INT;
#else
#define BORINGSSL_ENUM_INT
#endif

// CRYPTO_THREADID is a dummy value.
typedef int CRYPTO_THREADID;

typedef int ASN1_BOOLEAN;
typedef int ASN1_NULL;
typedef struct ASN1_ITEM_st ASN1_ITEM;
typedef struct asn1_object_st ASN1_OBJECT;
typedef struct asn1_pctx_st ASN1_PCTX;
typedef struct asn1_string_st ASN1_BIT_STRING;
typedef struct asn1_string_st ASN1_BMPSTRING;
typedef struct asn1_string_st ASN1_ENUMERATED;
typedef struct asn1_string_st ASN1_GENERALIZEDTIME;
typedef struct asn1_string_st ASN1_GENERALSTRING;
typedef struct asn1_string_st ASN1_IA5STRING;
typedef struct asn1_string_st ASN1_INTEGER;
typedef struct asn1_string_st ASN1_OCTET_STRING;
typedef struct asn1_string_st ASN1_PRINTABLESTRING;
typedef struct asn1_string_st ASN1_STRING;
typedef struct asn1_string_st ASN1_T61STRING;
typedef struct asn1_string_st ASN1_TIME;
typedef struct asn1_string_st ASN1_UNIVERSALSTRING;
typedef struct asn1_string_st ASN1_UTCTIME;
typedef struct asn1_string_st ASN1_UTF8STRING;
typedef struct asn1_string_st ASN1_VISIBLESTRING;
typedef struct asn1_type_st ASN1_TYPE;
typedef struct AUTHORITY_KEYID_st AUTHORITY_KEYID;
typedef struct BASIC_CONSTRAINTS_st BASIC_CONSTRAINTS;
typedef struct DIST_POINT_st DIST_POINT;
typedef struct DSA_SIG_st DSA_SIG;
typedef struct ISSUING_DIST_POINT_st ISSUING_DIST_POINT;
typedef struct NAME_CONSTRAINTS_st NAME_CONSTRAINTS;
typedef struct Netscape_spkac_st NETSCAPE_SPKAC;
typedef struct Netscape_spki_st NETSCAPE_SPKI;
typedef struct RIPEMD160state_st RIPEMD160_CTX;
typedef struct bignum_ctx BN_CTX;
typedef struct bignum_st BIGNUM;
typedef struct bio_method_st BIO_METHOD;
typedef struct bio_st BIO;
typedef struct bn_gencb_st BN_GENCB;
typedef struct bn_mont_ctx_st BN_MONT_CTX;
typedef struct buf_mem_st BUF_MEM;
typedef struct cbb_st CBB;
typedef struct cbs_st CBS;
typedef struct cmac_ctx_st CMAC_CTX;
typedef struct conf_st CONF;
typedef struct conf_value_st CONF_VALUE;
typedef struct crypto_buffer_pool_st CRYPTO_BUFFER_POOL;
typedef struct crypto_buffer_st CRYPTO_BUFFER;
typedef struct dh_st DH;
typedef struct dsa_st DSA;
typedef struct ec_group_st EC_GROUP;
typedef struct ec_key_st EC_KEY;
typedef struct ec_point_st EC_POINT;
typedef struct ecdsa_method_st ECDSA_METHOD;
typedef struct ecdsa_sig_st ECDSA_SIG;
typedef struct engine_st ENGINE;
typedef struct env_md_ctx_st EVP_MD_CTX;
typedef struct env_md_st EVP_MD;
typedef struct evp_aead_st EVP_AEAD;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;
typedef struct evp_cipher_st EVP_CIPHER;
typedef struct evp_encode_ctx_st EVP_ENCODE_CTX;
typedef struct evp_pkey_asn1_method_st EVP_PKEY_ASN1_METHOD;
typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;
typedef struct evp_pkey_method_st EVP_PKEY_METHOD;
typedef struct evp_pkey_st EVP_PKEY;
typedef struct hmac_ctx_st HMAC_CTX;
typedef struct md5_state_st MD5_CTX;
typedef struct ossl_init_settings_st OPENSSL_INIT_SETTINGS;
typedef struct private_key_st X509_PKEY;
typedef struct rand_meth_st RAND_METHOD;
typedef struct rsa_meth_st RSA_METHOD;
typedef struct rsa_st RSA;
typedef struct sha256_state_st SHA256_CTX;
typedef struct sha512_state_st SHA512_CTX;
typedef struct sha_state_st SHA_CTX;
typedef struct spake2_ctx_st SPAKE2_CTX;
typedef struct srtp_protection_profile_st SRTP_PROTECTION_PROFILE;

typedef void *OPENSSL_BLOCK;

#if defined(__cplusplus) || (defined(_MSC_VER) && !defined(__clang__))
// In C++ and non-clang MSVC, |static_assert| is a keyword.
#define OPENSSL_STATIC_ASSERT(cond, msg) static_assert(cond, msg)
#else
// C11 defines the |_Static_assert| keyword and the |static_assert| macro in
// assert.h. While the former is available at all versions in Clang and GCC, the
// later depends on libc and, in glibc, depends on being built in C11 mode. We
// do not require this, for now, so use |_Static_assert| directly.
#define OPENSSL_STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#endif



#if defined(__cplusplus)
}  // extern C
#elif !defined(BORINGSSL_NO_CXX)
#define BORINGSSL_NO_CXX
#endif

#if defined(XCRYPTO_PREFIX)
#define BSSL_NAMESPACE_BEGIN \
  namespace bssl {           \
  inline namespace XCRYPTO_PREFIX {
#define BSSL_NAMESPACE_END \
  }                        \
  }
#else
#define BSSL_NAMESPACE_BEGIN namespace bssl {
#define BSSL_NAMESPACE_END }
#endif

// MSVC doesn't set __cplusplus to 201103 to indicate C++11 support (see
// https://connect.microsoft.com/VisualStudio/feedback/details/763051/a-value-of-predefined-macro-cplusplus-is-still-199711l)
// so MSVC is just assumed to support C++11.
#if !defined(BORINGSSL_NO_CXX) && __cplusplus < 201103L && !defined(_MSC_VER)
#define BORINGSSL_NO_CXX
#endif


#endif  // OPENSSL_HEADER_BASE_H
