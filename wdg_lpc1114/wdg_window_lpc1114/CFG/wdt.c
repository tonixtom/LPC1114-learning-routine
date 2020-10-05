#include "lpc11xx.h"
#include "wdt.h"
#include "uart.h"

/******************************************/
/* �������ܣ�ʹ�ܴ��ڿ��Ź�����           */
/******************************************/
void WDT_Window_Enable()
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
	LPC_WDT->WARNINT = 1023; // �����Ź���ʱ��������1023ʱ�������ж�
	LPC_WDT->WINDOW = 4600; // ���ι��ֵ
	LPC_WDT->MOD |= 0x03;		// дֵ0x03����ι��������λ  
 	LPC_WDT->FEED = 0xAA;		// ι���Ź�������
  LPC_WDT->FEED = 0x55;    
}


/******************************************/
/* �������ܣ�ι��                         */
/******************************************/
void WDTFeed(void)
{
  LPC_WDT->FEED = 0xAA;		// ι��
  LPC_WDT->FEED = 0x55;
}




