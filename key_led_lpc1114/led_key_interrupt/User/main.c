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

#define LED1_ON LPC_GPIO0->DATA &= ~(1<<3)
#define LED1_OFF LPC_GPIO0->DATA |= (1<<3)
#define KEY1_DOWN (LPC_GPIO1->DATA&(1<<0))!=(1<<0)


//GPIO1中断服务函数
void PIOINT1_IRQHandler_keytest(void)
{	
	if((LPC_GPIO1->MIS&0x001) == 0x001)	   // 检测是不是P1.0引脚产生的中断
	{
		LED1_ON;				 // 开LED1
		while(KEY1_DOWN);	 // 等待按键释放
		LED1_OFF;			 // 关LED1	
	}
	else if((LPC_GPIO1->MIS&0x002)==0x002) // 检测是不是P1.1引脚产生的中断
	{
		LPC_GPIO1->DATA &= ~(1<<10);			 // 开LED2
		while((LPC_GPIO1->DATA&(1<<1))!=(1<<1));	 // 等待按键释放
		LPC_GPIO1->DATA |= (1<<10);				 // 关LED2
	}
	LPC_GPIO1->IC = 0x3FF;  // 清除GPIO1上的中断
}

void led_init()
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
 	LPC_GPIO0->DATA |= (1<<3);
	LPC_GPIO1->DATA |= (1<<10);
}

int main(void)
{	
	
	led_init();
		
	//LPC_GPIO1->DATA |= (1<<0);   //P1.0置0
	
	
	LPC_GPIO1->IS |= (1<<0); //选择P1.0为电平触发
	LPC_GPIO1->IEV &= ~(1<<0);//选择P1.0为低电平触发 
	LPC_GPIO1->IE |= (1<<0);  //设置P1.0中断不被屏蔽

	LPC_GPIO1->IS &= ~(1<<1); //选择P1.1为边沿触发
	LPC_GPIO1->IEV &= ~(1<<1);//选择P1.1为下降沿触发
	LPC_GPIO1->IE |= (1<<1);  //设置P1.1中断不被屏蔽
	NVIC_EnableIRQ(EINT1_IRQn);	// 使能GPIO1中断
	
	while(1)
	{
		;
	}
}
