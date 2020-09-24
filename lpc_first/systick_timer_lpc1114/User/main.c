#include <LPC11xx.h>



/**********************************************/
/*  函数功能：SysTick延时                     */
/*  入口参数：毫秒值或微秒值                  */
/*  说明：    利用系统定时器实现              */
/*            48Mhz时钟工作下                 */
/**********************************************/
static volatile uint32_t TimeTick = 0;
		  
void SysTick_Handler(void)					  //系统定时器中断服务函数
{
	TimeTick++;
}

void delay_ms(uint32_t ms) /* 注意：这里的参数最大取699，否则会超出24位计数器值 */
{
	SysTick->LOAD =	(((24000)*ms)-1);	  //往重载计数器里写值
	SysTick->VAL   =	 0;					  //计数器清零
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //开启计数器,开启计数器中断
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	
}

void delay_us(uint32_t us)
{
	SysTick->LOAD =	(((24)*us)-1);	  //往重载计数器里写值
	SysTick->VAL   =	 0;					  //计数器清零
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //开启计数器,开启计数器中断
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	    //关定时器，延时使用完毕
}



int main()
{	

	// 把P0.3和P1.10引脚设置为输出
	LPC_GPIO0->DIR |= (1<<3);
	LPC_GPIO1->DIR |= (1<<10);
	//关LED1  LED2
 	LPC_GPIO0->DATA |= (1<<3);
	LPC_GPIO1->DATA |= (1<<10);

	while(1)
	{
		LPC_GPIO0->DATA &= ~(1<<3); // LED1亮
		delay_ms(500);
		delay_ms(500);
		LPC_GPIO0->DATA |= (1<<3);  // LED1灭
		LPC_GPIO1->DATA &= ~(1<<10);// LED2亮
		delay_ms(500);
		delay_ms(500);
		LPC_GPIO1->DATA |= (1<<10); // LED2灭
	} 
}




