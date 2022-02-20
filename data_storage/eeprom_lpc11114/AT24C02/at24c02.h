#ifndef  __AT24C02_H
#define  __AT24C02_H
/*------------ע�⣺AT24C02�ĵ�ַΪ��0x00~0xFF��������Խ�磩------- */
extern uint8_t AT24C02_ReadOneByte(uint8_t ReadAddr);	//ָ����ַ��ȡһ���ֽ�
extern void AT24C02_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);	//ָ����ַд��һ���ֽ�
extern void AT24C02_Write(uint8_t WriteAddr,uint8_t *Buffer,uint16_t Num);	//��ָ����ַ��ʼд��ָ�����ȵ�����
extern void AT24C02_Read(uint8_t ReadAddr,uint8_t *Buffer,uint16_t Num);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

extern uint8_t AT24C02_Check(void);  //�������


#endif



