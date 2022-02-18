/************************************************************************************** 
*   ����    ��2013��11��6��  
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 4.60
*   �ⲿ����12Mhz(��Ƶ48M)
*   ����    ��ѧϰʹ��AT24C02�洢����
*   ����    ��Ration
*   �ٷ���ַ��http://www.rationmcu.com
//  Description:   ģ��I2Cʱ����LM75Aͨ��                                   //
**************************************************************************************/
#include "lpc11xx.h"
#include "uart.h"
#include "i2c.h"
#include "stdio.h"
#include "stdlib.h"
#include "lm75a.h"


static volatile uint32_t TimeTick = 0;
		  
void SysTick_Handler(void)					  //ϵͳ��ʱ���жϷ�����
{
	TimeTick++;
}

void delay_ms(uint32_t ms) /* ע�⣺����Ĳ������ȡ699������ᳬ��24λ������ֵ */
{
	SysTick->LOAD =	(((24000)*ms)-1);	  //�����ؼ�������дֵ
	SysTick->VAL   =	 0;					  //����������
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //����������,�����������ж�
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	
}


/*******************************************************************************
* Function Name  : I2C_LM75_Read
* Description    : Reads Temperature data from the LM75.
* Input          : None
* Output         : 0xFFFF -- Error
*					0x0000 ~ 0x01FF -- Valid data
*					Temp	Binary 					Hex
*					+125	0111 1101 0xxx xxxx 	0FAh
*					+25		0001 1001 0xxx xxxx 	032h
*					+0.5	0000 0000 1xxx xxxx 	001h
*					0		0000 0000 0xxx xxxx		000h
*					-0.5	1111 1111 1xxx xxxx 	1FFh
*					-25		1110 0111 0xxx xxxx 	1CEh
*					-55		1100 1001 0xxx xxxx 	192h
* Return         : None
*******************************************************************************/


float I2C_LM75A_read(void)
{
	uint8_t TempH,TempL;
	uint16_t data;
	float temp;
	delay_ms(500);	

	TempH = LM75A_ReadOneByte(0x00);
	delay_ms(500);
	TempL = LM75A_ReadOneByte(0x01);

	data=((uint16_t)TempH << 8) | TempL ;
	data=(data>>5);
	temp = 0.125*data;

	return temp;

}

float readTemperature(void){
	unsigned char temp[2]={0};
	float temp_value=0.0;
	unsigned int temp_high=0;
	unsigned int temp_low=0;
	unsigned int low=0;
	unsigned int tempforh=0;
	unsigned int judge_posneg=0;
LM75A_Read(0x00,temp,2);
	
delay_ms(1000);
	temp_high=temp[0];
	temp_low=temp[1];
	low=temp_low>>5;
	tempforh=temp_high*8+low;
 
	judge_posneg=(temp_high & 0x80)>>7;
	if(judge_posneg==0){
		temp_value=tempforh*0.125;
		return temp_value;
		}else {
			tempforh=(tempforh^0x7FF)+1;
			temp_value=tempforh*(-0.125);   
			return temp_value;
			}
		
				
}


int main()
{

	char str[8]={'0'};

	float temp=0;



	UART_Init(9600); // ��ʼ������	
	I2C_Init(1); // ��ʼ��I2C ����ģʽ
	
	/*
	UART_send("�Ҽ�⵽�7777�LM75A  !!", 20);//���ڷ����ַ�������
	
	if(LM75A_Check()==0)	 // �����⵽��LM75A
	{
		UART_send("�Ҽ�⵽��LM75A  !!", 20);//���ڷ����ַ�������
		UART_send_byte('\n');
	}
	else   // ���û�м�⵽AT24C16
	{
		UART_send("��û�м�⵽LM75a  !! ", 23);//���ڷ����ַ�������
	}
	
*/
	while(1)
	{
		UART_send("begin: ", 8);//���ڷ����ַ�������
		
	//	temp = I2C_LM75A_read();
		temp = 5.34535;
	//temp = readTemperature();
		sprintf(str,"%8.3f",temp);    //С�����3λ
		
		UART_send(str, 8);//���ڷ����ַ�������	
		UART_send_byte('\n');// �Ѷ��������ݷ��ص��Դ���

	}
		
}
