/* Master/main.c — 主节点（ID=0x01）：界面/判决/CSV 上报/下行指令 */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#include "..\Common\rtc.h"
#include "..\Common\frame.h"
#include "..\Common\rf.h"
#include "..\Common\easter_frames.h"
#include "..\Common\uart.h"
#include "csv.h"
#define NODE_ID 0x01
#define EASTER_BUTTON P0_1
#define EASTER_BUTTON_SAMPLE_MS 10
#define EASTER_BUTTON_DEBOUNCE_MS 30
#define EASTER_FRAME_MS 100
#define LED_ALARM P0_5                   /* 低电平点亮 */

typedef struct {
    u8  online;
    u32 last_ms;
    u8  last_seq;
    u16 loss, total;
    u8  temp_i, temp_d, hum_i, hum_d;    /* 节点 2 用 */
    u16 gas;  u8  gas_do;                /* 节点 3 用 */
} node_info_t;

node_info_t n2, n3;
u16 th_temp = 45, th_gas = 600;
u8  alarm_on = 0, alarm_src = 0, test_on = 0;
static u8 easter_on = 0;
static u8 easter_frame = 0;
static u32 easter_next_ms = 0;
static u8 easter_button_state = 1;
static u8 easter_button_sample = 1;
static u8 easter_button_stable_ms = 0;

static void draw_time_row(void)
{
    char b[17];
    rtc_fmt(b);
    LCD_P8x16Str(0, 0, (u8 *)b);
}

static void draw_values(void)      /* 局部刷新三行数值，不清屏避免闪烁 */
{
    char b[17];
    /* 温度行：温度:xx.x℃ */
    LCD_P16x16Ch(0, 2, 0); LCD_P16x16Ch(16, 2, 2);
    b[0]=':'; b[1]='0'+n2.temp_i/10; b[2]='0'+n2.temp_i%10;
    b[3]='.'; b[4]='0'+n2.temp_d; b[5]='\0';
    LCD_P8x16Str(32, 2, (u8 *)b); LCD_P16x16Ch(72, 2, 16);
    /* 湿度行：湿度:xx.x% */
    LCD_P16x16Ch(0, 4, 1); LCD_P16x16Ch(16, 4, 2);
    b[0]=':'; b[1]='0'+n2.hum_i/10; b[2]='0'+n2.hum_i%10;
    b[3]='.'; b[4]='0'+n2.hum_d; b[5]='%'; b[6]='\0';
    LCD_P8x16Str(32, 4, (u8 *)b);
    /* 有害气体行：正常/异常/离线（gas_do=1 为超阈异常，与 GasNode d[3] 语义一致） */
    LCD_P16x16Ch(0, 6, 3); LCD_P16x16Ch(16, 6, 4);
    LCD_P16x16Ch(32, 6, 5); LCD_P16x16Ch(48, 6, 6);
    LCD_P8x16Str(64, 6, (u8 *)":");
    if(!n3.online)      { LCD_P16x16Ch(72, 6, 14); LCD_P16x16Ch(88, 6, 15); }  /* 离线 */
    else if(n3.gas_do)  { LCD_P16x16Ch(72, 6, 8);  LCD_P16x16Ch(88, 6, 9);  }  /* 异常 */
    else                { LCD_P16x16Ch(72, 6, 7);  LCD_P16x16Ch(88, 6, 9);  }  /* 正常 */
}
static void draw_main_page(void)  /* 整页重画：仅初始化/页面切换时调用 */
{
    LCD_CLS(); LCD_Invert(0);
    draw_time_row();
    draw_values();
}
static void draw_alarm_page(void)
{
    LCD_CLS();
    LCD_P16x16Ch(32, 3, 10); LCD_P16x16Ch(48, 3, 11);
    LCD_P16x16Ch(64, 3, 12); LCD_P16x16Ch(80, 3, 13);   /* 火灾警报 居中 */
    LCD_Invert(1);
}
static void easter_broadcast(u8 on)
{
    u8 state = on, buf[FRAME_MAX_LEN], n;
    n = frame_pack(buf, NODE_ID, 0xFF, 0x04, &state, 1);
    if(n) RF_Send(buf, n);
    csv_send_easter(on);
}
static void easter_set(u8 on)
{
    easter_on = on;
    if(on)
    {
        easter_frame = 0;
        LCD_Invert(0);
        LCD_DrawBitmap64(easter_frames[easter_frame]);
        easter_next_ms = ms_get() + EASTER_FRAME_MS;
    }
    else if(alarm_on) draw_alarm_page();
    else draw_main_page();
    easter_broadcast(on);
}
static void easter_tick(u32 now)
{
    if(!easter_on || (long)(now - easter_next_ms) < 0) return;
    easter_frame++;
    if(easter_frame >= EASTER_FRAME_COUNT) easter_frame = 0;
    LCD_DrawBitmap64(easter_frames[easter_frame]);
    easter_next_ms += EASTER_FRAME_MS;
}
static void easter_button_init(void)
{
    P0SEL &= ~0x02;
    P0DIR &= ~0x02;
    P0INP &= ~0x02;
    P2INP &= ~0x20;                /* P0 输入启用内部上拉 */
    easter_button_state = EASTER_BUTTON ? 1 : 0;
    easter_button_sample = easter_button_state;
}
static void easter_button_poll(void)
{
    u8 sample = EASTER_BUTTON ? 1 : 0;
    if(sample == easter_button_sample)
    {
        if(easter_button_stable_ms < EASTER_BUTTON_DEBOUNCE_MS)
            easter_button_stable_ms += EASTER_BUTTON_SAMPLE_MS;
        if(easter_button_stable_ms >= EASTER_BUTTON_DEBOUNCE_MS &&
           easter_button_state != sample)
        {
            if(easter_button_state == 1 && sample == 0) easter_set(!easter_on);
            easter_button_state = sample;
        }
    }
    else
    {
        easter_button_sample = sample;
        easter_button_stable_ms = EASTER_BUTTON_SAMPLE_MS;
    }
}
static void broadcast_time(void)          /* 广播对时：cmd 0x02、dst 0xFF、域 [年-2000,月,日,时,分,秒] */
{
    u8 d[6], buf[FRAME_MAX_LEN], n;
    d[0] = g_rtc.year; d[1] = g_rtc.mon; d[2] = g_rtc.day;
    d[3] = g_rtc.hour; d[4] = g_rtc.min; d[5] = g_rtc.sec;
    n = frame_pack(buf, NODE_ID, 0xFF, 0x02, d, 6);
    RF_Send(buf, n);
}
static void set_alarm(u8 on, u8 src)      /* 页面切换 + RF 广播 + 串口上报 三联动 */
{
    u8 d[2], buf[FRAME_MAX_LEN], n;
    alarm_on = on; alarm_src = src;
    if(!on) test_on = 0;
    if(!easter_on)
    {
        if(on) draw_alarm_page(); else draw_main_page();
    }
    d[0] = on; d[1] = src;
    n = frame_pack(buf, NODE_ID, 0xFF, 0x03, d, 2);
    RF_Send(buf, n);
    csv_send_alarm(on, src);
}
static void judge_alarm(void)             /* 500ms 调一次；回差 5% 防抖 */
{
    if(alarm_on)
    {
        u8 still = 0;
        if(alarm_src == 1 && n2.online && n2.temp_i > th_temp - th_temp / 20) still = 1;
        else if(alarm_src == 2 && n3.online && n3.gas > th_gas - th_gas / 20) still = 1;
        else if(alarm_src == 3 && test_on) still = 1;
        if(!still) set_alarm(0, 0);
    }
    else
    {
        if(n2.online && n2.temp_i > th_temp)      set_alarm(1, 1);
        else if(n3.online && n3.gas > th_gas)     set_alarm(1, 2);
        else if(test_on)                          set_alarm(1, 3);
    }
}
static void handle_rf(void)               /* 序号连续性统计丢包 */
{
    u8 src, dst, cmd, out[FRAME_MAX_LEN], n, diff;
    if(!rf_rxLen) return;
    n = frame_parse((const u8 *)rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
    rf_rxLen = 0;
    if(!n || dst != NODE_ID) return;
    if(cmd == 0x01 && src == 0x02 && n == 5)
    {
        diff = (u8)(out[0] - n2.last_seq);
        if(n2.online && diff > 1) n2.loss += diff - 1;
        n2.total++;
        n2.last_seq = out[0];
        n2.temp_i = out[1]; n2.temp_d = out[2]; n2.hum_i = out[3]; n2.hum_d = out[4];
        if(!n2.online) { n2.online = 1; csv_send_status(2, 1); csv_send_loss(2, n2.loss, n2.total); }
        n2.last_ms = ms_get();
        csv_send_data_th(n2.temp_i, n2.temp_d, n2.hum_i, n2.hum_d);
        if(!alarm_on && !easter_on) draw_values();          /* 局部刷新数值行，不清屏不闪 */
    }
    else if(cmd == 0x01 && src == 0x03 && n == 4)
    {
        diff = (u8)(out[0] - n3.last_seq);
        if(n3.online && diff > 1) n3.loss += diff - 1;
        n3.total++;
        n3.last_seq = out[0];
        n3.gas = ((u16)out[1] << 8) | out[2]; n3.gas_do = out[3];
        if(!n3.online) { n3.online = 1; csv_send_status(3, 1); csv_send_loss(3, n3.loss, n3.total); }
        n3.last_ms = ms_get();
        csv_send_data_gas(n3.gas, n3.gas_do);
        if(!alarm_on && !easter_on) draw_values();
    }
}
static void check_offline(void)              /* 1s 调一次；10s 无心跳判离线 */
{
    u32 now = ms_get();
    if(n2.online && now - n2.last_ms > 10000)
    { n2.online = 0; csv_send_status(2, 0); csv_send_loss(2, n2.loss, n2.total); if(!alarm_on) draw_values(); }
    if(n3.online && now - n3.last_ms > 10000)
    { n3.online = 0; csv_send_status(3, 0); csv_send_loss(3, n3.loss, n3.total); if(!alarm_on) draw_values(); }
}
void main(void)
{
    u32 last_500 = 0, last_1s = 0, last_10s = 0, last_button = 0;
    u8  last_min = 0xFF;
    CLK_Init();
    T1_Init();
    RF_Init();
    UART_Init();
    P0SEL &= ~0x20; P0DIR |= 0x20; LED_ALARM = 1;
    easter_button_init();
    LCD_Init(); LCD_CLS();
    draw_main_page();
    csv_send_thresh(th_temp, th_gas);        /* 上线告知上位机当前阈值 */
    while(1)
    {
        u32 now = ms_get();               /* 每圈取一次原子时间，圈内共用 */
        if(now - last_button >= EASTER_BUTTON_SAMPLE_MS)
        {
            last_button += EASTER_BUTTON_SAMPLE_MS;
            easter_button_poll();
        }
        easter_tick(now);
        if(uart_line_ready)
        {
            u8 r = csv_handle_line();
            if(r == 2) judge_alarm();         /* TEST 置位/复位后立即判决 */
            else if(r == 3) { broadcast_time(); if(!alarm_on && !easter_on) draw_time_row(); }
        }
        handle_rf();
        if(now - last_500 >= 500) { last_500 += 500; judge_alarm(); }
        if(now - last_1s >= 1000)
        {
            /* 卡顿过久（>5s）直接对齐，只防秒数连跳，不追补历史 tick */
            last_1s = (now - last_1s > 5000) ? now : last_1s + 1000;
            rtc_sec_tick();
            check_offline();
            if(alarm_on && !easter_on) LCD_Invert(g_rtc.sec & 1);      /* 报警 1Hz 闪烁 */
            else if(!easter_on && g_rtc.min != last_min) { last_min = g_rtc.min; draw_time_row(); }
        }
        if(now - last_10s >= 10000)
        {
            last_10s += 10000;
            broadcast_time();                 /* 10s 周期对时，新节点入网即同步 */
            csv_send_status(1, 1);            /* 主节点串口心跳：网页忽略 node=1，供 bridge 日志诊断串口上行 */
        }
        LED_ALARM = (alarm_on && ((now / 500) & 1)) ? 0 : 1;   /* 500ms 翻转 */
    }
}
