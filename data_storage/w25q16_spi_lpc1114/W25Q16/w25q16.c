/*************************************************************/
//  W25Q16 ����32��BLOCK,512��SECTOR      
//         BLOCK��С:64K    SECTOR��С��4K    
//         һ��2M�ֽ�,��2048K�ֽ�  16M����
//  16���Ʊ�ʾ���Ĵ洢��Χ��0x000000~0x1FFFFF                 
/*************************************************************/
#include "w25q16.h" 
#include "ssp.h"
/*****************************************/
/* �������ܣ� ��ʼ��W25Q16�Ŀ���IO��     */
/* ע    ��:  ��MINI LPC1114������������ */
/*            ����������SPI0�ڣ�����Ϊ�� */
/*            ����SPI0�ڵ��ظ���ʼ������ */
/*            �������������뷽ʽ��       */
/*****************************************/
void W25Q16_Init(void)
{
	// ����F_CS����
	LPC_GPIO0->DIR |= (1<<7);  // ��P0.7������Ϊ���
	LPC_GPIO0->DATA |= (1<<7); // F_CS = 1;
#ifndef SSP0INIT		   // ���û�г�ʼ����SPI0
	SPI0_Init();		   // ��ʼ��SPI0
#define SSP0INIT		   // ���߱������Ѿ���ʼ����SPI0
#endif
}  

/******************************************************/
/* �������ܣ���W25Q16��״̬�Ĵ���                     */
/* ���ڲ�����8λW25Q16��״ֵ̬                        */
/******************************************************/
uint8_t W25Q16_ReadSR(void)   
{  
	uint8_t byte=0;   

	F_CS_Low;   //ʹ������   
	SPI0_communication(W25Q_ReadStatusReg);  //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI0_communication(0Xff);  //��ȡһ���ֽ�  
	F_CS_High;  //ȡ��Ƭѡ
	     
	return byte;   
} 

/******************************************************/
/* �������ܣ�дW25Q16��״̬�Ĵ���                     */
/* ��ڲ�����8λ״̬�Ĵ���ֵ                          */
/******************************************************/
void W25Q16_Write_SR(uint8_t sr)   
{   
	F_CS_Low;                            //ʹ������   
	SPI0_communication(W25Q_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	SPI0_communication(sr);               //д��һ���ֽ�  
	F_CS_High;                            //ȡ��Ƭѡ     	      
}   

/*******************************************************/
/* �������ܣ�W25Q16дʹ��                           */
/*******************************************************/  
void W25Q16_Write_Enable(void)   
{
	F_CS_Low;                            //ʹ������   
  SPI0_communication(W25Q_WriteEnable);      //����дʹ��  
	F_CS_High;                            //ȡ��Ƭѡ     	      
} 
/*******************************************************/
/* �������ܣ�W25Q16д����                           */
/*******************************************************/ 
void W25Q16_Write_Disable(void)   
{  
	F_CS_Low;                            //ʹ������   
  SPI0_communication(W25Q_WriteDisable);     //����д��ָֹ��    
	F_CS_High;                            //ȡ��Ƭѡ     	      
}
/*******************************************************/
/* �������ܣ���ȡW25Q16��ID��                          */
/* ���ڲ�����16λ��ֵ��0xEF14(ʮ���ƣ�61204)           */
/*******************************************************/  			    
uint16_t W25Q16_ReadID(void)
{
	uint16_t Temp = 0;	  
	F_CS_Low;				    
	SPI0_communication(0x90);//���Ͷ�ȡID����	    
	SPI0_communication(0x00); 	    
	SPI0_communication(0x00); 	    
	SPI0_communication(0x00); 	 			   
	Temp|=SPI0_communication(0xFF)<<8;  
	Temp|=SPI0_communication(0xFF);	 
	F_CS_High;				    
	return Temp;
}   		    

/********************************************************/
/* �������ܣ���ȡW25Q16����                             */
/* ��ڲ�����Buffer:�������ݺ�ŵ�������                */
/*           Addr:��ʼ��ȡ�ĵ�ַ(24bit)                 */
/*           ByteNum:Ҫ��ȡ���ֽ���(���65535)          */
/********************************************************/
void W25Q16_Read(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum)   
{ 
 	uint16_t i;    							
						    
	F_CS_Low;   //ʹ������   
    SPI0_communication(W25Q_ReadData);         //���Ͷ�ȡ����   
    SPI0_communication((uint8_t)((Addr)>>16));  //����24bit��ַ    
    SPI0_communication((uint8_t)((Addr)>>8));   
    SPI0_communication((uint8_t)Addr);   
    for(i=0;i<ByteNum;i++)
	{ 
        Buffer[i]=SPI0_communication(0XFF);   //ѭ������  
    }
	F_CS_High;  //ȡ��Ƭѡ     	      
}  

/********************************************************/
/* �������ܣ���W25Q16д��һҳ����                       */
/* ��ڲ�����Buffer:�������Ž�Ҫд��W25Q16������      */
/*           Addr:��ʼд��ĵ�ַ(24bit)                 */
/*           ByteNum:Ҫд����ֽ���(���256)            */
/* ע    �⣺���д��256���ֽڣ����Ҳ��ܳ�����ҳ��ʣ����*/
/*           ���������򽫻Ḳ�Ǹ�ҳǰ������ݡ�         */
/********************************************************/	 
void W25Q16_Write_Page(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum)
{
 	uint16_t i;  
    W25Q16_Write_Enable();  // ����дʹ������ 
	F_CS_Low;   //ʹ��SPIͨ��   
    SPI0_communication(W25Q_PageProgram);  //����дҳ����   
    SPI0_communication((uint8_t)((Addr)>>16)); //����24bit��ַ    
    SPI0_communication((uint8_t)((Addr)>>8));   
    SPI0_communication((uint8_t)Addr);   
    for(i=0;i<ByteNum;i++)SPI0_communication(Buffer[i]);//ѭ��д��  
	F_CS_High;  // ����SPIͨ�� 
	W25Q16_Wait_Busy();  //�ȴ�д�����
} 

/********************************************************/
/* �������ܣ���W25Q16д������                           */
/* ��ڲ�����Buffer:�������Ž�Ҫд��W25Q16������      */
/*           Addr:��ʼд��ĵ�ַ(24bit)                 */
/*           ByteNum:Ҫд����ֽ���(���65536)          */
/* ע    �⣺����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF�� */
/*           ���Ѿ��������������򽫻��ڷ�0XFF��д��ʧ�� */
/********************************************************/	
void W25Q16_Write(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum)   
{ 			 		 
	uint16_t pageremain;
		   
	pageremain=256-Addr%256; //��ҳʣ����ֽ���		 	    
	if(ByteNum<=pageremain)pageremain=ByteNum;//������256���ֽ�
	while(1)
	{	   
		W25Q16_Write_Page(Buffer, Addr, pageremain);
		if(ByteNum==pageremain)break;//д�������
	 	else //ByteNum>pageremain
		{
			Buffer+=pageremain;
			Addr+=pageremain;	

			ByteNum-=pageremain;	 //��ȥ�Ѿ�д���˵��ֽ���
			if(ByteNum>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=ByteNum; //����256���ֽ���
		}
	};	    
} 
 		   

/**********************************************/
/* �������ܣ�������ƬW25Q16                   */
/* ˵    ����ʵ����MINI LPC1114������������   */
/*           ����ʱ��Ϊ10s                    */
/**********************************************/
void W25Q16_Erase_Chip(void)   
{                                             
    W25Q16_Write_Enable();                  //SET WEL 
    W25Q16_Wait_Busy();   
  	F_CS_Low;                            //ʹ������   
    SPI0_communication(W25Q_ChipErase);        //����Ƭ��������  
	F_CS_High;                            //ȡ��Ƭѡ     	      
	W25Q16_Wait_Busy();   				   //�ȴ�оƬ��������
}   

/**********************************************/
/* �������ܣ�����W25Q16һ������ (4K)          */
/* ��ڲ�����Dst_Addr:������ַ��0~511��       */
/**********************************************/
void W25Q16_Erase_Sector(uint32_t Dst_Addr)   
{   
	Dst_Addr*=4096;

    W25Q16_Write_Enable();   // дʹ�� 	 
    W25Q16_Wait_Busy();   
  	F_CS_Low;     // ʹ��SPIͨ��   
    SPI0_communication(W25Q_SectorErase);      //������������ָ�� 
    SPI0_communication((uint8_t)((Dst_Addr)>>16));  //����24bit��ַ    
    SPI0_communication((uint8_t)((Dst_Addr)>>8));   
    SPI0_communication((uint8_t)Dst_Addr);  
	F_CS_High;    // ����SPIͨ��     	      
    W25Q16_Wait_Busy(); //�ȴ��������
} 
/**********************************************/
/* �������ܣ�����W25Q16һ��������64K��        */
/* ��ڲ�����Bst_Addr:������ַ��0~31��        */
/**********************************************/
void W25Q16_Erase_Block(uint32_t Bst_Addr)   
{   
	Bst_Addr*=65536;

    W25Q16_Write_Enable();   // дʹ�� 	 
    W25Q16_Wait_Busy();   
  	F_CS_Low;     // ʹ��SPIͨ��   
    SPI0_communication(W25Q_BlockErase);      //���Ϳ�������ָ�� 
    SPI0_communication((uint8_t)((Bst_Addr)>>16));  //����24bit��ַ    
    SPI0_communication((uint8_t)((Bst_Addr)>>8));   
    SPI0_communication((uint8_t)Bst_Addr);  
	F_CS_High;    // ����SPIͨ��     	      
    W25Q16_Wait_Busy(); //�ȴ��������
}   
/**********************************************/
/* �������ܣ��ȴ�����                         */
/**********************************************/
void W25Q16_Wait_Busy(void)   
{   
	while ((W25Q16_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  




























