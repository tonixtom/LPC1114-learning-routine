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
**--------------File Info-------------------------------------------------------
** File name:               os_cpu.h
** Latest modified Date:    2011-09-06
** Latest Version:          1.0
** Descriptions:            ��COS-II��Cortex-M3�ϵ���ֲ����CPU���ò��֣���realview����
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
  ������������޹ص���������
*********************************************************************************************************/
typedef unsigned char  BOOLEAN;                                         /*  ��������                    */
typedef unsigned char  INT8U;                                           /*  �޷���8λ���ͱ���           */
typedef signed   char  INT8S;                                           /*  �з���8λ���ͱ���           */
typedef unsigned short INT16U;                                          /*  �޷���16λ���ͱ���          */
typedef signed   short INT16S;                                          /*  �з���16λ���ͱ���          */
typedef unsigned long  INT32U;                                          /*  �޷���32λ���ͱ���          */
typedef signed   long  INT32S;                                          /*  �з���32λ���ͱ���          */
typedef float          FP32;                                            /*  �����ȸ�������32λ���ȣ�    */
typedef double         FP64;                                            /*  ˫���ȸ�������64λ���ȣ�    */

typedef INT32U         OS_STK;                                          /*  ��ջ��32λ���              */

/*********************************************************************************************************
  ��ϵ�ṹ��ص�һЩ����
*********************************************************************************************************/

#define OS_CRITICAL_METHOD      2                                       /*  ѡ�񿪡����жϵķ�ʽ        */
#define OS_STK_GROWTH           1                                       /*  ��ջ�Ǵ������³���          */


#define  OS_TASK_SW   OSIntCtxSw
 
/*********************************************************************************************************
  ȫ�ֱ���
*********************************************************************************************************/
extern unsigned int __GuiOsEnterSum;

/*********************************************************************************************************
** Function name:           __s_OSStartHighRdy
** Descriptions:            uC/OS-II����ʹ��OSStartHighRdy���е�һ������,OSStartHighRdy�����
**                          __s_OSStartHighRdy
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void __OSStartHighRdy (void);

/*********************************************************************************************************
** Function name:           PendSV_Handler
** Descriptions:            uC/OS-II������Ⱥ���
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void PendSV_Handler(void);

/*********************************************************************************************************
** Function name:           __s_OS_ENTER_CRITICAL
** Descriptions:            ��ֹ�ж�
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void OS_ENTER_CRITICAL (void);

/*********************************************************************************************************
** Function name:           __s_OS_EXIT_CRITICAL
** Descriptions:            �����ж�
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void OS_EXIT_CRITICAL (void);

/*********************************************************************************************************
** Function name:           changeToSYSMode
** Descriptions:            �����л���ϵͳģʽ
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void changeToSYSMode (void);

/*********************************************************************************************************
** Function name:           changeToUSRMode
** Descriptions:            �����л����û�ģʽ
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void changeToUSRMode(void);

/*********************************************************************************************************
** Function name:           taskEntry
* Descriptions:            �������
** input parameters:        pdata: ���ݸ�����Ĳ���
** output parameters:       none
** Returned value:          none
**********************************************************************************************************/
extern void taskEntry (void *pvData, void (*task)(void *pd));

/*********************************************************************************************************
** Function name:       SysTick_Handler
** Descriptions:        ϵͳ�����ж�
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
extern void SysTick_Handler (void);

/*********************************************************************************************************
** Function name:           OSStartHighRdy
** Descriptions:            uC/OS-II����ʹ��OSStartHighRdy���е�һ������
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void OSStartHighRdy (void);

/*********************************************************************************************************
** Function name:           OSIntCtxSw
** Descriptions:            �жϼ�����Ⱥ���
** input parameters:        none
** output parameters:       none
** Returned value:          none
********************************************************************************************************/
extern void OSIntCtxSw (void);

 /*********************************************************************************************************
** Function name:           SVC_Handler
** Descriptions:            svcall�������
** input parameters:        uiHandle:ѡ���ӹ���
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern void SVC_Handler (unsigned int uiHandle);

/*********************************************************************************************************
** Function name:           OSTaskStkInit
** Descriptions:            �����ջ��ʼ�����룬����������ʧ�ܻ�ʹϵͳ����
** input parameters:        task:  ����ʼִ�еĵ�ַ
**                          pdata: ���ݸ�����Ĳ���
**                          ptos:  ����Ķ�ջ��ʼλ��
**                          opt:   ���Ӳ���,��ǰ�汾���ڱ���������,��������μ�OSTaskCreateExt()��opt����
** output parameters:       none
** Returned value:          �¶�ջλ��
********************************************************************************************************/
extern OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt);

#endif                                                                  /*  __OS_CPU_H                  */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
