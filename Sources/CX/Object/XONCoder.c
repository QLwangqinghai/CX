
#include "XRuntimeInternal.h"
#include "XONCoder.h"


XDateRef _Nullable XONDecodeBufferReadTimeval(XDecodeBuffer_s * _Nonnull buffer, ssize_t count) {
    XTimestamp time = 0;
    buffer->error = XONDecodeTime(buffer->bytes, buffer->capacity, &(buffer->location), count, &time);
    if (buffer->error != XONErrorNone) {
        return NULL;
    }
    return XDateCreate(0, time);
}
XNumberRef _Nullable XONDecodeBufferReadNumber(XDecodeBuffer_s * _Nonnull buffer, ssize_t count) {
    XONNumberNormalContent_s value = { 0 };
    buffer->error = XONDecodeNormalNumber(buffer->bytes, buffer->capacity, &(buffer->location), count, &value);
    if (buffer->error != XONErrorNone) {
        return NULL;
    }
    double d = 0;
    if (XONErrorNone == XONNumberToFloat64(&value, &d)) {
        return XNumberCreateWithFloat64(0, d);
    }
    int64_t si = 0;
    if (XONErrorNone == XONNumberToSInt64(&value, &si)) {
        return XNumberCreateWithSInt64(0, si);
    }
    uint64_t ui = 0;
    if (XONErrorNone == XONNumberToUInt64(&value, &ui)) {
        return XNumberCreateWithUInt64(0, ui);
    }
    buffer->error = XONErrorNumberOutOfRange;
    return NULL;
}

ssize_t XONDecodeBufferReadCount(XDecodeBuffer_s * _Nonnull buffer, uint32_t layout) {
    ssize_t value = 0;
    buffer->error = XONDecodeCount(buffer->bytes, buffer->capacity, &(buffer->location), layout, &value);
    if (buffer->error != XONErrorNone) {
        return 0;
    }
    return value;
}
uint32_t XONDecodeBufferReadMessageFieldOffset(XDecodeBuffer_s * _Nonnull buffer) {
    uint32_t offset = 0;
    buffer->error = XONDecodeFieldKeyOffset(buffer->bytes, buffer->capacity, &(buffer->location), &offset);
    if (buffer->error != XONErrorNone) {
        return 0;
    }
    return offset;
}

XStringRef _Nullable XONDecodeBufferReadString(XDecodeBuffer_s * _Nonnull buffer, uint32_t layout) {
    ssize_t count = XONDecodeBufferReadCount(buffer, layout);
    if (buffer->error != XONErrorNone) {
        return NULL;
    }
    if (buffer->location <= buffer->capacity - count) {
        buffer->error = XONErrorNotEnough;
        return NULL;
    }
    XStringRef string = XStringCreateWithBytes(0, buffer->bytes + buffer->location, count, XStringEncodingUtf8, 0);
    if (NULL == string) {
        buffer->error = XONErrorStringContent;
        return NULL;
    }
    return string;
}
XDateRef _Nullable XONDecodeBufferReadData(XDecodeBuffer_s * _Nonnull buffer, uint32_t layout) {
    ssize_t length = XONDecodeBufferReadCount(buffer, layout);
    if (buffer->error != XONErrorNone) {
        return NULL;
    }
    if (buffer->location <= buffer->capacity - length) {
        buffer->error = XONErrorNotEnough;
        return NULL;
    }
    return XDataCreate(0, buffer->bytes + buffer->location, length);
}


XObjectRef _Nullable __XONDecodeBufferRead(XDecodeBuffer_s * _Nonnull buffer) {
    if (buffer->error != XONErrorNone) {
        return NULL;
    }
    if (buffer->location >= buffer->capacity) {
        buffer->error = XONErrorNotEnough;
        return NULL;
    }
    XONValueHeader_s header = {};
    XONError_e error = XONDecodeHeader(buffer->bytes, buffer->capacity, &(buffer->location), &header);
    if (XONErrorNone != error) {
        buffer->error = error;
        return NULL;
    }
    
    switch (header.type) {
        case XONWireTypeSimpleValue: {
            switch ((XONSimpleValue_e)(header.layout)) {
                case XONSimpleValueError: {
                    buffer->error = XONErrorType;
                    return NULL;
                }
                case XONSimpleValueNil: {
                    return NULL;
                }
                case XONSimpleValueBoolFalse: {
                    return XBoolFalse();
                }
                case XONSimpleValueBoolTrue: {
                    return XBoolTrue();
                }
                case XONSimpleValueTimeInvalid: {
                    return XDateInvalid;
                }
                case XONSimpleValueTime0: {
                    return XONDecodeBufferReadTimeval(buffer, 0);
                }
                case XONSimpleValueTime1: {
                    return XONDecodeBufferReadTimeval(buffer, 1);
                }
                case XONSimpleValueTime2: {
                    return XONDecodeBufferReadTimeval(buffer, 2);
                }
                case XONSimpleValueTime3: {
                    return XONDecodeBufferReadTimeval(buffer, 3);
                }
                case XONSimpleValueTime4: {
                    return XONDecodeBufferReadTimeval(buffer, 4);
                }
                case XONSimpleValueTime5: {
                    return XONDecodeBufferReadTimeval(buffer, 5);
                }
                case XONSimpleValueTime6: {
                    return XONDecodeBufferReadTimeval(buffer, 6);
                }
                case XONSimpleValueTime7: {
                    return XONDecodeBufferReadTimeval(buffer, 7);
                }
                case XONSimpleValueTime8: {
                    return XONDecodeBufferReadTimeval(buffer, 8);
                }
                case XONSimpleValueUndefine14: {
                    buffer->error = XONErrorNotSupport;
                    return NULL;
                }
                case XONSimpleValueNumberLarge: {
                    buffer->error = XONErrorNotSupport;
                    return NULL;
                }
                case XONSimpleValueNumberNAN: {
                    return XNumberCreateWithFloat64(0, __XONDoubleNan());
                }
                case XONSimpleValueNumberPositiveInfinity: {
                    return XNumberCreateWithFloat64(0, __XONDoublePositiveInfinity());
                }
                case XONSimpleValueNumberNegativeInfinity: {
                    return XNumberCreateWithFloat64(0, __XONDoubleNegativeInfinity());
                }
                case XONSimpleValueNumberZero: {
                    return XNumberCreateWithFloat64(0, __XONDoubleZero());
                }
                default: {
                    ssize_t contentLength = header.layout - XONSimpleValueNumberZero;
                    return XONDecodeBufferReadNumber(buffer, contentLength);
                }
            }
        }
            break;
        case XONWireTypeString: {
            return XONDecodeBufferReadString(buffer, header.layout);
        };
        case XONWireTypeData: {
            return XONDecodeBufferReadData(buffer, header.layout);
        }
        case XONWireTypeMessage: {
//            let count: Int = try self.readCount(index: index, layout: header.layout)
//            var prev: UInt32 = 0
//            var collection: [UInt32 : XONValue] = [:]
//            collection.reserveCapacity(count)
//            for _ in 0 ..< count {
//                let offset = try self.readMessageFieldOffset(index: index)
//                guard prev <= UInt32.max - offset else {
//                    throw XON.error(code: XONErrorMessageFieldKeyOffset)
//                }
//                let key = prev + offset
//                prev = key
//                let field = try self.readValue(index: index, deep: deep + 1)
//                collection[key] = field
//            }
//            guard collection.count == count else {
//                throw XON.error(code: XONErrorMessageContent)
//            }
//            return .message(collection)
            ssize_t count = XONDecodeBufferReadCount(buffer, header.layout);
            if (XONErrorNone != buffer->error) {
                return NULL;
            }
            if (buffer->location > buffer->capacity - count) {
                buffer->error = XONErrorNotEnough;
                return NULL;
            }
            if (count > 0) {
                XMessageRef message = XMessageBuilderCreateWithCount(0, count);
                uint32_t lastKey = 0;
                for (ssize_t i=0; i<count; i++) {
                    int32_t offset = XONDecodeBufferReadMessageFieldOffset(buffer);
                    if (buffer->error != XONErrorNone) {
                        XObjectRelease(message);
                        return NULL;
                    }
                    XObjectRef obj = __XONDecodeBufferRead(buffer);
                    if (buffer->error != XONErrorNone) {
                        XObjectRelease(message);
                        return NULL;
                    }
                    uint32_t key = lastKey + offset;
                    if (key < lastKey) {
                        buffer->error = XONErrorMessageFieldKeyOffset;
                        XObjectRelease(obj);
                        XObjectRelease(message);
                        return NULL;
                    }
                    XMessageBuilderReplaceWithRetainedValue(message, i, key, obj);
                    lastKey = key;
                }
                XMessageBuilderFinich(message);
                return message;
            } else {
                buffer->error = XONErrorNone;
                return XMessageCreate(0);
            }

        }
        case XONWireTypeArray: {
            ssize_t count = XONDecodeBufferReadCount(buffer, header.layout);
            if (XONErrorNone != buffer->error) {
                return NULL;
            }
            if (buffer->location > buffer->capacity - count) {
                buffer->error = XONErrorNotEnough;
                return NULL;
            }
            if (count > 0) {
                XArrayRef array = XArrayBuilderCreateWithCount(0, count);
                buffer->error = XONErrorNone;
                for (ssize_t i=0; i<count; i++) {
                    XObjectRef obj = __XONDecodeBufferRead(buffer);
                    if (buffer->error != XONErrorNone) {
                        XObjectRelease(array);
                        return NULL;
                    }
                    XArrayBuilderReplaceWithRetainedValue(array, i, obj);
                }
                XArrayBuilderFinich(array);
                return array;
            } else {
                return XArrayCreateWithValues(0, 0);
            }
        }
        default: {
            buffer->error = XONErrorType;
            return NULL;
        }
    }
}

XObjectRef _Nullable XONDecodeBufferRead(XDecodeBuffer_s * _Nonnull buffer) {
    XAssert(buffer, "");
    if (buffer->error != XONErrorNone) {
        return NULL;
    }
    if (buffer->capacity <= buffer->location) {
        buffer->error = XONErrorNotEnough;
        return NULL;
    }
    return __XONDecodeBufferRead(buffer);
}

XObjectRef _Nullable XONDecodeWithData(XDataRef _Nonnull data, XONError_e * _Nullable error) {
    _XDataUnpacked_t unpackedData = {};
    _XDataUnpack(data, &unpackedData, __func__, "");
    XDecodeBuffer_s buffer = XDecodeBufferMakeDefault(NULL, unpackedData.bytes, unpackedData.length);
    XObjectRef object = XONDecodeBufferRead(&buffer);
    if (error) {
        *error = (XONError_e)buffer.error;
    }
    XDecodeBufferDeinit(&buffer);
    return object;
}

XObjectRef _Nullable XONDecode(const void * _Nonnull bytes, ssize_t length, XONError_e * _Nullable error) {
    XDecodeBuffer_s buffer = XDecodeBufferMakeDefault(NULL, bytes, length);
    XObjectRef object = XONDecodeBufferRead(&buffer);
    if (error) {
        *error = (XONError_e)buffer.error;
    }
    XDecodeBufferDeinit(&buffer);
    return object;
}




XONError_e __XONEncode(XONEncodeBuffer_s * _Nonnull buffer, XObjectRef _Nullable object);

typedef struct __XONEncodeMessageContext {
    XONEncodeBuffer_s * _Nonnull buffer;
    uint32_t prevKey;
    int error;
} XONEncodeMessageContext_s;

typedef struct __XONEncodeArrayContext {
    XONEncodeBuffer_s * _Nonnull buffer;
    size_t index;
    int error;
} XONEncodeArrayContext_s;

void _XArrayEnumerateEncodeXON(size_t index, XObjectRef _Nullable object, void * _Nullable context, bool_t * _Nonnull stop) {
    __XONEncode(((XONEncodeArrayContext_s *)context)->buffer, object);
    ((XONEncodeArrayContext_s *)context)->index = index;
    *stop = ((XONEncodeArrayContext_s *)context)->error != XONErrorNone;
}
void _XMessageEnumerateEncodeXON(int32_t key, XObjectRef _Nullable value, void * _Nullable ctx, bool_t * _Nonnull stop) {
    XONEncodeMessageContext_s * context = (XONEncodeMessageContext_s *)ctx;
    XONEncodeFieldKeyOffset(context->buffer, key - context->prevKey);
    context->prevKey = key;
    if (context->error != XONErrorNone) {
        *stop = true;
    } else {
        __XONEncode(context->buffer, value);
        *stop = context->error != XONErrorNone;
    }
}

XONError_e __XONEncode(XONEncodeBuffer_s * _Nonnull buffer, XObjectRef _Nullable object) {
    if (NULL == object) {
        return XONEncodeNull(buffer);
    } else {
        XClassRef cls = XObjectGetClass(object);
        if (cls == XBoolClass) {
            return XONEncodeBool(buffer, XBoolGetValue(object));
        } else if (cls == XNumberClass) {
            XNumberValue_s value = XNumberGetValue(object);
            switch (value.storageType) {
                case XNumberStorageTypeSInt: {
                    if (value.storage.s >= INT64_MIN && value.storage.s <= INT64_MAX) {
                        return XONEncodeNumberSInt64(buffer, value.storage.s);
                    } else {
                        return XONErrorNumberContent;
                    }
                }
                case XNumberStorageTypeUInt: {
                    if (value.storage.u <= UINT64_MAX) {
                        return XONEncodeNumberUInt64(buffer, value.storage.u);
                    } else {
                        return XONErrorNumberContent;
                    }
                }
                case XNumberStorageTypeFloat: {
                    return XONEncodeNumberDouble(buffer, value.storage.f);
                }
                default:
                    return XONErrorNumberContent;
            }
        } else if (cls == XDateClass) {
            microsecond_t microsecond = XDateGetTimevalSince1970(object);
            return XONEncodeTime(buffer, microsecond);
        } else if (cls == XStringClass) {
            ssize_t length = XStringGetUtf8Length(object);
            XONError_e error = XONEncodeStringHeader(buffer, length);
            if (XONErrorNone != error) {
                return error;
            }
            XONEncodeBufferReserveCapacity(buffer, buffer->location + length);
            //XONEncodeBody
            XStringGetBytes(object, 0, length, buffer->bytes + buffer->location);
            buffer->location += length;
            return XONErrorNone;
        } else if (cls == XDataClass) {
            ssize_t count = XDataGetLength(object);
            XONError_e error = XONEncodeDataHeader(buffer, count);
            if (XONErrorNone != error) {
                return error;
            }
            XONEncodeBufferReserveCapacity(buffer, buffer->location + count);
            //XONEncodeBody
            XDataGetBytes(object, 0, count, buffer->bytes + buffer->location);
            buffer->location += count;
            return XONErrorNone;
        } else if (cls == XArrayClass) {
            XONEncodeArrayContext_s context = {
                .buffer = buffer,
                .index = 0,
                .error = 0,
            };
            ssize_t count = XArrayGetCount(object);
            XONError_e error = XONEncodeArrayHeader(buffer, count);
            if (XONErrorNone != error) {
                return error;
            }
            XArrayEnumerate(object, false, _XArrayEnumerateEncodeXON, &context);
            return context.error;
        } else if (cls == XMessageClass) {
            XONEncodeMessageContext_s context = {
                .buffer = buffer,
                .prevKey = 0,
                .error = 0,
            };
            ssize_t count = XMessageGetCount(object);
            XONEncodeMessageHeader(buffer, count);
            XMessageEnumerate(object, _XMessageEnumerateEncodeXON, &context);
            return context.error;
        } else {
            return XONErrorContent;
        }
    }
}

XDataRef _Nullable XONEncode(XObjectRef _Nullable object, XONError_e * _Nullable error) {
    XONEncodeBuffer_s buffer = XONEncodeBufferMakeDefault();
    XONError_e e = __XONEncode(&buffer, object);
    if (error) {
        *error = e;
    }
    if (XONErrorNone == e) {
        XDataRef r = XDataCreate(0, buffer.bytes, buffer.location);
        XONEncodeBufferDeallocate(&buffer);
        return r;
    } else {
        return NULL;
    }
}

