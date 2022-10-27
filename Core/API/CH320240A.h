#ifndef _CH320240A_H_
#define _CH320240A_H_

#include "stm32f10x.h"


#define WR	  GPIO_Pin_8
#define RD    GPIO_Pin_9
#define CS	  GPIO_Pin_11
#define RS	  GPIO_Pin_10
#define RST	  GPIO_Pin_12
#define Data_d GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
#define DATAOUT(x) GPIOB->BSRR = (x & 0xff) | (~x & 0xff)<<16; //数据输出

//#define DATAOUT(x)   {GPIOB->ODR = (GPIOB->ODR & 0xff00) | x ;}


//#define DATAIN (GPIOB->IDR &0xff)//数据输入

#define     LCD_RS(x)  	             x ? GPIO_SetBits(GPIOB,RS)  : 	GPIO_ResetBits(GPIOB,RS)
#define     LCD_WR(x) 	             x ? GPIO_SetBits(GPIOB,WR)  : 	GPIO_ResetBits(GPIOB,WR)
#define     LCD_RD(x)  		           x ? GPIO_SetBits(GPIOB,RD)  :  GPIO_ResetBits(GPIOB,RD)
#define     LCD_CS(x) 	  	         x ? GPIO_SetBits(GPIOB,CS) : 	GPIO_ResetBits(GPIOB,CS)
#define     LCD_RST(x)  	           x ? GPIO_SetBits(GPIOB,RST) :  GPIO_ResetBits(GPIOB,RST)

void GPIO_Config(void);

void LCD_DataOutX(u8 vData);

void LCD_CmdWrite(u8 cmdaddr);
void LCD_DataWrite(u8 wrdata);
void LCD_Init(void);
void LCD_Clear(u8 color);
void LCD_GotoXY(u8 xx,u8 yy);
u8 ReBit8(u8 x);
void Disp_16X16_hanzi(u8 x, u16 y,u8 *p,u8 flag);
void Disp_8X16_zifu(u8 x, u16 y,u8 *p,u8 flag);
void Disp_hanzi(u8 x, u16 y,u8 width,u8 hight,u8 *p,u8 flag);
void LCD_String_hanzi(u8 x,u8 y,u8 width,u8 hight,u8 *q,u8 num,u8 color);
void Draw_Text_8_16_Str(u32 x, u32 y,u8 *chs,u8 flag);
void Disp_Picture(u8 *p);
void LCD_DrawPoint( u16 x, u16 y, u8 flag);
void LCD_DrawLineX_f(u16 lcd_x1,u16 lcd_x2,u16 lcd_y,u8 color);
void LCD_DrawLineY_f(u16 lcd_x,u16 lcd_y1,u16 lcd_y2,u8 color);
void LCD_Drawline(u16 StartX, u16 StartY, u16 EndX,u16 EndY, u8 Color);
void display_kuang(void);
void LCD_Str(u32 x, u32 y,u8 *chs,u8 flag);
#endif
