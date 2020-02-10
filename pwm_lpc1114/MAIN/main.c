////////////////////////////////////////////////////////////////////////////////
//  Company: �ɶ������ܿƼ� Ruichuang Smart Technology                      //
//     shop: http://ruicstech.taobao.com                                      // 
//  Engineer:  Youzhiyu                                                       //
//  QQ      :  4016682  													  //
//  ����    �� yzyseal                                                        //
//  Target Device: LPC1114                                                    //
//  Tool versions: MDK4.12                                                    //
//  Create Date  :   2011-09-06 10:09                                         //
//  Description  :   LPC1114 ��ʱ����ʾ                                       //
////////////////////////////////////////////////////////////////////////////////
// 	   Copyright (C) 2011-2012  Youzhiyu   All rights reserved                //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////


#include "nxplpc11xx.h"
#include "ct.h"

void KEY_Init(void)
{
	SYSCON->SYSAHBCLKCTRL |= (1<<16); //ʹ��IOCONʱ��(bit16)
	IOCON->PIO1_0 = 0XD1; //��PIN33����ΪP1.0��
	IOCON->PIO1_1 = 0XD1; //��PIN34����ΪP1.1��
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16);//����IOCONʱ��(bit16)������������ɺ�رո�ʱ�ӣ�

	//��P1.0��P1.1����Ϊ����
	GPIO1->DIR &= ~(1<<0);
	GPIO1->DIR &= ~(1<<1);	
}

int main()
{
	uint8 duty=50;
	uint32 cycle_us=10000;
	
	SysCLK_config(); // ϵͳʱ�ӳ�ʼ��
	KEY_Init();      // ��ʼ��MINI LPC1114�������ϵİ���
	

	TIM32B0_init();	 // ʹ�ܶ�ʱ��TIM32B0
	TIM32B0_PWM(cycle_us, duty);	 // ��P1.6�������ռ�ձ�Ϊ50%��100Hz�����ź�

   //��P1.6�����������100Hz�����źţ��������ʾ�����۲죬С�Ĳ��ԣ��ڿ�����ı����и������ŵı�ǣ�����Ժܿ���ҵ�����");
	 //�����ͨ������KEY1��KEY2�ı������źŵ�ռ�ձȣ�KEY1����ռ�ձȣ�KEY2��Сռ�ձ�  Ϊduty;


	while(1)
	{
		if((GPIO1->DATA&(1<<0))!=(1<<0))		 // �����KEY1������
		{
			if(duty<99)
			{
				duty++;
				TMR32B0->MR0 = 48*cycle_us*(100-duty)/100;//����ռ�ձ�
				//show duty, 2
			}
			while((GPIO1->DATA&(1<<0))!=(1<<0));	 // �ȴ������ͷ�
		}
		else if((GPIO1->DATA&(1<<1))!=(1<<1))	 // �����KEY2������
		{
			if(duty>1)
			{
				duty--;
				TMR32B0->MR0 = 48*cycle_us*(100-duty)/100;//����ռ�ձ�
				//show duty, 2
			}
			while((GPIO1->DATA&(1<<1))!=(1<<1));	 // �ȴ������ͷ�
		}
	}
}




