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
/* �������ܣ���AT24C02��дһ���ֽ�����       */
/* ��ڲ�����WriteAddr:��Ҫд���Ŀ���ַ    */
/*           DataToWrite:��Ҫд����ֽ�����  */
/* ע�⣺AT24C02�ĵ�ַΪ��0x00~0xFF��    */
/*********************************************/
void AT24C02_WriteOneByte(uint8_t WriteAddr, uint8_t DataToWrite)
{				  
  I2C_Send_Ctrl(0XA0);   
	I2C_Send_Byte(WriteAddr);	 //���͵�ַ 										  		   
	I2C_Send_Byte(DataToWrite);     //�����ֽ�							   		    	   
  I2C_Stop();//����һ��ֹͣ���� 
	delay_i2c(4);// �����ʱ���Բ���ȥ��	 
}

/*********************************************/
/* �������ܣ���AT24C02�ж�һ���ֽ�����       */
/* ���ڲ�����temp :����������                */
/* ע�⣺AT24C02�ĵ�ַΪ��0x00~0xFF��    */
/*********************************************/
uint8_t AT24C02_ReadOneByte(uint8_t ReadAddr)
{				  
	uint8_t temp=0;
			  	    																 
	I2C_Send_Ctrl(0XA0); 	 
  I2C_Send_Byte(ReadAddr);   //���͵�ַ    	 	   
	I2C_Send_Ctrl(0XA1);			   
  temp=I2C_Recieve_Byte();	   
  I2C_Stop();//����һ��ֹͣ����
		    
	return temp;
}

/*********************************************/
/* �������ܣ���AT24C02�ж�����ֽ�����       */
/* ��ڲ�����ReadAddr:��Ҫ�����ݵ�Ŀ���ַ   */
/*           *Buffer:�����������ŵ��������  */
/*           Num��Ҫ���������ֽڸ���         */
/* ע�⣺AT24C02�ĵ�ַΪ��0x00~0xFF��    */
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
/* �������ܣ���AT24C02��д����ֽ�����       */
/* ��ڲ�����WriteAddr:��Ҫд���ݵ�Ŀ���ַ  */
/*           *Buffer:����������е�����д��  */
/*           Num��Ҫд�������ֽڸ���         */
/* ע�⣺AT24C02�ĵ�ַΪ��0x00~0xFF��    */
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
/* �������ܣ����AT24C02�Ƿ����               */
/* ���ڲ�����0������                           */
/*           1��������                         */
/***********************************************/
uint8_t AT24C02_Check(void)
{
	uint8_t temp;
	temp = AT24C02_ReadOneByte(0x00);	 // ���ֽ�		   
	if(temp==0x88)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24C02_WriteOneByte(0x00,0x88);
	  temp=AT24C02_ReadOneByte(0x00);	  
		if(temp==0X88)return 0;
	}
	return 1;											  
}








