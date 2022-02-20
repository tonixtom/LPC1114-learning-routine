#ifndef  __AT24C02_H
#define  __AT24C02_H
/*------------注意：AT24C02的地址为（0x00~0xFF）（不可越界）------- */
extern uint8_t AT24C02_ReadOneByte(uint8_t ReadAddr);	//指定地址读取一个字节
extern void AT24C02_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);	//指定地址写入一个字节
extern void AT24C02_Write(uint8_t WriteAddr,uint8_t *Buffer,uint16_t Num);	//从指定地址开始写入指定长度的数据
extern void AT24C02_Read(uint8_t ReadAddr,uint8_t *Buffer,uint16_t Num);   	//从指定地址开始读出指定长度的数据

extern uint8_t AT24C02_Check(void);  //检查器件


#endif



