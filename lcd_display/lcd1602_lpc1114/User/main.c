#include <LPC11xx.h>
#include "lcd_1602.h"

//******************************定义显示字符串**********************************
uint8_t const str0[]={"  Hello World!"};
uint8_t const str1[]={"LPC1114 duble !"};



//*******************************主函数***********************************
int main(void) 
{
  LPC_GPIO2->DIR = 0xFFF;   		//设置端口2为输出方向
  LPC_GPIO2->DATA = 0xFFF;  	//端口输出高电平
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//使能CT16B0时钟
	
  InitLcd();                                 		//LCD初始化
  ePutstr(0,0,str0);                   		//第一行字符显示
  TIM16B0_delay_ms(5);        		//延时5ms等待显示稳定
  ePutstr(0,1,str1);                   		//第二行字符显示
  while(1)
    {
         ;      //空循环
    }
}

