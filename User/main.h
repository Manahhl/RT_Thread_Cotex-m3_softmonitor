/*
 * @Author: jiagebu jack shiyanerzhong@outlook.com
 * @Date: 2024-04-25 16:44:22
 * @LastEditors: jiagebu jack shiyanerzhong@outlook.com
 * @LastEditTime: 2024-04-25 17:59:43
 * @FilePath: \Projectd:\Git_projects\RT_Thread_From0to1_softmonitor\User\main.h
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __MAIN_H
#define __MAIN_H

#include "rtconfig.h"
#include "rtdef.h"
#include "rtthread.h"
#include "ARMCM3.h"
#include "rtservice.h"

rt_err_t rt_thread_init(struct rt_thread *thread,
                        const char  *name,
                        void (*entry)(void *parameter),
                        void *parameter,
                        void *stack_start,
                        rt_uint32_t stack_size);


rt_uint8_t *rt_hw_stack_init(void *tentry,
                            void *parameter,
                            rt_uint8_t *stack_addr);
void rt_object_init(struct rt_object *object, enum rt_object_class_type type, const char *name);
char *rt_strncpy(char *destination, const char *source, rt_ubase_t n);														
void rt_system_scheduler_init(void);
void rt_schedule(void);
void rt_system_scheduler_start(void);

#endif
