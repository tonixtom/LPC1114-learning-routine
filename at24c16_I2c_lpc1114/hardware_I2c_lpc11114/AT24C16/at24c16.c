#include "lpc11xx.h" 
#include "at24c16.h" 
#include "i2c.h"

/*********************************************/
/* 函数功能：给AT24C16中写一个字节数据       */
/* 入口参数：WriteAddr:将要写入的目标地址    */
/*           DataToWrite:将要写入的字节数据  */
/* 注意：AT24C16的地址为（0x0000~0x07FF）    */
/*********************************************/
void AT24C16_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite)
{				  
    I2C_Send_Ctrl(0XA0+((WriteAddr/256)<<1)); //发送高位地址	  
	I2C_Send_Byte(WriteAddr%256);	 //发送低地址 										  		   
	I2C_Send_Byte(DataToWrite);     //发送字节							   		    	   
    I2C_Stop();//产生一个停止条件 
	delay_ms(5);// 这个延时绝对不能去掉	一次操作完成，需要在保持一段时间不再使用总线，等待总线超时
}

/*********************************************/
/* 函数功能：从AT24C16中读一个字节数据       */
/* 出口参数：temp :读出的数据                */
/* 注意：AT24C16的地址为（0x0000~0x07FF）    */
/*********************************************/
uint8_t AT24C16_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;
			  	    																 
	I2C_Send_Ctrl(0XA0+((ReadAddr/256)<<1)); 	 
    I2C_Send_Byte(ReadAddr%256);   //发送低地址    	 	   
	I2C_Send_Ctrl(0XA1+((ReadAddr/256)<<1));			   
    temp=I2C_Recieve_Byte();	   
    I2C_Stop();//产生一个停止条件
		    
	return temp;
}

/*********************************************/
/* 函数功能：从AT24C16中读多个字节数据       */
/* 入口参数：ReadAddr:将要读数据的目标地址   */
/*           *Buffer:读出数据来放到这个数组  */
/*           Num：要读的数据字节个数         */
/* 注意：AT24C16的地址为（0x0000~0x07FF）    */
/*********************************************/
void AT24C16_Read(uint16_t ReadAddr,uint8_t *Buffer,uint16_t Num)
{
	while(Num)
	{
		*Buffer++=AT24C16_ReadOneByte(ReadAddr++);	
		Num--;
	}
}  

/*********************************************/
/* 函数功能：给AT24C16中写多个字节数据       */
/* 入口参数：WriteAddr:将要写数据的目标地址  */
/*           *Buffer:把这个数组中的数据写入  */
/*           Num：要写的数据字节个数         */
/* 注意：AT24C16的地址为（0x0000~0x07FF）    */
/*********************************************/
void AT24C16_Write(uint16_t WriteAddr,uint8_t *Buffer,uint16_t Num)
{
	while(Num--)
	{
		AT24C16_WriteOneByte(WriteAddr,*Buffer);
		WriteAddr++;
		Buffer++;
	}
}

/***********************************************/
/* 函数功能：检测AT24C16是否存在               */
/* 出口参数：0：存在                           */
/*           1：不存在                         */
/***********************************************/
uint8_t AT24C16_Check(void)
{
	uint8_t temp;
	temp = AT24C16_ReadOneByte(0x0000);	 // 读字节		   
	if(temp==0x88)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24C16_WriteOneByte(0x0000,0x88);
	    temp=AT24C16_ReadOneByte(0x0000);	  
		if(temp==0X88)return 0;
	}
	return 1;											  
}

