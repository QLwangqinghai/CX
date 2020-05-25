//
//  XObject.c
//  
//
//  Created by vector on 2020/4/4.
//

#include "internal/XRuntimeInternal.h"
#include "XAtomic.h"
#include "internal/XAllocator.h"
#include "XMemory.h"

typedef XPtr _XDescriptionBuffer;

typedef void (*XObjectDescribe_f)(XObject _Nonnull obj, _XDescriptionBuffer buffer);
typedef XObject _Nonnull (*XObjectCopy_f)(XObject _Nonnull obj);


#pragma pack(push, 1)



#pragma pack(pop)



//typedef struct {
//    CCDomainRefType_s types[0x1000];
//    UInteger count;
//} CCDomainRefTypeTable_s;
//
//static CCDomainRefTypeTable_s _CCDomainRefTypeTable = {
//    .types = {
//        {
//            .name = "CCClosure",
//            .deinit = _CCClosureDeinit,
//        }
//        
//    },
//    .count = 1,
//};








XBool XObjectEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {

    return lhs == rhs;
};

XHashCode XObjectHash(XRef _Nonnull obj) {

    return (XHashCode)(((uintptr_t)obj) >> 4);
};

