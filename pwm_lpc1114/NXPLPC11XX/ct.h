#ifndef __NXPLPC11xx_CT_H__
#define __NXPLPC11xx_CT_H__

void TIM32B0_init(void);
void TIM32B0_INT_init(uint32 ms);
void TIM32B0_delay_ms(uint32 ms);
void TIM32B0_delay_us(uint32 us);
void TIM32B0_Square(uint32 cycle_us);
void TIM32B0_PWM(uint32 cycle_us, uint8 duty);
void TIM32B0_CAP0(void);
void TIMER32_0_IRQHandler(void);

#endif





