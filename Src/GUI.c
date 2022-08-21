#include "stm32f1xx.h"
#include "gui.h"
#include "font.h"

uint16_t LCD_BGR2RGB(uint16_t c)
{
    uint16_t  r,g,b,rgb;
    b=(c>>0)&0x1f;
    g=(c>>5)&0x3f;
    r=(c>>11)&0x1f;
    rgb=(b<<11)+(g<<5)+(r<<0);
    return(rgb);
}

void Gui_Circle(uint16_t X,uint16_t Y,uint16_t R,uint16_t fc)
{
    unsigned short  a,b;
    int c;
    a=0;
    b=R;
    c=3-2*R;
    while (a<b)
    {
        Gui_DrawPoint(X+a,Y+b,fc);     //        7
        Gui_DrawPoint(X-a,Y+b,fc);     //        6
        Gui_DrawPoint(X+a,Y-b,fc);     //        2
        Gui_DrawPoint(X-a,Y-b,fc);     //        3
        Gui_DrawPoint(X+b,Y+a,fc);     //        8
        Gui_DrawPoint(X-b,Y+a,fc);     //        5
        Gui_DrawPoint(X+b,Y-a,fc);     //        1
        Gui_DrawPoint(X-b,Y-a,fc);     //        4

        if(c<0) c=c+4*a+6;
        else
        {
            c=c+4*(a-b)+10;
            b-=1;
        }
        a+=1;
    }
    if (a==b)
    {
        Gui_DrawPoint(X+a,Y+b,fc);
        Gui_DrawPoint(X+a,Y+b,fc);
        Gui_DrawPoint(X+a,Y-b,fc);
        Gui_DrawPoint(X-a,Y-b,fc);
        Gui_DrawPoint(X+b,Y+a,fc);
        Gui_DrawPoint(X-b,Y+a,fc);
        Gui_DrawPoint(X+b,Y-a,fc);
        Gui_DrawPoint(X-b,Y-a,fc);
    }

}

void Gui_DrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,uint16_t Color)
{
    int dx,             // difference in x's
    dy,             // difference in y's
    dx2,            // dx,dy * 2
    dy2,
            x_inc,          // amount in pixel space to move during drawing
    y_inc,          // amount in pixel space to move during drawing
    error,          // the discriminant i.e. error i.e. decision variable
    index;          // used for looping


    Lcd_SetXY(x0,y0);
    dx = x1-x0;
    dy = y1-y0;

    if (dx>=0)
    {
        x_inc = 1;
    }
    else
    {
        x_inc = -1;
        dx    = -dx;
    }

    if (dy>=0)
    {
        y_inc = 1;
    }
    else
    {
        y_inc = -1;
        dy    = -dy;
    }

    dx2 = dx << 1;
    dy2 = dy << 1;

    if (dx > dy)
    {
        // initialize error term
        error = dy2 - dx;

        // draw the line
        for (index=0; index <= dx; index++)
        {

            Gui_DrawPoint(x0,y0,Color);

            // test if error has overflowed
            if (error >= 0)
            {
                error-=dx2;

                // move to next line
                y0+=y_inc;
            } // end if error overflowed

            // adjust the error term
            error+=dy2;

            // move to the next pixel
            x0+=x_inc;
        } // end for
    } // end if |slope| <= 1
    else
    {
        // initialize error term
        error = dx2 - dy;

        // draw the line
        for (index=0; index <= dy; index++)
        {
            // set the pixel
            Gui_DrawPoint(x0,y0,Color);

            // test if error overflowed
            if (error >= 0)
            {
                error-=dy2;

                // move to next line
                x0+=x_inc;
            } // end if error overflowed

            // adjust the error term
            error+=dx2;

            // move to the next pixel
            y0+=y_inc;
        } // end for
    } // end else |slope| > 1
}



void Gui_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t bc)
{
    Gui_DrawLine(x,y,x+w,y,0xEF7D);
    Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
    Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
    Gui_DrawLine(x,y,x,y+h,0xEF7D);
    Gui_DrawLine(x+1,y+1,x+1+w-2,y+1+h-2,bc);
}
void Gui_box2(uint16_t x,uint16_t y,uint16_t w,uint16_t h, uint8_t mode)
{
    if (mode==0)	{
        Gui_DrawLine(x,y,x+w,y,0xEF7D);
        Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
        Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
        Gui_DrawLine(x,y,x,y+h,0xEF7D);
    }
    if (mode==1)	{
        Gui_DrawLine(x,y,x+w,y,0x2965);
        Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xEF7D);
        Gui_DrawLine(x,y+h,x+w,y+h,0xEF7D);
        Gui_DrawLine(x,y,x,y+h,0x2965);
    }
    if (mode==2)	{
        Gui_DrawLine(x,y,x+w,y,0xffff);
        Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xffff);
        Gui_DrawLine(x,y+h,x+w,y+h,0xffff);
        Gui_DrawLine(x,y,x,y+h,0xffff);
    }
}


void DisplayButtonDown(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    Gui_DrawLine(x1,  y1,  x2,y1, GRAY2);  //H
    Gui_DrawLine(x1+1,y1+1,x2,y1+1, GRAY1);  //H
    Gui_DrawLine(x1,  y1,  x1,y2, GRAY2);  //V
    Gui_DrawLine(x1+1,y1+1,x1+1,y2, GRAY1);  //V
    Gui_DrawLine(x1,  y2,  x2,y2, WHITE);  //H
    Gui_DrawLine(x2,  y1,  x2,y2, WHITE);  //V
}

void DisplayButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    Gui_DrawLine(x1,  y1,  x2,y1, WHITE); //H
    Gui_DrawLine(x1,  y1,  x1,y2, WHITE); //V

    Gui_DrawLine(x1+1,y2-1,x2,y2-1, GRAY1);  //H
    Gui_DrawLine(x1,  y2,  x2,y2, GRAY2);  //H
    Gui_DrawLine(x2-1,y1+1,x2-1,y2, GRAY1);  //V
    Gui_DrawLine(x2  ,y1  ,x2,y2, GRAY2); //V
}

void Gui_DrawFont_GBK(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc,uint8_t size, uint8_t *s)
{
    unsigned char i,j;
    unsigned short k,x0;
    unsigned short height = size;
    unsigned short width = size/2;
    uint8_t temp;
    x0=x;

    while(*s)
    {
        if((*s) < 128)
        {
            k=*s;
            if (k==13)
            {
                x=x0;
                y+=16;
            }
            else
            {
                if (k>32) k-=32; else k=0;

                for(i=0;i<height;i++)    //高度
                    for(j=0;j<width;j++) //宽度
                    {
                        switch (size) {
                            case 12:
                                temp = asc2_1206[k][i];
                                break;
                            case 16:
                                temp = asc2_1608[k][i];
                                break;
                            default:
                                temp = asc2_1206[k][i];
                        }
                        if(temp&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
                        else
                        {
                            if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
                        }
                    }
                x+=width;  //两个数之间的间隔
            }
            s++;
        }

        else
        {


            for (k=0;k<hz16_num;k++)
            {
                if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
                {
                    for(i=0;i<16;i++)
                    {
                        for(j=0;j<8;j++)
                        {
                            if(hz16[k].Msk[i*2]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
                            else {
                                if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
                            }
                        }
                        for(j=0;j<8;j++)
                        {
                            if(hz16[k].Msk[i*2+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
                            else
                            {
                                if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
                            }
                        }
                    }
                }
            }
            s+=2;x+=16;
        }

    }
}

void showimage(const unsigned char *p)
{
    int i,j,k;
    unsigned char picH,picL;
    Lcd_Clear(WHITE);
    Lcd_SetRegion(0,0,127,127);
    for(i=0;i<128*128;i++)
    {
        picL=*(p+i*2);
        picH=*(p+i*2+1);
        LCD_WriteData_16Bit(picH<<8|picL);
    }
}