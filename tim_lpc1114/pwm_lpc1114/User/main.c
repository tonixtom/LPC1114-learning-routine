/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ��ͨ�ö�ʱ��PWM����
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "timer.h"

void delay_ms(uint16_t ms)
{
	uint16_t i,j;
	
	for(i=0;i<5000;i++)
		for(j=0;j<ms;j++);
}


int main()
{
	cycle = 10000;
	duty = 99;
	
	T16B0M0_PWM_Init(); // ����10000΢�룬ռ�ձ�20%
	
	while(1)
	{
		delay_ms(50);
		if(duty<50)duty=99;		
		T16B0M0_PWM_SET();
		duty--;
	}
}





