/* GasNode/adc.c */
#include <ioCC2530.h>
#include "adc.h"
u16 ADC_Read6(void)
{
    u16 v;
    ADCCFG |= 0x40;               /* P0.6 ADC 输入使能 */
    ADCCON3 = 0xB6;               /* 参考 AVDD5(3.3V)、64 分频 12 位、通道 AIN6 */
    while(!(ADCCON1 & 0x80));     /* 等待 EOC */
    v = ADCL >> 4;                /* 先读 ADCL（低 8 位取高 4 位） */
    v |= ((u16)ADCH) << 4;        /* 再读 ADCH，拼装 12 位结果 0~4095 */
    return v;
}
u16 ADC_Avg6(u16 v)
{
    static u16 buf[8];
    static u8 idx = 0, full = 0;
    u32 sum = 0;
    u8 i, n;
    buf[idx] = v;
    idx = (idx + 1) & 7;
    if(!full && idx == 0) full = 1;
    n = full ? 8 : idx;
    for(i = 0; i < n; i++) sum += buf[i];
    return (u16)(sum / n);
}
