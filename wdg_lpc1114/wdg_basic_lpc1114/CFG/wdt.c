#include "lpc11xx.h"
#include "wdt.h"


/******************************************/
/* �������ܣ�ʹ�ܿ��Ź�                   */
/* ��    ����mode = 1 ��ι��������λ      */
/*           mode = 0 ��ι�������ж�      */
/******************************************/
void WDT_Enable(uint8_t mode)
{ 
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    // ���Ź�����ʱ���ϵ磨bit6��
	LPC_SYSCON->WDTOSCCTRL = (0x1<<5); // DIVSEL=0 FREQSEL=1  WDT_OSC_CLK=300KHz
  LPC_SYSCON->WDTCLKSEL = 0x2;        // ѡ���Ź�ʱ��Դ
  LPC_SYSCON->WDTCLKUEN = 0x01;          // ����ʱ��Դ
  LPC_SYSCON->WDTCLKUEN = 0x00;          // ��д0����д1�ﵽ����Ŀ��
  LPC_SYSCON->WDTCLKUEN = 0x01;
  while ( !(LPC_SYSCON->WDTCLKUEN & 0x01) );  // �ȴ����³ɹ�
  LPC_SYSCON->WDTCLKDIV = 3;            // ���ÿ��Ź���ƵֵΪ3���������ڵĿ��Ź�ʱ��Ϊ100K	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<15);// ����WDTʱ��
  LPC_WDT->TC = 25000;		// �����Ź���ʱ����ֵ����ʱʱ���Լ1��(������wdt_clk=100KHzʱ)
	if(mode==1) LPC_WDT->MOD |= 0x03;		// дֵ0x03����ι��������λ  
  else if(mode==0) LPC_WDT->MOD |= 0x01; //  дֵ0x01����ι�������ж�
 	LPC_WDT->FEED = 0xAA;		// ι���Ź�������
  LPC_WDT->FEED = 0x55;    
}

/******************************************/
/* �������ܣ����Ź��жϷ�����           */
/* ˵������MODֵ����Ϊ0x01ʱ�����û�м�ʱ*/
/*       ι���������������жϺ�����     */
/******************************************/
void WDT_IRQHandler(void)
{
 	LPC_WDT->MOD &= ~(0x1<<2);		// �忴�Ź���ʱ��־λWDTOF
	// ���������д�뵱���Ź��жϷ���ʱ����Ҫ��������
}
/******************************************/
/* �������ܣ�ι��                         */
/******************************************/
void WDTFeed(void)
{
  LPC_WDT->FEED = 0xAA;		// ι��
  LPC_WDT->FEED = 0x55;
}




