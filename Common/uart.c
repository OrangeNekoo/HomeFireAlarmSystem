/* Common/uart.c — 行缓冲：一帧一行（波特率 115200，行最长约 40 字符） */
#include <ioCC2530.h>
#include "uart.h"
volatile u8 uart_line[UART_RX_BUF];
volatile u8 uart_line_ready = 0;
static u8 line_len = 0;

void UART_Init(void)
{
    PERCFG &= ~0x01;              /* USART0 位置 1：P0.2 RX、P0.3 TX */
    P0SEL |= 0x0C;                /* P0.2/P0.3 外设功能 */
    U0GCR = 12; U0BAUD = 216;     /* 115200 @ 32MHz */
    U0CSR |= 0xC0;                /* UART 模式 + 接收使能 */
    UTX0IF = 0;
    URX0IE = 1;                   /* 接收中断使能 */
    EA = 1;
}
void UART_SendBytes(const u8 *s, u8 len)
{
    while(len--) { U0DBUF = *s++; while(!UTX0IF); UTX0IF = 0; }
}
void UART_SendStr(const char *s)
{
    while(*s) { U0DBUF = *s++; while(!UTX0IF); UTX0IF = 0; }
}
void uart_line_consume(void)      /* 主循环取走行后复位缓冲 */
{
    uart_line_ready = 0;
    line_len = 0;
}
#pragma vector = URX0_VECTOR
__interrupt void URX0_ISR(void)
{
    u8 ch = U0DBUF;
    if(ch == '\n' || ch == '\r')
    {
        if(line_len > 0)
        {
            uart_line[line_len] = '\0';
            uart_line_ready = 1;      /* 行就绪，等主循环取走 */
        }
    }
    else if(!uart_line_ready && line_len < UART_RX_BUF - 1)
    {
        uart_line[line_len++] = ch;   /* 上一行未被取走期间丢弃新字符（上行频率 0.5Hz，不会发生） */
    }
}
