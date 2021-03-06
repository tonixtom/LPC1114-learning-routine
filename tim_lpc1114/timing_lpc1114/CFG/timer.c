#include "lpc11xx.h"
#include "timer.h"


void T16B0_init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//使能TIM16B0时钟
	LPC_TMR16B0->IR  = 0x01;		//MR0中断复位,即清中断（bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0）
	LPC_TMR16B0->MCR = 0x04;		//MR0中断产生时停止TC和PC，并使TCR[0]=0, 停止定时器工作
}

void T16B0_delay_ms(uint16_t ms)
{
	LPC_TMR16B0->TCR = 0x02;		//复位定时器（bit1：写1复位）
	LPC_TMR16B0->PR  = SystemCoreClock/1000-1;		// 1毫秒TC+1
	LPC_TMR16B0->MR0 = ms;	// 注意：MR0是16位寄存器，值不要超过65535
	LPC_TMR16B0->TCR = 0x01;		//启动定时器：TCR[0]=1;	  
	LPC_TMR16B0->TCR = 0x01;		//启动定时器：TCR[0]=1;	 
	while (LPC_TMR16B0->TCR & 0x01);//等待定时器计时时间到
}

void T16B0_delay_us(uint16_t us)
{
	LPC_TMR16B0->TCR = 0x02;		//复位定时器（bit1：写1复位）
	LPC_TMR16B0->PR  = SystemCoreClock/1000000-1;		// 1微秒TC+1
	LPC_TMR16B0->MR0 = us;	// 注意：MR0是16位寄存器，值不要超过65535
	LPC_TMR16B0->TCR = 0x01;		//启动定时器：TCR[0]=1;	  
	while (LPC_TMR16B0->TCR & 0x01);//等待定时器计时时间到
}






