#include "lpc11xx.h"
#include "uart.h"


/************************************************/
/* �������ܣ���ʼ��UART��                       */
/************************************************/
void UART_init(uint32_t baudrate)
{
	uint32_t DL_value,Clear=Clear;   // (�����ַ�ʽ������������������Warning)                       
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ�� 
	LPC_IOCON->PIO1_6 &= ~0x07;    
	LPC_IOCON->PIO1_6 |= 0x01; //��P1.6������ΪRXD
	LPC_IOCON->PIO1_7 &= ~0x07;	
	LPC_IOCON->PIO1_7 |= 0x01; //��P1.7������ΪTXD
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��

	LPC_SYSCON->UARTCLKDIV = 0x1;	//ʱ�ӷ�ƵֵΪ1
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//����UARTʱ��
	LPC_UART->LCR = 0x83;   //8λ���䣬1��ֹͣλ���޼�żУ�飬������ʳ���������
	DL_value = SystemCoreClock/16/baudrate ;  //����ò�����Ҫ��ĳ�������Ĵ���ֵ
	LPC_UART->DLM = DL_value / 256;	   //д������������λֵ			
	LPC_UART->DLL = DL_value % 256;	  //д������������λֵ
	LPC_UART->LCR = 0x03;    //DLAB��0
	LPC_UART->FCR = 0x07;    //����FIFO�����RxFIFO �� TxFIFO
	Clear = LPC_UART->LSR;   //��UART״̬�Ĵ�������ղ���״̬
}

/************************************************/
/* �������ܣ����ڽ����ֽ�����                       */
/************************************************/
uint8_t UART_recive(void)
{	
	while(!(LPC_UART->LSR & (1<<0)));//�ȴ����յ�����
	return(LPC_UART->RBR);			 //��������
}

/************************************************/
/* �������ܣ����ڷ����ֽ�����                       */
/************************************************/
void UART_send_byte(uint8_t byte)
{
	while ( !(LPC_UART->LSR & (1<<5)) );//�ȴ�������
	LPC_UART->THR = byte;
}

/************************************************/
/* �������ܣ����ڷ�����������                   */
/************************************************/
void UART_send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		while ( !(LPC_UART->LSR & (1<<5)) );//�ȴ�������
		LPC_UART->THR = *Buffer;
		Buffer++;
		Length--;
	}
}


