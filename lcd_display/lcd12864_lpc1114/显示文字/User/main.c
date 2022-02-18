#include <LPC11xx.h>
#include "lcd12864.h"
#include "uart.h"




/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main(void)
{

	LPC_GPIO2->DIR = 0xFFF;   		//设置端口2为输出方向
	LPC_GPIO2->DATA = 0xFFF;  	//端口输出高电平
	LPC_GPIO3->DIR = 0xFFF;   		//设置端口2为输出方向
	LPC_GPIO3->DATA = 0xFFF;  	//端口输出高电平
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//使能CT16B0时钟

	

	UART_init(9600);
	Lcd12864_Init();
	Lcd12864_ClearScreen();
	
	UART_send("begin   ",8);
	UART_send_byte('\n');
		

	while (1)
	{
		Lcd12864_Write16CnCHAR(0, 0, (uint8_t *)"司公限有技科中普");
		TIM16B0_delay_ms(100);
		Lcd12864_Write16CnCHAR(0, 2, (uint8_t *)"司公限有技科中普");
		TIM16B0_delay_ms(100);
		Lcd12864_Write16CnCHAR(0, 4, (uint8_t *)"司公限有技科中普");
		TIM16B0_delay_ms(100);
		Lcd12864_Write16CnCHAR(0, 6, (uint8_t *)"司公限有技科中普");
		TIM16B0_delay_ms(100);
	}

}


