#include "lcd_1602.h"


//*****************************���ŵ�ƽ�ĺ궨��*********************************
#define LCM_RS_1 LPC_GPIO2->MASKED_ACCESS[1024] = 0xFFF//RS�ӵ�10������ߵ�ƽ
#define LCM_RS_0 LPC_GPIO2->MASKED_ACCESS[1024] = 0x000 //RS�ӵ�10������͵�ƽ
#define LCM_RW_1 LPC_GPIO2->MASKED_ACCESS[512] = 0xFFF //RW�ӵ�9������ߵ�ƽ
#define LCM_RW_0 LPC_GPIO2->MASKED_ACCESS[512] = 0x000 //RW�ӵ�9������͵�ƽ
#define LCM_EN_1 LPC_GPIO2->MASKED_ACCESS[256] = 0xFFF //EN�ӵ�8������ߵ�ƽ
#define LCM_EN_0 LPC_GPIO2->MASKED_ACCESS[256] = 0x000   //EN�ӵ�8������͵�ƽ
#define DataPort LPC_GPIO2->DATA          //PIO2Ϊ���ݶ˿�
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
  LPC_GPIO2->DATA &= 0xF00;    	//PIO2�ĵͰ�λ���㣬����λ���ֲ���
  LPC_GPIO2->DATA |= data;     	//��PIO2�ĵͰ�λд������
}
//************************��LCD���ݶ˿������Ӻ���****************************
uint8_t ReadDataPort(void)
{
  uint8_t temp;
  temp = LPC_GPIO2->DATA;    //��ȡPIO2�ĵͰ�λ����
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
    LPC_GPIO2->DIR = 0xF00;       	 //�ı������߷��������
    val = ReadDataPort();             		//��ȡ����
    while(val&Busy)
      val = ReadDataPort();           		//��PIO2�ĵ�7��Ϊ1ʱ��ʾæ��ѭ�����
    LCM_EN_0;             			//æ�źŽ���������ʹ�ܶ˵�ƽ
    LPC_GPIO2->DIR = 0xFFF;          	//�ı������߷�������
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



