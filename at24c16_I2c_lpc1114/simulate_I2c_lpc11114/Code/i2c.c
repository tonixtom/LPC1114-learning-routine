#include "i2c.h"





/****************************************/
/* �������ܣ���ʼ��I2C���ţ�ģ��I2C��   */
/****************************************/
void I2C_Init(void)
{					     
	LPC_GPIO0->DIR |= (1<<4)|(1<<5);//	����P0.4,P0.5��Ϊ���
	LPC_GPIO0->DATA |= (1<<4)|(1<<5);// ����ߵ�ƽ SCL=1 SDA=1
}

/****************************************/
/* �������ܣ���I2C��ʼ�źţ�ģ��I2C��   */
/****************************************/
void I2C_Start(void)
{
	LPC_GPIO0->DIR |= (1<<5);     // ����SDA����Ϊ���
	LPC_GPIO0->DATA  |= (1<<5);	  // SDA=1;
	delay_us(5);	  
	LPC_GPIO0->DATA  |= (1<<4);	  // SCL=1;
	delay_us(5);
 	LPC_GPIO0->DATA  &= ~(1<<5);  // SDA=0;
	delay_us(5);
}	  

/****************************************/
/* �������ܣ���I2C�����źţ�ģ��I2C��   */
/****************************************/
void I2C_Stop(void)
{
	LPC_GPIO0->DIR |= (1<<5);     // SDA���
	LPC_GPIO0->DATA  &= ~(1<<5);  // SDA=0;
 	delay_us(5);
	LPC_GPIO0->DATA  |= (1<<4);   // SCL=1;
	delay_us(5);
	LPC_GPIO0->DATA  |= (1<<5);   // SDA=1;
	delay_us(5);							   	
}

/****************************************/
/* �������ܣ��ȴ�Ӧ���ź� ��ģ��I2C��   */
/* ���ڲ�����1������Ӧ��ʧ��            */
/*           0������Ӧ��ɹ�            */
/****************************************/
uint8_t I2C_Wait_Ack(void)
{
	uint8_t ack_sign;

	LPC_GPIO0->DIR|=(1<<5);     // ����SDA����Ϊ���
	LPC_GPIO0->DATA|=(1<<5);	  // SDA=1;
	LPC_GPIO0->DATA|=(1<<4);	  //SCL=1;
	LPC_GPIO0->DIR  &= ~(1<<5);   //SDA����Ϊ����  
	delay_us(5);
	if((LPC_GPIO0->DATA&(1<<5))==(1<<5))ack_sign=1;
	else ack_sign=0;	   
	LPC_GPIO0->DATA&=~(1<<4);	  //SCL=0; 
	  
	return ack_sign;  
} 

/****************************************/
/* �������ܣ�����һ���ֽ����ݣ�ģ��I2C��*/
/* ��ڲ�����wbyte:Ҫ���͵��ֽ�         */
/****************************************/		  
void I2C_Send_Byte(uint8_t wbyte)
{                        
    uint8_t i,temp,temp1;   
	LPC_GPIO0->DIR |= (1<<5); 	// ����SDA����Ϊ���    
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
/* �������ܣ���һ���ֽ����ݣ�ģ��I2C��  */
/* ���ڲ�����rebyte:�������ֽ�          */
/****************************************/   
uint8_t I2C_Read_Byte(void)
{
	uint8_t i,rebyte=0;
	LPC_GPIO0->DIR &= ~(1<<5);//SDA����Ϊ����
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


