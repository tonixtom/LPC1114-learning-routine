#include "lpc11xx.h"


#ifndef __ST7565_H
#define __ST7565_H




//*****************************���ŵ�ƽ�ĺ궨��*********************************





#define LCD12864_RSET_1 LPC_GPIO3->MASKED_ACCESS[1] = 0xFFF //RSET�ӵ�0������ߵ�ƽ
#define LCD12864_RSET_0 LPC_GPIO3->MASKED_ACCESS[1] = 0x000   //RSET�ӵ�0������͵�ƽ

#define LCD12864_CS_1 LPC_GPIO3->MASKED_ACCESS[2] = 0xFFF //RW�ӵ�1������ߵ�ƽ
#define LCD12864_CS_0 LPC_GPIO3->MASKED_ACCESS[2] = 0x000 //RW�ӵ�1������͵�ƽ

#define LCD12864_RW_1 LPC_GPIO3->MASKED_ACCESS[4] = 0xFFF //RW�ӵڽ�2����ߵ�ƽ
#define LCD12864_RW_0 LPC_GPIO3->MASKED_ACCESS[4] = 0x000 //RW�ӵ�2������͵�ƽ

#define LCD12864_RD_1 LPC_GPIO3->MASKED_ACCESS[8] = 0xFFF //EN�ӵ�3������ߵ�ƽ
#define LCD12864_RD_0 LPC_GPIO3->MASKED_ACCESS[8] = 0x000   //EN�ӵ�3������͵�ƽ

#define LCD12864_RS_1 LPC_GPIO3->MASKED_ACCESS[16] = 0xFFF//RS�ӵ�4������ߵ�ƽ
#define LCD12864_RS_0 LPC_GPIO3->MASKED_ACCESS[16] = 0x000 //RS�ӵ�4������͵�ƽ




#define DataPort LPC_GPIO2->DATA          //PIO2Ϊ���ݶ˿�





//--����ȫ�ֺ���--//
void LcdSt7565_WriteCmd(uint8_t cmd);
void LcdSt7565_WriteData(uint8_t dat);
void Lcd12864_Init(void);
void Lcd12864_ClearScreen(void);
uint8_t Lcd12864_Write16CnCHAR(uint8_t x, uint8_t y, uint8_t *cn);

//*******************************n*1mS��ʱ�Ӻ���*******************************
void TIM16B0_delay_ms(uint16_t ms);

//*******************************n*1uS��ʱ�Ӻ���******************************
void TIM16B0_delay_us(uint16_t us);

//************************д���ݵ�LCD���ݶ˿��Ӻ���**************************
void WriteDataPort(uint8_t data);

#endif
