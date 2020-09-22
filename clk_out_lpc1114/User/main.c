/******************************************************************/
/* ���ƣ�CLKOUT����(��P0.1��)���ʱ��Ƶ��                         */
/* Ч������P1.0����ռ�ձ�Ϊ50%�ķ���Ƶ����������Ƶ��ȡ����div   */
/* ���Ź�������Ϊ��ʱ��Դ������LPC1114����ƵΪ2.3MHz,��div���з�Ƶ           */
/*       div = 1   ���Ƶ�� = 2.3MHz  ���Դ����ƣ�                 */
/******************************************************************/
#include "lpc11xx.h"
#include "stdio.h"
#include "stdlib.h"



#if 0    //��һ��ʱ������

void SysCLK_config(void)
{
	uint8_t i;
	/*ִ�����´���ѡ���ⲿ12M������Ϊʱ��Դ*/
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          //ϵͳ�����ϵ�   
  	LPC_SYSCON->SYSOSCCTRL    = 0x00000000;			//����δ����·��1~20MhzƵ������
  	for (i = 0; i < 200; i++) __nop();		    //�ȴ������ȶ�
 	LPC_SYSCON->SYSPLLCLKSEL  = 0x00000001;         //PLLʱ��Դѡ��ϵͳ������
  	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               //����PLLѡ��ʱ��Դ
  	LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               //��д0����д1�ﵽ����ʱ��Դ��Ŀ�ģ������ֲ�涨��
  	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
  	while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     //ȷ��ʱ��Դ���º�����ִ��
	/*ִ�����´��뱶ƵΪ48MHz*/
	LPC_SYSCON->SYSPLLCTRL    = 0x00000023;     	//����M=4;P=2; FCLKOUT=12*4=48Mhz
  	LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          //PLL�ϵ�
  	while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	    //ȷ��PLL�����Ժ�����ִ��
	/*��ʱ��Դѡ��Ƶ�Ժ��ʱ��*/
	LPC_SYSCON->MAINCLKSEL    = 0x00000003;			//��ʱ��Դѡ��PLL���ʱ��
	LPC_SYSCON->MAINCLKUEN    = 0x01;				//������ʱ��Դ
	LPC_SYSCON->MAINCLKUEN    = 0x00;				//��д0����д1�ﵽ����ʱ��Դ��Ŀ�ģ������ֲ�涨��
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));	    //ȷ����ʱ�������Ժ�����ִ��
	LPC_SYSCON->SYSAHBCLKDIV  = 0x01;				//AHBʱ�ӷ�ƵֵΪ1��ʹAHBʱ������Ϊ48Mhz
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);            //ʹ��GPIOʱ�ӣ��õ�Ƭ������û�в���GPIO��ʱ��
}

#endif

/***********************************************/
/*  �������ܣ�ʹ��CLKOUT�����Ƶ��             */
/*  ��ڲ�����CLKOUT_DIV,��CLKOUT��Ƶֵ��1~255 */
/*  ˵����    �˺�������������ʱ����ʵ��       */
/***********************************************/
void CLKOUT_EN(uint8_t CLKOUT_DIV)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);          // ʹ��IOCONʱ�� 
	LPC_IOCON->PIO0_1=0XD1;						   // ��P0.1������ΪCLKOUT����
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);          // ����IOCONʱ��
	LPC_SYSCON->CLKOUTDIV   = CLKOUT_DIV;			//CLKOUTʱ��ֵΪ48/CLKOUT_DIV
	LPC_SYSCON->CLKOUTCLKSEL= 0X00000003;	  		//CLKOUTʱ��Դѡ��Ϊ��ʱ��
	LPC_SYSCON->CLKOUTUEN   =0X01;
	LPC_SYSCON->CLKOUTUEN   =0X00;
	LPC_SYSCON->CLKOUTUEN   =1;
	while (!(LPC_SYSCON->CLKOUTUEN & 0x01));        //ȷ��ʱ��Դ���º�����ִ��
}


#define div   250

int main(void)
{

	// ʹ��CLKOUT�������ʱ��Ƶ��
	CLKOUT_EN(div);
	//clkoutʱ�����ֵ = 2.3M/250=9.2k
	while(1)
	{
		 ;
	}
}



