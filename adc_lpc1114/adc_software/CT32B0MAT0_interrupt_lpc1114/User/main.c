/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ��CT32B0MAT0��������ADCת�����жϷ�ʽ��ȡADCֵ
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "adc.h"

uint8_t Channel;

void ADC_IRQHandler(void)
{
	uint16_t adc_value;
	
	adc_value = (LPC_ADC->DR[Channel]>>6)&0x3FF;		
	adc_value = (adc_value*Vref)/1024; // ת��Ϊ�����ĵ�ѹֵ
	UART_send_byte(adc_value>>8);
	UART_send_byte(adc_value);
}

int main()
{
	Channel = 7;
	
	UART_init(9600);
	ADC_Init(Channel);
	TIM32B0_MAT_Init(500);
	
	while(1)
	{
		;
	}
}




