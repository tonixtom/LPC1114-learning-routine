#include "lpc11xx.h"
#include "at24c02.h"
#include "i2c.h"

void delay_i2c(uint8_t t)
{
	uint16_t i,j;
	for(i=0;i<50000;i++)
		for(j=0;j<t;j++);
}
/*********************************************/
/* 函数功能：给AT24C02中写一个字节数据       */
/* 入口参数：WriteAddr:将要写入的目标地址    */
/*           DataToWrite:将要写入的字节数据  */
/* 注意：AT24C02的地址为（0x00~0xFF）    */
/*********************************************/
void AT24C02_WriteOneByte(uint8_t WriteAddr, uint8_t DataToWrite)
{				  
  I2C_Send_Ctrl(0XA0);   
	I2C_Send_Byte(WriteAddr);	 //发送地址 										  		   
	I2C_Send_Byte(DataToWrite);     //发送字节							   		    	   
  I2C_Stop();//产生一个停止条件 
	delay_i2c(4);// 这个延时绝对不能去掉	 
}

/*********************************************/
/* 函数功能：从AT24C02中读一个字节数据       */
/* 出口参数：temp :读出的数据                */
/* 注意：AT24C02的地址为（0x00~0xFF）    */
/*********************************************/
uint8_t AT24C02_ReadOneByte(uint8_t ReadAddr)
{				  
	uint8_t temp=0;
			  	    																 
	I2C_Send_Ctrl(0XA0); 	 
  I2C_Send_Byte(ReadAddr);   //发送地址    	 	   
	I2C_Send_Ctrl(0XA1);			   
  temp=I2C_Recieve_Byte();	   
  I2C_Stop();//产生一个停止条件
		    
	return temp;
}

/*********************************************/
/* 函数功能：从AT24C02中读多个字节数据       */
/* 入口参数：ReadAddr:将要读数据的目标地址   */
/*           *Buffer:读出数据来放到这个数组  */
/*           Num：要读的数据字节个数         */
/* 注意：AT24C02的地址为（0x00~0xFF）    */
/*********************************************/
void AT24C02_Read(uint8_t ReadAddr,uint8_t *Buffer,uint16_t Num)
{
	while(Num)
	{
		*Buffer++=AT24C02_ReadOneByte(ReadAddr++);	
		Num--;
	}
}  

/*********************************************/
/* 函数功能：给AT24C02中写多个字节数据       */
/* 入口参数：WriteAddr:将要写数据的目标地址  */
/*           *Buffer:把这个数组中的数据写入  */
/*           Num：要写的数据字节个数         */
/* 注意：AT24C02的地址为（0x00~0xFF）    */
/*********************************************/
void AT24C02_Write(uint8_t WriteAddr,uint8_t *Buffer,uint16_t Num)
{
	while(Num--)
	{
		AT24C02_WriteOneByte(WriteAddr,*Buffer);
		WriteAddr++;
		Buffer++;
	}
}

/***********************************************/
/* 函数功能：检测AT24C02是否存在               */
/* 出口参数：0：存在                           */
/*           1：不存在                         */
/***********************************************/
uint8_t AT24C02_Check(void)
{
	uint8_t temp;
	temp = AT24C02_ReadOneByte(0x00);	 // 读字节		   
	if(temp==0x88)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24C02_WriteOneByte(0x00,0x88);
	  temp=AT24C02_ReadOneByte(0x00);	  
		if(temp==0X88)return 0;
	}
	return 1;											  
}








