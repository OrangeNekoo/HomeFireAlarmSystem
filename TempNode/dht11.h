/* TempNode/dht11.h */
#ifndef DHT11_H
#define DHT11_H
#include "timer.h"
u8 DHT11_Read(u8 *temp_i, u8 *temp_d, u8 *hum_i, u8 *hum_d);  /* 1=成功 */
#endif
