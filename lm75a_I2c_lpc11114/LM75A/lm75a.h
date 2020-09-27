#ifndef __LM75A_H
#define __LM75A_H
 
#define LM75_ADDRESS			0x92


/*------------ע�⣺LM75A�ĵ�ַΪ��0x0000~0x07FF��������Խ�磩------- */
extern uint8_t LM75A_ReadOneByte(uint8_t ReadAddr);	//ָ����ַ��ȡһ���ֽ�
extern void LM75A_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);	//ָ����ַд��һ���ֽ�


extern void LM75A_Write(uint8_t WriteAddr,uint8_t *Buffer,uint8_t Num);	//��ָ����ַ��ʼд��ָ�����ȵ�����
extern void LM75A_Read(uint8_t ReadAddr,uint8_t *Buffer,uint8_t Num);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

extern uint8_t LM75A_Check(void);  //�������

#endif

