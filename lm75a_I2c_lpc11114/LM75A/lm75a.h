#ifndef __LM75A_H
#define __LM75A_H
 
#define LM75_ADDRESS			0x92


/*------------注意：LM75A的地址为（0x0000~0x07FF）（不可越界）------- */
extern uint8_t LM75A_ReadOneByte(uint8_t ReadAddr);	//指定地址读取一个字节
extern void LM75A_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);	//指定地址写入一个字节


extern void LM75A_Write(uint8_t WriteAddr,uint8_t *Buffer,uint8_t Num);	//从指定地址开始写入指定长度的数据
extern void LM75A_Read(uint8_t ReadAddr,uint8_t *Buffer,uint8_t Num);   	//从指定地址开始读出指定长度的数据

extern uint8_t LM75A_Check(void);  //检查器件

#endif

