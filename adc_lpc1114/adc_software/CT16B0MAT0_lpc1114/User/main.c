/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用CT16B0MAT0引脚启动ADC转换，获取ADC值
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "adc.h"

#include "stdio.h"
#include "stdlib.h"



int main()
{
	uint16_t adc_value;
	char str[8]={'0'};

	UART_init(9600);
	ADC_Init(5);
	
	while(1)
	{

		UART_send("next: ", 6);
		
		adc_value = ADC_Read(5);
		//itoa(adc_value, str, 10);
		sprintf(str, "%8d", adc_value);
		UART_send(str, 8);
		UART_send_byte('\n');
		
	//	UART_send_byte(adc_value>>8);
	//	UART_send_byte(adc_value);
	}
}   



