#include "lcd12864.h"

#include "charcode.h"


#define _nop_() TIM16B0_delay_us(10);

//*******************************n*1mS延时子函数*******************************
void TIM16B0_delay_ms(uint16_t ms)
{
  LPC_TMR16B0->TCR = 0x02;  	//复位定时器
  LPC_TMR16B0->PR = 1000;  		//预分频置1000
  LPC_TMR16B0->MR0 = ms * 48;  	//在48Mhz下工作的匹配值
  LPC_TMR16B0->IR = 0x01;  		//清除中断标志
  LPC_TMR16B0->MCR = 0x04; //MR0匹配时停止TC和PC，并清零TCR[0]，不产生中断
  LPC_TMR16B0->TCR = 0x01;  	//启动定时器
  while (LPC_TMR16B0->TCR & 0x01);  //等待定时器计时时间到
}
//*******************************n*1uS延时子函数******************************
void TIM16B0_delay_us(uint16_t us)
{
  LPC_TMR16B0->TCR = 0x02;  	//复位定时器
  LPC_TMR16B0->PR = 0x00;  		//预分频置0
  LPC_TMR16B0->MR0 = us * 48;  	//在48Mhz下工作的匹配值
  LPC_TMR16B0->IR = 0x01;  		//清除中断标志
  LPC_TMR16B0->MCR = 0x04; //MR0匹配时停止TC和PC，并清零TCR[0]，不产生中断
  LPC_TMR16B0->TCR = 0x01;  	//启动定时器
  while (LPC_TMR16B0->TCR & 0x01);  	//等待定时器计时时间到
}



//************************写数据到LCD数据端口子函数**************************
void WriteDataPort(uint8_t data)
{
  LPC_GPIO2->DATA &= 0xF00;    	//PIO2的低八位清零，高四位保持不变
  LPC_GPIO2->DATA |= data;     	//对PIO2的低八位写入数据
}



/*******************************************************************************
* 函 数 名         : LCD12864_WriteCmd
* 函数功能		   : 写入一个命令到12864
* 输    入         : cmd
* 输    出         : 无
*******************************************************************************/

void LcdSt7565_WriteCmd(uint8_t cmd)
{
	LCD12864_CS_0;	   //chip select,打开片选
	LCD12864_RD_1;	   //disable read，读失能	
	LCD12864_RS_0;       //select command，选择命令
	LCD12864_RW_0;       //select write，选择写模式
	_nop_();
	_nop_();

	WriteDataPort(cmd); //put command，放置命令
	_nop_();
	_nop_();

	LCD12864_RW_1;	   //command writing ，写入命令
 }

/*******************************************************************************
* 函 数 名         : LcdSt7565_WriteData
* 函数功能		   : 写入一个数据到12864
* 输    入         : dat
* 输    出         : 无
*******************************************************************************/

void LcdSt7565_WriteData(uint8_t dat)
{	
	LCD12864_CS_0;	   //chip select，打开片选
	LCD12864_RD_1;	   //disable read，读失能	
	LCD12864_RS_1;       //select data，选择数据
	LCD12864_RW_0;       //select write，选择写模式
	_nop_();
	_nop_();

	WriteDataPort(dat);       //put data，放置数据
	_nop_();
	_nop_();

	LCD12864_RW_1;	   //data writing，写数据 
}
/*******************************************************************************
* 函 数 名         : LCD12864_Init
* 函数功能		   : 初始化12864
* 输    入         : 无
* 输    出         : 无
* 说    明         : LCD12864的命令指令可以查看例程文件夹下的《ST7565p数据手册》
*                  * 的第51页的位置。
*******************************************************************************/

void Lcd12864_Init()
{
	uint8_t i;
	LCD12864_RSET_0;
	for (i=0; i<100; i++);
	_nop_()
	LCD12864_CS_0;
	LCD12864_RSET_1;
	
	//----------------Star Initial Sequence-------//
	//------程序初始化设置，具体命令可以看文件夹下---//

	//--软件初始化--//
	LcdSt7565_WriteCmd(0xE2);  //reset
	for (i=0; i<100; i++);	   //延时一下
	_nop_()

	//--表格第8个命令，0xA0段（左右）方向选择正常方向（0xA1为反方向）--//
	LcdSt7565_WriteCmd(0xA0);  //ADC select segment direction 
	
	//--表格第15个命令，0xC8普通(上下)方向选择选择反向，0xC0为正常方向--// 
	LcdSt7565_WriteCmd(0xC8);  //Common direction 
	                  
	//--表格第9个命令，0xA6为设置字体为黑色，背景为白色---//
	//--0xA7为设置字体为白色，背景为黑色---//
	LcdSt7565_WriteCmd(0xA6);  //reverse display

	//--表格第10个命令，0xA4像素正常显示，0xA5像素全开--//
	LcdSt7565_WriteCmd(0xA4);  //normal display
	
	//--表格第11个命令，0xA3偏压为1/7,0xA2偏压为1/9--//
	LcdSt7565_WriteCmd(0xA2);  //bias set 1/9
	
	//--表格第19个命令，这个是个双字节的命令，0xF800选择增压为4X;--//
	//--0xF801,选择增压为5X，其实效果差不多--//	
	LcdSt7565_WriteCmd(0xF8);  //Boost ratio set
	LcdSt7565_WriteCmd(0x01);  //x4
	
	//--表格第18个命令，这个是个双字节命令，高字节为0X81，低字节可以--//
	//--选择从0x00到0X3F。用来设置背景光对比度。---/
	LcdSt7565_WriteCmd(0x81);  //V0 a set
	LcdSt7565_WriteCmd(0x23);

	//--表格第17个命令，选择调节电阻率--//
	LcdSt7565_WriteCmd(0x25);  //Ra/Rb set
	
	//--表格第16个命令，电源设置。--//
	LcdSt7565_WriteCmd(0x2F);
	for (i=0; i<100; i++);
	_nop_()

	//--表格第2个命令，设置显示开始位置--//
	LcdSt7565_WriteCmd(0x40);  //start line

	//--表格第1个命令，开启显示--//
	LcdSt7565_WriteCmd(0xAF);  // display on
	for (i=0; i<100; i++);

}

/*******************************************************************************
* 函 数 名         : LCD12864_ClearScreen
* 函数功能		   : 清屏12864
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Lcd12864_ClearScreen(void)
{
	uint8_t i, j;

	for(i=0; i<8; i++)
	{
		//--表格第3个命令，设置Y的坐标--//
		//--Y轴有64个，一个坐标8位，也就是有8个坐标--//
		//所以一般我们使用的也就是从0xB0到0x07,就够了--//	
		LcdSt7565_WriteCmd(0xB0+i); 

		//--表格第4个命令，设置X坐标--//
		//--当你的段初始化为0xA1时，X坐标从0x10,0x04到0x18,0x04,一共128位--//
		//--当你的段初始化为0xA0时，X坐标从0x10,0x00到0x18,0x00,一共128位--//
		//--在写入数据之后X坐标的坐标是会自动加1的，我们初始化使用0xA0所以--//
		//--我们的X坐标从0x10,0x00开始---//
		LcdSt7565_WriteCmd(0x10); 
		LcdSt7565_WriteCmd(0x04);							   
		
		//--X轴有128位，就一共刷128次，X坐标会自动加1，所以我们不用再设置坐标--//
		for(j=0; j<128; j++)
		{
			LcdSt7565_WriteData(0x00);  //如果设置背景为白色时，清屏选择0XFF
		}
	}
}

/*******************************************************************************
* 函 数 名         : LCD12864_Write16CnCHAR
* 函数功能		   : 在12864上面书写16X16的汉字
* 输    入         : x, y, cn
* 输    出         : 无
* 说    明		   : 该函数可以直接书写字符串，但是书写是从右到左，所以输入的时
*                  * 侯注意输入。汉字的取模方式请观看文件夹下的《汉字取模软件的
*                  * 使用说明》
*******************************************************************************/



uint8_t Lcd12864_Write16CnCHAR(uint8_t x, uint8_t y, uint8_t *cn)
{
	uint8_t j, x1, x2, wordNum;

	//--Y的坐标只能从0到7，大于则直接返回--//
	if(y > 7)
	{
		return 0;
	}

	//--X的坐标只能从0到128，大于则直接返回--//
	if(x > 128)
	{
		return 0;
	}
	y += 0xB0;	   //求取Y坐标的值
	//--设置Y坐标--//
	LcdSt7565_WriteCmd(y);
	while ( *cn != '\0')	 //在C语言中字符串结束以‘\0’结尾
	{	
	
		//--设置Y坐标--//
		LcdSt7565_WriteCmd(y);

		x1 = (x >> 4) & 0x0F;   //由于X坐标要两句命令，分高低4位，所以这里先取出高4位
		x2 = x & 0x0F;          //去低四位
		//--设置X坐标--//
		LcdSt7565_WriteCmd(0x10 + x1);   //高4位
		LcdSt7565_WriteCmd(0x04 + x2);	//低4位

		for (wordNum=0; wordNum<50; wordNum++)
		{
		    //--查询要写的字在字库中的位置--//
			if ((CN16CHAR[wordNum].Index[0] == *cn)
			     &&(CN16CHAR[wordNum].Index[1] == *(cn+1)))
			{
				for (j=0; j<32; j++) //写一个字
				{		
					if (j == 16)	 //由于16X16用到两个Y坐标，当大于等于16时，切换坐标
					{
						//--设置Y坐标--//
			   			LcdSt7565_WriteCmd(y + 1);
			
						//--设置X坐标--//
						LcdSt7565_WriteCmd(0x10 + x1);   //高4位
						LcdSt7565_WriteCmd(0x04 + x2);	//低4位
					}
					LcdSt7565_WriteData(CN16CHAR[wordNum].Msk[j]);
				}
				x += 16;
			}//if查到字结束		
		} //for查字结束	
		cn += 2;
	}	//while结束
	return 1;
}


