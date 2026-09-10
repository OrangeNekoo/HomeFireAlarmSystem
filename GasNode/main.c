/* GasNode/main.c — 气体节点（ID=0x03） */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#include "..\Common\rtc.h"
#include "..\Common\frame.h"
#include "..\Common\rf.h"
#include "adc.h"
#define NODE_ID 0x03
#define LED_ALARM P1_0                /* 核心板 LED1，低电平点亮 */
#define MQ2_DO P0_5                   /* DO：超模块电位器阈值为低 */

static u8  page_alarm = 0;            /* 1=火灾警报页 */
static u16 gas_avg = 0;               /* 滑动平均后的 ADC 浓度值 */

static void draw_time_row(void)       /* 与 TempNode 相同实现 */
{
    char b[17];
    rtc_fmt(b);
    LCD_P8x16Str(0, 0, (u8 *)b);
}
static void draw_data_rows(void)
{
    char b[6];
    /* 行1（页2）：有害气体:正常/异常（按 DO 判） */
    LCD_P16x16Ch(0, 2, 3); LCD_P16x16Ch(16, 2, 4);
    LCD_P16x16Ch(32, 2, 5); LCD_P16x16Ch(48, 2, 6);
    b[0] = ':'; b[1] = '\0';
    LCD_P8x16Str(64, 2, (u8 *)b);
    if(MQ2_DO == 0) { LCD_P16x16Ch(72, 2, 8); LCD_P16x16Ch(88, 2, 9); }   /* 异常 */
    else            { LCD_P16x16Ch(72, 2, 7); LCD_P16x16Ch(88, 2, 9); }   /* 正常 */
    /* 行2（页4）：ADC:xxxx（平均后浓度值） */
    b[0] = '0' + gas_avg / 1000;
    b[1] = '0' + gas_avg / 100 % 10;
    b[2] = '0' + gas_avg / 10 % 10;
    b[3] = '0' + gas_avg % 10;
    b[4] = '\0';
    LCD_P8x16Str(0, 4, (u8 *)"ADC:");
    LCD_P8x16Str(32, 4, (u8 *)b);
    /* 行3（页6）：节点标识 */
    LCD_P8x16Str(40, 6, (u8 *)"NODE 3");
}
static void draw_warmup(u8 s)         /* 预热倒计时（剩余 s 秒，2s 步进） */
{
    char b[12];
    b[0]='W'; b[1]='A'; b[2]='R'; b[3]='M'; b[4]=' '; b[5]='U'; b[6]='P'; b[7]=' ';
    b[8]='0'+s/10%10; b[9]='0'+s%10; b[10]='s'; b[11]='\0';
    LCD_P8x16Str(16, 4, (u8 *)b);
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
static void send_report(void)         /* 上报帧 [seq,adc_hi,adc_lo,do] 4B -> 主节点 */
{
    u8 d[4], buf[FRAME_MAX_LEN], n;
    static u8 seq = 0;
    d[0] = ++seq;
    d[1] = (u8)(gas_avg >> 8); d[2] = (u8)(gas_avg & 0xFF);
    d[3] = (MQ2_DO == 0) ? 1 : 0;
    n = frame_pack(buf, NODE_ID, 0x01, 0x01, d, 4);
    RF_Send(buf, n);
}
static void handle_rf(void)           /* 与 TempNode 相同：0x02 对时、0x03 报警页切换 */
{
    u8 src, dst, cmd, out[FRAME_MAX_LEN], n;
    if(!rf_rxLen) return;
    n = frame_parse((const u8 *)rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
    rf_rxLen = 0;
    if(!n || (dst != NODE_ID && dst != 0xFF)) return;
    if(cmd == 0x02 && n == 6)                 /* 对时广播 */
    {
        rtc_set(out);
        if(!page_alarm) draw_time_row();
    }
    else if(cmd == 0x03 && n == 2)            /* 报警状态广播 */
    {
        if((out[0] & 0x01) && !page_alarm) { page_alarm = 1; draw_alarm_page(); }
        else if(!(out[0] & 0x01) && page_alarm) { page_alarm = 0; draw_main_page(); }
    }
}
void main(void)
{
    u32 last_1s = 0, last_2s = 0;
    u8  last_min = 0xFF, warmup = 60;         /* 上电 60s 预热期（秒） */
    CLK_Init();
    T1_Init();
    RF_Init();
    P1SEL &= ~0x01; P1DIR |= 0x01; LED_ALARM = 1;
    P0SEL &= ~0x20; P0DIR &= ~0x20;           /* P0.5 输入（MQ-2 DO） */
    LCD_Init(); LCD_CLS();
    draw_warmup(60);                          /* 预热倒计时从 60s 开始 */
    draw_time_row();
    while(1)
    {
        u32 now = ms_get();               /* 每圈取一次原子时间，圈内共用 */
        if(now - last_1s >= 1000)
        {
            last_1s = (now - last_1s > 5000) ? now : last_1s + 1000;   /* 卡顿过久直接对齐防连跳 */
            rtc_sec_tick();
            if(page_alarm) LCD_Invert(g_rtc.sec & 1);   /* 报警页 1Hz 反显闪烁 */
            else if(warmup)
            {
                warmup--;
                if(warmup) draw_warmup(warmup);           /* 每秒 -1 倒计时 */
                else draw_main_page();                    /* 预热结束进主页面 */
            }
            else if(g_rtc.min != last_min) { last_min = g_rtc.min; draw_time_row(); }
        }
        if(now - last_2s >= 2000)
        {
            last_2s += 2000;
            gas_avg = ADC_Avg6(ADC_Read6());
            if(!warmup)
            {
                send_report();              /* 数据包即心跳 */
                if(!page_alarm) draw_data_rows();   /* ADC 值每 2s 刷新 */
            }
        }
        handle_rf();
        LED_ALARM = (page_alarm && ((now / 500) & 1)) ? 0 : 1;   /* 500ms 翻转 */
    }
}
