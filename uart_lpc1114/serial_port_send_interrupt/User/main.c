/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用串口发送
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"





void UART_IRQHandler(void)
{
	uint32_t IRQ_ID;		  // 定义读取中断ID号变量
	uint8_t redata;    // 定义接收数据变量数组

	IRQ_ID = LPC_UART->IIR;   // 读中断ID号
	IRQ_ID =((IRQ_ID>>1)&0x7);// 检测bit4:bit1	
	if(IRQ_ID == 0x02 )		  // 检测是不是接收数据引起的中断
	{
		redata = LPC_UART->RBR;	  // 从RXFIFO中读取接收到的数据
		UART_send_byte(redata); //串口发送换行符字节
	}

}
int main()
{
	UART_init(9600); // 把串口波特率配置为9600
	LPC_UART->IER = 0x01;	//只允许接收中断，关闭其他中断
	NVIC_EnableIRQ(UART_IRQn); //打开外部中断总开关，利用其打开串口中断
	
	
	while(1)
	{
		;
	}

}

