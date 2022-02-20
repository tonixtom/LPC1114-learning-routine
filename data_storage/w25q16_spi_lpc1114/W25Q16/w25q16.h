#ifndef __W25Q16_H
#define __W25Q16_H			    
#include "lpc11xx.h" 

#define	F_CS_High  LPC_GPIO0->DATA|=(1<<7) 	  // F_CS = 1;
#define F_CS_Low   LPC_GPIO0->DATA&=~(1<<7)	  // F_CS = 0;
#define GBK_EN			 
////////////////////////////////////////////////////////////////////////////
//W25Q16��д
#define FLASH_ID 0XEF14
//ָ���
#define W25Q_WriteEnable		0x06 
#define W25Q_WriteDisable		0x04 
#define W25Q_ReadStatusReg		0x05 
#define W25Q_WriteStatusReg		0x01 
#define W25Q_ReadData			0x03 
#define W25Q_FastReadData		0x0B 
#define W25Q_FastReadDual		0x3B 
#define W25Q_PageProgram		0x02 
#define W25Q_BlockErase			0xD8 
#define W25Q_SectorErase		0x20 
#define W25Q_ChipErase			0xC7 
#define W25Q_PowerDown			0xB9 
#define W25Q_ReleasePowerDown	0xAB 
#define W25Q_DeviceID			0xAB 
#define W25Q_ManufactDeviceID	0x90 
#define W25Q_JedecDeviceID		0x9F 

extern void W25Q16_Init(void);		// ��ʼ��W25Q16
extern uint16_t W25Q16_ReadID(void);  //��ȡW25Q16 ID��
extern uint8_t W25Q16_ReadSR(void);    //��ȡ״̬�Ĵ��� 
extern void W25Q16_Write_SR(uint8_t sr); //д״̬�Ĵ���
extern void W25Q16_Write_Enable(void);  //дʹ�� 
extern void W25Q16_Write_Disable(void);	//д����
extern void W25Q16_Read(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum);  //��ȡW25Q16
extern void W25Q16_Write_Page(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum); //дһҳW25Q16
extern void W25Q16_Write(uint8_t* Buffer,uint32_t Addr,uint16_t NumByte);//д��ҳW25Q16
extern void W25Q16_Erase_Chip(void);   //��Ƭ����
extern void W25Q16_Erase_Sector(uint32_t Dst_Addr);//��������
extern void W25Q16_Erase_Block(uint32_t Bst_Addr); // ��������
extern void W25Q16_Wait_Busy(void);           //�ȴ�����


#endif
















