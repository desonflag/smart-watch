/**
  ******************************************************************************
  * @file    gui.c
  * @author  Deson
  * @version V1.0.0
  * @date    2019-12-27
  * @brief   图形绘制程序
  ******************************************************************************
  */
/*--Include-start-------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "ST7735.h"
#include "gui.h"
#include "font.h"
#include "pic.h"

uint8_t get_number_c(uint16_t numeber,uint8_t w) {
    uint8_t i;
    int k=1;
    for(uint8_t j=0; j<w-1; j++) {
        k=10*k;
    }
    i=numeber/(k)%10;
    return i;
}
/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{
    uint16_t i,j;
    LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
    for(i=ysta; i<yend; i++)
    {
        for(j=xsta; j<xend; j++)
        {
            LCD_WR_DATA(color);
        }
    }
}

/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    LCD_Address_Set(x,y,x,y);//设置光标位置
    LCD_WR_DATA(color);
}


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
    uint16_t t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x=x2-x1; //计算坐标增量
    delta_y=y2-y1;
    uRow=x1;//画线起点坐标
    uCol=y1;
    if(delta_x>0)incx=1; //设置单步方向
    else if (delta_x==0)incx=0;//垂直线
    else {
        incx=-1;
        delta_x=-delta_x;
    }
    if(delta_y>0)incy=1;
    else if (delta_y==0)incy=0;//水平线
    else {
        incy=-1;
        delta_y=-delta_y;
    }
    if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
    else distance=delta_y;
    for(t=0; t<distance+1; t++)
    {
        LCD_DrawPoint(uRow,uCol,color);//画点
        xerr+=delta_x;
        yerr+=delta_y;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
    LCD_DrawLine(x1,y1,x2,y1,color);
    LCD_DrawLine(x1,y1,x1,y2,color);
    LCD_DrawLine(x1,y2,x2,y2,color);
    LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
    int a,b;
    a=0;
    b=r;
    while(a<=b)
    {
        LCD_DrawPoint(x0-b,y0-a,color);             //3
        LCD_DrawPoint(x0+b,y0-a,color);             //0
        LCD_DrawPoint(x0-a,y0+b,color);             //1
        LCD_DrawPoint(x0-a,y0-b,color);             //2
        LCD_DrawPoint(x0+b,y0+a,color);             //4
        LCD_DrawPoint(x0+a,y0-b,color);             //5
        LCD_DrawPoint(x0+a,y0+b,color);             //6
        LCD_DrawPoint(x0-b,y0+a,color);             //7
        a++;
        if((a*a+b*b)>(r*r))//判断要画的点是否过远
        {
            b--;
        }
    }
}


void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
    uint8_t temp,sizex,t;
    uint16_t i,TypefaceNum;//一个字符所占字节大小
    uint16_t x0=x;
    sizex=sizey/2;
    TypefaceNum=sizex/8*sizey;
    num=num-' ';    //得到偏移后的值
    LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置
    for(i=0; i<TypefaceNum; i++)
    {
        if(sizey==16)temp=ascii_1608[num][i];		       //调用8x16字体
        else if(sizey==32)temp=ascii_3216[num][i];		 //调用16x32字体
        else return;
        for(t=0; t<8; t++)
        {
            if(!mode)//非叠加模式
            {
                if(temp&(0x01<<t))LCD_WR_DATA(fc);
                else LCD_WR_DATA(bc);
            }
            else//叠加模式
            {
                if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//画一个点
                x++;
                if((x-x0)==sizex)
                {
                    x=x0;
                    y++;
                    break;
                }
            }
        }
    }
}





/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
    uint32_t result=1;
    while(n--)result*=m;
    return result;
}


/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{
    uint8_t t,temp;
    uint8_t enshow=0;
    uint8_t sizex=sizey/2;
    for(t=0; t<len; t++)
    {
        temp=(num/mypow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,1);
                continue;
            } else enshow=1;

        }
        LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,1);
    }
}


/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey)
{
    uint8_t t,temp,sizex;
    uint16_t num1;
    sizex=sizey/2;
    num1=num*100;
    for(t=0; t<len; t++)
    {
        temp=(num1/mypow(10,len-t-1))%10;
        if(t==(len-2))
        {
            LCD_ShowChar(x+(len-2)*sizex,y,'.',fc,bc,sizey,0);
            t++;
            len+=1;
        }
        LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
    }
}


/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组
      返回值：  无
******************************************************************************/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint8_t p)
{
    uint16_t i,j,k=0;
    const unsigned char *q;
    if (p==0) {
        q=gImage_14;
    } else if (p==1) {
        q=gImage_15;
    }
    else if (p==2) {
        q=gImage_99;//时间设置页面
    }
    else if (p==3) {
        q=gImage_22;//主页面！！！！！！

    }    else if (p==4) {
        q=heart_logo;//主页面

    }    else if (p==61) {
        q=gImage_61;//今日
    } else if (p==62) {
        q=gImage_62;//目标
    } else if (p==63) {
        q=gImage_63;//步
    } else if (p==64) {
        q=gImage_64;//步
    } else if (p==65) {
        q=gImage_65;//步
    }else if (p==66) {
        q=gImage_g;//步
    }else if (p==67) {
        q=gImage_gg;//步
    }


    LCD_Address_Set(x,y,x+length-1,y+width-1);
    for(i=0; i<length; i++)
    {
        for(j=0; j<width; j++)
        {
            LCD_WR_DATA8(*(q+k*2+1));
            LCD_WR_DATA8(*(q+k*2));

            k++;
        }
    }
}
void LCD_ShowPicture_action_foot(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint8_t p)
{
    uint16_t i,j,k=0;
    const unsigned char *q;
    if (p==1) {
        q=gImage_71;
    }
    else if (p==2) {
        q=gImage_72;//时间设置页面
    }
    else if (p==3) {
        q=gImage_73;//主页面
    }    else if (p==4) {
        q=gImage_74;//今日
    } else if (p==5) {
        q=gImage_75;//目标
    } else if (p==6) {
        q=gImage_76;//步
    } else if (p==7) {
        q=gImage_77;//步
    } else if (p==8) {
        q=gImage_78;//步
    }


    LCD_Address_Set(x,y,x+length-1,y+width-1);
    for(i=1118*(p-1); i<1118*p; i++) {
        LCD_WR_DATA8(*(q+k*2+1));
        LCD_WR_DATA8(*(q+k*2));
        k++;
    }

}
void LCD_ShowPicture_action_cal(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint8_t p) {
    uint16_t i,j,k=0;
    const unsigned char *q;
    if (p==1) {
        q=gImage_81;
    }
    else if (p==2) {
        q=gImage_82;//时间设置页面
    }
    else if (p==3) {
        q=gImage_83;//主页面
    }    else if (p==4) {
        q=gImage_84;//今日
    } else if (p==5) {
        q=gImage_85;//目标
    } else if (p==6) {
        q=gImage_86;//步
    } else if (p==7) {
        q=gImage_87;//步
    } else if (p==8) {
        q=gImage_88;//步
    }


    LCD_Address_Set(x,y,x+length-1,y+width-1);
    for(i=2016*(p-1); i<2016*p; i++) {
        LCD_WR_DATA8(*(q+k*2+1));
        LCD_WR_DATA8(*(q+k*2));
        k++;
    }
}


void Show_top(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint16_t back,uint16_t color,uint8_t p)
{
    int j;
    unsigned char picH=0;
    const unsigned char *q;
    if (p==0) {
        q=gImage_16;
    } else if (p==1) {
        q=gImage_17;
    } else if (p==2) {
        q=gImage_18;
    } else if (p==3) {
        q=gImage_19;
    } else if (p==4) {
        q=gImage_20;
    } else if (p==5) {
        q=blue_tool;
    } else if (p==6) {
        q=power;
    } else if (p==7) {
        q=power1;
    } else if (p==8) {
        q=power2;
    } else if (p==9) {
        q=power3;
    } else if (p==10) {
        back=RED;
        q=power4;
    }

    LCD_Address_Set(x,y,x+length-1,y+width-1);
    for(int i=0; i<((length*(width))/8); i++) {
        picH=*(q+i);
        for(j=7; j>-1; j--) {
            if(((picH>>j)%2)) {
                LCD_WR_DATA(back);
            } else {
                LCD_WR_DATA(color);
            }
        }

    }

}

/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片长度
                width  图片宽度
                pic[]  图片数组
      返回值：  无
******************************************************************************/
void Show_roll(uint16_t x,uint16_t y,uint16_t length,uint16_t width,uint16_t ud,uint16_t up_down)
{
    uint16_t i,k=0,g=0,z=0;
    uint16_t uds2,uds3,uds4;


    if (ud==0) {
        uds2=0;
        uds3=0;
        uds4=0;
    } else {
        if(up_down==1) {
            uds2=2*(((ud-1)*60)+20)*55;
            uds3=2*(((ud-1)*60)+40)*55;
            uds4=2*(((ud-1)*60)+60)*55;

        } else {

            uds2=2*(((ud-1)*60)+40)*55;
            uds3=2*(((ud-1)*60)+20)*55;
            uds4=2*(((ud-1)*60))*55;

        }
    }
    LCD_Address_Set(x,y,x+length-1,y+width-1);
    int gg=length*width;
    for(i=0; i<gg; i++)
    {
        LCD_WR_DATA8(*(gImage_21+k*2+uds2));

        LCD_WR_DATA8(*(gImage_21+k*2+1+uds2));

        k++;
    }

    for(i=0; i<gg; i++)
    {
        LCD_WR_DATA8(*(gImage_21+g*2+uds3));

        LCD_WR_DATA8(*(gImage_21+g*2+1+uds3));

        g++;
    }
    for(i=0; i<gg; i++)
    {
        LCD_WR_DATA8(*(gImage_21+z*2+uds4));

        LCD_WR_DATA8(*(gImage_21+z*2+1+uds4));

        z++;
    }
}
//显示16*48的数字//两个
void Word48(uint16_t x,uint16_t y,uint16_t color,uint8_t p)
{
    int fist=get_number_c(p,2);
    int late=get_number_c(p,1);
    int j,k=0;
    int length=16;
    int width=48;
    unsigned char picH=0;
    const unsigned char *q;
    const unsigned char *q2;

    if (fist==0) {
        q=gImage_30;
    } else if (fist==1) {
        q=gImage_31;
    } else if (fist==2) {
        q=gImage_32;
    } else if (fist==3) {
        q=gImage_33;
    } else if (fist==4) {
        q=gImage_34;
    } else if (fist==5) {
        q=gImage_35;
    } else if (fist==6) {
        q=gImage_36;
    } else if (fist==7) {
        q=gImage_37;
    } else if (fist==8) {
        q=gImage_38;
    } else if (fist==9) {
        q=gImage_39;
    }
    if (late==0) {
        q2=gImage_30;
    } else if (late==1) {
        q2=gImage_31;
    } else if (late==2) {
        q2=gImage_32;
    } else if (late==3) {
        q2=gImage_33;
    } else if (late==4) {
        q2=gImage_34;
    } else if (late==5) {
        q2=gImage_35;
    } else if (late==6) {
        q2=gImage_36;
    } else if (late==7) {
        q2=gImage_37;
    } else if (late==8) {
        q2=gImage_38;
    } else if (late==9) {
        q2=gImage_39;
    }

    for(int i=0; i<96; i++) {
        picH=*(q+i);
        for(j=7; j>-1; j--) {
            if(((picH>>j)%2)) {
                LCD_Address_Set(x+7-j+(i%2)*8,(i/2)+y,x+7-j+(i%2)*8,(i/2)+y);
                LCD_WR_DATA(color);
            }
        }

    }
    x=x+20;
    for(int i=0; i<96; i++) {
        picH=*(q2+i);
        for(j=7; j>-1; j--) {
            if(((picH>>j)%2)) {
                LCD_Address_Set(x+7-j+(i%2)*8,(i/2)+y,x+7-j+(i%2)*8,(i/2)+y);
                LCD_WR_DATA(color);
            }
        }

    }

}
//显示16*23的数字//点显示//两个
void Word23(uint16_t x,uint16_t y,uint16_t color,uint16_t p)
{
    int fist=get_number_c(p,2);
    int late=get_number_c(p,1);

    int h=0,t=0;
    int j,k=0;
    int length=16;
    int width=23;
    unsigned char picH=0;
    const unsigned char *q;
    const unsigned char *q2;

    if (fist==0) {
        q=gImage_40;
    } else if (fist==1) {
        q=gImage_41;
    } else if (fist==2) {
        q=gImage_42;
    } else if (fist==3) {
        q=gImage_43;
    } else if (fist==4) {
        q=gImage_44;
    } else if (fist==5) {
        q=gImage_45;
    } else if (fist==6) {
        q=gImage_46;
    } else if (fist==7) {
        q=gImage_47;
    } else if (fist==8) {
        q=gImage_48;
    } else if (fist==9) {
        q=gImage_49;
    }
    if (late==0) {
        q2=gImage_40;
    } else if (late==1) {
        q2=gImage_41;
    } else if (late==2) {
        q2=gImage_42;
    } else if (late==3) {
        q2=gImage_43;
    } else if (late==4) {
        q2=gImage_44;
    } else if (late==5) {
        q2=gImage_45;
    } else if (late==6) {
        q2=gImage_46;
    } else if (late==7) {
        q2=gImage_47;
    } else if (late==8) {
        q2=gImage_48;
    } else if (late==9) {
        q2=gImage_49;
    }

    for(int i=0; i<46; i++) {
        picH=*(q+i);
        for(j=7; j>-1; j--) {
            if(((picH>>j)%2)) {
                LCD_Address_Set(x+7-j+(i%2)*8,(i/2)+y,x+7-j+(i%2)*8,(i/2)+y);
                LCD_WR_DATA(color);
            }
        }
    }
    x=x+20;

    for(int i=0; i<46; i++) {
        picH=*(q2+i);
        for(j=7; j>-1; j--) {
            if(((picH>>j)%2)) {
                LCD_Address_Set(x+7-j+(i%2)*8,(i/2)+y,x+7-j+(i%2)*8,(i/2)+y);
                LCD_WR_DATA(color);
            }
        }
    }

}
//刷新
void Refresh(uint8_t p)
{
    uint16_t x, y, length, width;
    uint16_t i,j,k=0;
    const unsigned char *q;
    if (p==0) {
        q=gImage_50;
        x=20;
        y=57;
        length=40;
        width=23;
    } else if(p==1) {
        q=gImage_51;
        x=73;
        y=57;
        length=40;
        width=23;
    }
    else if(p==2) {
        q=gImage_52;
        x=21;
        y=111;
        length=40;
        width=48;
    }
    else if(p==3) {
        q=gImage_53;
        x=72;
        y=111;
        length=40;
        width=48;
    }

    LCD_Address_Set(x,y,x+length-1,y+width-1);
    for(i=0; i<length; i++)
    {
        for(j=0; j<width; j++)
        {
            LCD_WR_DATA8(*(q+k*2+1));
            LCD_WR_DATA8(*(q+k*2));

            k++;
        }
    }
}


void Word23_sig(uint16_t x,uint16_t y,uint16_t color,uint16_t p)
{
    int late=p;

    int h=0,t=0;
    int j,k=0;
    int length=16;
    int width=23;
    unsigned char picH=0;
    const unsigned char *q2;


    if (late==0) {
        q2=gImage_40;
    } else if (late==1) {
        q2=gImage_41;
    } else if (late==2) {
        q2=gImage_42;
    } else if (late==3) {
        q2=gImage_43;
    } else if (late==4) {
        q2=gImage_44;
    } else if (late==5) {
        q2=gImage_45;
    } else if (late==6) {
        q2=gImage_46;
    } else if (late==7) {
        q2=gImage_47;
    } else if (late==8) {
        q2=gImage_48;
    } else if (late==9) {
        q2=gImage_49;
    }



    for(int i=0; i<46; i++) {
        picH=*(q2+i);
        for(j=7; j>-1; j--) {
            if(((picH>>j)%2)) {
                LCD_Address_Set(x+7-j+(i%2)*8,(i/2)+y,x+7-j+(i%2)*8,(i/2)+y);
                LCD_WR_DATA(color);
            }
        }
    }

}
