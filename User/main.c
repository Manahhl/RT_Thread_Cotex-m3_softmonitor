/**
*********************************************************
*											main����
*
*********************************************************
*/
#include "main.h"
#include "stdio.h"

rt_uint8_t flag1 = 0;
rt_uint8_t flag2 = 0;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

ALIGN(RT_ALIGN_SIZE)//����ֻ�������·��ı���
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

/* �߳����� */
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
 * @brief �߳�1
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
		//putchar((int)(p_arg));

		rt_schedule();
	}
}

/**
 * @brief �߳�2
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

	//���������̴߳����thread.c�ļ�
	/* ��ʼ���߳� */
	rt_thread_init(&rt_flag1_thread,			   /* �߳̿��ƿ� */
				   flag1_thread_entry,			   /* �߳���ڵ�ַ */
				   RT_NULL,						   /* �߳��β� */
				   &rt_flag1_thread_stack[0],	   /* �߳�ջ��ʼ��ַ */
				   sizeof(rt_flag1_thread_stack)); /* �߳�ջ��С����λΪ�ֽ�*/
	/* ���̲߳��뵽�����б� */
	rt_list_insert_before(&(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist));

	/* ��ʼ���߳� */
	rt_thread_init(&rt_flag2_thread,			   /* �߳̿��ƿ� */
				   flag2_thread_entry,			   /* �߳���ڵ�ַ */
				   RT_NULL,						   /* �߳��β� */
				   &rt_flag2_thread_stack[0],	   /* �߳�ջ��ʼ��ַ */
				   sizeof(rt_flag2_thread_stack)); /* �߳�ջ��С����λΪ�ֽ� */
	/* ���̲߳��뵽�����б� */
	rt_list_insert_before(&(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist));
	
	rt_system_scheduler_start();
}

