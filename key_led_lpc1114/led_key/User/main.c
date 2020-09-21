/**************************************************************************************/

/* ���ƣ���������LEDʵ��                                          */
/* Ч�������°���1��LED1�����ͷŰ�����LED1��                      */
/*       ���°���2��LED2�����ͷŰ�����LED2��                      */
/* Ӳ�����ӣ�P1.0---KEY1   P1.1---KEY2                            */
/*           P0.3---LED1   P1.10--LED2                            */

/**************************************************************************************/
#include "lpc11xx.h"
#include "stdio.h"
#include "stdlib.h"


int main(void)
{


	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);     // ʹ��IOCONʱ��
	LPC_IOCON->R_PIO1_0 = 0XD1; //��PIN33����ΪP1.0��
	LPC_IOCON->R_PIO1_1 = 0XD1; //��PIN34����ΪP1.1��
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);     // ʹ��IOCONʱ�ӣ�����������ɺ�رո�ʱ�ӣ�

	//��P1.0��P1.1����Ϊ����
	LPC_GPIO1->DIR &= ~(1<<0);
	LPC_GPIO1->DIR &= ~(1<<1);	
	//��P0.3��P1.10��������Ϊ���
	LPC_GPIO0->DIR |= (1<<3);
	LPC_GPIO1->DIR |= (1<<10);
	//��LED1  ��LED2
 	LPC_GPIO0->DATA &= ~(1<<3);
	LPC_GPIO1->DATA |= (1<<10); 



	while(1)
	{
		if((LPC_GPIO1->DATA&(1<<0))!=(1<<0))		 // �����KEY1������
		{
			LPC_GPIO0->DATA |= (1<<3);				 // ��LED1
			while((LPC_GPIO1->DATA&(1<<0))!=(1<<0));	 // �ȴ������ͷ�
			LPC_GPIO0->DATA &= ~(1<<3);				 // ��LED1
		}
		else if((LPC_GPIO1->DATA&(1<<1))!=(1<<1))	 // �����KEY2������
		{
			LPC_GPIO1->DATA &= ~(1<<10);			 // ��LED2
			while((LPC_GPIO1->DATA&(1<<1))!=(1<<1));	 // �ȴ������ͷ�
			LPC_GPIO1->DATA |= (1<<10);				 // ��LED2
		}
	}
}