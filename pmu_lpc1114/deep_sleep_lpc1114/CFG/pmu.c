#include "lpc11xx.h"
#include "pmu.h"

void Entry_Deep_Sleep(void)
{
	// step1
	LPC_PMU->PCON &= ~(1<<1);	// DPDEN=0; 选择sleep/deep-sleep模式
	// step2     主时钟源更新
	LPC_SYSCON->MAINCLKSEL    = 0x0;                /* Select IRC  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
	// step3
	LPC_SYSCON->PDAWAKECFG &= ~(1<<5);  // SYSOSC_PD 唤醒后系统振荡器上电
	LPC_SYSCON->PDAWAKECFG &= ~(1<<7);	 // SYSPLL_PD 唤醒后PLL上电
	// step4
	LPC_SYSCON->STARTRSRP0CLR |= (1<<7); // RESET P0.7
	LPC_SYSCON->STARTAPRP0 &= ~(1<<7);  // 配置P0.7脚为唤醒引脚  （P0.0~P0.11 and P1.0都可以作为唤醒引脚）
	LPC_SYSCON->STARTERP0 |= (1<<7); // Enable P0.7脚作为唤醒引脚	
	NVIC_EnableIRQ(WAKEUP7_IRQn);
	// step5
	LPC_SYSCON->SYSAHBCLKCTRL = 0x01f; // 关闭所有外设模块
	// step6
	SCB->SCR |= (1<<2);      // SLEEPDEEP=1; 选择deep_sleep模式
	// step7 调用WFI指令，进入深度睡眠模式
	 __wfi();				          // 写wfi指令进入低功耗模式
}


void WAKEUP_IRQHandler(void)
{
	// 时钟配置
	LPC_SYSCON->MAINCLKSEL    = 0x3;                /* Select PLL Clock Output  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
	// 清唤醒标志
	LPC_SYSCON->STARTRSRP0CLR |= (1<<7); // RESET P0.7
	LPC_PMU->PCON &= ~(1<<8); // SLEEPFLAG标志位清零	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); // GPIO上电
}









