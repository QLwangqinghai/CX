
#include "XObjectInternal.h"
#include "XRuntimeInternal.h"
#include "XProcess.h"
#include "XObject.h"
#include "XTaskQueue.h"

typedef enum {
    XTaskQueueStateNotAlive = 0,
    XTaskQueueStateRunning = 1,
    
    /// 这个状态下不允许再添加任务，否则abort
    XTaskQueueStateWillStop = 2,
    
    /// 这个状态下不允许再添加任务，否则abort
    XTaskQueueStateStopped = 3,
} XTaskQueueState_e;

typedef struct {
    _Atomic(uintptr_t) info;
    void * _Nullable context;
    XTask_f _Nonnull work;
    XTaskGroupRef _Nullable group;
} XTaskItem_s;
_Static_assert(sizeof(XTaskItem_s) == sizeof(size_t) * 4, "error");


typedef struct {
    // FIFOQueue head/tail 一直非空，除非_XTaskQueue_o释放， 当一个task的next非空时， task才能从队列移除
    XTaskItem_s * _Nonnull head;
    _Atomic(uintptr_t) tail;
    
    /// FastCache 0 表示mem未使用， 1表示mem已经被使用
    _Atomic(size_fast_t) cacheState;
    XTaskItem_s cache[SIZE_BITS_COUNT];
} _XCoreTaskQueue_s;

typedef bool_t (*_XTaskQueueWorkerCheckCurrent_f)(XObjectRef _Nonnull object);
typedef void (*_XTaskQueueWorkerAppendItem_f)(XObjectRef _Nonnull object, void * _Nullable context, XTask_f _Nonnull work, XTaskGroupRef _Nullable group);
typedef void (*_XTaskQueueWorker_f)(XObjectRef _Nonnull object);

typedef struct {
    _XTaskQueueWorkerCheckCurrent_f _Nonnull checkCurrent;
    _XTaskQueueWorkerAppendItem_f _Nonnull appendItem;
    _XTaskQueueWorker_f _Nonnull stop;
} _XTaskQueueApi_s;

typedef struct {
    XObjectBase_o _runtime;
    const char * _Nullable label;
    XObjectRef _Nonnull _worker;
    const _XTaskQueueApi_s * _Nonnull _api;
} _XTaskQueue_o;

typedef struct {
    XObjectBase_o _runtime;

} _XTaskQueueWorker_s;


// 找不到返回 SIZE_BITS_COUNT
static inline size_fast_t __XCoreTaskQueueFastItemIndex(_XCoreTaskQueue_s * _Nonnull queue, XTaskItem_s * _Nonnull _task) {
    uintptr_t address = (uintptr_t)_task;
    uintptr_t first = (uintptr_t)(queue->cache);
    uintptr_t last = first + sizeof(XTaskItem_s) * SIZE_BITS_COUNT;
    
    if (address < first) {
        return SIZE_BITS_COUNT;
    } else if (address >= last) {
        return SIZE_BITS_COUNT;
    } else {
        uintptr_t offset = address - first;
        XAssert(offset % sizeof(XTaskItem_s) == 0, "");
        return offset / sizeof(XTaskItem_s);
    }
}

typedef struct {
    void * _Nullable context;
    XTask_f _Nonnull work;
    XTask_f _Nullable queue;
} XGroupBlockContext_s;

struct __XGroupBlock;
typedef struct __XGroupBlock XGroupBlock_s;
struct __XGroupBlock {
    XGroupBlock_s * _Nullable next;
    XTaskQueueRef _Nullable queue;
    void * _Nullable context;
    XTask_f _Nonnull work;
};
_Static_assert(sizeof(XGroupBlock_s) == sizeof(size_t) * 4, "error");

static inline XGroupBlock_s * _Nonnull XGroupBlockCreate(XTaskQueueRef _Nullable queue, void * _Nullable context, XTask_f _Nonnull work) {
    XGroupBlock_s * block = malloc(sizeof(XGroupBlock_s));
    block->next = NULL;
    block->work = work;
    block->queue = queue;
    block->context = context;
    XAssert(((uintptr_t)block) % 2 == 0, "");
    return block;
}

static inline void XGroupBlockDestroy(XGroupBlock_s * _Nonnull block) {
    free(block);
}

typedef struct {
    XObjectBase_o _runtime;
    XSpinlock_t lock;
    ssize_t count;
    XGroupBlock_s * _Nullable blocks;
} _XTaskGroup_o;

/// Dispatch 是一个待执行的task
#define _XTaskInfoUnexecutedFlag SIZE_C(0x1)

uintptr_t __XAtomicPtrExchange(_Atomic(uintptr_t) * _Nonnull ptr, uintptr_t new) {
    uintptr_t old = 0;
    do {
        old = atomic_load(ptr);
        XAssert(old != new, "");
    } while (!atomic_compare_exchange_strong(ptr, &old, new));
    return old;
}

void __XTaskItemDealloc(XTaskItem_s * _Nonnull task) {
    free(task);
}
XTaskItem_s * _Nonnull __XTaskItemAlloc(void) {
    return malloc(sizeof(XTaskItem_s));
}
XTaskItem_s * _Nullable __XCoreTaskQueueCreateFastItem(_XCoreTaskQueue_s * _Nonnull queue) {
    XTaskItem_s * task = NULL;
    // step0: get a cache;
    size_fast_t cacheState = 0;
    size_fast_t newCacheState = 0;
    size_fast_t one = 0x1;
    do {
        cacheState = atomic_load(&(queue->cacheState));
        size_fast_t index = USizeFindFirstZero(cacheState);
        if (index >= SIZE_BITS_COUNT) {
            task = NULL;
            break;
        }
        task = &(queue->cache[index]);
        newCacheState = cacheState | (one << index);
    } while (!atomic_compare_exchange_strong(&(queue->cacheState), &cacheState, newCacheState));
    return task;
}

XTaskItem_s * _Nullable __XCoreTaskQueueCreateSpacingItem(_XCoreTaskQueue_s * _Nonnull queue) {
    XTaskItem_s * task = __XCoreTaskQueueCreateFastItem(queue);
    if (task) {
        uintptr_t info = (uintptr_t)NULL;
        task->work = NULL;
        task->context = NULL;
        task->group = NULL;
        atomic_store(&(task->info), info);
    }
    return task;
}

XTaskItem_s * _Nonnull __XCoreTaskQueueCreateItem(_XCoreTaskQueue_s * _Nonnull queue, void * _Nullable context, XTask_f _Nonnull work, XTaskGroupRef _Nullable group) {
    // step0: get a cache;
    XTaskItem_s * task = __XCoreTaskQueueCreateFastItem(queue);
    
    // step1: create if needed
    if (NULL == task) {
        task = __XTaskItemAlloc();
    }
    
    // step2: init
    uintptr_t info = _XTaskInfoUnexecutedFlag;
    task->work = work;
    task->context = context;
    task->group = XObjectRetain(group);
    atomic_store(&(task->info), info);
    return task;
}

void __XCoreTaskQueueDestroyItem(_XCoreTaskQueue_s * _Nonnull queue, XTaskItem_s * _Nonnull _task) {
    if (_task->group) {
        XObjectRelease(_task->group);
        _task->group = NULL;
    }
    
    size_fast_t index = __XCoreTaskQueueFastItemIndex(queue, _task);
    if (index < SIZE_BITS_COUNT) {
        size_fast_t cacheState = 0;
        size_fast_t newCacheState = 0;
        size_fast_t one = 0x1;
        do {
            cacheState = atomic_load(&(queue->cacheState));
            size_fast_t mask = (one << index);
            XAssert(mask == (cacheState & mask), "");
            newCacheState = cacheState & (~mask);
        } while (!atomic_compare_exchange_strong(&(queue->cacheState), &cacheState, newCacheState));
    } else {
        __XTaskItemDealloc(_task);
    }
}

void __XCoreTaskQueueInit(_XCoreTaskQueue_s * queue) {
    atomic_store(&(queue->cacheState), 0);
    atomic_store(&(queue->tail), (uintptr_t)NULL);
    queue->head = NULL;
    
    XTaskItem_s * spacing = __XCoreTaskQueueCreateSpacingItem(queue);
    XAssert(spacing, "");
    atomic_store(&(queue->tail), (uintptr_t)spacing);
    queue->head = spacing;
}

void _XCoreTaskQueueDeinit(_XCoreTaskQueue_s * _Nonnull queue) {
    if (queue->head) {
        __XCoreTaskQueueDestroyItem(queue, queue->head);
        queue->head = NULL;
    }
}

///  线程安全， 允许 多个线程同时操作,  返回true 表示需要wakeup
bool_t __XCoreTaskQueueAppendItem(_XCoreTaskQueue_s * _Nonnull queue, void * _Nullable context, XTask_f _Nonnull work, XTaskGroupRef _Nullable group) {
    XTaskItem_s * task = __XCoreTaskQueueCreateItem(queue, context, work, group);
    const uintptr_t unfinishedFlag = _XTaskInfoUnexecutedFlag;
    XDebugAssert(0 == ((uintptr_t)task & unfinishedFlag), "");
    // 由于队列中的元素永远>=1, 对tail的操作不会影响head，
    /*
     先把entity设置成尾节点，然后再把entity添加到上个尾节点上
     添加元素永远只操作尾节点永远正确，把entity添加到上个节点上有个时间间隔，万一上个节点被移出了呢， 只有当一个节点的next非空时，才能被移出
     
     移出元素只能操作head节点
     
     当没有上一个节点时，则此事queue是个空的queue，把entity放到head节点上，然后single
     */
    uintptr_t prevptr = (uintptr_t)NULL;
    do {
        prevptr = atomic_load(&(queue->tail));
        if (prevptr == (uintptr_t)NULL) {
            __XCoreTaskQueueDestroyItem(queue, task);
            abort();
        }
    } while (!atomic_compare_exchange_strong(&(queue->tail), &prevptr, (uintptr_t)task));
    
    XTaskItem_s * prev = (XTaskItem_s *)prevptr;
    uintptr_t oldInfo = 0;
    uintptr_t newInfo = 0;
    do {
        oldInfo = atomic_load(&(prev->info));
        uintptr_t flag = oldInfo & unfinishedFlag;

        XAssert((uintptr_t)NULL == (oldInfo & (~unfinishedFlag)), "");
        newInfo = (uintptr_t)task | flag;
    } while (!atomic_compare_exchange_strong(&(prev->info), &oldInfo, newInfo));
    
    return (0 == (newInfo & unfinishedFlag));
}

void XTaskQueueLogError(void) {
    XLog("%s", strerror(errno));
}



#pragma mark - XTaskQueueThreadWorker

extern const _XTaskQueueApi_s _XTaskQueueApiThreadWorker;
extern const XClass_o _XTaskQueueThreadWorkerClass;

typedef struct {
    XObjectBase_o _runtime;
    _Atomic(uintptr_t) _context;

    XThread_t thread;
    XSemaphore_s * _Nonnull sem;
    
    _XCoreTaskQueue_s core;
} _XTaskQueueThreadWorker_o;

void _XTaskQueueThreadWorkerDeinit(XObjectRef _Nonnull self);

void * __XTaskQueueThreadWorkerRun(void * args);

_XTaskQueueThreadWorker_o * _Nonnull _XTaskQueueThreadWorkerCreateMain(XTaskQueueRef _Nonnull queue) {
    _XTaskQueueThreadWorker_o * worker = (_XTaskQueueThreadWorker_o *)XObjectAllocate(&_XTaskQueueThreadWorkerClass, 0, sizeof(_XTaskQueueThreadWorker_o), 0);
    XAssert(worker, "");
    XAssert(queue, "");
    worker->sem = XSemaphoreCreate(0);
    atomic_store(&(worker->_context), (uintptr_t)queue);
    __XCoreTaskQueueInit(&(worker->core));
    worker->thread = XThreadMain();
    return worker;
}

_XTaskQueueThreadWorker_o * _Nonnull _XTaskQueueThreadWorkerCreate(XTaskQueueRef _Nonnull queue, double priority) {
    _XTaskQueueThreadWorker_o * worker = (_XTaskQueueThreadWorker_o *)XObjectAllocate(&_XTaskQueueThreadWorkerClass, 0, sizeof(_XTaskQueueThreadWorker_o), 0);
    XAssert(queue, "");
    XAssert(worker, "");
    worker->sem = XSemaphoreCreate(0);
    atomic_store(&(worker->_context), (uintptr_t)queue);
    worker->thread = XThreadInvalid();
    __XCoreTaskQueueInit(&(worker->core));
    worker->thread = XThreadCreate(priority, 512 * 1024, __XTaskQueueThreadWorkerRun, worker);
    
    // 此处retain 对应的release 在 __XTaskQueueThreadWorkerRun
    XObjectRetain(worker);
    return worker;
}

void _XTaskQueueThreadWorkerDeinit(XObjectRef _Nonnull self) {
    _XTaskQueueThreadWorker_o * _Nonnull worker = (_XTaskQueueThreadWorker_o *)self;
    XSemaphoreDestroy(worker->sem);
    _XCoreTaskQueueDeinit(&(worker->core));
    XDeallocate(worker);
}

void _XTaskQueueThreadWorkerStop(void * _Nonnull args) {
    _XTaskQueueThreadWorker_o * _Nonnull worker = (_XTaskQueueThreadWorker_o *)args;
    _Atomic(uintptr_t) * contextptr = &(worker->_context);
    uintptr_t context = 0;
    uintptr_t newContext = (uintptr_t)NULL;
    do {
        context = atomic_load(contextptr);
        if (context == newContext) {
            return;
        }
    } while (!atomic_compare_exchange_strong(contextptr, &context, newContext));
    XSemaphoreSignal(worker->sem);
}

void _XCoreTaskQueueProgress(_XCoreTaskQueue_s * _Nonnull queue) {
    static const uintptr_t unfinishedFlag = _XTaskInfoUnexecutedFlag;
    while (true) {
        XTaskItem_s * head = queue->head;
        XAssert(head, "head only null deiniting");
        uintptr_t info = atomic_load(&(head->info));
        // 第一个永远是已经完成的
        XAssert((info & unfinishedFlag) != unfinishedFlag, "");
        XTaskItem_s * task = (XTaskItem_s *)(info & (~unfinishedFlag));
        
        if (NULL == task) {
            do {
                // 及时释放非fasttask内存
                size_fast_t index = __XCoreTaskQueueFastItemIndex(queue, head);
                if (index < SIZE_BITS_COUNT) {
                    break;
                }
                XTaskItem_s * spacing = __XCoreTaskQueueCreateSpacingItem(queue);
                uintptr_t prevptr = (uintptr_t)NULL;
                do {
                    prevptr = atomic_load(&(queue->tail));
                    if (prevptr != (uintptr_t)head) {
                        break;
                    }
                } while (!atomic_compare_exchange_strong(&(queue->tail), &prevptr, (uintptr_t)spacing));
                if (prevptr != (uintptr_t)head) {
                    break;
                }
                queue->head = spacing;
                __XTaskItemDealloc(head);
            } while(0);
            return;
        } else {
            queue->head = task;
            uintptr_t oldHeadInfo = __XAtomicPtrExchange(&(head->info), (uintptr_t)NULL);
            XAssert(info == oldHeadInfo, "");
            __XCoreTaskQueueDestroyItem(queue, head);
            
            uintptr_t oldInfo = atomic_load(&(task->info));
            if (oldInfo & unfinishedFlag) {
                task->work(task->context);
                if (task->group) {
                    XTaskGroupLeave(task->group);
                    XObjectRelease(task->group);
                    task->group = NULL;
                }
                task->context = NULL;
                task->work = NULL;
                uintptr_t newInfo = 0;
                do {
                    oldInfo = atomic_load(&(task->info));
                    newInfo = oldInfo & (~unfinishedFlag);
                    XAssert(oldInfo != newInfo, "");
                } while (!atomic_compare_exchange_strong(&(task->info), &oldInfo, newInfo));
            }
        }
    }
}

void * __XTaskQueueThreadWorkerRun(void * args) {
    _XTaskQueueThreadWorker_o * worker = (_XTaskQueueThreadWorker_o *)args;
    _XCoreTaskQueue_s * _Nonnull queue = &(worker->core);
    uintptr_t context = atomic_load(&(worker->_context));
    do {
        XSemaphoreWait(worker->sem);
        _XCoreTaskQueueProgress(queue);
        context = atomic_load(&(worker->_context));
    } while (context != (uintptr_t)NULL);
    do {
        _XCoreTaskQueueProgress(queue);
    } while(XSemaphoreTimedWait(worker->sem, 0));
//    pthread_setname_np(pthread_self(), "thread name");
    XObjectRelease(worker);
    return NULL;
}

#define CELogError(format, ...) if (1) {\
fprintf(stderr, format, ##__VA_ARGS__);                                               \
fprintf(stderr, "\n");                                          \
}

bool_t _XTaskQueueThreadWorkerCheckCurrent(XObjectRef _Nonnull self) {
    _XTaskQueueThreadWorker_o * worker = (_XTaskQueueThreadWorker_o *)self;
    XThread_t t = XThreadCurrent();
    bool_t result = XThreadIsEqual(t, worker->thread);
    return result;
}

void _XTaskQueueThreadWorkerAppendItem(XObjectRef _Nonnull self, void * _Nullable context, XTask_f _Nonnull work, XTaskGroupRef _Nullable group) {
    _XTaskQueueThreadWorker_o * worker = (_XTaskQueueThreadWorker_o *)self;
    _XCoreTaskQueue_s * core = &(worker->core);
    bool_t needWakeUp = __XCoreTaskQueueAppendItem(core, context, work, group);
    if (needWakeUp) {
        XSemaphoreSignal(worker->sem);
    }
}

const _XTaskQueueApi_s _XTaskQueueApiThreadWorker = {
    .checkCurrent = _XTaskQueueThreadWorkerCheckCurrent,
    .appendItem = _XTaskQueueThreadWorkerAppendItem,
    .stop = _XTaskQueueThreadWorkerStop,
};


#pragma mark - XTaskQueueGCDWorker

#if CX_TARGET_SUPPORT_DISPATCH

typedef struct {
    XObjectBase_o _runtime;
    _Atomic(uintptr_t) _context;
    dispatch_queue_t _Nonnull gcd;
    _XCoreTaskQueue_s core;
} _XTaskQueueGCDWorker_o;

extern const _XTaskQueueApi_s _XTaskQueueApiGCDWorker;
extern const XClass_o _XTaskGroupGCDWorkerClass;

void __XTaskQueueGCDWorkerDispatchFunc(void * _Nonnull ctx);
void _XTaskQueueGCDWorkerWakeUp(_XTaskQueueGCDWorker_o * _Nonnull worker) {
    XObjectRetain(worker);
    dispatch_async_f(worker->gcd, worker, __XTaskQueueGCDWorkerDispatchFunc);
}

_XTaskQueueGCDWorker_o * _Nonnull __XTaskQueueGCDWorkerCreate(XTaskQueueRef _Nonnull owner, dispatch_queue_t _Nonnull gcdQueue) {
    _XTaskQueueGCDWorker_o * worker = (_XTaskQueueGCDWorker_o *)XObjectAllocate(&_XTaskGroupGCDWorkerClass, 0, sizeof(_XTaskQueueGCDWorker_o), 0);
    XAssert(worker, "");
    XAssert(owner, "");
    dispatch_retain(gcdQueue);
    worker->gcd = gcdQueue;
    atomic_store(&(worker->_context), (uintptr_t)owner);
    __XCoreTaskQueueInit(&(worker->core));
    return worker;
}

void _XTaskQueueGCDWorkerDeinit(XObjectRef _Nonnull self) {
    _XTaskQueueGCDWorker_o * _Nonnull worker = (_XTaskQueueGCDWorker_o *)self;
    if (worker->gcd) {
        dispatch_release(worker->gcd);
        worker->gcd = NULL;
    }
    _XCoreTaskQueueDeinit(&(worker->core));
    XDeallocate(worker);
}
static int XTaskQueueGCDWorkerateSpecificKey = 0x3;

XTaskQueueRef _Nonnull XTaskQueueCreateWithGCDQueue(XObjectOption option, const char *_Nullable label, dispatch_queue_t _Nonnull gcdQueue) {
    dispatch_queue_set_specific(gcdQueue, &XTaskQueueGCDWorkerateSpecificKey, gcdQueue, NULL);
    _XTaskQueue_o * queue = (_XTaskQueue_o *)XObjectAllocate(XTaskQueueClass, option, sizeof(_XTaskQueue_o), 0);
    XAssert(queue, "");
    if (label) {
        queue->label = strdup(label);
    } else {
        queue->label = NULL;
    }
    // queue->_core对应的deinit 在_XCoreTaskQueueThreadRun中执行
    queue->_api = &_XTaskQueueApiGCDWorker;
    queue->_worker = __XTaskQueueGCDWorkerCreate(queue, gcdQueue);
    return queue;
}

void _XTaskQueueGCDWorkerStop(void * _Nonnull args) {
    _XTaskQueueGCDWorker_o * _Nonnull worker = (_XTaskQueueGCDWorker_o *)args;
    _Atomic(uintptr_t) * contextptr = &(worker->_context);
    uintptr_t context = 0;
    uintptr_t newContext = (uintptr_t)NULL;
    do {
        context = atomic_load(contextptr);
        if (context == newContext) {
            return;
        }
    } while (!atomic_compare_exchange_strong(contextptr, &context, newContext));
    _XTaskQueueGCDWorkerWakeUp(worker);
}

void __XTaskQueueGCDWorkerProgress(_XTaskQueueGCDWorker_o * _Nonnull worker) {
    _XCoreTaskQueue_s * _Nonnull queue = &(worker->core);
    _XCoreTaskQueueProgress(queue);
}

void __XTaskQueueGCDWorkerDispatchFunc(void * _Nonnull ctx) {
    _XTaskQueueGCDWorker_o * _Nonnull worker = (_XTaskQueueGCDWorker_o *)ctx;
    __XTaskQueueGCDWorkerProgress(worker);
    XObjectRelease(worker);
}

bool_t _XTaskQueueGCDWorkerCheckCurrent(XObjectRef _Nonnull self) {
    _XTaskQueueGCDWorker_o * _Nonnull worker = (_XTaskQueueGCDWorker_o *)self;
    dispatch_queue_t queue = (dispatch_queue_t)dispatch_get_specific(&XTaskQueueGCDWorkerateSpecificKey);
    return queue == worker->gcd;
}

void _XTaskQueueGCDWorkerAppendItem(XObjectRef _Nonnull self, void * _Nullable context, XTask_f _Nonnull work, XTaskGroupRef _Nullable group) {
    _XTaskQueueGCDWorker_o * worker = (_XTaskQueueGCDWorker_o *)self;
    _XCoreTaskQueue_s * core = &(worker->core);
    bool_t needWakeUp = __XCoreTaskQueueAppendItem(core, context, work, group);
    if (needWakeUp) {
        _XTaskQueueGCDWorkerWakeUp(worker);
    }
}

const _XTaskQueueApi_s _XTaskQueueApiGCDWorker = {
    .checkCurrent = _XTaskQueueGCDWorkerCheckCurrent,
    .appendItem = _XTaskQueueGCDWorkerAppendItem,
    .stop = _XTaskQueueGCDWorkerStop,
};

const XClass_o _XTaskGroupGCDWorkerClass = XClassMakeNameDeinit(XTaskQueueGCDWorker, 0, _XTaskQueueGCDWorkerDeinit);

#endif

#pragma mark - target queue

extern const _XTaskQueueApi_s _XTaskQueueApiTargetQueue;

void _XTaskQueueTargetQueueStop(void * _Nonnull args) {
    // do nothing
}

const _XTaskQueueApi_s _XTaskQueueApiTargetQueue = {
    .checkCurrent = XTaskQueueCheckCurrent,
    .appendItem = XTaskQueueAppendItem,
    .stop = _XTaskQueueTargetQueueStop,
};

XTaskQueueRef _Nonnull XTaskQueueCreateWithTargetQueue(XObjectOption option, const char *_Nullable label, XTaskQueueRef _Nonnull targetQueue) {
    _XTaskQueue_o * queue = (_XTaskQueue_o *)XObjectAllocate(XTaskQueueClass, option, sizeof(_XTaskQueue_o), 0);
    XAssert(queue, "");
    if (label) {
        queue->label = strdup(label);
    } else {
        queue->label = NULL;
    }
    // queue->_core对应的deinit 在_XCoreTaskQueueThreadRun中执行
    queue->_api = &_XTaskQueueApiTargetQueue;
    queue->_worker = XObjectRetain(targetQueue);
    return queue;
}

#pragma mark - queue

static _XTaskQueue_o * _Nonnull __XTaskQueueMainQueue = NULL;
void __XTaskQueueMainQueueCreate(void) {
#if CX_TARGET_SUPPORT_DISPATCH
    __XTaskQueueMainQueue = XTaskQueueCreateWithGCDQueue(XObjectOptionStatic, "main", dispatch_get_main_queue());
#else
    _XTaskQueue_o * queue = (_XTaskQueue_o *)XObjectAllocate(XTaskQueueClass, XObjectOptionStatic, sizeof(_XTaskQueue_o), 0);
    XAssert(queue, "");
    queue->label = strdup("main");
    queue->_api = &_XTaskQueueApiThreadWorker;
    queue->_worker = _XTaskQueueThreadWorkerCreateMain(queue);
    __XTaskQueueMainQueue = queue;
#endif
}
XTaskQueueRef _Nonnull XTaskQueueGetMainQueue(void) {
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, __XTaskQueueMainQueueCreate);
    return __XTaskQueueMainQueue;
}

void XTaskQueueMain(void) {
    XAssert(XThreadIsMain(), "");

#if CX_TARGET_SUPPORT_DISPATCH
    XTaskQueueGetMainQueue();
    dispatch_main();
#else
    _XTaskQueue_o * queue = (_XTaskQueue_o *)XTaskQueueGetMainQueue();
    XObjectRetain(queue->_context);
    __XTaskQueueThreadWorkerRun(queue->_context);
#endif
}

XTaskQueueRef _Nonnull XTaskQueueCreate(XObjectOption option, const char *_Nullable label, double _priority) {
    double priority = 0;
    if (_priority <= 0) {
        priority = 0;
    } else if (_priority >= 1) {
        priority = 1;
    } else {
        priority = _priority;
    }
    
    _XTaskQueue_o * queue = (_XTaskQueue_o *)XObjectAllocate(XTaskQueueClass, option, sizeof(_XTaskQueue_o), 0);
    XAssert(queue, "");
    if (label) {
        queue->label = strdup(label);
    } else {
        queue->label = NULL;
    }
    queue->_api = &_XTaskQueueApiThreadWorker;
    queue->_worker = _XTaskQueueThreadWorkerCreate(queue, priority);
    return queue;
}

bool_t XTaskQueueCheckCurrent(XTaskQueueRef _Nonnull q) {
    XAssert(XTaskQueueClass == XObjectGetClass(q), "");
    _XTaskQueue_o * queue = (_XTaskQueue_o *)q;
    return queue->_api->checkCurrent(queue->_worker);
}
void XTaskQueueAppendItem(XTaskQueueRef _Nonnull q, void * _Nullable context, XTask_f _Nonnull work, XTaskGroupRef _Nullable group) {
    XAssert(XTaskQueueClass == XObjectGetClass(q), "");
    _XTaskQueue_o * queue = (_XTaskQueue_o *)q;
    return queue->_api->appendItem(queue->_worker, context, work, group);
}
void XTaskQueueAsync(XTaskQueueRef _Nonnull q, void * _Nullable context, XTask_f _Nonnull work) {
    XTaskQueueAppendItem(q, context, work, NULL);
}
void XTaskQueueSync(XTaskQueueRef _Nonnull q, void * _Nullable context, XTask_f _Nonnull work) {
    XTaskGroupRef group = XTaskGroupCreate(0, 0);
    XTaskGroupEnter(group);
    XTaskQueueAppendItem(q, context, work, group);
    XTaskGroupWait(group);
    XObjectRelease(group);
}

#pragma mark - XTaskQueue runtime

void _XTaskQueueDeinit(XObjectRef _Nonnull self) {
    _XTaskQueue_o * queue = (_XTaskQueue_o *)self;
    queue->_api->stop(queue->_worker);
    XObjectRelease(queue->_worker);
    queue->_worker = NULL;
    if (queue->label) {
        free((void *)queue->label);
        queue->label = NULL;
    }
}
void _XTaskQueueDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XTaskQueueDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

#pragma mark - XTaskGroup
XTaskGroupRef _Nonnull XTaskGroupCreate(XObjectOption option, ssize_t value) {
    XAssert(value >= 0, "");
    _XTaskGroup_o * group = (_XTaskGroup_o *)XObjectAllocate(XTaskGroupClass, option, sizeof(_XTaskGroup_o), 0);
    XSpinlockInit(&(group->lock));
    group->count = 0;
    group->blocks = NULL;
    return group;
}

void _XTaskGroupDeinit(XObjectRef _Nonnull self) {
    _XTaskGroup_o * group = (_XTaskGroup_o *)self;
    XAssert(group->count == 0, "");
    XAssert(group->blocks == NULL, "");
    XSpinlockDeinit(&(group->lock));
}

void XTaskGroupValueAdjust(XTaskGroupRef _Nonnull self, ssize_t delta) {
    _XTaskGroup_o * group = (_XTaskGroup_o *)self;
    XGroupBlock_s * list = NULL;
    XSpinlockLock(&(group->lock));
    if (delta < 0) {
        XAssertFunc(group->count + delta >= 0 , __func__, "count error");
    } else {
        XAssertFunc(group->count <= SSIZE_MAX - delta , __func__, "count error");
    }
    group->count += delta;
    if (0 == group->count) {
        list = group->blocks;
        group->blocks = NULL;
    }
    XSpinlockUnlock(&(group->lock));
    
    // reverse
    XGroupBlock_s * head = NULL;
    while (list) {
        XGroupBlock_s * tmp = list->next;
        list->next = head;
        head = list;
        list = tmp;
    }
    while (head) {
        // 执行
        if (head->queue) {
            XTaskQueueAsync(head->queue, head->context, head->work);
        } else {
            head->work(head->context);
        }
        XGroupBlock_s * tmp = head;
        head = head->next;
        XGroupBlockDestroy(tmp);
    }
}
ssize_t XTaskGroupGetValue(XTaskGroupRef _Nonnull self) {
    _XTaskGroup_o * group = (_XTaskGroup_o *)self;
    ssize_t value = 0;
    XSpinlockLock(&(group->lock));
    value = group->count;
    XSpinlockUnlock(&(group->lock));
    return value;
}

void XTaskGroupEnter(XTaskGroupRef _Nonnull self) {
    _XTaskGroup_o * group = (_XTaskGroup_o *)self;
    XSpinlockLock(&(group->lock));
    XAssertFunc(group->count >= 0, __func__, "count error");
    XAssertFunc(group->count < SSIZE_MAX, __func__, "count error");
    group->count += 1;
    XSpinlockUnlock(&(group->lock));
}
void XTaskGroupLeave(XTaskGroupRef _Nonnull self) {
    _XTaskGroup_o * group = (_XTaskGroup_o *)self;
    XGroupBlock_s * list = NULL;
    XSpinlockLock(&(group->lock));
    XAssertFunc(group->count > 0, __func__, "count error");
    XAssertFunc(group->count <= SSIZE_MAX, __func__, "count error");
    group->count -= 1;
    if (0 == group->count) {
        list = group->blocks;
        group->blocks = NULL;
    }
    XSpinlockUnlock(&(group->lock));
    // reverse
    XGroupBlock_s * head = NULL;
    while (list) {
        XGroupBlock_s * tmp = list->next;
        list->next = head;
        head = list;
        list = tmp;
    }
    while (head) {
        // 执行
        if (head->queue) {
            XTaskQueueAsync(head->queue, head->context, head->work);
        } else {
            head->work(head->context);
        }
        XGroupBlock_s * tmp = head;
        head = head->next;
        XGroupBlockDestroy(tmp);
    }
}

void XTaskGroupAppenBlock(XTaskGroupRef _Nonnull self, XTaskQueueRef _Nullable queue, void * _Nullable context, XTask_f _Nonnull work) {
    _XTaskGroup_o * group = (_XTaskGroup_o *)self;
    XGroupBlock_s * block = XGroupBlockCreate(queue, context, work);
    XSpinlockLock(&(group->lock));
    if (group->count > 0) {
        block->next = group->blocks;
        group->blocks = block;
        block = NULL;
    }
    XSpinlockUnlock(&(group->lock));
    if (block) {
        if (queue) {
            XTaskQueueAsync(queue, context, work);
        } else {
            work(context);
        }
        XGroupBlockDestroy(block);
    }
}

void _XTaskGroupDoSemaphoreSignal(void * _Nullable _sem) {
    XSemaphore_s * sem = (XSemaphore_s *)_sem;
    XSemaphoreSignal(sem);
}

typedef struct {
    /// 0 表示mem未使用， 1表示mem已经被使用
    _Atomic(size_fast_t) cacheState;
    XSemaphore_s cache[SIZE_BITS_COUNT];
} XSemaphoreCache_s;

static XSemaphoreCache_s * _Nullable ___XSemaphoreCacheDispatchQueueSyncShared = NULL;
void __XTaskQueueSemaphoreCacheSharedCreate(void) {
    ___XSemaphoreCacheDispatchQueueSyncShared = malloc(sizeof(XSemaphoreCache_s));
    atomic_store(&(___XSemaphoreCacheDispatchQueueSyncShared->cacheState), 0);
    for (ssize_t i=0; i<SIZE_BITS_COUNT; i++) {
        XSemaphoreInit(&(___XSemaphoreCacheDispatchQueueSyncShared->cache[i]), 0);
    }
}

XSemaphoreCache_s * _Nonnull XSemaphoreCacheDispatchQueueSyncShared(void) {
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, __XTaskQueueSemaphoreCacheSharedCreate);
    return ___XSemaphoreCacheDispatchQueueSyncShared;
}

// 找不到返回 SIZE_BITS_COUNT
static inline size_fast_t __XTaskQueueSemaphoreCacheIndex(XSemaphoreCache_s * _Nonnull cache, XSemaphore_s * _Nonnull sem) {
    uintptr_t address = (uintptr_t)sem;
    uintptr_t first = (uintptr_t)(cache->cache);
    uintptr_t last = first + sizeof(XSemaphore_s) * SIZE_BITS_COUNT;
    if (address < first) {
        return SIZE_BITS_COUNT;
    } else if (address >= last) {
        return SIZE_BITS_COUNT;
    } else {
        uintptr_t offset = address - first;
        XAssert(offset % sizeof(XSemaphore_s) == 0, "");
        return offset / sizeof(XSemaphore_s);
    }
}

XSemaphore_s * _Nonnull __XTaskGroupCreateSemaphore(XSemaphoreCache_s * _Nonnull cache) {
    // step0: get a cache;
    
    XSemaphore_s * sem = NULL;
    // step0: get a cache;
    size_fast_t cacheState = 0;
    size_fast_t newCacheState = 0;
    size_fast_t one = 0x1;
    do {
        cacheState = atomic_load(&(cache->cacheState));
        size_fast_t index = USizeFindFirstZero(cacheState);
        if (index >= SIZE_BITS_COUNT) {
            sem = NULL;
            break;
        }
        sem = &(cache->cache[index]);
        newCacheState = cacheState | (one << index);
    } while (!atomic_compare_exchange_strong(&(cache->cacheState), &cacheState, newCacheState));
    if (NULL == sem) {
        sem = XSemaphoreCreate(0);
    }
    return sem;
}

void __XTaskGroupDestroySemaphore(XSemaphoreCache_s * _Nonnull cache, XSemaphore_s * _Nonnull sem) {
    size_fast_t index = __XTaskQueueSemaphoreCacheIndex(cache, sem);
    if (index < SIZE_BITS_COUNT) {
        size_fast_t cacheState = 0;
        size_fast_t newCacheState = 0;
        size_fast_t one = 0x1;
        do {
            cacheState = atomic_load(&(cache->cacheState));
            size_fast_t mask = (one << index);
            XAssert(mask == (cacheState & mask), "");
            newCacheState = cacheState & (~mask);
        } while (!atomic_compare_exchange_strong(&(cache->cacheState), &cacheState, newCacheState));
    } else {
        XSemaphoreDestroy(sem);
    }
}

void XTaskGroupWait(XTaskGroupRef _Nonnull self) {
    XSemaphoreCache_s * cache = XSemaphoreCacheDispatchQueueSyncShared();
    XSemaphore_s * sem = __XTaskGroupCreateSemaphore(cache);
    XTaskGroupAppenBlock(self, NULL, sem, _XTaskGroupDoSemaphoreSignal);
    XSemaphoreWait(sem);
    __XTaskGroupDestroySemaphore(cache, sem);
}

void XTaskGroupNotify(XTaskGroupRef _Nonnull self, XTaskQueueRef _Nullable queue, void * _Nullable context, XTask_f _Nonnull work) {
    XTaskGroupAppenBlock(self, queue, context, work);
}

#pragma mark - class

const XClass_o _XTaskQueueClass = XClassMakeNameDeinit(XTaskQueue, 0, _XTaskQueueDeinit);
XClassRef _Nonnull XTaskQueueClass = &_XTaskQueueClass;

const XClass_o _XTaskGroupClass = XClassMakeNameDeinit(XTaskGroup, 0, _XTaskGroupDeinit);
XClassRef _Nonnull XTaskGroupClass = &_XTaskGroupClass;

const XClass_o _XTaskQueueThreadWorkerClass = XClassMakeNameDeinit(XTaskQueueThreadWorker, 0, _XTaskQueueThreadWorkerDeinit);
