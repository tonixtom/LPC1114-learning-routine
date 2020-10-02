#include "lpc11xx.h"
#include "timer.h"


void T16B0_init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//ʹ��TIM16B0ʱ��
	LPC_TMR16B0->TCR = 0x02;		//��λ��ʱ����bit1��д1��λ��
	LPC_TMR16B0->IR  = 0x01;		//MR0�жϸ�λ,�����жϣ�bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0��
	LPC_TMR16B0->MCR = 0x04;		//MR0�жϲ���ʱֹͣTC��PC����ʹTCR[0]=0, ֹͣ��ʱ������
}

void T16B0_delay_ms(uint16_t ms)
{
	LPC_TMR16B0->TCR = 0x02;		//��λ��ʱ����bit1��д1��λ��
	LPC_TMR16B0->PR  = SystemCoreClock/1000-1;		// 1����TC+1
	LPC_TMR16B0->MR0 = ms;	// ע�⣺MR0��16λ�Ĵ�����ֵ��Ҫ����65535
	LPC_TMR16B0->TCR = 0x01;		//������ʱ����TCR[0]=1;	  
	while (LPC_TMR16B0->TCR & 0x01);//�ȴ���ʱ����ʱʱ�䵽
}

void T16B0_delay_us(uint16_t us)
{
	LPC_TMR16B0->TCR = 0x02;		//��λ��ʱ����bit1��д1��λ��
	LPC_TMR16B0->PR  = SystemCoreClock/1000000-1;		// 1΢��TC+1
	LPC_TMR16B0->MR0 = us;	// ע�⣺MR0��16λ�Ĵ�����ֵ��Ҫ����65535
	LPC_TMR16B0->TCR = 0x01;		//������ʱ����TCR[0]=1;	  
	while (LPC_TMR16B0->TCR & 0x01);//�ȴ���ʱ����ʱʱ�䵽
}

void T16B0_cnt_init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);  // ʹ��IOCONʱ��
	LPC_IOCON->PIO0_2 &= ~0x07;
	LPC_IOCON->PIO0_2 |= 0x02;	/* CT16B0 CAP0 */
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  // ����IOCONʱ��
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//ʹ��TIM16B0ʱ��
	LPC_TMR16B0->TCR = 0x02;		//��λ��ʱ����bit1��д1��λ��
	LPC_TMR16B0->CTCR = 0x02; // ������ģʽ ����CT16B0_CAP0�½��ؼ��� ����P0.2��
	LPC_TMR16B0->TCR = 0x01;		//������ʱ����TCR[0]=1;	  
}

void T16B0_CAP_Init(void) 
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);  // ʹ��IOCONʱ��
	LPC_IOCON->PIO0_2 &= ~0x07;
	LPC_IOCON->PIO0_2 |= 0x02;	/* CT16B0 CAP0 */
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);  // ����IOCONʱ��
	LPC_SYSCON->SYSAHBCLKCTRL |= (0X1<<7);	// ʹ��TIM16B0ʱ��
	
	LPC_TMR16B0->TCR = 0x02;		//��λ��ʱ����bit1��д1��λ��
	LPC_TMR16B0->PR  = SystemCoreClock/100000-1;		//ʹ(SystemCoreClock/100000-1)��PCLK��TC+1����10΢��TC+1
	LPC_TMR16B0->IR  = 0x1F;		//CAP0�жϸ�λ,�����жϣ�bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0��
	LPC_TMR16B0->CCR = 0x06;	 // �½����ж�
	LPC_TMR16B0->MR0 = 0XFFFF; // ƥ��ֵ
	LPC_TMR16B0->MCR = 0X01; // ��MR0ƥ������ж�
	LPC_TMR16B0->TCR = 0x01;
	NVIC_EnableIRQ(TIMER_16_0_IRQn);	// ʹ��CT16B0�ж�
}






