/************************************************************************************** 
*   ����    ��2013��11��6��  
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧϰʹ��AT24C02�洢����
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "i2c.h"
#include "at24c02.h"

int main()
{
	uint8_t rece_data;
	
	UART_Init(9600); // ��ʼ������
	I2C_Init(0); // ��ʼ��I2C��
	
	while(1)
	{
		rece_data = UART_recive();// �ȴ����ڷ���������
		AT24C02_WriteOneByte(0x00, rece_data);// �Ѵ��ڷ���������д��AT24C02��ַ0x00��
		rece_data = 0;// rece_data����
		rece_data = AT24C02_ReadOneByte(0x00);// ����AT24C02��ַ0x00�����ݣ�����rece_data
		UART_send_byte(rece_data);// �Ѷ��������ݷ��ص��Դ���
	}
}









