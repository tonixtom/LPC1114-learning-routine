/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 4.60
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用通用定时器捕获功能
*   作者    ：Ration
*   官方网址：http://www.rationmcu.com
*   淘宝店  ：http://ration.taobao.com
**************************************************************************************/
#include "lpc11xx.h"
#include "timer.h"
#include "uart.h"

uint16_t temp;   // 
uint16_t freq;   // 

// 非精确延时
void delay_ms(uint16_t ms)
{
	uint16_t i,j;
	
	for(i=0;i<5000;i++)
		for(j=0;j<ms;j++);
}

/***********************************************/
/*  函数功能：使能CLKOUT脚输出频率             */
/*  入口参数：CLKOUT_DIV,即CLKOUT分频值，1~255 */
/*             =0 关闭时钟输出                 */
/*  说明：    此函数可用来测试时钟             */
/***********************************************/
void CLKOUT_EN(uint8_t CLKOUT_DIV)
{
	LPC_SYSCON->PDRUNCFG &= ~(0x1<<6);    // 看门狗振荡器时钟上电（bit6）
	LPC_SYSCON->WDTOSCCTRL = 0X3F; // DIVSEL = 31, FREQSEL = 0X1; 即看门狗时钟输出为0.6M/2*(1+31)=9375赫兹
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);          // 使能IOCON时钟 
	LPC_IOCON->PIO0_1=0XD1;						             // 把P0.1脚设置为CLKOUT引脚
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);         // 禁能IOCON时钟
	LPC_SYSCON->CLKOUTDIV   = CLKOUT_DIV;			     // CLKOUT时钟值输出=主时钟/CLKOUT_DIV
	LPC_SYSCON->CLKOUTCLKSEL= 0X00000002;	  		   // CLKOUT时钟源选择为看门狗时钟
	LPC_SYSCON->CLKOUTUEN   =0;
	LPC_SYSCON->CLKOUTUEN   =1;
	while (!(LPC_SYSCON->CLKOUTUEN & 0x01));       // 确定时钟源更新后向下执行
}

void TIMER16_0_IRQHandler(void)
{
	if((LPC_TMR16B0->IR&0x10)==0x10) // 如果是CAP引起的中断
	{
		temp = LPC_TMR16B0->CR0;
		LPC_TMR16B0->TC = 0;
		freq = 100000/temp; // 把单位转换成赫兹
	}
	else if((LPC_TMR16B0->IR&0X01)==0X01) // 如果是MR0匹配引起的中断,即溢出中断
	{
		freq = 0;
	}
	LPC_TMR16B0->IR = 0X1F; // 清中断位
}

int main()
{
	UART_init(9600);
	T16B0_CAP_Init();
	CLKOUT_EN(200);//  9375/200=46Hz
	
	while(1)
	{
		delay_ms(500);
		UART_send_byte(freq);
		UART_send_byte(freq>>8);
	}
}





