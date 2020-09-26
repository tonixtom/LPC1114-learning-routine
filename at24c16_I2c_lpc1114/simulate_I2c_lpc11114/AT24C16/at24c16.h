#ifndef __AT24C16_H
#define __AT24C16_H
#include "lpc11xx.h"  
					  
extern uint8_t AT24C16_ReadOneByte(uint16_t ReadAddr);	//指定地址读取一个字节
extern void AT24C16_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);	//指定地址写入一个字节
extern void AT24C16_Write(uint16_t WriteAddr,uint8_t *Buffer,uint16_t Num);	//从指定地址开始写入指定长度的数据
extern void AT24C16_Read(uint16_t ReadAddr,uint8_t *Buffer,uint16_t Num);   	//从指定地址开始读出指定长度的数据

extern uint8_t AT24C16_Check(void);  //检查器件

#endif

