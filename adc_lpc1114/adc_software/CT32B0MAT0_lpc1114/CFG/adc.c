#include "lpc11xx.h"
#include "adc.h"


/*****************************************/
/* 函数名称：初始化ADC口                 */
/*****************************************/
void ADC_Init(uint8_t Channel)
{
	if(Channel>7) return;
	LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);        // ADC模块上电
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);     // 使能ADC时钟
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);     // 使能IOCON时钟
	switch(Channel)
	{
		case 0: // 通道0配置 set channel 0
			LPC_IOCON->R_PIO0_11 &= ~0x07;              // 
			LPC_IOCON->R_PIO0_11 |= 0x02;               // 把P0.11引脚设置为AD0功能
			LPC_IOCON->R_PIO0_11 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->R_PIO0_11 &= ~(1<<7) ;           // 模拟输入模式
			break;
		case 1:  // 通道1配置 set channel 1
			LPC_IOCON->R_PIO1_0 &= ~0x07;              // 
			LPC_IOCON->R_PIO1_0 |= 0x02;               // 把P1.0引脚设置为AD1功能
			LPC_IOCON->R_PIO1_0 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->R_PIO1_0 &= ~(1<<7) ;           // 模拟输入模式
			break;
		case 2:  // 通道2配置 set channel 2
			LPC_IOCON->R_PIO1_1 &= ~0x07;              // 
			LPC_IOCON->R_PIO1_1 |= 0x02;               // 把P1.1引脚设置为AD2功能
			LPC_IOCON->R_PIO1_1 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->R_PIO1_1 &= ~(1<<7) ;           // 模拟输入模式
			break;
		case 3:  // 通道3配置 set channel 3
			LPC_IOCON->R_PIO1_2 &= ~0x07;              // 
			LPC_IOCON->R_PIO1_2 |= 0x02;               // 把P1.2引脚设置为AD3功能
			LPC_IOCON->R_PIO1_2 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->R_PIO1_2 &= ~(1<<7) ;           // 模拟输入模式
			break;
		case 4:  // 通道4配置 set channel 4
			LPC_IOCON->SWDIO_PIO1_3 &= ~0x07;              // 
			LPC_IOCON->SWDIO_PIO1_3 |= 0x02;               // 把P1.3引脚设置为AD4功能
			LPC_IOCON->SWDIO_PIO1_3 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->SWDIO_PIO1_3 &= ~(1<<7) ;           // 模拟输入模式
			break;
		case 5:  // 通道5配置 set channel 5
			LPC_IOCON->PIO1_4 &= ~0x07;              // 
			LPC_IOCON->PIO1_4 |= 0x01;               // 把P1.4引脚设置为AD5功能
			LPC_IOCON->PIO1_4 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->PIO1_4 &= ~(1<<7) ;           // 模拟输入模式
			break;
		case 6:  // 通道6配置 set channel 6
			LPC_IOCON->PIO1_10 &= ~0x07;              // 
			LPC_IOCON->PIO1_10 |= 0x01;               // 把P1.10引脚设置为AD6功能
			LPC_IOCON->PIO1_10 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->PIO1_10 &= ~(1<<7) ;           // 模拟输入模式
			break;
		case 7:  // 通道7配置 set channel 7
			LPC_IOCON->PIO1_11 &= ~0x07;              // 
			LPC_IOCON->PIO1_11 |= 0x01;               // 把P1.11引脚设置为AD7功能
			LPC_IOCON->PIO1_11 &= ~(3<<3) ;           // 去掉上拉和下拉电阻
			LPC_IOCON->PIO1_11 &= ~(1<<7) ;           // 模拟输入模式
			break;
		default:break;
	}
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);    // 关闭IOCON时钟
	LPC_ADC->CR = (1<<Channel)|                /* bit7:bit0   选择通道Channel*/
										(24<<8)|                     /* bit15:bit8  把采样时钟频率设置为2MHz 50/(24+1)*/
	                  (0x4<<24);                    /* CT32B0MAT0触发转换 */
}

/********************************************/
/* 函数功能：读取电压值（AD7）              */
/* 出口参数：adc_value, 读到的电压值        */
/********************************************/
uint32_t ADC_Read(uint8_t Channel)
{
	uint32_t adc_value=0;

	while((LPC_ADC->DR[Channel]&0x80000000)==0);
	adc_value = ((LPC_ADC->DR[Channel]>>6)&0x3FF);		
	adc_value = (adc_value*Vref)/1024; // 转换为真正的电压值

	return adc_value;	  // 返回结果
}

void TIM32B0_MAT_Init(uint16_t cycle_ms)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);	//使能TIM32B0时钟
	LPC_TMR32B0->TCR = 0x02;		  //复位定时器（bit1：写1复位）
	LPC_TMR32B0->PR  = SystemCoreClock/1000-1;		  //1ms TC+1
	LPC_TMR32B0->MR0 = cycle_ms;//
	LPC_TMR32B0->IR  = 0x01;		  //MR0中断复位（bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0）
	LPC_TMR32B0->MCR = 0x02;		  //MR0中断产生时复位TC
	LPC_TMR32B0->EMR = 0x30;		  //MR0与PC相等时，MAT0引脚翻转电平
	LPC_TMR32B0->TCR = 0x01;		  //启动定时器：TCR[0]=1;
}


//////////////////////////////////////////////////////////



