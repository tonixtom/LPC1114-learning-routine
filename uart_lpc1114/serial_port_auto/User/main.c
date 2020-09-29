/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ���Զ������ʲ��Թ���
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "stdio.h"
#include "stdlib.h"




/********************** �������� ********************/
/****************************************************
*��  �ƣ�	��ʱ����    							*
*��  ����   ��ʱʱ��								*
*��  ע��	��������    							*
*****************************************************/
__inline void delay_ms(uint32_t a)    //1ms��ʱ����
{                           
	uint32_t i;
	while( --a != 0)
	{
   		for(i = 0; i<5500; i++);
	}             
}
void AutoBaud(void)
{
	char str[64];
	uint32_t baud;
	uint8_t dlm,  dll;

	LPC_UART->ACR  = 0x03;							// �����Զ�������
	while ((LPC_UART->ACR & 0x01) != 0x0);			// �ȴ��Զ������ʲ������
	LPC_UART->ACR 		 |= 0x01 << 8;				// ����Զ��������жϱ�־
	LPC_UART->LCR = 0x83;
	dlm   = LPC_UART->DLM;
	dll   = LPC_UART->DLL;
	LPC_UART->LCR = 0x03;
	LPC_UART->FCR = 0x07;    //����FIFO�����RxFIFO �� TxFIFO
	baud  = ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV) / (16 * (256 * dlm + dll)));
	sprintf(str,  "LPC1114  ZhengMing Hello! Baud is %4d bps \n",  baud);
	UART_send((uint8_t *)str,45);
}

/**********************************************/
/*               ������                       */
/**********************************************/
int main()
{
	char str[8]={'0'};
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ�� 
	LPC_IOCON->PIO1_6 &= ~0x07;    
	LPC_IOCON->PIO1_6 |= 0x01; //��P1.6������ΪRXD
	LPC_IOCON->PIO1_7 &= ~0x07;	
	LPC_IOCON->PIO1_7 |= 0x01; //��P1.7������ΪTXD
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��

	LPC_SYSCON->UARTCLKDIV = 0x1;	//ʱ�ӷ�ƵֵΪ1	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//����UARTʱ��
	
	AutoBaud();
	
	//sprintf(str,"%8d",baud);    //С�����3λ
	while(1)
	{
		
	//	UART_send(str,8);
		UART_send((uint8_t *)"�������ӣ�http://shop58972409.taobao.com\r\n",42);
		delay_ms(1000);
	}
}







