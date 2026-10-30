
#ifndef XTaskQueue_h
#define XTaskQueue_h

#include "XRuntime.h"

/*
 XTask_f + context = XTask
 
 */

typedef XObjectRef XTaskQueueRef;
typedef XObjectRef XTaskGroupRef;

extern XClassRef _Nonnull XTaskQueueClass;
extern XClassRef _Nonnull XTaskGroupClass;

typedef void (*XTask_f)(void * _Nullable context);

#pragma mark - XTaskQueue

#if CX_TARGET_SUPPORT_DISPATCH
#if __has_include(<dispatch/dispatch.h>)
#include <dispatch/dispatch.h>
#else
#include "dispatch.h"
#endif
XTaskQueueRef _Nonnull XTaskQueueCreateWithGCDQueue(XObjectOption option, const char *_Nullable label, dispatch_queue_t _Nonnull gcdQueue);
#endif

extern void XTaskQueueMain(void);

/// priority 在[0. 1] 之间，最高优先级为1
extern XTaskQueueRef _Nonnull XTaskQueueCreate(XObjectOption option, const char *_Nullable label, double priority);
extern XTaskQueueRef _Nonnull XTaskQueueCreateWithTargetQueue(XObjectOption option, const char *_Nullable label, XTaskQueueRef _Nonnull queue);

extern XTaskQueueRef _Nonnull XTaskQueueGetMainQueue(void);
extern bool_t XTaskQueueCheckCurrent(XTaskQueueRef _Nonnull q);
extern void XTaskQueueAsync(XTaskQueueRef _Nonnull q, void * _Nullable context, XTask_f _Nonnull work);
extern void XTaskQueueSync(XTaskQueueRef _Nonnull q, void * _Nullable context, XTask_f _Nonnull work);
extern void XTaskQueueAppendItem(XTaskQueueRef _Nonnull q, void * _Nullable context, XTask_f _Nonnull work, XTaskGroupRef _Nullable group);

#pragma mark - XTaskGroup

/// value >= 0; value > 0 时阻塞，value==0 signal
extern XTaskGroupRef _Nonnull XTaskGroupCreate(XObjectOption option, ssize_t value);

/// value = value + delta
extern void XTaskGroupValueAdjust(XTaskGroupRef _Nonnull self, ssize_t delta);
extern ssize_t XTaskGroupGetValue(XTaskGroupRef _Nonnull self);

/// value += 1
extern void XTaskGroupEnter(XTaskGroupRef _Nonnull self);

/// value -= 1, value == 0 signal
extern void XTaskGroupLeave(XTaskGroupRef _Nonnull self);

/// work 只会执行一次
extern void XTaskGroupAppenBlock(XTaskGroupRef _Nonnull self, XTaskQueueRef _Nullable queue, void * _Nullable context, XTask_f _Nonnull work);

extern void XTaskGroupWait(XTaskGroupRef _Nonnull self);

/// work 只会执行一次
extern void XTaskGroupNotify(XTaskGroupRef _Nonnull self, XTaskQueueRef _Nullable queue, void * _Nullable context, XTask_f _Nonnull work);

#endif /* XTaskQueue_h */
