/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ��CT16B0MAT1��������ADCת������ȡADCֵ
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "adc.h"



int main()
{
	uint16_t adc_value;
	
	UART_init(9600);
	ADC_Init(7);
	TIM16B0_MAT1_Init(500);
	
	while(1)
	{
		adc_value = ADC_Read(7);
		UART_send_byte(adc_value>>8);
		UART_send_byte(adc_value);
	}
}




