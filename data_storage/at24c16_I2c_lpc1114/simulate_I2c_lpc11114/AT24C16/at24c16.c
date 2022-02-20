#include "at24c16.h" 
#include "i2c.h"

/*********************************************/
/* �������ܣ���AT24C16�ж�һ���ֽ�����       */
/* ���ڲ�����temp :����������                */
/*********************************************/
uint8_t AT24C16_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;
			  	    																 
    I2C_Start();  
    I2C_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 
	I2C_Wait_Ack(); 
    I2C_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	I2C_Wait_Ack();	    
	I2C_Start();  	 	   
	I2C_Send_Byte(0XA1+((ReadAddr/256)<<1));   //�������ģʽ			   
	I2C_Wait_Ack();	 
    temp=I2C_Read_Byte();
	I2C_Wait_Ack();			   
    I2C_Stop();//����һ��ֹͣ����
		    
	return temp;
}

/*********************************************/
/* �������ܣ���AT24C16��дһ���ֽ�����       */
/* ��ڲ�����WriteAddr:��Ҫд���Ŀ���ַ    */
/*           DataToWrite:��Ҫд����ֽ�����  */
/*********************************************/
void AT24C16_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite)
{				   	  	    																 
    I2C_Start();  
	I2C_Send_Byte(0XA0+((WriteAddr/256)<<1));   //���͸�λ��ַ 	 
	I2C_Wait_Ack();	   
    I2C_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	I2C_Wait_Ack(); 	 										  		   
	I2C_Send_Byte(DataToWrite);     //�����ֽ�							   
	I2C_Wait_Ack();  		    	   
    I2C_Stop();//����һ��ֹͣ���� 
	delay_ms(5);// �����ʱ���Բ���ȥ��	 
}

/*********************************************/
/* �������ܣ���AT24C16�ж�����ֽ�����       */
/* ��ڲ�����ReadAddr:��Ҫ�����ݵ�Ŀ���ַ   */
/*           *Buffer:�����������ŵ��������  */
/*           Num��Ҫ���������ֽڸ���         */
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
/* �������ܣ���AT24C16��д����ֽ�����       */
/* ��ڲ�����WriteAddr:��Ҫд���ݵ�Ŀ���ַ  */
/*           *Buffer:����������е�����д��  */
/*           Num��Ҫд�������ֽڸ���         */
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
/* �������ܣ����AT24C16�Ƿ����               */
/* ���ڲ�����0������                           */
/*           1��������                         */
/***********************************************/
uint8_t AT24C16_Check(void)
{
	uint8_t temp;
	temp = AT24C16_ReadOneByte(0x0000);			   
	if(temp==0x88)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24C16_WriteOneByte(0x0000,0x88);
	    temp=AT24C16_ReadOneByte(0x0000);	  
		if(temp==0X88)return 0;
	}
	return 1;											  
}
