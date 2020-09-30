/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用系统定时器systick
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<0)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<0)
#define LED2_ON  LPC_GPIO1->DATA &= ~(1<<1)
#define LED2_OFF LPC_GPIO1->DATA |= (1<<1)

uint32_t msTicks=0;

void led_init()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟 
	LPC_IOCON->R_PIO1_0 &= ~0x07;    
	LPC_IOCON->R_PIO1_0 |= 0x01; //把P1.0脚设置为GPIO
	LPC_IOCON->R_PIO1_1 &= ~0x07;	
	LPC_IOCON->R_PIO1_1 |= 0x01; //把P1.1脚设置为GPIO
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟
	
	LPC_GPIO1->DIR |= (1<<0);
	LPC_GPIO1->DATA |= (1<<0);
	LPC_GPIO1->DIR |= (1<<1);
	LPC_GPIO1->DATA |= (1<<1);
}

void SysTick_Handler(void)  
{                              
  msTicks++;                                                 
}



int main()
{
	led_init();
	SysTick_Config(SystemCoreClock/100); //设置每10毫秒进一次中断
	
	while(1)
	{
		while(msTicks<100);
		msTicks = 0;
		LED1_ON;
		LED2_OFF;
		while(msTicks<100);
		LED1_OFF;
		LED2_ON;
		msTicks = 0;
	}
}




