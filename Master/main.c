#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\uart.h"
#include "..\Common\rf.h"
#include "..\Common\frame.h"
#define NODE_ID 0x01
void main(void)
{
    u8 src, dst, cmd, out[FRAME_MAX_LEN], n;
    CLK_Init();
    UART_Init();
    RF_Init();
    UART_SendStr("RX-READY\n");
    while(1)
    {
        if(rf_rxLen)
        {
            n = frame_parse((const u8 *)rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
            rf_rxLen = 0;
            if(n && dst == NODE_ID)
                UART_SendStr("RF-RX OK, src=\n");   /* 收到即打印，现象验证用 */
        }
    }
}
