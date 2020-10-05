/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ��CT16B0MAT0��������ADCת������ȡADCֵ
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "adc.h"

#include "stdio.h"
#include "stdlib.h"



int main()
{
	uint16_t adc_value;
	char str[8]={'0'};

	UART_init(9600);
	ADC_Init(5);
	
	while(1)
	{

		UART_send("next: ", 6);
		
		adc_value = ADC_Read(5);
		//itoa(adc_value, str, 10);
		sprintf(str, "%8d", adc_value);
		UART_send(str, 8);
		UART_send_byte('\n');
		
	//	UART_send_byte(adc_value>>8);
	//	UART_send_byte(adc_value);
	}
}   



