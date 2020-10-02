#include "lpc11xx.h"
#include "pmu.h"

void Entry_Sleep(void)
{
	LPC_PMU->PCON &= ~(1<<1);	// DPDEN=0; 选择sleep/deep-sleep模式
	SCB->SCR &= ~(1<<2);      // SLEEPDEEP=0; 选择sleep模式
  __wfi();				          // 写wfi指令进入低功耗模式
}














