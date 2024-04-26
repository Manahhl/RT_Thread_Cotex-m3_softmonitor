#include "main.h"

/* ���ڴ洢��һ���̵߳�ջ�� sp ��ָ�� */
rt_uint32_t rt_interrupt_from_thread;

/* ���ڴ洢��һ����Ҫ���е��̵߳�ջ�� sp ��ָ�� */
rt_uint32_t rt_interrupt_to_thread;

/* PendSV �жϷ�����ִ�б�־ */
rt_uint32_t rt_thread_switch_interrupt_flag;

struct exception_stack_frame 
{
    /* �쳣����ʱ���Զ����ص� CPU �Ĵ��������� */
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r12;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t psr;
    
};
struct stack_frame 
{
    /* �쳣����ʱ�����ֶ����ص� CPU �Ĵ��������� */
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t r11;
    struct exception_stack_frame exception_stack_frame;
    
};

rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr)
{
    struct stack_frame *stack_frame;
    rt_uint8_t         *stk;
    unsigned long       i;

    stk  = stack_addr + sizeof(rt_uint32_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);
    stk -= sizeof(struct stack_frame);

    stack_frame = (struct stack_frame *)stk;

    /* init all register */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = 0; 									     /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

    /* return task's current stack address */
    return stk;
}



//rt_uint8_t *rt_hw_stack_init(void *tentry,
//                            void *parameter,
//                            rt_uint8_t *stack_addr)
//{
//    struct stack_frame *stack_frame;
//    rt_uint8_t         *stk;
//    unsigned long      i;
//    //��ȡջ��ָ��
//    stk = stack_addr + sizeof(rt_uint32_t);

//    /* �� stk ָ������ 8 �ֽڶ��� */
//    stk = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);

//    /* stk ָ����������ƶ� sizeof(struct stack_frame)��ƫ�� */
//    stk -= sizeof(struct stack_frame);

//    /* �� stk ָ��ǿ��ת��Ϊ stack_frame ���ͺ�浽 stack_frame */
//    stack_frame = (struct stack_frame *)stk;

//    /* �� stack_frame Ϊ��ʼ��ַ����ջ�ռ������ sizeof(struct stack_frame)���ڴ��ʼ��Ϊ 0xdeadbeef */
//    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i++)
//    {
//        ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
//    }

//    /* ��ʼ���쳣����ʱ�Զ�����ļĴ��� */
//    stack_frame->exception_stack_frame.r0 = (unsigned long)parameter;                                            /* r0 : argument */
//    stack_frame->exception_stack_frame.r1 = 0;                                                                   /* r1 */
//    stack_frame->exception_stack_frame.r2 = 0;                                                                   /* r2 */
//    stack_frame->exception_stack_frame.r3 = 0;                                                                   /* r3 */
//    stack_frame->exception_stack_frame.r12 = 0;                                                                  /* r12 */
//    stack_frame->exception_stack_frame.lr = 0;                                                                   /* lr����ʱ��ʼ��Ϊ 0 */
//    stack_frame->exception_stack_frame.pc = (unsigned long)tentry;                                               /* entry point, pc */
//    stack_frame->exception_stack_frame.psr = 0x01000000L;                                                        /* PSR */

//    /*����ջ��ָ��*/
//    return stk;
//}


