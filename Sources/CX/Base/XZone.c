
#include "XBaseType.h"
#include "XProcess.h"


/*
 
 
 多个group
 
 isEmpty 1 bit 是否有空闲: 1 表示空
 isIdle 1 bit 是否正在使用中: 1 表示空闲
 
 dequeue = (~isEmpty) & isIdle
 enqueue = isEmpty & isIdle
 
 16 个组
 
 时间长了 不再均衡怎么办
 
 平衡策略
 
 
 
 
 
 
 
 
 
 
 
 
 */
