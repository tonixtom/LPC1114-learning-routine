#include "nxplpc11xx.h"
#include "ssp.h"

/*****************************************/
/* �������ܣ�SPI1ͨ��                    */
/* ˵����    ����һ���ֽڣ�����һ���ֽ�  */
/*****************************************/
uint8 SPI1_communication(uint8 TxData)
{		
	while(((SSP1->SR)&(1<<4))==(1<<4));//æʱ�ȴ�,SR״̬�Ĵ���bit4 BSY:æʱΪ1
	SSP1->DR = TxData;                 //��Ҫ���͵���д��TxFIFO
	while(((SSP1->SR)&(1<<2))!=(1<<2));//�ȴ�������,SR״̬�Ĵ���bit2 RNE:����FIFO�ǿ�Ϊ1
	return(SSP1->DR);		    	   //�����յ�������
}

/*****************************************/
/* �������ܣ�SPI0ͨ��                    */
/* ˵����    ����һ���ֽڣ�����һ���ֽ�  */
/*****************************************/
uint8 SPI0_communication(uint8 TxData)
{		
	while(((SSP0->SR)&(1<<4))==(1<<4));//æʱ�ȴ�,SR״̬�Ĵ���bit4 BSY:æʱΪ1
	SSP0->DR = TxData;                 //��Ҫ���͵���д��TxFIFO
	while(((SSP0->SR)&(1<<2))!=(1<<2));//�ȴ�������,SR״̬�Ĵ���bit2 RNE:����FIFO�ǿ�Ϊ1
	return(SSP0->DR);		    	   //�����յ�������
}

/*****************************************/
/* �������ܣ�SPI1��ʼ��                  */
/* ˵����    û����SSEL1                 */
/*****************************************/
void SPI1_Init(void)
{
	uint8 i,Clear=Clear;//Clear=Clear:�����������ʽ������������Waring:never used!	

	SYSCON->PRESETCTRL |= (0x1<<2);	   //��ֹSSP1��λ
	SYSCON->SYSAHBCLKCTRL |= (0x1<<18);//����SSP1ʱ�� bit18
	SYSCON->SSP1CLKDIV =  0x01;		   //��Ƶϵ��Ϊ1��ʹSPI1�������48Mhz

	SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ��(bit16)
	IOCON->PIO2_1 &= ~0x07;
	IOCON->PIO2_1 |= 0x02;		//��PIO2_1ѡ��ΪSSP CLK 
	IOCON->PIO2_2 &= ~0x07;	
	IOCON->PIO2_2 |= 0x02;		//��PIO2_2ѡ��ΪSSP MISO 
	IOCON->PIO2_3 &= ~0x07;	
	IOCON->PIO2_3 |= 0x02;		//��PIO2_3ѡ��ΪSSP MOSI 
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��(bit16)

	// 8λ���ݴ��䣬SPIģʽ, CPOL = 0, CPHA = 0,����ʱCLIΪ0����һ�������زɼ����ݣ�SCR = 0
	SSP1->CR0 = 0x0107;	    
	// Ԥ��ƵֵΪ254��ע�⣺������СΪ2�����ұ���Ϊż�� 2~254�� 
	SSP1->CPSR = 0x02;
	SSP1->CR1 &= ~(1<<0);//LBM=0:����ģʽ
	SSP1->CR1 &= ~(1<<2);//MS=0:����ģʽ 
	SSP1->CR1 |=  (1<<1);//SSE=1:ʹ��SPI1
	//���RxFIFO��LPC1114�շ�����8֡FIFO,ÿ֡�ɷ���4~16λ����
	for ( i = 0; i < 8; i++ )
	{
	  	Clear = SSP1->DR;//�����ݼĴ���DR�����RxFIFO
	} 		 		  
}


/*****************************************/
/* �������ܣ�SPI0��ʼ��                  */
/* ˵����    û����SSEL0                 */
/*****************************************/
void SPI0_Init(void)
{
	uint8 i,Clear=Clear;//Clear=Clear:�����������ʽ������������Waring:never used!	

	SYSCON->PRESETCTRL |= (0x1<<0);	   //��ֹSSP0��λ
	SYSCON->SYSAHBCLKCTRL |= (0x1<<11);//����SSP0ʱ�� bit11
	SYSCON->SSP0CLKDIV = 0x06;		   //6��Ƶ��48/6=8Mhz

	SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ��(bit16)
	IOCON->SCK_LOC = 0x02;      //��SCK0���õ�PIO0_6����

	IOCON->PIO0_6 &= ~0x07;
	IOCON->PIO0_6 |= 0x02;		//��PIO0_6����ΪSSP CLK 
	IOCON->PIO0_8 &= ~0x07;	
	IOCON->PIO0_8 |= 0x01;		//��PIO0_8����ΪSSP MISO 
	IOCON->PIO0_9 &= ~0x07;	
	IOCON->PIO0_9 |= 0x01;		//��PIO0_9����ΪSSP MOSI 
	SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��(bit16)
	
	// 8λ���ݴ��䣬SPIģʽ, CPOL = 0, CPHA = 0,����ʱCLKΪ0����һ�������زɼ����ݣ�SCR = 0
	SSP0->CR0 = 0x0107;	    
	// Ԥ��Ƶֵ��ע�⣺����Ϊż�� 2~254�� 
	SSP0->CPSR = 0x02;
	SSP0->CR1 &= ~(1<<0);//LBM=0:����ģʽ
	SSP0->CR1 &= ~(1<<2);//MS=0:����ģʽ 
	SSP0->CR1 |=  (1<<1);//SSE=1:ʹ��SPI0
	//���RxFIFO��LPC1114�շ�����8֡FIFO,ÿ֡�ɷ���4~16λ����
	for ( i = 0; i < 8; i++ )
	{
	  	Clear = SSP0->DR;//�����ݼĴ���DR�����RxFIFO
	} 		 		  
}






