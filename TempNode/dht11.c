/* TempNode/dht11.c — 数据脚 P0.7，读取全程 ~5ms，调用方需 EA=0 保护 */
#include <ioCC2530.h>
#include "dht11.h"
#include "delay.h"
#define DHT P0_7
static u8 read_byte(u8 *dat)   /* 返回 0=超时失败（读取中途拔线时防死循环） */
{
    u8 i, d = 0;
    u16 t;
    for(i = 0; i < 8; i++)
    {
        t = 3000;
        while(DHT == 0)  if(--t == 0) return 0;   /* 等待本位 50us 低电平结束 */
        Delay_us(40);         /* 40us 后采样：高持续 26-28us=0，70us=1 */
        d <<= 1;
        if(DHT == 1)
        {
            d |= 0x01;
            t = 3000;
            while(DHT == 1)  if(--t == 0) return 0;   /* 等待高电平结束 */
        }
    }
    *dat = d;
    return 1;
}
u8 DHT11_Read(u8 *temp_i, u8 *temp_d, u8 *hum_i, u8 *hum_d)
{
    u8 buf[5], i;
    u16 t;
    P0DIR |= 0x80;            /* 输出 */
    DHT = 0;
    Delay_ms(20);             /* 主机拉低 ≥18ms */
    DHT = 1;
    Delay_us(30);             /* 释放总线 20-40us */
    P0DIR &= ~0x80;           /* 切输入 */
    t = 3000;
    while(DHT == 0)  if(--t == 0) return 0;   /* DHT 响应 80us 低 */
    t = 3000;
    while(DHT == 1)  if(--t == 0) return 0;   /* DHT 响应 80us 高 */
    for(i = 0; i < 5; i++)
        if(!read_byte(&buf[i])) return 0;
    if((u8)(buf[0] + buf[1] + buf[2] + buf[3]) != buf[4]) return 0;
    *hum_i = buf[0]; *hum_d = buf[1]; *temp_i = buf[2]; *temp_d = buf[3];
    return 1;
}
