////////////////////////////////////////////////////////////////////////////////
//  Company: 成都锐创智能科技 Ruichuang Smart Technology                      //
//     shop: http://ruicstech.taobao.com                                      // 
//  Engineer:  Youzhiyu                                                       //
//  QQ      :  4016682  													  //
//  旺旺    ： yzyseal                                                        //
//  Target Device: LPC1114                                                    //
//  Tool versions: MDK4.12                                                    //
//  Create Date  :   2011-09-06 10:09                                         //
//  Description  :   LPC1114 定时器演示                                       //
////////////////////////////////////////////////////////////////////////////////
// 	   Copyright (C) 2011-2012  Youzhiyu   All rights reserved                //
//----------------------------------------------------------------------------//
////////////////////////////////////////////////////////////////////////////////


#include "nxplpc11xx.h"
#include "ct.h"

void KEY_Init(void)
{
	SYSCON->SYSAHBCLKCTRL |= (1<<16); //使能IOCON时钟(bit16)
	IOCON->PIO1_0 = 0XD1; //把PIN33设置为P1.0脚
	IOCON->PIO1_1 = 0XD1; //把PIN34设置为P1.1脚
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16);//禁能IOCON时钟(bit16)（引脚配置完成后关闭该时钟）

	//把P1.0和P1.1设置为输入
	GPIO1->DIR &= ~(1<<0);
	GPIO1->DIR &= ~(1<<1);	
}

int main()
{
	uint8 duty=50;
	uint32 cycle_us=10000;
	
	SysCLK_config(); // 系统时钟初始化
	KEY_Init();      // 初始化MINI LPC1114开发板上的按键
	

	TIM32B0_init();	 // 使能定时器TIM32B0
	TIM32B0_PWM(cycle_us, duty);	 // 在P1.6脚上输出占空比为50%的100Hz脉冲信号

   //在P1.6引脚上输出了100Hz脉冲信号，你可以用示波器观察，小心测试！在开发板的背面有各个引脚的标记，你可以很快的找到它！");
	 //你可以通过按键KEY1和KEY2改变脉冲信号的占空比，KEY1增大占空比，KEY2减小占空比  为duty;


	while(1)
	{
		if((GPIO1->DATA&(1<<0))!=(1<<0))		 // 如果是KEY1被按下
		{
			if(duty<99)
			{
				duty++;
				TMR32B0->MR0 = 48*cycle_us*(100-duty)/100;//设置占空比
				//show duty, 2
			}
			while((GPIO1->DATA&(1<<0))!=(1<<0));	 // 等待按键释放
		}
		else if((GPIO1->DATA&(1<<1))!=(1<<1))	 // 如果是KEY2被按下
		{
			if(duty>1)
			{
				duty--;
				TMR32B0->MR0 = 48*cycle_us*(100-duty)/100;//设置占空比
				//show duty, 2
			}
			while((GPIO1->DATA&(1<<1))!=(1<<1));	 // 等待按键释放
		}
	}
}




