#ifndef __MAIN_H
#define __MAIN_H
<<<<<<< HEAD
=======
<<<<<<< HEAD

>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf
#include "rtconfig.h"
#include "rtdef.h"
#include "rtthread.h"
#include "ARMCM3.h"
#include "rtservice.h"
<<<<<<< HEAD
=======

=======
#include "rtconfig.h"
#include "rtdef.h"
#include <rtthread.h>
#include "ARMCM3.h"
#include "rtservice.h"
>>>>>>> 15defa99e7e4f7da199465be6f38fedccd8f08cc
>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf
rt_uint8_t *rt_hw_stack_init(void *tentry,
                            void *parameter,
                            rt_uint8_t *stack_addr);
void rt_system_scheduler_init(void);
void rt_schedule(void);
void rt_system_scheduler_start(void);
<<<<<<< HEAD
=======
<<<<<<< HEAD

=======
>>>>>>> 15defa99e7e4f7da199465be6f38fedccd8f08cc
>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf
#endif
