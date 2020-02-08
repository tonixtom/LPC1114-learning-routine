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
/********************************************************************************
**--------------File Info--------------------------------------------------------
** File name:           main.c
** Last modified Date:  2011-09-06
** Last Version:        V1.0
** Descriptions:        The main() function example template
**
********************************************************************************/
#include "LPC11xx.h"            // LPC11xx����Ĵ���  
#include "os_cpu.h"
#include "os_cfg.h"
#include "ucos_ii.h"
#include "gpio.h"

/**********************************************************************************
  �궨��
***********************************************************************************/
#define LED1         (1ul << 10)
#define LED1_INIT()  LPC_GPIO0->DIR  |=  LED1       /* LED1��ʼ��               */
#define LED1OFF()    LPC_GPIO0->DATA |=  LED1       /* LED1��                   */
#define LED1ON()     LPC_GPIO0->DATA &= ~LED1       /* LED1��                   */

#define LED2         (1ul << 6)
#define LED2_INIT()  LPC_GPIO0->DIR  |=  LED2       /* LED2��ʼ��                 */
#define LED2OFF()    LPC_GPIO0->DATA |=  LED2       /* LED2��                     */
#define LED2ON()     LPC_GPIO0->DATA &= ~LED2       /* LED2��                     */

/**********************************************************************************
  ����ȫ�ֱ���
**********************************************************************************/
static OS_STK stkTask1[100];
static OS_STK stkTask2[100];

/*********************************************************************************
** Function name:       Task1
** Descriptions:        ����1
** input parameters:    pvData: û��ʹ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************/
void Task1(void *pvData)
{
    pvData = pvData;
     
    LED1_INIT(); //LED1�ӿڳ�ʼ��
    LED1OFF();	//LED1�ƹ�
    while (1) 
	{
	     OSTimeDly(OS_TICKS_PER_SEC / 4); //������𣬵ȴ���ʱʱ�䵽
         LED1ON();	 //LED1�ƿ�
				
		GPIOSetDir(PORT2,10,1);			//����P3.4Ϊ�����LED3
				GPIOSetValue(PORT2,10,1);	//����P2.8���0������LED1
			
    
	
		
         OSTimeDly(OS_TICKS_PER_SEC / 4); //������𣬵ȴ���ʱʱ�䵽
         LED1OFF();	 //LED1�ƹ�
					GPIOSetValue(PORT2,10,0);
    }
}

/***************************************************************************
** Function name:       Task2
** Descriptions:        ����2
** input parameters:    pvData: û��ʹ��
** output parameters:   ��
** Returned value:      ��
*****************************************************************************/
void Task2(void *pvData)
{
    pvData = pvData;
     
    LED2_INIT(); //LED2�ӿڳ�ʼ��
    LED2OFF();	 //LED2�ƹ�
    while (1) {
	     OSTimeDly(OS_TICKS_PER_SEC / 8); //������𣬵ȴ���ʱʱ�䵽
         LED2ON(); //LED2�ƿ�
			
				GPIOSetDir(PORT1,8,1);			//����P3.4Ϊ�����LED3
				GPIOSetValue(PORT1,8,1);	//����P2.8���0������LED1
			
         OSTimeDly(OS_TICKS_PER_SEC / 8);//������𣬵ȴ���ʱʱ�䵽
         LED2OFF();	//LED2�ƹ�
				GPIOSetValue(PORT1,8,0);
    }
}

/***************************************************************************************
** Function name:   main
** Descriptions:    �û�������ں���
**              ����˵����uCOS-II V2.52��Դ�룬
**              �������������ش��룬ȫ�����г���
**              ��    ��LED��˸��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
***************************************************************************************/
int main(void)
{
    SystemInit();    // ��ʼ��Ŀ��壬����ϵͳʱ��
		GPIOInit();
    OSInit();        //OS��ʼ��                                                                                           
    OSTaskCreate(Task1, (void *)0, &stkTask1[sizeof(stkTask1) / 4 - 1], 4);	 //��������1
	OSTaskCreate(Task2, (void *)0, &stkTask2[sizeof(stkTask2) / 4 - 1], 5);	 //��������2
	OSStart();	 //OS����
}
/***************************************************************************************
  End Of File
****************************************************************************************/
