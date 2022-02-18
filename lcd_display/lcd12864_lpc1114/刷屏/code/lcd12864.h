#include "lpc11xx.h"


#ifndef __ST7565_H
#define __ST7565_H




//*****************************引脚电平的宏定义*********************************





#define LCD12864_RSET_1 LPC_GPIO3->MASKED_ACCESS[1] = 0xFFF //RSET接第0脚输出高电平
#define LCD12864_RSET_0 LPC_GPIO3->MASKED_ACCESS[1] = 0x000   //RSET接第0脚输出低电平

#define LCD12864_CS_1 LPC_GPIO3->MASKED_ACCESS[2] = 0xFFF //RW接第1脚输出高电平
#define LCD12864_CS_0 LPC_GPIO3->MASKED_ACCESS[2] = 0x000 //RW接第1脚输出低电平

#define LCD12864_RW_1 LPC_GPIO3->MASKED_ACCESS[4] = 0xFFF //RW接第脚2输出高电平
#define LCD12864_RW_0 LPC_GPIO3->MASKED_ACCESS[4] = 0x000 //RW接第2脚输出低电平

#define LCD12864_RD_1 LPC_GPIO3->MASKED_ACCESS[8] = 0xFFF //EN接第3脚输出高电平
#define LCD12864_RD_0 LPC_GPIO3->MASKED_ACCESS[8] = 0x000   //EN接第3脚输出低电平

#define LCD12864_RS_1 LPC_GPIO3->MASKED_ACCESS[16] = 0xFFF//RS接第4脚输出高电平
#define LCD12864_RS_0 LPC_GPIO3->MASKED_ACCESS[16] = 0x000 //RS接第4脚输出低电平




#define DataPort LPC_GPIO2->DATA          //PIO2为数据端口





//--定义全局函数--//
void LcdSt7565_WriteCmd(uint8_t cmd);
void LcdSt7565_WriteData(uint8_t dat);
void Lcd12864_Init(void);
void Lcd12864_ClearScreen(void);
uint8_t Lcd12864_Write16CnCHAR(uint8_t x, uint8_t y, uint8_t *cn);

//*******************************n*1mS延时子函数*******************************
void TIM16B0_delay_ms(uint16_t ms);

//*******************************n*1uS延时子函数******************************
void TIM16B0_delay_us(uint16_t us);

//************************写数据到LCD数据端口子函数**************************
void WriteDataPort(uint8_t data);

#endif
