/* TempNode/main.c — 温湿度节点（ID=0x02） */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#include "..\Common\rtc.h"
#include "..\Common\frame.h"
#include "..\Common\rf.h"
#include "dht11.h"
#include "..\Common\easter_frames.h"
#define NODE_ID 0x02
#define LED_ALARM P1_0                /* 核心板 LED1，低电平点亮 */

static u8 page_alarm = 0;             /* 1=火灾警报页 */
static u8 temp_i = 0, temp_d = 0, hum_i = 0, hum_d = 0;
static u8 dirty = 0;
static u8 easter_on = 0;
static u8 easter_frame = 0;
static u32 easter_next_ms = 0;

static void draw_time_row(void)
{
    char b[17];
    rtc_fmt(b);
    LCD_P8x16Str(0, 0, (u8 *)b);
}
static void draw_data_rows(void)
{
    char b[8];
    /* 行1（页2）：温度:xx.x℃ */
    LCD_P16x16Ch(0, 2, 0);  LCD_P16x16Ch(16, 2, 2);
    b[0]=':'; b[1]='0'+temp_i/10; b[2]='0'+temp_i%10;
    b[3]='.'; b[4]='0'+temp_d; b[5]='\0';
    LCD_P8x16Str(32, 2, (u8 *)b);
    LCD_P16x16Ch(72, 2, 16);          /* ℃ */
    /* 行2（页4）：湿度:xx.x% */
    LCD_P16x16Ch(0, 4, 1);  LCD_P16x16Ch(16, 4, 2);
    b[0]=':'; b[1]='0'+hum_i/10; b[2]='0'+hum_i%10;
    b[3]='.'; b[4]='0'+hum_d; b[5]='%'; b[6]='\0';
    LCD_P8x16Str(32, 4, (u8 *)b);
    /* 行3（页6）：节点标识 */
    LCD_P8x16Str(40, 6, (u8 *)"NODE 2");
}
static void draw_alarm_page(void)
{
    LCD_CLS();
    LCD_P16x16Ch(32, 3, 10); LCD_P16x16Ch(48, 3, 11);
    LCD_P16x16Ch(64, 3, 12); LCD_P16x16Ch(80, 3, 13);   /* 火灾警报 居中 */
    LCD_Invert(1);
}
static void draw_main_page(void)
{
    LCD_CLS();
    LCD_Invert(0);
    draw_time_row();
    draw_data_rows();
}
static void easter_tick(u32 now)
{
    if(!easter_on || now < easter_next_ms) return;
    LCD_DrawBitmap64(easter_frames[easter_frame]);
    easter_frame = (easter_frame + 1) % 30;
    easter_next_ms = now + 100;
}
static void send_report(void)
{
    u8 d[5], buf[FRAME_MAX_LEN], n;
    static u8 seq = 0;
    d[0] = ++seq; d[1] = temp_i; d[2] = temp_d; d[3] = hum_i; d[4] = hum_d;
    n = frame_pack(buf, NODE_ID, 0x01, 0x01, d, 5);
    RF_Send(buf, n);
}
static void handle_rf(void)
{
    u8 src, dst, cmd, out[FRAME_MAX_LEN], n;
    if(!rf_rxLen) return;
    n = frame_parse((const u8 *)rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
    rf_rxLen = 0;
    if(!n || (dst != NODE_ID && dst != 0xFF)) return;
    if(cmd == 0x02 && n == 6)                 /* 对时广播 */
    {
        rtc_set(out);
        if(!page_alarm && !easter_on) draw_time_row();
    }
    else if(cmd == 0x03 && n == 2)            /* 报警状态广播 */
    {
        u8 new_page_alarm = (out[0] & 0x01) ? 1 : 0;
        if(new_page_alarm != page_alarm)
        {
            page_alarm = new_page_alarm;
            if(!easter_on)
            {
                if(page_alarm) draw_alarm_page();
                else draw_main_page();
            }
        }
    }
    else if(cmd == 0x04 && n == 1)            /* 彩蛋播放状态广播 */
    {
        if((out[0] & 0x01) && !easter_on)
        {
            easter_on = 1;
            easter_frame = 0;
            LCD_CLS();
            LCD_DrawBitmap64(easter_frames[easter_frame]);
            easter_next_ms = ms_get() + 100;
        }
        else if(!(out[0] & 0x01) && easter_on)
        {
            easter_on = 0;
            if(page_alarm) draw_alarm_page();
            else draw_main_page();
        }
    }
}
void main(void)
{
    u32 last_1s = 0, last_2s = 0;
    u8  last_min = 0xFF;
    CLK_Init();
    T1_Init();
    RF_Init();
    P1SEL &= ~0x01; P1DIR |= 0x01; LED_ALARM = 1;
    LCD_Init(); LCD_CLS();
    draw_time_row(); draw_data_rows();
    while(1)
    {
        u32 now = ms_get();               /* 每圈取一次原子时间，圈内共用 */
        if(now - last_1s >= 1000)
        {
            last_1s = (now - last_1s > 5000) ? now : last_1s + 1000;   /* 卡顿过久直接对齐防连跳 */
            rtc_sec_tick();
            if(!easter_on && page_alarm) LCD_Invert(g_rtc.sec & 1);   /* 报警页 1Hz 反显闪烁 */
            else if(!easter_on && g_rtc.min != last_min) { last_min = g_rtc.min; draw_time_row(); }
        }
        if(now - last_2s >= 2000)
        {
            last_2s += 2000;
            EA = 0;                     /* DHT11 时序 ~5ms，期间丢 RF 帧可接受（2s 周期） */
            if(DHT11_Read(&temp_i, &temp_d, &hum_i, &hum_d)) dirty = 1;
            EA = 1;
            send_report();              /* 数据包即心跳 */
            if(dirty && !page_alarm && !easter_on) { draw_data_rows(); dirty = 0; }
        }
        handle_rf();
        easter_tick(now);
        LED_ALARM = (page_alarm && ((now / 500) & 1)) ? 0 : 1;   /* 500ms 翻转 */
    }
}
