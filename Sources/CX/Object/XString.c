
#include "XObjectInternal.h"
#include <pthread.h>
#include "XRuntimeInternal.h"

#pragma mark - Common


// string 必须支持的api 获取utf8cstring， 以及length

// none notstring utf8cstring ascii

const XStringEncoding XStringEncodingUtf8 = 1;
const XStringDecodeOption XStringDecodeOptionAllowEndWith0 = 1;
const XStringDecodeOption XStringDecodeOptionAllowEndWithIllegalCharacters = 1 << 1;
const XStringDecodeOption XStringDecodeOptionAllowStartWithBom = 1 << 2;
const XStringDecodeOption XStringDecodeOptionAllowMultiBom = 1 << 3;

size_t __XDataStringInlineSizeAlign(size_t size) {
    static const size_t mask = sizeof(size_t) - 1;
    size_t s = (size + sizeof(size_t)) & (~mask);
    return s;
};


void _XStringUnpack(XPtr _Nonnull ref, _XStringUnpacked_t * _Nonnull receiver, const char * _Nonnull func, const char * _Nonnull desc) {
    XAssertFunc(receiver, func, desc);
    if (XObjectIsTaggedObject(ref)) {
        // tagged
        size_t count = 0;
        receiver->_nanoBytes = __XRTaggedStringDecode(ref, &count, func);
        receiver->length = count;
        receiver->bytes = (uint8_t *)&(receiver->_nanoBytes);
        receiver->hashCode = 0;
    } else {
        _XString_o * object = __XHeapRefAsXString(ref, func, desc);
        switch (__XHeapStringGetLayout(object)) {
            case _XStringLayoutSmall: {
                _XStringInlineContent_s * content = (_XStringInlineContent_s *)(object->content);
                receiver->length = content->length;
                receiver->bytes = content->bytes;
                receiver->_nanoBytes = 0;
                receiver->hashCode = atomic_load(&(content->hashCode));
            }
                break;
            case _XStringLayoutLarge: {
                _XStringLargeContent * content = (_XStringLargeContent *)(object->content);
                receiver->length = content->length;
                receiver->bytes = content->bytes;
                receiver->_nanoBytes = 0;
                receiver->hashCode = atomic_load(&(content->hashCode));
            }
                break;
//            case _XStringLayoutBridgeSmallCString: {
//                _XStringBridgeSmallCString * content = (_XStringBridgeSmallCString *)(object->content);
//                receiver->length = content->length;
//                receiver->bytes = content->bytes;
//                receiver->_nanoBytes = 0;
//                receiver->hashCode = atomic_load(&(content->hashCode));
//            }
//                break;
//            case _XStringLayoutBridgeLargeCString: {
//                _XStringBridgeLargeCString * content = (_XStringBridgeLargeCString *)(object->content);
//                receiver->length = content->length;
//                receiver->bytes = content->bytes;
//                receiver->_nanoBytes = 0;
//                receiver->hashCode = atomic_load(&(content->hashCode));
//            }
//                break;
            default: {
                abort();
            }
                break;
        }
    }
}


//XComparisonResult _XStringUnpackedCompare(const _XStringUnpacked_t * _Nonnull lhs, const _XStringUnpacked_t * _Nonnull rhs, const char * _Nonnull func) {
//    size_t leftLength = lhs->content.count;
//    size_t rightLength = rhs->content.count;
//    size_t size = MIN(leftLength, rightLength);
//    XComparisonResult result = XMemoryCompare((const XPtr)(lhs->content.bytes), (const XPtr)(rhs->content.bytes), size);
//    if (XCompareEqualTo == result) {
//        if (leftLength < rightLength) {
//            return XCompareLessThan;
//        } else if (leftLength > rightLength) {
//            return XCompareGreaterThan;
//        }
//    }
//    return result;
//}
//
//XComparisonResult _XDataStringCompare(const _XStringUnpacked_t * _Nonnull lhs, const _XStringUnpacked_t * _Nonnull rhs, const char * _Nonnull func) {
//    return _XStringUnpackedCompare(lhs, rhs, func);
//}

/// 外部check len 和 bytes， len < sizeof(size_t), bytes 必须是utf8字符串
XStringRef _Nonnull __XRTaggedStringCreate(const uint8_t * _Nonnull buffer, size_t length) {
    size_t bytes = 0;
    memcpy(&bytes, buffer, length);
    return __XRTaggedStringEncode(bytes, (size_t)length, __func__);
}

static inline void __XStringInlineInitData(uint8_t * _Nonnull dst, const uint8_t * _Nonnull buffer, size_t length, size_t capacity) {
    memcpy(dst, buffer, length);
    memset(dst + length, 0, capacity - length);
}
XStringRef _Nonnull __XStringSmallCreate(XObjectOption flag, const uint8_t * _Nonnull buffer, size_t length, size_t unicodeCount, size_t hashCode) {
    XAssert(length <= X_BUILD_XStringDataSmallCapacityMax, "");
    size_t capacity = __XDataStringInlineSizeAlign(length);
    _XString_o * result = __XClassStringAllocateInstance(flag, _XStringLayoutSmall, sizeof(_XString_o) + sizeof(_XStringInlineContent_s) + capacity);
    _XStringInlineContent_s * content = (_XStringInlineContent_s *)result->content;
    content->length = length;
    content->unicodeCount = unicodeCount;
    atomic_store(&(content->hashCode), hashCode);
    __XStringInlineInitData(content->bytes, buffer, length, capacity);
    return result;
}
XStringRef _Nonnull __XStringLargeCreate(XObjectOption flag, const uint8_t * _Nonnull buffer, size_t length, size_t unicodeCount, size_t hashCode) {
    XAssert(length > X_BUILD_XStringDataSmallCapacityMax, "");
    size_t capacity = __XDataStringInlineSizeAlign(length);
    _XString_o * result = __XClassStringAllocateInstance(flag, _XStringLayoutLarge, sizeof(_XString_o) + sizeof(_XStringLargeContent) + capacity);
    _XStringLargeContent * content = (_XStringLargeContent *)result->content;
    content->length = length;
    content->unicodeCount = unicodeCount;
    atomic_store(&(content->hashCode), hashCode);
    __XStringInlineInitData(content->bytes, buffer, length, capacity);
    return result;
}

XStringRef _Nonnull __XStringInlineCreate(XObjectOption flag, const uint8_t * _Nonnull buffer, size_t length, size_t unicodeCount, size_t hashCode) {
    if (length <= X_BUILD_XStringDataSmallCapacityMax) {
        return __XStringSmallCreate(flag, buffer, length, unicodeCount, hashCode);
    } else {
        return __XStringLargeCreate(flag, buffer, length, unicodeCount, hashCode);
    }
}

XStringRef _Nonnull __XStringCreateWithUtf8Bytes(XObjectOption flag, const uint8_t * _Nonnull buffer, size_t length, size_t unicodeCount, size_t hashCode, const char * _Nonnull func) {
    if (length < sizeof(size_t)) {
        size_t bytes = 0;
        memcpy(&bytes, buffer, length);
        return __XRTaggedStringEncode(bytes, (size_t)length, __func__);
    } else {
        return __XStringInlineCreate(flag, buffer, length, unicodeCount, hashCode);
    }
}

XStringRef _Nullable XStringCreateWithCString(XObjectOption flag, const char * _Nonnull cString, XStringEncoding encode) {
    XAssert(NULL != cString, "cString is NULL");
    switch (encode) {
        case XStringEncodingUtf8: {
            const uint8_t * bytes = (const uint8_t *)cString;
            XStringUtf8Layout_s layout = _XUtf8StringLayoutMakeWithCString(cString);
            if (0 == cString[layout.location + layout.length]) {
                return __XStringCreateWithUtf8Bytes(flag, bytes + layout.location, layout.length, layout.unicodeCount, 0, __func__);
            } else {
                return NULL;
            }
        }
        default:
            return NULL;
    }
}

//// 完全decode， 遇到0， 遇到非法字符
//static inline XString _Nullable ___XStringCreateByDecodeUtf8Bytes(XObjectOption flag, const uint8_t * _Nonnull bytes, size_t length, XStringDecodeOption decodeOption, const char * _Nonnull func) {
//    XAssert(NULL != bytes, "bytes is NULL");
//
//    XStringUtf8Layout_s layout = _XUtf8StringLayoutMakeWithBytes(bytes, length);
//    if (length == layout.location + layout.length) {
//        return __XStringCreateWithUtf8Bytes(flag, bytes + layout.location, layout.length, layout.unicodeCount, 0, func);
//    } else {
//        uint8_t end = bytes[layout.location + layout.length];
//        if (0 == end) {
//            if (XStringDecodeOptionAllowEndWith0 == (decodeOption & XStringDecodeOptionAllowEndWith0)) {
//                return __XStringCreateWithUtf8Bytes(flag, bytes + layout.location, layout.length, layout.unicodeCount, 0, func);;
//            } else {
//                return NULL;
//            }
//        } else {
//            if (XStringDecodeOptionAllowEndWithIllegalCharacters == (decodeOption & XStringDecodeOptionAllowEndWithIllegalCharacters)) {
//                return __XStringCreateWithUtf8Bytes(flag, bytes + layout.location, layout.length, layout.unicodeCount, 0, func);;
//            } else {
//                return NULL;
//            }
//        }
//    }
//}

static inline XStringRef _Nullable __XStringCreateWithUtf8StringLayout(XObjectOption flag, const uint8_t * _Nonnull bytes, size_t length, const XStringUtf8Layout_s * _Nonnull layout, XStringDecodeOption decodeOption, const char * _Nonnull func) {
    size_t endIndex = layout->location + layout->length;
    
    if (layout->location != 0) {
        if (0 == (decodeOption & XStringDecodeOptionAllowStartWithBom)) {
            return NULL;
        } else {
            if (0 == (decodeOption & XStringDecodeOptionAllowMultiBom)) {
                if (layout->location != _XStringUtf8BomLength) {
                    return NULL;
                }
            }
        }
    }
    if (endIndex < length) {
        uint8_t end = bytes[endIndex];
        if (0 == end) {
            if (XStringDecodeOptionAllowEndWith0 == (decodeOption & XStringDecodeOptionAllowEndWith0)) {
                return __XStringCreateWithUtf8Bytes(flag, bytes + layout->location, layout->length, layout->unicodeCount, 0, func);
            } else {
                return NULL;
            }
        } else {
            if (XStringDecodeOptionAllowEndWithIllegalCharacters == (decodeOption & XStringDecodeOptionAllowEndWithIllegalCharacters)) {
                return __XStringCreateWithUtf8Bytes(flag, bytes + layout->location, layout->length, layout->unicodeCount, 0, func);
            } else {
                return NULL;
            }
        }
    } else {
        return __XStringCreateWithUtf8Bytes(flag, bytes + layout->location, layout->length, layout->unicodeCount, 0, func);
    }
}

// 完全decode， 遇到0， 遇到非法字符
XStringRef _Nullable __XStringCreateByDecodeUtf8Bytes(XObjectOption flag, const uint8_t * _Nonnull bytes, size_t length, XStringDecodeOption decodeOption, const char * _Nonnull func) {
    XAssert(NULL != bytes, "bytes is NULL");
    
    XStringUtf8Layout_s layout = _XUtf8StringLayoutMakeWithBytes(bytes, length);
    return __XStringCreateWithUtf8StringLayout(flag, bytes, length, &layout, decodeOption, func);
}

// 完全decode， 遇到0， 遇到非法字符
XStringRef _Nullable __XStringCreateWithBytes(XObjectOption flag, const uint8_t * _Nonnull bytes, size_t length, XStringEncoding encode, XStringDecodeOption decodeOption, const char * _Nonnull func) {
    XAssert(NULL != bytes, "bytes is NULL");
    
    switch (encode) {
        case XStringEncodingUtf8:
            return __XStringCreateByDecodeUtf8Bytes(flag, bytes, length, decodeOption, func);
        default:
            return NULL;
    }
}

// 完全decode， 遇到0， 遇到非法字符
XStringRef _Nullable XStringCreateWithBytes(XObjectOption flag, const uint8_t * _Nonnull bytes, size_t length, XStringEncoding encode, XStringDecodeOption decodeOption) {
    return __XStringCreateWithBytes(flag, bytes, length, encode, decodeOption, __func__);
}

XStringRef _Nullable XStringCreateWithData(XObjectOption flag, XDataRef _Nonnull _data, XStringEncoding encode, XStringDecodeOption decodeOption) {
    XAssert(NULL != _data, "data is NULL");

    switch (encode) {
        case XStringEncodingUtf8: {
            if (XObjectIsTaggedObject(_data)) {
                // tagged
                size_t length = 0;
                size_t bin = __XRTaggedDataDecode(_data, &length, __FUNCTION__);
                uint8_t * bytes = (uint8_t *)&bin;
                return __XStringCreateByDecodeUtf8Bytes(flag, bytes, length, decodeOption, __func__);
            } else {
                _XData_o * data = _XHeapRefAsXData(_data, __func__, "ref not XDataRef");
                switch (__XHeapDataGetLayout(data)) {
                    case _XDataLayoutBridgeString: {
                        _XDataBridgeString_s * content = (_XDataBridgeString_s *)data->content;
                        XStringRef string = (XStringRef)(content->string);
                        XObjectRetain(string);
                        return string;
                    }
                    default: {
                        _XDataUnpacked_t dataContent = {};
                        _XDataUnpack(_data, &dataContent, __func__, "");
                        XStringUtf8Layout_s layout = _XRHeapDataGetUtf8StringLayout(data, __func__);
                        return __XStringCreateWithUtf8StringLayout(flag, dataContent.bytes, dataContent.length, &layout, decodeOption, __func__);
                    }
                }
            }
        }
            break;
        default:
            return NULL;
    }
}
XStringRef _Nonnull XStringCreateEmpty(void) {
    const char * empty = "";
    return XStringCreateWithCString(0, empty, XStringEncodingUtf8);
}

XStringRef _Nullable XStringCreateWithDataRange(XObjectOption flag, XDataRef _Nonnull _data, XRange_s range, XStringEncoding encode, XStringDecodeOption decodeOption) {
    XAssert(NULL != _data, "data is NULL");
    XAssert(XRangeIsValid(range), "");
    if (XRangeIsEmpty(range)) {
        return XStringCreateEmpty();
    }
    switch (encode) {
        case XStringEncodingUtf8: {
            if (XObjectIsTaggedObject(_data)) {
                // tagged
                size_t length = 0;
                size_t bin = __XRTaggedDataDecode(_data, &length, __FUNCTION__);
                XAssert(length >= range.upperBound, "");
                
                uint8_t * bytes = (uint8_t *)&bin;
                return __XStringCreateByDecodeUtf8Bytes(flag, bytes + range.lowerBound, range.upperBound - range.lowerBound, decodeOption, __func__);
            } else {
                _XData_o * data = _XHeapRefAsXData(_data, __func__, "ref not XDataRef");
                switch (__XHeapDataGetLayout(data)) {
                    case _XDataLayoutBridgeString: {
                        _XDataBridgeString_s * content = (_XDataBridgeString_s *)data->content;
                        XStringRef string = (XStringRef)(content->string);
                        _XStringUnpacked_t stringContent = {};
                        _XStringUnpack(string, &stringContent, __func__, "");
                        XAssert(stringContent.length >= range.upperBound, "");
                        if (range.lowerBound == 0 && range.upperBound == stringContent.length) {
                            return XObjectRetain(string);
                        } else {
                            return __XStringCreateByDecodeUtf8Bytes(flag, stringContent.bytes + range.lowerBound, range.upperBound - range.lowerBound, decodeOption, __func__);
                        }
                    }
                    case _XDataLayoutByte: {
                        _XDataByteContent_s * content = (_XDataByteContent_s *)(data->content);
                        XAssert(content->length >= range.upperBound, "");
                        return __XStringCreateByDecodeUtf8Bytes(flag, content->bytes + range.lowerBound, range.upperBound - range.lowerBound, decodeOption, __func__);
                    }
                    default: abort();
                }
            }
        }
            break;
        default:
            return NULL;
    }
}


static inline ssize_t _XHeapStringGetUnicodeCount(_XString_o * _Nonnull ref, const char * _Nonnull func) {
    switch (__XHeapStringGetLayout(ref)) {
        case _XStringLayoutSmall: {
            _XStringInlineContent_s * content = (_XStringInlineContent_s *)ref->content;
            return content->unicodeCount;
        }
        case _XStringLayoutLarge: {
            _XStringLargeContent * content = (_XStringLargeContent *)ref->content;
            return content->unicodeCount;
        }
        default: {
            abort();
        }
    }
}
ssize_t XStringGetUnicodeCount(XObjectRef _Nonnull ref) {
    XAssertFunc(ref, __func__, "ref Null error");
    if (XObjectIsTaggedObject(ref)) {
        // tagged
        size_t len = 0;
        size_t bytes = __XRTaggedStringDecode(ref, &len, __FUNCTION__);
        XStringUtf8Layout_s scanInfo = _XUtf8StringLayoutMakeWithBytes((uint8_t *)&bytes, len);
        XAssert(0 == scanInfo.location, "");
        XAssert(len == scanInfo.length, "");
        return scanInfo.unicodeCount;
    } else {
        _XString_o * object = __XHeapRefAsXString(ref, __func__, "ref not XString");
        return _XHeapStringGetUnicodeCount(object, __func__);
    }
}

void XStringEnumerateUnicode(XStringRef _Nonnull self, XStringEnumerateUnicode_f _Nonnull func, void * _Nullable context) {
    if (XObjectIsTaggedObject(self)) {
        // tagged
        size_t len = 0;
        size_t _bytes = __XRTaggedStringDecode(self, &len, __FUNCTION__);
        const uint8_t * bytes = (const uint8_t *)&_bytes;
        
        uint32_t chars[SIZE_BITS_COUNT] = {};
        ssize_t cindex = 0;
        const uint8_t * s = bytes;
        const uint8_t * s_end = bytes + len;
        while (s < s_end) {
          /* Keep in sync with unistr.h and u8-mbtouc-aux.c.  */
            uint8_t c = *s;

            if (c == 0) {
                abort();
            }
            if (c < 0x80) {
                s++;
                chars[cindex] = c;
                cindex += 1;
                continue;
            }
            // 110 
            if (0xC0 == (c & 0xE0)) {
                XAssert(s + 2 <= s_end && 0x80 == (s[1] & 0xC0), "");
                chars[cindex] = (((uint32_t)(c & 0x1f)) << 6) | (s[1] & 0x3f);
                cindex += 1;
                s += 2;
                continue;
            } else if (0xE0 == (c & 0xF0)) {
                XAssert(s + 3 <= s_end && 0x80 == (s[1] & 0xC0) && 0x80 == (s[2] & 0xC0), "");
                chars[cindex] = (((uint32_t)(c & 0xf)) << 12) | (((uint32_t)(s[1] & 0x3f)) << 6) | (((uint32_t)(s[2] & 0x3f)));
                cindex += 1;
                s += 3;
                continue;
            } else if (c < 0xf8) {
                XAssert(s + 4 <= s_end && 0x80 == (s[1] & 0xC0) && 0x80 == (s[2] & 0xC0) && 0x80 == (s[3] & 0xC0), "");
                chars[cindex] = (((uint32_t)(c & 0x7)) << 18) | (((uint32_t)(s[1] & 0x3f)) << 12) | (((uint32_t)(s[2] & 0x3f)) << 6) | (((uint32_t)(s[3] & 0x3f)));
                cindex += 1;
                s += 4;
                continue;
            }
            abort();
        }
        
        for (ssize_t index=0; index<cindex; index++) {
            bool_t stop = false;
            func(index, chars[index], context, &stop);
            if (stop) {
                return;
            }
        }
    } else {
        size_t layout = XObjectCheckGetLayout(self, XStringClass);
        _XString_o * string = (_XString_o *)self;
        ssize_t length = 0;
        ssize_t count = 0;
        const uint8_t * bytes = NULL;
        switch (layout) {
            case _XStringLayoutSmall: {
                _XStringInlineContent_s * content = (_XStringInlineContent_s *)(string->content);
                length = content->length;
                bytes = content->bytes;
                count = content->unicodeCount;
            }
                break;
            case _XStringLayoutLarge: {
                _XStringLargeContent * content = (_XStringLargeContent *)(string->content);
                length = content->length;
                bytes = content->bytes;
                count = content->unicodeCount;
            }
                break;
            default: {
                abort();
            }
                break;
        }
        uint32_t uchar = 0;
        ssize_t cindex = 0;
        const uint8_t * s = bytes;
        const uint8_t * s_end = bytes + length;
        bool_t stop = false;
        while (s < s_end && !stop) {
          /* Keep in sync with unistr.h and u8-mbtouc-aux.c.  */
            uint8_t c = *s;
            XAssert(cindex < count, "");
            if (c == 0) {
                abort();
            }
            if (c < 0x80) {
                s++;
                uchar = c;
                func(cindex, uchar, context, &stop);
                cindex += 1;
                continue;
            }
            // 110
            if (0xC0 == (c & 0xE0)) {
                XAssert(s + 2 <= s_end && 0x80 == (s[1] & 0xC0), "");
                uchar = (((uint32_t)(c & 0x1f)) << 6) | (s[1] & 0x3f);
                func(cindex, uchar, context, &stop);
                cindex += 1;
                s += 2;
                continue;
            } else if (0xE0 == (c & 0xF0)) {
                XAssert(s + 3 <= s_end && 0x80 == (s[1] & 0xC0) && 0x80 == (s[2] & 0xC0), "");
                uchar = (((uint32_t)(c & 0xf)) << 12) | (((uint32_t)(s[1] & 0x3f)) << 6) | (((uint32_t)(s[2] & 0x3f)));
                func(cindex, uchar, context, &stop);
                cindex += 1;
                s += 3;
                continue;
            } else if (c < 0xf8) {
                XAssert(s + 4 <= s_end && 0x80 == (s[1] & 0xC0) && 0x80 == (s[2] & 0xC0) && 0x80 == (s[3] & 0xC0), "");
                uchar = (((uint32_t)(c & 0x7)) << 18) | (((uint32_t)(s[1] & 0x3f)) << 12) | (((uint32_t)(s[2] & 0x3f)) << 6) | (((uint32_t)(s[3] & 0x3f)));
                func(cindex, uchar, context, &stop);
                cindex += 1;
                s += 4;
                continue;
            }
            abort();
        }
    }
}


size_t __XHeapStringGetLength(_XString_o * _Nonnull ref, const char * _Nonnull func) {
    XAssertFunc(ref, func, "ref Null error");
    switch (__XHeapStringGetLayout(ref)) {
        case _XStringLayoutSmall: {
            _XStringInlineContent_s * content = (_XStringInlineContent_s *)ref->content;
            return content->length;
        }
        case _XStringLayoutLarge: {
            _XStringLargeContent * content = (_XStringLargeContent *)ref->content;
            return content->length;
        }
//        case _XStringLayoutBridgeSmallCString: {
//            _XStringBridgeSmallCString * content = (_XStringBridgeSmallCString *)ref->content;
//            return content->length;
//        }
//        case _XStringLayoutBridgeLargeCString: {
//            _XStringBridgeLargeCString * content = (_XStringBridgeLargeCString *)ref->content;
//            return content->length;
//        }
        default: {
            abort();
        }
    }
}
ssize_t XStringGetUtf8Length(XObjectRef _Nonnull ref) {
    if (XObjectIsTaggedObject(ref)) {
        // tagged
        size_t len = 0;
        __XRTaggedStringDecode(ref, &len, __FUNCTION__);
        return (ssize_t)len;
    } else {
        _XString_o * object = __XHeapRefAsXString(ref, __func__, "ref not XString");
        return (ssize_t)__XHeapStringGetLength(object, __func__);
    }
}

void XStringGetBytes(XObjectRef _Nonnull ref, ssize_t location, ssize_t length, void * _Nonnull buffer) {
    _XStringUnpacked_t string = {};
    _XStringUnpack(ref, &string, __func__, "");
    XAssert(location >= 0, "");
    XAssert(length >= 0, "");
    XAssert(location + length >= string.length, "");
    memcpy(buffer, string.bytes + location, length);
}


/// 返回负数表示不是utf8
XStringUtf8Layout_s __XHeapStringGetUtf8StringLayout(_XString_o * _Nonnull ref, const char * _Nonnull func) {
    switch(__XHeapStringGetLayout(ref)) {
        case _XStringLayoutSmall: {
            _XStringInlineContent_s * content = (_XStringInlineContent_s *)ref->content;
            return XStringUtf8LayoutMake(0, content->length, content->unicodeCount);
        }
        case _XStringLayoutLarge: {
            _XStringLargeContent * content = (_XStringLargeContent *)ref->content;
            return XStringUtf8LayoutMake(0, content->length, content->unicodeCount);
        }
//        case _XStringLayoutBridgeSmallCString: {
//            _XStringBridgeSmallCString * content = (_XStringBridgeSmallCString *)ref->content;
//            return XStringUtf8LayoutMake(0, content->length, content->unicodeCount);
//        }
//        case _XStringLayoutBridgeLargeCString: {
//            _XStringBridgeLargeCString * content = (_XStringBridgeLargeCString *)ref->content;
//            return XStringUtf8LayoutMake(0, content->length, content->unicodeCount);
//        }
        default:
            XAssert(false, "error XDataRef");
    }
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

size_t __XStringGetHashCodeWithCache(_Atomic(size_fast_t) * _Nonnull cache, const uint8_t * _Nonnull bytes, size_t count, const char * _Nonnull func) {
    size_fast_t hashCode = atomic_load(cache);
    if (0 == hashCode) {
        hashCode = _XStringDataByteHash(bytes, count);
        _XUpdateTwoValuedAtomicVariable(cache, hashCode, 0, func);
    }
    return hashCode;
}

size_t __XStringGetHashCode(_XString_o * _Nonnull ref, const char * _Nonnull func) {
    switch(__XHeapStringGetLayout(ref)) {
        case _XStringLayoutSmall: {
            _XStringInlineContent_s * content = (_XStringInlineContent_s *)ref->content;
            return __XStringGetHashCodeWithCache(&(content->hashCode), content->bytes, content->length, func);
        }
        case _XStringLayoutLarge: {
            _XStringLargeContent * content = (_XStringLargeContent *)ref->content;
            return __XStringGetHashCodeWithCache(&(content->hashCode), content->bytes, content->length, func);
        }
//        case _XStringLayoutBridgeSmallCString: {
//            _XStringBridgeSmallCString * content = (_XStringBridgeSmallCString *)ref->content;
//            return __XStringGetHashCodeWithCache(&(content->hashCode), content->bytes, content->length, func);
//        }
//        case _XStringLayoutBridgeLargeCString: {
//            _XStringBridgeLargeCString * content = (_XStringBridgeLargeCString *)ref->content;
//            return __XStringGetHashCodeWithCache(&(content->hashCode), content->bytes, content->length, func);
//        }
        default:
            XAssert(false, "error XDataRef");
    }
}

size_t _XStringGetHashCodeIfExisted(_XString_o * _Nonnull ref, const char * _Nonnull func) {
    switch(__XHeapStringGetLayout(ref)) {
        case _XStringLayoutSmall: {
            return 0;
        }
        case _XStringLayoutLarge: {
            _XStringLargeContent * content = (_XStringLargeContent *)ref->content;
            return atomic_load(&(content->hashCode));
        }
//        case _XStringLayoutBridgeSmallCString: {
//            _XStringBridgeSmallCString * content = (_XStringBridgeSmallCString *)ref->content;
//            return atomic_load(&(content->hashCode));
//        }
//        case _XStringLayoutBridgeLargeCString: {
//            _XStringBridgeLargeCString * content = (_XStringBridgeLargeCString *)ref->content;
//            return atomic_load(&(content->hashCode));
//        }
        default:
            XAssert(false, "error XDataRef");
    }
}

#pragma mark - XString

void _XStringDeinit(XObjectRef _Nonnull self) {

}
size_t _XStringGetHashCode(XObjectRef _Nonnull self) {
    const char * func = __func__;
    if (XObjectIsTaggedObject(self)) {
        // tagged
        size_t len = 0;
        size_t bytes = __XRTaggedStringDecode(self, &len, __FUNCTION__);
        return _XStringDataByteHash(&bytes, len);
    } else {
        _XString_o * object = __XHeapRefAsXString(self, func, "ref not XString");
        return __XStringGetHashCode(object, __func__);
    }
}
bool_t _XStringEqual(XClassRef _Nonnull self, XObjectRef _Nonnull lhs, XObjectRef _Nonnull rhs) {
    _XStringUnpacked_t lhsv = {};
    _XStringUnpack(lhs, &lhsv, __func__, "");

    _XStringUnpacked_t rhsv = {};
    _XStringUnpack(rhs, &rhsv, __func__, "");

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
void _XStringDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}
void _XStringDebugDescribe(XObjectRef _Nonnull self, _XDescriptionBuffer _Nonnull buffer) {}


size_t _XStringGetInstanceSize(XObjectRef _Nonnull self) {
    _XString_o * object = __XHeapRefAsXString(self, __func__, "");
    switch (__XHeapStringGetLayout(object)) {
        case _XStringLayoutSmall: {
            _XStringInlineContent_s * content = (_XStringInlineContent_s *)(object->content);
            return XAllocatorAlignedSize(sizeof(_XString_o) + sizeof(_XStringInlineContent_s) + content->length + 1);
        }
        case _XStringLayoutLarge: {
            _XStringLargeContent * content = (_XStringLargeContent *)(object->content);
            return XAllocatorAlignedSize(sizeof(_XString_o) + sizeof(_XStringLargeContent) + content->length + 1);
        }
//            case _XStringLayoutBridgeSmallCString: {
//                _XStringBridgeSmallCString * content = (_XStringBridgeSmallCString *)(object->content);
//                receiver->length = content->length;
//                receiver->bytes = content->bytes;
//                receiver->_nanoBytes = 0;
//                receiver->hashCode = atomic_load(&(content->hashCode));
//            }
//                break;
//            case _XStringLayoutBridgeLargeCString: {
//                _XStringBridgeLargeCString * content = (_XStringBridgeLargeCString *)(object->content);
//                receiver->length = content->length;
//                receiver->bytes = content->bytes;
//                receiver->_nanoBytes = 0;
//                receiver->hashCode = atomic_load(&(content->hashCode));
//            }
//                break;
        default: return XAllocatorAlignedSize(sizeof(_XString_o));
    }
}
