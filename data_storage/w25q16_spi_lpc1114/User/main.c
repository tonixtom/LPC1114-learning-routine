/************************************************************************************** 
*   日期    ：2013年11月6日  
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学习使用W25Q16存储数据
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "ssp.h"
#include "w25q16.h"
#include "stdio.h"
#include "stdlib.h"

// 注意：W25Q16可以一次写入一个字节，但是写入字节的位置必须先擦除才能写进去
//       每次擦除至少要擦除4K的字节，不能一次擦除一个字节
//       W25Q16在RATION LPC1114 V3.0开发板上被用作了字库存储器，占用了前面的部分。
//       为了避免做实验的时候损坏字库，所以这里在W25Q16的最后一个扇区(511)做实验




int main()
{
	uint8_t rece_data[1];
	uint32_t flash_addr;

	
	char str[4]={'0'};
	
	UART_init(9600);
	W25Q16_Init();

	flash_addr = 0x1FF000;// 从W25Q16第511个扇区第一个字节开始写入数据
	 
	
	
	UART_send("begin", 10);//串口发送字符串数组
	UART_send_byte('\n'); //串口发送换行符字节
	
	W25Q16_Erase_Sector(511);// 擦除W25Q16第511个扇区数据
	

	
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



