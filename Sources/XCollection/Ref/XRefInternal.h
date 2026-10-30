
#ifndef XRefInternal_h
#define XRefInternal_h

#include "XRef.h"
#include "CXBaseInternal.h"


//#pragma mark - XRStruct
//
//typedef struct {
//    const XStructType_s * _Nonnull type;
//    uint8_t payload[0];
//} _XRStructContent_t;
//typedef struct {
//    _XRBase _runtime;
//    _XRStructContent_t content;
//} _XRStruct;
//
//static inline XStructValue XStructValueMake(const XStructType_s * _Nonnull type, size_t size, XPtr _Nonnull content) {
//    XStructValue result = {
//        .type = type,
//        .size = size,
//        .content = content,
//    };
//    return result;
//}
//static inline XStructValue _XRStructGetConent(_XRStruct * _Nonnull s) {
//    size_t size = 0 == s->content.type->size;
//    uint8_t * payload = s->content.payload;
//    if (0 == size) {
//        size = *((size_t *)payload);
//        return XStructValueMake(s->content.type, size, (XPtr)(payload + sizeof(size_t)));
//    } else {
//        return XStructValueMake(s->content.type, size, (XPtr)(payload));
//    }
//}
//
//
///// TODO: 有一个问题， XRStruct copy 函数需要区分情况 copy 和返回 原对象； 如果内容支持可以copy， 如果内容不支持则需要返回自身， 如果content中有只能关闭1次的资源怎么处理
//
//struct __XStructType;
//typedef struct __XStructType XStructType_s;
//
//typedef struct __XStructContent {
//    const XStructType_s * _Nonnull type;
//    size_t size;
//    XPtr _Nonnull content;
//} XStructValue;
//
//typedef void (*XRStructDeinit_f)(XStructValue s);
//typedef XRef _Nonnull (*XRStructCopy_f)(XStructValue s);
//typedef void (*XRStructHash_f)(XStructValue lhs, XHasher _Nonnull hasher);
//typedef bool_t (*XRStructEqual_f)(XStructValue lhs, XStructValue rhs);
//typedef void (*XRStructDescribe_f)(XStructValue value, _XDescriptionBuffer _Nonnull buffer);
//
//struct __XStructType {
//    size_t size;// 结构体size， 如果size=0，则为动态size类型的struct
//    const char * _Nonnull name;
//    XRStructDeinit_f _Nullable deinit;
//    XRStructCopy_f _Nullable copy;
//    XRStructHash_f _Nullable hash;
//    XRStructEqual_f _Nullable equal;
//    XRStructDescribe_f _Nullable describe;
//    XRStructDescribe_f _Nullable debugDescribe;
//};
//
//extern XRStruct _Nonnull XRStructCreate(XObjectOption flag, const XStructType_s * _Nonnull type, size_t size);
//extern XRStruct _Nonnull XRStructCreateWithValue(XObjectOption flag, XStructValue value);
//
//extern XStructValue XRStructGetValue(XRStruct _Nonnull ref);
//
//
//#pragma mark - XStructTypeByte16
//
//extern const XStructType_s * _Nonnull XStructTypeByte16;
//
//extern XRStructByte16 _Nonnull XRStructByte16Create(XObjectOption flag, XByte16 content);
//extern XRStructByte16 _Nonnull XRStructByte16CreateWithBytes(XObjectOption flag, const uint8_t * _Nonnull content);
//
//extern XByte16 XRStructByte16GetValue(XRStructByte16 _Nonnull ref);





#endif /* XRefInternal_h */
