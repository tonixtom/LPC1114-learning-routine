#include "i2c.h"





/****************************************/
/* 函数功能：初始化I2C引脚（模拟I2C）   */
/****************************************/
void I2C_Init(void)
{					     
	LPC_GPIO0->DIR |= (1<<4)|(1<<5);//	设置P0.4,P0.5脚为输出
	LPC_GPIO0->DATA |= (1<<4)|(1<<5);// 输出高电平 SCL=1 SDA=1
}

/****************************************/
/* 函数功能：发I2C起始信号（模拟I2C）   */
/****************************************/
void I2C_Start(void)
{
	LPC_GPIO0->DIR |= (1<<5);     // 设置SDA引脚为输出
	LPC_GPIO0->DATA  |= (1<<5);	  // SDA=1;
	delay_us(5);	  
	LPC_GPIO0->DATA  |= (1<<4);	  // SCL=1;
	delay_us(5);
 	LPC_GPIO0->DATA  &= ~(1<<5);  // SDA=0;
	delay_us(5);
}	  

/****************************************/
/* 函数功能：发I2C结束信号（模拟I2C）   */
/****************************************/
void I2C_Stop(void)
{
	LPC_GPIO0->DIR |= (1<<5);     // SDA输出
	LPC_GPIO0->DATA  &= ~(1<<5);  // SDA=0;
 	delay_us(5);
	LPC_GPIO0->DATA  |= (1<<4);   // SCL=1;
	delay_us(5);
	LPC_GPIO0->DATA  |= (1<<5);   // SDA=1;
	delay_us(5);							   	
}

/****************************************/
/* 函数功能：等待应答信号 （模拟I2C）   */
/* 出口参数：1：接收应答失败            */
/*           0：接收应答成功            */
/****************************************/
uint8_t I2C_Wait_Ack(void)
{
	uint8_t ack_sign;

	LPC_GPIO0->DIR|=(1<<5);     // 设置SDA引脚为输出
	LPC_GPIO0->DATA|=(1<<5);	  // SDA=1;
	LPC_GPIO0->DATA|=(1<<4);	  //SCL=1;
	LPC_GPIO0->DIR  &= ~(1<<5);   //SDA设置为输入  
	delay_us(5);
	if((LPC_GPIO0->DATA&(1<<5))==(1<<5))ack_sign=1;
	else ack_sign=0;	   
	LPC_GPIO0->DATA&=~(1<<4);	  //SCL=0; 
	  
	return ack_sign;  
} 

/****************************************/
/* 函数功能：发送一个字节数据（模拟I2C）*/
/* 入口参数：wbyte:要发送的字节         */
/****************************************/		  
void I2C_Send_Byte(uint8_t wbyte)
{                        
    uint8_t i,temp,temp1;   
	LPC_GPIO0->DIR |= (1<<5); 	// 设置SDA引脚为输出    
	temp1=wbyte;
    for(i=0;i<8;i++)
    {              
        LPC_GPIO0->DATA&=~(1<<4); // SCL=0;
		delay_us(5);
		temp=temp1;
		temp=temp&0x80;
		if(temp==0x80)
		LPC_GPIO0->DATA |= (1<<5); // SDA=1;
		else
		LPC_GPIO0->DATA &= ~(1<<5);// SDA=0;
		delay_us(5);
		LPC_GPIO0->DATA  |= (1<<4); // SCL=1;
		delay_us(5); 
		LPC_GPIO0->DATA  &= ~(1<<4);// SCL=0;	
		delay_us(5);
		temp1<<=1;
    }	 
} 	    

/****************************************/
/* 函数功能：读一个字节数据（模拟I2C）  */
/* 出口参数：rebyte:读出的字节          */
/****************************************/   
uint8_t I2C_Read_Byte(void)
{
	uint8_t i,rebyte=0;
	LPC_GPIO0->DIR &= ~(1<<5);//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        rebyte<<=1;
		delay_us(5);
		LPC_GPIO0->DATA  &= ~(1<<4);  // SCL=0;
        delay_us(5);
		LPC_GPIO0->DATA  |= (1<<4);	  // SCL=1;
        delay_us(5);
        if((LPC_GPIO0->DATA&(1<<5))==(1<<5))//if(SDA==1)
		rebyte|=0x01;  
    }					 
    return rebyte;
}


