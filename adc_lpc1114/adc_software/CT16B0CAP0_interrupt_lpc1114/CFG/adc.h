#ifndef __NXP_ADC_H
#define __NXP_ADC_H

#define  Vref   3300

extern void ADC_Init(uint8_t Channel);	   // 初始化ADC口（AD0）
extern uint32_t ADC_Read(uint8_t Channel);   // 读取电压值（AD0）

#endif



