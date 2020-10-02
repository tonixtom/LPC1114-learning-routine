/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用通用定时器计数功能
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "timer.h"
#include "uart.h"
#include "stdlib.h"
#include "stdio.h"

int main()
{
	uint16_t temp1,temp2;
	char str[8]={'0'};
	
	UART_init(9600); // 初始化串口
	T16B0_cnt_init(); // 初始化定时器
	temp1 = LPC_TMR16B0->TC; // 获取TC值
	
	while(1)
	{
		temp2 = LPC_TMR16B0->TC; // 获取TC值
		if(temp2!=temp1) // 如果这次获取的TC值与上一次的不相等
		{
			temp1 = LPC_TMR16B0->TC; // 把这次的TC值给了temp1
 			sprintf(str, "%8d", temp1);
			UART_send((uint8_t *)str, 8);
			UART_send_byte('\n');
 		}
	}
}





