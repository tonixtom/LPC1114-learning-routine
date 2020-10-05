#ifndef __NXP_ADC_H
#define __NXP_ADC_H

#define  Vref   3300

extern void ADC_Init(uint8_t Channel);	   // 初始化ADC口
extern uint32_t ADC_Read(uint8_t Channel);   // 读取电压值
extern void TIM16B0_MAT_Init(uint16_t cycle_ms); // 定时器TIM16B0MAT0匹配触发ADC转换

#endif



