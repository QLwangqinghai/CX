
#ifndef XHashTable_h
#define XHashTable_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "CXBaseInternal.h"
#include "XCollection.h"
#include "XBasicHash.h"

typedef struct {
    XObjectBase_o _runtime;
    size_t count;
#if CX_TARGET_RT_64_BIT
    size_t bucketCount: 52;
    size_t bucketIndexShift: 6;
    size_t pageCapacityExponent: 6;
#else
    size_t bucketCount: 22;
    size_t bucketIndexShift: 5;
    size_t pageCapacityExponent: 5;
#endif
    
    XDeque_s * _Nullable storage;
    /// hash+二分查找
} XMutableHashTable_s;

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
        
//    // bucket head 的索引位置, 环形区域， 放的是startIndex
//    ssize_t bucketIndexs[0];
//
//    // elements
//    uint8_t elements[0];
    /// hash+二分查找
} XImmutableHashTable_s;

extern void XImmutableHashTableDeinit(XImmutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit);

typedef void (*XHashTableEnumerate_f)(ssize_t index, void * _Nonnull element, void * _Nullable subfunc, void * _Nullable context, bool_t * _Nonnull stop);

extern ssize_t XImmutableHashTableGetCount(XImmutableHashTable_s * _Nonnull table);

/// return unretained object
extern bool_t XImmutableHashTableGetElement(XImmutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer);

extern void XImmutableHashTableEnumerate(XImmutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context);


extern XMutableHashTable_s * _Nonnull XMutableHashTableCreate(XClassRef _Nonnull class, XObjectOption option, const XHashElementType_s * _Nonnull elementType, ssize_t capacity);

extern void XMutableHashTableDeinit(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, _XHashElementElementDeinit_f _Nonnull deinit);

extern ssize_t XMutableHashTableGetCount(XMutableHashTable_s * _Nonnull table);

extern bool_t XMutableHashTableGetElement(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, void * _Nonnull elementBuffer);

// update value, 如果有oldElement， 返回true
extern bool_t XMutableHashTableReplace(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull element, void * _Nullable oldElementBuffer);

// 如果有oldElement， 返回true
extern bool_t XMutableHashTableRemove(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, void * _Nonnull keyBuffer, bool_t allowReduceCapacity, void * _Nullable oldElementBuffer);

extern XImmutableHashTable_s * _Nonnull XMutableHashTableRemoveAll(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, bool_t allowReduceCapacity, XObjectOption option);

extern void XMutableHashTableEnumerate(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XHashTableEnumerate_f _Nonnull func, void * _Nullable subfunc, void * _Nullable context);

extern XImmutableHashTable_s * _Nonnull XMutableHashTableCopy(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, XObjectOption option, _XHashElementElementCopy_f _Nonnull copy);

extern void XMutableHashTableResize(XMutableHashTable_s * _Nonnull table, const XHashElementType_s * _Nonnull elementType, ssize_t minCapacity);

#if defined(__cplusplus)
}  // extern C
#endif


#endif /* XHashTable_h */
