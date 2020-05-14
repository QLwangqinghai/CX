//
//  XByteStorage.c
//  
//
//  Created by vector on 2020/4/3.
//

#include "XType.h"
#include "internal/XRuntimeInternal.h"
#include "internal/XAllocator.h"
#include "XMemory.h"

#pragma mark - _XBuffer

#define _XBufferClearWhenDeallocFlag X_BUILD_UInt(1)
#define _XBufferRcOne X_BUILD_UInt(2)
#define _XBufferRcMax (XFastUIntMax-X_BUILD_UInt(1))

_XBuffer * _Nonnull _XBufferAllocate(XPtr _Nonnull content, XUInt size, XBool clearWhenDealloc) {
    XAssert(size <= (XUIntMax - X_BUILD_UInt(0xf)), __func__, "size to large");
    XUInt bufferSize = (size + 15) & (~X_BUILD_UInt(0xf));
    _XBuffer * buffer = XAlignedAllocate(bufferSize, 16);
    buffer->size = bufferSize;
    _Atomic(XFastUInt) * rcPtr = &(buffer->_refCount);
    XFastUInt rc = _XBufferRcOne;
    if (clearWhenDealloc) {
        rc |= _XBufferClearWhenDeallocFlag;
    }
    atomic_store(rcPtr, rc);
    memcpy(&(buffer->content[0]), content, size);
    
    if (bufferSize > size) {
        memset(&(buffer->content[size]), 0, bufferSize - size);
    }
    return buffer;
}

void __XBufferDeallocate(_XBuffer * _Nonnull buffer) {
    XDeallocate(buffer);
}

XPtr _Nonnull _XBufferGetContent(_XBuffer * _Nonnull buffer) {
    assert(buffer);
    return &(buffer->content);
}


void _XBufferSetClearWhenDealloc(_XBuffer * _Nonnull buffer) {
    assert(buffer);
    _Atomic(XFastUInt) * rcInfoPtr = &(buffer->_refCount);

    XFastUInt rcInfo = 0;
    XFastUInt newRcInfo = 0;
    
    do {
        rcInfo = atomic_load(rcInfoPtr);
        if ((rcInfo & _XBufferClearWhenDeallocFlag) == _XBufferClearWhenDeallocFlag) {
            return;
        }
        assert(rcInfo >= _XBufferRcOne);
        newRcInfo = rcInfo | _XBufferClearWhenDeallocFlag;
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    return;
}


_XBuffer * _Nonnull _XBufferRetain(_XBuffer * _Nonnull buffer) {
    assert(buffer);
    _Atomic(XFastUInt) * rcInfoPtr = &(buffer->_refCount);

    XFastUInt rcInfo = 0;
    XFastUInt newRcInfo = 0;
    
    do {
        rcInfo = atomic_load(rcInfoPtr);
        if (rcInfo >= _XBufferRcMax) {
            return buffer;
        }
        assert(rcInfo >= _XBufferRcOne);
        newRcInfo = rcInfo + _XBufferRcOne;
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));

    return buffer;
}

void _XBufferRelease(_XBuffer * _Nonnull buffer) {
    assert(buffer);
    _Atomic(XFastUInt) * rcInfoPtr = &(buffer->_refCount);

    XFastUInt rcInfo = 0;
    XFastUInt newRcInfo = 0;

    do {
        rcInfo = atomic_load(rcInfoPtr);
        if (rcInfo >= _XBufferRcMax) {
            return;
        }
        assert(rcInfo >= _XBufferRcOne);
        newRcInfo = rcInfo - _XBufferRcOne;
    } while (!atomic_compare_exchange_strong(rcInfoPtr, &rcInfo, newRcInfo));
    if (newRcInfo == 0) {
        __XBufferDeallocate(buffer);
    }
}

#pragma mark - _XByteStorage

/*
 TaggedObject32

 refType: 1, value = 1
 taggedContent: {
    class: 2
    objectContent: 28 {
        len: 4
        content: 24
    }
 }
 flag: 1, value = 1
*/
/*
 TaggedObject64

 refType: 2, value = 1
 taggedContent: 61 {
    class: 2
    objectContent: 59 {
       len: 3
       content: 56
   }
 }
 flag: 1, value = 1
*/

#if BUILD_TARGET_RT_64_BIT
#define X_BUILD_TaggedByteStorageContentMask 0xFFFFFFFFFFFFFFULL
#define X_BUILD_TaggedByteStorageContentLengthMask 0x7ULL
#define X_BUILD_TaggedByteStorageContentLengthShift 57ULL
#define X_BUILD_TaggedByteStorageContentLengthMax 0x7UL
#else
#define X_BUILD_TaggedByteStorageContentMask 0xFFFFFFUL
#define X_BUILD_TaggedByteStorageContentLengthMask 0xFUL
#define X_BUILD_TaggedByteStorageContentLengthShift 25ULL
#define X_BUILD_TaggedByteStorageContentLengthMax 0x3UL
#endif




static void _XByteStorageDistory(_XByteStorage * _Nonnull storage) {
    XUInt32 length = storage->content.length;
    if (length < _XByteStorageContentBufferSizeMin) {
        size_t size = sizeof(_XByteStorageContent_t);
        if (length > 4) {
            XUInt bufferSize = (length - 1) & (~X_BUILD_UInt(0x3));
            size += bufferSize;
        }
        memset(&(storage->content), 0, size);
    } else {
        _XByteStorageContentLarge_t * content = (_XByteStorageContentLarge_t *)&(storage->content);
        _XBufferRelease(content->buffer);
        memset(&(storage->content), 0, sizeof(_XByteStorageContentLarge_t));
    }
}

_Static_assert(sizeof(_XByteStorageContent_t) == 8, "error");

static XRef _Nonnull _XByteStorageCreate(XBool isString, XObjectFlag flag, const XUInt8 * _Nullable buffer, XUInt32 length, const char * _Nonnull func) {
    if (length > 0) {
        XAssert(NULL != buffer, func, "length > 0, buffer cannot NULL");
    }
    if (length <= X_BUILD_TaggedByteStorageContentLengthMax) {
        XUInt bytes = 0;
        memcpy(&bytes, buffer, length);
        
#if BUILD_TARGET_RT_BIG_ENDIAN
        bytes = bytes >> X_BUILD_UInt(8);
#endif
        XUInt len = length;
        len = len << X_BUILD_TaggedByteStorageContentLengthShift;
        XUInt t = isString ? X_BUILD_TaggedObjectClassString : X_BUILD_TaggedObjectClassData;
        XUInt v = X_BUILD_TaggedObjectFlag | t | len | (bytes << X_BUILD_UInt(1));
        /*
         abc00000
         */
        /*
         大端
         xacb0000
         */
        /*
         小端
         0000bca
         */
        return (XRef)((uintptr_t)v);
    }

    const _XType_s * cls = isString ? _XClassString : _XClassData;
    const _XAllocator_s * allocator = (const _XAllocator_s *)(cls->base.allocator);
    XSize size = sizeof(_XByteStorageContent_t);
    
    XObjectRcFlag rcFlag = 0;
    if ((flag & XObjectFlagStatic) == XObjectFlagStatic) {
        rcFlag |= XObjectRcFlagStatic;
    }
    
    if (length >= _XByteStorageContentBufferSizeMin) {
        size += sizeof(_XByteStorageContentLarge_t) - sizeof(_XByteStorageContent_t);
        XRef ref = allocator->allocateRef(allocator, (XClass)cls, size, rcFlag);
        _XByteStorage * storage = (_XByteStorage *)ref;
        _XByteStorageContentLarge_t * storageContent = (_XByteStorageContentLarge_t *)&(storage->content);
        _XBuffer * buf = _XBufferAllocate((XPtr)buffer, length, ((flag & XObjectFlagClearWhenDealloc) == XObjectFlagClearWhenDealloc));
        storageContent->length = length;
        storageContent->offset = 0;
        storageContent->buffer = 0;
        storageContent->buffer = buf;
        atomic_store(&(storageContent->hashCode), XHash32NoneFlag);
        return ref;
    } else {
        XUInt bufferSize = 4;
        if (length > 4) {
            bufferSize = (length + 3) & (~X_BUILD_UInt(0x3));
            size += bufferSize - 4;
        }
        XRef ref = allocator->allocateRef(allocator, (XClass)cls, size, rcFlag);
        _XByteStorage * storage = (_XByteStorage *)ref;
        
        _XByteStorageContentSmall_t * storageContent = (_XByteStorageContentSmall_t *)&(storage->content);
        storageContent->length = length;
        if (length > 0) {
            memcpy(&(storageContent->extended[0]), buffer, length);
        }

        if (bufferSize > length) {
            memset(&(storageContent->extended[length]), 0, bufferSize - length);
        }
        return ref;
    }
}

static _XByteStorage * _Nonnull _XByteStorageCreateWithBuffer(XBool isString, XObjectFlag flag, _XBuffer * _Nonnull xbuffer, XUInt offset, XUInt32 length, const char * _Nonnull func) {
    XAssert(NULL != xbuffer, func, "length > 0, buffer cannot NULL");
    XAssert(length <= xbuffer->size, func, "range error");
    XAssert(offset <= xbuffer->size - length, func, "range error");
    
    const _XType_s * cls = isString ? _XClassString : _XClassData;
    const _XAllocator_s * allocator = (const _XAllocator_s *)(cls->base.allocator);
    XSize size = sizeof(_XByteStorageContent_t);
    
    XObjectRcFlag rcFlag = 0;
    if ((flag & XObjectFlagStatic) == XObjectFlagStatic) {
        rcFlag |= XObjectRcFlagStatic;
    }
    
    if (length >= _XByteStorageContentBufferSizeMin) {
        size += sizeof(_XByteStorageContentLarge_t) - sizeof(_XByteStorageContent_t);
        XRef ref = allocator->allocateRef(allocator, (XClass)cls, size, rcFlag);
        _XByteStorage * storage = (_XByteStorage *)ref;
        _XByteStorageContentLarge_t * storageContent = (_XByteStorageContentLarge_t *)&(storage->content);

        _XBuffer * buf = _XBufferRetain(xbuffer);
        if ((flag & XObjectFlagClearWhenDealloc) == XObjectFlagClearWhenDealloc) {
            _XBufferSetClearWhenDealloc(buf);
        }
        storageContent->buffer = buf;
        storageContent->offset = offset;
        storageContent->length = length;
        return ref;
    } else {
        XUInt bufferSize = 4;
        if (length > 4) {
            bufferSize = (length + 3) & (~X_BUILD_UInt(0x3));
            size += bufferSize - 4;
        }
        
        XUInt8 * buffer = &(xbuffer->content[offset]);
        XRef ref = allocator->allocateRef(allocator, (XClass)cls, size, rcFlag);
        _XByteStorage * storage = (_XByteStorage *)ref;
        _XByteStorageContentSmall_t * storageContent = (_XByteStorageContentSmall_t *)&(storage->content);
        storage->content.length = length;
        if (length > 0) {
            memcpy(&(storageContent->extended[0]), buffer, length);
        }
        if (bufferSize > length) {
            memset(&(storageContent->extended[length]), 0, bufferSize - length);
        }
        return ref;
    }
}


static _XByteStorage * _Nonnull __XRefAsByteStorage(XRef _Nonnull ref, XBool * _Nonnull isString, const char * _Nonnull func, const char * _Nonnull desc) {
    XCompressedType compressedType = XCompressedTypeNone;
    
#if BUILD_TARGET_RT_64_BIT
    __unused
#endif
    XClass info = _XRefGetUnpackedType(ref, &compressedType, func);
    
#if BUILD_TARGET_RT_64_BIT
    if (XCompressedTypeString == compressedType) {
        *isString = true;
    } else if (XCompressedTypeData == compressedType) {
        *isString = false;
    } else {
        XAssert(false, func, desc);
    }
    return (_XByteStorage *)ref;
#else
    const _XType_s * type = (const _XType_s *)info;
    
    if (type->base.identifier == _XClassTable[X_BUILD_CompressedType_String - 1].base.identifier) {
        *isString = true;
    } else if (type->base.identifier == _XClassTable[X_BUILD_CompressedType_Data - 1].base.identifier) {
        *isString = false;
    } else {
        XAssert(false, func, desc);
    }
    return (_XByteStorage *)ref;
#endif
}

XByteStorageUnpacked_t _XByteStorageUnpack(XPtr _Nonnull ref, const char * _Nonnull func, const char * _Nonnull desc) {
    XByteStorageUnpacked_t result = {};
    XTaggedType type = XRefGetTaggedType(ref);
    if (XTaggedTypeMax < type) {
        XBool isString = false;
        _XByteStorage * storage = __XRefAsByteStorage(ref, &isString, func, desc);
        result.isString = isString ? 1 : 0;
        if (storage->content.length >= _XByteStorageContentBufferSizeMin) {
            _XByteStorageContentLarge_t * storageContent = (_XByteStorageContentLarge_t *)&(storage->content);
            result.content.large = storageContent;
            result.contentType = 2;
        } else {
            _XByteStorageContentSmall_t * storageContent = (_XByteStorageContentSmall_t *)&(storage->content);
            result.content.small = storageContent;
            result.contentType = 1;
        }
        return result;
    } else {
        if (XTaggedTypeString == type) {
            result.isString = 1;
        } else if (XTaggedTypeData == type) {
            result.isString = 0;
        } else {
            XAssert(false, func, desc);
        }
        result.contentType = 0;

#if BUILD_TARGET_RT_64_BIT
        XUInt64 v = (XUInt64)((uintptr_t)ref);
        XUInt64 storageContent = (v >> 1) & X_BUILD_TaggedByteStorageContentMask;
        XUInt64 len = (v >> X_BUILD_TaggedByteStorageContentLengthShift) & X_BUILD_TaggedByteStorageContentLengthMask;
        XAssert(len <= X_BUILD_TaggedByteStorageContentLengthMax, func, "");
        
        XUInt64 bytes = storageContent;        
        /*
         abc00000
         */
        /*
         大端
         xacb0000
         */
        /*
         小端
         0000bca
         */
        
#if BUILD_TARGET_RT_BIG_ENDIAN
        bytes |= (len << 56ULL);
#else
        bytes = (bytes << 8ULL) | len;
#endif
        result.content.__nano = bytes;
        return result;
#else
        XUInt32 v = (XUInt32)((uintptr_t)ref);
        XUInt32 storageContent = (v >> 1) & X_BUILD_TaggedByteStorageContentMask;
        XUInt32 len = (v >> X_BUILD_TaggedByteStorageContentLengthShift) & X_BUILD_TaggedByteStorageContentLengthMask;
        XAssert(len <= X_BUILD_TaggedByteStorageContentLengthMax, __func__, "");
        
        XUInt32 bytes = storageContent;
#if BUILD_TARGET_RT_BIG_ENDIAN
        bytes |= (len << 24UL);
#else
        bytes = (bytes << 8ULL) | len;
#endif
        result.content.__nano = bytes;
        return result;
#endif
    }
}


XHashCode _XByteStorageHash(XRef _Nonnull ref, XBool isString, const char * _Nonnull func) {
    XAssert(NULL != ref, func, "ref NULL error");
    const char * desc = isString ? "not String instance" : "not Data instance";
    XByteStorageUnpacked_t v = _XByteStorageUnpack(ref, func, desc);
    uint32_t isStringValue = isString ? 1 : 0;
    XAssert(isStringValue == v.isString, func, desc);
    if (0 == v.contentType) {
        XUInt8 * bytes = &(v.content.nano.content[1]);
        return _XELFHashBytes(bytes, MIN(XHashEverythingLimit, v.content.nano.content[0])) & XHash32Mask;
    } else if (1 == v.contentType) {
        XUInt8 * bytes = &(v.content.small->extended[0]);
        return _XELFHashBytes(bytes, MIN(XHashEverythingLimit, v.content.small->length)) & XHash32Mask;
    } else if (2 == v.contentType) {
        XFastUInt32 hashCode = atomic_load(&(v.content.large->hashCode));
        if ((hashCode & XHash32NoneFlag) == XHash32NoneFlag) {
            XUInt8 * bytes = &(v.content.large->buffer->content[v.content.large->offset]);
            hashCode = _XELFHashBytes(bytes, MIN(XHashEverythingLimit, v.content.large->length)) & XHash32Mask;
            atomic_store(&(v.content.large->hashCode), hashCode);
        }
        return hashCode;
    } else {
        XAssert(false, func, "unknown error");
    }
}
XUInt8 * _Nonnull _XByteStorageUnpackedGetByte(XByteStorageUnpacked_t * _Nonnull ptr, XUInt32 * _Nonnull lengthPtr, const char * _Nonnull func) {
    XUInt32 length = 0;
    XUInt8 * bytes = NULL;
    if (0 == ptr->contentType) {
        bytes = &(ptr->content.nano.content[1]);
        length = ptr->content.nano.content[0];
    } else if (1 == ptr->contentType) {
        bytes = &(ptr->content.small->extended[0]);
        length = ptr->content.small->length;
    } else if (2 == ptr->contentType) {
        bytes = &(ptr->content.large->buffer->content[ptr->content.large->offset]);
        length = ptr->content.large->length;
    } else {
        XAssert(false, func, "unknown error");
    }
    *lengthPtr = length;
    return bytes;
}



XComparisonResult _XByteStorageUnpackedCompare(XByteStorageUnpacked_t * _Nonnull lhs, XByteStorageUnpacked_t * _Nonnull rhs, const char * _Nonnull func) {
    XUInt32 leftLength = 0;
    XUInt32 rightLength = 0;
    XUInt8 * left = _XByteStorageUnpackedGetByte(lhs, &leftLength, func);
    XUInt8 * right = _XByteStorageUnpackedGetByte(rhs, &rightLength, func);
    
    XSize size = MIN(leftLength, rightLength);
    
    XComparisonResult result = XMemoryCompare(left, right, size);
    if (XCompareEqualTo == result) {
        if (leftLength < rightLength) {
            return XCompareLessThan;
        } else if (leftLength > rightLength) {
            return XCompareGreaterThan;
        }
    }
    return result;
}

XBool _XByteStorageUnpackedEqual(XByteStorageUnpacked_t * _Nonnull lhs, XByteStorageUnpacked_t * _Nonnull rhs, const char * _Nonnull func) {
    XUInt32 leftLength = 0;
    XUInt32 rightLength = 0;
    XUInt8 * left = _XByteStorageUnpackedGetByte(lhs, &leftLength, func);
    XUInt8 * right = _XByteStorageUnpackedGetByte(rhs, &rightLength, func);
    if (leftLength != rightLength) {
        return false;
    }
    XSize size = leftLength;
    
    XComparisonResult result = XMemoryCompare(left, right, size);
    return (XCompareEqualTo == result);
}


XComparisonResult _XByteStorageCompare(XRef _Nonnull lhs, XRef _Nonnull rhs, XBool isString, const char * _Nonnull func) {
    XAssert(NULL != lhs, func, "lhs NULL error");
    XAssert(NULL != rhs, func, "rhs NULL error");
    
    const char * desc = isString ? "not String instance" : "not Data instance";
    XByteStorageUnpacked_t left = _XByteStorageUnpack(lhs, func, desc);
    XByteStorageUnpacked_t right = _XByteStorageUnpack(rhs, func, desc);
    uint32_t isStringValue = isString ? 1 : 0;
    XAssert(isStringValue == left.isString, func, desc);
    XAssert(isStringValue == right.isString, func, desc);
    return _XByteStorageUnpackedCompare(&left, &right, func);
}



XBool _XByteStorageEqual(XRef _Nonnull lhs, XRef _Nonnull rhs, XBool isString, const char * _Nonnull func) {
    XAssert(NULL != lhs, func, "lhs NULL error");
    XAssert(NULL != rhs, func, "rhs NULL error");

    const char * desc = isString ? "not String instance" : "not Data instance";
    XByteStorageUnpacked_t left = _XByteStorageUnpack(lhs, func, desc);
    XByteStorageUnpacked_t right = _XByteStorageUnpack(rhs, func, desc);
    uint32_t isStringValue = isString ? 1 : 0;
    XAssert(isStringValue == left.isString, func, desc);
    XAssert(isStringValue == right.isString, func, desc);

    if (2 == left.contentType && 2 == right.contentType) {
        XFastUInt32 leftHashCode = atomic_load(&(left.content.large->hashCode));
        XFastUInt32 rightHashCode = atomic_load(&(right.content.large->hashCode));
        if ((leftHashCode & XHash32NoneFlag) != XHash32NoneFlag && (rightHashCode & XHash32NoneFlag) != XHash32NoneFlag) {
            if (leftHashCode != rightHashCode) {
                return false;
            }
        }
    }
    return _XByteStorageUnpackedEqual(&left, &right, func);
}


#pragma mark - Common

typedef XUInt32 XStringEncoding;

static const XStringEncoding XStringEncodingUtf8 = 1;


#pragma mark - XString

static XRange _XRangeOfString(const XUInt8 * _Nonnull bytes, size_t length) {
    XIndex begin = 0;
    XIndex end = length;
    XIndex offset = 0;
    if (length >= 3) {
        //check bom
        if (0xEF == bytes[0] && 0xBB == bytes[1] && 0xBF == bytes[2]) {
            begin = 3;
            offset = 3;
        }
    }
    XIndex errorIndex = XIndexNotFound;
    while (length - offset > 0 && SIZE_T_MAX == errorIndex) {
        uint8_t byte = bytes[offset];
        if (byte == 0x0) {
            //终止符
            end = offset;
            break;
        } else if (byte < 0x80) {
            //1
            offset += 1;
        } else if ((byte & 0xE0) == 0xC0) {
            //2
            if (offset > length-2) {
                errorIndex = offset;
                break;
            }
            if ((byte & 0x1E) == 0) {
                //0x0080 ~ 0x07FF
                errorIndex = offset;
                break;
            }
            uint8_t tmp = bytes[offset+1];
            if ((tmp & 0xC0) == 0x80) {
                //10xxxxxx
                offset += 2;
            } else {
                errorIndex = offset;
            }
        } else if ((byte & 0xF0) == 0xE0) {
            //3
            if (offset > length-3) {
                errorIndex = offset;
                break;
            }
            
            uint16_t tmp = *(uint16_t *)(bytes + offset + 1);
            
#if BUILD_TARGET_RT_BIG_ENDIAN
            //大端
            if ((byte & 0xF) == 0 && (tmp & 0x2000) == 0) {
                //0x0800 ~ 0xFFFF
                errorIndex = offset;
                break;
            }
#else
            //小端
            if ((byte & 0xF) == 0 && (tmp & 0x20) == 0) {
                //0x0800 ~ 0xFFFF
                errorIndex = offset;
                break;
            }
#endif
            
            if ((tmp & 0xC0C0) == 0x8080) {
                //10xxxxxx 10xxxxxx
                offset += 3;
            } else {
                errorIndex = offset;
                break;
            }
        } else if ((byte & 0xF8) == 0xF0) {
            //4
            if (offset > length-4) {
                errorIndex = offset;
                break;
            }
            uint32_t tmp = *(uint32_t *)(bytes + offset);
            
#if BUILD_TARGET_RT_BIG_ENDIAN
            //大端
            if ((tmp & 0x7300000) == 0) {
                //0x10000 ~ 0x1FFFFF
                errorIndex = offset;
                break;
            }
            if ((tmp & 0xF8C0C0C0) == 0xF0808080) {
                offset += 4;
            } else {
                errorIndex = offset;
                break;
            }
#else
            //小端
            if ((tmp & 0x3007) == 0) {
                //0x10000 ~ 0x1FFFFF
                errorIndex = offset;
                break;
            }
            if ((tmp & 0xC0C0C0F8) == 0x808080F0) {
                offset += 4;
            } else {
                errorIndex = offset;
                break;
            }
#endif
        }
    }
    if (XIndexNotFound != errorIndex) {
        return XRangeMake(XIndexNotFound, 0);
    } else {
        return XRangeMake(begin, end - begin);
    }
}

XString _Nullable _XStringCreateWithUtf8Bytes(XObjectFlag flag, const XUInt8 * _Nonnull bytes, XSize length, const char * _Nonnull func) {
    XRange range = _XRangeOfString(bytes, length);
    XAssert(length < UINT32_MAX, func, "too large");
    if (XIndexNotFound != range.location) {
        return _XByteStorageCreate(true, flag, bytes + range.location, (XUInt32)range.length, __func__);
    }
    return NULL;
}
XString _Nonnull XStringCreateWithUtf8CString(XObjectFlag flag, const char * _Nonnull cString) {
    XAssert(NULL != cString, __func__, "cString is NULL");
    size_t length = strlen(cString);
    if (length == 0) {
        return XStringEmpty;
    }
    XString str = _XStringCreateWithUtf8Bytes(flag, (const XUInt8 *)cString, length, __func__);
    XAssert(NULL != str, __func__, "cString error");
    return str;
}

XString _Nullable XStringCreateWithBytes(XObjectFlag flag, const XUInt8 * _Nonnull bytes, XSize length, XStringEncoding encode) {
    XAssert(NULL != bytes, __func__, "cString is NULL");
    switch (encode) {
        case XStringEncodingUtf8: {
            if (length == 0) {
                return XStringEmpty;
            }
            return _XStringCreateWithUtf8Bytes(flag, bytes, length, __func__);
        }
            break;
        default:
            return NULL;
            break;
    }
}

XString _Nullable XStringCreateByDecodeData(XObjectFlag flag, XData _Nonnull data, XStringEncoding encode) {
    XAssert(NULL != data, __func__, "data is NULL");
    XByteStorageUnpacked_t v = _XByteStorageUnpack(data, __func__, "not Data instance");
    XAssert(0 == v.isString, __func__, "not Data instance");
    
    switch (encode) {
        case XStringEncodingUtf8: {
            if (0 == v.contentType) {
                XUInt8 * bytes = &(v.content.nano.content[1]);
                return _XStringCreateWithUtf8Bytes(flag, bytes, v.content.nano.content[0], __func__);
            } else if (1 == v.contentType) {
                XUInt8 * bytes = &(v.content.small->extended[0]);
                return _XStringCreateWithUtf8Bytes(flag, bytes, v.content.small->length, __func__);
            } else if (2 == v.contentType) {
                _XBuffer * buffer = v.content.large->buffer;
                XUInt offset = v.content.large->offset;
                XUInt8 * bytes = &(buffer->content[offset]);
                XUInt32 length = v.content.large->length;
                XRange range = _XRangeOfString(bytes, length);
                if (XIndexNotFound == range.location) {
                    return NULL;
                }
                if (range.length < buffer->size / 2) {
                    return _XByteStorageCreate(true, flag, bytes + range.location, (XUInt32)range.length, __func__);
                } else {
                    return _XByteStorageCreateWithBuffer(true, flag, buffer, range.location + offset, (XUInt32)range.length, __func__);
                }
            } else {
                XAssert(false, __func__, "unknown error");
            }
        }
            break;
        default:
            return NULL;
            break;
    }
    return NULL;
}

XHashCode XStringHash(XRef _Nonnull ref) {
    return _XByteStorageHash(ref, true, __func__);
}

#pragma mark - Data

XData _Nonnull XDataCreate(XObjectFlag flag, XUInt8 * _Nullable bytes, XUInt32 length) {
    if (length == 0) {
        return XDataEmpty;
    }
    return _XByteStorageCreate(false, flag, bytes, length, __func__);
}

XData _Nullable XDataCreateByEncodeString(XObjectFlag flag, XString _Nonnull string, XStringEncoding encode) {
    XAssert(NULL != string, __func__, "string is NULL");
    XByteStorageUnpacked_t v = _XByteStorageUnpack(string, __func__, "not String instance");
    XAssert(1 == v.isString, __func__, "not Data instance");
    switch (encode) {
        case XStringEncodingUtf8: {
            if (0 == v.contentType) {
                XUInt8 * bytes = &(v.content.nano.content[1]);
                return XDataCreate(flag, bytes, v.content.nano.content[0]);
            } else if (1 == v.contentType) {
                XUInt8 * bytes = &(v.content.small->extended[0]);
                return XDataCreate(flag, bytes, v.content.small->length);
            } else if (2 == v.contentType) {
                _XBuffer * buffer = v.content.large->buffer;
                XUInt offset = v.content.large->offset;
                XUInt8 * bytes = &(buffer->content[offset]);
                XUInt32 length = v.content.large->length;
                XRange range = _XRangeOfString(bytes, length);
                if (XIndexNotFound == range.location) {
                    return NULL;
                }
                if (range.length < buffer->size / 2) {
                    return _XByteStorageCreate(false, flag, bytes + range.location, (XUInt32)range.length, __func__);
                } else {
                    return _XByteStorageCreateWithBuffer(false, flag, buffer, range.location + offset, (XUInt32)range.length, __func__);
                }
            } else {
                XAssert(false, __func__, "unknown error");
            }
        }
            break;
        default:
            return NULL;
            break;
    }

    return NULL;
}

XHashCode XDataHash(XRef _Nonnull ref) {
    return _XByteStorageHash(ref, false, __func__);
}



