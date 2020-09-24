#include <LPC11xx.h>


//**************************系统定时器中断服务程序***************************
void SysTick_Handler(void)
{
 uint32_t temp;   				//定义临时中间变量
 temp = LPC_GPIO2->DATA;	 //读取当前端口2的值
 temp = ~temp;        			//把中间变量进行取反
 temp<<=1;           			 //把中间变量进行左移一位
 temp = ~temp;       			 //再次把中间变量进行取反
 LPC_GPIO2->DATA = temp; 	//把左移后的量赋给端口2
 if(temp==0xFFF)      		//如果左移到头，则从头开始
  {
 LPC_GPIO2->DATA = 0xFFE;
  }
}
//*****************************系统定时器初始化*******************************
void SysTick_init(void)
{
 SysTick->LOAD = (((24000)*100)-1); //设置100ms的定时 
 SysTick->VAL = 0;         //计数清零
 SysTick->CTRL |= ((1<<1)|(1<<0));  //允许中断，选择半系统时钟，启动定时器
}





//**********************************主函数************************************
int main(void) 
{
 LPC_GPIO2->DIR = 0xFFF;     //设置端口2为输出方向
 LPC_GPIO2->DATA = 0xFFE; //端口2最低位输出0，点亮最末一个LED
 SysTick_init();    //调用系统定时器
 while(1)
  {
   ;   //空循环
  }
}
