#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"

#define SYSTICK_US 72
#define SYSTICK_MS 72000
#define delay_us Delay_us
#define delay_ms Delay_ms
#define Delay_ms(time) Delay_us(time*1000)
#define Delay_s(time) Delay_ms(time*1000)


//void Delay_us(u32 time);
void Systick_Init(void );
void Delay_us(u32 time);


#endif


