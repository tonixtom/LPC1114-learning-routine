#include "nxplpc11xx.h"
#include "ct.h"

/****************************/
/* 函数功能：初始化TIM32B0  */
/****************************/
void TIM32B0_init(void) 
{
	SYSCON->SYSAHBCLKCTRL |= (1<<9);	//使能TIM32B0时钟
}

/********************************************************/
/* 函数功能：初始化TIM32B0                              */
/* 入口参数：ms ：定时毫秒值                            */
/* 说    明：当定时时间到了以后，会进入TIM32B0中断函数  */
/********************************************************/
void TIM32B0_INT_init(uint32 ms)
{
	SYSCON->SYSAHBCLKCTRL |= (1<<9);	//使能TIM32B0时钟
	TMR32B0->TCR = 0x02;		//复位定时器（bit1：写1复位）
	TMR32B0->PR  = 0x00;		//把预分频寄存器置0，使PC+1，TC+1
	TMR32B0->MR0 = ms * 48000;	//在48Mhz下工作的值，其它请修改
	TMR32B0->IR  = 0x01;		//MR0中断复位,即清中断（bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0）
	TMR32B0->MCR = 0x05;		//MR0中断产生时停止TC和PC，并使TCR[0]=0, 停止定时器工作，并产生中断
	TMR32B0->TCR = 0x01;		//启动定时器：TCR[0]=1;
	NVIC_EnableIRQ(TIMER_32_0_IRQn);   // 使能TIM32B0中断	
}

/*******************************/
/* 函数功能：TIM32B0毫秒延时   */
/*******************************/ 
void TIM32B0_delay_ms(uint32 ms)
{
	TMR32B0->TCR = 0x02;		//复位定时器（bit1：写1复位）
	TMR32B0->PR  = 0x00;		//把预分频寄存器置0，使PC+1，TC+1
	TMR32B0->MR0 = ms * 48000;	//在48Mhz下工作的值，其它请修改
	TMR32B0->IR  = 0x01;		//MR0中断复位,即清中断（bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0）
	TMR32B0->MCR = 0x04;		//MR0中断产生时停止TC和PC，并使TCR[0]=0, 停止定时器工作
	TMR32B0->TCR = 0x01;		//启动定时器：TCR[0]=1;
	  
	while (TMR32B0->TCR & 0x01);//等待定时器计时时间到
}

/*******************************/
/* 函数功能：TIM32B0微秒延时   */
/*******************************/ 
void TIM32B0_delay_us(uint32 us)
{
	TMR32B0->TCR = 0x02;		//复位定时器（bit1：写1复位）
	TMR32B0->PR  = 0x00;		//把预分频寄存器置0，使PC+1，TC+1
	TMR32B0->MR0 = us * 48;	    //在48Mhz下工作的值，其它请修改
	TMR32B0->IR  = 0x01;		//MR0中断复位（bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0）
	TMR32B0->MCR = 0x04;		//MR0中断产生时停止TC和PC，并使TCR[0]=0, 停止定时器工作
	TMR32B0->TCR = 0x01;		//启动定时器：TCR[0]=1;
	  
	while (TMR32B0->TCR & 0x01);//等待定时器计时时间到
}

/**************************************/
/* 函数功能：MAT0上输出方波信号       */
/* 注    意：这里不是用PWM控制寄存器  */
/**************************************/ 
void TIM32B0_Square(uint32 cycle_us)
{
	SYSCON->SYSAHBCLKCTRL |= (1<<16);  // 使能IOCON时钟
	IOCON->PIO1_6 &= ~0x07;
	IOCON->PIO1_6 |= 0x02;	/* Timer0_32 MAT0 */
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  // 禁能IOCON时钟

	TMR32B0->TCR = 0x02;		  //复位定时器（bit1：写1复位）
	TMR32B0->PR  = 0x00;		  //把预分频寄存器置0，使PC+1，TC+1
	TMR32B0->MR0 = (cycle_us/2) * 48;//在48Mhz下工作的值，其它请修改
	TMR32B0->IR  = 0x01;		  //MR0中断复位（bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0）
	TMR32B0->MCR = 0x02;		  //MR0中断产生时复位TC
	TMR32B0->EMR = 0x31;		  //MR0与PC相等时，MAT0引脚翻转电平
	TMR32B0->TCR = 0x01;		  //启动定时器：TCR[0]=1;
}

/************************************************/
/* 函数功能：MAT0上输出占空比可调脉冲信号       */
/* 注    意：这里用PWM控制寄存器                */
/************************************************/ 
void TIM32B0_PWM(uint32 cycle_us, uint8 duty)
{
	if((duty>=100)&&(duty<=0))return;

	SYSCON->SYSAHBCLKCTRL |= (1<<16);  // 使能IOCON时钟
	IOCON->PIO1_6 &= ~0x07;
	IOCON->PIO1_6 |= 0x02;	      //把P1.6脚设置为MAT0
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  // 禁能IOCON时钟

	TMR32B0->TCR = 0x02;		  //复位定时器（bit1：写1复位）
	TMR32B0->PR  = 0x00;		  //把预分频寄存器置0，使PC+1，TC+1
	TMR32B0->PWMC= 0x01;		  //设置MAT0为PWM输出引脚
	TMR32B0->MCR = 0x02<<9;       //设置MR3匹配时复位TC,也就是把MR3当做周期寄存器
	TMR32B0->MR3 = 48*cycle_us;		  //设置周期
	TMR32B0->MR0 = 48*cycle_us*(100-duty)/100;//设置占空比
	TMR32B0->TCR = 0x01;			  //启动定时器
}

/***************************************/
/* 函数功能：利用CAP0进行计数          */
/***************************************/ 
void TIM32B0_CAP0(void)
{
	SYSCON->SYSAHBCLKCTRL |= (1<<16);  // 使能IOCON时钟
	IOCON->PIO1_5 &= ~0x07;
	IOCON->PIO1_5 |= 0x02;	      //把P1.5脚设置为CAP0
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  // 禁能IOCON时钟

	TMR32B0->CTCR  = 0x01;		  //选择外来信号的上升沿作为TC递增，CAP0捕获
	TMR32B0->TC    = 0x00;        //TC清零
	TMR32B0->TCR   = 0x01;        //启动定时器
}

/***************************************/
/* 函数功能：TIM32B0z中断服务函数      */
/***************************************/ 
void TIMER32_0_IRQHandler(void)
{
	if((TMR32B0->IR & 0x1)==1) // 检测是不是MR0引起的中断
	{
		// 在这里写入你想执行的代码
	}
	TMR32B0->IR = 0x1F; // 清所有中断标志	
}





