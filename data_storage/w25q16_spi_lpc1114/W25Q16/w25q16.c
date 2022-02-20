/*************************************************************/
//  W25Q16 共有32个BLOCK,512个SECTOR      
//         BLOCK大小:64K    SECTOR大小：4K    
//         一共2M字节,即2048K字节  16M比特
//  16进制表示它的存储范围：0x000000~0x1FFFFF                 
/*************************************************************/
#include "w25q16.h" 
#include "ssp.h"
/*****************************************/
/* 函数功能： 初始化W25Q16的控制IO口     */
/* 注    意:  在MINI LPC1114开发板上有三 */
/*            个器件共享SPI0口，所以为了 */
/*            避免SPI0口的重复初始化，采 */
/*            用如下条件编译方式。       */
/*****************************************/
void W25Q16_Init(void)
{
	// 设置F_CS引脚
	LPC_GPIO0->DIR |= (1<<7);  // 把P0.7脚设置为输出
	LPC_GPIO0->DATA |= (1<<7); // F_CS = 1;
#ifndef SSP0INIT		   // 如果没有初始化过SPI0
	SPI0_Init();		   // 初始化SPI0
#define SSP0INIT		   // 告诉编译器已经初始化过SPI0
#endif
}  

/******************************************************/
/* 函数功能：读W25Q16的状态寄存器                     */
/* 出口参数：8位W25Q16的状态值                        */
/******************************************************/
uint8_t W25Q16_ReadSR(void)   
{  
	uint8_t byte=0;   

	F_CS_Low;   //使能器件   
	SPI0_communication(W25Q_ReadStatusReg);  //发送读取状态寄存器命令    
	byte=SPI0_communication(0Xff);  //读取一个字节  
	F_CS_High;  //取消片选
	     
	return byte;   
} 

/******************************************************/
/* 函数功能：写W25Q16的状态寄存器                     */
/* 入口参数：8位状态寄存器值                          */
/******************************************************/
void W25Q16_Write_SR(uint8_t sr)   
{   
	F_CS_Low;                            //使能器件   
	SPI0_communication(W25Q_WriteStatusReg);   //发送写取状态寄存器命令    
	SPI0_communication(sr);               //写入一个字节  
	F_CS_High;                            //取消片选     	      
}   

/*******************************************************/
/* 函数功能：W25Q16写使能                           */
/*******************************************************/  
void W25Q16_Write_Enable(void)   
{
	F_CS_Low;                            //使能器件   
  SPI0_communication(W25Q_WriteEnable);      //发送写使能  
	F_CS_High;                            //取消片选     	      
} 
/*******************************************************/
/* 函数功能：W25Q16写禁能                           */
/*******************************************************/ 
void W25Q16_Write_Disable(void)   
{  
	F_CS_Low;                            //使能器件   
  SPI0_communication(W25Q_WriteDisable);     //发送写禁止指令    
	F_CS_High;                            //取消片选     	      
}
/*******************************************************/
/* 函数功能：读取W25Q16的ID号                          */
/* 出口参数：16位定值：0xEF14(十进制：61204)           */
/*******************************************************/  			    
uint16_t W25Q16_ReadID(void)
{
	uint16_t Temp = 0;	  
	F_CS_Low;				    
	SPI0_communication(0x90);//发送读取ID命令	    
	SPI0_communication(0x00); 	    
	SPI0_communication(0x00); 	    
	SPI0_communication(0x00); 	 			   
	Temp|=SPI0_communication(0xFF)<<8;  
	Temp|=SPI0_communication(0xFF);	 
	F_CS_High;				    
	return Temp;
}   		    

/********************************************************/
/* 函数功能：读取W25Q16数据                             */
/* 入口参数：Buffer:读出数据后放到此数组                */
/*           Addr:开始读取的地址(24bit)                 */
/*           ByteNum:要读取的字节数(最大65535)          */
/********************************************************/
void W25Q16_Read(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum)   
{ 
 	uint16_t i;    							
						    
	F_CS_Low;   //使能器件   
    SPI0_communication(W25Q_ReadData);         //发送读取命令   
    SPI0_communication((uint8_t)((Addr)>>16));  //发送24bit地址    
    SPI0_communication((uint8_t)((Addr)>>8));   
    SPI0_communication((uint8_t)Addr);   
    for(i=0;i<ByteNum;i++)
	{ 
        Buffer[i]=SPI0_communication(0XFF);   //循环读数  
    }
	F_CS_High;  //取消片选     	      
}  

/********************************************************/
/* 函数功能：给W25Q16写入一页数据                       */
/* 入口参数：Buffer:此数组存放将要写入W25Q16的数据      */
/*           Addr:开始写入的地址(24bit)                 */
/*           ByteNum:要写入的字节数(最大256)            */
/* 注    意：最多写入256个字节，而且不能超过该页的剩余字*/
/*           节数，否则将会覆盖该页前面的数据。         */
/********************************************************/	 
void W25Q16_Write_Page(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum)
{
 	uint16_t i;  
    W25Q16_Write_Enable();  // 发送写使能命令 
	F_CS_Low;   //使能SPI通信   
    SPI0_communication(W25Q_PageProgram);  //发送写页命令   
    SPI0_communication((uint8_t)((Addr)>>16)); //发送24bit地址    
    SPI0_communication((uint8_t)((Addr)>>8));   
    SPI0_communication((uint8_t)Addr);   
    for(i=0;i<ByteNum;i++)SPI0_communication(Buffer[i]);//循环写数  
	F_CS_High;  // 禁能SPI通信 
	W25Q16_Wait_Busy();  //等待写入结束
} 

/********************************************************/
/* 函数功能：给W25Q16写入数据                           */
/* 入口参数：Buffer:此数组存放将要写入W25Q16的数据      */
/*           Addr:开始写入的地址(24bit)                 */
/*           ByteNum:要写入的字节数(最大65536)          */
/* 注    意：必须确保所写的地址范围内的数据全部为0XFF， */
/*           即已经被擦除过，否则将会在非0XFF处写入失败 */
/********************************************************/	
void W25Q16_Write(uint8_t* Buffer,uint32_t Addr,uint16_t ByteNum)   
{ 			 		 
	uint16_t pageremain;
		   
	pageremain=256-Addr%256; //单页剩余的字节数		 	    
	if(ByteNum<=pageremain)pageremain=ByteNum;//不大于256个字节
	while(1)
	{	   
		W25Q16_Write_Page(Buffer, Addr, pageremain);
		if(ByteNum==pageremain)break;//写入结束了
	 	else //ByteNum>pageremain
		{
			Buffer+=pageremain;
			Addr+=pageremain;	

			ByteNum-=pageremain;	 //减去已经写入了的字节数
			if(ByteNum>256)pageremain=256; //一次可以写入256个字节
			else pageremain=ByteNum; //不够256个字节了
		}
	};	    
} 
 		   

/**********************************************/
/* 函数功能；擦除整片W25Q16                   */
/* 说    明：实测在MINI LPC1114开发板上所用   */
/*           擦除时间为10s                    */
/**********************************************/
void W25Q16_Erase_Chip(void)   
{                                             
    W25Q16_Write_Enable();                  //SET WEL 
    W25Q16_Wait_Busy();   
  	F_CS_Low;                            //使能器件   
    SPI0_communication(W25Q_ChipErase);        //发送片擦除命令  
	F_CS_High;                            //取消片选     	      
	W25Q16_Wait_Busy();   				   //等待芯片擦除结束
}   

/**********************************************/
/* 函数功能；擦除W25Q16一个扇区 (4K)          */
/* 入口参数：Dst_Addr:扇区地址（0~511）       */
/**********************************************/
void W25Q16_Erase_Sector(uint32_t Dst_Addr)   
{   
	Dst_Addr*=4096;

    W25Q16_Write_Enable();   // 写使能 	 
    W25Q16_Wait_Busy();   
  	F_CS_Low;     // 使能SPI通信   
    SPI0_communication(W25Q_SectorErase);      //发送扇区擦除指令 
    SPI0_communication((uint8_t)((Dst_Addr)>>16));  //发送24bit地址    
    SPI0_communication((uint8_t)((Dst_Addr)>>8));   
    SPI0_communication((uint8_t)Dst_Addr);  
	F_CS_High;    // 禁能SPI通信     	      
    W25Q16_Wait_Busy(); //等待擦除完成
} 
/**********************************************/
/* 函数功能；擦除W25Q16一个块区（64K）        */
/* 入口参数：Bst_Addr:块区地址（0~31）        */
/**********************************************/
void W25Q16_Erase_Block(uint32_t Bst_Addr)   
{   
	Bst_Addr*=65536;

    W25Q16_Write_Enable();   // 写使能 	 
    W25Q16_Wait_Busy();   
  	F_CS_Low;     // 使能SPI通信   
    SPI0_communication(W25Q_BlockErase);      //发送块区擦除指令 
    SPI0_communication((uint8_t)((Bst_Addr)>>16));  //发送24bit地址    
    SPI0_communication((uint8_t)((Bst_Addr)>>8));   
    SPI0_communication((uint8_t)Bst_Addr);  
	F_CS_High;    // 禁能SPI通信     	      
    W25Q16_Wait_Busy(); //等待擦除完成
}   
/**********************************************/
/* 函数功能；等待空闲                         */
/**********************************************/
void W25Q16_Wait_Busy(void)   
{   
	while ((W25Q16_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  




























