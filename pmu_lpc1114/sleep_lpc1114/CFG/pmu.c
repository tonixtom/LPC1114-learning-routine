#include "lpc11xx.h"
#include "pmu.h"

void Entry_Sleep(void)
{
	LPC_PMU->PCON &= ~(1<<1);	// DPDEN=0; ѡ��sleep/deep-sleepģʽ
	SCB->SCR &= ~(1<<2);      // SLEEPDEEP=0; ѡ��sleepģʽ
  __wfi();				          // дwfiָ�����͹���ģʽ
}














