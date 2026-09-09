/* Common/delay.h */
#ifndef DELAY_H
#define DELAY_H
#include "timer.h"
void Delay_ms(u16 ms);            /* 忙等毫秒（不依赖中断，可在 EA=0 区使用） */
void Delay_us(u16 us);            /* 忙等微秒（32MHz 下近似值，DHT11 时序用） */
#endif
