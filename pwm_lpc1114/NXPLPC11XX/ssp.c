#include "nxplpc11xx.h"
#include "ssp.h"

/*****************************************/
/* 函数功能：SPI1通信                    */
/* 说明：    发送一个字节，接收一个字节  */
/*****************************************/
uint8 SPI1_communication(uint8 TxData)
{		
	while(((SSP1->SR)&(1<<4))==(1<<4));//忙时等待,SR状态寄存器bit4 BSY:忙时为1
	SSP1->DR = TxData;                 //把要发送的数写入TxFIFO
	while(((SSP1->SR)&(1<<2))!=(1<<2));//等待接收完,SR状态寄存器bit2 RNE:接收FIFO非空为1
	return(SSP1->DR);		    	   //返回收到的数据
}

/*****************************************/
/* 函数功能：SPI0通信                    */
/* 说明：    发送一个字节，接收一个字节  */
/*****************************************/
uint8 SPI0_communication(uint8 TxData)
{		
	while(((SSP0->SR)&(1<<4))==(1<<4));//忙时等待,SR状态寄存器bit4 BSY:忙时为1
	SSP0->DR = TxData;                 //把要发送的数写入TxFIFO
	while(((SSP0->SR)&(1<<2))!=(1<<2));//等待接收完,SR状态寄存器bit2 RNE:接收FIFO非空为1
	return(SSP0->DR);		    	   //返回收到的数据
}

/*****************************************/
/* 函数功能：SPI1初始化                  */
/* 说明：    没有用SSEL1                 */
/*****************************************/
void SPI1_Init(void)
{
	uint8 i,Clear=Clear;//Clear=Clear:用这种语句形式解决编译产生的Waring:never used!	

	SYSCON->PRESETCTRL |= (0x1<<2);	   //禁止SSP1复位
	SYSCON->SYSAHBCLKCTRL |= (0x1<<18);//允许SSP1时钟 bit18
	SYSCON->SSP1CLKDIV =  0x01;		   //分频系数为1，使SPI1速率最大：48Mhz

	SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟(bit16)
	IOCON->PIO2_1 &= ~0x07;
	IOCON->PIO2_1 |= 0x02;		//把PIO2_1选择为SSP CLK 
	IOCON->PIO2_2 &= ~0x07;	
	IOCON->PIO2_2 |= 0x02;		//把PIO2_2选择为SSP MISO 
	IOCON->PIO2_3 &= ~0x07;	
	IOCON->PIO2_3 |= 0x02;		//把PIO2_3选择为SSP MOSI 
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟(bit16)

	// 8位数据传输，SPI模式, CPOL = 0, CPHA = 0,空闲时CLI为0，第一个上升沿采集数据，SCR = 0
	SSP1->CR0 = 0x0107;	    
	// 预分频值为254（注意：这里最小为2，而且必须为偶数 2~254） 
	SSP1->CPSR = 0x02;
	SSP1->CR1 &= ~(1<<0);//LBM=0:正常模式
	SSP1->CR1 &= ~(1<<2);//MS=0:主机模式 
	SSP1->CR1 |=  (1<<1);//SSE=1:使能SPI1
	//清空RxFIFO，LPC1114收发均有8帧FIFO,每帧可放置4~16位数据
	for ( i = 0; i < 8; i++ )
	{
	  	Clear = SSP1->DR;//读数据寄存器DR将清空RxFIFO
	} 		 		  
}


/*****************************************/
/* 函数功能：SPI0初始化                  */
/* 说明：    没有用SSEL0                 */
/*****************************************/
void SPI0_Init(void)
{
	uint8 i,Clear=Clear;//Clear=Clear:用这种语句形式解决编译产生的Waring:never used!	

	SYSCON->PRESETCTRL |= (0x1<<0);	   //禁止SSP0复位
	SYSCON->SYSAHBCLKCTRL |= (0x1<<11);//允许SSP0时钟 bit11
	SYSCON->SSP0CLKDIV = 0x06;		   //6分频：48/6=8Mhz

	SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟(bit16)
	IOCON->SCK_LOC = 0x02;      //把SCK0复用到PIO0_6引脚

	IOCON->PIO0_6 &= ~0x07;
	IOCON->PIO0_6 |= 0x02;		//把PIO0_6设置为SSP CLK 
	IOCON->PIO0_8 &= ~0x07;	
	IOCON->PIO0_8 |= 0x01;		//把PIO0_8设置为SSP MISO 
	IOCON->PIO0_9 &= ~0x07;	
	IOCON->PIO0_9 |= 0x01;		//把PIO0_9设置为SSP MOSI 
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // 禁能IOCON时钟(bit16)
	
	// 8位数据传输，SPI模式, CPOL = 0, CPHA = 0,空闲时CLK为0，第一个上升沿采集数据，SCR = 0
	SSP0->CR0 = 0x0107;	    
	// 预分频值（注意：必须为偶数 2~254） 
	SSP0->CPSR = 0x02;
	SSP0->CR1 &= ~(1<<0);//LBM=0:正常模式
	SSP0->CR1 &= ~(1<<2);//MS=0:主机模式 
	SSP0->CR1 |=  (1<<1);//SSE=1:使能SPI0
	//清空RxFIFO，LPC1114收发均有8帧FIFO,每帧可放置4~16位数据
	for ( i = 0; i < 8; i++ )
	{
	  	Clear = SSP0->DR;//读数据寄存器DR将清空RxFIFO
	} 		 		  
}






