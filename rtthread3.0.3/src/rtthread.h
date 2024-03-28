#ifndef __RTTHREAD_H
#define __RTTHREAD_H

rt_err_t rt_thread_init(struct rt_thread *thread,
                        void (*entry)(void *parameter),
                        void *parameter,
                        void *stack_start,
                        rt_uint32_t stack_size);
                        

#endif // !__RTTHREAD_H
