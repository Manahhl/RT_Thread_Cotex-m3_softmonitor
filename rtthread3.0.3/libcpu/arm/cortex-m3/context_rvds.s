;************************************************************************
; 全局变量 
;************************************************************************
	IMPORT rt_thread_switch_interrupt_flag
	IMPORT rt_interrupt_from_thread
	IMPORT rt_interrupt_to_thread

;************************************************************************
; 常量 
;************************************************************************
;------------------------------------------------------------------------
;有关内核外设寄存器定义可参考官方文档：STM32F10xxx Cortex-M3 programming manual
;系统控制块外设 SCB 地址范围：0xE000ED00-0xE000ED3F
;------------------------------------------------------------------------
SCB_VTOR EQU 0xE000ED08 ; 向量表偏移寄存器
NVIC_INT_CTRL EQU 0xE000ED04 ; 中断控制状态寄存器
NVIC_SYSPRI2 EQU 0xE000ED20 ; 系统优先级寄存器(2)
NVIC_PENDSV_PRI EQU 0x00FF0000 ; PendSV 优先级值 (lowest)
NVIC_PENDSVSET EQU 0x10000000 ; 触发 PendSV exception 的值

;************************************************************************
; 代码产生指令 
;************************************************************************

	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8

;/*
; *----------------------------------------------------------------------
; * 函数原型：void rt_hw_context_switch_to(rt_uint32 to);
; * r0 --> to
; * 该函数用于开启第一次线程切换
; *----------------------------------------------------------------------
; */
rt_hw_context_switch_to  PROC 

    ; 导出 rt_hw_context_switch_to，让其具有全局属性，可以在 C 文件调用
    EXPORT rt_hw_context_switch_to 
    
    ; 设置 rt_interrupt_to_thread 的值 
    ;将 rt_interrupt_to_thread 的地址加载到 r1
    LDR r1, =rt_interrupt_to_thread 
    ;将 r0 的值存储到 rt_interrupt_to_thread 
    STR r0, [r1]
    
    ; 设置 rt_interrupt_from_thread 的值为 0，表示启动第一次线程切换 (9)
    ;将 rt_interrupt_from_thread 的地址加载到 r1
    LDR r1, =rt_interrupt_from_thread 
    ;配置 r0 等于 0
    MOV r0, #0x0 
    ;将 r0 的值存储到 rt_interrupt_from_thread
    STR r0, [r1] 
    
    ; 设置中断标志位 rt_thread_switch_interrupt_flag 的值为 1 (10)
    ;将 rt_thread_switch_interrupt_flag 的地址加载到 r1
    LDR r1, =rt_thread_switch_interrupt_flag 
    ;配置 r0 等于 1
    MOV r0, #1 
    ;将 r0 的值存储到 rt_thread_switch_interrupt_flag
    STR r0, [r1] 
    
    ; 设置 PendSV 异常的优先级 
    LDR r0, =NVIC_SYSPRI2
    LDR r1, =NVIC_PENDSV_PRI
    LDR.W r2, [r0,#0x00] ; 读
    ORR r1,r1,r2 ; 改
    STR r1, [r0] ; 写
    
    ; 触发 PendSV 异常 (产生上下文切换) 
    LDR r0, =NVIC_INT_CTRL
    LDR r1, =NVIC_PENDSVSET
    STR r1, [r0]
    
    ; 开中断
    CPSIE F
    CPSIE I
    
    ; 不会到这里
    ENDP

;/*
; *----------------------------------------------------------------------
; * void PendSV_Handler(void);
; * r0 --> switch from thread stack
; * r1 --> switch to thread stack
; * psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
; *----------------------------------------------------------------------
; */

PendSV_Handler PROC
    EXPORT PendSV_Handler

    ; 失能中断，为了保护上下文切换不被中断 (1)
    MRS r2, PRIMASK
    CPSID I

    ; 获取中断标志位，看看是否为 0 (2)
    ; 加载 rt_thread_switch_interrupt_flag 的地址到 r0
    LDR r0, =rt_thread_switch_interrupt_flag
    ; 加载 rt_thread_switch_interrupt_flag 的值到 r1
    LDR r1, [r0]
    ; 判断 r1 是否为 0，为 0 则跳转到 pendsv_exit
    CBZ r1, pendsv_exit

    ; r1 不为 0 则清 0 (3)
    MOV r1, #0x00
    ; 将 r1 的值存储到 rt_thread_switch_interrupt_flag，即清 0
    STR r1, [r0]
    ; 判断 rt_interrupt_from_thread 的值是否为 0 (4)
    ; 加载 rt_interrupt_from_thread 的地址到 r0
    LDR r0, =rt_interrupt_from_thread 
    ; 加载 rt_interrupt_from_thread 的值到 r1
    LDR r1, [r0]
    ; 判断 r1 是否为 0，为 0 则跳转到 switch_to_thread

    ; 第一次线程切换时 rt_interrupt_from_thread 肯定为 0，则跳转到 switch_to_thread
    CBZ r1, switch_to_thread

    ; ========================== 上文保存 ======================== (6)
    ; 当进入 PendSVC Handler 时，上一个线程运行的环境即：
    ; xPSR，PC（线程入口地址），R14，R12，R3，R2，R1，R0（线程的形参）
    ; 这些 CPU 寄存器的值会自动保存到线程的栈中，剩下的 r4~r11 需要手动保存
    ; 获取线程栈指针到 r1
    MRS r1, psp
    ;将 CPU 寄存器 r4~r11 的值存储到 r1 指向的地址(每操作一次地址将递减一次)
    STMFD r1!, {r4 - r11}
    ; 加载 r0 指向值到 r0，即 r0=rt_interrupt_from_thread
    LDR r0, [r0]
    ; 将 r1 的值存储到 r0，即更新线程栈 sp
    STR r1, [r0]

    ; ========================== 下文切换 ========================== (5)
switch_to_thread
    ; 加载 rt_interrupt_to_thread 的地址到 r1
    ;rt_interrupt_to_thread 是一个全局变量，里面存的是线程栈指针 SP 的指针
    LDR r1, =rt_interrupt_to_thread
    ; 加载 rt_interrupt_to_thread 的值到 r1，即 sp 指针的指针
    LDR r1, [r1]
    ; 加载 rt_interrupt_to_thread 的值到 r1，即 sp
    LDR r1, [r1]

    ;将线程栈指针 r1(操作之前先递减)指向的内容加载到 CPU 寄存器 r4~r11
    LDMFD r1!, {r4 - r11}
    ;将线程栈指针更新到 PSP
    MSR psp, r1

pendsv_exit
    ; 恢复中断
    MSR PRIMASK, r2 

    ; 确保异常返回使用的栈指针是 PSP，即 LR 寄存器的位 2 要为 1
    ORR lr, lr, #0x04 
    ; 异常返回，这个时候栈中的剩下内容将会自动加载到 CPU 寄存器：
    ; xPSR，PC（线程入口地址），R14，R12，R3，R2，R1，R0（线程的形参）
    ; 同时 PSP 的值也将更新，即指向线程栈的栈顶
    BX lr 

    ; PendSV_Handler 子程序结束
    ENDP

;/*
; *----------------------------------------------------------------------
; * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
; * r0 --> from
; * r1 --> to
; *----------------------------------------------------------------------
; */
rt_hw_context_switch PROC
    EXPORT rt_hw_context_switch

    ; 设置中断标志位 rt_thread_switch_interrupt_flag 为 1 (1)
    ; 加载 rt_thread_switch_interrupt_flag 的地址到 r2

    LDR r2, =rt_thread_switch_interrupt_flag
    ; 加载 rt_thread_switch_interrupt_flag 的值到 r3
    LDR r3, [r2]
    ;r3 与 1 比较，相等则执行 BEQ 指令，否则不执行
    CMP r3, #1 
    BEQ _reswitch
    ; 设置 r3 的值为 1
    MOV r3, #1 
    ; 将 r3 的值存储到 rt_thread_switch_interrupt_flag，即置 1
    STR r3, [r2]

    ; 设置 rt_interrupt_from_thread 的值 (2)
    ; 加载 rt_interrupt_from_thread 的地址到 r2
    LDR r2, =rt_interrupt_from_thread 
    ; 存储 r0 的值到 rt_interrupt_from_thread，即上一个线程栈指针 sp 的指针
    STR r0, [r2]

_reswitch
    ; 设置 rt_interrupt_to_thread 的值 (3)
    ; 加载 rt_interrupt_from_thread 的地址到 r2
    LDR r2, =rt_interrupt_to_thread 
    ; 存储 r1 的值到 rt_interrupt_from_thread，即下一个线程栈指针 sp 的指针
    STR r1, [r2] 

    ; 触发 PendSV 异常，实现上下文切换 (4)
    LDR r0, =NVIC_INT_CTRL
    LDR r1, =NVIC_PENDSVSET
    STR r1, [r0]
    ; 子程序返回
    BX LR 
    ; 子程序结束
    ENDP
<<<<<<< HEAD
    
=======
<<<<<<< HEAD

;/**关闭中断
;* rt_base_t rt_hw_interrrupt_disable();
;*/
rt_hw_interrrupt_disable    PROC
    EXPORT rt_hw_interrupt_disable
    MRS r0, PRIMASK
    CPISD I
    BX LR
    ENDP

;/**开启中断
;* void rt_hw_interrupt_enable(rt_base_t level)
;*/
rt_hw_interrupt_enable    PROC
    EXPORT rt_hw_interrupt_enable
    MSR PRIMASK, r0
    BX  LR
    ENDP

=======
    
>>>>>>> 15defa99e7e4f7da199465be6f38fedccd8f08cc
>>>>>>> a909705842d9a831a44f2597fd0153fec3b1a0cf
    ALIGN  4
    
    END
