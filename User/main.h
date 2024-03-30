#ifndef __MAIN_H
#define __MAIN_H
#include "rtconfig.h"
#include "rtdef.h"
#include <rtthread.h>
#include "ARMCM3.h"
#include "rtservice.h"
rt_uint8_t *rt_hw_stack_init(void *tentry,
                            void *parameter,
                            rt_uint8_t *stack_addr);
void rt_system_scheduler_init(void);
void rt_schedule(void);
void rt_system_scheduler_start(void);
#endif
