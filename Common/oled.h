/* Common/oled.h — SSD1306 0.96寸 128x64 I2C 驱动接口 */
#ifndef OLED_H
#define OLED_H

void LCD_Init(void);                                        /* 初始化（含清屏） */
void LCD_CLS(void);                                         /* 全屏清零 */
void LCD_WrCmd(unsigned char cmd);                          /* 写命令 */
void LCD_WrDat(unsigned char dat);                          /* 写数据 */
void LCD_Set_Pos(unsigned char x, unsigned char y);         /* 设置坐标（x列0~127，y页0~7） */
void LCD_P6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);   /* 6x8 ASCII 字符串 */
void LCD_P8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);  /* 8x16 ASCII 字符串 */
void LCD_P16x16Ch(unsigned char x, unsigned char y, unsigned char N);     /* 16x16 汉字，N=字库索引 */
void LCD_Invert(unsigned char on);                          /* 反显开关（1=反显 0=正常） */
void LCD_DrawBitmap64(const unsigned char __code *bitmap);    /* 居中绘制逐行 MSB-first 64x64 位图 */

#endif /* OLED_H */
