/************************************************************************************** 
*   日期    ：2013年11月6日  
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：12Mhz(主频48M)
*   功能    ：学习使用AT24C02存储数据
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
//  Description:   模拟I2C时序与AT24C16通信                                   //
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "i2c.h"
#include "at24c16.h"

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

void delay_us(uint32_t us)
{
	SysTick->LOAD =	(((24)*us)-1);	  //往重载计数器里写值
	SysTick->VAL   =	 0;					  //计数器清零
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //开启计数器,开启计数器中断
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	
}

int main()
{

  uint8_t temp,i;
	uint8_t buf[6];
	
	
	UART_Init(9600); // 初始化串口	
	I2C_Init(); // 初始化I2C 
	if(AT24C16_Check()==0)	 // 如果检测到了AT24C16
	{
	  UART_send("我检测到了AT24C16!!", 19);//串口发送字符串数组
		UART_send_byte('\n');
	}
	else   // 如果没有检测到AT24C16
	{
		UART_send("我没有检测到AT24C16!! ", 24);//串口发送字符串数组
	}
	


	
	/*  ----  测试读写单字节数据函数 ----   */
	AT24C16_WriteOneByte(0X0030,5);// 给AT24C16 0X0766地址写入一个字节数据：5
	temp = 0x00;  // temp 清零
	temp = AT24C16_ReadOneByte(0X0030);	 // 从AT24C16 0X0766地址读出一个字节数据，并给了temp
	if(temp == 5)		  // 如果temp = 5 ,说明读取和写入都成功
	{
		temp = '0' + temp;
		UART_send("您刚才写进去的数是: ", 20);//串口发送字符串数组
		UART_send_byte(temp);// 把读出的数据返回电脑串口
		UART_send_byte('\n');// 把读出的数据返回电脑串口
	}
	else	 // 如果temp != 5,说明读取或写入失败
	{
		UART_send("失败！！！", 29);//串口发送字符串数组
		UART_send_byte('\n');// 把读出的数据返回电脑串口
	}
	

	
	
	/*  ----  测试读写多字节数据函数 ----   */
	for(i = 0; i < 6; i++)			
	{
		buf[i] = i;    // 给数组赋值
	}
	AT24C16_Write(0x0010, buf,6);	   // 给AT24C16 0X0010开始的地址写入6个字节数据
	
	for(i = 0; i < 6; i++)
	{
		buf[i] = 0;    // 给数组清零
	}
	AT24C16_Read(0x0010,buf,6);		  // 从AT24C16 0x0010开始的地址读出6个字节数据
	UART_send("您刚才写进去的数是: ", 20);//串口发送字符串数组
	
	
	for(i = 0; i < 6; i++)
	{
		buf[i] = '0' + buf[i];
		UART_send_byte(buf[i]);// 把读出的数据返回电脑串口
		UART_send_byte(' ');// 把读出的数据返回电脑串口
	}

  UART_send_byte('\n');// 把读出的数据返回电脑串口
	while(1)
	{
		;
	}


}
