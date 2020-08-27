#ifndef __GUI_H
#define __GUI_H

#include "stm32f4xx_hal.h"

void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//指定区域填充颜色
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);//在指定位置画一个点
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//在指定位置画一条线
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//在指定位置画一个矩形
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);//在指定位置画一个圆
uint8_t get_number_c(uint16_t numeber,uint8_t w);

uint32_t mypow(uint8_t m,uint8_t n);//求幂
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示整数变量
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//显示两位小数变量

void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint8_t p);//显示图片

void Show_top(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint16_t back,uint16_t color,uint8_t p);
void Show_roll(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint16_t ud,uint16_t up_down) ;
void Word48(uint16_t x,uint16_t y,uint16_t color,uint8_t p);
void Word23(uint16_t x,uint16_t y,uint16_t color,uint16_t p);
void Refresh(uint8_t p) ;
void Word23_sig(uint16_t x,uint16_t y,uint16_t color,uint16_t p);
uint8_t get_number_c(uint16_t numeber,uint8_t w);
void LCD_ShowPicture_action_foot(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint8_t p);
void LCD_ShowPicture_action_cal(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint8_t p);
void Cal_page(void);
//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	
#define ORG         	 0xE2DC	  

#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif






