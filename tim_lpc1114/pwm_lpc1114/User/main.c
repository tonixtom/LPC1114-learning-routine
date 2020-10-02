/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用通用定时器PWM功能
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "timer.h"

void delay_ms(uint16_t ms)
{
	uint16_t i,j;
	
	for(i=0;i<5000;i++)
		for(j=0;j<ms;j++);
}


int main()
{
	cycle = 10000;
	duty = 99;
	
	T16B0M0_PWM_Init(); // 周期10000微秒，占空比20%
	
	while(1)
	{
		delay_ms(50);
		if(duty<50)duty=99;		
		T16B0M0_PWM_SET();
		duty--;
	}
}





