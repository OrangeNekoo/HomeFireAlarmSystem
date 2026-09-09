/* Common/clk.c */
#include <ioCC2530.h>
void CLK_Init(void)
{
    SLEEPCMD &= ~0x04;            /* 上电 32MHz 晶振 */
    while(!(SLEEPSTA & 0x40));    /* 等待 XOSC 稳定 */
    CLKCONCMD &= ~0x47;           /* 系统时钟 32MHz、定时器 tick 32MHz */
    while(CLKCONSTA & 0x40);      /* 等待时钟源切换生效 */
    SLEEPCMD |= 0x04;             /* 关闭未使用的 16MHz RC 振荡器 */
}
