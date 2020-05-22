//
//  XAllocator.h
//  
//
//  Created by vector on 2020/4/4.
//

#ifndef XAllocator_h
#define XAllocator_h


#if defined(__cplusplus)
extern "C" {
#endif

#include "XType.h"
#include "XRuntime.h"

    
    /*
     流传状态
     
     >= rcBase 的才可以retain
     
     0  -> rcBase -> hasWeak -> retain -> release -> release ->
     
     
     */
    
    /* compressed == 1
     counter
     type: 6
     compressed: 1
     */
    
#define X_BUILD_CompressedRcMask X_BUILD_UInt(0x1)
#define X_BUILD_CompressedRcFlag X_BUILD_UInt(0x1)
    
#define X_BUILD_CompressedRcTypeMask X_BUILD_UInt(0x7E)
#define X_BUILD_CompressedRcTypeShift X_BUILD_UInt(0x1)
#define X_BUILD_CompressedTypeWeakStorageRcFlag (X_BUILD_CompressedType_WeakStorage << X_BUILD_CompressedRcTypeShift)
    
#define X_BUILD_CompressedRcOne X_BUILD_UInt(0x80)
#define X_BUILD_CompressedRcTwo X_BUILD_UInt(0x100)
#define X_BUILD_CompressedRcBase X_BUILD_CompressedRcTwo
#define X_BUILD_CompressedRcDeallocing X_BUILD_CompressedRcOne
#define X_BUILD_CompressedRcMax (XUIntMax - X_BUILD_UInt(0x7F))
    
    
    
    /* compressed == 0
     counter
     weak: 1
     compressed: 1
     */
    
#define X_BUILD_RcHasWeakMask X_BUILD_UInt(0x2)
#define X_BUILD_RcHasWeakFlag X_BUILD_UInt(0x2)
    
#define X_BUILD_RcOne X_BUILD_UInt(0x4)
#define X_BUILD_RcTwo X_BUILD_UInt(0x8)
    
#define X_BUILD_RcBase X_BUILD_RcTwo

//析构中， 不允许retain
#define X_BUILD_RcDeallocing X_BUILD_RcOne
    
    
#define X_BUILD_RcMax (XUIntMax - X_BUILD_UInt(0x3))

    

#pragma pack(push, 1)

typedef struct _XAllocator _XAllocator_s;

typedef XPtr _Nonnull (*_XAllocate_f)(_XAllocatorPtr _Nonnull allocator, XSize size);
typedef void (*_XDeallocate_f)(_XAllocatorPtr _Nonnull allocator, XPtr _Nonnull ptr);

struct _XAllocator {
    void * _Nullable context;
    XUInt headerSize;
    _XAllocate_f _Nonnull allocate;
    _XDeallocate_f _Nonnull deallocate;
    
    XRefAllocate_f _Nonnull allocateRef;
    XRefDeallocate_f _Nonnull deallocateRef;
};

#pragma pack(pop)

//静态class
extern const _XAllocator_s _XConstantClassAllocator;

//Boolean Null
extern const _XAllocator_s _XConstantValueAllocator;



/*
 _XCompressedValueClassMake(Number),
 _XCompressedValueClassMake(String),
 _XCompressedValueClassMake(Data),
 _XCompressedValueClassMake(Date),
 _XCompressedValueClassMake(Value),
 _XCompressedValueClassMake(Storage),
 _XCompressedValueClassMake(Array),
 _XCompressedValueClassMake(Map),
 _XCompressedValueClassMake(Set),
 */
extern const _XAllocator_s _XCompressedObjectAllocator;
extern const _XAllocator_s _XCompressedValueAllocator;

extern const _XAllocator_s _XObjectAllocator;
extern const _XAllocator_s _XValueAllocator;


//动态class not support
//extern const _XAllocator_s _XClassAllocator;


extern const _XAllocator_s _XWeakStorageAllocator;


XRef _Nonnull _XRefRetain(XRef _Nonnull ref, const char * _Nonnull func);
void _XRefRelease(XRef _Nonnull ref, const char * _Nonnull func);


#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XAllocator_h */
