#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\uart.h"
#include "..\Common\frame.h"
#define NODE_ID 0x01
void main(void)
{
    u8 txbuf[FRAME_MAX_LEN];
    CLK_Init();
    UART_Init();
    if(frame_selftest(txbuf))  UART_SendStr("FRAME-TEST PASS\n");
    else                       UART_SendStr("FRAME-TEST FAIL\n");
    UART_SendStr("ECHO-OK\n");
    while(1) { }
}
