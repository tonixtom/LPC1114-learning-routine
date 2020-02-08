////////////////////////////////////////////////////////////////////////////////
//  Company: �ɶ������ܿƼ� Ruichuang Smart Technology                      //
//     shop: http://ruicstech.taobao.com                                      // 
//  Engineer:  Youzhiyu                                                       //
//  QQ      :  4016682  													  //
//  ����    �� yzyseal                                                        //
//  Target Device: LPC1114                                                    //
//  Tool versions: MDK4.12                                                    //
//  Create Date  :   2011-09-06 10:09                                         //
//  Description:                                                              //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
// 	   Copyright (C) 2011-2012  Youzhiyu   All rights reserved                //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
**--------------File Info------------------------------------------------------
** File name:               os_cpu_c.c
** Latest modified Date:    2011-09-06
** Latest Version:          1.0
** Descriptions:            ��COS-II��Cortex-M0�ϵ���ֲ����C���Բ��֣���realview����
**
**------------------------------------------------------------------------------
** Created by:              Youzhiyu
** Created date:            2011-09-06
** Version:                 1.0
** Descriptions:            The original version           
**
*********************************************************************************/
#define  OS_CPU_GLOBALS
#include <LPC11xx.h>
#include "os_cpu.h"
#include "os_cfg.h"
#include "ucos_ii.h"
   
/***************************************************************************************
  ȫ�ֱ���
****************************************************************************************/
unsigned int __GuiOsEnterSum;

/***************************************************************************************
** Function name:       __s_OSStartHighRdy
** Descriptions:        uC/OS-II����ʹ��OSStartHighRdy���е�һ������,OSStartHighRdy�����
**                      __s_OSStartHighRdy
** input parameters:    none
** output parameters:   none
** Returned value:      none
********************************************************************************************/
__asm void __OSStartHighRdy (void)
{
     IMPORT  __GuiOsEnterSum
    IMPORT  OSRunning
    IMPORT  OSTCBCur
    IMPORT  OSTCBHighRdy
    IMPORT  OSTaskSwHook

         preserve8

    LDR     R4, =OSRunning
    MOVS    R5, #1
    STRB    R5, [R4]
	MOV     R7, LR
    BL      OSTaskSwHook
    MOV     LR, R7

    LDR     R6, =OSTCBHighRdy
    LDR     R6, [R6]
    LDR     R4, =OSTCBCur
    STR     R6, [R4]
	
    LDR     R2, [R6]
	MOV     SP, R2
    POP     {R0}
    LDR     R1, =__GuiOsEnterSum
    STR     R0, [R1]
	     
    POP     {R4-R7}
	POP     {R0-R3}
	MOV     R8,R0
	MOV     R9,R1
	MOV     R10,R2
	MOV     R11,R3
	ADD     SP,SP,#16
	POP     {R0-R3}
	MOV     R12,R0
	MOV     LR,R2
	SUB    SP,SP,#32
	POP     {R0-R3}
	ADD     SP,SP,#16
	CPSIE   I     
    BX      LR
	NOP 
}

/**************************************************************************************
** Function name:           PendSV_Handler
** Descriptions:            uC/OS-II������Ⱥ���
** input parameters:        none
** output parameters:       none
** Returned value:          none
***************************************************************************************/
__asm void PendSV_Handler(void) 
{
    IMPORT  __GuiOsEnterSum
    IMPORT  OSTCBCur
    IMPORT  OSTCBHighRdy
    IMPORT  OSPrioCur
    IMPORT  OSPrioHighRdy
    IMPORT  OSTaskSwHook

         preserve8

     CPSID   I
	PUSH    {R4-R7}
	MOV     R0,R8
	MOV     R1,R9
	MOV     R2,R10
	MOV     R3,R11
	PUSH    {R0-R3}
	
    MOV      R4,LR
    BL      OSTaskSwHook
    MOV     LR,R4
    
    
    LDR     R1, =__GuiOsEnterSum
    LDR     R0, [R1]
    PUSH    {R0}

    LDR     R2, =OSTCBCur
    LDR     R2, [R2]
	MOV     R0,SP
    STR     R0, [R2]
    
    LDR     R4, =OSPrioCur
    LDR     R5, =OSPrioHighRdy
    LDRB    R6, [R5]
    STRB    R6, [R4]

    LDR     R6, =OSTCBHighRdy
    LDR     R6, [R6]
    LDR     R4, =OSTCBCur
    STR     R6, [R4]

    LDR     R0, [R6]
	MOV     SP,R0
    POP     {R0}
    STR     R0, [R1]

    CMP     R0, #0
    BNE       OUT
	CPSIE   I
OUT
	POP     {R0-R3}
	MOV     R8,R0
	MOV     R9,R1
	MOV     R10,R2
	MOV     R11,R3
    POP     {R4-R7}
	
    BX      LR

}

/***********************************************************************************
** Function name:           __s_OS_ENTER_CRITICAL
** Descriptions:            ��ֹ�ж�
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
**************************************************************************************/
void OS_ENTER_CRITICAL (void)
{
   	  __disable_irq();
	  __GuiOsEnterSum++;
}

/**************************************************************************************
** Function name:           __s_OS_EXIT_CRITICAL
** Descriptions:            �����ж�
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
****************************************************************************************/
void OS_EXIT_CRITICAL (void)
{
    if(	__GuiOsEnterSum > 0)
		__GuiOsEnterSum--;
	if(	__GuiOsEnterSum == 0)
		__enable_irq();

}

/***************************************************************************************
** Function name:           changeToSYSMode
** Descriptions:            �����л���ϵͳģʽ
** input parameters:        none
** output parameters:       none
** Returned value:          none
******************************************************************************************/
__asm void changeToSYSMode (void)
{
    MOVS    R0, #0
    MSR     CONTROL, R0
    BX      LR
}

/*****************************************************************************************
** Function name:           changeToUSRMode
** Descriptions:            �����л����û�ģʽ
** input parameters:        none
** output parameters:       none
** Returned value:          none
******************************************************************************************/
__asm void changeToUSRMode (void)
{
    MOVS    R0, #1
    MSR     CONTROL, R0
    BX      LR
}

/******************************************************************************************
** Function name:           taskEntry
* Descriptions:            �������
** input parameters:        pdata: ���ݸ�����Ĳ���
** output parameters:       none
** Returned value:          none
*******************************************************************************************/
__asm void taskEntry (void *pvData, void (*task)(void *pd))
{
    IMPORT  OSTaskDel

    BLX     R1
    MOVS     R0, #OS_PRIO_SELF
    BL      OSTaskDel
}

/******************************************************************************************
** Function name:       SysTick_Handler
** Descriptions:        ϵͳ�����ж�
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*******************************************************************************************/
void SysTick_Handler (void)
{
    OSIntEnter();
    OSTimeTick();     // ϵͳ���Ĵ���   
    OSIntExit();
}

/*******************************************************************************************
** Function name:           OSStartHighRdy
** Descriptions:            uC/OS-II����ʹ��OSStartHighRdy���е�һ������
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************/
void OSStartHighRdy (void)
{
    NVIC_EnableIRQ(PendSV_IRQn);
    NVIC_SetPriority(PendSV_IRQn, 0xFF);
    NVIC_EnableIRQ(SysTick_IRQn);
    NVIC_SetPriority(SysTick_IRQn, 0x80);

    SysTick->LOAD = SystemFrequency / OS_TICKS_PER_SEC;
    SysTick->CTRL   = 0x07;
    __OSStartHighRdy();
}

/******************************************************************************************
** Function name:           OSIntCtxSw
** Descriptions:            �жϼ�����Ⱥ���
** input parameters:        none
** output parameters:       none
** Returned value:          none
******************************************************************************************/
void OSIntCtxSw (void)
{
    SCB->ICSR = 1ul << 28;
}

 

/****************************************************************************************
** Function name:           OSTaskStkInit
** Descriptions:            �����ջ��ʼ�����룬����������ʧ�ܻ�ʹϵͳ����
** input parameters:        task:  ����ʼִ�еĵ�ַ
**                          pdata: ���ݸ�����Ĳ���
**                          ptos:  ����Ķ�ջ��ʼλ��
**                          opt:   ���Ӳ���,��ǰ�汾���ڱ���������,��������μ�OSTaskCreateExt()��opt����
** output parameters:       none
** Returned value:          �¶�ջλ��
***************************************************************************************/
OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    OS_STK *pstk;    

    opt     = opt;         //  �������������           
    pstk    = (OS_STK *)(((unsigned long)ptos) & ~0x07ul);        //��ȡ��ջָ��,8�ֶ���    
    
    /* 
     *  �������񻷾���ADS1.2ʹ�����ݼ���ջ
     */
    *pstk   = 0x01000000;                                               /*  xPSR                        */
    *--pstk = (OS_STK) taskEntry;                                       /*  pc��������������          */
    *--pstk = 0;                                                        /*  lr                          */

    *--pstk = 0;                                                        /*  r12                         */
    *--pstk = 0;                                                        /*  r3                          */
    *--pstk = 0;                                                        /*  r2                          */
    *--pstk = (OS_STK) task;                                            /*  r1,�������������           */
    *--pstk = (unsigned int) pdata;                                     /*  r0,��һ������ʹ��R0����     */
    *--pstk = 0;                                                        /*  r11                         */
    *--pstk = 0;                                                        /*  r10                         */
    *--pstk = 0;                                                        /*  r9                          */
    *--pstk = 0;                                                        /*  r8                          */
    *--pstk = 0;                                                        /*  r7                          */
    *--pstk = 0;                                                        /*  r6                          */
    *--pstk = 0;                                                        /*  r5                          */
    *--pstk = 0;                                                        /*  r4                          */
    *--pstk = 0;                                                        /*  ���жϼ�����OsEnterSum;     */

    return (pstk);
}


/*********************************************************************************************************
  uCOSII OS���Ӻ���
*********************************************************************************************************/

#if OS_CPU_HOOKS_EN
/*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************/
#if OS_VERSION > 203
void OSInitHookBegin (void)
{
}
#endif                                                                  /*  OS_VERSION                  */

/*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************/
#if OS_VERSION > 203
void OSInitHookEnd (void)
{
}
#endif                                                                  /*  OS_VERSION                  */


/*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                                        /*  Prevent compiler warning    */
}


/*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                                        /*  Prevent compiler warning    */
}

/*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************/
void OSTaskSwHook (void)
{
}

/*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************/
void OSTaskStatHook (void)
{
}

/*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                                        /*  Prevent Compiler warning    */
}
#endif                                                                  /*  OS_VERSION                  */

/*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************/
void OSTimeTickHook (void)
{
}


/*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************/
#if OS_VERSION >= 251
void OSTaskIdleHook (void)
{
}
#endif                                                                  /*  OS_VERSION                  */
#endif                                                                  /*  OS_CPU_GLOBALS              */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
