/* GasNode/adc.h */
#ifndef ADC_H
#define ADC_H
#include "timer.h"
u16 ADC_Read6(void);        /* AIN6(P0.6) 单次 12 位采样 */
u16 ADC_Avg6(u16 v);        /* 8 点滑动平均（对应规格"滤波算法"要求） */
#endif
