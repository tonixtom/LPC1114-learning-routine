/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: system_LPC11xx.h
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : CMSIS Cortex-M0核外围访问层头文件，用于NXP LPC11xx系列设备
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#ifndef __SYSTEM_LPC11xx_H
#define __SYSTEM_LPC11xx_H

/* 向量表基地址      ---------------------------------------------------------*/
#define NVIC_VectTab_RAM             (0x10000000)
#define NVIC_VectTab_FLASH           (0x00000000)

extern uint32_t ClockSource;
extern uint32_t SystemFrequency;    /*!< 系统时钟频率 (内核时钟)  */
extern uint32_t SystemAHBFrequency;
extern void SystemInit (void);
#endif
/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
