/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ��ͨ�ö�ʱ��������
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "timer.h"
#include "uart.h"

uint16_t temp;   // 
uint16_t freq;   // 

// �Ǿ�ȷ��ʱ
void delay_ms(uint16_t ms)
{
	uint16_t i,j;
	
	for(i=0;i<5000;i++)
		for(j=0;j<ms;j++);
}

/***********************************************/
/*  �������ܣ�ʹ��CLKOUT�����Ƶ��             */
/*  ��ڲ�����CLKOUT_DIV,��CLKOUT��Ƶֵ��1~255 */
/*             =0 �ر�ʱ�����                 */
/*  ˵����    �˺�������������ʱ��             */
/***********************************************/
void CLKOUT_EN(uint8_t CLKOUT_DIV)
{
	LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    // ���Ź�����ʱ���ϵ磨bit6��
	LPC_SYSCON->WDTOSCCTRL = 0X3F; // DIVSEL = 31, FREQSEL = 0X1; �����Ź�ʱ�����Ϊ0.6M/2*(1+31)=9375����
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);          // ʹ��IOCONʱ�� 
	LPC_IOCON->PIO0_1=0XD1;						             // ��P0.1������ΪCLKOUT����
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);         // ����IOCONʱ��
	LPC_SYSCON->CLKOUTDIV   = CLKOUT_DIV;			     // CLKOUTʱ��ֵ���=��ʱ��/CLKOUT_DIV
	LPC_SYSCON->CLKOUTCLKSEL= 0X00000002;	  		   // CLKOUTʱ��Դѡ��Ϊ���Ź�ʱ��
	LPC_SYSCON->CLKOUTUEN   =0;
	LPC_SYSCON->CLKOUTUEN   =1;
	while (!(LPC_SYSCON->CLKOUTUEN & 0x01));       // ȷ��ʱ��Դ���º�����ִ��
}

void TIMER16_0_IRQHandler(void)
{
	if((LPC_TMR16B0->IR&0x10)==0x10) // �����CAP������ж�
	{
		temp = LPC_TMR16B0->CR0;
		LPC_TMR16B0->TC = 0;
		freq = 100000/temp; // �ѵ�λת���ɺ���
	}
	else if((LPC_TMR16B0->IR&0X01)==0X01) // �����MR0ƥ��������ж�,������ж�
	{
		freq = 0;
	}
	LPC_TMR16B0->IR = 0X1F; // ���ж�λ
}

int main()
{
	UART_init(9600);
	T16B0_CAP_Init();
	CLKOUT_EN(200);//  9375/200=46Hz
	
	while(1)
	{
		delay_ms(500);
		UART_send_byte(freq);
		UART_send_byte(freq>>8);
	}
}





