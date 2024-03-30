/**
 * @file object.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "main.h"

static struct rt_object_information rt_object_container[RT_Object_Info_Unknown] =
{
    /* 初始化对象容器 - 线程 */
    {RT_Object_Class_Thread, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Thread), sizeof(struct rt_thread)},
#ifdef RT_USING_SEMAPHORE
    /* 初始化对象容器 - 信号量 */
    {RT_Object_Class_Semaphore, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Semaphore), sizeof(struct rt_semaphore)},
#endif

#ifdef RT_USING_MUTEX
    /* 初始化对象容器 - 互斥量 */
    {RT_Object_Class_Mutex, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Mutex), sizeof(struct rt_mutex)},
#endif

#ifdef RT_USING_EVENT
    /* 初始化对象容器 - 事件 */
    {RT_Object_Class_Event, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Event), sizeof(struct rt_event)},
#endif

#ifdef RT_USING_MAILBOX
    /* 初始化对象容器 - 邮箱 */
    {RT_Object_Class_MailBox, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MailBox), sizeof(struct rt_mailbox)},
#endif

#ifdef RT_USING_MESSAGEQUEUE
    /* 初始化对象容器 - 消息队列 */
    {RT_Object_Class_MessageQueue, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MessageQueue), sizeof(struct rt_messagequeue)},
#endif

#ifdef RT_USING_MEMHEAP
    /* 初始化对象容器 - 内存堆 */
    {RT_Object_Class_MemHeap, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemHeap), sizeof(struct rt_memheap)},
#endif

#ifdef RT_USING_MEMPOOL
    /* 初始化对象容器 - 内存池 */
    {RT_Object_Class_MemPool, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemPool), sizeof(struct rt_mempool)},
#endif

#ifdef RT_USING_DEVICE
    /* 初始化对象容器 - 设备 */
    {RT_Object_Class_Device, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Device), sizeof(struct rt_device)},
#endif

    //初始化对象->初始化定时器
    //{RT_Object_Class_Timer, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Timer), sizeof(struct rt_timer)},
#ifdef RT_USING_MODULE
    /* 初始化对象容器 - 模块 */
    {RT_Object_Class_Module, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Module), sizeof(struct rt_dlmodule)},
#endif

};


