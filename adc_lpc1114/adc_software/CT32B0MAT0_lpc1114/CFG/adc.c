#include "lpc11xx.h"
#include "adc.h"


/*****************************************/
/* �������ƣ���ʼ��ADC��                 */
/*****************************************/
void ADC_Init(uint8_t Channel)
{
	if(Channel>7) return;
	LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);        // ADCģ���ϵ�
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);     // ʹ��ADCʱ��
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);     // ʹ��IOCONʱ��
	switch(Channel)
	{
		case 0: // ͨ��0���� set channel 0
			LPC_IOCON->R_PIO0_11 &= ~0x07;              // 
			LPC_IOCON->R_PIO0_11 |= 0x02;               // ��P0.11��������ΪAD0����
			LPC_IOCON->R_PIO0_11 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->R_PIO0_11 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		case 1:  // ͨ��1���� set channel 1
			LPC_IOCON->R_PIO1_0 &= ~0x07;              // 
			LPC_IOCON->R_PIO1_0 |= 0x02;               // ��P1.0��������ΪAD1����
			LPC_IOCON->R_PIO1_0 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->R_PIO1_0 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		case 2:  // ͨ��2���� set channel 2
			LPC_IOCON->R_PIO1_1 &= ~0x07;              // 
			LPC_IOCON->R_PIO1_1 |= 0x02;               // ��P1.1��������ΪAD2����
			LPC_IOCON->R_PIO1_1 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->R_PIO1_1 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		case 3:  // ͨ��3���� set channel 3
			LPC_IOCON->R_PIO1_2 &= ~0x07;              // 
			LPC_IOCON->R_PIO1_2 |= 0x02;               // ��P1.2��������ΪAD3����
			LPC_IOCON->R_PIO1_2 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->R_PIO1_2 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		case 4:  // ͨ��4���� set channel 4
			LPC_IOCON->SWDIO_PIO1_3 &= ~0x07;              // 
			LPC_IOCON->SWDIO_PIO1_3 |= 0x02;               // ��P1.3��������ΪAD4����
			LPC_IOCON->SWDIO_PIO1_3 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->SWDIO_PIO1_3 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		case 5:  // ͨ��5���� set channel 5
			LPC_IOCON->PIO1_4 &= ~0x07;              // 
			LPC_IOCON->PIO1_4 |= 0x01;               // ��P1.4��������ΪAD5����
			LPC_IOCON->PIO1_4 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->PIO1_4 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		case 6:  // ͨ��6���� set channel 6
			LPC_IOCON->PIO1_10 &= ~0x07;              // 
			LPC_IOCON->PIO1_10 |= 0x01;               // ��P1.10��������ΪAD6����
			LPC_IOCON->PIO1_10 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->PIO1_10 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		case 7:  // ͨ��7���� set channel 7
			LPC_IOCON->PIO1_11 &= ~0x07;              // 
			LPC_IOCON->PIO1_11 |= 0x01;               // ��P1.11��������ΪAD7����
			LPC_IOCON->PIO1_11 &= ~(3<<3) ;           // ȥ����������������
			LPC_IOCON->PIO1_11 &= ~(1<<7) ;           // ģ������ģʽ
			break;
		default:break;
	}
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);    // �ر�IOCONʱ��
	LPC_ADC->CR = (1<<Channel)|                /* bit7:bit0   ѡ��ͨ��Channel*/
										(24<<8)|                     /* bit15:bit8  �Ѳ���ʱ��Ƶ������Ϊ2MHz 50/(24+1)*/
	                  (0x4<<24);                    /* CT32B0MAT0����ת�� */
}

/********************************************/
/* �������ܣ���ȡ��ѹֵ��AD7��              */
/* ���ڲ�����adc_value, �����ĵ�ѹֵ        */
/********************************************/
uint32_t ADC_Read(uint8_t Channel)
{
	uint32_t adc_value=0;

	while((LPC_ADC->DR[Channel]&0x80000000)==0);
	adc_value = ((LPC_ADC->DR[Channel]>>6)&0x3FF);		
	adc_value = (adc_value*Vref)/1024; // ת��Ϊ�����ĵ�ѹֵ

	return adc_value;	  // ���ؽ��
}

void TIM32B0_MAT_Init(uint16_t cycle_ms)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);	//ʹ��TIM32B0ʱ��
	LPC_TMR32B0->TCR = 0x02;		  //��λ��ʱ����bit1��д1��λ��
	LPC_TMR32B0->PR  = SystemCoreClock/1000-1;		  //1ms TC+1
	LPC_TMR32B0->MR0 = cycle_ms;//
	LPC_TMR32B0->IR  = 0x01;		  //MR0�жϸ�λ��bit0:MR0, bit1:MR1, bit2:MR2, bit3:MR3, bit4:CP0��
	LPC_TMR32B0->MCR = 0x02;		  //MR0�жϲ���ʱ��λTC
	LPC_TMR32B0->EMR = 0x30;		  //MR0��PC���ʱ��MAT0���ŷ�ת��ƽ
	LPC_TMR32B0->TCR = 0x01;		  //������ʱ����TCR[0]=1;
}


//////////////////////////////////////////////////////////



