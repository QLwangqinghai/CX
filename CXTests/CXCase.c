
#include <CX/XDeque.h>
#include <CX/XObject.h>
#include <CX/CX.h>

void * _Nonnull _XDequeElementAtLocation(XDeque_s * _Nonnull deque, size_t elementSize, ssize_t location) {
    XRingBuffer_s * buffer = deque->buffer;
    return buffer->items + elementSize * location;
}

void CXCaseTestXDeque(void) {
//    size_t elementSize = sizeof(size_t);
//    XDeque_s _deque = {};
//    XDequeInit(&_deque, elementSize, 12);
//    XDeque_s * buffer = &_deque;
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = i;
//        memcpy(element, &v, elementSize);
//    }
//
//    //    6, 7, 8, 9, 10, 11, | 0, 1, 2, 3, 4, 5,
//
//    for (size_t i=6; i<12; i++) {
//        void * element = _XDequeElementAtLocation(buffer, elementSize, i);
//        size_t v = 0;
//        memcpy(&v, element, elementSize);
//        XAssert(v == i-6, "");
//    }
//    for (size_t i=0; i<6; i++) {
//        void * element = _XDequeElementAtLocation(buffer, elementSize, i);
//        size_t v = 0;
//        memcpy(&v, element, elementSize);
//        XAssert(v == i+6, "");
//    }
//
//    // 0, 1 , 2, 3, 4, ,5 , 6, 7, 8, 9, 10, 11
//
//    //
//
//
//    size_t values1[12] = {
//        0, 1 , 2, 3, 4, 5 , 6, 4, 5 , 6, 7, 11
//    };
//
//    XDequeMove(buffer, elementSize, 4, 4, 3);
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = 0;
//        memcpy(&v, element, elementSize);
//        XAssert(v == values1[i], "");
//    }
//
//
//
//
//
//
//    // 0, 1 , 2, 3, 4, ,5 , 6, 7, 8, 9, 10, 11
//
//    size_t values[12] = {
//        0, 1 , 2, 3, 7, 8, 9, 10, 8, 9, 10, 11
//    };
//
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = i;
//        memcpy(element, &v, elementSize);
//    }
//    XDequeMove(buffer, elementSize, 7, 4, -3);
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = 0;
//        memcpy(&v, element, elementSize);
//        XAssert(v == values[i], "");
//    }
//
//
//
//    // 0, 1 , 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
//
//    size_t values2[12] = {
//        2, 3, 4, 3, 4, 5, 6, 7, 8, 9, 10, 11
//    };
//
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = i;
//        memcpy(element, &v, elementSize);
//    }
//    XDequeMove(buffer, elementSize, 2, 3, -2);
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = 0;
//        memcpy(&v, element, elementSize);
//        XAssert(v == values2[i], "");
//    }
//
//    size_t values3[12] = {
//        0, 1 , 2, 3, 2, 3, 4, 7, 8, 9, 10, 11
//    };
//
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = i;
//        memcpy(element, &v, elementSize);
//    }
//    XDequeMove(buffer, elementSize, 2, 3, 2);
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = 0;
//        memcpy(&v, element, elementSize);
//        XAssert(v == values3[i], "");
//    }
//
//
//
//
//
//
//    for (size_t i=0; i<12; i++) {
//        void * element = XDequeElementAtIndex(buffer, elementSize, i);
//        size_t v = i;
//        memcpy(element, &v, elementSize);
//    }
//
//    XDeque_s _deque2 = {};
//    XDequeInit(&_deque2, elementSize, 12);
//    XDeque_s * bufferB = &_deque2;
////    XDequeCopyElements(bufferB, elementSize, 0, 12, buffer);
////    for (size_t i=0; i<12; i++) {
////        void * element = XDequeElementAtIndex(bufferB, elementSize, i);
////        size_t v = 0;
////        memcpy(&v, element, elementSize);
////        XAssert(v == i, "");
////    }
//    printf("CXCaseTestXDeque OK\n");
//
}


void CXCaseDequeCapacity(void) {
//    size_t elementSize = sizeof(size_t);
    
    size_t lastUp = 0;
    size_t lastDown = 0;
    
    for (size_t i=0; i<SIZE_MAX; i++) {
        size_t up = XCollectionSizeRoundUp(i);
        size_t down = XCollectionSizeRoundDown(i);
        if ((up != lastUp || down != lastDown) && up != down) {
            printf("%zx  up: %zx  down: %zx\n", i, up, down);
        }
        lastUp = up;
        lastDown = down;
    }
    
    
    
}

void testNumber(void) {
    float64_t f = 1.0 / 3;
    XNumberRef number = XNumberCreateWithFloat64(0, f);
    XNumberValue_s value = XNumberGetValue(number);
    XAssert(value.storageType == XNumberStorageTypeFloat, "");
    XAssert(value.storage.f == f, "");
    XObjectRelease(number);
}
void testSet(void) {
    XSetRef set = XMutableSetCreate(0, 12);
    
    XNumberRef n0 = XNumberCreateWithFloat64(0, 1.0/3);
    XNumberRef n1 = XNumberCreateWithFloat64(0, 1.0/30);

    XMutableSetInsert(set, n0, NULL);
    XMutableSetInsert(set, n1, NULL);

    XAssert(XSetContains(set, n0), "");
    XAssert(XSetContains(set, n1), "");
    
    XObjectRelease(n0);
    XObjectRelease(n1);
    
    XAssert(XSetGetCount(set) == 2, "");
    XObjectRelease(set);
}

void testMap(void) {
    XMapRef map = XMutableMapCreate(0, 12);
    
    XNumberRef n0 = XNumberCreateWithFloat64(0, 1.0/3);
    XNumberRef n1 = XNumberCreateWithFloat64(0, 1.0/30);

    XMutableMapSetValue(map, n1, n0, NULL);
    XObjectRelease(n0);
    XObjectRelease(n1);
    
    XAssert(XMapGetCount(map) == 1, "");
    XObjectRelease(map);
}




void CXCaseRun(void) {
//    CXCaseDequeCapacity();
    testZone();
    testNumber();
    testSet();
    testMap();
}
