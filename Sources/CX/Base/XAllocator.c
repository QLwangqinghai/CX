
#include "XAllocator.h"
#include "XProcess.h"
#include "XCoreBase.h"
#include <sys/mman.h>
#include "XObject.h"



const XAllocatorOption XAllocatorOptionStatic = 0x1;

#pragma mark - zone
struct __XZone;
typedef struct __XZone XZone_s;
struct __XZone {
    size_t id;
    // 当前zone失败后下一个zone的id
    size_t next;
    
    void * _Nullable context;
    void * _Nullable (* allocate)(const XZone_s * _Nonnull zone, size_t size);
    void (* deallocate)(const XZone_s * _Nonnull zone, void * _Nonnull ptr);
};

static inline void XZoneInit(XZone_s * zone, size_t id, size_t next, void * _Nullable context, void * _Nullable (* allocate)(const XZone_s * _Nonnull zone, size_t size), void (* deallocate)(const XZone_s * _Nonnull zone, void * _Nonnull ptr)) {
    zone->id = id;
    zone->next = next;
    zone->context = context;
    zone->allocate = allocate;
    zone->deallocate = deallocate;
}

extern void * _Nullable _XZoneDefaultAllocate(const XZone_s * _Nonnull zone, size_t size);
extern void _XZoneDefaultDeallocate(const XZone_s * _Nonnull zone, void * _Nonnull ptr);

extern void * _Nonnull _XZoneStaticAllocate(const XZone_s * _Nonnull zone, size_t size);
extern void _XZoneStaticDeallocate(const XZone_s * _Nonnull zone, void * _Nonnull ptr);

extern void * _Nullable _XZoneTinyAllocate(const XZone_s * _Nonnull zone, size_t size);
extern void _XZoneTinyDeallocate(const XZone_s * _Nonnull zone, void * _Nonnull ptr);


#pragma mark - cache

struct __XMEntity;
typedef struct __XMEntity XMEntity_s;

struct __XMEntity {
    _Atomic(size_fast_t) _runtime;
    _Atomic(uintptr_t) next;
};
void __XMEntityStore(XMEntity_s * _Nonnull entity, uintptr_t oldNext, uintptr_t next) {
    _Atomic(uintptr_t) * nextPtr = &(entity->next);
    if (!atomic_compare_exchange_strong(nextPtr, &oldNext, next)) {
        abort();
    }
}

typedef struct {
    XSpinlock_t lock;
    XMEntity_s * _Nullable head;
} XMEntityBucket_s;

typedef struct {
    size_t objectSize;
    size_t count;
    size_t alignSize;
    uint8_t * _Nonnull mem;
    
    XSpinlock_t lock;
    _Atomic(uintptr_t) head;
} XZoneCache_s;

void XZoneCacheInit(XZoneCache_s * _Nonnull cache, size_t objectSize, size_t count, size_t alignSize, uint8_t * _Nonnull mem) {
    cache->objectSize = objectSize;
    cache->count = count;
    cache->alignSize = alignSize;
    cache->mem = mem;
    XSpinlockInit(&(cache->lock));
    
    uint8_t * ptr = mem;
    uintptr_t head = (uintptr_t)ptr;
    for (ssize_t i=0; i<count; i++) {
        XMEntity_s * entity = (XMEntity_s *)ptr;
        atomic_store(&(entity->_runtime), (size_fast_t)0);
        ptr += alignSize;
        atomic_store(&(entity->next), (uintptr_t)ptr);
    }
    atomic_store(&(cache->head), head);
}

void XZoneCacheEnqueue(XZoneCache_s * _Nonnull cache, void * _Nonnull item) {
    XAssert(cache, "");
    XAssert(item, "");
    _Atomic(uintptr_t) * headPtr = &(cache->head);
    XMEntity_s * entity = (XMEntity_s *)item;
    atomic_store(&(entity->_runtime), (size_fast_t)0);
    uintptr_t oldHead = (uintptr_t)NULL;
    do {
        oldHead = atomic_load(headPtr);
        atomic_store(&(entity->next), oldHead);
    } while (!atomic_compare_exchange_strong(headPtr, &oldHead, (uintptr_t)entity));
}

void * _Nullable XZoneCacheDequeue(XZoneCache_s * _Nonnull cache) {
    XAssert(cache, "");
    XMEntity_s * result = NULL;
    XSpinlock_t * lock = &(cache->lock);
    _Atomic(uintptr_t) * headPtr = &(cache->head);
    uintptr_t head = atomic_load(headPtr);
    if ((uintptr_t)NULL == head) {
        return NULL;
    }
    XSpinlockLock(lock);
    head = atomic_load(headPtr);
    uintptr_t next = (uintptr_t)NULL;
    while ((uintptr_t)NULL != head) {
        XMEntity_s * entity = (XMEntity_s *)head;
        XMEntity_s * item = (XMEntity_s *)atomic_load(&(entity->next));
        if (item) {
            next = atomic_load(&(item->next));
            __XMEntityStore(entity, (uintptr_t)item, next);
            result = item;
            break;
        } else {
            // remove head
            if (atomic_compare_exchange_strong(headPtr, &head, (uintptr_t)NULL)) {
                result = (XMEntity_s *)head;
                break;
            }
        }
        head = atomic_load(headPtr);
    }
    XSpinlockUnlock(lock);
    if (result) {
        if ((XMEntity_s *)head != result) {
            __XMEntityStore(result, next, (uintptr_t)NULL);
        }
        size_fast_t _runtime = atomic_load(&(result->_runtime));
        XAssert(_runtime == 0, "");
    }
    return result;
}

#pragma mark - config

typedef struct {
    size_t block2;
    size_t block3Pair5;
    size_t block4;
} XZoneConfig_s;

// 4m / 8k / 16 = 32
static XZoneConfig_s __XZoneConfigShared = {
    .block2 = 6 * 8 * 1024,
    .block3Pair5 = 1 * 8 * 1024,
    .block4 = 3 * 8 * 1024,
};

void __XZoneDefaultConfigInit(void) {
    // read config
}

#pragma mark - manager

#define XZoneDefaultId 0
#define XZoneStaticId 1
#define XZoneWord4Id 4

typedef struct {
    size_t zoneCount;
    size_t tinyMemSize;
    uint8_t * _Nonnull tinyMem;
    const XZone_s zones[XZoneInfoMax + 1];
    XZoneCache_s caches[4];
} XZoneManager_s;

static inline const XZone_s * _Nonnull XZoneManagerGetZone(XZoneManager_s * _Nonnull manager, size_t id) {
    if (id >= manager->zoneCount) {
        return &(manager->zones[XZoneDefaultId]);
    } else {
        return &(manager->zones[id]);
    }
}

static inline const XZone_s * _Nonnull XZoneManagerGetZoneWithBlockCount(XZoneManager_s * _Nonnull manager, size_t blockCount) {
    //
    // wcount : zoneid
    static size_t XZoneTinyMapper[6] = {
        2, 2, 2, 3, 4, 5,
    };
    if (blockCount > 5) {
        return XZoneManagerGetZone(manager, XZoneDefaultId);
    } else {
        return XZoneManagerGetZone(manager, XZoneTinyMapper[blockCount]);
    }
}

static XZoneManager_s * _Nullable __XZoneManagerShared = NULL;

static inline size_t __XZoneSizeAlign64(size_t size) {
    return (size + 63) >> 6 << 6;
}

void __XZoneManagerSharedCreate(void) {
    __XZoneDefaultConfigInit();
    size_t sizes[3] = {
        __XZoneSizeAlign64(__XZoneConfigShared.block2 * XOBJECT_BLOCK_SIZE * 2),
        __XZoneSizeAlign64(__XZoneConfigShared.block3Pair5 * XOBJECT_BLOCK_SIZE * 8),
        __XZoneSizeAlign64(__XZoneConfigShared.block4 * XOBJECT_BLOCK_SIZE * 4),
    };
    size_t memSize = 0;
    for (ssize_t i=0; i<3; i++) {
        memSize += sizes[i];
    }
    
    uint8_t * mem = (uint8_t *)XAlignedAllocate(memSize, 128);
    
    XZoneManager_s * manager = malloc(sizeof(XZoneManager_s));
    manager->tinyMem = mem;
    manager->tinyMemSize = memSize;
    manager->zoneCount = 6;

    XZoneInit((XZone_s *)&manager->zones[0], 0, 0, NULL, _XZoneDefaultAllocate, _XZoneDefaultDeallocate);
    XZoneInit((XZone_s *)&manager->zones[1], 1, 0, NULL, _XZoneStaticAllocate, _XZoneStaticDeallocate);
    
    XZoneCache_s * cache = &(manager->caches[0]);
    XZoneCacheInit(cache, 2 * XOBJECT_BLOCK_SIZE, __XZoneConfigShared.block2, 2 * XOBJECT_BLOCK_SIZE, mem);
    XZoneInit((XZone_s *)&manager->zones[2], 2, 0, cache, _XZoneTinyAllocate, _XZoneTinyDeallocate);
    mem += sizes[0];

    cache = &(manager->caches[2]);
    XZoneCacheInit(cache, 4 * XOBJECT_BLOCK_SIZE, __XZoneConfigShared.block4, 4 * XOBJECT_BLOCK_SIZE, mem);
    XZoneInit((XZone_s *)&manager->zones[4], 4, 0, cache, _XZoneTinyAllocate, _XZoneTinyDeallocate);
    mem += sizes[2];
    
    cache = &(manager->caches[1]);
    XZoneCacheInit(cache, 3 * XOBJECT_BLOCK_SIZE, __XZoneConfigShared.block3Pair5, 8 * XOBJECT_BLOCK_SIZE, mem);
    XZoneInit((XZone_s *)&manager->zones[3], 3, 0, cache, _XZoneTinyAllocate, _XZoneTinyDeallocate);
    
    cache = &(manager->caches[3]);
    XZoneCacheInit(cache, 5 * XOBJECT_BLOCK_SIZE, __XZoneConfigShared.block3Pair5, 8 * XOBJECT_BLOCK_SIZE, mem + 3 * XOBJECT_BLOCK_SIZE);
    XZoneInit((XZone_s *)&manager->zones[5], 5, 0, cache, _XZoneTinyAllocate, _XZoneTinyDeallocate);
    mem += sizes[1];
    
    printf("ZoneTiny total memSize %ld  [%p-%p]\n", memSize, manager->tinyMem, manager->tinyMem + manager->tinyMemSize);
    
    for (ssize_t i=0; i<4; i++) {
        printf("Zone(%lu).count %lu\n", manager->caches[i].objectSize, manager->caches[i].count);
    }
    __XZoneManagerShared = manager;
}

XZoneManager_s * _Nonnull XZoneManagerShared(void) {
    static pthread_once_t once = PTHREAD_ONCE_INIT;
    pthread_once(&once, __XZoneManagerSharedCreate);
    return __XZoneManagerShared;
}

typedef struct {
    uint32_t wcount[2];
    uint32_t nexts[2];
} XPairSize_s;

#define XPairSizeMake(a, b, aup, bup) {\
    .wcount = { a, b },\
    .nexts = { aup, bup },\
}

struct __XZoneStaticPage;
typedef struct __XZoneStaticPage XZoneStaticPage_s;
struct __XZoneStaticPage {
    XZoneStaticPage_s * _Nullable prev;
    XZoneStaticPage_s * _Nullable next;
    size_t capacity;
    size_t used;
    uint8_t mem[0];
};


// min-word
// chuck-count: SIZE_BITS_COUNT

// 占用2m * sizeof(size_t) / 4

// 8 * (4 + 8 + 8 + 6 + 6 + 8 + 8) = 48 * 8
typedef struct {
    uint8_t * _Nonnull mem;
} XZoneStaticData_s;

const XZone_s * _Nonnull XZoneDefault(void) {
    XZoneManager_s * manager = XZoneManagerShared();
    return XZoneManagerGetZone(manager, XZoneDefaultId);
}
const XZone_s * _Nonnull XZoneStatic(void) {
    XZoneManager_s * manager = XZoneManagerShared();
    return XZoneManagerGetZone(manager, XZoneStaticId);
}

typedef struct {
    _Atomic(uintptr_t) next;
} XSLink_s;

// 32 64

// FIFO 单个生产者-单个消费者 ringbuffer
// FIFO 多个生产者-多个消费者 link
// FIFO 多个生产者-单个消费者 link
// FIFO 单个生产者-多个消费者 link

//void * _Nullable __XZoneDefaultAllocateWithController(XZone1Data_s * _Nonnull zoneData, XZoneController_s * _Nonnull controller, size_t size, size_t * _Nonnull zoneInfo) {
//    size_t stateCount = controller->chuckCount / SIZE_BITS_COUNT;
//    for (size_t sindex=0; sindex<stateCount; sindex++) {
//        _Atomic(size_fast_t) * statePtr = controller->states + sindex;
//        size_fast_t cacheState = 0;
//        size_fast_t newCacheState = 0;
//        size_fast_t index = 0;
//        do {
//            cacheState = atomic_load(statePtr);
//            index = USizeFindFirstZero(cacheState);
//            if (index >= SIZE_BITS_COUNT) {
//                break;
//            }
//            newCacheState = cacheState | (SIZE_C(0x1) << index);
//        } while (!atomic_compare_exchange_strong(statePtr, &cacheState, newCacheState));
//        if (index < SIZE_BITS_COUNT) {
//            *zoneInfo = controller->zoneInfo;
//            return controller->mem + (sindex * SIZE_BITS_COUNT + index) * controller->alignSize;
//        }
//    }
//    size_t nextIndex = controller->nextIndex;
//    if (nextIndex < __XZone1DataSharedControllerSize) {
//        return __XZoneDefaultAllocateWithController(zoneData, &(zoneData->controllers[nextIndex]), size, zoneInfo);
//    } else {
//        return NULL;
//    }
//}
//void __XZoneDefaultDeallocateWithController(XZone1Data_s * _Nonnull zoneData, XZoneController_s * _Nonnull controller, void * _Nonnull ptr) {
//    uintptr_t p = (uintptr_t)ptr;
//    uintptr_t base = (uintptr_t)controller->mem;
//    XAssert(p >= base, "");
//    uintptr_t offset = p - base;
//    XAssert(0 == (offset % controller->alignSize), "");
//    size_t index = offset / controller->alignSize;
//    XAssert(index < controller->chuckCount, "");
//
//    _Atomic(size_fast_t) * statePtr = controller->states + index / SIZE_BITS_COUNT;
//    size_fast_t cacheState = 0;
//    size_fast_t newCacheState = 0;
//    size_fast_t shift = index % SIZE_BITS_COUNT;
//    size_fast_t bit = SIZE_C(0x1) << shift;
//    do {
//        cacheState = atomic_load(statePtr);
//        XAssert((cacheState & bit) == bit, "");
//        newCacheState = cacheState ^ bit;
//    } while (!atomic_compare_exchange_strong(statePtr, &cacheState, newCacheState));
//}



void * _Nonnull _XZoneDefaultAllocate(const XZone_s * _Nonnull zone, size_t _size) {
    void * ptr = XAlignedAllocate(_size, XOBJECT_BLOCK_SIZE);
    return ptr;
}
void _XZoneDefaultDeallocate(const XZone_s * _Nonnull zone, void * _Nonnull ptr) {
    XDeallocate(ptr);
}

void * _Nonnull _XZoneStaticAllocate(const XZone_s * _Nonnull zone, size_t _size) {
    void * ptr = XAlignedAllocate(_size, XOBJECT_BLOCK_SIZE);
    return ptr;
}
void _XZoneStaticDeallocate(const XZone_s * _Nonnull zone, void * _Nonnull ptr) {
    free(ptr);
}

void * _Nullable _XZoneTinyAllocate(const XZone_s * _Nonnull zone, size_t size) {
    XDebugAssert(zone, "");
    XZoneCache_s * cache = zone->context;
    XDebugAssert(cache, "");
    XDebugAssert(cache->objectSize >= size, "");
    return XZoneCacheDequeue(cache);
}

void _XZoneTinyDeallocate(const XZone_s * _Nonnull zone, void * _Nonnull ptr) {
    XDebugAssert(zone, "");
    XZoneCache_s * cache = zone->context;
    XDebugAssert(cache, "");
    return XZoneCacheEnqueue(cache, ptr);
}

// 128
// size / 8 - 1

/*
 RC 中放 zoneInfo, 内存字节数
 // width: 1 ~ 16, padding: 1 ~ 8; hasSign: ; float or int
 // Date(32: 24B; 64: 32b;) Number(32: 16B/24B; 64: 24B/32B) Date(32: 16B/24B; 64: 24B) String(32: 8B~128B; 64: 16B~128B) Data(32: 12B~128B; 64: 24B~128B~...)
 // 内存池: 0， 对象进入内存池之前要清0
  [16(Number, Date, Data), 24(Number), 32(Number, Date, Weak, Data), 40、48、56、64(Data, String), static]
 */
void * _Nonnull XInstanceAllocate(XAllocatorOption option, size_t size, size_t * _Nonnull zoneInfo) {
    XAssert(zoneInfo, "");
    
    const size_t blockSize = XOBJECT_BLOCK_SIZE;
    const size_t blockShift = XOBJECT_BLOCK_SIZE_SHIFT;
    
    size_t blockCount = (size + blockSize - 1) >> blockShift;
    blockCount = MAX(1, blockCount);
    size = blockCount << blockShift;
    
    XZoneManager_s * manager = XZoneManagerShared();

    const XZone_s * zone = NULL;
    if (option & XAllocatorOptionStatic) {
        zone = XZoneManagerGetZone(manager, XZoneStaticId);
    } else {
        zone = XZoneManagerGetZoneWithBlockCount(manager, blockCount);
    }
    void * result = zone->allocate(zone, size);
    *zoneInfo = zone->id;
    while (NULL == result) {
        zone = XZoneManagerGetZone(manager, zone->next);
        result = zone->allocate(zone, size);
        *zoneInfo = zone->id;
    }
    return result;
}
void XInstanceDeallocate(void * _Nonnull ptr, size_t zoneInfo) {
    XZoneManager_s * manager = XZoneManagerShared();
    const XZone_s * zone = XZoneManagerGetZone(manager, zoneInfo);
    zone->deallocate(zone, ptr);
}

void * _Nullable XAllocateFastWord4(void) {
    XZoneManager_s * manager = XZoneManagerShared();
    const XZone_s * zone = XZoneManagerGetZone(manager, XZoneWord4Id);
    return zone->allocate(zone, sizeof(size_t) * 4);
}
void XDeallocateFastWord4(void * _Nonnull ptr) {
    XZoneManager_s * manager = XZoneManagerShared();
    const XZone_s * zone = XZoneManagerGetZone(manager, XZoneWord4Id);
    zone->deallocate(zone, ptr);
}



void testZone(void) {

    
    
    
}
