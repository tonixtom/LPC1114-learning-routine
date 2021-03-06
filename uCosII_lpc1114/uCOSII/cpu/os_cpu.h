////////////////////////////////////////////////////////////////////////////////
//  Company: 成都锐创智能科技 Ruichuang Smart Technology                      //
//     shop: http://ruicstech.taobao.com                                      // 
//  Engineer:  Youzhiyu                                                       //
//  QQ      :  4016682  													  //
//  旺旺    ： yzyseal                                                        //
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
**--------------File Info-------------------------------------------------------
** File name:               os_cpu.h
** Latest modified Date:    2011-09-06
** Latest Version:          1.0
** Descriptions:            μCOS-II在Cortex-M3上的移植代码CPU配置部分，用realview编译
**
**-------------------------------------------------------------------------------
** Created by:              Youzhiyu
** Created date:            2011-09-06
** Version:                 1.0
** Descriptions:            The original version           
**
*********************************************************************************/

#ifndef __OS_CPU_H
#define __OS_CPU_H

/*********************************************************************************************************
  定义与编译器无关的数据类型
*********************************************************************************************************/
typedef unsigned char  BOOLEAN;                                         /*  布尔变量                    */
typedef unsigned char  INT8U;                                           /*  无符号8位整型变量           */
typedef signed   char  INT8S;                                           /*  有符号8位整型变量           */
typedef unsigned short INT16U;                                          /*  无符号16位整型变量          */
typedef signed   short INT16S;                                          /*  有符号16位整型变量          */
typedef unsigned long  INT32U;                                          /*  无符号32位整型变量          */
typedef signed   long  INT32S;                                          /*  有符号32位整型变量          */
typedef float          FP32;                                            /*  单精度浮点数（32位长度）    */
typedef double         FP64;                                            /*  双精度浮点数（64位长度）    */

typedef INT32U         OS_STK;                                          /*  堆栈是32位宽度              */

/*********************************************************************************************************
  体系结构相关的一些定义
*********************************************************************************************************/

#define OS_CRITICAL_METHOD      2                                       /*  选择开、关中断的方式        */
#define OS_STK_GROWTH           1                                       /*  堆栈是从上往下长的          */


#define  OS_TASK_SW   OSIntCtxSw
 
/*********************************************************************************************************
  全局变量
*********************************************************************************************************/
extern unsigned int __GuiOsEnterSum;

/*********************************************************************************************************
** Function name:           __s_OSStartHighRdy
** Descriptions:            uC/OS-II启动使用OSStartHighRdy运行第一个任务,OSStartHighRdy会调用
**                          __s_OSStartHighRdy
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void __OSStartHighRdy (void);

/*********************************************************************************************************
** Function name:           PendSV_Handler
** Descriptions:            uC/OS-II任务调度函数
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void PendSV_Handler(void);

/*********************************************************************************************************
** Function name:           __s_OS_ENTER_CRITICAL
** Descriptions:            禁止中断
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void OS_ENTER_CRITICAL (void);

/*********************************************************************************************************
** Function name:           __s_OS_EXIT_CRITICAL
** Descriptions:            允许中断
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void OS_EXIT_CRITICAL (void);

/*********************************************************************************************************
** Function name:           changeToSYSMode
** Descriptions:            任务切换到系统模式
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void changeToSYSMode (void);

/*********************************************************************************************************
** Function name:           changeToUSRMode
** Descriptions:            任务切换到用户模式
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void changeToUSRMode(void);

/*********************************************************************************************************
** Function name:           taskEntry
* Descriptions:            任务入口
** input parameters:        pdata: 传递给任务的参数
** output parameters:       none
** Returned value:          none
**********************************************************************************************************/
extern void taskEntry (void *pvData, void (*task)(void *pd));

/*********************************************************************************************************
** Function name:       SysTick_Handler
** Descriptions:        系统节拍中断
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
extern void SysTick_Handler (void);

/*********************************************************************************************************
** Function name:           OSStartHighRdy
** Descriptions:            uC/OS-II启动使用OSStartHighRdy运行第一个任务
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void OSStartHighRdy (void);

/*********************************************************************************************************
** Function name:           OSIntCtxSw
** Descriptions:            中断级别调度函数
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void OSIntCtxSw (void);

 /*********************************************************************************************************
** Function name:           SVC_Handler
** Descriptions:            svcall处理程序
** input parameters:        uiHandle:选择子功能
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void SVC_Handler (unsigned int uiHandle);

/*********************************************************************************************************
** Function name:           OSTaskStkInit
** Descriptions:            任务堆栈初始化代码，本函数调用失败会使系统崩溃
** input parameters:        task:  任务开始执行的地址
**                          pdata: 传递给任务的参数
**                          ptos:  任务的堆栈开始位置
**                          opt:   附加参数,当前版本对于本函数无用,具体意义参见OSTaskCreateExt()的opt参数
** output parameters:       none
** Returned value:          新堆栈位置
********************************************************************************************************/
extern OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt);

#endif                                                                  /*  __OS_CPU_H                  */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
