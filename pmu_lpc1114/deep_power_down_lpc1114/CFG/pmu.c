#include "lpc11xx.h"
#include "pmu.h"

void Entry_Deep_PD(void)
{
	// step1
	LPC_PMU->PCON |= (1<<1);	// DPDEN=1; 选择deep_power_down模式
	// step2 (这一步可以保存需要保存的数据，一共有4个32位的通用寄存器可用)
// 	LPC_PMU->GPREG0 = 0x0011;
// 	LPC_PMU->GPREG1 = ;
// 	LPC_PMU->GPREG2 = ;
// 	LPC_PMU->GPREG3 = ;
	// step3
	SCB->SCR |= (1<<2);      // SLEEPDEEP=1;
	// step4
	LPC_SYSCON->PDRUNCFG &= ~(0X3); // 确保IRCOUT_PD和IRC_PD 为0
	// setp5
  __wfi();				          // 写wfi指令进入低功耗模式
}














