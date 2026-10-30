
#include "XRefInternal.h"



//#pragma mark - XStructTypeByte16
//
//void _XRStructByte16Hash(XStructValue value, XHasher _Nonnull hasher) {
//    XHasherCombineByte16(hasher, value.content);
//}
//bool_t _XRStructByte16Equal(XStructValue lhs, XStructValue rhs) {
//    return XByte16Equal(lhs.content, rhs.content);
//}
//XRef _Nonnull _XRStructByte16Copy(XStructValue s) {
//    return XRStructCreateWithValue(0, s);
//}
//
//void _XRStructByte16Describe(XStructValue ref, _XDescriptionBuffer _Nonnull buffer) {}
//void _XRStructByte16DebugDescribe(XStructValue value, _XDescriptionBuffer _Nonnull buffer) {}
//
//
//const XStructType_s _XStructTypeByte16 = {
//    .size = sizeof(XByte16),
//    .name = "XByte16",
//    .copy = _XRStructByte16Copy,
//    .hash = _XRStructByte16Hash,
//    .equal = _XRStructByte16Equal,
//    .describe = _XRStructByte16Describe,
//    .debugDescribe = _XRStructByte16DebugDescribe,
//};
//
//const XStructType_s * _Nonnull XStructTypeByte16 = &_XStructTypeByte16;
//
//
//#pragma mark - XRStruct
//
//struct __XStructType;
//typedef struct __XStructType XStructType_s;
//
//
//typedef void (*XRStructDeinit_f)(XStructValue s);
//typedef XRef _Nonnull (*XRStructCopy_f)(XStructValue s);
//typedef void (*XRStructHash_f)(XStructValue lhs, XHasher _Nonnull hasher);
//typedef bool_t (*XRStructEqual_f)(XStructValue lhs, XStructValue rhs);
//
//struct __XStructType {
//    size_t size;// 结构体size， 如果size=0，则为动态size类型的struct
//    const char * _Nonnull name;
//    XRStructDeinit_f _Nullable deinit;
//    XRStructCopy_f _Nullable copy;
//    XRStructHash_f _Nullable hash;
//    XRStructEqual_f _Nullable equal;
//    XRDescribe_f _Nullable describe;
//    XRDescribe_f _Nullable debugDescribe;
//};
//
//
//static XByte16 * _Nonnull __XRefGetStructByte16Content(XRef _Nonnull ref, const char * _Nonnull func) {
//    XStructValue structValue = XRStructGetValue(ref);
//    _XRStruct * result = (_XRStruct *)_XHeapObjectAs(ref, XRTypeRStruct, func);
//    XAssert(structValue.type == XStructTypeByte16, "");
//    return structValue.content;
//}
//XRStructByte16 _Nonnull XRStructByte16Create(XObjectOption flag, XByte16 content) {
//    XRStruct structRef = XRStructCreate(flag, XStructTypeByte16, sizeof(XByte16));
//    XStructValue structValue = XRStructGetValue(structRef);
//    memcpy(structValue.content, &content, sizeof(XByte16));
//    return structRef;
//}
//XRStructByte16 _Nonnull XRStructByte16CreateWithBytes(XObjectOption flag, const uint8_t * _Nonnull content) {
//    XRStruct structRef = XRStructCreate(flag, XStructTypeByte16, sizeof(XByte16));
//    XStructValue structValue = XRStructGetValue(structRef);
//    XByte16 * c = structValue.content;
//    memcpy(c->content, content, 16);
//    return structRef;
//}
//XByte16 XRStructByte16GetValue(XRStructByte16 _Nonnull ref) {
//    XByte16 * v = __XRefGetStructByte16Content(ref, __func__);
//    return *v;
//}
//#pragma mark - XRStruct
//
//static _XRStruct * _Nonnull __XRefAsRStruct(XRef _Nonnull ref, const char * _Nonnull func) {
//    return (_XRStruct *)_XHeapObjectAs(ref, XRTypeRStruct, func);
//}
//XStructValue XRStructGetValue(XRStruct _Nonnull ref) {
//    _XRStruct * v = __XRefAsRStruct(ref, __func__);
//    return _XRStructGetConent(v);
//}
//
//XRStruct _Nonnull _XRStructCreate(XObjectOption flag, const XStructType_s * _Nonnull type, size_t size, XPtr _Nullable content) {
//    if (type->size != 0) {
//        XAssert(type->size == size, "");
//    }
//    size_t payloadSize = size;
//    if (type->size == 0) {
//        payloadSize += sizeof(size_t);
//    }
//    _XRStruct * ref = (_XRStruct *)_XRAllocate(XClassIdRStruct, sizeof(_XRStruct) + payloadSize, flag);
//    ref->content.type = type;
//
//    uint8_t * payload = ref->content.payload;
//    uint8_t * contentByte = NULL;
//    if (type->size != 0) {
//        contentByte = payload;
//    } else {
//        *(size_t *)payload = size;
//        contentByte = payload + sizeof(size_t);
//    }
//    if (content) {
//        memcpy(contentByte, content, size);
//    }
//    return ref;
//}
//
//XRStruct _Nonnull XRStructCreate(XObjectOption flag, const XStructType_s * _Nonnull type, size_t size) {
//    return _XRStructCreate(flag, type, size, NULL);
//}
//XRStruct _Nonnull XRStructCreateWithValue(XObjectOption flag, XStructValue value) {
//    return _XRStructCreate(flag, value.type, value.size, value.content);
//}
//
//#pragma mark - _XCCollection_t
//// _xinfo 31标识是否是mutable, 30标识是否并发检查, [15, 29] write, [0, 14] read
//
//static const uint32_fast_t _XCCollectionMutableFlag = 0x1 << 31;
//static const uint32_fast_t _XCCollectionMutableMask = _XCCollectionMutableFlag;
//
//static const uint32_fast_t _XCCollectionConcurrentNotCheckFlag = 0x1 << 30;
//static const uint32_fast_t _XCCollectionConcurrentNotCheckMask = _XCCollectionConcurrentNotCheckFlag;
//
//static const uint32_fast_t _XCCollectionReadMask = 0x7f;
//static const uint32_fast_t _XCCollectionReadOne = 0x1;
//
//static const uint32_fast_t _XCCollectionWriteMask = 0x7f << 15;
//static const uint32_fast_t _XCCollectionWriteOne = 0x1 << 15;
//
//
//void _XCCollectionInit(_XCCollection_t * _Nonnull collection, bool_t isMutable, bool_t concurrentCheckEnable, int32_t capacity, int32_t count, uint64_t cls) {
//    uint32_fast_t _xinfo = isMutable ? _XCCollectionMutableFlag : 0;
//    _xinfo += (concurrentCheckEnable && isMutable) ? 0 : _XCCollectionConcurrentNotCheckFlag;
//    atomic_store(&(collection->_xinfo), _xinfo);
//    collection->payloadLayout = isMutable ? 1 : 0;
//    collection->offset = 0;
//    collection->capacity = capacity;
//    collection->count = count;
//    collection->cls = cls;
//}
//
//bool_t __XCCollectionCheckConcurrent(uint32_fast_t newCount) {
//    uint32_fast_t writeCount = newCount & _XCCollectionWriteMask;
//    if (_XCCollectionConcurrentNotCheckFlag == (newCount & _XCCollectionConcurrentNotCheckMask)) {
//        return true;
//    }
//    if (writeCount == 0) {
//        return true;
//    } else {
//        if (writeCount > _XCCollectionWriteOne) {
//            return false;
//        } else {
//            return (newCount & _XCCollectionReadMask) == 0;
//        }
//    }
//}
//
//bool_t _XCCollectionBeginRead(_XCCollection_t * _Nonnull collection) {
//    _Atomic(uint32_fast_t) * counterPtr = &(collection->_xinfo);
//    uint32_fast_t count = 0;
//    uint32_fast_t newCount = 0;
//    uint32_fast_t mask = _XCCollectionReadMask;
//    uint32_fast_t one = _XCCollectionReadOne;
//    do {
//        count = atomic_load(counterPtr);
//        newCount = count;
//        if (_XCCollectionConcurrentNotCheckFlag == (count & _XCCollectionConcurrentNotCheckMask)) {
//            return true;
//        }
//        if (mask == (count & mask)) {
//            newCount = count | _XCCollectionConcurrentNotCheckFlag;
//        } else {
//            newCount = count + one;
//        }
//    } while (!atomic_compare_exchange_strong(counterPtr, &count, newCount));
//    return __XCCollectionCheckConcurrent(newCount);
//}
//bool_t _XCCollectionEndRead(_XCCollection_t * _Nonnull collection) {
//    _Atomic(uint32_fast_t) * counterPtr = &(collection->_xinfo);
//    uint32_fast_t count = 0;
//    uint32_fast_t newCount = 0;
//    uint32_fast_t mask = _XCCollectionReadMask;
//    uint32_fast_t one = _XCCollectionReadOne;
//    do {
//        count = atomic_load(counterPtr);
//        newCount = count;
//        if (_XCCollectionConcurrentNotCheckFlag == (count & _XCCollectionConcurrentNotCheckMask)) {
//            return true;
//        }
//        XAssert((count & mask) >= one, "");
//        newCount = count - one;
//    } while (!atomic_compare_exchange_strong(counterPtr, &count, newCount));
//    return __XCCollectionCheckConcurrent(newCount);
//}
//bool_t _XCCollectionBeginWrite(_XCCollection_t * _Nonnull collection) {
//    _Atomic(uint32_fast_t) * counterPtr = &(collection->_xinfo);
//    uint32_fast_t count = 0;
//    uint32_fast_t newCount = 0;
//    uint32_fast_t mask = _XCCollectionWriteMask;
//    uint32_fast_t one = _XCCollectionWriteOne;
//    do {
//        count = atomic_load(counterPtr);
//        newCount = count;
//        if (_XCCollectionConcurrentNotCheckFlag == (count & _XCCollectionConcurrentNotCheckMask)) {
//            return true;
//        }
//        if (mask == (count & mask)) {
//            newCount = count | _XCCollectionConcurrentNotCheckFlag;
//        } else {
//            newCount = count + one;
//        }
//    } while (!atomic_compare_exchange_strong(counterPtr, &count, newCount));
//    if (_XCCollectionMutableFlag != (newCount & _XCCollectionMutableMask)) {
//        return false;
//    }
//    return __XCCollectionCheckConcurrent(newCount);
//}
//bool_t _XCCollectionEndWrite(_XCCollection_t * _Nonnull collection) {
//    _Atomic(uint32_fast_t) * counterPtr = &(collection->_xinfo);
//    uint32_fast_t count = 0;
//    uint32_fast_t newCount = 0;
//    uint32_fast_t mask = _XCCollectionWriteMask;
//    uint32_fast_t one = _XCCollectionWriteOne;
//    do {
//        count = atomic_load(counterPtr);
//        newCount = count;
//        if (_XCCollectionConcurrentNotCheckFlag == (count & _XCCollectionConcurrentNotCheckMask)) {
//            return true;
//        }
//        XAssert((count & mask) >= one, "");
//        newCount = count - one;
//    } while (!atomic_compare_exchange_strong(counterPtr, &count, newCount));
//    if (_XCCollectionMutableFlag != (newCount & _XCCollectionMutableMask)) {
//        return false;
//    }
//    return __XCCollectionCheckConcurrent(newCount);
//}
//
//bool_t _XCCollectionIsMutable(_XCCollection_t * _Nonnull collection) {
//    _Atomic(uint32_fast_t) * counterPtr = &(collection->_xinfo);
//    uint32_fast_t count = count = atomic_load(counterPtr);;
//    return (_XCCollectionMutableFlag == (count & _XCCollectionMutableMask));
//}
////bool_t _XCCollectionBecomesImmutable(_XCCollection_t * _Nonnull collection) {
////    _Atomic(uint32_fast_t) * counterPtr = &(collection->_xinfo);
////    uint32_fast_t count = 0;
////    uint32_fast_t newCount = 0;
////    do {
////        count = atomic_load(counterPtr);
////        newCount = count;
////        if (_XCCollectionMutableFlag != (newCount & _XCCollectionMutableMask)) {
////            return (0 == (newCount & _XCCollectionWriteMask));
////        } else {
////            newCount = count & (~_XCCollectionMutableMask);
////        }
////    } while (!atomic_compare_exchange_strong(counterPtr, &count, newCount));
////    return (0 == (newCount & _XCCollectionWriteMask));
////}
//
//#pragma mark - XRMessage
//
//
//#pragma mark - XRMessageArray





#pragma mark - _XRIODescriptor

XRef _Nonnull _XRIODescriptorCopy(XRef _Nonnull ref) {
    XObjectRetain(ref);
    return ref;
}

void _XRIODescriptorHash(XRef _Nonnull ref, XHasher _Nonnull hasher) {
    XHasherCombineAddress(hasher, ref);
}
bool_t _XRIODescriptorEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
    return lhs == rhs;
}
size_t _XRIODescriptorDeinit(XRef _Nonnull ref, XRType _Nonnull type) {

    abort();

//    _Atomic(uint32_fast_t) * flagPtr = &(v->content.flag);
//    uint32_fast_t flag = atomic_load(flagPtr);
//    uint32_fast_t newFlag = 0;
//    do {
//        flag = atomic_load(flagPtr);
//        if ((flag & XRIODescriptorOptionClosed) == XRIODescriptorOptionClosed) {
//            return;
//        }
//        if ((flag & XRIODescriptorOptionCloseWhenDeinit) != XRIODescriptorOptionCloseWhenDeinit) {
//            return;
//        }
//        newFlag = flag | XRIODescriptorOptionClosed;
//    } while (!atomic_compare_exchange_strong(flagPtr, &flag, newFlag));
//    close(v->content.fd);
    
}
void _XRIODescriptorDescribe(XRef _Nonnull ref, _XDescriptionBuffer _Nonnull buffer) {}
void _XRIODescriptorDebugDescribe(XRef _Nonnull ref, _XDescriptionBuffer _Nonnull buffer) {}

//#pragma mark - _XRStruct
//
//XRef _Nonnull _XRStructCopy(XRef _Nonnull ref) {
//    _XRStruct * v = (_XRStruct *)ref;
//    if (v->content.type->copy) {
//        return v->content.type->copy(_XRStructGetConent(v));
//    } else {
//        return ref;
//    }
//}
//void _XRStructHash(XRef _Nonnull ref, XHasher _Nonnull hasher) {
//    _XRStruct * v = (_XRStruct *)ref;
//    if (v->content.type->hash) {
//        return v->content.type->hash(_XRStructGetConent(v), hasher);
//    } else {
//        XHasherCombineAddress(hasher, ref);
//    }
//}
//bool_t _XRStructEqual(XRef _Nonnull lhs, XRef _Nonnull rhs) {
//    _XRStruct * lhsV = (_XRStruct *)lhs;
//    _XRStruct * rhsV = (_XRStruct *)rhs;
//    if (lhs == rhs) {
//        return true;
//    }
//    if (lhsV->content.type == rhsV->content.type) {
//        if (lhsV->content.type->equal) {
//            return lhsV->content.type->equal(_XRStructGetConent(lhs), _XRStructGetConent(rhs));
//        } else {
//            return false;
//        }
//    } else {
//        return false;
//    }
//}
//size_t _XRStructDeinit(XRef _Nonnull ref, XRType _Nonnull type) {
//    _XRStruct * v = (_XRStruct *)ref;
//    
//    XStructValue structValue = _XRStructGetConent(v);
//    size_t payloadSize = structValue.size;
//    if (0 == structValue.type->size) {
//        payloadSize += sizeof(size_t);
//    }
//    if (v->content.type->deinit) {
//        v->content.type->deinit(structValue);
//    }
//    _Atomic(size_fast_t) * infoPtr = &(v->_runtime._xinfo);
//    size_fast_t info = atomic_load(infoPtr);
//    abort();
//};
//void _XRStructDescribe(XRef _Nonnull ref, _XDescriptionBuffer _Nonnull buffer) {};
//void _XRStructDebugDescribe(XRef _Nonnull ref, _XDescriptionBuffer _Nonnull buffer) {};



#pragma mark - XAllocator
