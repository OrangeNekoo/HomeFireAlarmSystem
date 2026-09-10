/* Common/oled.c — SSD1306 0.96寸 128×64，4线SPI 软件模拟 */
/* 引脚与初始化严格参照 docs/OLED资料/LCD_OLED示例代码/LCD.h（模块实测为 SPI 接线） */
#include <ioCC2530.h>
#include "oled.h"
#include "delay.h"
#include "font16.h"

#define LCD_SCL P1_2       /* SCLK  时钟 D0（SCLK） */
#define LCD_SDA P1_3       /* SDA   D1（MOSI） 数据 */
#define LCD_RST P1_7       /* _RES  hardware reset   复位 */
#define LCD_DC  P0_0       /* A0  H/L 命令数据选通端，H：数据，L:命令 */

/*********************LCD写数据（照示例代码）********************/
void LCD_WrDat(unsigned char dat)
{
    unsigned char i;
    LCD_DC = 1;                 /* 高：数据 */
    for(i = 0; i < 8; i++)
    {
        LCD_SCL = 0;
        if(dat & 0x80) LCD_SDA = 1; else LCD_SDA = 0;
        LCD_SCL = 1;
        dat <<= 1;
    }
}
/*********************LCD写命令（照示例代码）********************/
void LCD_WrCmd(unsigned char cmd)
{
    unsigned char i;
    LCD_DC = 0;                 /* 低：命令 */
    for(i = 0; i < 8; i++)
    {
        LCD_SCL = 0;
        if(cmd & 0x80) LCD_SDA = 1; else LCD_SDA = 0;
        LCD_SCL = 1;
        cmd <<= 1;
    }
}
/*********************LCD 设置坐标********************/
void LCD_Set_Pos(unsigned char x, unsigned char y)
{
    LCD_WrCmd(0xb0 + y);
    LCD_WrCmd(((x & 0xf0) >> 4) | 0x10);
    LCD_WrCmd(x & 0x0f);        /* 示例原文 |0x01 会造成列偏移不均匀，按标准命令格式修正 */
}
/*********************LCD全屏填充********************/
void LCD_Fill(unsigned char bmp_dat)
{
    unsigned char y, x;
    for(y = 0; y < 8; y++)
    {
        LCD_WrCmd(0xb0 + y);
        LCD_WrCmd(0x00);        /* 示例原文 0x01 同源列偏移，修正 */
        LCD_WrCmd(0x10);
        for(x = 0; x < 128; x++) LCD_WrDat(bmp_dat);
    }
}
/*********************LCD清屏********************/
void LCD_CLS(void)
{
    LCD_Fill(0x00);
}
/*********************整屏反显（报警界面用）********************/
void LCD_Invert(unsigned char on)
{
    LCD_WrCmd(on ? 0xA7 : 0xA6);
}
/*********************LCD初始化（照示例代码）********************/
void LCD_Init(void)
{
    P0SEL &= 0xFE;              /* P0.0 普通 IO */
    P0DIR |= 0x01;              /* P0.0 输出（DC） */

    P1SEL &= 0x73;              /* P1.2/P1.3/P1.7 普通 IO */
    P1DIR |= 0x8C;              /* P1.2/P1.3/P1.7 输出 */

    LCD_SCL = 1;
    LCD_RST = 0;                /* 硬件复位（SPI 模块必须） */
    Delay_ms(50);
    LCD_RST = 1;                /* 等待 RC 复位完毕 */

    LCD_WrCmd(0xae);            /* turn off oled panel */
    LCD_WrCmd(0x00);            /* set low column address */
    LCD_WrCmd(0x10);            /* set high column address */
    LCD_WrCmd(0x40);            /* set start line address */
    LCD_WrCmd(0x81);            /* set contrast control register */
    LCD_WrCmd(0xcf);            /* Set SEG Output Current Brightness */
    LCD_WrCmd(0xa1);            /* Set SEG/Column Mapping 0xa1正常 */
    LCD_WrCmd(0xc8);            /* Set COM/Row Scan Direction 0xc8正常 */
    LCD_WrCmd(0xa6);            /* normal display */
    LCD_WrCmd(0xa8);            /* multiplex ratio(1 to 64) */
    LCD_WrCmd(0x3f);            /* 1/64 duty */
    LCD_WrCmd(0xd3);            /* set display offset */
    LCD_WrCmd(0x00);            /* not offset */
    LCD_WrCmd(0xd5);            /* set display clock divide ratio/oscillator frequency */
    LCD_WrCmd(0x80);            /* 100 Frames/Sec */
    LCD_WrCmd(0xd9);            /* set pre-charge period */
    LCD_WrCmd(0xf1);            /* Pre-Charge as 15 Clocks & Discharge as 1 Clock */
    LCD_WrCmd(0xda);            /* set com pins hardware configuration */
    LCD_WrCmd(0x12);
    LCD_WrCmd(0xdb);            /* set vcomh */
    LCD_WrCmd(0x40);            /* Set VCOM Deselect Level */
    LCD_WrCmd(0x20);            /* Set Page Addressing Mode */
    LCD_WrCmd(0x02);
    LCD_WrCmd(0x8d);            /* set Charge Pump enable/disable */
    LCD_WrCmd(0x14);            /* enable */
    LCD_WrCmd(0xa4);            /* Disable Entire Display On */
    LCD_WrCmd(0xa6);            /* Disable Inverse Display On */
    LCD_WrCmd(0xaf);            /* turn on oled panel */

    LCD_Fill(0x00);             /* 清屏 */
    LCD_Set_Pos(0, 0);
}
/***************功能描述：显示6*8一组标准ASCII字符串（照示例代码）****************/
void LCD_P6x8Str(unsigned char x, unsigned char y, unsigned char ch[])
{
    unsigned char c = 0, i = 0, j = 0;
    while(ch[j] != '\0')
    {
        c = ch[j] - 32;
        if(x > 126) { x = 0; y++; }
        LCD_Set_Pos(x, y);
        for(i = 0; i < 6; i++)
            LCD_WrDat(F6x8[c][i]);
        x += 6;
        j++;
    }
}
/*******************功能描述：显示8*16一组标准ASCII字符串（照示例代码）*******************/
void LCD_P8x16Str(unsigned char x, unsigned char y, unsigned char ch[])
{
    unsigned char c = 0, i = 0, j = 0;
    while(ch[j] != '\0')
    {
        c = ch[j] - 32;
        if(x > 120) { x = 0; y++; }
        LCD_Set_Pos(x, y);
        for(i = 0; i < 8; i++)
            LCD_WrDat(F8X16[c * 16 + i]);
        LCD_Set_Pos(x, y + 1);
        for(i = 0; i < 8; i++)
            LCD_WrDat(F8X16[c * 16 + i + 8]);
        x += 8;
        j++;
    }
}
/*****************功能描述：显示16*16点阵汉字（照示例代码，N=字模索引）*****************/
void LCD_P16x16Ch(unsigned char x, unsigned char y, unsigned char N)
{
    unsigned char wm;
    unsigned int adder = 32 * N;
    LCD_Set_Pos(x, y);
    for(wm = 0; wm < 16; wm++)
    {
        LCD_WrDat(F16x16[adder]);
        adder += 1;
    }
    LCD_Set_Pos(x, y + 1);
    for(wm = 0; wm < 16; wm++)
    {
        LCD_WrDat(F16x16[adder]);
        adder += 1;
    }
}
