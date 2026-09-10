/* Common/timer.h */
#ifndef TIMER_H
#define TIMER_H
#include <ioCC2530.h>
typedef unsigned char  u8;
typedef unsigned int   u16;
typedef unsigned long  u32;
extern volatile u32 g_ms;      /* 上电以来毫秒数（约 49.7 天回绕，课设无碍） */
u32 ms_get(void);              /* 关中断原子读取 g_ms，主循环计时一律用它 */
void T1_Init(void);
#endif
