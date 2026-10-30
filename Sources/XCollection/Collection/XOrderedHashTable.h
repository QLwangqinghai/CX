
#ifndef XOrderedHashTable_h
#define XOrderedHashTable_h


#if defined(__cplusplus)
extern "C" {
#endif

#include "XBasicHash.h"

struct __XMutableOrderedHashTableNode;
typedef struct __XMutableOrderedHashTableNode XMutableOrderedHashTableNode_s;

// 40 - 48

// 256 个hash 为一个page，node为一个chuck，
// n 个page 为一个bucket
//

#define ORDERED_HASH_TABLE_CHUCK_BITS_COUNT 8
#define ORDERED_HASH_TABLE_CHUCK_MASK SIZE_C(0xFF)

_Static_assert(ORDERED_HASH_TABLE_CHUCK_BITS_COUNT >= XZoneInfoBitCount, "error");


struct __XMutableOrderedHashTableNode {
    size_t zoneInfo: ORDERED_HASH_TABLE_CHUCK_BITS_COUNT;
    
    // 作为page.head, id 位pageindex，否则为chuckindex
    size_t id: SIZE_BITS_COUNT - ORDERED_HASH_TABLE_CHUCK_BITS_COUNT;

    // pages 形成一个双向环结构
    
    // pageIndex or chuckIndex
    // page 的第一个元素， 那么为pageIndex
    // page中非head元素， 那么为chuckIndex
    
    // (pageIndex << ORDERED_HASH_TABLE_CHUCK_BITS_COUNT) + chuckIndex 为hashcode
    // page 的第一个元素 的hashcode 每次需要计算
    
    // page
    XMutableOrderedHashTableNode_s * _Nullable pagePrev;
    XMutableOrderedHashTableNode_s * _Nullable pageNext;
    
    // pageid 相同的next
    XMutableOrderedHashTableNode_s * _Nullable chuckNext;
    
    XMutableOrderedHashTableNode_s * _Nullable dprev;
    XMutableOrderedHashTableNode_s * _Nullable dnext;
    uint8_t element[0];
};

//static inline bool_t XMutableOrderedHashTableGetElement(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer) {
//    if (table->count <= 0) {
//        return false;
//    }
//    XAssert(keyBuffer, "");
//    XAssert(elementBuffer, "");
//    XAssert(table->buckets, "");
//
//    size_t elementSize = elementType->size;
//    XMutableOrderedHashTableBucket_s * buckets = table->buckets;
//
//    size_t hashCode = elementType->getKeyHashCode(keyBuffer);
//    size_t pageIndex = hashCode >> 8;
//    ssize_t bucketIndex = hashCode >> table->bucketIndexShift;
//
//    XMutableOrderedHashTableBucket_s * bucket = buckets + bucketIndex;
//
//    XMutableOrderedHashTableNode_s * page = bucket->head;
//    while (NULL != page) {
//        if (page->pageIndex == pageIndex) {
//            break;
//        } else if (page->pageIndex > pageIndex) {
//            page = NULL;
//        } else {
//            page = page->pageNext;
//        }
//    }
//
//    XMutableOrderedHashTableNode_s * node = page;
//    while (NULL != node) {
//        if (node->pageIndex != pageIndex) {
//            return false;
//        }
//        size_t elementHashCode = elementType->getKeyHashCode(node->element);
//        if (elementHashCode == hashCode) {
//            if (elementType->isKeyMatch(node->element, keyBuffer)) {
//                memcpy(elementBuffer, node->element, elementSize);
//                return true;
//            }
//            node = node->chuckNext;
//        } else if (elementHashCode > hashCode) {
//            node = NULL;
//        } else {
//            node = node->chuckNext;
//        }
//    }
//    return false;
//}



typedef struct __XMutableOrderedHashTableBucket {
    // 可以为空
    XMutableOrderedHashTableNode_s * _Nullable head;
} XMutableOrderedHashTableBucket_s;


typedef struct {
    XObjectBase_o _runtime;
    size_t count;
    
    // index hashCode element
    
} XOrderedHashTableBuilder_s;


typedef struct {
    XObjectBase_o _runtime;
    size_t count;
#if CX_TARGET_RT_64_BIT
    size_t bucketCount: 58;
    size_t bucketIndexShift: 6;
#else
    size_t bucketCount: 27;
    size_t bucketIndexShift: 5;
#endif
//    XMutableOrderedHashTableNode_s * _Nullable pageHead;
//    XMutableOrderedHashTableNode_s * _Nullable pageFoot;
    
    // pages 是个环形双端链表， 便于重新设置bucket的head
    // bucket 为什么是要指向第一个page， 便于resize， 逻辑简单清晰
    
    XMutableOrderedHashTableNode_s * _Nullable head;
    XMutableOrderedHashTableNode_s * _Nullable tail;
    XMutableOrderedHashTableBucket_s * _Nullable buckets;
    /// hash+二分查找
} XMutableOrderedHashTable_s;

typedef struct {
    // 可以为空
    void * _Nonnull element;
} XCollectionElementContainer_s;

typedef struct {
    XObjectBase_o _runtime;
    const size_t count;
    
    // size_t capacity; // capacity = (bucketCount >> 2) * 3
    
#if CX_TARGET_RT_64_BIT
    size_t bucketCount: 58;
    size_t bucketIndexShift: 6;
#else
    size_t bucketCount: 27;
    size_t bucketIndexShift: 5;
#endif
    _Atomic(size_fast_t) _hashCode;
    
    uint8_t payload[0];
    
    // array 中的元素为element的index
//   XCollectionElementContainer_s array[0]; // 指向element
    
//    // bucket head 的索引位置
//    ssize_t bucketIndexs[0];
//
//    // elements
//    uint8_t elements[0];
    /// hash+二分查找
} XImmutableOrderedHashTable_s;

typedef struct {
    
    // array 中的元素为element的index
    XCollectionElementContainer_s * _Nonnull array; // 指向element
    
    // bucket head 的索引位置
    ssize_t * _Nonnull bucketIndexs;
    
    uint8_t * _Nonnull elements;
} XImmutableOrderedHashTableContent_s;



struct __XOrderedHashTableIter;
typedef struct __XOrderedHashTableIter XOrderedHashTableIter_s;

struct __XOrderedHashTableIter {
    bool_t reverse;
    void * _Nonnull table;
    void * _Nullable (* _Nonnull next)(XOrderedHashTableIter_s * _Nonnull iter);
    intptr_t context;
};

static inline XImmutableOrderedHashTableContent_s XImmutableOrderedHashTableUnpack(XImmutableOrderedHashTable_s * _Nonnull table) {
    XCollectionElementContainer_s * array = (XCollectionElementContainer_s *)table->payload;
    ssize_t * bucketIndexs = (ssize_t *)(array + table->count);
    uint8_t * elements = (uint8_t *)(bucketIndexs + table->bucketCount);
    XImmutableOrderedHashTableContent_s content = {
        .array = array,
        .bucketIndexs = bucketIndexs,
        .elements = elements
    };
    return content;
}


extern void XImmutableOrderedHashTableDeinit(XImmutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit);

extern XMutableOrderedHashTable_s * _Nonnull XMutableOrderedHashTableCreate(XClassRef _Nonnull class, XObjectOption option, const XHashElementType_s * _Nonnull elementType, ssize_t capacity);

extern void XMutableOrderedHashTableDeinit(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit);


typedef void (*XOrderedHashTableEnumerate_f)(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable context, bool_t * _Nonnull stop);

extern ssize_t XImmutableOrderedHashTableGetCount(XImmutableOrderedHashTable_s * _Nonnull table);

/// return unretained object
extern bool_t XImmutableOrderedHashTableGetElement(XImmutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer);

extern void XImmutableOrderedHashTableEnumerate(XImmutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t reverse, XOrderedHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context);

extern XOrderedHashTableIter_s XImmutableOrderedHashTableMakeIter(XImmutableOrderedHashTable_s * _Nonnull table, bool_t reverse);


extern ssize_t XMutableOrderedHashTableGetCount(XMutableOrderedHashTable_s * _Nonnull table);

extern bool_t XMutableOrderedHashTableGetElement(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer);

// update value, 如果有oldElement， 返回true
extern bool_t XMutableOrderedHashTableReplace(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull element, void * _Nullable oldElementBuffer);

// 如果有oldElement， 返回true
extern bool_t XMutableOrderedHashTableRemove(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, bool_t allowReduceCapacity, void * _Nullable oldElementBuffer);

extern XImmutableOrderedHashTable_s * _Nonnull XMutableOrderedHashTableRemoveAll(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t allowReduceCapacity, XObjectOption option);

extern void XMutableOrderedHashTableEnumerate(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t reverse, XOrderedHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context);

extern XImmutableOrderedHashTable_s * _Nonnull XMutableOrderedHashTableCopy(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XObjectOption option, _XHashElementElementCopy_f _Nonnull copy);

extern void XMutableOrderedHashTableResize(XMutableOrderedHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, ssize_t minCapacity);

extern XOrderedHashTableIter_s XMutableOrderedHashTableMakeIter(XMutableOrderedHashTable_s * _Nonnull table, bool_t reverse);

extern void * _Nullable XOrderedHashTableIterNext(XOrderedHashTableIter_s * _Nonnull iter);



#if defined(__cplusplus)
}  // extern C
#endif


#endif /* XOrderedHashTable_h */
