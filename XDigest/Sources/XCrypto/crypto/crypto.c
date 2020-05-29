/* Copyright (c) 2014, Google Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

#include "XCrypto.h"

#include "XCrypto_cpu.h"

#include "internal.h"

#if !defined(OPENSSL_NO_ASM) && !defined(OPENSSL_STATIC_ARMCAP) && \
    (defined(OPENSSL_X86) || defined(XCRYPTO_X86_64) || \
     defined(XCRYPTO_ARM) || defined(OPENSSL_AARCH64) || \
     defined(XCRYPTO_PPC64LE))
// x86, x86_64, the ARMs and ppc64le need to record the result of a
// cpuid/getauxval call for the asm to work correctly, unless compiled without
// asm code.
#define NEED_CPUID

#else

// Otherwise, don't emit a static initialiser.

#if !defined(BORINGSSL_NO_STATIC_INITIALIZER)
#define BORINGSSL_NO_STATIC_INITIALIZER
#endif

#endif  // !NO_ASM && !STATIC_ARMCAP &&
        // (X86 || X86_64 || ARM || AARCH64 || PPC64LE)


// Our assembly does not use the GOT to reference symbols, which means
// references to visible symbols will often require a TEXTREL. This is
// undesirable, so all assembly-referenced symbols should be hidden. CPU
// capabilities are the only such symbols defined in C. Explicitly hide them,
// rather than rely on being built with -fvisibility=hidden.
#if defined(XCRYPTO_WINDOWS)
#define HIDDEN
#else
#define HIDDEN __attribute__((visibility("hidden")))
#endif


// The capability variables are defined in this file in order to work around a
// linker bug. When linking with a .a, if no symbols in a .o are referenced
// then the .o is discarded, even if it has constructor functions.
//
// This still means that any binaries that don't include some functionality
// that tests the capability values will still skip the constructor but, so
// far, the init constructor function only sets the capability variables.

#if defined(BORINGSSL_DISPATCH_TEST)
// This value must be explicitly initialised to zero in order to work around a
// bug in libtool or the linker on OS X.
//
// If not initialised then it becomes a "common symbol". When put into an
// archive, linking on OS X will fail to resolve common symbols. By
// initialising it to zero, it becomes a "data symbol", which isn't so
// affected.
HIDDEN uint8_t BORINGSSL_function_hit[7] = {0};
#endif

#if defined(OPENSSL_X86) || defined(XCRYPTO_X86_64)

// This value must be explicitly initialized to zero. See similar comment above.
HIDDEN uint32_t OPENSSL_ia32cap_P[4] = {0};

#elif defined(XCRYPTO_PPC64LE)

HIDDEN unsigned long XCRYPTO_PPC64LE_hwcap2 = 0;

#elif defined(XCRYPTO_ARM) || defined(OPENSSL_AARCH64)

#include "XCrypto_arm_arch.h"

#if defined(OPENSSL_STATIC_ARMCAP)

HIDDEN uint32_t XCRYPTO_ARMcap_P =
#if defined(OPENSSL_STATIC_ARMCAP_NEON) || \
    (defined(__ARM_NEON__) || defined(__ARM_NEON))
    ARMV7_NEON |
#endif
#if defined(OPENSSL_STATIC_ARMCAP_AES) || defined(__ARM_FEATURE_CRYPTO)
    ARMV8_AES |
#endif
#if defined(OPENSSL_STATIC_ARMCAP_SHA1) || defined(__ARM_FEATURE_CRYPTO)
    ARMV8_SHA1 |
#endif
#if defined(OPENSSL_STATIC_ARMCAP_SHA256) || defined(__ARM_FEATURE_CRYPTO)
    ARMV8_SHA256 |
#endif
#if defined(OPENSSL_STATIC_ARMCAP_PMULL) || defined(__ARM_FEATURE_CRYPTO)
    ARMV8_PMULL |
#endif
    0;

#else
HIDDEN uint32_t XCRYPTO_ARMcap_P = 0;

uint32_t *OPENSSL_get_armcap_pointer_for_test(void) {
  return &XCRYPTO_ARMcap_P;
}
#endif


#endif

#if defined(NEED_CPUID)

__attribute__((constructor)) void do_library_init(void) {
 // WARNING: this function may only configure the capability variables. See the
 // note above about the linker bug.
#if defined(NEED_CPUID)
  OPENSSL_cpuid_setup();
#endif
}

#endif

