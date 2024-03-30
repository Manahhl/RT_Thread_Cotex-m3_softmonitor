#ifndef __RT_DEF_H
#define __RT_DEF_H
#include "main.h"

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

#define  RT_ALIGN(size,align)       (((size)+(align) - 1)& ~((aling) - 1))
#define  RT_ALIGN_DOWN(size,align)  ((size) & ~((align) - 1))

#define  RT_NULL                    (0)

/**
 * @brief 线程列表节点
 * 
 */
struct rt_list_node
{
    struct rt_list_node *next;
    struct rt_list_node *prev;
};
typedef struct rt_list_node rt_list_t;

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

/* RT-Thread 错误码重定义 */
#define RT_EOK 0      /**< There is no error */
#define RT_ERROR 1    /**< A generic error happens */
#define RT_ETIMEOUT 2 /**< Timed out */
#define RT_EFULL 3    /**< The resource is full */
#define RT_EEMPTY 4   /**< The resource is empty */
#define RT_ENOMEM 5   /**< No memory */
#define RT_ENOSYS 6   /**< No system */
#define RT_EBUSY 7    /**< Busy */
#define RT_EIO 8      /**< IO error */
#define RT_EINTR 9    /**< Interrupted system call */
#define RT_EINVAL 10  /**< Invalid argument */

#endif // __RT_DEF_H

