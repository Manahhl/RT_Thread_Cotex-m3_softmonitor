/*
 * @Author: jiagebu jack shiyanerzhong@outlook.com
 * @Date: 2024-04-25 16:44:23
 * @LastEditors: jiagebu jack shiyanerzhong@outlook.com
 * @LastEditTime: 2024-04-25 17:59:08
 * @FilePath: \Projectd:\Git_projects\RT_Thread_From0to1_softmonitor\rtthread3.0.3\src\thread.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */

#include "main.h"

/// @brief 由main函数调用
/// @param thread 线程控制块参数指针
/// @param entry 线程函数入口，目标线程函数
/// @param parameter 线程参数
/// @param stack_start 线程栈空间起始地址
/// @param stack_size 线程栈空间大小，单位为字节 定义大小为512字节
/// @return 
rt_err_t rt_thread_init(struct rt_thread *thread,
                        const char       *name,
                        void             (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        rt_uint32_t      stack_size)
{
    /* 线程对象初始化 */ 
    /* 线程结构体开头部分的 4 个成员就是 rt_object_t 成员 */ 
    rt_object_init((rt_object_t)thread, RT_object_Class_Thread, name);
    
    rt_list_init(&(thread->tlist));

    thread->entry = (void *)entry;
    thread->parameter = parameter;
    thread->stack_addr = stack_start;
    thread->stack_size = stack_size;

    thread->sp = (void *)rt_hw_stack_init(thread->entry,
                                          thread->parameter,
                                          (void *)((char *)thread->stack_addr + thread->stack_size - 4));
    return RT_EOK;
} 


