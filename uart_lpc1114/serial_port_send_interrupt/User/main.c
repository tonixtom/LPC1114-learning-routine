/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ�ô��ڷ���
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"





void UART_IRQHandler(void)
{
	uint32_t IRQ_ID;		  // �����ȡ�ж�ID�ű���
	uint8_t redata;    // ����������ݱ�������

	IRQ_ID = LPC_UART->IIR;   // ���ж�ID��
	IRQ_ID =((IRQ_ID>>1)&0x7);// ���bit4:bit1	
	if(IRQ_ID == 0x02 )		  // ����ǲ��ǽ�������������ж�
	{
		redata = LPC_UART->RBR;	  // ��RXFIFO�ж�ȡ���յ�������
		UART_send_byte(redata); //���ڷ��ͻ��з��ֽ�
	}

}
int main()
{
	UART_init(9600); // �Ѵ��ڲ���������Ϊ9600
	LPC_UART->IER = 0x01;	//ֻ��������жϣ��ر������ж�
	NVIC_EnableIRQ(UART_IRQn); //���ⲿ�ж��ܿ��أ�������򿪴����ж�
	
	
	while(1)
	{
		;
	}

}

