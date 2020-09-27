#include "lpc11xx.h" 
#include "lm75a.h" 
#include "i2c.h"


/*********************************************/
/* �������ܣ���LM75A��дһ���ֽ�����       */
/* ��ڲ�����WriteAddr:��Ҫд���Ŀ���ַ    */
/*           DataToWrite:��Ҫд����ֽ�����  */
/* ע�⣺LM75A�ĵ�ַΪ��0x0000~0x07FF��    */
/*********************************************/
void LM75A_WriteOneByte(uint8_t WriteAddr, uint8_t DataToWrite)
{				  
    I2C_Send_Ctrl(LM75_ADDRESS); //���͸�λ��ַ	  
	I2C_Send_Byte(WriteAddr);	 //���͵͵�ַ 										  		   
	I2C_Send_Byte(DataToWrite);     //�����ֽ�							   		    	   
    I2C_Stop();//����һ��ֹͣ���� 
	delay_ms(5);// �����ʱ���Բ���ȥ��	һ�β�����ɣ���Ҫ�ڱ���һ��ʱ�䲻��ʹ�����ߣ��ȴ����߳�ʱ
}

/*********************************************/
/* �������ܣ���LM75A�ж�һ���ֽ�����       */
/* ���ڲ�����temp :����������                */
/* ע�⣺LM75A�ĵ�ַΪ��0x0000~0x07FF��    */
/*********************************************/
uint8_t LM75A_ReadOneByte(uint8_t ReadAddr)
{				  
	uint8_t temp=0;
			  	    																 
	I2C_Send_Ctrl(LM75_ADDRESS); 	 
    I2C_Send_Byte(ReadAddr);   //���͵͵�ַ    	 	   
	I2C_Send_Ctrl(LM75_ADDRESS | 0x01);			   
    temp=I2C_Recieve_Byte();	   
    I2C_Stop();//����һ��ֹͣ����
		    
	return temp;
}

/*********************************************/
/* �������ܣ���LM75A�ж�����ֽ�����       */
/* ��ڲ�����ReadAddr:��Ҫ�����ݵ�Ŀ���ַ   */
/*           *Buffer:�����������ŵ��������  */
/*           Num��Ҫ���������ֽڸ���         */
/* ע�⣺LM75A�ĵ�ַΪ��0x0000~0x07FF��    */
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
/* �������ܣ���LM75A��д����ֽ�����       */
/* ��ڲ�����WriteAddr:��Ҫд���ݵ�Ŀ���ַ  */
/*           *Buffer:����������е�����д��  */
/*           Num��Ҫд�������ֽڸ���         */
/* ע�⣺LM75A�ĵ�ַΪ��0x0000~0x07FF��    */
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
/* �������ܣ����LM75A�Ƿ����               */
/* ���ڲ�����0������                           */
/*           1��������                         */
/***********************************************/
uint8_t LM75A_Check(void)
{
	uint8_t temp;
	temp = LM75A_ReadOneByte(0x01);	 // ��  0x01λ�� ��һ���ֽ�		   
	if(temp==0x00)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		LM75A_WriteOneByte(0x01,0x00);   //λ�ã�����
	    temp=LM75A_ReadOneByte(0x01);	 
		if(temp==0X00)return 0;
	}
	return 1;											  
}

