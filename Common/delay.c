/* Common/delay.c */
#include <ioCC2530.h>
#include <intrinsics.h>       /* __no_operation 内建函数声明（消除 Pe223 隐式声明警告） */
#include "delay.h"
void Delay_ms(u16 ms)
{
    u16 i;
    while(ms--)
        for(i = 0; i < 1070; i++);   /* 32MHz 下实测约 1ms，任务 6 校准 DHT11 时验证 */
}
void Delay_us(u16 us)
{
    while(us--)
    {
        __no_operation(); __no_operation(); __no_operation(); __no_operation();
        __no_operation(); __no_operation(); __no_operation(); __no_operation();
    }
}
