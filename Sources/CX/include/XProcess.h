
#ifndef XProcess_h
#define XProcess_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XCoreBase.h"
#include <pthread.h>

#pragma mark - XSemaphore

typedef struct {
    ssize_t value;
    pthread_cond_t cont;
    pthread_mutex_t mutex;
} XSemaphore_s;

extern void XSemaphoreInit(XSemaphore_s * _Nonnull sem, ssize_t value);
extern void XSemaphoreDeinit(XSemaphore_s * _Nonnull sem);
extern XSemaphore_s * _Nonnull XSemaphoreCreate(ssize_t value);
extern void XSemaphoreDestroy(XSemaphore_s * _Nonnull sem);
extern void XSemaphoreSignal(XSemaphore_s * _Nonnull sem);
extern void XSemaphoreWait(XSemaphore_s * _Nonnull sem);

/// 返回false 表示超时, 返回true表示操作成功, timeout 为相对时间， 表示于当前时间的偏差
extern bool_t XSemaphoreTimedWait(XSemaphore_s * _Nonnull sem, xdispatch_time_t timeout);

#pragma mark - XSpinlock

#if CX_TARGET_OS_DARWIN
#import <os/lock.h>
typedef os_unfair_lock XSpinlock_t;
#elif CX_TARGET_OS_LINUX
typedef pthread_spinlock_t XSpinlock_t;
#else
#error "error"
#endif


extern void XSpinlockInit(XSpinlock_t * _Nonnull lock);
extern void XSpinlockDeinit(XSpinlock_t * _Nonnull lock);
extern void XSpinlockLock(XSpinlock_t * _Nonnull lock);
extern void XSpinlockUnlock(XSpinlock_t * _Nonnull lock);
extern bool_t XSpinlockTrylock(XSpinlock_t * _Nonnull lock);

#pragma mark - XMutex

typedef pthread_mutex_t XMutex_t;

extern void XMutexInit(XMutex_t * _Nonnull lock, bool_t isRecursive);
extern void XMutexDeinit(XMutex_t * _Nonnull lock);
extern void XMutexLock(XMutex_t * _Nonnull lock);
extern void XMutexUnlock(XMutex_t * _Nonnull lock);
extern bool_t XMutexTrylock(XMutex_t * _Nonnull lock);

//返回0成功
extern int XProcessExecutablePath(char * _Nonnull buf, uint32_t * _Nonnull bufsize);


#if CX_TARGET_OS_DARWIN

#define pthread_Nonnull _Nonnull
#define pthread_Nullable _Nullable

#else

#define pthread_Nonnull
#define pthread_Nullable

#endif


typedef struct {
    pthread_t pthread_Nullable id;
} XThread_t;


extern XThread_t XThreadInvalid(void);

extern XThread_t XThreadMake(pthread_t pthread_Nullable pt);
extern XThread_t XThreadCurrent(void);
extern bool_t XThreadIsEqual(XThread_t lhs, XThread_t rhs);
extern bool_t XThreadIsCurrent(XThread_t t);
extern bool_t XThreadIsInvalid(XThread_t t);
extern bool_t XThreadIsMain(void);

extern microsecond_t thread_cpu_time(void);

///
extern XThread_t XThreadCreate(double priority, size_t minStacksize, void * _Nullable (* _Nonnull func)(void * _Nullable), void * _Nullable context);

extern XThread_t XThreadMain(void);

#if CX_TARGET_OS_WINDOWS
struct timespec {
    time_t tv_sec;  // 秒
    long   tv_nsec; // 纳秒
};
#endif
/**
 * 系统启动时长
 */
extern struct timespec XDeviceUptime(void);

//Avaliable CPU processor count
extern size_t XDeviceProcessorCount(void);


extern size_t XDeviceCachelineSize(void);

extern void XRandomBytes(void * _Nonnull buffer, size_t size);

#if defined(__cplusplus)
}  // extern C
#endif


#endif /* XProcess_h */
