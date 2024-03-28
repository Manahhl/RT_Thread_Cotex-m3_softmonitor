/**
*********************************************************
*											main函数
*
*********************************************************
*/
#include "rtdef.h"
#include "rtconfig.h"

ALIGN(RT_ALIGN_SIZE)

rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

rt_uint8_t flag1 = 0;
rt_uint8_t flag2 = 0;

struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

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
	}
}

int main()
{
	for(;;)
	{
	}
}

