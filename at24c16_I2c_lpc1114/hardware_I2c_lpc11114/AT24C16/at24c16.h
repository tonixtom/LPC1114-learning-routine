#ifndef __AT24C16_H
#define __AT24C16_H
 
					  
/*------------ע�⣺AT24C16�ĵ�ַΪ��0x0000~0x07FF��������Խ�磩------- */
extern uint8_t AT24C16_ReadOneByte(uint16_t ReadAddr);	//ָ����ַ��ȡһ���ֽ�
extern void AT24C16_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);	//ָ����ַд��һ���ֽ�
extern void AT24C16_Write(uint16_t WriteAddr,uint8_t *Buffer,uint16_t Num);	//��ָ����ַ��ʼд��ָ�����ȵ�����
extern void AT24C16_Read(uint16_t ReadAddr,uint8_t *Buffer,uint16_t Num);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

extern uint8_t AT24C16_Check(void);  //�������

#endif

