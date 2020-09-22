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

#define LED1_ON LPC_GPIO0->DATA &= ~(1<<3)
#define LED1_OFF LPC_GPIO0->DATA |= (1<<3)
#define KEY1_DOWN (LPC_GPIO1->DATA&(1<<0))!=(1<<0)


//GPIO1�жϷ�����
void PIOINT1_IRQHandler_keytest(void)
{	
	if((LPC_GPIO1->MIS&0x001) == 0x001)	   // ����ǲ���P1.0���Ų������ж�
	{
		LED1_ON;				 // ��LED1
		while(KEY1_DOWN);	 // �ȴ������ͷ�
		LED1_OFF;			 // ��LED1	
	}
	else if((LPC_GPIO1->MIS&0x002)==0x002) // ����ǲ���P1.1���Ų������ж�
	{
		LPC_GPIO1->DATA &= ~(1<<10);			 // ��LED2
		while((LPC_GPIO1->DATA&(1<<1))!=(1<<1));	 // �ȴ������ͷ�
		LPC_GPIO1->DATA |= (1<<10);				 // ��LED2
	}
	LPC_GPIO1->IC = 0x3FF;  // ���GPIO1�ϵ��ж�
}

void led_init()
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
 	LPC_GPIO0->DATA |= (1<<3);
	LPC_GPIO1->DATA |= (1<<10);
}

int main(void)
{	
	
	led_init();
		
	//LPC_GPIO1->DATA |= (1<<0);   //P1.0��0
	
	
	LPC_GPIO1->IS |= (1<<0); //ѡ��P1.0Ϊ��ƽ����
	LPC_GPIO1->IEV &= ~(1<<0);//ѡ��P1.0Ϊ�͵�ƽ���� 
	LPC_GPIO1->IE |= (1<<0);  //����P1.0�жϲ�������

	LPC_GPIO1->IS &= ~(1<<1); //ѡ��P1.1Ϊ���ش���
	LPC_GPIO1->IEV &= ~(1<<1);//ѡ��P1.1Ϊ�½��ش���
	LPC_GPIO1->IE |= (1<<1);  //����P1.1�жϲ�������
	NVIC_EnableIRQ(EINT1_IRQn);	// ʹ��GPIO1�ж�
	
	while(1)
	{
		;
	}
}
