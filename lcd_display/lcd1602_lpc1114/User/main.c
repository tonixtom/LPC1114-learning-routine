#include <LPC11xx.h>
#include "lcd_1602.h"

//******************************������ʾ�ַ���**********************************
uint8_t const str0[]={"  Hello World!"};
uint8_t const str1[]={"LPC1114 duble !"};



//*******************************������***********************************
int main(void) 
{
  LPC_GPIO2->DIR = 0xFFF;   		//���ö˿�2Ϊ�������
  LPC_GPIO2->DATA = 0xFFF;  	//�˿�����ߵ�ƽ
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//ʹ��CT16B0ʱ��
	
  InitLcd();                                 		//LCD��ʼ��
  ePutstr(0,0,str0);                   		//��һ���ַ���ʾ
  TIM16B0_delay_ms(5);        		//��ʱ5ms�ȴ���ʾ�ȶ�
  ePutstr(0,1,str1);                   		//�ڶ����ַ���ʾ
  while(1)
    {
         ;      //��ѭ��
    }
}

