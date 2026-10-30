
#include "XObjectInternal.h"
#include <pthread.h>
#include "XRuntimeInternal.h"

static const ssize_t _XDataMaxCount = (ssize_t)(SIZE_MAX >> 1);

#pragma mark - internal & fileprivate

size_t __XHeapDataGetLayout(_XData_o * _Nonnull ref) {
    return __XHeapObjectGetLayout(ref);
}

size_t __XHeapDataGetLength(_XData_o * _Nonnull ref, const char * _Nonnull func) {
    switch(__XHeapDataGetLayout(ref)) {
        case _XDataLayoutByte: {
            _XDataByteContent_s * content = (_XDataByteContent_s *)(ref->content);
            return content->length;
        }
        case _XDataLayoutBridgeString: {
            _XDataBridgeString_s * content = (_XDataBridgeString_s *)(ref->content);
            return __XHeapStringGetLength(content->string, func);
        }
//        case _XDataLayoutBridgeByte: {
//            _XDataBridgeByte * content = (_XDataBridgeByte *)(ref->content);
//            return content->count;
//        }
        default:
            XAssert(false, "error XDataRef");
    }
}

// count <= _XDataCountMax;
static inline ssize_t __XDataCountAlign(size_t count) {
    size_t size = count;
    const size_t alignment = sizeof(size_t) - 1;
    size = (size + alignment) & (SIZE_MAX - alignment);
    return (ssize_t)size;
}

/// infoRef 只有2种值， 默认值 和新值
static void _XUpdateTwoValuedAtomicVariable(_Atomic(size_fast_t) * _Nonnull ptr, size_fast_t newValue, size_fast_t defaultValue, const char * _Nonnull func) {
    XAssertFunc(newValue != defaultValue, func, "");
    size_fast_t oldValue = 0;
    do {
        oldValue = atomic_load(ptr);
        
        if (oldValue == newValue) {
            return;
        } else {
            XAssertFunc(oldValue == defaultValue, func, "");
        }
    } while (!atomic_compare_exchange_strong(ptr, &oldValue, newValue));
}


size_t _XDataGetHashCodeIfExisted(_XData_o * _Nonnull ref, const char * _Nonnull func) {
    switch(__XHeapDataGetLayout(ref)) {
        case _XDataLayoutByte: {
            _XDataByteContent_s * content = (_XDataByteContent_s *)ref->content;
            return atomic_load(&(content->hashCode));
        }
        case _XDataLayoutBridgeString: {
            _XDataBridgeString_s * content = (_XDataBridgeString_s *)(ref->content);
            XStringRef string = (XStringRef)(content->string);
            return _XStringGetHashCodeIfExisted(string, func);
        }
//        case _XDataLayoutBridgeByte: {
//            _XDataBridgeByte * content = (_XDataBridgeByte *)ref->content;
//            return atomic_load(&(content->hashCode));
//        }
        default:
            XAssert(false, "error XDataRef");
    }
}

size_t __XDataGetHashCodeWithCache(_Atomic(size_fast_t) * _Nonnull cache, const uint8_t * _Nonnull bytes, size_t count, const char * _Nonnull func) {
    size_fast_t hashCode = atomic_load(cache);
    if (0 == hashCode) {
        hashCode = _XStringDataByteHash(bytes, count);
        _XUpdateTwoValuedAtomicVariable(cache, hashCode, 0, func);
    }
    return hashCode;
}

size_t __XDataGetHashCode(_XData_o * _Nonnull ref, const char * _Nonnull func) {
    switch(__XHeapDataGetLayout(ref)) {
        case _XDataLayoutByte: {
            _XDataByteContent_s * content = (_XDataByteContent_s *)ref->content;
            return __XDataGetHashCodeWithCache(&(content->hashCode), content->bytes, content->length, func);
        }
        case _XDataLayoutBridgeString: {
            _XDataBridgeString_s * content = (_XDataBridgeString_s *)(ref->content);
            XStringRef string = (XStringRef)(content->string);
            return __XStringGetHashCode(string, func);
        }
//        case _XDataLayoutBridgeByte: {
//            _XDataBridgeByte * content = (_XDataBridgeByte *)ref->content;
//            return __XDataGetHashCodeWithCache(&(content->hashCode), content->bytes, content->count, func);
//        }
        default:
            XAssert(false, "error XDataRef");
    }
}

/// 返回负数表示不是utf8
XStringUtf8Layout_s _XRHeapDataGetUtf8StringLayout(_XData_o * _Nonnull ref, const char * _Nonnull func) {
    switch(__XHeapDataGetLayout(ref)) {
        case _XDataLayoutByte: {
            _XDataByteContent_s * content = (_XDataByteContent_s *)ref->content;
            return _XUtf8StringLayoutMakeWithBytes(content->bytes, content->length);
        }
        case _XDataLayoutBridgeString: {
            _XDataBridgeString_s * content = (_XDataBridgeString_s *)(ref->content);
            XStringRef string = (XStringRef)(content->string);
            return __XHeapStringGetUtf8StringLayout(string, func);
        }
//        case _XDataLayoutBridgeByte: {
//            _XDataBridgeByte * content = (_XDataBridgeByte *)ref->content;
//            return _XUtf8StringLayoutMakeWithBytes(content->bytes, content->count);
//        }
        default:
            XAssert(false, "error XDataRef");
    }
}

static XObjectRef _Nullable _XRTaggedDataCreate(const uint8_t * _Nullable buffer, size_t length, const char * _Nonnull func) {
    size_t bytes = 0;
    memcpy(&bytes, buffer, length);
    return __XRTaggedDataEncode(bytes, (size_t)length, __func__);
}

static inline void __XDataInitData(uint8_t * _Nonnull dst, const uint8_t * _Nonnull buffer, size_t count, size_t capacity) {
    memcpy(dst, buffer, count);
    memset(dst + count, 0, capacity - count);
}

// 对内容不做校验
static XObjectRef _Nullable __XDataCreate(XObjectOption flag, const uint8_t * _Nullable buffer, size_t length, size_t hashCode, const char * _Nonnull func) {
    if (length < sizeof(size_t)) {
        return _XRTaggedDataCreate(buffer, length, func);
    } else {
        size_t capacity = __XDataCountAlign(length);
        
        XAssert(length <= _XDataMaxCount, "");
        
        size_t size = capacity + sizeof(_XData_o) + sizeof(_XDataByteContent_s);
        _XData_o * result = __XClassDataAllocateInstance(flag, _XDataLayoutByte, size);
        _XDataByteContent_s * content = (_XDataByteContent_s *)result->content;
        content->length = length;
        atomic_store(&(content->hashCode), hashCode);
        __XDataInitData(content->bytes, buffer, length, capacity);
        return result;
    }
}

XObjectRef _Nonnull _XDataCreateWithStringContentUtf8Bytes(XObjectOption flag, const uint8_t * _Nullable buffer, size_t length, size_t unicodeCount, size_t hashCode, const char * _Nonnull func) {

    XAssertFunc(length <= _XDataMaxCount, func, "count too large");
    XAssert(unicodeCount <= length, "");
    return __XDataCreate(flag, buffer, length, hashCode, __func__);
}

XObjectRef _Nonnull __XDataCreateWithString(XObjectOption flag, _XString_o * _Nullable string, const char * _Nonnull func) {
    size_t size = sizeof(_XData_o);
    _XData_o * result = __XClassDataAllocateInstance(flag, _XDataLayoutBridgeString, size);
    XObjectRetain(string);
    _XDataBridgeString_s * content = (_XDataBridgeString_s *)(result->content);
    content->string = string;
    return result;
}

void _XDataUnpack(XPtr _Nonnull ref, _XDataUnpacked_t * _Nonnull receiver, const char * _Nonnull func, const char * _Nonnull desc) {
    if (XObjectIsTaggedObject(ref)) {
        size_t count = 0;
        receiver->_nanoBytes = __XRTaggedDataDecode(ref, &count, func);
        receiver->length = count;
        receiver->bytes = (uint8_t *)&(receiver->_nanoBytes);
        receiver->hashCode = 0;
    } else {
        _XData_o * object = _XHeapRefAsXData(ref, func, desc);
        receiver->_nanoBytes = 0;
        
        switch(__XHeapDataGetLayout(object)) {
            case _XDataLayoutByte: {
                _XDataByteContent_s * content = (_XDataByteContent_s *)object->content;
                receiver->bytes = content->bytes;
                receiver->length = content->length;
                receiver->hashCode = atomic_load(&(content->hashCode));
            }
                break;
            case _XDataLayoutBridgeString: {
                _XDataBridgeString_s * content = (_XDataBridgeString_s *)(object->content);
                _XStringUnpacked_t string = {};
                _XStringUnpack(content->string, &string, func, "");
                receiver->_nanoBytes = string._nanoBytes;
                receiver->bytes = string.bytes;
                receiver->length = string.length;
                receiver->hashCode = string.hashCode;
            }
                break;
//            case _XDataLayoutBridgeByte: {
//                _XDataBridgeByte * content = (_XDataBridgeByte *)object->content;
//                receiver->bytes = content->bytes;
//                receiver->count = content->count;
//                receiver->hashCode = atomic_load(&(content->hashCode));
//            }
//                break;
            default:
                XAssert(false, "error XDataRef");
                
        }
    }
}

#pragma mark - public

ssize_t XDataGetMaxCount(void) {
    return _XDataMaxCount;
}
ssize_t XDataGetLength(XObjectRef _Nonnull ref) {
    const char * func = __func__;
    if (XObjectIsTaggedObject(ref)) {
        size_t len = 0;
        __XRTaggedDataDecode(ref, &len, __func__);
        return (ssize_t)len;
    } else {
        return (ssize_t)__XHeapDataGetLength(ref, func);
    }
}

void XDataGetBytes(XObjectRef _Nonnull ref, ssize_t location, ssize_t length, void * _Nonnull buffer) {
    _XDataUnpacked_t data = {};
    _XDataUnpack(ref, &data, __func__, "");
    XAssert(location >= 0, "");
    XAssert(length >= 0, "");
    XAssert(location + length >= data.length, "");
    memcpy(buffer, data.bytes + location, length);
}

XDataRef _Nonnull XDataCreate(XObjectOption flag, const uint8_t * _Nullable bytes, ssize_t count) {
    XAssertFunc(count <= _XDataMaxCount, __func__, "count too large");
    XAssert(count >= 0, "");
    return __XDataCreate(flag, bytes, (size_t)count, 0, __func__);
}

XDataRef _Nullable XDataCreateWithStringUtf8Encoding(XObjectOption flag, XStringRef _Nonnull string) {
    XAssertFunc(string, __func__, "string Null error");
    
    if (XObjectIsTaggedObject(string)) {
        // tagged
        size_t count = 0;
        size_t binary = __XRTaggedStringDecode(string, &count, __func__);
        return __XRTaggedDataEncode(binary, count, __func__);
    } else {
        _XString_o * object = __XHeapRefAsXString(string, __func__, "string not XString");
        _XStringUnpacked_t stringu = {};
        _XStringUnpack(object, &stringu, __func__, "");
        if (stringu.length <= X_BUILD_XStringDataSmallCapacityMax) {
            return __XDataCreate(flag, stringu.bytes, stringu.length, stringu.hashCode, __func__);
        } else {
            return __XDataCreateWithString(flag, string, __func__);
        }
    }
}

#pragma mark - private

bool_t __XDataEqual(XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs, const char * _Nonnull func) {
    _XDataUnpacked_t lhsv = {};
    _XDataUnpack(lhs, &lhsv, func, "");

    _XDataUnpacked_t rhsv = {};
    _XDataUnpack(rhs, &rhsv, func, "");
    
    size_t count = lhsv.length;
    if (count != rhsv.length) {
        return false;
    }
    if (lhsv.hashCode != 0 && rhsv.hashCode != 0) {
        if (lhsv.hashCode != rhsv.hashCode) {
            return false;
        }
    }
    
    size_t blockCount = __XDataGetUIntBlockCount(count);
    size_t * lp = (size_t *)lhsv.bytes;
    size_t * rp = (size_t *)rhsv.bytes;

    for (size_t i=0; i<blockCount; i++) {
        if (*lp != *rp) {
            return false;
        }
        lp ++;
        rp ++;
    }
    return true;
}


#pragma mark - runtime

void _XDataDeinit(XObjectRef _Nonnull self) {
//    _XData * object = (_XData *)self;
//    size_t capacity = __XDataCountAlign(object->count);
//    switch(object->layout) {
//        case _XDataLayoutSmall: {
//            // 在dealloc 中清0
//            object->layout = 0;
//            return sizeof(_XData) + capacity;
//        }
//        case _XDataLayoutMedium: {
//            object->layout = 0;
//            object->count = 0;
//            memset(object->content, 0, capacity + sizeof(_XDataMediumContent));
//            return sizeof(_XData) + sizeof(_XDataMediumContent) + capacity;
//        }
//        case _XDataLayoutByte: {
//            object->layout = 0;
//            object->count = 0;
//            memset(object->content, 0, capacity + sizeof(_XDataByteContent_s));
//            return sizeof(_XData) + sizeof(_XDataByteContent_s) + capacity;
//        }
//        default:
//            XAssert(false, "error XDataRef");
//    }
}
size_t _XDataGetHashCode(XObjectRef _Nonnull self) {
    const char * func = __func__;
    XAssertFunc(self, func, "ref Null error");
    
    if (XObjectIsTaggedObject(self)) {
        size_t len = 0;
        size_t bytes = __XRTaggedDataDecode(self, &len, __FUNCTION__);
        return _XStringDataByteHash(&bytes, len);
    } else {
        _XData_o * object = _XHeapRefAsXData(self, func, "ref not XDataRef");
        return __XDataGetHashCode(object, __func__);
    }
}
bool_t _XDataEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    return __XDataEqual(lhs, rhs, __func__);
}
void _XDataDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XDataDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}

size_t _XDataGetInstanceSize(XObjectRef _Nonnull self) {
    _XData_o * object = _XHeapRefAsXData(self, __func__, "");
    switch(__XHeapDataGetLayout(self)) {
        case _XDataLayoutByte: {
            _XDataByteContent_s * content = (_XDataByteContent_s *)object->content;
            return XAllocatorAlignedSize(sizeof(_XData_o) + sizeof(_XDataByteContent_s) + content->length);
        }
        case _XDataLayoutBridgeString: {
            return XAllocatorAlignedSize(sizeof(_XData_o) + sizeof(_XDataBridgeString_s));
        }
//        case _XDataLayoutBridgeByte: {
//            _XDataBridgeByte * content = (_XDataBridgeByte *)object->content;
//            receiver->bytes = content->bytes;
//            receiver->count = content->count;
//            receiver->hashCode = atomic_load(&(content->hashCode));
//        }
//            break;
        default:
            return XAllocatorAlignedSize(sizeof(_XData_o));
    }
    
}
