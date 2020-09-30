#include <LPC11xx.h>



/**********************************************/
/*  �������ܣ�SysTick��ʱ                     */
/*  ��ڲ���������ֵ��΢��ֵ                  */
/*  ˵����    ����ϵͳ��ʱ��ʵ��              */
/*            48Mhzʱ�ӹ�����                 */
/**********************************************/
static volatile uint32_t TimeTick = 0;
		  
void SysTick_Handler(void)					  //ϵͳ��ʱ���жϷ�����
{
	TimeTick++;
}

void delay_ms(uint32_t ms) /* ע�⣺����Ĳ������ȡ699������ᳬ��24λ������ֵ */
{
	SysTick->LOAD =	(((24000)*ms)-1);	  //�����ؼ�������дֵ
	SysTick->VAL   =	 0;					  //����������
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //����������,�����������ж�
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	
}

void delay_us(uint32_t us)
{
	SysTick->LOAD =	(((24)*us)-1);	  //�����ؼ�������дֵ
	SysTick->VAL   =	 0;					  //����������
	SysTick->CTRL  |=  ((1<<1)|(1<<0));     //����������,�����������ж�
	while(!TimeTick);
	TimeTick = 0;
	SysTick->CTRL =0;	    //�ض�ʱ������ʱʹ�����
}



int main()
{	

	// ��P0.3��P1.10��������Ϊ���
	LPC_GPIO0->DIR |= (1<<3);
	LPC_GPIO1->DIR |= (1<<10);
	//��LED1  LED2
 	LPC_GPIO0->DATA |= (1<<3);
	LPC_GPIO1->DATA |= (1<<10);

	while(1)
	{
		LPC_GPIO0->DATA &= ~(1<<3); // LED1��
		delay_ms(500);
		delay_ms(500);
		LPC_GPIO0->DATA |= (1<<3);  // LED1��
		LPC_GPIO1->DATA &= ~(1<<10);// LED2��
		delay_ms(500);
		delay_ms(500);
		LPC_GPIO1->DATA |= (1<<10); // LED2��
	} 
}




