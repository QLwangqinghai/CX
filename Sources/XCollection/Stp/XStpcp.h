
#ifndef XStpcp_h
#define XStp_h

#if defined(__cplusplus)
extern "C" {
#endif

#include "XStpBase.h"



#pragma mark - FrameLayout

// SPacket_s
#pragma pack(push, 1)

// 协议层数据块大小为8字节
// 应用层数据块大小协商

// 协议分为大包协议/小包协议，不同的协议值， 大包用于少量socket，大量数据， 小包适合大量socket，每个socket的数据量不大
// 大包协议sequence 用更大的uint64_t
// 单帧数据不应该过大， 2k/4k/8k/16k/32k/64k/128/256k 建联阶段协商
// 应用层的data最大blocksize，totalsize 建联阶段协商最大值， blocksize：支持 1/8/16， 协议层如果有aes块加密，则16字节更优；如果应用层的data 不是blocksize对齐的，协议层需要对data，进行padding， padding方式建联阶段协商

// 单帧数据 的size 应该受应用层数据影响， 应用层最大发4g数据时，帧size应该不小于16k
// 1个流的数据分解成帧时 数量应该小于64k

// 4g  16k: 16k* 16/8 = 32k
// 4g  8k: 64k
// 4g  4k: 128k

// basesequence 动态更新
// 校验码
// sendAll sendLast  sendFirst sendPart; sendAll sendLast 需要知道负载长度， sendFirst sendPart 是满负载

// 关于加密： 应用层的数据应用自己加密。协议层的数据协议层自己加密，唯一可共享的是aeskey。或者一下其他的上下文信息，可以算出key

typedef struct {
    uint32_t frameType: 3;// control/ack/sendfirst/sendremain
    uint32_t controlType: 5;// contextControl/connect
    uint32_t controlSubtype: 8;// barrier&heart
    uint32_t check;
    // 6
    
    
    // 12
    uint64_t time;
    // 20
    uint32_t sendSequence;
    uint16_t sendRemain;
    uint32_t receiveSequence;
    uint16_t receiveRemain;
} XStpcpControlFrameHeader_s;

typedef struct {
    uint32_t frameType: 3;// control/ack/sendfirst/sendremain
    uint32_t controlType: 5;// contextControl/connect
    uint32_t controlSubtype: 8;// barrier&heart
    uint32_t check;
    // 6
    
    
    // 10
    uint64_t time;
    // 18
    uint32_t sendSequence;
    uint32_t sendRemain: 16;
    uint32_t receiveSequence;
    uint32_t receiveRemain: 16;
} XStpcpControlBarrierFrame_s;



typedef struct {
    // 11
    uint8_t controlSubtype;
    // 12
    uint8_t controlType;
    
    
    
    
    
    // 13
    uint8_t frameType;
    // 14
    uint32_t time;
    // 18
    uint16_t magicBlockCount;
    // 20
    uint32_t sendSequence;
    uint16_t sendRemain;
    uint32_t receiveSequence;
    uint16_t receiveRemain;
    
    // option uint8_t segmentHeader[24];
} XStpcpFrameSignContext_s;

typedef struct {
    uint16_t frameType: 3;// control=0/first/last/part/all/xxx 非0就是应用层type
    // 2的n次个刻度范围，需要 n+1 位 checktime，刻度间隔再大也会有 c/s相差一个刻度的情况
    // 需要加入当前时间进行check, 把时间分成适合的刻度(30s)，比如说如果你的应用程序不接受超出8个刻度的数据。只接受当前刻度前3个刻度后4个刻度的数据
    uint16_t timeOffset: 13;
    uint32_t check; // 签名的时间刻度1s
    uint16_t magicBlockCount;// blockCount = magicBlockCount + 1;
    // 8
    uint16_t sequenceOffset;
    uint16_t remain;
    uint16_t receiveSequenceOffset;
    uint16_t receiveRemain;
    // 16
} XStpcpFrameBaseHeader_s  __attribute__((aligned(1)));

// first/all:   part/last: padding4
// first/part:  not need length
// all/last length>=0

typedef struct {
    uint8_t data[0];
    uint8_t padding[0];
} XStpcpFrameSegmentBody_s;

typedef struct {
    XStpcpFrameBaseHeader_s base;
    uint8_t segmentHeader[24];
} XStpcpFrameSegmentStartHeader_s;

typedef struct {
    // custom
    XStpcpFrameSegmentStartHeader_s header;
    XStpcpFrameSegmentBody_s body;
} XStpcpFrameSegmentStart_s;

typedef struct {
    XStpcpFrameBaseHeader_s header;
    XStpcpFrameSegmentBody_s body;
} XStpcpFrameSegmentContinue_s;

typedef struct {
    XStpcpFrameBaseHeader_s header;
    XStpcpFrameSegmentBody_s body;
} XStpcpFrameSegmentFinish_s;



// Frame - segment

// Frame 协议层
// Segment 应用层


// 16k

//  uri-kind-method-tag 标识一条数据的唯一性， 这部分数据对协议层是暴露的， 只有data 是透明的； 就像调用函数一样 uri 是handler的id method是告诉handler做什么，key-data函数入参， kind 区分是调用还是回馈（request、response） 如果是应答模式则 2个包出了data部分和kind 其他应该是一致的
// key 理论上不应该传递数据， 应该是data加解密用的

// 20 字节
typedef struct {
    uint64_t uri;
    uint8_t kind;// request, response, notification, 等
    uint8_t method;
    uint16_t tag;
    uint32_t dataInfo;
    uint8_t key[8];
} XStpcpSegmentHeader_s;
typedef struct {
    uint32_t blockCount: 24; // <=(16m - 1) * blocksize
    uint32_t coding: 8;
} XStpcpSegmentDataInfo_s;
#pragma pack(pop)



#pragma mark - Types



typedef struct {
    uint32_t type;// control/ack/sendfirst/sendremain
    uint32_t sequence;
    uint16_t uri;
    uint16_t cmd;
    uint64_t key;
} SPacket_s;

// 16

typedef struct {
    
    uint32_t type;// control/ack/sendfirst/sendremain
    uint32_t clientSequence;
    uint32_t clientRemain: 16;
    uint32_t serverSequence;
    uint32_t serverRemain: 16;
    uint32_t time;
} SAck_s;
// 14 +
typedef struct {
    
    uint32_t type;// control/ack/sendfirst/sendremain
    uint32_t sendSequence;
    uint32_t sendRemain;
    uint32_t readSequence;
    uint32_t sendSequenceSegmentId;

    
    uint32_t check;

} XStpcpControlFrame_s;


// domain-uri-suburi-method 4 字节不够用？
typedef struct {
    uint32_t location: 24;// like http-url
    uint32_t method: 8;// like http-method
} StpcpUri_s;






#pragma mark - Apis

// require: length > 0;
// void XStpcpSendRequest(uint32_t uri, uint16_t sequence, uint8_t keytype, uint8_t key[8], size_t length, void * data);
// void onXStpcpSendResponse(uint32_t uri, uint16_t sequence, uint8_t keytype, uint8_t key[8], size_t length, void * data);

// uint64_t XStpcpNoKey = 0;
// uint64_t XStpcpDecodeData(void * connect, uint32_t uri, uint16_t sequence, size_t length, void * data); 返回一个key
// void XStpcpEncodeData(void * connect, uint32_t uri, uint16_t sequence, uint64_t key, size_t length, void * data);





#if defined(__cplusplus)
}  // extern C
#endif

#endif /* XStp_h */
