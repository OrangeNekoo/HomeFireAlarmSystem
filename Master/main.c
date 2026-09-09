/* Master/main.c — 任务 2 验证：LED 每秒翻转 */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#define NODE_ID 0x01
#define LED_ALARM P0_5          /* 报警 LED，低电平点亮 */
void main(void)
{
    u32 last = 0;
    CLK_Init();
    P0SEL &= ~0x20;             /* P0.5 普通 IO */
    P0DIR |= 0x20;              /* P0.5 输出 */
    LED_ALARM = 1;              /* 熄灭 */
    T1_Init();
    while(1)
    {
        if(g_ms - last >= 1000)
        {
            last += 1000;
            LED_ALARM = !LED_ALARM;   /* 1Hz 翻转即通过（裁决：sbit 上用 ! 而非 ~） */
        }
    }
}
