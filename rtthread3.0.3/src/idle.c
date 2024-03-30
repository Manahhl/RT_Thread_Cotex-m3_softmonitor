/*
 * @Author: jiagebu jack shiyanerzhong@outlook.com
 * @Date: 2024-04-25 17:33:02
 * @LastEditors: jiagebu jack shiyanerzhong@outlook.com
 * @LastEditTime: 2024-04-25 17:56:54
 * @FilePath: \Projectd:\Git_projects\RT_Thread_From0to1_softmonitor\rtthread3.0.3\src\idle.c
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#include "main.h"

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
#define IDLE_THREAD_STACK_SIZE 512

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_thread_stack[IDLE_THREAD_STACK_SIZE];

/* 空闲线程的线程控制块 */
struct rt_thread idle;

rt_ubase_t rt_idletask_ctr = 0;

void rt_thread_idle_entry(void *parameter)
{
	parameter = parameter;
	while (1)
	{
		rt_idletask_ctr ++;
	}
}

void rt_thread_idle_init(void)
{

	/* 初始化线程 */
		rt_thread_init(&idle,
					   "idle",
					   rt_thread_idle_entry,
					   RT_NULL,
					   &rt_thread_stack[0],
					   sizeof(rt_thread_stack));

	/* 将线程插入到就绪列表 */ 
		rt_list_insert_before(&(rt_thread_priority_table[RT_THREAD_PRIORITY_MAX - 1]),&(idle.tlist));
}
