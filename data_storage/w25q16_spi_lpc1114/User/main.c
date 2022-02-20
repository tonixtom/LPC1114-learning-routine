/************************************************************************************** 
*   ����    ��2013��11��6��  
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧϰʹ��W25Q16�洢����
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
*   �Ա���  ��http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "ssp.h"
#include "w25q16.h"
#include "stdio.h"
#include "stdlib.h"

// ע�⣺W25Q16����һ��д��һ���ֽڣ�����д���ֽڵ�λ�ñ����Ȳ�������д��ȥ
//       ÿ�β�������Ҫ����4K���ֽڣ�����һ�β���һ���ֽ�
//       W25Q16��RATION LPC1114 V3.0�������ϱ��������ֿ�洢����ռ����ǰ��Ĳ��֡�
//       Ϊ�˱�����ʵ���ʱ�����ֿ⣬����������W25Q16�����һ������(511)��ʵ��




int main()
{
	uint8_t rece_data[1];
	uint32_t flash_addr;

	
	char str[4]={'0'};
	
	UART_init(9600);
	W25Q16_Init();

	flash_addr = 0x1FF000;// ��W25Q16��511��������һ���ֽڿ�ʼд������
	 
	
	
	UART_send("begin", 10);//���ڷ����ַ�������
	UART_send_byte('\n'); //���ڷ��ͻ��з��ֽ�
	
	W25Q16_Erase_Sector(511);// ����W25Q16��511����������
	

	
	while(1)
	{
		rece_data[0] = UART_recive();

		W25Q16_Write_Page(rece_data, flash_addr, 1); 
		rece_data[0] = 0;

		W25Q16_Read(rece_data, flash_addr, 1);


		sprintf(str, "%4d", rece_data[0]);
		UART_send(str,4);
		UART_send_byte('\n');


		flash_addr++;
	}
}



