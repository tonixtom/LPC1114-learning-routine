#ifndef   __NXPLPC11XX_UART_H__
#define   __NXPLPC11XX_UART_H__

extern uint8_t Recived_data; // �����ֽ�

extern void UART_Init(uint32_t baudrate);  // ��ʼ������
extern uint8_t UART_recive(void);   // ���ڽ����ֽ�����
extern void UART_send_byte(uint8_t byte); // ���ڷ����ֽ�����
extern void UART_send(char *Buffer, uint32_t Length); // ���ڷ�����������

#endif




