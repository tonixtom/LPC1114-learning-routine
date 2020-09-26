/************************************************************************************** 
*   ����    ��2013��11��6��  
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����12Mhz(��Ƶ48M)
*   ����    ��ѧϰʹ��AT24C02�洢����
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
//  Description:   ģ��I2Cʱ����AT24C16ͨ��                                   //
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "i2c.h"
#include "at24c16.h"

static volatile uint32_t TimeTick = 0;
		  
void SysTick_Handler(void)					  //ϵͳ��ʱ���жϷ�����
{
	TimeTick++;
}

void delay_ms(uint32_t ms) /* ע�⣺����Ĳ������ȡ699������ᳬ��24λ������ֵ */
{
	SysTick->LOAD =	(((24000)*ms)-1);	  //�����ؼ�������дֵ
	SysTick->VAL   =	 0;					  //����������
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //����������,�����������ж�
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	
}

void delay_us(uint32_t us)
{
	SysTick->LOAD =	(((24)*us)-1);	  //�����ؼ�������дֵ
	SysTick->VAL   =	 0;					  //����������
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //����������,�����������ж�
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	
}

int main()
{

  uint8_t temp,i;
	uint8_t buf[6];
	
	
	UART_Init(9600); // ��ʼ������	
	I2C_Init(); // ��ʼ��I2C 
	if(AT24C16_Check()==0)	 // �����⵽��AT24C16
	{
	  UART_send("�Ҽ�⵽��AT24C16!!", 19);//���ڷ����ַ�������
		UART_send_byte('\n');
	}
	else   // ���û�м�⵽AT24C16
	{
		UART_send("��û�м�⵽AT24C16!! ", 24);//���ڷ����ַ�������
	}
	


	
	/*  ----  ���Զ�д���ֽ����ݺ��� ----   */
	AT24C16_WriteOneByte(0X0030,5);// ��AT24C16 0X0766��ַд��һ���ֽ����ݣ�5
	temp = 0x00;  // temp ����
	temp = AT24C16_ReadOneByte(0X0030);	 // ��AT24C16 0X0766��ַ����һ���ֽ����ݣ�������temp
	if(temp == 5)		  // ���temp = 5 ,˵����ȡ��д�붼�ɹ�
	{
		temp = '0' + temp;
		UART_send("���ղ�д��ȥ������: ", 20);//���ڷ����ַ�������
		UART_send_byte(temp);// �Ѷ��������ݷ��ص��Դ���
		UART_send_byte('\n');// �Ѷ��������ݷ��ص��Դ���
	}
	else	 // ���temp != 5,˵����ȡ��д��ʧ��
	{
		UART_send("ʧ�ܣ�����", 29);//���ڷ����ַ�������
		UART_send_byte('\n');// �Ѷ��������ݷ��ص��Դ���
	}
	

	
	
	/*  ----  ���Զ�д���ֽ����ݺ��� ----   */
	for(i = 0; i < 6; i++)			
	{
		buf[i] = i;    // �����鸳ֵ
	}
	AT24C16_Write(0x0010, buf,6);	   // ��AT24C16 0X0010��ʼ�ĵ�ַд��6���ֽ�����
	
	for(i = 0; i < 6; i++)
	{
		buf[i] = 0;    // ����������
	}
	AT24C16_Read(0x0010,buf,6);		  // ��AT24C16 0x0010��ʼ�ĵ�ַ����6���ֽ�����
	UART_send("���ղ�д��ȥ������: ", 20);//���ڷ����ַ�������
	
	
	for(i = 0; i < 6; i++)
	{
		buf[i] = '0' + buf[i];
		UART_send_byte(buf[i]);// �Ѷ��������ݷ��ص��Դ���
		UART_send_byte(' ');// �Ѷ��������ݷ��ص��Դ���
	}

  UART_send_byte('\n');// �Ѷ��������ݷ��ص��Դ���
	while(1)
	{
		;
	}


}
