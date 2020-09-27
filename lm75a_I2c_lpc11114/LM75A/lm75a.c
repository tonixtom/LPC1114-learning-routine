#include "lpc11xx.h" 
#include "lm75a.h" 
#include "i2c.h"


/*********************************************/
/* 函数功能：给LM75A中写一个字节数据       */
/* 入口参数：WriteAddr:将要写入的目标地址    */
/*           DataToWrite:将要写入的字节数据  */
/* 注意：LM75A的地址为（0x0000~0x07FF）    */
/*********************************************/
void LM75A_WriteOneByte(uint8_t WriteAddr, uint8_t DataToWrite)
{				  
    I2C_Send_Ctrl(LM75_ADDRESS); //发送高位地址	  
	I2C_Send_Byte(WriteAddr);	 //发送低地址 										  		   
	I2C_Send_Byte(DataToWrite);     //发送字节							   		    	   
    I2C_Stop();//产生一个停止条件 
	delay_ms(5);// 这个延时绝对不能去掉	一次操作完成，需要在保持一段时间不再使用总线，等待总线超时
}

/*********************************************/
/* 函数功能：从LM75A中读一个字节数据       */
/* 出口参数：temp :读出的数据                */
/* 注意：LM75A的地址为（0x0000~0x07FF）    */
/*********************************************/
uint8_t LM75A_ReadOneByte(uint8_t ReadAddr)
{				  
	uint8_t temp=0;
			  	    																 
	I2C_Send_Ctrl(LM75_ADDRESS); 	 
    I2C_Send_Byte(ReadAddr);   //发送低地址    	 	   
	I2C_Send_Ctrl(LM75_ADDRESS | 0x01);			   
    temp=I2C_Recieve_Byte();	   
    I2C_Stop();//产生一个停止条件
		    
	return temp;
}

/*********************************************/
/* 函数功能：从LM75A中读多个字节数据       */
/* 入口参数：ReadAddr:将要读数据的目标地址   */
/*           *Buffer:读出数据来放到这个数组  */
/*           Num：要读的数据字节个数         */
/* 注意：LM75A的地址为（0x0000~0x07FF）    */
/*********************************************/
void LM75A_Read(uint8_t ReadAddr,uint8_t *Buffer,uint8_t Num)
{
	while(Num)
	{
		*Buffer++=LM75A_ReadOneByte(ReadAddr++);	
		Num--;
	}
}  

/*********************************************/
/* 函数功能：给LM75A中写多个字节数据       */
/* 入口参数：WriteAddr:将要写数据的目标地址  */
/*           *Buffer:把这个数组中的数据写入  */
/*           Num：要写的数据字节个数         */
/* 注意：LM75A的地址为（0x0000~0x07FF）    */
/*********************************************/
void LM75A_Write(uint8_t WriteAddr,uint8_t *Buffer,uint8_t Num)
{
	while(Num--)
	{
		LM75A_WriteOneByte(WriteAddr,*Buffer);
		WriteAddr++;
		Buffer++;
	}
}

/***********************************************/
/* 函数功能：检测LM75A是否存在               */
/* 出口参数：0：存在                           */
/*           1：不存在                         */
/***********************************************/
uint8_t LM75A_Check(void)
{
	uint8_t temp;
	temp = LM75A_ReadOneByte(0x01);	 // 读  0x01位置 的一个字节		   
	if(temp==0x00)return 0;		   
	else//排除第一次初始化的情况
	{
		LM75A_WriteOneByte(0x01,0x00);   //位置，数据
	    temp=LM75A_ReadOneByte(0x01);	 
		if(temp==0X00)return 0;
	}
	return 1;											  
}

