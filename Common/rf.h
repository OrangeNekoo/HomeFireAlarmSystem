/* Common/rf.h */
#ifndef RF_H
#define RF_H
#include "timer.h"
#define RF_RX_MAX 36
extern volatile u8 rf_rxBuf[RF_RX_MAX];   /* 最近一帧原始字节 */
extern volatile u8 rf_rxLen;              /* >0 表示有待处理帧，处理后清 0 */
void RF_Init(void);
u8   RF_Send(const u8 *data, u8 len);     /* 发一帧原始数据，1=成功 */
#endif
