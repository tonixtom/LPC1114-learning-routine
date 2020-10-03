#include "lcd_1602.h"


//*****************************引脚电平的宏定义*********************************
#define LCM_RS_1 LPC_GPIO2->MASKED_ACCESS[1024] = 0xFFF//RS接第10脚输出高电平
#define LCM_RS_0 LPC_GPIO2->MASKED_ACCESS[1024] = 0x000 //RS接第10脚输出低电平
#define LCM_RW_1 LPC_GPIO2->MASKED_ACCESS[512] = 0xFFF //RW接第9脚输出高电平
#define LCM_RW_0 LPC_GPIO2->MASKED_ACCESS[512] = 0x000 //RW接第9脚输出低电平
#define LCM_EN_1 LPC_GPIO2->MASKED_ACCESS[256] = 0xFFF //EN接第8脚输出高电平
#define LCM_EN_0 LPC_GPIO2->MASKED_ACCESS[256] = 0x000   //EN接第8脚输出低电平
#define DataPort LPC_GPIO2->DATA          //PIO2为数据端口
#define Busy 0x80         //忙信号
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
//************************读LCD数据端口数据子函数****************************
uint8_t ReadDataPort(void)
{
  uint8_t temp;
  temp = LPC_GPIO2->DATA;    //读取PIO2的低八位数据
  return temp;
}
//***************************检测LCD忙信号子函数*****************************
void WaitForEnable(void)
{
    uint8_t val;
    WriteDataPort(0xFF);        		//数据线电平拉高
    LCM_RS_0;             				//选择指令寄存器
    LCM_RW_1;             			//选择写方式
    TIM16B0_delay_us(1);  			//延时一微秒，等待稳定
    LCM_EN_1;             			//使能端拉高电平
    TIM16B0_delay_us(2);  			//延时两微秒，等待稳定
    LPC_GPIO2->DIR = 0xF00;       	 //改变数据线方向成输入
    val = ReadDataPort();             		//读取数据
    while(val&Busy)
      val = ReadDataPort();           		//当PIO2的第7脚为1时表示忙，循环检测
    LCM_EN_0;             			//忙信号结束，拉低使能端电平
    LPC_GPIO2->DIR = 0xFFF;          	//改变数据线方向成输出
}
//****************************写命令到LCD子函数****************************
void LcdWriteCommand(uint8_t CMD,uint8_t Attribc)
//写命令CMD到LCD中，Arribc为1时检测忙信号，否则不检测
{
    if(Attribc)
      WaitForEnable();      	//检测忙信号
    LCM_RS_0;                 	//选择指令寄存器
    LCM_RW_0;                 	//选择写方式
    TIM16B0_delay_us(1);            	//延时一微秒，等待稳定
    WriteDataPort(CMD);             	//把命令数据送到数据线上
    TIM16B0_delay_us(1);            	//延时一微秒，等待稳定
    LCM_EN_1;                 		//使能端拉高电平
    TIM16B0_delay_us(2);            	//延时两微秒，等待稳定
    LCM_EN_0;                 		//拉低使能端，执行写入动作
}
//****************************写数据到LCD子函数****************************
void LcdWriteData(uint8_t dataW)      //写数据dataW到LCD中
{
    WaitForEnable();        	//检测忙信号
    LCM_RS_1;               	//选择数据寄存器
    LCM_RW_0;               	//选择读方式
    TIM16B0_delay_us(1);     //延时一微秒，等待稳定
    WriteDataPort(dataW);     //把显示数据送到数据线上
    TIM16B0_delay_us(1);     //延时一微秒，等待稳定
    LCM_EN_1;               	//使能端拉高电平
    TIM16B0_delay_us(2);    	//延时两微秒，等待稳定
    LCM_EN_0;               	//拉低使能端，执行写入动作
}
//*****************************LCD初始化子函数*****************************
void InitLcd(void) 
{
    LcdWriteCommand(0x38,0);      //8位数据方式，双行显示，5X7字形，不检测忙信号
    TIM16B0_delay_ms(5);                //延时5ms
    LcdWriteCommand(0x38,0); 
    TIM16B0_delay_ms(5);
    LcdWriteCommand(0x38,0); 
    TIM16B0_delay_ms(5);                //重复三次
    LcdWriteCommand(0x38,1);      //8位数据方式，双行显示，5X7字形，检测忙信号
    LcdWriteCommand(0x08,1);      //关闭显示，检测忙信号
    LcdWriteCommand(0x01,1);      //清屏，检测忙信号
    LcdWriteCommand(0x06,1);      //显示光标右移设置，检测忙信号
    LcdWriteCommand(0x0C,1);      //打开显示，光标不显示，不闪烁，检测忙信号
}
//***************************显示光标定位子函数****************************
void LocateXY(char posx,char posy)      //定位位置到地址x列y行
{
    uint8_t temp;
    temp = posx & 0x0F;       	//屏蔽高4位,限定x坐标的范围为0~15
    posy &= 0x01;           	//屏蔽高7位,限定y坐标的范围为0~1
    if(posy) 
      temp |= 0x40;         //若要显示的是第二行，则地址码+0x40，因为第二行起始地址为0x40
    temp |= 0x80;    //指令码为地址码+0x80，因为写DDRAM时PIO2的第7脚恒为1（即0x80）
    LcdWriteCommand(temp,1);    	//把temp写入LCD中，检测忙信号
}
//**********************显示指定座标的一个字符子函数************************
void DisplayOneChar(uint8_t x,uint8_t y,uint8_t Wdata) 
//在x列y行处显示变量Wdata中的一个字符
{
    LocateXY(x,y);          	//定位要显示的位置
    LcdWriteData(Wdata);    	//将要显示的数据Wdata写入LCD
} 
//**********************显示指定座标的一串字符子函数************************
void ePutstr(uint8_t x,uint8_t y,uint8_t const *ptr)    //在x列y行处显示ptr指向的字符串
{
    uint8_t i,j=0;
    while(ptr[j]>31)
      j++;                         //ptr[j]>31时为ASCII码，j累加，计算出字符串长度
    for(i=0;i<j;i++)
    {
      DisplayOneChar(x++,y,ptr[i]);       //显示单个字符，同时x坐标递增
      if(x==16)
        {
          x=0;
          y^=1;         //当每行显示超过16个字符时换行继续显示
        }
    }
}



