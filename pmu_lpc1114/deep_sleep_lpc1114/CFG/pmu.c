#include "lpc11xx.h"
#include "pmu.h"

void Entry_Deep_Sleep(void)
{
	// step1
	LPC_PMU->PCON &= ~(1<<1);	// DPDEN=0; ѡ��sleep/deep-sleepģʽ
	// step2     ��ʱ��Դ����
	LPC_SYSCON->MAINCLKSEL    = 0x0;                /* Select IRC  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
	// step3
	LPC_SYSCON->PDAWAKECFG &= ~(1<<5);  // SYSOSC_PD ���Ѻ�ϵͳ�����ϵ�
	LPC_SYSCON->PDAWAKECFG &= ~(1<<7);	 // SYSPLL_PD ���Ѻ�PLL�ϵ�
	// step4
	LPC_SYSCON->STARTRSRP0CLR |= (1<<7); // RESET P0.7
	LPC_SYSCON->STARTAPRP0 &= ~(1<<7);  // ����P0.7��Ϊ��������  ��P0.0~P0.11 and P1.0��������Ϊ�������ţ�
	LPC_SYSCON->STARTERP0 |= (1<<7); // Enable P0.7����Ϊ��������	
	NVIC_EnableIRQ(WAKEUP7_IRQn);
	// step5
	LPC_SYSCON->SYSAHBCLKCTRL = 0x01f; // �ر���������ģ��
	// step6
	SCB->SCR |= (1<<2);      // SLEEPDEEP=1; ѡ��deep_sleepģʽ
	// step7 ����WFIָ��������˯��ģʽ
	 __wfi();				          // дwfiָ�����͹���ģʽ
}


void WAKEUP_IRQHandler(void)
{
	// ʱ������
	LPC_SYSCON->MAINCLKSEL    = 0x3;                /* Select PLL Clock Output  */
  LPC_SYSCON->MAINCLKUEN    = 0x01;               /* Update MCLK Clock Source */
  LPC_SYSCON->MAINCLKUEN    = 0x00;               /* Toggle Update Register   */
  LPC_SYSCON->MAINCLKUEN    = 0x01;
  while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       /* Wait Until Updated       */
	// �廽�ѱ�־
	LPC_SYSCON->STARTRSRP0CLR |= (1<<7); // RESET P0.7
	LPC_PMU->PCON &= ~(1<<8); // SLEEPFLAG��־λ����	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6); // GPIO�ϵ�
}









