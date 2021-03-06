#include "lpc11xx.h"
#include "wdt.h"
#include "uart.h"

/******************************************/
/* 函数功能：使能窗口看门狗功能           */
/******************************************/
void WDT_Window_Enable()
{ 	
	LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    // 看门狗振荡器时钟上电（bit6）
	LPC_SYSCON->WDTOSCCTRL = (0x1<<5); // DIVSEL=0 FREQSEL=1  WDT_OSC_CLK=300KHz
  LPC_SYSCON->WDTCLKSEL = 0x2;        // 选择看门狗时钟源
  LPC_SYSCON->WDTCLKUEN = 0x01;          // 更新时钟源
  LPC_SYSCON->WDTCLKUEN = 0x00;          // 先写0，再写1达到更新目的
  LPC_SYSCON->WDTCLKUEN = 0x01;
  while ( !(LPC_SYSCON->WDTCLKUEN & 0x01) );  // 等待更新成功
  LPC_SYSCON->WDTCLKDIV = 3;            // 设置看门狗分频值为3，所以现在的看门狗时钟为100K
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<15);// 允许WDT时钟
  LPC_WDT->TC = 25000;		// 给看门狗定时器赋值，定时时间大约1秒(这是在wdt_clk=100KHz时)
	LPC_WDT->WARNINT = 1023; // 当看门狗定时器倒数到1023时，产生中断
	LPC_WDT->WINDOW = 4600; // 最大喂狗值
	LPC_WDT->MOD |= 0x03;		// 写值0x03：不喂狗产生复位  
 	LPC_WDT->FEED = 0xAA;		// 喂看门狗，开启
  LPC_WDT->FEED = 0x55;    
}


/******************************************/
/* 函数功能：喂狗                         */
/******************************************/
void WDTFeed(void)
{
  LPC_WDT->FEED = 0xAA;		// 喂狗
  LPC_WDT->FEED = 0x55;
}




