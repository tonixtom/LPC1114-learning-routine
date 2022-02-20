#include "lpc11xx.h"
#include "ssp.h"

/*****************************************/
/* �������ܣ�SPI1ͨ��                    */
/* ˵����    ����һ���ֽڣ�����һ���ֽ�  */
/*****************************************/
uint8_t SPI1_communication(uint8_t TxData)
{		
	while(((LPC_SSP1->SR)&(1<<4))==(1<<4));//æʱ�ȴ�,SR״̬�Ĵ���bit4 BSY:æʱΪ1
	LPC_SSP1->DR = TxData;                 //��Ҫ���͵���д��TxFIFO
	while(((LPC_SSP1->SR)&(1<<2))!=(1<<2));//�ȴ�������,SR״̬�Ĵ���bit2 RNE:����FIFO�ǿ�Ϊ1
	return(LPC_SSP1->DR);		    	   //�����յ�������
}

/*****************************************/
/* �������ܣ�SPI0ͨ��                    */
/* ˵����    ����һ���ֽڣ�����һ���ֽ�  */
/*****************************************/
uint8_t SPI0_communication(uint8_t TxData)
{		
	while(((LPC_SSP0->SR)&(1<<4))==(1<<4));//æʱ�ȴ�,SR״̬�Ĵ���bit4 BSY:æʱΪ1
	LPC_SSP0->DR = TxData;                 //��Ҫ���͵���д��TxFIFO
	while(((LPC_SSP0->SR)&(1<<2))!=(1<<2));//�ȴ�������,SR״̬�Ĵ���bit2 RNE:����FIFO�ǿ�Ϊ1
	return(LPC_SSP0->DR);		    	   //�����յ�������
}

/*****************************************/
/* �������ܣ�SPI1��ʼ��                  */
/* ˵����    û����SSEL1                 */
/*****************************************/
void SPI1_Init(void)
{
	uint8_t i,Clear=Clear;//Clear=Clear:�����������ʽ������������Waring:never used!	

	LPC_SYSCON->PRESETCTRL |= (0x1<<2);	   //��ֹLPC_SSP1��λ
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x1<<18);//����LPC_SSP1ʱ�� bit18
	LPC_SYSCON->SSP1CLKDIV = 0x06;		   //6��Ƶ��48/6=8Mhz
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ��(bit16)
	LPC_IOCON->PIO2_1 &= ~0x07;
	LPC_IOCON->PIO2_1 |= 0x02;		//��PIO2_1ѡ��ΪLPC_SSP CLK 
	LPC_IOCON->PIO2_2 &= ~0x07;	
	LPC_IOCON->PIO2_2 |= 0x02;		//��PIO2_2ѡ��ΪLPC_SSP MISO 
	LPC_IOCON->PIO2_3 &= ~0x07;	
	LPC_IOCON->PIO2_3 |= 0x02;		//��PIO2_3ѡ��ΪLPC_SSP MOSI 
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��(bit16)
	// 8λ���ݴ��䣬SPIģʽ, CPOL = 1, CPHA = 1,����ʱCLKΪ1��SCR = 0
	LPC_SSP1->CR0 = 0x01C7;	    
	// Ԥ��Ƶֵ��ע�⣺�������Ϊż�� 2~254�� 
	LPC_SSP1->CPSR = 0x04;
	LPC_SSP1->CR1 &= ~(1<<0);//LBM=0:����ģʽ
	LPC_SSP1->CR1 &= ~(1<<2);//MS=0:����ģʽ 
	LPC_SSP1->CR1 |=  (1<<1);//SSE=1:ʹ��SPI1
	//���RxFIFO��LPC1114�շ�����8֡FIFO,ÿ֡�ɷ���4~16λ����
	for ( i = 0; i < 8; i++ )
	{
	  	Clear = LPC_SSP1->DR;//�����ݼĴ���DR�����RxFIFO
	} 		 		  
}


/*****************************************/
/* �������ܣ�SPI0��ʼ��                  */
/* ˵����    û����SSEL0                 */
/*****************************************/
void SPI0_Init(void)
{
	uint8_t i,Clear=Clear;//Clear=Clear:�����������ʽ������������Waring:never used!	

	LPC_SYSCON->PRESETCTRL |= (0x1<<0);	   //��ֹLPC_SSP0��λ
	LPC_SYSCON->SYSAHBCLKCTRL |= (0x1<<11);//����LPC_SSP0ʱ�� bit11
	LPC_SYSCON->SSP0CLKDIV = 0x01;		   //��Ƶϵ��Ϊ1��ʹSPI0�������48Mhz
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ��(bit16)
	LPC_IOCON->SCK_LOC = 0x02;      //��SCK0���õ�PIO0_6����
	LPC_IOCON->PIO0_6 &= ~0x07;
	LPC_IOCON->PIO0_6 |= 0x02;		//��PIO0_6����ΪSSP CLK 
	LPC_IOCON->PIO0_8 &= ~0x07;	
	LPC_IOCON->PIO0_8 |= 0x01;		//��PIO0_8����ΪSSP MISO 
	LPC_IOCON->PIO0_9 &= ~0x07;	
	LPC_IOCON->PIO0_9 |= 0x01;		//��PIO0_9����ΪSSP MOSI 
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��(bit16)
	// 8λ���ݴ��䣬SPIģʽ, CPOL = 0, CPHA = 0,����ʱCLKΪ0����һ�������زɼ����ݣ�SCR = 0
	LPC_SSP0->CR0 = 0x0107;	    
	// Ԥ��Ƶֵ��ע�⣺����Ϊż�� 2~254�� 
	LPC_SSP0->CPSR = 0x02;
	LPC_SSP0->CR1 &= ~(1<<0);//LBM=0:����ģʽ
	LPC_SSP0->CR1 &= ~(1<<2);//MS=0:����ģʽ 
	LPC_SSP0->CR1 |=  (1<<1);//SSE=1:ʹ��SPI0
	//���RxFIFO��LPC1114�շ�����8֡FIFO,ÿ֡�ɷ���4~16λ����
	for ( i = 0; i < 8; i++ )
	{
	  	Clear = LPC_SSP0->DR;//�����ݼĴ���DR�����RxFIFO
	} 		 		  
}






