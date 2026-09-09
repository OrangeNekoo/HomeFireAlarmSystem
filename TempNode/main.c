#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\rf.h"
#include "..\Common\frame.h"
#define NODE_ID 0x02
void main(void)
{
    u8 d[5] = {1, 25, 0, 61, 0};   /* seq=1, 温25.0, 湿61.0 固定值 */
    u8 buf[FRAME_MAX_LEN];
    CLK_Init();
    T1_Init();
    RF_Init();
    while(1)
    {
        static u32 last = 0;
        if(g_ms - last >= 2000)
        {
            last += 2000;
            d[0]++;
            frame_pack(buf, NODE_ID, 0x01, 0x01, d, 5);
            RF_Send(buf, buf[5] + 7);   /* 长度 = 数据域 + 7 头尾字节 */
        }
    }
}
