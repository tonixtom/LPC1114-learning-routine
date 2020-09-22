/******************************************************************/
/* 名称：CLKOUT引脚(即P0.1脚)输出时钟频率                         */
/* 效果：在P1.0脚有占空比为50%的方波频率输出，输出频率取决于div   */
/* 看门狗振荡器作为主时钟源，配置LPC1114的主频为2.3MHz,以div进行分频           */
/*       div = 1   输出频率 = 2.3MHz  （以此类推）                 */
/******************************************************************/
#include "lpc11xx.h"
#include "stdio.h"
#include "stdlib.h"



#if 0    //另一个时钟配置

void SysCLK_config(void)
{
	uint8_t i;
	/*执行以下代码选择外部12M晶振作为时钟源*/
	LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          //系统振荡器上电   
  	LPC_SYSCON->SYSOSCCTRL    = 0x00000000;			//振荡器未被旁路，1~20Mhz频率输入
  	for (i = 0; i < 200; i++) __nop();		    //等待振荡器稳定
 	LPC_SYSCON->SYSPLLCLKSEL  = 0x00000001;         //PLL时钟源选择“系统振荡器”
  	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;               //更新PLL选择时钟源
  	LPC_SYSCON->SYSPLLCLKUEN  = 0x00;               //先写0，再写1达到更新时钟源的目的（数据手册规定）
  	LPC_SYSCON->SYSPLLCLKUEN  = 0x01;
  	while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     //确定时钟源更新后向下执行
	/*执行以下代码倍频为48MHz*/
	LPC_SYSCON->SYSPLLCTRL    = 0x00000023;     	//设置M=4;P=2; FCLKOUT=12*4=48Mhz
  	LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          //PLL上电
  	while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	    //确定PLL锁定以后向下执行
	/*主时钟源选择倍频以后的时钟*/
	LPC_SYSCON->MAINCLKSEL    = 0x00000003;			//主时钟源选择PLL后的时钟
	LPC_SYSCON->MAINCLKUEN    = 0x01;				//更新主时钟源
	LPC_SYSCON->MAINCLKUEN    = 0x00;				//先写0，再写1达到更新时钟源的目的（数据手册规定）
	LPC_SYSCON->MAINCLKUEN    = 0x01;
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));	    //确定主时钟锁定以后向下执行
	LPC_SYSCON->SYSAHBCLKDIV  = 0x01;				//AHB时钟分频值为1，使AHB时钟设置为48Mhz
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);            //使能GPIO时钟（用单片机好像没有不用GPIO的时候）
}

#endif

/***********************************************/
/*  函数功能：使能CLKOUT脚输出频率             */
/*  入口参数：CLKOUT_DIV,即CLKOUT分频值，1~255 */
/*  说明：    此函数可用来测试时钟真实性       */
/***********************************************/
void CLKOUT_EN(uint8_t CLKOUT_DIV)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);          // 使能IOCON时钟 
	LPC_IOCON->PIO0_1=0XD1;						   // 把P0.1脚设置为CLKOUT引脚
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);          // 禁能IOCON时钟
	LPC_SYSCON->CLKOUTDIV   = CLKOUT_DIV;			//CLKOUT时钟值为48/CLKOUT_DIV
	LPC_SYSCON->CLKOUTCLKSEL= 0X00000003;	  		//CLKOUT时钟源选择为主时钟
	LPC_SYSCON->CLKOUTUEN   =0X01;
	LPC_SYSCON->CLKOUTUEN   =0X00;
	LPC_SYSCON->CLKOUTUEN   =1;
	while (!(LPC_SYSCON->CLKOUTUEN & 0x01));        //确定时钟源更新后向下执行
}


#define div   250

int main(void)
{

	// 使能CLKOUT引脚输出时钟频率
	CLKOUT_EN(div);
	//clkout时钟输出值 = 2.3M/250=9.2k
	while(1)
	{
		 ;
	}
}



