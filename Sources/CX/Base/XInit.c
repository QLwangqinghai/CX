
#include "XBaseType.h"
#include "XRuntimeInternal.h"


#pragma mark - Init

_Static_assert(sizeof(_Atomic(size_fast_t)) == sizeof(size_t), "error");
_Static_assert(sizeof(_Atomic(ssize_fast_t)) == sizeof(ssize_t), "error");

_Static_assert(sizeof(_Atomic(uint32_fast_t)) == sizeof(uint32_t), "error");
_Static_assert(sizeof(_Atomic(uint64_fast_t)) == sizeof(uint64_t), "error");

extern void __XThreadMainInit(void);

static size_t __XInited = 0;

__attribute__((constructor(101)))
static void __CXInit(void) {
    if (__XInited == 0) {
        __XInited = 1;
        assert(UINT_FAST32_MAX == UINT32_MAX);
        assert(UINT_FAST64_MAX == UINT64_MAX);
        assert(sizeof(_Atomic(size_fast_t)) == sizeof(size_t));
        assert(UINT_FAST64_MAX == UINT64_MAX);

        assert(sizeof(uintptr_t) == sizeof(size_t));
        assert(sizeof(size_t) == sizeof(size_t));
        xdispatch_time_now();
        __XThreadMainInit();
        __XRuntimeInit();
        
        __XInited = 2;
    }
}
