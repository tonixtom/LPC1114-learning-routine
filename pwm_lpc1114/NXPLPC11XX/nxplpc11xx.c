////////////////////////////////////////////////////////////////////////////////
//  Company: �ɶ������ܿƼ� Ruichuang Smart Technology                      //
//     shop: http://ruicstech.taobao.com                                      // 
//  Engineer:  Youzhiyu                                                       //
//  QQ      :  4016682  													  //
//  ����    �� yzyseal                                                        //
//  Target Device: LPC1114                                                    //
//  Tool versions: MDK4.12                                                    //
//  Create Date  :   2011-09-06 10:09                                         //
//  Description:                                                              //
//        �������ܣ�����ϵͳʱ��                                              //
//		  ˵����ѡ���ⲿ12M������Ϊϵͳʱ�ӣ���ͨ����Ƶ����PLL����ʱ�ӱ�Ƶ4�� //
//		  ע�⣺ʹ������ֵ����ʱ�޸ı�Ƶֵ�����ʱ��Ҫ����<=50MHz		      //
////////////////////////////////////////////////////////////////////////////////
// 	   Copyright (C) 2011-2012  Youzhiyu   All rights reserved                //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////

#include "nxplpc11xx.h"

void SysCLK_config(void)
{
	uint8 i;
	/*ִ�����´���ѡ���ⲿ12M������Ϊʱ��Դ*/
	SYSCON->PDRUNCFG     &= ~(1 << 5);          //ϵͳ�����ϵ�   
  	SYSCON->SYSOSCCTRL    = 0x00000000;			//����δ����·��1~20MhzƵ������
  	for (i = 0; i < 200; i++) __nop();		    //�ȴ������ȶ�
 	SYSCON->SYSPLLCLKSEL  = 0x00000001;         //PLLʱ��Դѡ��ϵͳ������
  	SYSCON->SYSPLLCLKUEN  = 0x01;               //����PLLѡ��ʱ��Դ
  	SYSCON->SYSPLLCLKUEN  = 0x00;               //��д0����д1�ﵽ����ʱ��Դ��Ŀ�ģ������ֲ�涨��
  	SYSCON->SYSPLLCLKUEN  = 0x01;
  	while (!(SYSCON->SYSPLLCLKUEN & 0x01));     //ȷ��ʱ��Դ���º�����ִ��
	/*ִ�����´��뱶ƵΪ48MHz*/
	SYSCON->SYSPLLCTRL    = 0x00000023;     	//����M=4;P=2; FCLKOUT=12*4=48Mhz
  	SYSCON->PDRUNCFG     &= ~(1 << 7);          //PLL�ϵ�
  	while (!(SYSCON->SYSPLLSTAT & 0x01));	    //ȷ��PLL�����Ժ�����ִ��
	/*��ʱ��Դѡ��Ƶ�Ժ��ʱ��*/
	SYSCON->MAINCLKSEL    = 0x00000003;			//��ʱ��Դѡ��PLL���ʱ��
	SYSCON->MAINCLKUEN    = 0x01;				//������ʱ��Դ
	SYSCON->MAINCLKUEN    = 0x00;				//��д0����д1�ﵽ����ʱ��Դ��Ŀ�ģ������ֲ�涨��
	SYSCON->MAINCLKUEN    = 0x01;
	while (!(SYSCON->MAINCLKUEN & 0x01));	    //ȷ����ʱ�������Ժ�����ִ��
	SYSCON->SYSAHBCLKDIV  = 0x01;				//AHBʱ�ӷ�ƵֵΪ1��ʹAHBʱ������Ϊ48Mhz
	SYSCON->SYSAHBCLKCTRL |= (1<<6);            //ʹ��GPIOʱ�ӣ��õ�Ƭ������û�в���GPIO��ʱ��
}



/***********************************************/
/*  �������ܣ�ʹ��CLKOUT�����Ƶ��             */
/*  ��ڲ�����CLKOUT_DIV,��CLKOUT��Ƶֵ��1~255 */
/*  ˵����    �˺�������������ʱ����ʵ��       */
/***********************************************/
void CLKOUT_EN(uint8 CLKOUT_DIV)
{
	SYSCON->SYSAHBCLKCTRL |= (1<<16);          // ʹ��IOCONʱ�� 
	IOCON->PIO0_1=0XD1;						   // ��P0.1������ΪCLKOUT����
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16);          // ����IOCONʱ��
	SYSCON->CLKOUTDIV   = CLKOUT_DIV;			//CLKOUTʱ��ֵΪ48/CLKOUT_DIV
	SYSCON->CLKOUTCLKSEL= 0X00000003;	  		//CLKOUTʱ��Դѡ��Ϊ��ʱ��
	SYSCON->CLKOUTUEN   =0X01;
	SYSCON->CLKOUTUEN   =0X00;
	SYSCON->CLKOUTUEN   =0X01;
	while (!(SYSCON->CLKOUTUEN & 0x01));        //ȷ��ʱ��Դ���º�����ִ��
}

/**********************************************/
/*  �������ܣ�SysTick��ʱ                     */
/*  ��ڲ���������ֵ��΢��ֵ                  */
/*  ˵����    ����ϵͳ��ʱ��ʵ��              */
/*            48Mhzʱ�ӹ�����                 */
/**********************************************/
static volatile uint32 TimeTick = 0;
		  
void SysTick_Handler(void)					  //ϵͳ��ʱ���жϷ�����
{
	TimeTick++;
}

void delay_ms(uint32 ms) /* ע�⣺����Ĳ������ȡ699������ᳬ��24λ������ֵ */
{
	SYSTICK->STRELOAD =	(((24000)*ms)-1);	  //�����ؼ�������дֵ
	SYSTICK->STCURR   =	 0;					  //����������
	SYSTICK->STCTRL  |=  ((1<<1)|(1<<0));     //����������,�����������ж�
	while(!TimeTick);
	TimeTick = 0;
	SYSTICK->STCTRL =0;	
}

void delay_us(uint32 us)
{
	SYSTICK->STRELOAD =	(((24)*us)-1);	  //�����ؼ�������дֵ
	SYSTICK->STCURR   =	 0;					  //����������
	SYSTICK->STCTRL  |=  ((1<<1)|(1<<0));     //����������,�����������ж�
	while(!TimeTick);
	TimeTick = 0;
	SYSTICK->STCTRL =0;	
}


