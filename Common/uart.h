/* Common/uart.h */
#ifndef UART_H
#define UART_H
#include "timer.h"
#define UART_RX_BUF 64
extern volatile u8  uart_line[UART_RX_BUF];  /* 完整一行（不含 \r\n，\0 结尾） */
extern volatile u8  uart_line_ready;         /* 1=有未处理行 */
void UART_Init(void);
void UART_SendStr(const char *s);
void UART_SendBytes(const u8 *s, u8 len);
void uart_line_consume(void);                /* 主循环处理完一行后调用 */
#endif
