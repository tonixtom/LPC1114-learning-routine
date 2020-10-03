
#ifndef   __NXPLPC11XX_LCD_H__
#define   __NXPLPC11XX_LCD_H__



#include "lpc11xx.h"
//*****************************���ŵ�ƽ�ĺ궨��*********************************
#define LCM_RS_1 LPC_GPIO2->MASKED_ACCESS[1024] = 0xFFF//RS�ӵ�10������ߵ�ƽ
#define LCM_RS_0 LPC_GPIO2->MASKED_ACCESS[1024] = 0x000 //RS�ӵ�10������͵�ƽ
#define LCM_RW_1 LPC_GPIO2->MASKED_ACCESS[512] = 0xFFF //RW�ӵ�9������ߵ�ƽ
#define LCM_RW_0 LPC_GPIO2->MASKED_ACCESS[512] = 0x000 //RW�ӵ�9������͵�ƽ
#define LCM_EN_1 LPC_GPIO2->MASKED_ACCESS[256] = 0xFFF //EN�ӵ�8������ߵ�ƽ
#define LCM_EN_0 LPC_GPIO2->MASKED_ACCESS[256] = 0x000   //EN�ӵ�8������͵�ƽ
#define DataPort LPC_GPIO2->DATA          //PIO2Ϊ���ݶ˿�
#define Busy 0x80         //æ�ź�


//*******************************n*1mS��ʱ�Ӻ���*******************************
void TIM16B0_delay_ms(uint16_t ms);

//*******************************n*1uS��ʱ�Ӻ���******************************
void TIM16B0_delay_us(uint16_t us);

//************************д���ݵ�LCD���ݶ˿��Ӻ���**************************
void WriteDataPort(uint8_t data);

//************************��LCD���ݶ˿������Ӻ���****************************
uint8_t ReadDataPort(void);

//***************************���LCDæ�ź��Ӻ���*****************************
void WaitForEnable(void);

//****************************д���LCD�Ӻ���****************************
void LcdWriteCommand(uint8_t CMD,uint8_t Attribc);
//д����CMD��LCD�У�ArribcΪ1ʱ���æ�źţ����򲻼��

//****************************д���ݵ�LCD�Ӻ���****************************
void LcdWriteData(uint8_t dataW);      //д����dataW��LCD��

//*****************************LCD��ʼ���Ӻ���*****************************
void InitLcd(void); 

//***************************��ʾ��궨λ�Ӻ���****************************
void LocateXY(char posx,char posy);      //��λλ�õ���ַx��y��

//**********************��ʾָ�������һ���ַ��Ӻ���************************
void DisplayOneChar(uint8_t x,uint8_t y,uint8_t Wdata); 

//**********************��ʾָ�������һ���ַ��Ӻ���************************
void ePutstr(uint8_t x,uint8_t y,uint8_t const *ptr);    //��x��y�д���ʾptrָ����ַ���


#endif
