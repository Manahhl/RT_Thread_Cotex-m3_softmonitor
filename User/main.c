/**
*********************************************************
*											main����
*
*********************************************************
*/
#include "main.h"
<<<<<<< HEAD
=======
<<<<<<< HEAD
#include "stdio.h"
=======
>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf


ALIGN(RT_ALIGN_SIZE)

rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];
>>>>>>> 15defa99e7e4f7da199465be6f38fedccd8f08cc

rt_uint8_t flag1 = 0;
rt_uint8_t flag2 = 0;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

<<<<<<< HEAD
=======
<<<<<<< HEAD
ALIGN(RT_ALIGN_SIZE)//����ֻ�������·��ı���
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

=======
>>>>>>> 15defa99e7e4f7da199465be6f38fedccd8f08cc
>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf
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
<<<<<<< HEAD
=======
<<<<<<< HEAD
		//putchar((int)(p_arg));
=======
>>>>>>> 15defa99e7e4f7da199465be6f38fedccd8f08cc
>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf

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

<<<<<<< HEAD
=======
<<<<<<< HEAD
	//���������̴߳����thread.c�ļ�
=======
>>>>>>> 15defa99e7e4f7da199465be6f38fedccd8f08cc
>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf
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

