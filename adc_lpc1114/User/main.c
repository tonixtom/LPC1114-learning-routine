/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：12Mhz(主频50M)
*   功能    ：学会使用START位启动ADC转换
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "adc.h"
#include "stdio.h"
#include "stdlib.h"

void delay(void)
{
	uint16_t i,j;
	for(j=0;j<5000;j++)
		for(i=0;i<500;i++);
}

int main()
{
	uint16_t adc_value;
	uint8_t i;
	char str[8]={'0'};

	UART_init(9600);
	ADC_Init(5);
	
	while(1)
	{
		delay();
		adc_value = ADC_Read(5);
	//itoa(adc_value, str, 10);
   sprintf(str, "%d", adc_value);
		UART_send(str, 8);//?????????
		UART_send("next: ", 5);//?????????
	//	UART_send_byte(adc_value>>8);
	//	UART_send_byte(adc_value);
	}
}




                       