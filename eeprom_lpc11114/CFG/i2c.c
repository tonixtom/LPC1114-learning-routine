#include "i2c.h"

/****************************************/
/* �������ܣ���ʼ��LPC1114 I2Cģ��      */
/* ��ڲ�����Mode :0 , ����ģʽ         */
/*                 1 , ����ģʽ         */
/****************************************/
void I2C_Init(uint8_t Mode)
{
	LPC_SYSCON->PRESETCTRL |= (1<<1); // De-asserted I2Cģ�飨������I2Cģ��֮ǰ���������λд1��
 	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<5); // ʹ��I2Cʱ��
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ��
	LPC_IOCON->PIO0_4 &= ~0x3F;	    
	LPC_IOCON->PIO0_4 |= 0x01;		// ��P0.4������Ϊ I2C SCL 
	LPC_IOCON->PIO0_5 &= ~0x3F;	
	LPC_IOCON->PIO0_5 |= 0x01;		// ��P0.5������Ϊ I2C SDA 
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ����IOCONʱ�� 
	if(Mode == 1)	// ����I2Cͨ�� (��Լ400KHz��������)
	{
		LPC_I2C->SCLH = 60; 
		LPC_I2C->SCLL = 65;  
	}
	else 	// ����I2Cͨ��	 (��Լ100KHz��������)
	{
		LPC_I2C->SCLH = 250; 
		LPC_I2C->SCLL = 250; 
	}
	LPC_I2C->CONCLR = 0xFF;  // �����б�־
	LPC_I2C->CONSET |= I2CONSET_I2EN;  // ʹ��I2C�ӿ�
}

/***************************************************/
/* �������ܣ�����ֹͣ�ź�                          */
/***************************************************/
void I2C_Stop(void)
{
   LPC_I2C->CONCLR = I2CONCLR_SIC;    // ��SI��־λ
   LPC_I2C->CONSET |= I2CONSET_STO; 	// ����ֹͣ�ź�
}

/***************************************************/
/* �������ܣ�I2C������������                       */
/* ��ڲ�����Ctrl : ����+��ַ�ֽ�                  */
/* ���ڲ�����0���ɹ�                               */
/*           1: ʧ��                               */
/***************************************************/
uint8_t I2C_Send_Ctrl(uint8_t CtrlAndAddr)
{
   	uint8_t res;

   	if(CtrlAndAddr & 1)    // ����Ƕ�����
   	   	res = 0x40; // 40H����ʼ�źźͶ������Ѿ�������ϣ������Ѿ����յ�ACK
   	else			   // �����д����
       	res = 0x18; // 18H����ʼ�źź�д�����Ѿ�������ϣ������Ѿ����յ�ACK
	// ���Ϳ�ʼ�ź�
   	LPC_I2C->CONCLR = 0xFF; // �����б�־λ
   	LPC_I2C->CONSET |= I2CONSET_I2EN | I2CONSET_STA;	// ʹ�ܷ��Ϳ�ʼ�ź�
   	while(!(LPC_I2C->CONSET & I2CONSET_SI));   // �ȴ���ʼ�źŷ������
	// ��������+��ַ�ֽ�
   	LPC_I2C->DAT = CtrlAndAddr;	 // ��Ҫ���͵��ֽڸ���DAT�Ĵ���
   	LPC_I2C->CONCLR = I2CONCLR_STAC | I2CONCLR_SIC; // �����ʼSTARTλ��SIλ 
   	while(!(LPC_I2C->CONSET & I2CONSET_SI));  // �ȴ����ݷ������
   	if(LPC_I2C->STAT != res)	  // �۲�STAT�Ĵ�����Ӧ��״̬���ж��Ƿ���ȷִ�ж���д����
   	{
      	I2C_Stop();		 // û��������񣬷���ֹͣ�źţ�����I2Cͨ��
      	return 1;			 // ����1������ʧ�ܣ�
   	}
   	return 0;			 // �����ȷִ�з���0
}
/***************************************************/
/* �������ܣ�I2C����һ�ֽ�����                     */
/* ��ڲ�����sebyte : Ҫ���͵��ֽ�                 */
/***************************************************/
void I2C_Send_Byte(uint8_t sebyte)
{
   LPC_I2C->DAT = sebyte;	  // ���ֽ�д��DAT�Ĵ���
   LPC_I2C->CONCLR = I2CONSET_SI;   // ���SI��־
   while(!(LPC_I2C->CONSET & I2CONSET_SI));  // �ȴ����ݷ������
}

/***************************************************/
/* �������ܣ�I2C����һ�ֽ�����                     */
/* ��ڲ�����rebyte : Ҫ���յ��ֽ�                 */
/***************************************************/
uint8_t I2C_Recieve_Byte(void)
{
	uint8_t rebyte;
	
	LPC_I2C->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC;  // ��AA��SI��־
	while(!(LPC_I2C->CONSET & I2CONSET_SI));  // �ȴ������������
	rebyte = (uint8_t)LPC_I2C->DAT;	// �ѽ��յ������ݸ���rebyte

	return rebyte;
}


