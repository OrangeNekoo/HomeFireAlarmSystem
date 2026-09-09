/* Common/oled.c — SSD1306 0.96寸 128×64，I2C 软件模拟（约 350kHz） */
/* 模块 QG-2864TMBEG01（BS[2:0]=010 选 I2C），从地址 0x3C，写地址 0x78 */
#include <ioCC2530.h>
#include <intrinsics.h>       /* __no_operation 内建函数声明（消除 Pe223 隐式声明警告，任务 2 经验） */
#include "oled.h"
#include "delay.h"
#include "font16.h"

#define OLED_ADDR 0x78          /* 上屏失败改试 0x7A（0x3D） */

void LCD_Fill(unsigned char bmp_dat);     /* 前置声明：LCD_Init 先于定义处调用 */

#define SCL_H() (P1_2 = 1)
#define SCL_L() (P1_2 = 0)
#define SDA_H() (P1DIR &= ~0x08)          /* SDA 释放为高阻，靠模块板载上拉 */
#define SDA_L() (P1_3 = 0, P1DIR |= 0x08) /* SDA 推挽拉低 */

static void i2c_dly(void)                 /* 半周期约 0.8us @32MHz */
{
    __no_operation(); __no_operation(); __no_operation();
    __no_operation(); __no_operation(); __no_operation();
}
static void i2c_start(void)
{
    SDA_H(); SCL_H(); i2c_dly();
    SDA_L(); i2c_dly();
    SCL_L();
}
static void i2c_stop(void)
{
    SDA_L(); i2c_dly();
    SCL_H(); i2c_dly();
    SDA_H(); i2c_dly();
}
static void i2c_wr_byte(unsigned char dat)    /* 8 位数据 + 第 9 位读 ACK（不校验） */
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        if(dat & 0x80) SDA_H(); else SDA_L();
        dat <<= 1;
        i2c_dly();
        SCL_H(); i2c_dly();
        SCL_L();
    }
    SDA_H();                     /* 释放 SDA 读 ACK */
    i2c_dly();
    SCL_H(); i2c_dly();
    SCL_L();
}
/* —— SSD1306 事务封装（I2C 控制字节：0x00 命令流 / 0x40 数据流） —— */
static void oled_cmd(unsigned char c)
{
    i2c_start();
    i2c_wr_byte(OLED_ADDR);
    i2c_wr_byte(0x00);
    i2c_wr_byte(c);
    i2c_stop();
}
static void oled_data(unsigned char d)
{
    i2c_start();
    i2c_wr_byte(OLED_ADDR);
    i2c_wr_byte(0x40);
    i2c_wr_byte(d);
    i2c_stop();
}
/* —— 显示层（签名与示例代码一致） —— */
void LCD_WrCmd(unsigned char cmd) { oled_cmd(cmd); }
void LCD_WrDat(unsigned char dat) { oled_data(dat); }
void LCD_Set_Pos(unsigned char x, unsigned char y)
{
    LCD_WrCmd(0xb0 + y);
    LCD_WrCmd(((x & 0xf0) >> 4) | 0x10);
    LCD_WrCmd(x & 0x0f);        /* 示例代码此处误写 |0x01 会整体偏移 1 列，I2C 版修正 */
}
void LCD_Init(void)
{
    P1SEL &= ~0x0C;             /* P1.2/P1.3 普通 IO */
    P1DIR |= 0x04;              /* SCL 输出；SDA 保持输入（释放） */
    SCL_H(); SDA_H();
    Delay_ms(100);              /* I2C 模块无复位脚，等上电稳定 */
    LCD_WrCmd(0xae); LCD_WrCmd(0x00); LCD_WrCmd(0x10); LCD_WrCmd(0x40);
    LCD_WrCmd(0x81); LCD_WrCmd(0xcf); LCD_WrCmd(0xa1); LCD_WrCmd(0xc8);
    LCD_WrCmd(0xa6); LCD_WrCmd(0xa8); LCD_WrCmd(0x3f); LCD_WrCmd(0xd3);
    LCD_WrCmd(0x00); LCD_WrCmd(0xd5); LCD_WrCmd(0x80); LCD_WrCmd(0xd9);
    LCD_WrCmd(0xf1); LCD_WrCmd(0xda); LCD_WrCmd(0x12); LCD_WrCmd(0xdb);
    LCD_WrCmd(0x40); LCD_WrCmd(0x20); LCD_WrCmd(0x02); LCD_WrCmd(0x8d);
    LCD_WrCmd(0x14);            /* 电荷泵使能 */
    LCD_WrCmd(0xa4); LCD_WrCmd(0xa6);
    LCD_WrCmd(0xaf);            /* display ON */
    LCD_Fill(0x00);
}
void LCD_Fill(unsigned char bmp_dat)
{
    unsigned char y, x;
    for(y = 0; y < 8; y++)
    {
        LCD_WrCmd(0xb0 + y);
        LCD_WrCmd(0x00); LCD_WrCmd(0x10);
        for(x = 0; x < 128; x++) LCD_WrDat(bmp_dat);
    }
}
void LCD_CLS(void) { LCD_Fill(0x00); }
void LCD_Invert(unsigned char on) { LCD_WrCmd(on ? 0xA7 : 0xA6); }
/***************功能描述：显示6*8一组标准ASCII字符串    显示的坐标（x,y），y为页范围0～7****************/
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
/*******************功能描述：显示8*16一组标准ASCII字符串     显示的坐标（x,y），y为页范围0～7****************/
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
/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void LCD_P16x16Ch(unsigned char x, unsigned char y, unsigned char N)  /* N = 汉字索引 */
{
    unsigned char wm;
    unsigned int adder = 32 * N;
    LCD_Set_Pos(x, y);
    for(wm = 0; wm < 16; wm++) LCD_WrDat(F16x16[adder++]);
    LCD_Set_Pos(x, y + 1);
    for(wm = 0; wm < 16; wm++) LCD_WrDat(F16x16[adder++]);
}
