
#ifndef XStpsp_h
#define XStpsp_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XStpBase.h"
#include "XStpsp.h"

#pragma mark - FrameLayout

#pragma pack(push, 1)


typedef struct {
    uint16_t frameType: 3;// control=0/first/last/part/all/xxx 非0就是应用层type
    // 2的n次个刻度范围，需要 n+1 位 checktime，刻度间隔再大也会有 c/s相差一个刻度的情况
    // 需要加入当前时间进行check, 把时间分成适合的刻度(30s)，比如说如果你的应用程序不接受超出8个刻度的数据。只接受当前刻度前3个刻度后4个刻度的数据
    uint16_t timeOffset: 13;
    uint32_t check; // 签名的时间刻度1s
    uint16_t magicBlockCount;// blockCount = magicBlockCount + 1;
    // 8
    uint32_t sequenceOffset;
    uint16_t remain;
    uint32_t receiveSequenceOffset;
    uint16_t receiveRemain;
    // 16
    //uint8_t session[0];
    //uint8_t key[0];
    //uint8_t context[0];
    //uint8_t seed[0];

    
    
    
    
} XStpspFrameBaseHeader_s  __attribute__((aligned(1)));


typedef struct {
    XStpspFrameBaseHeader_s base;
    uint8_t segmentHeader[24];
} XStpspFrameSegmentStartHeader_s;

typedef struct {
    // custom
    XStpspFrameSegmentStartHeader_s header;
    uint8_t body[0];
} XStpspFrameSegmentStart_s;

typedef struct {
    XStpspFrameBaseHeader_s header;
    uint8_t body[0];
} XStpspFrameSegmentContinue_s;

typedef struct {
    XStpspFrameBaseHeader_s header;
    uint8_t body[0];
} XStpspFrameSegmentFinish_s;





#pragma pack(pop)

#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XStpsp_h */
