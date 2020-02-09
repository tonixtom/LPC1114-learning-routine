#include "GPIO.H"
#include <LPC11xx.h>
#include "stdint.h"

//******************************������ʾ�ַ���**********************************
uint8_t const str0[]={"  wang lei"};
uint8_t const str1[]={"I love xiaozeng"};
//*****************************���ŵ�ƽ�ĺ궨��*********************************



//third method 
#define LCM_RS_1 LPC_GPIO3->DATA |=(1<<2)     //RS�ӵ�p2.10������ߵ�ƽ
#define LCM_RS_0 LPC_GPIO3->DATA &=~(1<<2)    //RS�ӵ�10������͵�ƽ
#define LCM_RW_1 GPIOSetValue(PORT3,1,1); //RW�ӵ�9������ߵ�ƽ
#define LCM_RW_0 GPIOSetValue(PORT3,1,0); //RW�ӵ�9������͵�ƽ
#define LCM_EN_1 LPC_GPIO3->MASKED_ACCESS[1] = 0xFFF //EN�ӵ�8������ߵ�ƽ
#define LCM_EN_0 LPC_GPIO3->MASKED_ACCESS[1] = 0x000   //EN�ӵ�8������͵�ƽ



#define Busy 0x80         //æ�ź�
//*******************************n*1mS��ʱ�Ӻ���*******************************
void TIM16B0_delay_ms(uint16_t ms)
{
  LPC_TMR16B0->TCR = 0x02;  	//��λ��ʱ��
  LPC_TMR16B0->PR = 1000;  		//Ԥ��Ƶ��1000
  LPC_TMR16B0->MR0 = ms * 48;  	//��48Mhz�¹�����ƥ��ֵ
  LPC_TMR16B0->IR = 0x01;  		//����жϱ�־
  LPC_TMR16B0->MCR = 0x04; //MR0ƥ��ʱֹͣTC��PC��������TCR[0]���������ж�
  LPC_TMR16B0->TCR = 0x01;  	//������ʱ��
  while (LPC_TMR16B0->TCR & 0x01);  //�ȴ���ʱ����ʱʱ�䵽
}
//*******************************n*1uS��ʱ�Ӻ���******************************
void TIM16B0_delay_us(uint16_t us)
{
  LPC_TMR16B0->TCR = 0x02;  	//��λ��ʱ��
  LPC_TMR16B0->PR = 0x00;  		//Ԥ��Ƶ��0
  LPC_TMR16B0->MR0 = us * 48;  	//��48Mhz�¹�����ƥ��ֵ
  LPC_TMR16B0->IR = 0x01;  		//����жϱ�־
  LPC_TMR16B0->MCR = 0x04; //MR0ƥ��ʱֹͣTC��PC��������TCR[0]���������ж�
  LPC_TMR16B0->TCR = 0x01;  	//������ʱ��
  while (LPC_TMR16B0->TCR & 0x01);  	//�ȴ���ʱ����ʱʱ�䵽
}
//************************д���ݵ�LCD���ݶ˿��Ӻ���**************************
void WriteDataPort(uint8_t data)
{
	
	uint8_t cont = 0x80;
	uint8_t temp[8],i;
	
	GPIOSetValue(PORT1,9,0);	//����P2.8���0������LED1	
	GPIOSetValue(PORT1,10,0);	//����P2.8���0������LED1	
	GPIOSetValue(PORT1,11,0);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,3,0);	//����P2.8���0������LED1
	GPIOSetValue(PORT2,4,0);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,5,0);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,6,0);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,7,0);	//����P2.7����0
	
	for(i = 0; i < 8; i++)
  {
    if (cont & data)
      temp[i] = 1;
    else
      temp[i] = 0;
    data <<= 1;
  }
	
	GPIOSetValue(PORT1,9,temp[7]);	//����P2.8���0������LED1	
	GPIOSetValue(PORT1,10,temp[6]);	//����P2.8���0������LED1	
	GPIOSetValue(PORT1,11,temp[5]);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,3,temp[4]);	//����P2.8���0������LED1
	GPIOSetValue(PORT2,4,temp[3]);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,5,temp[2]);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,6,temp[1]);	//����P2.8���0������LED1	
	GPIOSetValue(PORT2,7,temp[0]);	//����P2.7����temp[0]
}
//************************��LCD���ݶ˿������Ӻ���****************************
uint8_t ReadDataPort(void)
{

	uint8_t dan[8];
  uint8_t temp=0,i;
	dan[0]=LPC_GPIO1->MASKED_ACCESS[512];      //is port  p2.0
	dan[1]=LPC_GPIO1->MASKED_ACCESS[1024];
	dan[2]=LPC_GPIO1->MASKED_ACCESS[2048];
	dan[3]=LPC_GPIO2->MASKED_ACCESS[8];
	dan[4]=LPC_GPIO2->MASKED_ACCESS[16];
	dan[5]=LPC_GPIO2->MASKED_ACCESS[32];
	dan[6]=LPC_GPIO2->MASKED_ACCESS[64];
	dan[7]=LPC_GPIO2->MASKED_ACCESS[128];      //�õ�p2.7��ֵ��dan[7]	
	for(i=0;i<8;i++)
	{
    temp >>= 1;
    if(dan[i])
    {
        temp |= 0x80;
    }
	}
  return temp;
}
//***************************���LCDæ�ź��Ӻ���*****************************
void WaitForEnable(void)
{
    uint8_t val;
    WriteDataPort(0xFF);        		//�����ߵ�ƽ����
    LCM_RS_0;             				//ѡ��ָ��Ĵ���
    LCM_RW_1;             			//ѡ��д��ʽ
    TIM16B0_delay_us(1);  			//��ʱһ΢�룬�ȴ��ȶ�
    LCM_EN_1;             			//ʹ�ܶ����ߵ�ƽ
    TIM16B0_delay_us(2);  			//��ʱ��΢�룬�ȴ��ȶ�

		GPIOSetDir(PORT1,9,0);     //����2.0Ϊ����
		GPIOSetDir(PORT1,10,0);
		GPIOSetDir(PORT1,11,0);
		GPIOSetDir(PORT2,3,0);
		GPIOSetDir(PORT2,4,0);
		GPIOSetDir(PORT2,5,0);
		GPIOSetDir(PORT2,6,0);
		GPIOSetDir(PORT2,7,0);

    val = ReadDataPort();             		//��ȡ����
    while(val&Busy)
      val = ReadDataPort();           		//��PIO2�ĵ�7��Ϊ1ʱ��ʾæ��ѭ�����
    LCM_EN_0;             			//æ�źŽ���������ʹ�ܶ˵�ƽ

		GPIOSetDir(PORT1,9,1);      //����2.0Ϊ���
		GPIOSetDir(PORT1,10,1);
		GPIOSetDir(PORT1,11,1);
		GPIOSetDir(PORT2,3,1);
		GPIOSetDir(PORT2,4,1);
		GPIOSetDir(PORT2,5,1);
		GPIOSetDir(PORT2,6,1);
		GPIOSetDir(PORT2,7,1);

}
//****************************д���LCD�Ӻ���****************************
void LcdWriteCommand(uint8_t CMD,uint8_t Attribc)
//д����CMD��LCD�У�ArribcΪ1ʱ���æ�źţ����򲻼��
{
    if(Attribc)
      WaitForEnable();      	//���æ�ź�
    LCM_RS_0;                 	//ѡ��ָ��Ĵ���
    LCM_RW_0;                 	//ѡ��д��ʽ
    TIM16B0_delay_us(1);            	//��ʱһ΢�룬�ȴ��ȶ�
    WriteDataPort(CMD);             	//�����������͵���������
    TIM16B0_delay_us(1);            	//��ʱһ΢�룬�ȴ��ȶ�
    LCM_EN_1;                 		//ʹ�ܶ����ߵ�ƽ
    TIM16B0_delay_us(2);            	//��ʱ��΢�룬�ȴ��ȶ�
    LCM_EN_0;                 		//����ʹ�ܶˣ�ִ��д�붯��
}
//****************************д���ݵ�LCD�Ӻ���****************************
void LcdWriteData(uint8_t dataW)      //д����dataW��LCD��
{
    WaitForEnable();        	//���æ�ź�
    LCM_RS_1;               	//ѡ�����ݼĴ���
    LCM_RW_0;               	//ѡ�����ʽ
    TIM16B0_delay_us(1);     //��ʱһ΢�룬�ȴ��ȶ�
    WriteDataPort(dataW);     //����ʾ�����͵���������
    TIM16B0_delay_us(1);     //��ʱһ΢�룬�ȴ��ȶ�
    LCM_EN_1;               	//ʹ�ܶ����ߵ�ƽ
    TIM16B0_delay_us(2);    	//��ʱ��΢�룬�ȴ��ȶ�
    LCM_EN_0;               	//����ʹ�ܶˣ�ִ��д�붯��
}
//*****************************LCD��ʼ���Ӻ���*****************************
void InitLcd(void) 
{
    LcdWriteCommand(0x38,0);      //8λ���ݷ�ʽ��˫����ʾ��5X7���Σ������æ�ź�
    TIM16B0_delay_ms(5);                //��ʱ5ms
    LcdWriteCommand(0x38,0); 
    TIM16B0_delay_ms(5);
    LcdWriteCommand(0x38,0); 
    TIM16B0_delay_ms(5);                //�ظ�����
    LcdWriteCommand(0x38,1);      //8λ���ݷ�ʽ��˫����ʾ��5X7���Σ����æ�ź�
    LcdWriteCommand(0x08,1);      //�ر���ʾ�����æ�ź�
    LcdWriteCommand(0x01,1);      //���������æ�ź�
    LcdWriteCommand(0x06,1);      //��ʾ����������ã����æ�ź�
    LcdWriteCommand(0x0C,1);      //����ʾ����겻��ʾ������˸�����æ�ź�
}
//***************************��ʾ��궨λ�Ӻ���****************************
void LocateXY(char posx,char posy)      //��λλ�õ���ַx��y��
{
    uint8_t temp;
    temp = posx & 0x0F;       	//���θ�4λ,�޶�x����ķ�ΧΪ0~15
    posy &= 0x01;           	//���θ�7λ,�޶�y����ķ�ΧΪ0~1
    if(posy) 
      temp |= 0x40;         //��Ҫ��ʾ���ǵڶ��У����ַ��+0x40����Ϊ�ڶ�����ʼ��ַΪ0x40
    temp |= 0x80;    //ָ����Ϊ��ַ��+0x80����ΪдDDRAMʱPIO2�ĵ�7�ź�Ϊ1����0x80��
    LcdWriteCommand(temp,1);    	//��tempд��LCD�У����æ�ź�
}
//**********************��ʾָ�������һ���ַ��Ӻ���************************
void DisplayOneChar(uint8_t x,uint8_t y,uint8_t Wdata) 
//��x��y�д���ʾ����Wdata�е�һ���ַ�
{
    LocateXY(x,y);          	//��λҪ��ʾ��λ��
    LcdWriteData(Wdata);    	//��Ҫ��ʾ������Wdataд��LCD
} 
//**********************��ʾָ�������һ���ַ��Ӻ���************************
void ePutstr(uint8_t x,uint8_t y,uint8_t const *ptr)    //��x��y�д���ʾptrָ����ַ���
{
    uint8_t i,j=0;
    while(ptr[j]>31)
      j++;                         //ptr[j]>31ʱΪASCII�룬j�ۼӣ�������ַ�������
    for(i=0;i<j;i++)
    {
      DisplayOneChar(x++,y,ptr[i]);       //��ʾ�����ַ���ͬʱx�������
      if(x==16)
        {
          x=0;
          y^=1;         //��ÿ����ʾ����16���ַ�ʱ���м�����ʾ
        }
    }
}
//*******************************������***********************************
int main(void) 
{
	GPIOInit();
	SystemInit();	  	 		//ϵͳ��ʼ��������ʹ��ʱ��
		
	GPIOSetDir(PORT3,0,1);			//����P2.8Ϊ�����LED1
	GPIOSetDir(PORT3,1,1);			//����P2.9Ϊ�����LED2
	GPIOSetDir(PORT3,2,1);			//����P3.4Ϊ�����
	
	GPIOSetValue(PORT3,0,1);	//����P2.8���0
	GPIOSetValue(PORT3,1,1);	//����P2.9���0
	GPIOSetValue(PORT3,2,1);	//����P3.4���0
	


	GPIOSetDir(PORT1,9,1);
	GPIOSetDir(PORT1,10,1);
	GPIOSetDir(PORT1,11,1);
	GPIOSetDir(PORT2,3,1);
	GPIOSetDir(PORT2,4,1);
	GPIOSetDir(PORT2,5,1);
	GPIOSetDir(PORT2,6,1);
	GPIOSetDir(PORT2,7,1);

	GPIOSetValue(PORT1,9																							,1);	//����P1.1���0������LED1
	GPIOSetValue(PORT1,10,1);	//����P1.1���0������LED1
	GPIOSetValue(PORT1,11,1);	//����P1.1���0������LED1
	GPIOSetValue(PORT2,3,1);	//����P1.1���0������LED1
	GPIOSetValue(PORT2,4,1);	//����P1.1���0������LED1
	GPIOSetValue(PORT2,5,1);	//����P1.1���0������LED1
	GPIOSetValue(PORT2,6,1);	//����P1.1���0������LED1
	GPIOSetValue(PORT2,7,1);	//����P1.1���0������LED1
	

  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);	//ʹ��CT16B0ʱ��
  InitLcd();                                 		//LCD��ʼ��
  ePutstr(0,0,str0);                   		//��һ���ַ���ʾ
  TIM16B0_delay_ms(5);        		//��ʱ5ms�ȴ���ʾ�ȶ�
  ePutstr(0,1,str1);                   		//�ڶ����ַ���ʾ
  while(1)
    {
         ;      //��ѭ��
    }
}
