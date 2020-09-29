/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用自动波特率测试功能
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "stdio.h"
#include "stdlib.h"




/********************** 函数定义 ********************/
/****************************************************
*名  称：	延时函数    							*
*参  数：   延时时间								*
*备  注：	内联函数    							*
*****************************************************/
__inline void delay_ms(uint32_t a)    //1ms延时函数
{                           
	uint32_t i;
	while( --a != 0)
	{
   		for(i = 0; i<5500; i++);
	}             
}
void AutoBaud(void)
{
	char str[64];
	uint32_t baud;
	uint8_t dlm,  dll;

	LPC_UART->ACR  = 0x03;							// 允许自动波特率
	while ((LPC_UART->ACR & 0x01) != 0x0);			// 等待自动波特率测量完成
	LPC_UART->ACR 		 |= 0x01 << 8;				// 清除自动波特率中断标志
	LPC_UART->LCR = 0x83;
	dlm   = LPC_UART->DLM;
	dll   = LPC_UART->DLL;
	LPC_UART->LCR = 0x03;
	LPC_UART->FCR = 0x07;    //允许FIFO，清空RxFIFO 和 TxFIFO
	baud  = ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV) / (16 * (256 * dlm + dll)));
	sprintf(str,  "LPC1114  ZhengMing Hello! Baud is %4d bps \n",  baud);
	UART_send((uint8_t *)str,45);
}

/**********************************************/
/*               主函数                       */
/**********************************************/
int main()
{
	char str[8]={'0'};
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟 
	LPC_IOCON->PIO1_6 &= ~0x07;    
	LPC_IOCON->PIO1_6 |= 0x01; //把P1.6脚设置为RXD
	LPC_IOCON->PIO1_7 &= ~0x07;	
	LPC_IOCON->PIO1_7 |= 0x01; //把P1.7脚设置为TXD
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟

	LPC_SYSCON->UARTCLKDIV = 0x1;	//时钟分频值为1	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//允许UART时钟
	
	AutoBaud();
	
	//sprintf(str,"%8d",baud);    //小数点后3位
	while(1)
	{
		
	//	UART_send(str,8);
		UART_send((uint8_t *)"贞明电子：http://shop58972409.taobao.com\r\n",42);
		delay_ms(1000);
	}
}







