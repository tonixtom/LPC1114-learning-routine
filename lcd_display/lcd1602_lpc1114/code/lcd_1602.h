
#ifndef   __NXPLPC11XX_LCD_H__
#define   __NXPLPC11XX_LCD_H__



#include "lpc11xx.h"
//*****************************引脚电平的宏定义*********************************
#define LCM_RS_1 LPC_GPIO2->MASKED_ACCESS[1024] = 0xFFF//RS接第10脚输出高电平
#define LCM_RS_0 LPC_GPIO2->MASKED_ACCESS[1024] = 0x000 //RS接第10脚输出低电平
#define LCM_RW_1 LPC_GPIO2->MASKED_ACCESS[512] = 0xFFF //RW接第9脚输出高电平
#define LCM_RW_0 LPC_GPIO2->MASKED_ACCESS[512] = 0x000 //RW接第9脚输出低电平
#define LCM_EN_1 LPC_GPIO2->MASKED_ACCESS[256] = 0xFFF //EN接第8脚输出高电平
#define LCM_EN_0 LPC_GPIO2->MASKED_ACCESS[256] = 0x000   //EN接第8脚输出低电平
#define DataPort LPC_GPIO2->DATA          //PIO2为数据端口
#define Busy 0x80         //忙信号


//*******************************n*1mS延时子函数*******************************
void TIM16B0_delay_ms(uint16_t ms);

//*******************************n*1uS延时子函数******************************
void TIM16B0_delay_us(uint16_t us);

//************************写数据到LCD数据端口子函数**************************
void WriteDataPort(uint8_t data);

//************************读LCD数据端口数据子函数****************************
uint8_t ReadDataPort(void);

//***************************检测LCD忙信号子函数*****************************
void WaitForEnable(void);

//****************************写命令到LCD子函数****************************
void LcdWriteCommand(uint8_t CMD,uint8_t Attribc);
//写命令CMD到LCD中，Arribc为1时检测忙信号，否则不检测

//****************************写数据到LCD子函数****************************
void LcdWriteData(uint8_t dataW);      //写数据dataW到LCD中

//*****************************LCD初始化子函数*****************************
void InitLcd(void); 

//***************************显示光标定位子函数****************************
void LocateXY(char posx,char posy);      //定位位置到地址x列y行

//**********************显示指定座标的一个字符子函数************************
void DisplayOneChar(uint8_t x,uint8_t y,uint8_t Wdata); 

//**********************显示指定座标的一串字符子函数************************
void ePutstr(uint8_t x,uint8_t y,uint8_t const *ptr);    //在x列y行处显示ptr指向的字符串


#endif
