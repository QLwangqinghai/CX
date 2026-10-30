
#ifndef CXBaseInternal_h
#define CXBaseInternal_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "CXBase.h"


#pragma mark - XParameterBuffer

typedef struct {
    XObjectBase_o _runtime;
    const XParameterBufferType_s * _Nonnull type;
    uint8_t buffer[0];
} _XParameterBuffer_o;

#pragma mark - XClosure

typedef struct {
    XObjectBase_o _runtime;
    const XMethod_s * _Nonnull method;
    XObjectRef _Nullable handler;
} _XClosure_o;

#pragma mark - XHashTable

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
} XHashTable_s;

// api 跟string一样 appending/removing/replacing

#pragma mark - XMap

typedef XHashTable_s _XMap_s;

#pragma mark -XSet

typedef XHashTable_s _XSet_s;

#pragma mark - XOrderedMap

typedef XHashTable_s _XOrderedMap_s;

#pragma mark - XOrderedSet

typedef XHashTable_s _XOrderedSet_s;


#if defined(__cplusplus)
}  // extern C
#endif

#endif /* CXBaseInternal_h */
