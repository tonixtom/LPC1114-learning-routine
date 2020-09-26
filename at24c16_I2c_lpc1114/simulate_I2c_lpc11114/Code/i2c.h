#ifndef __MONII2C_H
#define __MONII2C_H
#include "lpc11xx.h"


void I2C_Init(void);                //��ʼ��I2C��IO��				 
void I2C_Start(void);				//����I2C��ʼ�ź�
void I2C_Stop(void);	  			//����I2Cֹͣ�ź�
uint8_t I2C_Wait_Ack(void); 			//I2C�ȴ�ACK�ź�
void I2C_Send_Byte(uint8_t wbyte);	//I2C����һ���ֽ�
uint8_t I2C_Read_Byte(void);          //I2C��ȡһ���ֽ�
extern void delay_ms(uint32_t ms); /* ע�⣺����Ĳ������ȡ699������ᳬ��24λ������ֵ */
extern void delay_us(uint32_t us);

	  
#endif

