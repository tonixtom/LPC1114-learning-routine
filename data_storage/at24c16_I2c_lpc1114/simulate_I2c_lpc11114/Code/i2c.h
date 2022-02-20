#ifndef __MONII2C_H
#define __MONII2C_H
#include "lpc11xx.h"


void I2C_Init(void);                //初始化I2C的IO口				 
void I2C_Start(void);				//发送I2C开始信号
void I2C_Stop(void);	  			//发送I2C停止信号
uint8_t I2C_Wait_Ack(void); 			//I2C等待ACK信号
void I2C_Send_Byte(uint8_t wbyte);	//I2C发送一个字节
uint8_t I2C_Read_Byte(void);          //I2C读取一个字节
extern void delay_ms(uint32_t ms); /* 注意：这里的参数最大取699，否则会超出24位计数器值 */
extern void delay_us(uint32_t us);

	  
#endif

