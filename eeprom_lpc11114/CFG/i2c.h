#ifndef __I2C_H 
#define __I2C_H
#include "lpc11xx.h"

/* I2C ���ƼĴ��� */  
#define I2CONSET_AA			(1<<2)	 // �Ƿ����Ӧ���ź�����λ�����Ƿ�����Ϊ�ӻ�ģʽ
#define I2CONSET_SI			(1<<3)	 // I2C�жϱ�־λ
#define I2CONSET_STO		(1<<4)	 // ֹͣ��־λ
#define I2CONSET_STA		(1<<5)	 // ��ʼ��־λ
#define I2CONSET_I2EN		(1<<6)	 // I2C�ӿ�����λ
/* I2C ������ƼĴ���λ���Ĵ��� */
#define I2CONCLR_AAC		(1<<2)   // ��Ӧ���ź�����λ
#define I2CONCLR_SIC		(1<<3)	 // ��I2C�жϱ�־λ
#define I2CONCLR_STAC		(1<<5)	 // �忪ʼ��־λ
#define I2CONCLR_I2ENC		(1<<6)	 // ��I2C�ӿ�����λ

extern void I2C_Init(uint8_t Mode);	// ��ʼ��LPC1114 I2Cģ��
extern void I2C_Send_Byte(uint8_t sebyte);  // I2C����һ�ֽ����� 
extern uint8_t I2C_Recieve_Byte(void);   // I2C����һ�ֽ�����
extern void I2C_Stop(void);	   // ����ֹͣ�ź� 
extern uint8_t I2C_Send_Ctrl(uint8_t CtrlAndAddr); // I2C������������  

#endif



