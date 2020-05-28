//
//  main.c
//  XDigest
//
//  Created by clf on 2020/5/28.
//  Copyright © 2020 clf. All rights reserved.
//

#include <stdio.h>
#include "XCrypto.h"

#include "CNIOBoringSSL_crypto.h"

#include "CNIOBoringSSL_cpu.h"

#include "internal.h"




int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    #if !defined(OPENSSL_NO_ASM)
    
        printf("OPENSSL_NO_ASM!\n");

    #endif
    
    #if !defined(OPENSSL_STATIC_ARMCAP)
    
        printf("!OPENSSL_STATIC_ARMCAP!\n");

    #endif
    
    #if defined(OPENSSL_X86)
    
        printf("OPENSSL_X86!\n");

    #endif
    
    #if defined(XCRYPTO_X86_64)
    
        printf("XCRYPTO_X86_64!\n");

    #endif
    
    
    #if defined(XCRYPTO_ARM)
    
        printf("XCRYPTO_ARM!\n");

    #endif
    
    #if defined(OPENSSL_AARCH64)
    
        printf("OPENSSL_AARCH64!\n");

    #endif
    
    #if defined(XCRYPTO_PPC64LE)
    
        printf("XCRYPTO_PPC64LE!\n");

    #endif
    OPENSSL_cpuid_setup();

    #if !defined(OPENSSL_NO_ASM) && !defined(OPENSSL_STATIC_ARMCAP) && \
        (defined(OPENSSL_X86) || defined(XCRYPTO_X86_64) || \
         defined(XCRYPTO_ARM) || defined(OPENSSL_AARCH64) || \
         defined(XCRYPTO_PPC64LE))
    // x86, x86_64, the ARMs and ppc64le need to record the result of a
    // cpuid/getauxval call for the asm to work correctly, unless compiled without
    // asm code.

    printf("NEED_CPUID!\n");

    #else

    // Otherwise, don't emit a static initialiser.
        printf("!!NEED_CPUID!\n");
    #endif
    
    return 0;
}
