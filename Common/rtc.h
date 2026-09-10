/* Common/rtc.h */
#ifndef RTC_H
#define RTC_H
#include "timer.h"
typedef struct { u8 year, mon, day, hour, min, sec; } rtc_t;   /* year = 公历年-2000 */
extern rtc_t g_rtc;
void rtc_set(const u8 *ymdhms);   /* 用 6 字节数组（年-2000,月,日,时,分,秒）设置 */
void rtc_sec_tick(void);          /* 每秒调用一次，走时进位 */
void rtc_fmt(char *buf);          /* 格式化为 "2026-09-10 12:00"（17 字节含 \0） */
#endif
