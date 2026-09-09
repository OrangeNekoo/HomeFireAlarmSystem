/* Common/timer.c */
#include <ioCC2530.h>
#include "timer.h"
volatile u32 g_ms = 0;
void T1_Init(void)
{
    T1CC0L = 249;                 /* 32MHz/128 = 250kHz，250 计数 = 1ms */
    T1CC0H = 0x00;
    T1CCTL0 |= 0x04;              /* 通道 0 比较中断使能 */
    T1CTL = 0x0E;                 /* 128 分频、模模式、启动 */
    IEN1 |= 0x02;                 /* T1 中断使能 */
    EA = 1;
}
#pragma vector = T1_VECTOR
__interrupt void T1_ISR(void)
{
    T1STAT &= ~0x01;              /* 清通道 0 比较标志 */
    g_ms++;
}
