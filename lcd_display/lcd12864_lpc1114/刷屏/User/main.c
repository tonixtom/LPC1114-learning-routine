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


	uint8_t i, j;
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
		
/*
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
		UART_send("tomish   ",8);
		UART_send_byte('\n');
	}
*/


	while(1)
	{
		//--��������ˢ����Ļ--//
		for (i=0; i<8; i++)
		{
			LcdSt7565_WriteCmd(0xB0+i); //����Y���꣬������Կ��������������˵��

			LcdSt7565_WriteCmd(0x10);   //����X���꣬������Կ��������������˵��
			LcdSt7565_WriteCmd(0x04);
			for (j=0; j<128; j++)
			{
				LcdSt7565_WriteData(0xFF);  //������ñ���Ϊ��ɫʱ������ѡ��0XFF
				TIM16B0_delay_ms(10);	           //��ʱһ��
			}
		}

		//--��������ˢ����Ļ--//
		for (i=0; i<8; i++)
		{
			LcdSt7565_WriteCmd(0xB0+i); //����Y���꣬������Կ��������������˵��

			LcdSt7565_WriteCmd(0x10);   //����X���꣬������Կ��������������˵��
			LcdSt7565_WriteCmd(0x04);
			for (j=0; j<128; j++)
			{
				LcdSt7565_WriteData(0x00);  //������ñ���Ϊ��ɫʱ������ѡ��0XFF
				TIM16B0_delay_ms(10);			   //��ʱһ��
			}
		}	
	}

}


