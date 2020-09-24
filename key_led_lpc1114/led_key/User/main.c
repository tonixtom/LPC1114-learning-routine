/**************************************************************************************/

/* 名称：按键控制LED实验                                          */
/* 效果：按下按键1，LED1亮，释放按键，LED1灭                      */
/*       按下按键2，LED2亮，释放按键，LED2灭                      */
/* 硬件连接：P1.0---KEY1   P1.1---KEY2                            */
/*           P0.3---LED1   P1.10--LED2                            */

/**************************************************************************************/
#include "lpc11xx.h"
#include "stdio.h"
#include "stdlib.h"

/********************** 函数声明 ********************/
__inline void delay_ms(uint32_t a);
int main(void)
{


	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);     // 使能IOCON时钟
	LPC_IOCON->R_PIO1_0 = 0XD1; //把PIN33设置为P1.0脚
	LPC_IOCON->R_PIO1_1 = 0XD1; //把PIN34设置为P1.1脚
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);     // 使能IOCON时钟（引脚配置完成后关闭该时钟）

	//把P1.0和P1.1设置为输入
	LPC_GPIO1->DIR &= ~(1<<0);
	LPC_GPIO1->DIR &= ~(1<<1);	
	//把P0.3和P1.10引脚设置为输出
	LPC_GPIO0->DIR |= (1<<3);
	LPC_GPIO1->DIR |= (1<<10);
	//开LED1  关LED2
 	LPC_GPIO0->DATA &= ~(1<<3);
	LPC_GPIO1->DATA |= (1<<10); 



	while(1)
	{
		if((LPC_GPIO1->DATA&(1<<0))!=(1<<0))		 // 如果是KEY1被按下
		{
			delay_ms(10);				  	//延时消抖
			if((LPC_GPIO1->DATA&(1<<0))!=(1<<0))//如果还是按下状态
			LPC_GPIO0->DATA |= (1<<3);				 // 关LED1
			while((LPC_GPIO1->DATA&(1<<0))!=(1<<0));	 // 等待按键释放
			LPC_GPIO0->DATA &= ~(1<<3);				 // 开LED1
		}
		else if((LPC_GPIO1->DATA&(1<<1))!=(1<<1))	 // 如果是KEY2被按下
		{
			LPC_GPIO1->DATA &= ~(1<<10);			 // 开LED2
			while((LPC_GPIO1->DATA&(1<<1))!=(1<<1));	 // 等待按键释放
			LPC_GPIO1->DATA |= (1<<10);				 // 关LED2
		}
	}
}
/********************** 函数定义 ********************/
/****************************************************
*名  称：	延时函数    							*
*参  数：   延时时间								*
*备  注：	内联函数    							*
*****************************************************/
__inline void delay_ms(uint32_t a)    //1ms延时函数
{                           
uint32_t i;
while( --a != 0){
   for(i = 0; i<5500; i++);
}             
}
