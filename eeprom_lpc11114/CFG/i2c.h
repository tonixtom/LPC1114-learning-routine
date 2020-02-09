#ifndef __I2C_H 
#define __I2C_H
#include "lpc11xx.h"

/* I2C 控制寄存器 */  
#define I2CONSET_AA			(1<<2)	 // 是否产生应答信号允许位，即是否设置为从机模式
#define I2CONSET_SI			(1<<3)	 // I2C中断标志位
#define I2CONSET_STO		(1<<4)	 // 停止标志位
#define I2CONSET_STA		(1<<5)	 // 开始标志位
#define I2CONSET_I2EN		(1<<6)	 // I2C接口允许位
/* I2C “清控制寄存器位”寄存器 */
#define I2CONCLR_AAC		(1<<2)   // 清应答信号允许位
#define I2CONCLR_SIC		(1<<3)	 // 清I2C中断标志位
#define I2CONCLR_STAC		(1<<5)	 // 清开始标志位
#define I2CONCLR_I2ENC		(1<<6)	 // 清I2C接口允许位

extern void I2C_Init(uint8_t Mode);	// 初始化LPC1114 I2C模块
extern void I2C_Send_Byte(uint8_t sebyte);  // I2C发送一字节数据 
extern uint8_t I2C_Recieve_Byte(void);   // I2C接收一字节数据
extern void I2C_Stop(void);	   // 发送停止信号 
extern uint8_t I2C_Send_Ctrl(uint8_t CtrlAndAddr); // I2C发送命令数据  

#endif



