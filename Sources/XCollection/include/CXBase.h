
#ifndef CXBase_h
#define CXBase_h

#if defined(__cplusplus)
extern "C" {
#endif

#if __has_include(<CXCore/CXCore.h>)
#include <CXCore/CXCore.h>
#else
#include "CXCore.h"
#endif

typedef XObjectRef XHashTableRef;
typedef XHashTableRef XSetRef;
typedef XHashTableRef XMapRef;

typedef XObjectRef XOrderedHashTableRef;
typedef XOrderedHashTableRef XOrderedSetRef;
typedef XOrderedHashTableRef XOrderedMapRef;

typedef XObjectRef XParameterBufferRef;
typedef XObjectRef XClosureRef;

#pragma mark - classes

extern XClassRef _Nonnull XClosureClass;
extern XClassRef _Nonnull XParameterBufferClass;
extern XClassRef _Nonnull XSetClass;
extern XClassRef _Nonnull XMapClass;
extern XClassRef _Nonnull XOrderedSetClass;
extern XClassRef _Nonnull XOrderedMapClass;

#pragma mark - XParameterBuffer


#pragma mark - XParameterBufferType

struct __XParameterBufferType;
typedef struct __XParameterBufferType XParameterBufferType_s;
typedef void (*XParameterBufferRetain_f)(const XParameterBufferType_s * _Nonnull type, void * _Nonnull buffer);
typedef void (*XParameterBufferRelease_f)(const XParameterBufferType_s * _Nonnull type, void * _Nonnull buffer);
struct __XParameterBufferType {
    size_t size;
    const char * _Nonnull name;
    XParameterBufferRetain_f _Nullable retain;
    XParameterBufferRelease_f _Nullable release;
};
extern const XParameterBufferType_s __XParameterBufferTypeXObject;

static inline void XParameterBufferRetain(const XParameterBufferType_s * _Nonnull type, void * _Nonnull buffer) {
    if (type->retain) {
        type->retain(type, buffer);
    }
}
static inline void XParameterBufferRelease(const XParameterBufferType_s * _Nonnull type, void * _Nonnull buffer) {
    if (type->release) {
        type->release(type, buffer);
    }
}

#define XParameterBufferTypeMake(Size, Type, Retain, Release) {\
    .size = Size,\
    .name = #Type,\
    .retain = Retain,\
    .release = Release,\
}

/// value 会被copy 到XValue 中，copy 执行后会调用retaindata,
extern XParameterBufferRef _Nonnull XParameterBufferCreate(XObjectOption flag, const XParameterBufferType_s * _Nonnull type, const void * _Nonnull content);
extern const XParameterBufferType_s * _Nonnull XParameterBufferGetType(XParameterBufferRef _Nonnull ref);
extern void * _Nonnull XParameterBufferGetContent(XParameterBufferRef _Nonnull ref);

#pragma mark - XClosure

// 回调闭包： 代理对象、被代理对象、数据

struct __XMethod;
typedef struct __XMethod XMethod_s;

///  超级函数 handler.call(handler, target, input, output), target 为 来自谁/谁回调/inputBuffer 为附带参数
typedef void (*XFunction_f)(void * _Nullable context, void * _Nullable handler, void * _Nullable target, void * _Nullable inputBuffer, void * _Nullable outputBuffer);

///  超级方法: 匹配XFunction_f， 但是第一个参数必须是 const XMethod_s *类型， handler.call(sel, handler, target, input, output), target 为 来自谁/谁回调/inputBuffer 为附带参数
typedef void (*XMethod_f)(const XMethod_s * _Nonnull sel, void * _Nullable handler, void * _Nullable target, void * _Nullable inputBuffer, void * _Nullable outputBuffer);

/// 超级函数：定义了函数信息(handler, target, input, output), handler/target是指针类型 ，input/output是buffer类型， handler/target/input copy到堆上时要执行retian操作，释放时要执行release操作； 任何函数都可以封装成超级函数
struct __XMethod {
    // context retain/release
    const XPointerType_s * _Nonnull handlerType;
    const XPointerType_s * _Nullable targetType;
    const XParameterBufferType_s * _Nonnull parameterBufferType;
    size_t outputBufferSize;
    const char * _Nonnull outputTypeName;
    const char * _Nonnull dispatchFuncName;
    XMethod_f _Nonnull dispatchFunc;
    const char * _Nonnull name;
    void * _Nonnull method;
};

static inline void XMethodExecute(const XMethod_s * _Nonnull method, void * _Nullable handler, void * _Nullable target, void * _Nullable inputBuffer, void * _Nullable outputBuffer) {
    method->dispatchFunc(method, handler, target, inputBuffer, outputBuffer);
}

#define XMethodMake(HandlerTypePtr, TargetTypePtr, ParameterBufferTypePtr, OutputType, DispatchFunc, Method) {\
    .handlerType = HandlerTypePtr,\
    .targetType = TargetTypePtr,\
    .parameterBufferType = ParameterBufferTypePtr,\
    .outputBufferSize = sizeof(OutputType),\
    .outputTypeName = #OutputType,\
    .name = ##Method,\
    .method = Method,\
    .dispatchFuncName = #DispatchFunc,\
    .dispatchFunc = DispatchFunc,\
}

// 是展开 还是不展开
typedef struct __XClosureBuffer {
    size_t size;
    void * _Nonnull buffer;
} XClosureBuffer_s;

extern void _XClosureDispatchFunction(const XMethod_s * _Nonnull sel, void * _Nullable handler, void * _Nullable target, void * _Nullable inputBuffer, void * _Nullable outputBuffer);

#define XClosureMethodMake(InputType, OutputType, ClosureFunc) XMethodMake(&__XPointerTypeXObject, &__XPointerTypeXObject, InputType, OutputType, _XClosureDispatchFunction, ClosureFunc)

typedef void * XClosureInputBuffer_t;
typedef void * XClosureOutputBuffer_t;

// 静态定义出来：inputSize, outputSize
/// 一个closure 包含3个基础部分， context部分，一些必要的上下文信息，input: 调用方的输入，output: 函数的输出
typedef void (*XClosureExecute_f)(XObjectRef _Nullable context, XObjectRef _Nullable target, void * _Nullable inputBuffer, void * _Nullable outputBuffer);


/// 谁
/// handler.doFuncation(handler, target, input, outputBuffer)

/// context 会被copy到堆上， 然后执行retain操作，XClosureRef释放时 会对context执行release操作
extern XClosureRef _Nonnull XClosureCreate(XObjectOption option, const XMethod_s * _Nonnull method, XObjectRef _Nullable handler);

extern const XMethod_s * _Nonnull XClosureGetMethod(XClosureRef _Nonnull object);

/// outputBuffer 可以为NULL，意味着丢弃返回值， inputBuffer 取决于XClosure中的XMethod_s中的inputBufferSize
extern void XClosurePerform(XClosureRef _Nonnull ref, XObjectRef _Nullable target, XClosureInputBuffer_t _Nullable inputBuffer, XClosureOutputBuffer_t _Nullable outputBuffer);



#if defined(__cplusplus)

}  // extern C
#endif



#endif /* CXBase_h */
