/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用通用定时器定时功能
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "timer.h"

#define LED1_ON  LPC_GPIO1->DATA &= ~(1<<0)
#define LED1_OFF LPC_GPIO1->DATA |= (1<<0)
#define LED2_ON  LPC_GPIO1->DATA &= ~(1<<1)
#define LED2_OFF LPC_GPIO1->DATA |= (1<<1)

/***********************************/
/* 函数名称：LED灯初始化           */
/***********************************/
void led_init()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟 
	LPC_IOCON->R_PIO1_0 &= ~0x07;    
	LPC_IOCON->R_PIO1_0 |= 0x01; //把P1.0脚设置为GPIO
	LPC_IOCON->R_PIO1_1 &= ~0x07;	
	LPC_IOCON->R_PIO1_1 |= 0x01; //把P1.1脚设置为GPIO
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟
	
	LPC_GPIO1->DIR |= (1<<0); // 把P1.0设置为输出引脚
	LPC_GPIO1->DATA |= (1<<0); // 把P1.0设置为高电平
	LPC_GPIO1->DIR |= (1<<1); // 把P1.1设置为输出引脚
	LPC_GPIO1->DATA |= (1<<1); // 把P1.1设置为高电平
}

int main()
{
	led_init();
	T16B0_init();

	while(1)
	{
		T16B0_delay_ms(1000);
		LED1_ON;
		LED2_OFF;
		T16B0_delay_ms(1000);
		LED1_OFF;
		LED2_ON;
	}
}





