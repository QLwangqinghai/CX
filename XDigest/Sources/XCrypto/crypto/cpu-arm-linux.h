/* Copyright (c) 2018, Google Inc.
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

#ifndef OPENSSL_HEADER_CRYPTO_CPU_ARM_LINUX_H
#define OPENSSL_HEADER_CRYPTO_CPU_ARM_LINUX_H

#include "XCryptoBase.h"

#include <string.h>

#include "internal.h"

#if defined(__cplusplus)
extern "C" {
#endif


// The cpuinfo parser lives in a header file so it may be accessible from
// cross-platform fuzzers without adding code to those platforms normally.

#define HWCAP_NEON (1 << 12)

// See /usr/include/asm/hwcap.h on an ARM installation for the source of
// these values.
#define HWCAP2_AES (1 << 0)
#define HWCAP2_PMULL (1 << 1)
#define HWCAP2_SHA1 (1 << 2)
#define HWCAP2_SHA2 (1 << 3)

}
#if defined(__cplusplus)
}  // extern C
#endif

#endif  // OPENSSL_HEADER_CRYPTO_CPU_ARM_LINUX_H
