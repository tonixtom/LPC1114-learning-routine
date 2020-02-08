/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* �ļ���: gpio.h
* ����  : Wuhan R&D Center, Embest
* ����  : 01/18/2010
* ����  : NXP LPC13xx ϵ�д����� GPIO ͷ�ļ�
*******************************************************************************
*******************************************************************************
* ��ʷ:
* 01/18/2010		 : V1.0		   ��ʼ�汾
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#ifndef __GPIO_H 
#define __GPIO_H

#define PORT0		0
#define PORT1		1
#define PORT2		2
#define PORT3		3

void GPIO_IRQHandler(void);
void GPIOInit( void );
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir );
void GPIOSetValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal );
void GPIOSetInterrupt( uint32_t portNum, uint32_t bitPosi, uint32_t sense,
		uint32_t single, uint32_t event );
void GPIOIntEnable( uint32_t portNum, uint32_t bitPosi );
void GPIOIntDisable( uint32_t portNum, uint32_t bitPosi );
uint32_t GPIOIntStatus( uint32_t portNum, uint32_t bitPosi );
void GPIOIntClear( uint32_t portNum, uint32_t bitPosi );

#endif /* end __GPIO_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****�ļ�����*******/
