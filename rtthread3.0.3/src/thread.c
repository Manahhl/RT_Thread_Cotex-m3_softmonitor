/**
 * @file thread.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-28
 * 
 * @copyright Copyright (c) 2024
 * 
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
                        void             (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        rt_uint32_t      stack_size)
{
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


