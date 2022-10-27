#include "stm32f10x.h"
#include "systick.h"
u32 systick_time = 0;
void Systick_Init(void )
{
	//初始化不成功程序死在这
	if(SysTick_Config (SYSTICK_US)==1)//初始化不成功返回1
	{
		while(1);
	}
	//关闭滴答时钟
	 SysTick->CTRL &= ~(1<<0);
}

//void Delay_us(u32 time)
//{
//	systick_time = time ;
//	//打开滴答时钟
//	SysTick->CTRL |= (1<<0);
//	while(systick_time);
//	//关闭滴答时钟
//	SysTick->CTRL &= ~(1<<0);
//}
	
void Delay_us(u32 time)
{
	systick_time = time;
	SysTick->CTRL |= (1<<0);
	while(systick_time);
	SysTick->CTRL &= ~(1<<0);
}
void SysTick_Handler(void )
{
	if(systick_time > 0)
		systick_time--;
}

