#ifndef __NXP_ADC_H
#define __NXP_ADC_H

#define  Vref   3300

extern void ADC_Init(uint8_t Channel);	   // ��ʼ��ADC�ڣ�AD0��
extern uint32_t ADC_Read(uint8_t Channel);   // ��ȡ��ѹֵ��AD0��

#endif



