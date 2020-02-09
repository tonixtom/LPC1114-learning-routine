/************************************************************************************** 
*   日期    ：2013年11月6日  
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学习使用AT24C02存储数据
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "i2c.h"
#include "at24c02.h"

int main()
{
	uint8_t rece_data;
	
	UART_Init(9600); // 初始化串口
	I2C_Init(0); // 初始化I2C口
	
	while(1)
	{
		rece_data = UART_recive();// 等待串口发来的数据
		AT24C02_WriteOneByte(0x00, rece_data);// 把串口发来的数据写入AT24C02地址0x00处
		rece_data = 0;// rece_data清零
		rece_data = AT24C02_ReadOneByte(0x00);// 读出AT24C02地址0x00处数据，赋予rece_data
		UART_send_byte(rece_data);// 把读出的数据返回电脑串口
	}
}









