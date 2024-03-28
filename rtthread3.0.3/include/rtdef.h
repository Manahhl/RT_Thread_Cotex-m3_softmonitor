#ifndef __RT_DEF_H
#define __RT_DEF_H
#include "rtservice.h"

/***
 * ******************************************************************
 *                  数据类型
 * ******************************************************************
 */
/** 
 * RT-thread 基础数据类型重定义
*/
typedef signed   char      rt_int8_t;
typedef signed   short     rt_int16_t;
typedef signed   long      rt_int32_t;
typedef unsigned char      rt_uint8_t;
typedef unsigned short     rt_uint16_t;
typedef unsigned long      rt_uint32_t;
typedef int                rt_boot_t;

/**
 * 32bit cpu
 */
typedef long            rt_base_t;
typedef unsigned long   rt_ubase_t;

typedef rt_base_t           rt_err_t;
typedef rt_uint32_t         rt_time_t;
typedef rt_uint32_t         rt_tick_t;
typedef rt_base_t           rt_flag_t;
typedef rt_ubase_t          rt_size_t;
typedef rt_ubase_t          rt_dev_t;
typedef rt_base_t           rt_off_t;

/**
 * @brief bool类型重定义
 * 
 */
#define RT_TRUE             1
#define RT_FALSE            0

#ifdef __CC_ARM
#define  rt_inline            static __inline
#define  ALIGN(n)           __attribute__((aligned(n)))
#elif defined (__IAR_SYSTEMS_ICC__)
#define  rt_inline            static inline
#define  ALIGN(n)           PRAGMA(data_alignment=n)
#elif defined (__GUNC__)
#define  rt_inline            static __inline
#define  ALIGN(n)           __attribute__((aligned(n)))
#else
#error not supported tool chain
#endif // __CC_ARM

#define  RT_ALIGN(size,align)       (((size)+(align) - 1)&((aling) - 1))
#define  RT_ALIGN_DOWN(size,align)  ((size) & ~((align) - 1))

#define  RT_NULL                    (0)

/**
 * @brief rt_thread 线程控制块
 * 
 */
struct rt_thread
{
    void *sp;//线程栈指针
    void *entry;//线程入口地址
    void *parameter;//线程形参
    void *stack_addr;//线程栈大小，单位为字节byte
    rt_uint32_t stack_size;

    rt_list_t tlist;//线程列表节点
};
typedef struct rt_thread *rt_thread_t;




/**
 * @brief RT-thead错误码重定义
 * 
 */
#define RT_EOK 0;//无错误

#endif // __RT_DEF_H

