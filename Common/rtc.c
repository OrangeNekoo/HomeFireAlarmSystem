/* Common/rtc.c */
#include "rtc.h"
rtc_t g_rtc = {26, 9, 10, 12, 0, 0};   /* 上电默认 2026-09-10 12:00，等待对时覆盖 */
static const u8 day_tab[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
void rtc_set(const u8 *t)
{
    g_rtc.year = t[0];
    g_rtc.mon  = (t[1] < 1) ? 1 : (t[1] > 12) ? 12 : t[1];    /* 钳位防畸形对时帧 */
    g_rtc.day  = (t[2] < 1) ? 1 : (t[2] > 31) ? 31 : t[2];
    g_rtc.hour = (t[3] > 23) ? 23 : t[3];
    g_rtc.min  = (t[4] > 59) ? 59 : t[4];
    g_rtc.sec  = (t[5] > 59) ? 59 : t[5];
}
void rtc_sec_tick(void)
{
    u8 max;
    if(++g_rtc.sec < 60) return;
    g_rtc.sec = 0;
    if(++g_rtc.min < 60) return;
    g_rtc.min = 0;
    if(++g_rtc.hour < 24) return;
    g_rtc.hour = 0;
    max = day_tab[g_rtc.mon - 1];
    if(g_rtc.mon == 2 && (g_rtc.year % 4) == 0) max = 29;   /* 20xx 闰年简化规则 */
    if(++g_rtc.day <= max) return;
    g_rtc.day = 1;
    if(++g_rtc.mon <= 12) return;
    g_rtc.mon = 1;
    g_rtc.year++;
}
void rtc_fmt(char *b)
{
    b[0] = '2';  b[1] = '0';
    b[2] = '0' + g_rtc.year / 10;  b[3] = '0' + g_rtc.year % 10;  b[4] = '-';
    b[5] = '0' + g_rtc.mon / 10;   b[6] = '0' + g_rtc.mon % 10;   b[7] = '-';
    b[8] = '0' + g_rtc.day / 10;   b[9] = '0' + g_rtc.day % 10;   b[10] = ' ';
    b[11] = '0' + g_rtc.hour / 10; b[12] = '0' + g_rtc.hour % 10; b[13] = ':';
    b[14] = '0' + g_rtc.min / 10;  b[15] = '0' + g_rtc.min % 10;  b[16] = '\0';
}
