#include <LPC11xx.h>
#include "lcd12864.h"
#include "uart.h"




/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main(void)
{

	LPC_GPIO2->DIR = 0xFFF;   		//���ö˿�2Ϊ�������
	LPC_GPIO2->DATA = 0xFFF;  	//�˿�����ߵ�ƽ
	LPC_GPIO3->DIR = 0xFFF;   		//���ö˿�2Ϊ�������
	LPC_GPIO3->DATA = 0xFFF;  	//�˿�����ߵ�ƽ
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//ʹ��CT16B0ʱ��

	

	UART_init(9600);
	Lcd12864_Init();
	Lcd12864_ClearScreen();
	
	UART_send("begin   ",8);
	UART_send_byte('\n');
		

	while (1)
	{
		Lcd12864_Write16CnCHAR(0, 0, (uint8_t *)"˾�����м�������");
		TIM16B0_delay_ms(100);
		Lcd12864_Write16CnCHAR(0, 2, (uint8_t *)"˾�����м�������");
		TIM16B0_delay_ms(100);
		Lcd12864_Write16CnCHAR(0, 4, (uint8_t *)"˾�����м�������");
		TIM16B0_delay_ms(100);
		Lcd12864_Write16CnCHAR(0, 6, (uint8_t *)"˾�����м�������");
		TIM16B0_delay_ms(100);
	}

}


