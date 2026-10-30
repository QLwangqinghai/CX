
#include "XCore.h"
#include <sys/time.h>

microsecond_t XMicrosecondNow(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    XAssert(tv.tv_sec < INT64_MAX / 1000000, "out of range");
    microsecond_t ret = (microsecond_t)(tv.tv_sec) * 1000000;
    ret += tv.tv_usec;
    return ret;
}

microsecond_t XMicrosecondGetInvalid(void) {
    return MICROSECOND_INVALID;
}
microsecond_t XMicrosecondGetDistantFuture(void) {
    return MICROSECOND_DISTANT_FUTURE;
}
microsecond_t XMicrosecondGetDistantPast(void) {
    return MICROSECOND_DISTANT_PAST;
}
microsecond_t XMicrosecondFromTimespec(struct timespec time) {
    microsecond_t result = 0;
    result += time.tv_sec * 1000000;
    result += time.tv_nsec * 1000;
    return result;
}
microsecond_t XMicrosecondFromTimeval(struct timeval time) {
    microsecond_t result = 0;
    result += time.tv_sec * 1000000;
    result += time.tv_usec;
    return result;
}

struct timespec XMicrosecondToTimespec(microsecond_t time) {
    struct timespec result = {};
    result.tv_sec = time / 1000000;
    result.tv_nsec = (time - result.tv_sec * 1000000) * 1000;
    return result;
}

struct timeval XMicrosecondToTimeval(microsecond_t time) {
    struct timeval result = {};
    result.tv_sec = time / 1000000;
    result.tv_usec = (int)(time - result.tv_sec * 1000000);
    return result;
}

microsecond_t XMicrosecondWithSecond(double sec) {
    static int64_t iscale = INT64_C(1000000);
    static double dscale = 1000000.0;
    static double min = (double)(INT64_MIN / INT64_C(1000000) - 1);
    static double max = (double)(INT64_MAX / INT64_C(1000000) + 1);

    if (isnan(sec)) {
        return 0;
    } else if (isinf(sec)) {
        if (signbit(sec) == 0) {
            return INT64_MAX;
        } else {
            return INT64_MIN;
        }
    } else {
        if (sec <= min) {
            return INT64_MIN;
        } else if (sec >= max) {
            return INT64_MAX;
        } else {
            microsecond_t st = (microsecond_t)sec;
            double sl = (sec - (double)st) * dscale;
            microsecond_t h = st * iscale;
            
            if (sl > 0) {
                sl += 0.5;
            } else if (sl < 0) {
                sl -= 0.5;
            }
            microsecond_t l = (microsecond_t)sl;
            if (st == INT64_MIN / iscale) {
                // 最小值
                if (l <= INT64_MIN % iscale) {
                    return INT64_MIN;
                } else {
                    return h + l;
                }
            } else if (st == INT64_MAX / iscale) {
                // 最大值
                if (l >= INT64_MAX % iscale) {
                    return INT64_MAX;
                } else {
                    return h + l;
                }
            } else {
                return h + l;
            }
        }
    }
}

double XMicrosecondGetSecond(microsecond_t ti) {
    static int64_t iscale = INT64_C(1000000);
    static double dscale = 1000000.0;
    double h = ti / iscale;
    double l = ((double)(ti % iscale)) / dscale;
    return h + l;
}


#if CX_TARGET_OS_DARWIN

#include <stdlib.h>
#include <mach/mach_time.h>
#include <sys/time.h>
#include <sys/times.h>

static uint64_t _xdispatch_time_base = 0;
static long double _xtimebase_info = 0;

void _xdispatch_time_base_init(void) {
    struct mach_timebase_info info;
    assert(0 == mach_timebase_info(&info));
    _xtimebase_info = (long double)info.numer / (long double)info.denom;
    uint64_t t = mach_continuous_time();
    assert(0 != t);
    _xdispatch_time_base = t - 1;
}

xdispatch_time_t xdispatch_time_now(void) {
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, _xdispatch_time_base_init);
    uint64_t t = mach_continuous_time() - _xdispatch_time_base;
    long double tmp = ((long double)t * _xtimebase_info) + .5L;
    if (XUnlikely(tmp >= INT64_MAX)) {
        return INT64_MAX;
    }
    return (uint64_t)tmp;
}

#elif CX_TARGET_OS_LINUX || CX_TARGET_OS_BSD || CX_TARGET_OS_ANDROID

#include <string.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdlib.h>

/*
 
 CLOCK_MONOTONIC：为单调时间。以绝对时间为准，获取的时间为系统重启到现在的时间，更改系统时间对它没有影响。用户不能修改这个时间，但是当系统进入休眠（suspend）时，CLOCK_MONOTONIC会停止增加。
 CLOCK_MONOTONIC_RAW：和CLOCK_MONOTONIC类似，但不同之处是MONOTONIC_RAW不会受到NTP的影响。CLOCK_MONOTONIC会受到NTP的影响并不是说NTP会去修改CLOCK_MONOTONIC，使其不连续。当NTP server 和本地的时钟硬件之间有问题时，NTP会影响到CLOCK_MONOTONIC的频率，但是CLOCK_MONOTONIC_RAW则不会受其影响。 其区别可以参考 Difference between MONOTONIC and MONOTONIC_RAW
 
 CLOCK_MONOTONIC、CLOCK_MONOTONIC_RAW 不包含系统休眠期间的时间
 CLOCK_BOOTTIME、CLOCK_REALTIME 包含系统休眠期间的时间
 */

static int64_t _xdispatch_time_base_sec = 0;

//clock_gettime_nsec_np(CLOCK_UPTIME_RAW);

void _xdispatch_time_base_init(void) {
    struct timespec ts;
    assert(0 == clock_gettime(CLOCK_BOOTTIME, &ts));
    _xdispatch_time_base_sec = ts.tv_sec;
}

xdispatch_time_t xdispatch_time_now(void) {
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, _xdispatch_time_base_init);
    
    struct timespec ts;
    assert(0 == clock_gettime(CLOCK_BOOTTIME, &ts));
    return (ts.tv_sec - _xdispatch_time_base_sec) * 10000000 + ts.tv_nsec;
}
#elif CX_TARGET_OS_WINDOWS
static ULONGLONG _xdispatch_time_base_ms = 0;

//clock_gettime_nsec_np(CLOCK_UPTIME_RAW);

void _xdispatch_time_base_init(void) {
    _xdispatch_time_base_ms = GetTickCount64();
}

xdispatch_time_t xdispatch_time_now(void) {
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, _xdispatch_time_base_init);
    
    ULONGLONG ullTickCount = GetTickCount64() - _xdispatch_time_base_ms;
    assert(ullTickCount < INT64_MAX / 1000000);
    return ullTickCount * 1000000;
}
#else
#error Unable XDeviceUptime for this platform
#endif



#if CX_TARGET_OS_DARWIN

#include <mach-o/dyld.h>
int XProcessExecutablePath(char * _Nonnull buf, uint32_t * _Nonnull bufsize) {
    return _NSGetExecutablePath(buf, bufsize);
}

#elif CX_TARGET_OS_LINUX

#include <unistd.h>
int XProcessExecutablePath(char* buf, uint32_t * bufsize) {
    if (NULL == buf || NULL == bufsize) {
        return -1;
    }
    ssize_t ret = readlink("/proc/self/exe", path, (size_t)(*bufsize));
    if (ret <= 0) {
        return -1;
    } else {
        *bufsize = (uint32_t)ret;
    }
}
#else
#error Unable XProcessExecutablePath for this platform
#endif

#pragma mark - thread

XThread_t XThreadInvalid(void) {
    XThread_t result = {};
    return result;
}
XThread_t XThreadMake(pthread_t pt) {
    XThread_t result = {
        .id = pt,
    };
    return result;
}
XThread_t XThreadCurrent(void) {
    XThread_t result = {
        .id = pthread_self(),
    };
    return result;
}

bool_t XThreadIsEqual(XThread_t lhs, XThread_t rhs) {
    return pthread_equal(lhs.id, rhs.id) != 0;
}

bool_t XThreadIsCurrent(XThread_t t) {
    return pthread_equal(t.id, pthread_self()) != 0;
}

bool_t XThreadIsInvalid(XThread_t t) {
    XThread_t r = {};
    return pthread_equal(t.id, r.id) != 0;
}

XThread_t XThreadCreate(double priority, size_t minStacksize, void * _Nullable (* _Nonnull func)(void * _Nullable), void * _Nullable context) {
    pthread_t tid;
    pthread_attr_t attr;
    struct sched_param param;
    //初始化线程属性
    int policy;
    int result = 0;

    result = pthread_attr_init(&attr);
    XAssertError(0 == result, "pthread_attr_init");
    result = pthread_getschedparam(pthread_self(), &policy, &param);
    XAssertError(0 == result, "pthread_getschedparam");
    result = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    XAssertError(0 == result, "pthread_attr_setscope");
    result = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    XAssertError(0 == result, "pthread_attr_setdetachstate");
    size_t stacksize = 0;
    result = pthread_attr_getstacksize(&attr, &stacksize);
    XAssertError(0 == result, "pthread_attr_getstacksize");
    if (stacksize < minStacksize) {
        result = pthread_attr_setstacksize(&attr, minStacksize);//设置线程堆栈大小
        XAssertError(0 == result, "pthread_attr_setstacksize");
    }
    int maxPriority = sched_get_priority_max(policy);
    XAssertError(-1 != maxPriority, "sched_get_priority_max");
    int minPriority = sched_get_priority_min(policy);
    XAssertError(-1 != minPriority, "sched_get_priority_min");
    
    int sched_priority = minPriority + (int)round((double)(maxPriority - minPriority) * priority);
    param.sched_priority = MAX(MIN(sched_priority, maxPriority), minPriority);
    result = pthread_attr_setschedparam(&attr, &param);
    XAssertError(0 == result, "pthread_attr_setschedparam");
    
    result = pthread_create(&tid, &attr, func, context);
    XAssertError(0 == result, "pthread_create");
    return XThreadMake(tid);
}

#pragma mark - Semaphore

void XSemaphoreInit(XSemaphore_s * _Nonnull sem, ssize_t value) {
    XAssert(sem, "");
    sem->value = value;
    pthread_condattr_t cattr;
    XAssert(0 == pthread_mutex_init(&(sem->mutex), NULL), "");
    XAssert(0 == pthread_condattr_init(&cattr), "");
#if __APPLE__
    
#else
    XAssert(0 == pthread_condattr_setclock(&cattr, CLOCK_MONOTONIC), "");
#endif
    XAssert(0 == pthread_cond_init(&(sem->cont), &cattr), "");
}

void XSemaphoreDeinit(XSemaphore_s * _Nonnull sem) {
    XAssert(sem, "");
    pthread_cond_destroy(&(sem->cont));
    pthread_mutex_destroy(&(sem->mutex));
}

XSemaphore_s * _Nonnull XSemaphoreCreate(ssize_t value) {
    XSemaphore_s * sem = (XSemaphore_s *)malloc(sizeof(XSemaphore_s));
    XSemaphoreInit(sem, value);
    return sem;
}

void XSemaphoreDestroy(XSemaphore_s * _Nonnull sem) {
    XSemaphoreDeinit(sem);
    free(sem);
}

void XSemaphoreSignal(XSemaphore_s * _Nonnull sem) {
    XAssert(sem, "");
    pthread_mutex_lock(&(sem->mutex));
    ssize_t old = sem->value;
    sem->value += 1;
    XAssert(sem->value > old, "");
    pthread_mutex_unlock(&(sem->mutex));
    XAssert(0 == pthread_cond_signal(&(sem->cont)), "");
}
void XSemaphoreWait(XSemaphore_s * _Nonnull sem) {
    XAssert(sem, "");
    pthread_mutex_lock(&(sem->mutex));
    while (sem->value <= 0) {
        XAssert(0 == pthread_cond_wait(&(sem->cont), &(sem->mutex)), "");
    }
    sem->value -= 1;
    pthread_mutex_unlock(&(sem->mutex));
}

/// 就绪返回true，否则返回false
typedef bool_t (*XPthreadCondIsReady_f)(void * _Nonnull context);


void _xpthread_cond_timedwait(void * _Nonnull context, XPthreadCondIsReady_f _Nonnull pression, pthread_cond_t * _Nonnull cont, pthread_mutex_t * _Nonnull mutex, xdispatch_time_t timeout) {

    if (!pression(context)) {
        struct timespec now;
        XAssert(0 == clock_gettime(CLOCK_MONOTONIC, &now), "");
        struct timespec endTime = now;
        endTime.tv_nsec += timeout % XNSEC_PER_SEC;
        endTime.tv_sec += endTime.tv_nsec / XNSEC_PER_SEC;
        endTime.tv_nsec = endTime.tv_nsec % XNSEC_PER_SEC;
        endTime.tv_sec += timeout / XNSEC_PER_SEC;
        
        while (!pression(context) && (now.tv_sec < endTime.tv_sec || (now.tv_sec == endTime.tv_sec && now.tv_nsec < endTime.tv_nsec))) {
#if __APPLE__
            struct timespec time = {};
            time.tv_sec = timeout / XNSEC_PER_SEC;
            time.tv_nsec = timeout % XNSEC_PER_SEC;
            int rcode = pthread_cond_timedwait_relative_np(cont, mutex, &time);
            if (rcode != 0) {
                XAssert(rcode == ETIMEDOUT, "");
            }
#else
            int rcode = pthread_cond_timedwait(&(sem->cont), &(sem->mutex), &endTime);
            if (rcode != 0) {
                XAssert(errno == ETIMEDOUT, "");
            }
#endif
            XAssert(0 == clock_gettime(CLOCK_MONOTONIC, &now), "");
        }
    }
}

bool_t _XSemaphoreIsReady(void * sem) {
    XSemaphore_s * s = (XSemaphore_s *)sem;
    return s->value > 0;
}

bool_t XSemaphoreTimedWait(XSemaphore_s * _Nonnull sem, xdispatch_time_t timeout) {
    if (timeout == XDISPATCH_TIME_FOREVER) {
        XSemaphoreWait(sem);
        return true;
    }
    
    XAssert(sem, "");
    pthread_mutex_lock(&(sem->mutex));
    _xpthread_cond_timedwait(sem, _XSemaphoreIsReady, &(sem->cont), &(sem->mutex), timeout);
    if (sem->value <= 0) {
        pthread_mutex_unlock(&(sem->mutex));
        return false;
    } else {
        sem->value -= 1;
        pthread_mutex_unlock(&(sem->mutex));
        return true;
    }
}

#if CX_TARGET_OS_DARWIN

void XSpinlockInit(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    *lock = OS_UNFAIR_LOCK_INIT;
}
void XSpinlockDeinit(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
}
void XSpinlockLock(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    os_unfair_lock_lock(lock);
}
void XSpinlockUnlock(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    os_unfair_lock_unlock(lock);
}
bool_t XSpinlockTrylock(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    return os_unfair_lock_trylock(lock);
}

#endif

#if CX_TARGET_OS_LINUX

void XSpinlockInit(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    XAssert(0 == pthread_spin_init(lock, PTHREAD_PROCESS_PRIVATE), "");
}
void XSpinlockDeinit(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    XAssert(0 == pthread_spin_destroy(lock), "");
}
void XSpinlockLock(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    XAssert(0 == pthread_spin_lock(lock), "");
}
void XSpinlockUnlock(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    XAssert(0 == pthread_spin_unlock(lock), "");
}
bool_t XSpinlockTrylock(XSpinlock_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    return 0 == pthread_spin_unlock(lock);
}

#endif

void XMutexInit(XMutex_t * _Nonnull lock, bool_t isRecursive) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    if (isRecursive) {
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    }
    XAssert(0 == pthread_mutex_init(lock, &attr), "");
}

void XMutexDeinit(XMutex_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    XAssert(0 == pthread_mutex_destroy(lock), "");
}
void XMutexLock(XMutex_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    XAssert(0 == pthread_mutex_lock(lock), "");
}
void XMutexUnlock(XMutex_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    XAssert(0 == pthread_mutex_unlock(lock), "");
}
bool_t XMutexTrylock(XMutex_t * _Nonnull lock) {
    XAssert(NULL != lock, "");
    int code = pthread_mutex_trylock(lock);
    if (0 == code) {
        return true;
    } else {
        return false;
    }
}

#if CX_TARGET_OS_DARWIN

#include <stdlib.h>
#include <mach/mach_time.h>
#include <sys/time.h>
#include <sys/times.h>

struct timespec XDeviceUptime(void) {
    struct timespec ts = {};
    assert(0 == clock_gettime(CLOCK_MONOTONIC, &ts));
    return ts;
}

#elif CX_TARGET_OS_LINUX || CX_TARGET_OS_BSD || CX_TARGET_OS_ANDROID

#include <string.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdlib.h>

/*
 
 CLOCK_MONOTONIC：为单调时间。以绝对时间为准，获取的时间为系统重启到现在的时间，更改系统时间对它没有影响。用户不能修改这个时间，但是当系统进入休眠（suspend）时，CLOCK_MONOTONIC会停止增加。
 CLOCK_MONOTONIC_RAW：和CLOCK_MONOTONIC类似，但不同之处是MONOTONIC_RAW不会受到NTP的影响。CLOCK_MONOTONIC会受到NTP的影响并不是说NTP会去修改CLOCK_MONOTONIC，使其不连续。当NTP server 和本地的时钟硬件之间有问题时，NTP会影响到CLOCK_MONOTONIC的频率，但是CLOCK_MONOTONIC_RAW则不会受其影响。 其区别可以参考 Difference between MONOTONIC and MONOTONIC_RAW
 */

struct timespec XDeviceUptime(void) {
    struct timespec ts;
    assert(0 == clock_gettime(CLOCK_MONOTONIC, &ts));
    return ts;
}
#elif CX_TARGET_OS_WINDOWS
struct timespec XDeviceUptime(void) {
    struct timespec ts = {};
    ULONGLONG ullTickCount = GetTickCount64();
    ts.tv_sec = (long)(ullTickCount / 1000);
    ts.tv_nsec = (long)(ullTickCount % 1000 * 1000000);
    return ts;
}
#else
#error Unable XDeviceUptime for this platform
#endif


size_t XDeviceProcessorCount(void) {
    int32_t pcnt;
#if CX_TARGET_OS_WINDOWS
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    DWORD_PTR activeProcessorMask = sysInfo.dwActiveProcessorMask;
    // assumes sizeof(DWORD_PTR) is 64 bits or less
    uint64_t v = activeProcessorMask;
    v = v - ((v >> 1) & 0x5555555555555555ULL);
    v = (v & 0x3333333333333333ULL) + ((v >> 2) & 0x3333333333333333ULL);
    v = (v + (v >> 4)) & 0xf0f0f0f0f0f0f0fULL;
    pcnt = (v * 0x0101010101010101ULL) >> ((sizeof(v) - 1) * 8);
#elif CX_TARGET_OS_DARWIN
    int32_t mib[] = {CTL_HW, HW_AVAILCPU};
    size_t len = sizeof(pcnt);
    int32_t result = sysctl(mib, sizeof(mib) / sizeof(int32_t), &pcnt, &len, NULL, 0);
    if (result != 0) {
        pcnt = 0;
    }
#elif CX_TARGET_OS_LINUX
    pcnt = sysconf(_SC_NPROCESSORS_ONLN);
#else
    // Assume the worst
    pcnt = 1;
#endif
    return pcnt;
}


#if CX_TARGET_OS_DARWIN
#include <sys/sysctl.h>
size_t XDeviceCachelineSize(void) {
    
    int name[] = {CTL_HW,HW_CACHELINE};
    size_t lineSize = 0;
    size_t sizeOfLineSize = sizeof(lineSize);

    int code = sysctl(name, 2, &lineSize, &sizeOfLineSize, NULL, 0); // getting size of answer
    if (0 == code) {
        return (size_t)lineSize;
    } else {
        return 64;
    }
}
#elif CX_TARGET_OS_WINDOWS

#include <stdlib.h>
#include <windows.h>
size_t XDeviceCachelineSize() {
    size_t line_size = 0;
    DWORD buffer_size = 0;
    DWORD i = 0;
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

    GetLogicalProcessorInformation(0, &buffer_size);
    buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)XAllocate(buffer_size);
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
        if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
            line_size = buffer[i].Cache.LineSize;
            break;
        }
    }

    XDeallocate(buffer);
    return line_size;
}

#elif CX_TARGET_OS_LINUX || CX_TARGET_OS_ANDROID

#include <stdio.h>
size_t XDeviceCachelineSize() {
    FILE * p = 0;
    p = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
    unsigned int i = 0;
    if (p) {
        fscanf(p, "%d", &i);
        fclose(p);
    }
    return i;
}

#else
    #error Unrecognized platform
#endif


#if CX_TARGET_OS_DARWIN

void XRandomBytes(void * _Nonnull buffer, size_t size) {
    XAssert(buffer, "");
    if (size <= 0) {
        return;
    }
    arc4random_buf(buffer, size);
}

#elif CX_TARGET_OS_WINDOWS

#error "XRandomBytes error"

#elif CX_TARGET_OS_LINUX || CX_TARGET_OS_ANDROID

static int __XRandomBytesFd = -1;
void __XRandomBytesFdInit(void) {
    int fd = open("/dev/urandom", O_RDONLY);
    XAssert(fd != -1, "open /dev/urandom error");
    __XRandomBytesFd = fd;
}
void __XRandomBytesFddeinit(void) {
    close(__XRandomBytesFd);
}
void XRandomBytes(void * _Nonnull b, size_t size) {
    XAssert(b, "");
    if (size <= 0) {
        return;
    }
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, __XRandomBytesInit);
    
    uint8_t * buffer = (uint8_t *)b;
    int fd = __XRandomBytesFd;
    size_t ready = 0;
    while (ready < size) {
        size_t s = ready < size;
        if (s > 4096) {
            s = 4096;
        }
        ssize_t result = read(fd, buffer + ready, s);
        XAssert(result >= 0, "read /dev/urandom error");
        ready += result;
    }
}

#else
    #error Unrecognized platform
#endif


#if CX_TARGET_OS_LINUX || CX_TARGET_OS_ANDROID
#include <unistd.h>
#if __has_include(<syscall.h>)
#include <syscall.h>
#else
#include <sys/syscall.h>
#endif // __has_include(<syscall.h>)
#endif

bool_t XThreadIsMain(void) {
#if CX_TARGET_OS_LINUX || CX_TARGET_OS_ANDROID
    return syscall(SYS_gettid) == getpid();
#else
    return pthread_main_np() == 1;
#endif
}

static XThread_t __XThreadMain;

extern void __XThreadMainInit(void);
void __XThreadMainInit(void) {
    __XThreadMain = XThreadCurrent();
}
XThread_t XThreadMain(void) {
    return __XThreadMain;
}

#if CX_TARGET_OS_DARWIN
microsecond_t thread_cpu_time(void) {
    struct timespec cpu_time;
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &cpu_time) != 0) {
        perror("clock_gettime");
        return MICROSECOND_INVALID;
    }
    return XMicrosecondFromTimespec(cpu_time);
}

#elif CX_TARGET_OS_LINUX
microsecond_t thread_cpu_time(void) {
    clockid_t clock_id;
    if (pthread_getcpuclockid(pthread_self(), &clock_id) != 0) {
        perror("pthread_getcpuclockid");
        return MICROSECOND_INVALID;
    }
    struct timespec cpu_time;
    if (clock_gettime(clock_id, &cpu_time) != 0) {
        perror("clock_gettime");
        return MICROSECOND_INVALID;
    }
    return XMicrosecondFromTimespec(cpu_time);
}
#else
#error "error"
#endif



