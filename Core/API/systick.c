#include "stm32f10x.h"
#include "systick.h"
u32 systick_time = 0;
void Systick_Init(void )
{
	//��ʼ�����ɹ�����������
	if(SysTick_Config (SYSTICK_US)==1)//��ʼ�����ɹ�����1
	{
		while(1);
	}
	//�رյδ�ʱ��
	 SysTick->CTRL &= ~(1<<0);
}

//void Delay_us(u32 time)
//{
//	systick_time = time ;
//	//�򿪵δ�ʱ��
//	SysTick->CTRL |= (1<<0);
//	while(systick_time);
//	//�رյδ�ʱ��
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

