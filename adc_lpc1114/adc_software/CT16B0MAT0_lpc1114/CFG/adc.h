#ifndef __NXP_ADC_H
#define __NXP_ADC_H

#define  Vref   3300

extern void ADC_Init(uint8_t Channel);	   // ��ʼ��ADC��
extern uint32_t ADC_Read(uint8_t Channel);   // ��ȡ��ѹֵ
extern void TIM16B0_MAT_Init(uint16_t cycle_ms); // ��ʱ��TIM16B0MAT0ƥ�䴥��ADCת��

#endif



