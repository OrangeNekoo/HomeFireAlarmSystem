/* Common/rf.c — 裸机 FIFO 透明收发，无硬件 CRC/帧过滤 */
#include <ioCC2530.h>
#include "rf.h"
/* RFST 命令选通 */
#define ISRXON     0xE3
#define ISTXON     0xE9
#define ISFLUSHRX  0xED
#define ISFLUSHTX  0xEE

volatile u8 rf_rxBuf[RF_RX_MAX];
volatile u8 rf_rxLen = 0;

void RF_Init(void)
{
    TXPOWER  = 0xD5;              /* 发射功率 */
    FREQCTRL = 0x0B;              /* 2405MHz（信道 11） */
    FRMCTRL0 = 0x00;              /* AUTOCRC=0：FIFO 纯透明 */
    FRMFILT0 = 0x00;              /* 关硬件帧过滤，接收所有帧 */
    SHORT_ADDR0 = 0x01;           /* 本机短地址（仅占位，软件按帧内 ID 过滤） */
    SHORT_ADDR1 = 0x00;
    PAN_ID0 = 0x1A; PAN_ID1 = 0xAA;
    RFST = ISFLUSHRX;
    RFST = ISFLUSHTX;
    RFST = ISRXON;                /* 进入接收态 */
    RFIRQM0 |= 0x40;              /* RXPKTDONE 中断使能 */
    IEN2 |= 0x01;                 /* RF 中断使能 */
    EA = 1;
}
u8 RF_Send(const u8 *data, u8 len)
{
    u8 i;
    u16 t = 0;
    RFST = ISFLUSHTX;
    RFD = len;                    /* 帧长度字节（含其后有效数据数） */
    for(i = 0; i < len; i++) RFD = data[i];
    RFST = ISTXON;
    while(!(RFIRQF1 & 0x02))      /* 等待 TXDONE */
        if(++t == 0) return 0;    /* 超时保护，防止卡死 */
    RFIRQF1 &= ~0x02;
    return 1;
}
#pragma vector = RF_VECTOR
__interrupt void RF_ISR(void)
{
    u8 len, i;
    S1CON = 0;                    /* 清 CPU 端 RF 中断标志 */
    if(RFIRQF0 & 0x40)            /* RXPKTDONE */
    {
        RFIRQF0 &= ~0x40;
        len = RFD;
        if(len > RF_RX_MAX - 4) { RFST = ISFLUSHRX; RFST = ISRXON; return; }
        for(i = 0; i < len; i++) rf_rxBuf[i] = RFD;
        rf_rxLen = len;           /* 通知主循环（2s 周期低负载，单缓冲够用） */
        RFST = ISFLUSHRX;         /* 立即恢复接收 */
        RFST = ISRXON;
    }
}
