#include "lpc11xx.h"
#include "pmu.h"

void Entry_Deep_PD(void)
{
	// step1
	LPC_PMU->PCON |= (1<<1);	// DPDEN=1; ѡ��deep_power_downģʽ
	// step2 (��һ�����Ա�����Ҫ��������ݣ�һ����4��32λ��ͨ�üĴ�������)
// 	LPC_PMU->GPREG0 = 0x0011;
// 	LPC_PMU->GPREG1 = ;
// 	LPC_PMU->GPREG2 = ;
// 	LPC_PMU->GPREG3 = ;
	// step3
	SCB->SCR |= (1<<2);      // SLEEPDEEP=1;
	// step4
	LPC_SYSCON->PDRUNCFG &= ~(0X3); // ȷ��IRCOUT_PD��IRC_PD Ϊ0
	// setp5
  __wfi();				          // дwfiָ�����͹���ģʽ
}














