/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ��ͨ�ö�ʱ����������
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "timer.h"
#include "uart.h"
#include "stdlib.h"
#include "stdio.h"

int main()
{
	uint16_t temp1,temp2;
	char str[8]={'0'};
	
	UART_init(9600); // ��ʼ������
	T16B0_cnt_init(); // ��ʼ����ʱ��
	temp1 = LPC_TMR16B0->TC; // ��ȡTCֵ
	
	while(1)
	{
		temp2 = LPC_TMR16B0->TC; // ��ȡTCֵ
		if(temp2!=temp1) // �����λ�ȡ��TCֵ����һ�εĲ����
		{
			temp1 = LPC_TMR16B0->TC; // ����ε�TCֵ����temp1
 			sprintf(str, "%8d", temp1);
			UART_send((uint8_t *)str, 8);
			UART_send_byte('\n');
 		}
	}
}





