/* Common/clk.c */
#include <ioCC2530.h>
void CLK_Init(void)
{
    SLEEPCMD &= ~0x04;            /* 上电 32MHz XOSC */
    while(!(SLEEPSTA & 0x40));    /* 等待 XOSC 稳定 */
    CLKCONCMD &= ~0x47;           /* OSC=32M XOSC、CLKSPD=32M、TICKSPD=32M */
    /* 必须等 CLKCONSTA 镜像的 OSC/CLKSPD/TICKSPD 三者全部生效：只等 OSC 位时
       TICKSPD/CLKSPD 可能仍被硬件钳在 16M（源切换期间 32M 不可用）——实测后果
       是 T1 实际 2ms 一跳（走时慢一半）、串口实际 57600（上行乱码）、RF 数据率减半 */
    while(CLKCONSTA & 0x47);
    SLEEPCMD |= 0x04;             /* 关闭未使用的 16MHz RC 振荡器 */
}
