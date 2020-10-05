/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ�ÿ��Ź������÷�
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/

#include "lpc11xx.h"
#include "wdt.h"
#include "uart.h"

void delay(void)
{
	uint16_t i,j;
	
	for(i=0;i<5000;i++)
		for(j=0;j<250;j++);
}

int main()
{
	uint8_t i=0;
	
	UART_init(9600);
	WDT_Enable(1);	 // ���Ź���ʼ����1����֮��ι��
	
	while(1)
	{
		delay();
		WDTFeed();
		UART_send_byte(i);
		i++;
	}
}




