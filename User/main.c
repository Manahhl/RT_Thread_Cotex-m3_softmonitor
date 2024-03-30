/**
*********************************************************
*											main函数
*
*********************************************************
*/
#include "main.h"


ALIGN(RT_ALIGN_SIZE)

rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

rt_uint8_t flag1 = 0;
rt_uint8_t flag2 = 0;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

/* 线程声明 */
void flag1_thread_entry(void *p_arg);
void flag2_thread_entry(void *p_arg);

/**
 * @brief soft_delay
 * 
 * @return 
 */
void delay(rt_uint32_t count)
{
	for (; count != 0; count--);
}

/**
 * @brief 线程1
 * 
 * @param p_arg 
 */
void flag1_thread_entry(void *p_arg)
{
	for (;;)
	{
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);

		rt_schedule();
	}
}

/**
 * @brief 线程2
 *
 * @param p_arg
 */
void flag2_thread_entry(void *p_arg)
{
	for (;;)
	{
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);

		rt_schedule();
	}
}

int main()
{
	rt_system_scheduler_init();

	/* 初始化线程 */
	rt_thread_init(&rt_flag1_thread,			   /* 线程控制块 */
				   flag1_thread_entry,			   /* 线程入口地址 */
				   RT_NULL,						   /* 线程形参 */
				   &rt_flag1_thread_stack[0],	   /* 线程栈起始地址 */
				   sizeof(rt_flag1_thread_stack)); /* 线程栈大小，单位为字节*/
	/* 将线程插入到就绪列表 */
	rt_list_insert_before(&(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist));

	/* 初始化线程 */
	rt_thread_init(&rt_flag2_thread,			   /* 线程控制块 */
				   flag2_thread_entry,			   /* 线程入口地址 */
				   RT_NULL,						   /* 线程形参 */
				   &rt_flag2_thread_stack[0],	   /* 线程栈起始地址 */
				   sizeof(rt_flag2_thread_stack)); /* 线程栈大小，单位为字节 */
	/* 将线程插入到就绪列表 */
	rt_list_insert_before(&(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist));
	
	rt_system_scheduler_start();
}

