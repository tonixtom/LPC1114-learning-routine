#include "i2c.h"

/****************************************/
/* 函数功能：初始化LPC1114 I2C模块      */
/* 入口参数：Mode :0 , 慢速模式         */
/*                 1 , 快速模式         */
/****************************************/
void I2C_Init(uint8_t Mode)
{
	LPC_SYSCON->PRESETCTRL |= (1<<1); // De-asserted I2C模块（在启动I2C模块之前，必须向该位写1）
 	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5); // 使能I2C时钟
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 使能IOCON时钟
	LPC_IOCON->PIO0_4 &= ~0x3F;	    
	LPC_IOCON->PIO0_4 |= 0x01;		// 把P0.4脚配置为 I2C SCL 
	LPC_IOCON->PIO0_5 &= ~0x3F;	
	LPC_IOCON->PIO0_5 |= 0x01;		// 把P0.5脚配置为 I2C SDA 
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // 禁能IOCON时钟 
	if(Mode == 1)	// 快速I2C通信 (大约400KHz传输速率)
	{
		LPC_I2C->SCLH = 60; 
		LPC_I2C->SCLL = 65;  
	}
	else 	// 低速I2C通信	 (大约100KHz传输速率)
	{
		LPC_I2C->SCLH = 250; 
		LPC_I2C->SCLL = 250; 
	}
	LPC_I2C->CONCLR = 0xFF;  // 清所有标志
	LPC_I2C->CONSET |= I2CONSET_I2EN;  // 使能I2C接口
}

/***************************************************/
/* 函数功能：发送停止信号                          */
/***************************************************/
void I2C_Stop(void)
{
   LPC_I2C->CONCLR = I2CONCLR_SIC;    // 清SI标志位
   LPC_I2C->CONSET |= I2CONSET_STO; 	// 发送停止信号
}

/***************************************************/
/* 函数功能：I2C发送命令数据                       */
/* 入口参数：Ctrl : 命令+地址字节                  */
/* 出口参数：0：成功                               */
/*           1: 失败                               */
/***************************************************/
uint8_t I2C_Send_Ctrl(uint8_t CtrlAndAddr)
{
   	uint8_t res;

   	if(CtrlAndAddr & 1)    // 如果是读命令
   	   	res = 0x40; // 40H代表开始信号和读命令已经传输完毕，并且已经接收到ACK
   	else			   // 如果是写命令
       	res = 0x18; // 18H代表开始信号和写命令已经传输完毕，并且已经接收到ACK
	// 发送开始信号
   	LPC_I2C->CONCLR = 0xFF; // 清所有标志位
   	LPC_I2C->CONSET |= I2CONSET_I2EN | I2CONSET_STA;	// 使能发送开始信号
   	while(!(LPC_I2C->CONSET & I2CONSET_SI));   // 等待开始信号发送完成
	// 发送命令+地址字节
   	LPC_I2C->DAT = CtrlAndAddr;	 // 把要发送的字节给了DAT寄存器
   	LPC_I2C->CONCLR = I2CONCLR_STAC | I2CONCLR_SIC; // 清除开始START位和SI位 
   	while(!(LPC_I2C->CONSET & I2CONSET_SI));  // 等待数据发送完成
   	if(LPC_I2C->STAT != res)	  // 观察STAT寄存器响应的状态，判断是否正确执行读或写命令
   	{
      	I2C_Stop();		 // 没有完成任务，发送停止信号，结束I2C通信
      	return 1;			 // 返回1，表明失败！
   	}
   	return 0;			 // 如果正确执行返回0
}
/***************************************************/
/* 函数功能：I2C发送一字节数据                     */
/* 入口参数：sebyte : 要发送的字节                 */
/***************************************************/
void I2C_Send_Byte(uint8_t sebyte)
{
   LPC_I2C->DAT = sebyte;	  // 把字节写入DAT寄存器
   LPC_I2C->CONCLR = I2CONSET_SI;   // 清除SI标志
   while(!(LPC_I2C->CONSET & I2CONSET_SI));  // 等待数据发送完成
}

/***************************************************/
/* 函数功能：I2C接收一字节数据                     */
/* 入口参数：rebyte : 要接收的字节                 */
/***************************************************/
uint8_t I2C_Recieve_Byte(void)
{
	uint8_t rebyte;
	
	LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC;  // 清AA和SI标志
	while(!(LPC_I2C->CONSET & I2CONSET_SI));  // 等待接收数据完成
	rebyte = (uint8_t)LPC_I2C->DAT;	// 把接收到的数据给了rebyte

	return rebyte;
}


