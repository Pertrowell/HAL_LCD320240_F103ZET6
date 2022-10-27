#include "ch320240a.h"
#include "systick.h"
#include "hanzi.h"
#include "stdlib.h"
/****************************************************
��������
�βΣ�
����ֵ��
�������ܣ�GPIO��ʼ��
���ߣ����ڴ������ӿƼ����޹�˾
****************************************************/
void GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
  
  GPIO_InitStruct.GPIO_Pin =RS|WR|RD|CS|RST;//Data_d 
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStruct);
 
  GPIO_InitStruct.GPIO_Pin = Data_d;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStruct);	
	
	
   GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);
	
}

void LCD_DataOutX(u8 vData)
{   
	// 0x50   0101 0000
	
	// 7 6 5 4 3 2 1 0
	//   1   1         ->set 1
	// 0   0   0 0 0 0 ->set 0
	// 0 1 0 1 0 0 0 0
#if(1)
	u16 tData = 0;
	tData = GPIOB->ODR;//get the orginal 16 bit data
	tData &= 0xff00;//clear low 8bit
	tData |= vData; //combine low 8bit
	GPIOB->ODR = tData; //set out reg
#else
	GPIOB->BSRR = vData&0x00ff;//    GPIOB->BSRR = 0101 0000 
	GPIOB->BRR  = (~vData)&0xff;// GPIOB->BRR  = 1010 1111 
#endif
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void LCD_CmdWrite(u8 cmdaddr)//д����
{		
  LCD_CS(0);
  LCD_RD(1);
  LCD_RS(1);
  LCD_WR(0);
  LCD_DataOutX(cmdaddr);
  LCD_WR(1);
  LCD_CS(1);
}


void ReadTest(u8 cmdaddr)//д����
{		
	int IsWrite = 0;
	int IsCMD = 0;
	u8   data = 0;
	if(LCD_CS == 0)
	{
		while((LCD_RD == 1)&&( LCD_WR == 1))//�ȴ� RD����WR�½���
		{
			
		}
		if(LCD_WR == 0)//�ж��Ƕ�����д����
		{
			IsWrite = 1;
		}
		else
		{
			IsWrite = 0;
		}
		if(LCD_RS == 1)//�ж���ָ��  ��������
		{
			IsCMD = 1;
		}
		else
		{
			IsCMD = 0;
		}
		
		if(IsWrite)
		{
			while(LCD_WR == 0)//�ȴ� ����д��
			{
				
			}
		}
		else
		{
			while(LCD_RD == 0)//�ȴ� ���� ��ȡ
			{
				
			}
		}
		data = GPIOC->ODR & 0xff;//Read the data
		
		
			while(LCD_CS == 0)//�ȴ� ���� ��ȡ
			{
				
			}
	}
	
//	int IsWrite = 0;
//	int IsCMD = 0;
//	u8   data = 0;
	
	if(IsWrite)
	{
		if(IsCMD)
		{
			LCD_CmdWrite(data);
		}
		else
		{
			LCD_DataWrite(data);
			
		}
		
	}
	
	
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void LCD_DataWrite(u8 wrdata)//д����
{    
		LCD_CS(0);
 		LCD_RD(1);
		LCD_RS(0);
		LCD_WR(0);
		LCD_DataOutX(wrdata);
		LCD_WR(1);
		LCD_CS(1);
}
void LCD_Init(void)
{
  GPIO_Config();
  delay_ms(200);
 LCD_RST(0);
 delay_ms(200);
  LCD_RST(1);
  delay_ms(200);
  LCD_CmdWrite(0x40);  //ϵͳ����
  LCD_DataWrite(0x30);  //P1 ѡ���ڲ�ROM 
  LCD_DataWrite(0x87);  //P2 �ַ���Ϊ7
  LCD_DataWrite(0x07);  //P3 �ַ���Ϊ7
  LCD_DataWrite(0x27);  //P4 ÿ����ʾ40���ַ�
  LCD_DataWrite(0x37);  //P5 ����Ƶ��
  LCD_DataWrite(0xef);  //P6 ����240��
  LCD_DataWrite(0x28);  //P7  ��8λ,һ��ռ��40���ֽ� 
  LCD_DataWrite(0x00);  //P8  

  LCD_CmdWrite(0x44);  //����RAM
  LCD_DataWrite(0x00);  //  SAD1-L
  LCD_DataWrite(0x00);  //  SAD1-H
  LCD_DataWrite(0xf0);  //  SAD1ռ240��
  LCD_DataWrite(0x80);  //  SAD2-L
  LCD_DataWrite(0x25);  //  SAD2-H
  LCD_DataWrite(0xf0);  //  SAD2ռ240��
  LCD_DataWrite(0x00);  //  SAD3-L
  LCD_DataWrite(0x3a);  //  SAD3-H
  LCD_DataWrite(0x00);  //  SAD4-L
  LCD_DataWrite(0x3a);  //  SAD4-H

  LCD_CmdWrite(0x5a);  //����һ���ֽھ�����
  LCD_DataWrite(0x00);  // P1

  

//  LCD_DataWrite(1,0x58);  // off display
//  LCD_DataWrite(0,0x54);  // 	 

//  LCD_DataWrite(1,0x46);  // ����ַ
//  LCD_DataWrite(0,0x00);  // P1
//  LCD_DataWrite(0,0x00);  // P2

	LCD_CmdWrite(0x5b);  //  ovlay
//  LCD_DataWrite(0x00);  //�ı���ʽ 
LCD_DataWrite(0x0c);  //ͼ�η�ʽ

  LCD_CmdWrite(0x5d);  // ������ʾ��ʽ����״
  LCD_DataWrite(0x07);  //  CRX
  LCD_DataWrite(0x87);  //  CRY

//   LCD_DataWrite(1,0x4c);  


  LCD_CmdWrite(0x59);  // oN display
//  LCD_DataWrite(0x54);  //
LCD_DataWrite(0x04);
}
//---------------��������-------
void LCD_Clear(u8 color)
{
  u8 i,j;
  LCD_CmdWrite(0x46);  //���ù���ַ
  LCD_DataWrite(0x00);  //
  LCD_DataWrite(0x00);  //
  LCD_CmdWrite(0x42);//д����
  for(i=0;i<240;i++)
  for(j=0;j<40;j++)
  {
    LCD_DataWrite(color);	
  }
}
//----------�� 0��39   y 0��239 ------
void LCD_GotoXY(u8 xx,u8 yy)
{   
  u8 temp_L=0,temp_H=0;
  u16 temp=0;
  temp = yy*40+xx;
  temp_L = temp&0xff;
  temp_H = (temp>>8)&0xff;
 LCD_CmdWrite(0x46);
 LCD_DataWrite(temp_L);
 LCD_DataWrite(temp_H);
}
/************���ݸߵ�λת��******************/
u8 ReBit8(u8 x)
{
	x = ((x >> 4) & 0x0F) | ((x << 4) & 0xF0);
	x = ((x >> 2) & 0x33) | ((x << 2) & 0xCC);
	x = ((x >> 1) & 0x55) | ((x << 1) & 0xAA);
	return x;
}
 //------- x 0��39   y 0��239 ---------------- ������ʾ����---- 16 X 16 -------------------
void Disp_16X16_hanzi(u8 x, u16 y,u8 *p,u8 flag) //flag  0����  1����
{
  u8 i=x,j,m=0xff,temp=0; 
  LCD_CmdWrite(0x4c); //������� 
                  
  for(j = y; j<y+16; j++)
  {
    if (x>40)  //  x 0��39 
      return;
    for (i = x; i<x+2;i++)
    { 
      LCD_GotoXY(i,j);
      LCD_CmdWrite(0x42);//д����
      temp=*p++;
      temp=ReBit8(temp);
      if(flag)
      {
        temp ^= m;
      }
      LCD_DataWrite(temp); 
    }
  }
}
 //------- x 0��39   y 0��239 ---------------- �ַ���ʾ����---- 8 X 16 -------------------
void Disp_8X16_zifu(u8 x, u16 y,u8 *p,u8 flag) //flag  0����  1����
{
  u8 i=x,j,m=0xff,temp=0; 
  LCD_CmdWrite(0x4c); //������� 
                  
  for(j = y; j<y+16; j++)
  {
    if (x>40)  //  x 0��39 
      return;
    for (i = x; i<x+1;i++)
    { 
      LCD_GotoXY(i,j);
      LCD_CmdWrite(0x42);//д����
      temp=*p++;
//      temp=ReBit8(temp);//���ݸߵ�λת��
      if(flag)
      {
        temp ^= m;
      }
      LCD_DataWrite(temp); 
    }
  }
}
//------- x 0��39   y 0��239 ---------------- ������ʾ����---- 24 X 24 -------------------
void Disp_hanzi(u8 x, u16 y,u8 width,u8 hight,u8 *p,u8 flag) //flag  0����  1����
{
  u8 i=x,j,m=0xff,temp=0; 
  LCD_CmdWrite(0x4c); //�������               
  for(j = y; j<y+hight;j++)
  {
    if (x>40)  //  x 0��39 
      return;
    for (i = x; i<x+width/8;i++)
    { 
      LCD_GotoXY(i,j);
      LCD_CmdWrite(0x42);//д����
      temp=*p++;
//      temp=ReBit8(temp);//���ݸߵ�λת��
      if(flag)
      {
        temp ^= m;
      }
      LCD_DataWrite(temp); 
    }
  }
}
void LCD_String_hanzi(u8 x,u8 y,u8 width,u8 hight,u8 *q,u8 num,u8 color)//
{
	u16 m,n,flag=0;
	u8 *p=q;
	for(n=y;n<240;n=n+hight)
	{
		for(m=x;m<320;m=m+width)
		{
			Disp_hanzi(m/8,n,width,hight,p,color);
			p=p+width*hight/8;
			flag++;
			if(flag==num)
				break;
		}
		if(flag==num)
			break;
	}
}

//------- x 0��39   y 0��239 ---------------- �ַ�����ʾ���� -------------------
void Draw_Text_8_16_Str(u32 x, u32 y,u8 *chs,u8 flag)
{
	u32 i=0;
	while (*chs != '\0')
	{
		if (*chs > 0xa0)				//�������붼�Ǵ���0xa0
		{
			for (i=0 ;i < GB16_NUM();i++)
			{	
				if(x>39){x=0;y=y+16;}//320/8-1 = 39

				if ((*chs == hz_index[i*2]) && (*(chs+1) == hz_index[i*2+1]))
				{
					Disp_16X16_hanzi(x,y,&hz[32*(i)],flag);
					x+=2;
					break;
				}
			}
			chs+=2;
		}
		else	 //������ַ�ִ������
		{	if(x>39){x=0;y=y+16;}
			for (i=0 ;i < ASCII_NUM();i++)
			{
				if (*chs == zf_index[i])
				{
					Disp_8X16_zifu(x,y,&zf[16*i],flag);
					x++;
					break;
				}
			}
			chs++;
		}	 
	}
}
void Disp_Picture(u8 *p)
{
  u8 i,j;
  LCD_CmdWrite(0x46);  //���ù���ַ
  LCD_DataWrite(0x00);  //
  LCD_DataWrite(0x00);  //
  LCD_CmdWrite(0x42);//д����
  for(i=0;i<240;i++)
  for(j=0;j<80;j++)
  {
    LCD_DataWrite(*p++);	
  }
}
//-----------x=0 ?�� 319   y=0 ?�� 239 ----------------------------
void LCD_DrawPoint( u16 x, u16 y, u8 flag) //flag = 0 ���(��)�� bf=1 ���(��)�� bf=2 �ڰ�ת��(ȡ��)
{
    u16 Addr;
    u16 a ,b;
    u8 temp ;
    u16 bitAddr = 0;
    u8 bit1;

    a  =  x >> 3;
    //temp  = Sed[a][y];
    bitAddr = x - ( a << 3 );
        
    b  =  y*40;
    Addr  =  b + a;
    
    a  =  Addr & 0x0FF;
    b  =  Addr >> 8;

    bit1 = 0x80;
    if(bitAddr)
      bit1 =  bit1>>bitAddr;

    if(flag  ==  0)//
       temp = bit1 | temp;
    else if(flag  ==  1) 
    { 
       bit1 = 255- bit1;
       temp = (bit1 & temp);
    }   
    else if(flag  ==  2)
       temp = bit1 ^ temp;
    
    LCD_CmdWrite(0x4f	);  //1a����??��?
 
    LCD_CmdWrite(0x46);
    LCD_DataWrite(a);
    LCD_DataWrite(b);
    LCD_CmdWrite(0x42);

    //Sed[x >> 3][y] = temp; //should be here,befor LcdWDataAddr  = temp;
    LCD_DataWrite(temp);

}
/****************************************************
��������void LCD_DrawLineX_f(u8 lcd_x1,u8 lcd_x2,u8 lcd_y,u8 color)
�βΣ�lcd_x1��ʼ�е�ַ��0~319��  lcd_x2��ֹ�е�ַ��0~319�� lcd_y�е�ַ��0~239����color��ɫֵ��0��ʾ��1����ʾ������������������������������
����ֵ����
�������ܣ���ֱ�ߺ���
���ߣ����ڴ������ӿƼ����޹�˾
****************************************************/
//void LCD_DrawLineX_f(u16 lcd_x1,u16 lcd_x2,u16 lcd_y,u8 color)
//{
//	u8 temp;
//	if(lcd_x1 > lcd_x2)
//	{
//		temp = lcd_x1;
//		lcd_x1 = lcd_x2;
//		lcd_x2 = temp;
//	}
//	for(;lcd_x1 <= lcd_x2;lcd_x1++)
//	LCD_DrawPoint(lcd_x1,lcd_y,color);
//}
/****************************************************
��������void LCD_DrawLineY_f(u8 lcd_x,u8 lcd_y1,u8 lcd_y2,u8 color)
�βΣ�lcd_x�е�ַ��0~319��lcd_y1��ʼ�е�ַ��0~329��  lcd_y2��ֹ�е�ַ��0~239�� ����color��ɫֵ��0��ʾ��1����ʾ����������������������������
����ֵ����
�������ܣ������ߺ���
���ߣ����ڴ������ӿƼ����޹�˾
****************************************************/
void LCD_DrawLineY_f(u16 lcd_x,u16 lcd_y1,u16 lcd_y2,u8 color)
{
	u8 temp;
	if(lcd_y1 > lcd_y2)
	{
		temp = lcd_y1;
		lcd_y1 = lcd_y2;
		lcd_y2 = temp;
	}
	for(;lcd_y1 <= lcd_y2;lcd_y1++)
	{
		LCD_DrawPoint(lcd_x,lcd_y1,color);
	}
}
///****************************************************
//��������void LCD_Drawline(u8 StartX, u8 StartY, u8 EndX,u8 EndY, u8 Color)
//�βΣ�StartX ��ʼ�е�ַ��0~319��  StartY ��ʼ�е�ַ��0~319��EndX ��ֹ�е�ַ��0~239��  EndY ��ֹ�е�ַ��0~239�� 
//  ����color��ɫֵ��0��ʾ��1����ʾ����������������������������
//����ֵ����
//�������ܣ�����������֮��ֱ�ߺ���
//���ߣ����ڴ������ӿƼ����޹�˾
//****************************************************/
//void LCD_Drawline(u16 StartX, u16 StartY, u16 EndX,u16 EndY, u8 Color)
//{
//	int t, distance; /*��������С�������ͣ���int�ͣ�*/
//	int x = 0 , y = 0 , delta_x, delta_y ;
//	char incx, incy ;
//	delta_x = EndX - StartX ;
//	delta_y = EndY - StartY ;
//	if( delta_x > 0 )
//	{
//		incx = 1;
//	}
//	else if( delta_x == 0 )
//	{
//		LCD_DrawLineY_f( StartX, StartY, EndY, Color ) ;
//		return ;
//	}
//	else
//	{
//		incx = -1 ;
//	}
//	if( delta_y > 0 )
//	{
//		incy = 1 ;
//	}
//	else if(delta_y == 0 )
//	{
//		LCD_DrawLineX_f( StartX, EndX, StartY, Color ) ;
//		return ;
//	}
//	else
//	{
//		incy = -1 ;
//	}
//	delta_x = abs( delta_x );
//	delta_y = abs( delta_y );
//	if( delta_x > delta_y )
//	{
//		distance = delta_x ;
//	}
//	else
//	{
//		distance = delta_y ;
//	}
//	LCD_DrawPoint( StartX, StartY, Color ) ;
//	/* Draw Line*/
//	for( t = 0 ; t <= distance+1 ; t++ )
//	{
//		LCD_DrawPoint( StartX, StartY, Color ) ;
//		x += delta_x ;
//		y += delta_y ;
//		if( x > distance )
//		{
//			x -= distance ;
//			StartX += incx ;
//		}
//		if( y > distance )
//		{
//			y -= distance ;
//			StartY += incy ;
//		}
//	}
//}
void display_kuang(void)
{
  u16 i=0;
  LCD_DrawLineY_f(0,0,239,0);
  LCD_DrawLineY_f(319,0,239,0);
  for(i=0;i<40;i++)
  {
    LCD_GotoXY(i,0);
    LCD_CmdWrite(0x42);
    LCD_DataWrite(0xff);
  }
  for(i=0;i<40;i++)
  {
    LCD_GotoXY(i,239);
    LCD_CmdWrite(0x42);
    LCD_DataWrite(0xff);
  }
}
void LCD_Str(u32 x, u32 y,u8 *chs,u8 flag)
{
	u32 i=0;
	while (*chs != '\0')
	{
		if (*chs > 0xa0)				//�������붼�Ǵ���0xa0
		{
			for (i=1 ;i < GB16_NUM();i++)
			{	
				if(x>38){x=1;y=y+16;}//320/8-1 = 39

				if ((*chs == hz_index[i*2]) && (*(chs+1) == hz_index[i*2+1]))
				{
					Disp_16X16_hanzi(x,y,&hz[32*(i)],flag);
					x+=2;
					break;
				}
			}
			chs+=2;
		}
		else	 //������ַ�ִ������
		{	if(x>38){x=1;y=y+16;}
			for (i=1 ;i < ASCII_NUM();i++)
			{
				if (*chs == zf_index[i])
				{
					Disp_8X16_zifu(x,y,&zf[16*i],flag);
					x++;
					break;
				}
			}
			chs++;
		}	 
	}
}

