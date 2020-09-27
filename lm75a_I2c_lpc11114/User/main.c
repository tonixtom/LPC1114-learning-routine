/************************************************************************************** 
*   日期    ：2013年11月6日  
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：12Mhz(主频48M)
*   功能    ：学习使用AT24C02存储数据
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
//  Description:   模拟I2C时序与LM75A通信                                   //
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "i2c.h"
#include "stdio.h"
#include "stdlib.h"
#include "lm75a.h"


static volatile uint32_t TimeTick = 0;
		  
void SysTick_Handler(void)					  //系统定时器中断服务函数
{
	TimeTick++;
}

void delay_ms(uint32_t ms) /* 注意：这里的参数最大取699，否则会超出24位计数器值 */
{
	SysTick->LOAD =	(((24000)*ms)-1);	  //往重载计数器里写值
	SysTick->VAL   =	 0;					  //计数器清零
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //开启计数器,开启计数器中断
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	
}


/*******************************************************************************
* Function Name  : I2C_LM75_Read
* Description    : Reads Temperature data from the LM75.
* Input          : None
* Output         : 0xFFFF -- Error
*					0x0000 ~ 0x01FF -- Valid data
*					Temp	Binary 					Hex
*					+125	0111 1101 0xxx xxxx 	0FAh
*					+25		0001 1001 0xxx xxxx 	032h
*					+0.5	0000 0000 1xxx xxxx 	001h
*					0		0000 0000 0xxx xxxx		000h
*					-0.5	1111 1111 1xxx xxxx 	1FFh
*					-25		1110 0111 0xxx xxxx 	1CEh
*					-55		1100 1001 0xxx xxxx 	192h
* Return         : None
*******************************************************************************/


float I2C_LM75A_read(void)
{
	uint8_t TempH,TempL;
	uint16_t data;
	float temp;
	delay_ms(500);	

	TempH = LM75A_ReadOneByte(0x00);
	delay_ms(500);
	TempL = LM75A_ReadOneByte(0x01);

	data=((uint16_t)TempH << 8) | TempL ;
	data=(data>>5);
	temp = 0.125*data;
	return temp;

}


int main()
{

	char str[8]={'0'};

	float temp=0;



	UART_Init(9600); // 初始化串口	
	I2C_Init(1); // 初始化I2C 快速模式
	
	if(LM75A_Check()==0)	 // 如果检测到了AT24C16
	{
		UART_send("我检测到了LM75A  !!", 20);//串口发送字符串数组
		UART_send_byte('\n');
	}
	else   // 如果没有检测到AT24C16
	{
		UART_send("我没有检测到LM75a  !! ", 23);//串口发送字符串数组
	}
	

	while(1)
	{
		UART_send("begin: ", 8);//串口发送字符串数组
		
		temp = I2C_LM75A_read();
		sprintf(str,"%8.3f",temp);    //小数点后3位
		
		UART_send(str, 8);//串口发送字符串数组	
		UART_send_byte('\n');// 把读出的数据返回电脑串口

	}
		
}
