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
/********************************************************************************
**--------------File Info--------------------------------------------------------
** File name:           main.c
** Last modified Date:  2011-09-06
** Last Version:        V1.0
** Descriptions:        The main() function example template
**
********************************************************************************/
#include "LPC11xx.h"            // LPC11xx外设寄存器  
#include "os_cpu.h"
#include "os_cfg.h"
#include "ucos_ii.h"
#include "gpio.h"

/**********************************************************************************
  宏定义
***********************************************************************************/
#define LED1         (1ul << 10)
#define LED1_INIT()  LPC_GPIO0->DIR  |=  LED1       /* LED1初始化               */
#define LED1OFF()    LPC_GPIO0->DATA |=  LED1       /* LED1关                   */
#define LED1ON()     LPC_GPIO0->DATA &= ~LED1       /* LED1开                   */

#define LED2         (1ul << 6)
#define LED2_INIT()  LPC_GPIO0->DIR  |=  LED2       /* LED2初始化                 */
#define LED2OFF()    LPC_GPIO0->DATA |=  LED2       /* LED2灭                     */
#define LED2ON()     LPC_GPIO0->DATA &= ~LED2       /* LED2亮                     */

/**********************************************************************************
  定义全局变量
**********************************************************************************/
static OS_STK stkTask1[100];
static OS_STK stkTask2[100];

/*********************************************************************************
** Function name:       Task1
** Descriptions:        任务1
** input parameters:    pvData: 没有使用
** output parameters:   无
** Returned value:      无
*********************************************************************************/
void Task1(void *pvData)
{
    pvData = pvData;
     
    LED1_INIT(); //LED1接口初始化
    LED1OFF();	//LED1灯关
    while (1) 
	{
	     OSTimeDly(OS_TICKS_PER_SEC / 4); //任务挂起，等待延时时间到
         LED1ON();	 //LED1灯开
				
		GPIOSetDir(PORT2,10,1);			//设置P3.4为输出，LED3
				GPIOSetValue(PORT2,10,1);	//设置P2.8输出0，点亮LED1
			
    
	
		
         OSTimeDly(OS_TICKS_PER_SEC / 4); //任务挂起，等待延时时间到
         LED1OFF();	 //LED1灯关
					GPIOSetValue(PORT2,10,0);
    }
}

/***************************************************************************
** Function name:       Task2
** Descriptions:        任务2
** input parameters:    pvData: 没有使用
** output parameters:   无
** Returned value:      无
*****************************************************************************/
void Task2(void *pvData)
{
    pvData = pvData;
     
    LED2_INIT(); //LED2接口初始化
    LED2OFF();	 //LED2灯关
    while (1) {
	     OSTimeDly(OS_TICKS_PER_SEC / 8); //任务挂起，等待延时时间到
         LED2ON(); //LED2灯开
			
				GPIOSetDir(PORT1,8,1);			//设置P3.4为输出，LED3
				GPIOSetValue(PORT1,8,1);	//设置P2.8输出0，点亮LED1
			
         OSTimeDly(OS_TICKS_PER_SEC / 8);//任务挂起，等待延时时间到
         LED2OFF();	//LED2灯关
				GPIOSetValue(PORT1,8,0);
    }
}

/***************************************************************************************
** Function name:   main
** Descriptions:    用户程序入口函数
**              特殊说明：uCOS-II V2.52的源码，
**              操作方法：下载代码，全速运行程序；
**              现    象：LED闪烁。
** input parameters:    无
** output parameters:   无
** Returned value:      无
***************************************************************************************/
int main(void)
{
    SystemInit();    // 初始化目标板，配置系统时钟
		GPIOInit();
    OSInit();        //OS初始化                                                                                           
    OSTaskCreate(Task1, (void *)0, &stkTask1[sizeof(stkTask1) / 4 - 1], 4);	 //创建任务1
	OSTaskCreate(Task2, (void *)0, &stkTask2[sizeof(stkTask2) / 4 - 1], 5);	 //创建任务2
	OSStart();	 //OS启动
}
/***************************************************************************************
  End Of File
****************************************************************************************/
