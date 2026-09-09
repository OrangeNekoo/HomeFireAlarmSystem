/* Master/main.c — 任务 3 验证：主节点静态界面（全部 17 字 + ASCII） */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#define NODE_ID 0x01
void main(void)
{
    CLK_Init();
    LCD_Init();
    LCD_CLS();
    /* 行0：日期时间占位（页0） */
    LCD_P8x16Str(0, 0, "2026:09:08 16:30");
    /* 行1：温度:25℃（页2） */
    LCD_P16x16Ch(0, 2, 0);            /* 温 */
    LCD_P16x16Ch(16, 2, 2);           /* 度 */
    LCD_P8x16Str(32, 2, ":25");
    LCD_P16x16Ch(56, 2, 16);          /* ℃ */
    /* 行2：湿度:60%（页4） */
    LCD_P16x16Ch(0, 4, 1);            /* 湿 */
    LCD_P16x16Ch(16, 4, 2);           /* 度 */
    LCD_P8x16Str(32, 4, ":60%");
    /* 行3：有害气体:正常（页6） */
    LCD_P16x16Ch(0, 6, 3);            /* 有 */
    LCD_P16x16Ch(16, 6, 4);           /* 害 */
    LCD_P16x16Ch(32, 6, 5);           /* 气 */
    LCD_P16x16Ch(48, 6, 6);           /* 体 */
    LCD_P8x16Str(64, 6, ":");
    LCD_P16x16Ch(72, 6, 7);           /* 正 */
    LCD_P16x16Ch(88, 6, 9);           /* 常 */
    while(1) { }
}
