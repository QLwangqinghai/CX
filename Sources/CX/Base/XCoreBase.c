
#include "XCoreBase.h"
#include "XAllocator.h"
#include <pthread.h>

static _Atomic(uint32_fast_t) _XLogDateAnchor = ATOMIC_VAR_INIT(0);
static pthread_mutex_t _XLogMutex = PTHREAD_MUTEX_INITIALIZER;

void XLog(const char *__restrict _Nonnull format, ...) {
    XLogBegin("");
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    XLogFinish("");
}

void XLogBegin(const char *__restrict _Nonnull format, ...) {
    struct timeval tv;
    struct timezone tz;
    struct tm * p;

    // 年月日+时区hhmm
    gettimeofday (&tv, &tz);
    time_t timep = tv.tv_sec;
    p = localtime(&timep);
    uint32_fast_t dateAnchor = (1900+p->tm_year) * 100000000 + p->tm_mon * 1000000 + p->tm_mday * 10000 + 5000 + tz.tz_minuteswest;
        
    uint32_fast_t old = atomic_load(&_XLogDateAnchor);
    if (old != dateAnchor) {
        const char * s = "";
        int offset = 0;
        if (tz.tz_minuteswest >= 0) {
            s = "+";
            offset = tz.tz_minuteswest;
        } else {
            s = "-";
            offset = tz.tz_minuteswest * (-1);
        }
        
        fprintf(stdout, "%c%d-%02d-%02dT%02d:%02d:%02d%s%02d:%02d\n", 0x1, p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, s, offset /  60, offset % 60);
        atomic_store(&_XLogDateAnchor, dateAnchor);
    }
    pthread_t t = pthread_self();
    fprintf(stdout, "%c%lx-%02d:%02d:%02d.%06d ", 0x2, *(uintptr_t *)&(t), p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    
//
//    bool_t anchorUpdate = true;
//
//    do {
//        gettimeofday (&tv, &tz);
//        time_t timep = tv.tv_sec;
//        p = localtime(&timep);
//
//        old = atomic_load(&_XLogDateAnchor);
//        dateAnchor = (1900+p->tm_year) * 100000000 + p->tm_mon * 1000000 + p->tm_mday * 10000 + 5000 + tz.tz_minuteswest;
//        if (dateAnchor == old) {
//            anchorUpdate = false;
//            break;
//        }
//    } while (!atomic_compare_exchange_strong(&_XLogDateAnchor, &old, dateAnchor));

    
//    //2004-05-03T17:30:08+08:00
//    if (anchorUpdate) {
//        printf("%d-%02d-%02dT%02d:%02d:%02d%s%02d:%02d", p->tm_year, p->tm_mon, p->tm_mday, p->tm_mon);
//    }
}
void XLogAppend(const char *__restrict _Nonnull format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
}
void XLogFinish(const char *__restrict _Nonnull format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\n");
}

const char XHexLowercaseTable[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const char XHexUppercaseTable[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

ssize_t XByteEncodeToHexString(const uint8_t * _Nonnull bytes, size_t byteLength, char * _Nonnull buffer, size_t capacity, uint32_t options) {
    size_t result = byteLength * 2 + 1;
    if (result < byteLength) {
        // 溢出
        return -1;
    }
    if (result > capacity) {
        return -1;
    }
    const char * table = ((options & XByteEncodeOptionToUppercase) == XByteEncodeOptionToUppercase) ? XHexUppercaseTable : XHexLowercaseTable;
    
    size_t offset = 0;
    for (size_t i=0; i<byteLength; i++) {
        uint8_t byte = bytes[i];
        buffer[offset] = table[(byte >> 4)];
        buffer[offset+1] = table[(byte & 0xf)];
        offset += 2;
    }
    buffer[offset] = '\0';
    return result;
}

const uint8_t XHexDecodeTable[256] = {
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 128, 128, 128, 128, 128, 128,
    128, 10, 11, 12, 13, 14, 15, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 10, 11, 12, 13, 14, 15, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
};

ssize_t XByteDecodeFromHexString(uint8_t * _Nonnull bytes, size_t capacity, const char * _Nonnull str, uint32_t options) {
    bool_t ignoreUnknownCharacters = ((options & XByteEncodeOptionIgnoreUnknownCharacters) == XByteEncodeOptionIgnoreUnknownCharacters);
    size_t count = 0;
    size_t offset = 0;
    
    uint8_t pending = 0;
    const uint8_t * strByte = (const uint8_t *)str;
    uint8_t c = strByte[0];
    while (c != 0) {
        uint8_t v = XHexDecodeTable[c];
        if (v > 15) {
            if (!ignoreUnknownCharacters) {
                return -1;
            }
        } else {
            if (count % 2 == 0) {
                pending = v;
            } else {
                pending = pending << 4;
                pending += v;
                if (count / 2 >= capacity) {
                    return -1;
                }
                bytes[count/2] = pending;
            }
            count += 1;
        }
        offset += 1;
        c = strByte[offset];
    }
    if (count % 2 != 0) {
        return -1;
    }
    return count / 2;
}


#pragma mark - SliceList

void XSliceListElementInit(XSliceListElement_s * _Nonnull element, size_t capacity, size_t itemSize) {
    XAssert(element, "");
    XAssert(capacity <= UINT32_MAX, "");
    XAssert(itemSize <= UINT32_MAX, "");
    XAssert(itemSize > 0, "");
    XAssert(capacity > 0, "");
    size_t payloadSize = capacity;
    payloadSize *= itemSize;
    XAssert(payloadSize > 0, "");
    XAssert(payloadSize / capacity == itemSize, "");
    
    element->owner = NULL;
    element->prev = NULL;
    element->next = NULL;
    element->offset = 0;
    element->count = 0;
    element->capacity = capacity;
    element->itemSize = itemSize;
    memset(element->payload, 0, payloadSize);
}
XSliceListElement_s * _Nonnull XSliceListElementCreate(size_t itemSize, size_t capacity) {
    XAssert(itemSize > 0, "");
    XAssert(capacity > 0, "");
    
    size_t payloadSize = capacity;
    payloadSize *= itemSize;
    XAssert(payloadSize > 0, "");
    XAssert(payloadSize / capacity == itemSize, "");

    XSliceListElement_s * element = XAllocate(sizeof(XSliceListElement_s) + payloadSize);
    XAssert(element, "");
    
    element->owner = NULL;
    element->prev = NULL;
    element->next = NULL;
    element->offset = 0;
    element->count = 0;
    element->capacity = capacity;
    element->itemSize = itemSize;
    memset(element->payload, 0, payloadSize);
    
    return element;
}

void XSliceListElementReset(XSliceListElement_s * _Nonnull element) {
    element->offset = 0;
    element->count = 0;
    
    size_t payloadSize = element->capacity;
    payloadSize *= element->itemSize;
    XAssert(payloadSize > 0, "");
    XAssert(payloadSize / element->capacity == element->itemSize, "");
    memset(element->payload, 0, payloadSize);
}

void XSliceListElementDestroy(XSliceListElement_s * _Nonnull element) {
    XAssert(element, "");
    XDeallocate(element);
}

void XSliceListInit(XSliceList_s * _Nonnull queue, size_t itemSize) {
    XAssert(queue, "");
    XAssert(itemSize <= UINT32_MAX, "");
    XAssert(itemSize > 0, "");

    queue->head = NULL;
    queue->tail = NULL;
    queue->head = NULL;
    queue->tail = NULL;
    queue->itemSize = itemSize;
}

void __XSliceListEmementLink(XSliceListElement_s * _Nonnull lhs, XSliceListElement_s * _Nonnull rhs) {
    XAssert(lhs->next == NULL, "");
    XAssert(rhs->prev == NULL, "");
    lhs->next = rhs;
    rhs->prev = lhs;
}

void __XSliceListEmementUnlink(XSliceListElement_s * _Nonnull lhs, XSliceListElement_s * _Nonnull rhs) {
    XAssert(lhs->next == rhs, "");
    XAssert(rhs->prev == lhs, "");

    lhs->next = NULL;
    rhs->prev = NULL;
}


void XSliceListAppendSlice(XSliceList_s * _Nonnull queue, XSliceListElement_s * _Nonnull element) {
    XAssert(queue, "");
    XAssert(element, "");
    XAssert(NULL == element->owner, "");
    XAssert(queue->itemSize == element->itemSize, "");
    XAssert(NULL == element->next, "");
    XAssert(NULL == element->prev, "");

    if (NULL == queue->head) {
        XAssert(NULL == queue->tail, "");
        queue->head = element;
        queue->tail = element;
        element->owner = queue;
    } else {
        XAssert(NULL != queue->tail, "");
        __XSliceListEmementLink(queue->tail, element);
        queue->tail = element;
        element->owner = queue;
    }
}

void XSliceListPrependSlice(XSliceList_s * _Nonnull queue, XSliceListElement_s * _Nonnull element) {
    XAssert(queue, "");
    XAssert(element, "");
    XAssert(NULL == element->owner, "");
    XAssert(queue->itemSize == element->itemSize, "");
    XAssert(NULL == element->owner, "");
    XAssert(NULL == element->next, "");

    if (NULL == queue->tail) {
        XAssert(NULL == queue->head, "");
        queue->head = element;
        queue->tail = element;
        element->owner = queue;
    } else {
        XAssert(NULL != queue->head, "");
        __XSliceListEmementLink(element, queue->head);
        queue->head = element;
        element->owner = queue;
    }
}

XSliceListElement_s *_Nullable XSliceListRemoveFirstSlice(XSliceList_s * _Nonnull queue) {
    XAssert(queue, "");
    if (NULL == queue->head) {
        XAssert(NULL == queue->tail, "");
        return NULL;
    } else {
        XSliceListElement_s * element = queue->head;
        XSliceListElement_s * newHead = element->next;
        
        element->owner = NULL;
        if (queue->tail == queue->head) {
            queue->tail = NULL;
            queue->head = NULL;
        } else {
            queue->head = newHead;
            XAssert(newHead, "");
            __XSliceListEmementUnlink(element, newHead);
        }
        return element;
    }
}

XSliceListElement_s *_Nullable XSliceListRemoveLastSlice(XSliceList_s * _Nonnull queue) {
    XAssert(queue, "");
    if (NULL == queue->tail) {
        XAssert(NULL == queue->head, "");
        return NULL;
    } else {
        XSliceListElement_s * element = queue->tail;
        XSliceListElement_s * newTail = element->prev;
        
        element->owner = NULL;
        if (queue->tail == queue->head) {
            queue->tail = NULL;
            queue->head = NULL;
        } else {
            queue->tail = newTail;
            XAssert(newTail, "");
            __XSliceListEmementUnlink(newTail, element);
        }
        return element;
    }
}

// BOM: 0xEF 0xBB 0xBF  11101111 10111011 10111111
XIndex _XScanUtf8Bom(const uint8_t * _Nonnull bytes, size_t length) {
    if (length < 3) {
        return 0;
    }
    size_t i = 0;
    for(; i<length-2; i+=3) {
        if (0xEF == bytes[i] && 0xBB == bytes[i+1] && 0xBF == bytes[i+2]) {
        } else {
            return i;
        }
    }
    return i;
}

//// 0, end; normal [1, 4] , other error
//static inline uint8_t XUtf8CharLength(uint8_t byte) {
//    /*
//     0x0000 0000 至 0x0000 007F:0xxxxxxx
//     0x0000 0080 至 0x0000 07FF:110xxxxx 10xxxxxx
//     0x0000 0800 至 0x0000 FFFF:1110xxxx 10xxxxxx 10xxxxxx
//     0x0001 0000 至 0x0010 FFFF:11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//     */
//    // 查表
//    static const uint8_t lengthTable[32] = {
//        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 255, 255, 255, 255, 255, 255, 255, 255, 2, 2, 2, 2, 3, 3, 4, 255
//    };
//    if (XUnlikely(byte == 0)) {
//        return 0;
//    } else {
//        return lengthTable[(byte >> 3)];
//    }
//}

/* Check whether an UTF-8 string is well-formed.
   Return NULL if valid, or a pointer to the first invalid unit otherwise.  */

/*
 0x000000 至 0x00007F:0xxxxxxx
 0x000080 至 0x0007FF:110xxxxx 10xxxxxx
 0x000800 至 0x00FFFF:1110xxxx 10xxxxxx 10xxxxxx
 0x010000 至 0x10FFFF:11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 */
// 代码源自 libunistring
size_t u8_check (const uint8_t * _Nonnull s, size_t n) {
    const uint8_t *s_end = s + n;
    const uint8_t * _Nonnull start = s;
    while (s < s_end) {
      /* Keep in sync with unistr.h and u8-mbtouc-aux.c.  */
        uint8_t c = *s;

        if (c < 0x80) {
            s++;
            continue;
        }
        if (c >= 0xc2) {
            if (c < 0xe0) {
                if (s + 2 <= s_end && (s[1] ^ 0x80) < 0x40) {
                    s += 2;
                    continue;
                }
            } else if (c < 0xf0) {
                /*
                 Unicode代理对
                 定义：
                 Unicode代理对由两个特殊的Unicode码点组成，用于表示U+10000到U+10FFFF范围内的字符。
                 这两个码点被称为高代理项（High Surrogate）和低代理项（Low Surrogate）。
                 范围：
                 高代理项的范围是U+D800到U+DBFF（即十进制的55296到56319）。
                 低代理项的范围是U+DC00到U+DFFF（即十进制的56320到57343）。
                 D800 - DFFF
                 作用：
                 */
                // 1110xxxx 10xxxxxx 10xxxxxx 0x000800 至 0x00FFFF， 0xd8   D7B0-D7FF
                // 
                // 确保 c 不是 0xED（因为 0xED 开头的 3 字节字符可能表示一个 Unicode 代理对，这在 UTF-8 中是无效的），或者 s[1] 的值大于或等于 0xA0（以避免某些 UTF-16 代理对的无效模式）。
                if (s + 3 <= s_end && (s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
                  && (c >= 0xe1 || s[1] >= 0xa0) && (c != 0xed || s[1] < 0xa0)) {
                    s += 3;
                    continue;
                }
            } else if (c < 0xf8) {
                // (c >= 0xf1 || s[1] >= 0x90) 高5位有值
                // (c < 0xf4 || (c == 0xf4 && s[1] < 0x90)) 编码后的数字 <= 10FFFF
                if (s + 4 <= s_end
                    && (s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
                    && (s[3] ^ 0x80) < 0x40
                    && (c >= 0xf1 || s[1] >= 0x90)
                    && (c < 0xf4 || (c == 0xf4 && s[1] < 0x90))) {
                    s += 4;
                    continue;
                }
            }
        }
        /* invalid or incomplete multibyte character */
        return s - start;
    }
    return n;
}

/// 废弃 3字节、4字节缺少逻辑
XStringUtf8Layout_s _XUtf8StringLayoutMakeWithBytes4(const uint8_t * _Nonnull bytes, size_t length) {
    /*
     // BOM是一个特殊的Unicode字符(U+FEFF) BOM: 0xEF 0xBB 0xBF  11101111 10111011 10111111
     7 - 11 - 16 - 21
     0x000000 至 0x00007F:0xxxxxxx
     0x000080 至 0x0007FF:110xxxxx 10xxxxxx
     0x000800 至 0x00FFFF:1110xxxx 10xxxxxx 10xxxxxx
     0x010000 至 0x10FFFF:11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
     */
    
    XIndex begin = _XScanUtf8Bom(bytes, length);
    XIndex offset = begin;
    XIndex unicodeCount = 0;
    bool_t noError = true;

    while (length > offset && noError) {
        uint8_t byte = bytes[offset];
        if (byte == 0x0) {
            //终止符
            break;
        } else if (byte < 0x80) {
            //1
            offset += 1;
            unicodeCount += 1;
        } else if ((byte & 0xE0) == 0xC0) {
            //2 byte & 11100000 == 11000000
            if (offset > length-2) {
                noError = false;
                break;
            }
            if ((byte & 0x1E) == 0) {
                //确保 unicode码在范围内 0x0080 ~ 0x07FF
                noError = false;
                break;
            }
            uint8_t tmp = bytes[offset+1];
            if ((tmp & 0xC0) == 0x80) {
                //10xxxxxx
                offset += 2;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
        } else if ((byte & 0xF0) == 0xE0) {
            //3 byte & 11110000 == 11100000

            //3
            if (offset > length-3) {
                noError = false;
                break;
            }
            
            uint16_t tmp = *(uint16_t *)(bytes + offset + 1);
            
#if CX_TARGET_RT_BIG_ENDIAN
            //大端
            if ((byte & 0xF) == 0 && (tmp & 0x2000) == 0) {
                //确保 unicode码在范围内 0x0800 ~ 0xFFFF
                noError = false;
                break;
            }
#else
            //小端
            if ((byte & 0xF) == 0 && (tmp & 0x20) == 0) {
                //0x0800 ~ 0xFFFF
                noError = false;
                break;
            }
#endif
            
            if ((tmp & 0xC0C0) == 0x8080) {
                //10xxxxxx 10xxxxxx
                offset += 3;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
        } else if ((byte & 0xF8) == 0xF0) {
            //4
            
            //4 byte & 11111000 == 11110000

            if (offset > length-4) {
                noError = false;
                break;
            }
            uint32_t tmp = *(uint32_t *)(bytes + offset);
            
#if CX_TARGET_RT_BIG_ENDIAN
            //大端
            if ((tmp & 0x7300000) == 0) {
                //0x10000 ~ 0x1FFFFF
                noError = false;
                break;
            }
            if ((tmp & 0xF8C0C0C0) == 0xF0808080) {
                offset += 4;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
#else
            //小端
            if ((tmp & 0x3007) == 0) {
                //0x10000 ~ 0x1FFFFF
                noError = false;
                break;
            }
            if ((tmp & 0xC0C0C0F8) == 0x808080F0) {
                offset += 4;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
#endif
        } else {
            noError = false;
        }
    }
    return XStringUtf8LayoutMake(begin, offset - begin, unicodeCount);
}
XStringUtf8Layout_s _XUtf8StringLayoutMakeWithBytes3(const uint8_t * _Nonnull bytes, size_t length) {
    /*
     0x000000 至 0x00007F:0xxxxxxx
     0x000080 至 0x0007FF:110xxxxx 10xxxxxx
     0x000800 至 0x00FFFF:1110xxxx 10xxxxxx 10xxxxxx
     0x010000 至 0x10FFFF:11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
     */
    
    XIndex begin = _XScanUtf8Bom(bytes, length);
    XIndex offset = begin;
    XIndex unicodeCount = 0;
    bool_t noError = true;

    while (length > offset && noError) {
        uint8_t byte = bytes[offset];
        if (byte == 0x0) {
            //终止符
            break;
        } else if (byte < 0x80) {
            //1
            offset += 1;
            unicodeCount += 1;
        } else if ((byte & 0xE0) == 0xC0) {
            //2 byte & 11100000 == 11000000
            if (offset > length-2) {
                noError = false;
                break;
            }
            if ((byte & 0x1E) == 0) {
                //确保 unicode码在范围内 0x0080 ~ 0x07FF
                noError = false;
                break;
            }
            uint8_t tmp = bytes[offset+1];
            if ((tmp & 0xC0) == 0x80) {
                //10xxxxxx
                offset += 2;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
        } else if ((byte & 0xF0) == 0xE0) {
            //3 byte & 11110000 == 11100000

            //3
            if (offset > length-3) {
                noError = false;
                break;
            }
            
            uint16_t tmp = *(uint16_t *)(bytes + offset + 1);
            
#if CX_TARGET_RT_BIG_ENDIAN
            //大端
            if ((byte & 0xF) == 0 && (tmp & 0x2000) == 0) {
                //确保 unicode码在范围内 0x0800 ~ 0xFFFF
                noError = false;
                break;
            }
#else
            //小端
            if ((byte & 0xF) == 0 && (tmp & 0x20) == 0) {
                //0x0800 ~ 0xFFFF
                noError = false;
                break;
            }
#endif
            
            if ((tmp & 0xC0C0) == 0x8080) {
                //10xxxxxx 10xxxxxx
                offset += 3;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
        } else if ((byte & 0xF8) == 0xF0) {
            //4
            
            //4 byte & 11111000 == 11110000

            if (offset > length-4) {
                noError = false;
                break;
            }
            uint32_t tmp = *(uint32_t *)(bytes + offset);
            
#if CX_TARGET_RT_BIG_ENDIAN
            //大端
            if ((tmp & 0x7300000) == 0) {
                //0x10000 ~ 0x1FFFFF
                noError = false;
                break;
            }
            if ((tmp & 0xF8C0C0C0) == 0xF0808080) {
                offset += 4;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
#else
            //小端
            if ((tmp & 0x3007) == 0) {
                //0x10000 ~ 0x1FFFFF
                noError = false;
                break;
            }
            if ((tmp & 0xC0C0C0F8) == 0x808080F0) {
                offset += 4;
                unicodeCount += 1;
            } else {
                noError = false;
                break;
            }
#endif
        } else {
            noError = false;
        }
    }
    return XStringUtf8LayoutMake(begin, offset - begin, unicodeCount);
}


XStringUtf8Layout_s _XUtf8StringLayoutMakeWithBytes(const uint8_t * _Nonnull bytes, size_t n) {
    XIndex begin = _XScanUtf8Bom(bytes, n);
    XStringUtf8Layout_s result = {
        .location = begin,
        .length = 0,
        .unicodeCount = 0,
    };
    const uint8_t * s = bytes + begin;
    const uint8_t * s_end = bytes + n;
    while (s < s_end) {
      /* Keep in sync with unistr.h and u8-mbtouc-aux.c.  */
        uint8_t c = *s;

        if (c == 0) {
            result.length = s - bytes - begin;
            return result;
        }
        if (c < 0x80) {
            s++;
            result.unicodeCount += 1;
            continue;
        }
        if (c >= 0xc2) {
            if (c < 0xe0) {
                if (s + 2 <= s_end && (s[1] ^ 0x80) < 0x40) {
                    s += 2;
                    result.unicodeCount += 1;
                    continue;
                }
            } else if (c < 0xf0) {
                if (s + 3 <= s_end && (s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
                  && (c >= 0xe1 || s[1] >= 0xa0) && (c != 0xed || s[1] < 0xa0)) {
                    s += 3;
                    result.unicodeCount += 1;
                    continue;
                }
            } else if (c < 0xf8) {
                if (s + 4 <= s_end
                    && (s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
                    && (s[3] ^ 0x80) < 0x40
                    && (c >= 0xf1 || s[1] >= 0x90)
                    && (c < 0xf4 || (c == 0xf4 && s[1] < 0x90))) {
                    s += 4;
                    result.unicodeCount += 1;
                    continue;
                }
            }
        }
        /* invalid or incomplete multibyte character */
        result.length = s - bytes - begin;
        return result;
    }
    result.length = s - bytes - begin;
    return result;
}

XStringUtf8Layout_s _XUtf8StringLayoutMakeWithBytes2(const uint8_t * _Nonnull bytes, size_t length) {
    /*
     0x000000 至 0x00007F:0xxxxxxx
     0x000080 至 0x0007FF:110xxxxx 10xxxxxx
     0x000800 至 0x00FFFF:1110xxxx 10xxxxxx 10xxxxxx
     0x010000 至 0x10FFFF:11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
     */

    XIndex begin = _XScanUtf8Bom(bytes, length);
    XIndex offset = begin;
    
    XStringUtf8Layout_s result = {
        .location = begin,
        .length = 0,
        .unicodeCount = 0,
    };
    
    while (length > offset) {
        uint8_t byte = bytes[offset];
        switch (byte) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
            case 56:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
            case 62:
            case 63:
            case 64:
            case 65:
            case 66:
            case 67:
            case 68:
            case 69:
            case 70:
            case 71:
            case 72:
            case 73:
            case 74:
            case 75:
            case 76:
            case 77:
            case 78:
            case 79:
            case 80:
            case 81:
            case 82:
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 89:
            case 90:
            case 91:
            case 92:
            case 93:
            case 94:
            case 95:
            case 96:
            case 97:
            case 98:
            case 99:
            case 100:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
            case 109:
            case 110:
            case 111:
            case 112:
            case 113:
            case 114:
            case 115:
            case 116:
            case 117:
            case 118:
            case 119:
            case 120:
            case 121:
            case 122:
            case 123:
            case 124:
            case 125:
            case 126:
            case 127: {
                // 1 byte
                offset += 1;
                result.unicodeCount += 1;
            }
                break;
            case 194:
            case 195:
            case 196:
            case 197:
            case 198:
            case 199:
            case 200:
            case 201:
            case 202:
            case 203:
            case 204:
            case 205:
            case 206:
            case 207:
            case 208:
            case 209:
            case 210:
            case 211:
            case 212:
            case 213:
            case 214:
            case 215:
            case 216:
            case 217:
            case 218:
            case 219:
            case 220:
            case 221:
            case 222:
            case 223: {
                //2 byte & 11100000 == 11000000
                if (offset > length-2) {
                    result.length = offset - begin;
                    return result;
                }
                uint8_t tmp = bytes[offset+1];
                if ((tmp & 0xC0) == 0x80) {
                    //10xxxxxx
                    offset += 2;
                    result.unicodeCount += 1;
                } else {
                    result.length = offset - begin;
                    return result;
                }
            }
                break;
            case 224:
            case 225:
            case 226:
            case 227:
            case 228:
            case 229:
            case 230:
            case 231:
            case 232:
            case 233:
            case 234:
            case 235:
            case 236:
            case 237:
            case 238:
            case 239: {
                //3 byte & 11110000 == 11100000
                if (offset > length-3) {
                    result.length = offset - begin;
                    return result;
                }
                
                uint16_t tmp = *(uint16_t *)(bytes + offset + 1);
                
#if CX_TARGET_RT_BIG_ENDIAN
                //大端
                if ((byte & 0xF) == 0 && (tmp & 0x2000) == 0) {
                    //确保 unicode码在范围内 0x0800 ~ 0xFFFF
                    result.length = offset - begin;
                    return result;
                }
#else
                //小端
                if ((byte & 0xF) == 0 && (tmp & 0x20) == 0) {
                    //0x0800 ~ 0xFFFF
                    result.length = offset - begin;
                    return result;
                }
#endif
                
                if ((tmp & 0xC0C0) == 0x8080) {
                    //10xxxxxx 10xxxxxx
                    offset += 3;
                    result.unicodeCount += 1;
                } else {
                    result.length = offset - begin;
                    return result;
                }
                
            }
                break;
            case 240:
            case 241:
            case 242:
            case 243:
            case 244:
            case 245:
            case 246:
            case 247: {
                //4 byte & 11111000 == 11110000
                
                if (offset > length-4) {
                    result.length = offset - begin;
                    return result;
                }
                uint32_t tmp = *(uint32_t *)(bytes + offset);
                
#if CX_TARGET_RT_BIG_ENDIAN
                //大端
                if ((tmp & 0x7300000) == 0) {
                    //0x10000 ~ 0x1FFFFF
                    result.length = offset - begin;
                    return result;
                }
                if ((tmp & 0xF8C0C0C0) == 0xF0808080) {
                    offset += 4;
                    result.unicodeCount += 1;
                } else {
                    result.length = offset - begin;
                    return result;
                }
#else
                //小端
                if ((tmp & 0x3007) == 0) {
                    //0x10000 ~ 0x1FFFFF
                    result.length = offset - begin;
                    return result;
                }
                if ((tmp & 0xC0C0C0F8) == 0x808080F0) {
                    offset += 4;
                    result.unicodeCount += 1;
                } else {
                    result.length = offset - begin;
                    return result;
                }
#endif
            }
                break;
            case 0: {
                result.length = offset - begin;
                return result;
            }
            default: {
                result.length = offset - begin;
                return result;
            }
        }
    }
    result.length = offset - begin;
    return result;
}


XIndex __XScanUtf8CStringBom(const uint8_t * _Nonnull bytes) {
    size_t i = 0;
    size_t max = SIZE_T_MAX - 2;
    for(; i<max; i+=3) {
        uint8_t byte0 = bytes[i];
        if (byte0 == 0) {
            break;
        }
        
        uint8_t byte1 = bytes[i+1];
        if (byte1 == 0) {
            break;
        }
        
        uint8_t byte2 = bytes[i+2];
        if (byte2 == 0) {
            break;
        }
        if (0xEF == byte0 && 0xBB == byte1 && 0xBF == byte2) {
        } else {
            return i;
        }
    }
    return i;
}



XStringUtf8Layout_s __XUtf8StringLayoutMakeWithCString(const uint8_t * _Nonnull _bytes) {
    /*
     0x0000 0000 至 0x0000 007F  :0xxxxxxx  7
     0x0000 0080 至 0x0000 07FF  :110xxxxx 10xxxxxx     5+6=11   0x1E
     0x0000 0800 至 0x0000 FFFF  :1110xxxx 10xxxxxx 10xxxxxx 4+6+6=16 0xF 0x20
     0x0001 0000 至 0x0010 FFFF  :11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 3+6+6+6=21  0x7 0x30
     */
    const uint8_t * _Nonnull bytes = (const uint8_t *)_bytes;
    XIndex begin = __XScanUtf8CStringBom(bytes);
    XIndex offset = begin;
    XIndex unicodeCount = 0;
    bool_t noError = true;
    while (noError) {
        uint8_t byte = bytes[offset];
        if (byte == 0x0) {
            //终止符
            break;
        } else if (byte < 0x80) {
            //1
            offset += 1;
            unicodeCount += 1;
        } else if ((byte & 0xE0) == 0xC0) {
            //2 byte & 11100000 == 11000000  5 + 6
            
            uint8_t byte1 = bytes[offset+1];
            if (byte1 == 0 || (byte1 & 0xC0) != 0x80) {
                noError = false;
                break;
            }
            
            if ((byte & 0x1E) == 0) {
                //确保 unicode码在范围内 0x0080 ~ 0x07FF
                noError = false;
                break;
            }
            
            offset += 2;
            unicodeCount += 1;
        } else if ((byte & 0xF0) == 0xE0) {
            //3 byte & 11110000 == 11100000  4 + 6 + 6
            uint8_t byte1 = bytes[offset+1];
            if (byte1 == 0 || (byte1 & 0xC0) != 0x80) {
                noError = false;
                break;
            }
            
            uint8_t byte2 = bytes[offset+2];
            if (byte2 == 0 || (byte2 & 0xC0) != 0x80) {
                noError = false;
                break;
            }
            
            if ((byte & 0xF) == 0 && (byte1 & 0x20) == 0) {
                //确保 unicode码在范围内 0x0800 ~ 0xFFFF
                noError = false;
                break;
            }
            
            offset += 3;
            unicodeCount += 1;
        } else if ((byte & 0xF8) == 0xF0) {
            //4
            uint8_t byte1 = bytes[offset+1];
            if (byte1 == 0 || (byte1 & 0xC0) != 0x80) {
                noError = false;
                break;
            }
            
            uint8_t byte2 = bytes[offset+2];
            if (byte2 == 0 || (byte2 & 0xC0) != 0x80) {
                noError = false;
                break;
            }
            uint8_t byte3 = bytes[offset+3];
            if (byte3 == 0 || (byte3 & 0xC0) != 0x80) {
                noError = false;
                break;
            }
            
            if ((byte & 0x7) == 0 && (byte1 & 0x30) == 0) {
                //确保 unicode码在范围内 0x0800 ~ 0xFFFF
                noError = false;
                break;
            }
            
            offset += 4;
            unicodeCount += 1;
        } else {
            noError = false;
        }
    }
    return XStringUtf8LayoutMake(begin, offset - begin, unicodeCount);
}

XStringUtf8Layout_s _XUtf8StringLayoutMakeWithCString(const char * _Nonnull str) {
    return __XUtf8StringLayoutMakeWithCString((const uint8_t *)str);
}




// URL 编码协议规定（即 RFC3986 协议）：URL 中只允许包含英文字母、数字、以及这 4 个 - _ . ~ 特殊字符和所有的保留字符。协议中规定了以下保留字符：
// ！ * ’ ( ) ; : @ & = + $ , / ? # [ ]

const uint8_t XBase64Spacing = '=';
const uint8_t XUrlBase64Spacing = '-';

// 排序 从小到大， 保证 data 排序 和 XUrlBase64编码排序规则一致
const uint8_t XUrlBase64Table[64] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '_',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '~'
};

// normal:[0, 63] spacing:64 error:255
uint8_t XUrlBase64Decode(uint32_t c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        return 9 + c - 'A';
    } else if (c == '_') {
        return 36;
    } else if (c >= 'a' && c <= 'z') {
        return 37 + c - 'a';
    } else if (c == '~') {
        return 63;
    } else if (c == XUrlBase64Spacing) {
        return 64;
    } else {
        return 255;
    }
}

const uint8_t XBase64Table[64] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

// normal:[0, 63] spacing:64 error:255
uint8_t XBase64Decode(uint32_t c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return 26 + c - 'a';
    } else if (c >= '0' && c <= '9') {
        return 52 + c - '0';
    } else if (c == '+') {
        return 62;
    } else if (c == '/') {
        return 63;
    } else if (c == XBase64Spacing) {
        return 64;
    } else {
        return 255;
    }
}

const uint8_t XBase32Table[32] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '2', '3', '4', '5', '6', '7'
};

const uint8_t XBech32Table[32] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k', 'm', 'n', 'p', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
};

const uint8_t XHexTable[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};



const XComparisonResult XCompareLessThan = -1;
const XComparisonResult XCompareEqualTo = 0;
const XComparisonResult XCompareGreaterThan = 1;


void XPrint(FILE * __restrict _Nonnull stream, const void * __restrict _Nonnull ptr, size_t size) {
    if (stream && ptr && size > 0) {
        while (0 == fwrite(ptr, size, 1, stream)) {}
    }
}



#pragma mark - crc

static const uint32_t __XCrc32Table[] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL,
    0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
    0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L,
    0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
    0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
    0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
    0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL,
    0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
    0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L,
    0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
    0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L,
    0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
    0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L,
    0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
    0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
    0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
    0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL,
    0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
    0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L,
    0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
    0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL,
    0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
    0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL,
    0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
    0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
    0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
    0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L,
    0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
    0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L,
    0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
    0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L,
    0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
    0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL,
    0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
    0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
    0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL,
    0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
    0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL,
    0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
    0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L,
    0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
    0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L,
    0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
    0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
    0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
    0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L,
    0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
    0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL,
    0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
    0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L,
    0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
    0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL,
    0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
    0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
    0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
    0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L,
    0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
    0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L,
    0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
    0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L,
    0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
    0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L,
    0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
};

static const uint16_t __XCrc16Table[256]= {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};


void XCrc16Init(uint16_t * _Nonnull context) {
    XAssert(context, "");
    *context = 0;
}
void XCrc16Compress(uint16_t * _Nonnull context, const unsigned char * _Nullable buf, uint32_t size) {
    XAssert(context, "");
    if (size > 0) {
        XAssert(buf, "");
    }
    uint16_t crc = *context;
    for (uint32_t iter = 0; iter < size; iter++) {
        crc = (crc<<8) ^ __XCrc16Table[((crc>>8) ^ *buf++)&0x00FF];
    }
    *context = crc;
}
void XCrc16Final(uint16_t * _Nonnull context) {
    XAssert(context, "");
}



void XCrc32Init(uint32_t * _Nonnull context) {
    XAssert(context, "");
    *context = 0xFFFFFFFFU;
}
void XCrc32Compress(uint32_t * _Nonnull context, const unsigned char * _Nullable buf, uint32_t size) {
    XAssert(context, "");
    if (size > 0) {
        XAssert(buf, "");
    }
    uint32_t crc = *context;
    for (uint32_t i = 0; i < size; i++)
        crc = __XCrc32Table[(crc ^ buf[i]) & 0xff] ^ (crc >> 8);
    *context = crc;
}
void XCrc32Final(uint32_t * _Nonnull context) {
    XAssert(context, "");
    *context = ~(*context);
}


ssize_t XCRoundUpSize(ssize_t minSize) {
    size_t size = MAX(0x1000, minSize);
    size_t leadingZeroBitCount = USizeLeadingZerosCount(size);
    size_t one = 1;
    if ((one << (sizeof(size_t) * 8 - 1 - leadingZeroBitCount)) != size) {
        size = one << (sizeof(size_t) * 8 - leadingZeroBitCount);
    }
    XAssert(size <= SSIZE_MAX, "");
    return size;
}

#pragma mark - XBuffer

XBuffer_s * _Nonnull XBufferCreate(ssize_t info, ssize_t minCapacity) {
    ssize_t size = XCRoundUpSize(minCapacity + sizeof(XBuffer_s));
    XBuffer_s * buffer = malloc(size);
    XAssert(buffer, "");
    buffer->info = info;
    buffer->count = 0;
    buffer->capacity = size - sizeof(XBuffer_s);
    return buffer;
}
XBuffer_s * _Nonnull XBufferRealloc(XBuffer_s * _Nonnull buffer, ssize_t minCapacity) {
    XAssert(buffer, "");
    ssize_t size = XCRoundUpSize(MAX(buffer->count + sizeof(XBuffer_s), minCapacity + sizeof(XBuffer_s)));
    ssize_t capacity = size - sizeof(XBuffer_s);
    if (capacity != buffer->capacity) {
        buffer = realloc(buffer, size);
        XAssert(buffer, "");
        buffer->capacity = capacity;
        return buffer;
    } else {
        return buffer;
    }
}

void XBufferDestroy(XBuffer_s * _Nonnull buffer) {
    if (buffer) {
        free(buffer);
    }
}

#pragma mark - XEncodeBuffer

void _XEncodeBufferDefaultRealloc(XEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity) {
    XAssert(minCapacity >= 0, "");
    XAssert(buffer, "");
    ssize_t size = XCRoundUpSize(MAX(buffer->location, minCapacity));
    if (size != buffer->capacity) {
        void * ptr = realloc(buffer->context, size);
        XAssert(ptr, "");
        buffer->context = ptr;
        buffer->bytes = (uint8_t *)ptr;
        buffer->capacity = size;
    }
}
void _XEncodeBufferDefaultDealloc(XEncodeBuffer_s * _Nonnull buffer) {
    if (buffer->context) {
        free(buffer->context);
    }
    bzero(buffer, sizeof(XEncodeBuffer_s));
}
void _XEncodeBufferDefaultFitSize(XEncodeBuffer_s * _Nonnull buffer) {
    XAssert(buffer, "");
    if (buffer->capacity > buffer->location) {
        void * ptr = realloc(buffer->context, buffer->location);
        XAssert(ptr, "");
        buffer->context = ptr;
        buffer->bytes = (uint8_t *)ptr;
        buffer->capacity = buffer->location;
    }
}

//void _XEncodeBufferDataBufferRealloc(XEncodeBuffer_s * _Nonnull buffer, ssize_t minCapacity) {
//    XAssert(minCapacity >= 0, "");
//    XAssert(buffer, "");
//    ssize_t size = XCRoundUpSize(MAX(buffer->location, minCapacity));
//
//    void * ptr = realloc(buffer->bytes, size);
//    XAssert(ptr, "");
//    buffer->context = ptr;
//    buffer->bytes = (uint8_t *)ptr;
//}
//void _XEncodeBufferDataBufferDealloc(XEncodeBuffer_s * _Nonnull buffer) {
//    if (buffer->context) {
//        XObjectRelease(buffer->context);
//    }
//    bzero(buffer, sizeof(XEncodeBuffer_s));
//}
//void _XEncodeBufferDataBufferFitSize(XEncodeBuffer_s * _Nonnull buffer) {
//    if (buffer->context) {
//        XObjectRelease(buffer->context);
//    }
//    bzero(buffer, sizeof(XEncodeBuffer_s));
//}

#pragma mark - memcmp


//返回相等的字节数
static inline size_t _XMemoryCompare8(const XPtr _Nonnull lhs, const XPtr _Nonnull rhs, size_t memorySize) {
    
    const uint64_t * left = lhs;
    const uint64_t * right = rhs;
    size_t size = 0;
    while (memorySize - size >= sizeof(uint64_t)) {
        if (*left != *right) {
            size += sizeof(uint64_t);
            left ++;
            right ++;
        } else {
            return size;
        }
    }
    return size;
}
static inline size_t _XMemoryCompare4(const XPtr _Nonnull lhs, const XPtr _Nonnull rhs, size_t memorySize) {
    const uint32_t * left = lhs;
    const uint32_t * right = rhs;
    size_t size = 0;
    while (memorySize - size >= sizeof(uint32_t)) {
        if (*left != *right) {
            size += sizeof(uint32_t);
            left ++;
            right ++;
        } else {
            return size;
        }
    }
    return size;
}
static inline size_t _XMemoryCompare2(const XPtr _Nonnull lhs, const XPtr _Nonnull rhs, size_t memorySize) {
    const uint16_t * left = lhs;
    const uint16_t * right = rhs;
    size_t size = 0;
    while (memorySize - size >= sizeof(uint16_t)) {
        if (*left != *right) {
            size += sizeof(uint16_t);
            left ++;
            right ++;
        } else {
            return size;
        }
    }
    return size;
}

static inline XComparisonResult _XMemoryCompare(const XPtr _Nonnull lhs, const XPtr _Nonnull rhs, size_t size) {
    if (0 == size) {
        return XCompareEqualTo;
    }
    if (lhs == rhs) {
        return XCompareEqualTo;
    }
    int code = memcmp(lhs, rhs, size);
    if (code == 0) {
        return XCompareEqualTo;
    } else if (code < 0) {
        return XCompareLessThan;
    } else {
        return XCompareGreaterThan;
    }
}

XComparisonResult XMemoryCompare(const XPtr _Nonnull lhs, const XPtr _Nonnull rhs, size_t size) {
    XAssert(size >= 0, "size error");
    if (size == 0) {
        return XCompareEqualTo;
    } else {//size > 0
        XAssert(NULL != lhs, "lhs NULL error");
        XAssert(NULL != rhs, "rhs NULL error");
        if (lhs == rhs) {
            return XCompareEqualTo;
        }
        uintptr_t lhsV = (uintptr_t)lhs;
        uintptr_t rhsV = (uintptr_t)rhs;
        const uint8_t * left = lhs;
        const uint8_t * right = rhs;
        if (size < 64) {
            return _XMemoryCompare(lhs, rhs, size);
        } else {
            size_t len = 0;
            XComparisonResult result = XCompareEqualTo;
            #if CX_TARGET_RT_64_BIT
                if ((lhsV & SIZE_C(0x7)) == (rhsV & SIZE_C(0x7))) {
                    size_t s = lhsV & SIZE_C(0x7);
                    result = _XMemoryCompare((const XPtr)(left + len), (const XPtr)(right + len), s);
                    if (XCompareEqualTo != result) {
                        return result;
                    } else {
                        len += s;
                    }
                    len += _XMemoryCompare8((const XPtr)(left + len), (const XPtr)(right + len), size - len);
                    if (size == len) {
                        return XCompareEqualTo;
                    }
                    return _XMemoryCompare((const XPtr)(left + len), (const XPtr)(right + len), size - len);
                }
            #endif
            if ((lhsV & SIZE_C(0x3)) == (rhsV & SIZE_C(0x3))) {
                size_t s = lhsV & SIZE_C(0x3);
                result = _XMemoryCompare((const XPtr)(left + len), (const XPtr)(right + len), s);
                if (XCompareEqualTo != result) {
                    return result;
                } else {
                    len += s;
                }
                len += _XMemoryCompare4((const XPtr)(left + len), (const XPtr)(right + len), size - len);
                if (size == len) {
                    return XCompareEqualTo;
                }
                return _XMemoryCompare((const XPtr)(left + len), (const XPtr)(right + len), size - len);
            }
            if ((lhsV & SIZE_C(0x1)) == (rhsV & SIZE_C(0x1))) {
                size_t s = lhsV & SIZE_C(0x1);
                result = _XMemoryCompare((const XPtr)(left + len), (const XPtr)(right + len), size - len);
                if (XCompareEqualTo != result) {
                    return result;
                } else {
                    len += s;
                }
                len += _XMemoryCompare2((const XPtr)(left + len), (const XPtr)(right + len), size - len);
                if (size == len) {
                    return XCompareEqualTo;
                }
                return _XMemoryCompare((const XPtr)(left + len), (const XPtr)(right + len), size - len);
            }
            return _XMemoryCompare((const XPtr)(left + len), (const XPtr)(right + len), size - len);
        }
    }
}


XRange_s XMemoryGetRangeOfNonbomUtfString(const uint8_t * _Nonnull bytes, size_t length) {
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
    while (length - offset > 0 && XIndexNotFound == errorIndex) {
        uint8_t byte = bytes[offset];
        if (byte == 0x0) {
            //终止符
            end = offset;
            break;
        } else if (byte < 0x80) {
            //1
            offset += 1;
        } else if ((byte & 0xE0) == 0xC0) {
            //2 byte & 11100000 == 11000000
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
            //3 byte & 11110000 == 11100000

            //3
            if (offset > length-3) {
                errorIndex = offset;
                break;
            }
            
            uint16_t tmp = *(uint16_t *)(bytes + offset + 1);
            
#if CX_TARGET_RT_BIG_ENDIAN
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
            
            //4 byte & 11111000 == 11110000

            if (offset > length-4) {
                errorIndex = offset;
                break;
            }
            uint32_t tmp = *(uint32_t *)(bytes + offset);
            
#if CX_TARGET_RT_BIG_ENDIAN
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
        } else {
            errorIndex = offset;
        }
    }
    if (XIndexNotFound != errorIndex) {
        return XRangeMake(XIndexNotFound, XIndexNotFound);
    } else {
        return XRangeMake(begin, end);
    }
}

