# 家庭火灾报警系统 实现计划

> **面向 AI 代理的工作者：** 必需子技能：使用 subagent-driven-development（推荐）或 executing-plans 逐任务实现此计划。步骤使用复选框（`- [ ]`）语法来跟踪进度。

**目标：** CC2530 三节点（主节点/温湿度节点/气体节点）裸机 RF 组网的火灾报警系统，配 Python 桥与原神风格网页上位机。

**架构：** 三个独立 IAR 工程共享 Common 模块（OLED/字库/RF/帧/串口/时基），自定义帧协议无线组网，主节点集中判决报警并经 CSV 串口上报；`bridge.py`（便携 Python311）做串口↔WebSocket 桥；网页（Three.js 元素粒子特效）展示数据、设阈值、触发模拟报警。

**技术栈：** C（IAR 8.10 8051，CC2530 裸机寄存器）、Python 3.11（pyserial + websockets，项目内 `Python311\python.exe`）、HTML/CSS/JS + Three.js（本地文件，不用 CDN）。

**规格：** `docs/superpowers/specs/2026-09-08-home-fire-alarm-design.md`（执行者必须与本计划一起阅读；协议数值、界面布局、阈值默认值以规格为准）

## 全局约束

- 平台：CC2530（8051 内核），系统时钟初始化为 32MHz 晶振；ZB2530 开发板 ×3，OLED（SSD1306 0.96 寸 SPI）×3
- 引脚（逐字照抄规格）：OLED 为 **I2C 模块**（SSD1306，从地址 0x3C/写 0x78），SCL=P1.2、SDA=P1.3（软件模拟 I2C）；主节点 LED=P0.5 输出低电平点亮；DHT11 DATA=P0.7；MQ-2 AO=P0.6(AIN6)、DO=P0.5 输入；终端报警 LED=P1.0；串口 P0.2(RX)/P0.3(TX) 115200 8N1
- 节点 ID：0x01 主节点、0x02 温湿度节点、0x03 气体节点、0xFF 广播；RF 信道 11（2405MHz，FREQCTRL=0x0B），250kbps
- RF 帧格式：`0xAA 0xBB | 源ID | 目标ID | 命令字 | 长度n | 数据域n | 异或校验`（校验=从源ID到数据域末尾逐字节异或）。裸机 FIFO 透明收发，**不用**硬件 AUTOCRC/帧过滤
- 命令字：0x01 数据上报（温湿度域 `[seq,temp_i,temp_d,hum_i,hum_d]` 5B；气体域 `[seq,adc_hi,adc_lo,do]` 4B）、0x02 对时广播（域 `[年-2000,月,日,时,分,秒]` 6B）、0x03 报警状态广播（域 `[state,src]` 2B，state bit0=报警中，src：0无/1温度/2气体/3模拟）
- 串口 CSV 协议：行以 `\r\n` 结尾，行尾 `*` + 校验和两位大写 HEX（行内 `*` 前所有字符的异或）。上行：`D,节点,字段…,*CS` / `S,节点,ONLINE|OFFLINE` / `A,报警中0|1,报警源` / `L,节点,丢包数,应收数` / `T,温度阈值,气体阈值`。下行：`SET,温度阈值,气体阈值,*CS` / `TEST,0|1` / `TIME,年-2000,月,日,时,分,秒,*CS`
- 报警阈值默认：温度 45℃、气体 ADC 600；触发/解除回差 5%；报警时 LED 500ms 翻转
- 离线判定：10 秒未收到终端数据即离线；终端每 2 秒上报（数据包即心跳）；主节点每 60 秒广播对时（串口收到 TIME 后立即再广播一次）
- OLED 汉字 16×16 字模索引（来自 `font matrix.txt`，17 字）：0温 1湿 2度 3有 4害 5气 6体 7正 8异 9常 10火 11灾 12警 13报 14离 15线 16℃
- 语言：代码注释、commit 信息一律简体中文；commit 遵循 conventional commits（feat/fix/docs/chore）
- 测试策略（嵌入式裁剪说明）：CC2530 无法在 PC 跑单元测试，嵌入式任务的"测试"= IAR 编译零错误 + 烧录后的**明确现象判定**（每个任务写明）；纯逻辑模块（frame、CSV 校验）用串口打印自测函数验证；Python 用 unittest；网页用演示模式 + 浏览器手动验证
- 项目直接在 main 分支开发（单人课程设计，IAR 工程对路径敏感，不建 worktree）
- 每个任务结束必须 commit

## 文件结构

```
HomeFireAlarmSystem/
├── HomeFireAlarmSystem.eww        [改] workspace 引用三个工程
├── Master/                        主节点工程
│   ├── Master.ewp/.ewd            [移自根目录并改名]
│   ├── main.c                     [改] 主节点应用（RTC/界面/判决/CSV/指令）
│   └── settings/ Debug/           [移] IAR 工程附属
├── TempNode/                      温湿度节点工程
│   ├── TempNode.ewp/.ewd          [新] 复制 Master.ewp 改路径
│   └── main.c                     [新] DHT11 采集/上报/联动
├── GasNode/                       气体节点工程
│   ├── GasNode.ewp/.ewd           [新] 复制 Master.ewp 改路径
│   └── main.c                     [新] ADC 采集/上报/联动
├── Common/                        共享模块（三工程引用）
│   ├── clk.c/h       [新] 32MHz 时钟初始化
│   ├── timer.c/h     [新] T1 1ms 时基 g_ms
│   ├── delay.c/h     [新] 忙等 ms/us 延时（关中断区可用）
│   ├── oled.c/h      [新] SSD1306 I2C 驱动（显示层签名沿用示例代码）
│   ├── font16.c/h    [新] 17 汉字字模 + F6x8/F8X16 ASCII 字库
│   ├── frame.c/h     [新] RF 帧打包/解析/异或校验
│   ├── rf.c/h        [新] 裸机 RF 驱动（收发+中断单缓冲）
│   └── uart.c/h      [新] USART0 串口驱动（中断收环形缓冲）
├── bridge.py                      [新] 串口↔WebSocket 桥
├── test_bridge.py                 [新] 桥纯逻辑单元测试（unittest）
├── web/                           [新] 上位机
│   ├── index.html  style.css  main.js  three.min.js
├── font matrix.txt                字模源（已存在，只读）
├── docs/                          任务书/模块资料/规格/本计划
└── Python311/                     便携 Python（已存在）
```

职责边界：Common 各模块只管自己的硬件/协议；节点 main.c 只做应用逻辑（采集、界面、判决、调度）；bridge.py 不解析业务含义以外的内容（字段原样转 JSON）。

---

### 任务 1：工程结构重组（三工程 workspace）

**文件：**
- 移动：`HomeFireAlarmSystem.ewp→Master/Master.ewp`、`.ewd`、`.dep`、`main.c`、`settings/`
- 创建：`TempNode/TempNode.ewp`、`GasNode/GasNode.ewp`、`TempNode/main.c`、`GasNode/main.c`、`Common/`（空目录，后续任务填充）
- 修改：`HomeFireAlarmSystem.eww`

- [ ] **步骤 1：git mv 现有工程文件到 Master/**

```bash
cd "C:\Users\orangeneko\Documents\HomeFireAlarmSystem"
mkdir Master TempNode GasNode Common
git mv HomeFireAlarmSystem.ewp Master/Master.ewp
git mv HomeFireAlarmSystem.ewd Master/Master.ewd
git mv HomeFireAlarmSystem.dep Master/Master.dep
git mv main.c Master/main.c
git mv settings Master/settings
git add -u && git commit -m "chore: 工程文件移入Master目录"
```

- [ ] **步骤 2：复制两份工程文件并改引用**

复制 `Master/Master.ewp` → `TempNode/TempNode.ewp`、`GasNode/GasNode.ewp`（.ewd 同理）。然后对每份新 .ewp 做文本替换：

```bash
sed -i 's/\$PROJ_DIR\$\\Master/$PROJ_DIR$/g; s/\$PROJ_DIR\$/$PROJ_DIR$\.\.\\/g; s/HomeFireAlarmSystem/TempNode/g' TempNode/TempNode.ewp
```

注意：替换后必须人工检查（用 Read）两点——① 所有源文件与 include 路径变为 `$PROJ_DIR$\..\Common\...` 或 `$PROJ_DIR$\main.c`；② 输出名变为 TempNode。若 .ewp 内 include 路径格式不同，用 Edit 逐处修正。

- [ ] **步骤 3：向三个 .ewp 的文件列表加入 Common 模块**

在每个 .ewp 的 `<files>` 组末尾（`</group>` 之后、`</files>` 之前——按现有 XML 结构定位）追加 Common 组（TempNode 示例，其余同名替换）：

```xml
<group>
  <name>Common</name>
  <file>
    <name>clk.c</name>
    <path>$PROJ_DIR$\..\Common\clk.c</path>
  </file>
  <file>
    <name>timer.c</name>
    <path>$PROJ_DIR$\..\Common\timer.c</path>
  </file>
  <file>
    <name>delay.c</name>
    <path>$PROJ_DIR$\..\Common\delay.c</path>
  </file>
  <file>
    <name>oled.c</name>
    <path>$PROJ_DIR$\..\Common\oled.c</path>
  </file>
  <file>
    <name>font16.c</name>
    <path>$PROJ_DIR$\..\Common\font16.c</path>
  </file>
  <file>
    <name>frame.c</name>
    <path>$PROJ_DIR$\..\Common\frame.c</path>
  </file>
  <file>
    <name>rf.c</name>
    <path>$PROJ_DIR$\..\Common\rf.c</path>
  </file>
  <file>
    <name>uart.c</name>
    <path>$PROJ_DIR$\..\Common\uart.c</path>
  </file>
</group>
```

同时在每个 .ewp 的编译器 include 路径（`<CCIncludes>` 下的 `<state>` 列表）追加一行：

```xml
<state>$PROJ_DIR$\..\Common</state>
```

本任务先只加任务 2-3 需要的 clk/timer/delay/oled/font16 六个文件也可（frame/rf/uart 文件创建后再补进 .ewp），避免工程引用不存在的文件导致 IAR 报错——**采用此方案：先只加六个，任务 4-5 创建 frame/uart/rf 后再 Edit 补进三个 .ewp。**

- [ ] **步骤 4：改写根 .eww**

```xml
<?xml version="1.0" encoding="iso-8859-1"?>
<workspace>
  <project>
    <path>$WS_DIR$\Master\Master.ewp</path>
  </project>
  <project>
    <path>$WS_DIR$\TempNode\TempNode.ewp</path>
  </project>
  <project>
    <path>$WS_DIR$\GasNode\GasNode.ewp</path>
  </project>
</workspace>
```

- [ ] **步骤 5：创建 TempNode/main.c、GasNode/main.c 骨架**

```c
/* TempNode/main.c — 温湿度节点（ID=0x02） */
#include <ioCC2530.h>
#define NODE_ID 0x02
void main(void)
{
    while(1) { }   /* 任务 6 实现 */
}
```

GasNode 同理（`NODE_ID 0x03`、注释改为"气体节点"）。Master/main.c 顶部加 `#define NODE_ID 0x01`。

- [ ] **步骤 6：编译验证**

查找 IAR 命令行构建工具（8051 版）：

```bash
ls "C:\Program Files (x86)\IAR Systems" 2>/dev/null; ls "C:\Program Files\IAR Systems" 2>/dev/null
# 找到形如 ...\8051\bin\IarBuild.exe 的路径后：
"<IarBuild路径>" HomeFireAlarmSystem.eww -build all
```

预期：三个工程 Build 全部 0 error（此时只有空 main，Common 文件为空壳即可——本步骤允许 Common/*.c 尚不存在的情况：若 .ewp 已引用不存在文件报错，先创建空 .c 占位文件，后续任务填充真实内容）。找不到 IarBuild.exe 时请用户在 IAR GUI 打开 `HomeFireAlarmSystem.eww` 目测三工程均可编译（F7）。

- [ ] **步骤 7：Commit**

```bash
git add -A && git commit -m "chore: 重组为三工程workspace并共享Common模块"
```

---

### 任务 2：时钟与时基（clk / timer / delay）

**文件：**
- 创建：`Common/clk.c`、`Common/clk.h`、`Common/timer.c`、`Common/timer.h`、`Common/delay.c`、`Common/delay.h`
- 修改：`Master/main.c`（临时验证代码）

- [ ] **步骤 1：编写 clk.c/h**

```c
/* Common/clk.h */
#ifndef CLK_H
#define CLK_H
void CLK_Init(void);          /* 系统时钟切换为 32MHz 晶振 */
#endif
```

```c
/* Common/clk.c */
#include <ioCC2530.h>
void CLK_Init(void)
{
    SLEEPCMD &= ~0x04;            /* 上电 32MHz 晶振 */
    while(!(SLEEPSTA & 0x40));    /* 等待 XOSC 稳定 */
    CLKCONCMD &= ~0x47;           /* 系统时钟 32MHz、定时器 tick 32MHz */
    while(CLKCONSTA & 0x40);      /* 等待时钟源切换生效 */
    SLEEPCMD |= 0x04;             /* 关闭未使用的 16MHz RC 振荡器 */
}
```

- [ ] **步骤 2：编写 timer.c/h（T1 毫秒时基）**

```c
/* Common/timer.h */
#ifndef TIMER_H
#define TIMER_H
#include <ioCC2530.h>
typedef unsigned char  u8;
typedef unsigned int   u16;
typedef unsigned long  u32;
extern volatile u32 g_ms;      /* 上电以来毫秒数（约 49.7 天回绕，课设无碍） */
void T1_Init(void);
#endif
```

```c
/* Common/timer.c */
#include <ioCC2530.h>
#include "timer.h"
volatile u32 g_ms = 0;
void T1_Init(void)
{
    T1CC0L = 249;                 /* 32MHz/128 = 250kHz，250 计数 = 1ms */
    T1CC0H = 0x00;
    T1CCTL0 |= 0x04;              /* 通道 0 比较中断使能 */
    T1CTL = 0x0E;                 /* 128 分频、模模式、启动 */
    IEN1 |= 0x02;                 /* T1 中断使能 */
    EA = 1;
}
#pragma vector = T1_VECTOR
__interrupt void T1_ISR(void)
{
    T1STAT &= ~0x01;              /* 清通道 0 比较标志 */
    g_ms++;
}
```

- [ ] **步骤 3：编写 delay.c/h（忙等版，DHT11 关中断区专用）**

```c
/* Common/delay.h */
#ifndef DELAY_H
#define DELAY_H
#include "timer.h"
void Delay_ms(u16 ms);            /* 忙等毫秒（不依赖中断，可在 EA=0 区使用） */
void Delay_us(u16 us);            /* 忙等微秒（32MHz 下近似值，DHT11 时序用） */
#endif
```

```c
/* Common/delay.c */
#include <ioCC2530.h>
#include "delay.h"
void Delay_ms(u16 ms)
{
    u16 i;
    while(ms--)
        for(i = 0; i < 1070; i++);   /* 32MHz 下实测约 1ms，任务 6 校准 DHT11 时验证 */
}
void Delay_us(u16 us)
{
    while(us--)
    {
        __no_operation(); __no_operation(); __no_operation(); __no_operation();
        __no_operation(); __no_operation(); __no_operation(); __no_operation();
    }
}
```

- [ ] **步骤 4：Master/main.c 写验证代码**

```c
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
            LED_ALARM = ~LED_ALARM;   /* 1Hz 翻转即通过 */
        }
    }
}
```

- [ ] **步骤 5：编译烧录验证现象**

编译 Master 工程零错误，烧录后：**主节点 LED 每秒翻转一次**（用手机秒表对 60 秒应翻转约 60 次，明显快/慢则 T1CC0 或分频配置有误）。

- [ ] **步骤 6：Commit**

```bash
git add Common/ Master/main.c && git commit -m "feat: 时钟32MHz初始化与T1毫秒时基"
```

---

### 任务 3：OLED 驱动与字库（oled / font16，I2C 底层）

**文件：**
- 创建：`Common/oled.c`、`Common/oled.h`、`Common/font16.c`、`Common/font16.h`
- 修改：`Master/main.c`（验证代码）、三个 .ewp 补引用（任务 1 步骤 3 已加则跳过）
- 参照（只读）：`docs/OLED资料/LCD_OLED示例代码/LCD.h`、`codetab.h`、`font matrix.txt`、`docs/OLED资料/MinerU_markdown_SPEC_QG-2864TMBEG01*.md`（I2C 从地址与时序）

- [ ] **步骤 1：编写软件 I2C 底层 + SSD1306 封装 + 显示层函数**

显示层函数（`LCD_P6x8Str`/`LCD_P8x16Str`/`LCD_P16x16Ch`/`LCD_Set_Pos` 等）**签名与示例代码完全一致**，任务 6-8 的调用代码无需任何改动；底层传输换为 GPIO 模拟 I2C（CC2530 无硬件 I2C）：

```c
/* Common/oled.c — SSD1306 0.96寸 128×64，I2C 软件模拟（约 350kHz） */
/* 模块 QG-2864TMBEG01（BS[2:0]=010 选 I2C），从地址 0x3C，写地址 0x78 */
#include <ioCC2530.h>
#include "oled.h"
#include "delay.h"

#define OLED_ADDR 0x78          /* 上屏失败改试 0x7A（0x3D） */

#define SCL_H() (P1_2 = 1)
#define SCL_L() (P1_2 = 0)
#define SDA_H() (P1DIR &= ~0x08)          /* SDA 释放为高阻，靠模块板载上拉 */
#define SDA_L() (P1_3 = 0, P1DIR |= 0x08) /* SDA 推挽拉低 */

static void i2c_dly(void)                 /* 半周期约 0.8us @32MHz */
{
    __no_operation(); __no_operation(); __no_operation();
    __no_operation(); __no_operation(); __no_operation();
}
static void i2c_start(void)
{
    SDA_H(); SCL_H(); i2c_dly();
    SDA_L(); i2c_dly();
    SCL_L();
}
static void i2c_stop(void)
{
    SDA_L(); i2c_dly();
    SCL_H(); i2c_dly();
    SDA_H(); i2c_dly();
}
static void i2c_wr_byte(unsigned char dat)    /* 8 位数据 + 第 9 位读 ACK（不校验） */
{
    unsigned char i;
    for(i = 0; i < 8; i++)
    {
        if(dat & 0x80) SDA_H(); else SDA_L();
        dat <<= 1;
        i2c_dly();
        SCL_H(); i2c_dly();
        SCL_L();
    }
    SDA_H();                     /* 释放 SDA 读 ACK */
    i2c_dly();
    SCL_H(); i2c_dly();
    SCL_L();
}
/* —— SSD1306 事务封装（I2C 控制字节：0x00 命令流 / 0x40 数据流） —— */
static void oled_cmd(unsigned char c)
{
    i2c_start();
    i2c_wr_byte(OLED_ADDR);
    i2c_wr_byte(0x00);
    i2c_wr_byte(c);
    i2c_stop();
}
static void oled_data(unsigned char d)
{
    i2c_start();
    i2c_wr_byte(OLED_ADDR);
    i2c_wr_byte(0x40);
    i2c_wr_byte(d);
    i2c_stop();
}
/* —— 显示层（签名与示例代码一致） —— */
void LCD_WrCmd(unsigned char cmd) { oled_cmd(cmd); }
void LCD_WrDat(unsigned char dat) { oled_data(dat); }
void LCD_Set_Pos(unsigned char x, unsigned char y)
{
    LCD_WrCmd(0xb0 + y);
    LCD_WrCmd(((x & 0xf0) >> 4) | 0x10);
    LCD_WrCmd(x & 0x0f);        /* 示例代码此处误写 |0x01 会整体偏移 1 列，I2C 版修正 */
}
void LCD_Init(void)
{
    P1SEL &= ~0x0C;             /* P1.2/P1.3 普通 IO */
    P1DIR |= 0x04;              /* SCL 输出；SDA 保持输入（释放） */
    SCL_H(); SDA_H();
    Delay_ms(100);              /* I2C 模块无复位脚，等上电稳定 */
    LCD_WrCmd(0xae); LCD_WrCmd(0x00); LCD_WrCmd(0x10); LCD_WrCmd(0x40);
    LCD_WrCmd(0x81); LCD_WrCmd(0xcf); LCD_WrCmd(0xa1); LCD_WrCmd(0xc8);
    LCD_WrCmd(0xa6); LCD_WrCmd(0xa8); LCD_WrCmd(0x3f); LCD_WrCmd(0xd3);
    LCD_WrCmd(0x00); LCD_WrCmd(0xd5); LCD_WrCmd(0x80); LCD_WrCmd(0xd9);
    LCD_WrCmd(0xf1); LCD_WrCmd(0xda); LCD_WrCmd(0x12); LCD_WrCmd(0xdb);
    LCD_WrCmd(0x40); LCD_WrCmd(0x20); LCD_WrCmd(0x02); LCD_WrCmd(0x8d);
    LCD_WrCmd(0x14);            /* 电荷泵使能 */
    LCD_WrCmd(0xa4); LCD_WrCmd(0xa6);
    LCD_WrCmd(0xaf);            /* display ON */
    LCD_Fill(0x00);
}
void LCD_Fill(unsigned char bmp_dat)
{
    unsigned char y, x;
    for(y = 0; y < 8; y++)
    {
        LCD_WrCmd(0xb0 + y);
        LCD_WrCmd(0x00); LCD_WrCmd(0x10);
        for(x = 0; x < 128; x++) LCD_WrDat(bmp_dat);
    }
}
void LCD_CLS(void) { LCD_Fill(0x00); }
void LCD_Invert(unsigned char on) { LCD_WrCmd(on ? 0xA7 : 0xA6); }
```

文本显示函数照示例代码 `LCD.h` 逐行抄录（内部调用指向上面的新版 `LCD_Set_Pos`/`LCD_WrDat`，无需改动函数体）。其中 `LCD_P16x16Ch` 完整对照：

```c
void LCD_P16x16Ch(unsigned char x, unsigned char y, unsigned char N)  /* N = 汉字索引 */
{
    unsigned char wm;
    unsigned int adder = 32 * N;
    LCD_Set_Pos(x, y);
    for(wm = 0; wm < 16; wm++) LCD_WrDat(F16x16[adder++]);
    LCD_Set_Pos(x, y + 1);
    for(wm = 0; wm < 16; wm++) LCD_WrDat(F16x16[adder++]);
}
```

`LCD_P6x8Str`、`LCD_P8x16Str` 与示例代码同名函数完全相同（循环取 F6x8/F8X16 字库写点阵），照抄即可。

性能说明：I2C 下每字节一次完整事务（地址+控制+数据约 90us），**全屏 1024 字节约 90ms**——只出现在报警页切换（低频，可接受）；数值行局部刷新（约 40 字节 = 4ms），每 2 秒一次，无可感影响。

`Common/oled.h` 与任务 1 计划一致（`LCD_Init/LCD_CLS/LCD_WrCmd/LCD_WrDat/LCD_Set_Pos/LCD_P6x8Str/LCD_P8x16Str/LCD_P16x16Ch/LCD_Invert`）。

- [ ] **步骤 2：生成 font16.c/h 字库**

`Common/font16.h`：

```c
#ifndef FONT16_H
#define FONT16_H
extern const unsigned char F16x16[];   /* 17 个 16x16 汉字，每字 32 字节 */
extern const unsigned char F6x8[][6];  /* ASCII 6x8，起始于空格 0x20 */
extern const unsigned char F8X16[];    /* ASCII 8x16，起始于空格 0x20 */
/* 汉字索引（与 font matrix.txt 一致）：
   0温 1湿 2度 3有 4害 5气 6体 7正 8异 9常
   10火 11灾 12警 13报 14离 15线 16℃ */
#endif
```

`Common/font16.c` 两部分：

1. `F16x16[]`：把 `font matrix.txt` 中 17 组（每组两行 `{...},{...}` 共 32 字节）按索引顺序**原样抄录**合并为一维数组。示例（温、湿两字，其余 15 字机械照搬，不改动任何字节）：

```c
const unsigned char F16x16[] = {
/* 0 温 */
0x20,0x08,0xC0,0xF8,0x06,0xFE,0xC4,0x81,0x30,0x80,0x00,0xFC,0xFE,0x83,0x92,0x82,
0x92,0xFC,0x92,0x82,0x92,0xFC,0x92,0x82,0xFE,0x83,0x00,0xFE,0x00,0x80,0x00,0x80,
/* 1 湿 */
0x20,0x00,0xC2,0xF8,0x04,0x0E,0xC0,0x01,0x30,0x82,0x00,0x84,0xFE,0xB8,0x52,0x80,
0x52,0xFF,0x52,0x80,0x52,0x80,0x52,0xFF,0x52,0x90,0xFE,0x88,0x00,0x86,0x00,0x80,
/* 2 度 … 16 ℃ 按 font matrix.txt 顺序继续 */
};
```

2. `F6x8` 与 `F8X16`：从 `docs/OLED资料/LCD_OLED示例代码/codetab.h` **整体复制**（先 Read 该文件获取数组）。若 codetab.h 使用了 IAR 特定存储修饰（如 `code`/`__code`），保持原样；用 `const` 也保持——均放入 Flash，不影响功能。

- [ ] **步骤 3：Master/main.c 换成上屏验证代码**

```c
/* Master/main.c — 任务 3 验证：主节点静态界面（全部 17 字 + ASCII） */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#define NODE_ID 0x01
void main(void)
{
    CLK_Init();
    LCD_Init();
    LCD_CLS();
    /* 行0：日期时间占位（页0） */
    LCD_P8x16Str(0, 0, "2026:09:08 16:30");
    /* 行1：温度:25℃（页2） */
    LCD_P16x16Ch(0, 2, 0);            /* 温 */
    LCD_P16x16Ch(16, 2, 2);           /* 度 */
    LCD_P8x16Str(32, 2, ":25");
    LCD_P16x16Ch(56, 2, 16);          /* ℃ */
    /* 行2：湿度:60%（页4） */
    LCD_P16x16Ch(0, 4, 1);            /* 湿 */
    LCD_P16x16Ch(16, 4, 2);           /* 度 */
    LCD_P8x16Str(32, 4, ":60%");
    /* 行3：有害气体:正常（页6） */
    LCD_P16x16Ch(0, 6, 3);            /* 有 */
    LCD_P16x16Ch(16, 6, 4);           /* 害 */
    LCD_P16x16Ch(32, 6, 5);           /* 气 */
    LCD_P16x16Ch(48, 6, 6);           /* 体 */
    LCD_P8x16Str(64, 6, ":");
    LCD_P16x16Ch(72, 6, 7);           /* 正 */
    LCD_P16x16Ch(88, 6, 9);           /* 常 */
    while(1) { }
}
```

- [ ] **步骤 4：编译烧录验证现象**

**判定标准（此步同时验证字模方向与 I2C 通信）：**
1. 四行内容完整显示、无乱码、无上下颠倒的碎点——字模方向正确；
2. 若汉字显示为上下镜像的乱码（上半/下半颠倒）：在 `LCD_P16x16Ch` 内把两个半页的写入顺序对调；若整体上下翻转：把 `LCD_Init` 里 `0xC8` 换 `0xC0`、`0xA1` 换 `0xA0` 重试；
3. ASCII 数字清晰；
4. **全屏黑/无任何显示**（I2C 不通）：`OLED_ADDR` 改 `0x7A` 重试；把 `i2c_dly` 里 nop 数量翻倍降速到 ~200kHz；确认模块背面 BS 电阻为 I2C 配置（BS[2:0]=010）；
5. 显示内容整体右偏 1 列：确认 `LCD_Set_Pos` 第三个命令为 `x & 0x0f`（无 `|0x01`）。

- [ ] **步骤 5：Commit**

```bash
git add Common/oled.c Common/oled.h Common/font16.c Common/font16.h Master/main.c && git commit -m "feat: OLED驱动移植与17汉字字库上屏"
```

---

### 任务 4：帧编解码 + 串口驱动（frame / uart）

**文件：**
- 创建：`Common/frame.c`、`Common/frame.h`、`Common/uart.c`、`Common/uart.h`
- 修改：三个 .ewp 补 frame.c/uart.c 引用、`Master/main.c`（验证代码）

- [ ] **步骤 1：编写 frame.c/h（纯逻辑，含自测）**

```c
/* Common/frame.h */
#ifndef FRAME_H
#define FRAME_H
#include "timer.h"
#define FRAME_MAX_LEN 32
u8 frame_pack(u8 *buf, u8 src, u8 dst, u8 cmd, const u8 *data, u8 len);
/* 返回打包后总长（0=失败）；buf 至少 FRAME_MAX_LEN 字节 */
u8 frame_parse(const u8 *buf, u8 len, u8 *src, u8 *dst, u8 *cmd, u8 *out);
/* 返回数据域长度（0=非法/校验错）；out 至少 FRAME_MAX_LEN-7 字节 */
u8 frame_selftest(u8 *buf);      /* 自测：返回 1=通过 */
#endif
```

```c
/* Common/frame.c */
#include <ioCC2530.h>
#include "frame.h"
u8 frame_pack(u8 *buf, u8 src, u8 dst, u8 cmd, const u8 *data, u8 len)
{
    u8 i, cs = 0;
    if(len > FRAME_MAX_LEN - 7) return 0;
    buf[0] = 0xAA; buf[1] = 0xBB;
    buf[2] = src;  buf[3] = dst;  buf[4] = cmd;  buf[5] = len;
    for(i = 0; i < len; i++) buf[6 + i] = data[i];
    for(i = 2; i < 6 + len; i++) cs ^= buf[i];
    buf[6 + len] = cs;
    return len + 7;
}
u8 frame_parse(const u8 *buf, u8 len, u8 *src, u8 *dst, u8 *cmd, u8 *out)
{
    u8 i, cs = 0;
    if(len < 7 || buf[0] != 0xAA || buf[1] != 0xBB) return 0;
    if(buf[5] != len - 7) return 0;
    for(i = 2; i < len - 1; i++) cs ^= buf[i];
    if(cs != buf[len - 1]) return 0;
    *src = buf[2]; *dst = buf[3]; *cmd = buf[4];
    for(i = 0; i < buf[5]; i++) out[i] = buf[6 + i];
    return buf[5];
}
u8 frame_selftest(u8 *buf)
{
    u8 d[5] = {10, 25, 0, 61, 0};
    u8 s, d2, c, out[FRAME_MAX_LEN], n;
    n = frame_pack(buf, 0x02, 0x01, 0x01, d, 5);
    if(n != 12) return 0;
    if(frame_parse(buf, n, &s, &d2, &c, out) != 5) return 0;
    if(s != 0x02 || d2 != 0x01 || c != 0x01 || out[0] != 10 || out[1] != 25) return 0;
    buf[3] ^= 0xFF;                              /* 破坏校验和 */
    if(frame_parse(buf, n, &s, &d2, &c, out) != 0) return 0;
    return 1;
}
```

- [ ] **步骤 2：编写 uart.c/h**

```c
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
```

```c
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
```

- [ ] **步骤 3：Master/main.c 验证代码（frame 自测 + 串口回显）**

```c
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
```

- [ ] **步骤 4：编译烧录 + 串口助手验证**

PC 用串口助手（115200 8N1）连主节点 USB 串口。**判定**：上电收到两行 `FRAME-TEST PASS` 与 `ECHO-OK`。收到 FAIL 则核对 frame_pack/parse 的异或范围（源 ID 起至校验前）。

- [ ] **步骤 5：Commit**

```bash
git add Common/frame.c Common/frame.h Common/uart.c Common/uart.h Master/main.c && git commit -m "feat: RF帧编解码与串口驱动自测通过"
```

---

### 任务 5：裸机 RF 驱动（rf）

**文件：**
- 创建：`Common/rf.c`、`Common/rf.h`
- 修改：三个 .ewp 补 rf.c 引用、`Master/main.c` 与 `TempNode/main.c`（双向收发验证代码）

- [ ] **步骤 1：编写 rf.c/h**

```c
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
```

```c
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
```

**排错提示（若收不到帧按序检查）：** ① 双方 FREQCTRL 同值；② `FRMFILT0=0` 是否生效（读回确认）；③ 用示波器/逻辑分析仪看对方天线端有无发射（无则发端问题：TXPOWER/RFD 写入顺序）；④ 把 `RFIRQM0 |= 0x40` 换成同时使能 `RFIRQF1 & 0x01`（SFD）打印验证收到能量。

- [ ] **步骤 2：TempNode/main.c 写定时发送验证代码**

```c
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
```

- [ ] **步骤 3：Master/main.c 写接收验证代码**

```c
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
            n = frame_parse(rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
            rf_rxLen = 0;
            if(n && dst == NODE_ID)
                UART_SendStr("RF-RX OK, src=\n");   /* 收到即打印，现象验证用 */
        }
    }
}
```

- [ ] **步骤 4：双板验证**

TempNode 工程烧入 2 号板、Master 烧入 1 号板，1 号板接 PC 串口。**判定**：串口助手每 2 秒出现一条 `RF-RX OK, src=`。收不到时按步骤 1 的排错提示逐项排查（本任务是全系统 RF 风险最集中处，宁可多花时间）。

- [ ] **步骤 5：Commit**

```bash
git add Common/rf.c Common/rf.h Master/main.c TempNode/main.c && git commit -m "feat: 裸机RF驱动双板互发验证通过"
```

---

### 任务 6：软件 RTC + 温湿度节点完整实现

**文件：**
- 创建：`Common/rtc.c`、`Common/rtc.h`、`TempNode/dht11.c`、`TempNode/dht11.h`
- 修改：`TempNode/main.c`（完整实现）、三个 .ewp（Common 组追加 rtc.c；TempNode 组追加 dht11.c）

- [ ] **步骤 1：编写 rtc.c/h（三节点共用）**

```c
/* Common/rtc.h */
#ifndef RTC_H
#define RTC_H
#include "timer.h"
typedef struct { u8 year, mon, day, hour, min, sec; } rtc_t;   /* year = 公历年-2000 */
extern rtc_t g_rtc;
void rtc_set(const u8 *ymdhms);   /* 用 6 字节数组（年-2000,月,日,时,分,秒）设置 */
void rtc_sec_tick(void);          /* 每秒调用一次，走时进位 */
void rtc_fmt(char *buf);          /* 格式化为 "2026:09:08 16:30"（17 字节含 \0） */
#endif
```

```c
/* Common/rtc.c */
#include "rtc.h"
rtc_t g_rtc = {26, 1, 1, 12, 0, 0};   /* 上电默认值，等待串口对时覆盖 */
static const u8 day_tab[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
void rtc_set(const u8 *t)
{
    g_rtc.year = t[0]; g_rtc.mon = t[1]; g_rtc.day = t[2];
    g_rtc.hour = t[3]; g_rtc.min = t[4]; g_rtc.sec = t[5];
}
void rtc_sec_tick(void)
{
    u8 max;
    if(++g_rtc.sec < 60) return;
    g_rtc.sec = 0;
    if(++g_rtc.min < 60) return;
    g_rtc.min = 0;
    if(++g_rtc.hour < 24) return;
    g_rtc.hour = 0;
    max = day_tab[g_rtc.mon - 1];
    if(g_rtc.mon == 2 && (g_rtc.year % 4) == 0) max = 29;   /* 20xx 闰年简化规则 */
    if(++g_rtc.day <= max) return;
    g_rtc.day = 1;
    if(++g_rtc.mon <= 12) return;
    g_rtc.mon = 1;
    g_rtc.year++;
}
void rtc_fmt(char *b)
{
    b[0] = '2';  b[1] = '0';
    b[2] = '0' + g_rtc.year / 10;  b[3] = '0' + g_rtc.year % 10;  b[4] = ':';
    b[5] = '0' + g_rtc.mon / 10;   b[6] = '0' + g_rtc.mon % 10;   b[7] = ':';
    b[8] = '0' + g_rtc.day / 10;   b[9] = '0' + g_rtc.day % 10;   b[10] = ' ';
    b[11] = '0' + g_rtc.hour / 10; b[12] = '0' + g_rtc.hour % 10; b[13] = ':';
    b[14] = '0' + g_rtc.min / 10;  b[15] = '0' + g_rtc.min % 10;  b[16] = '\0';
}
```

- [ ] **步骤 2：编写 dht11.c/h**

```c
/* TempNode/dht11.h */
#ifndef DHT11_H
#define DHT11_H
#include "timer.h"
u8 DHT11_Read(u8 *temp_i, u8 *temp_d, u8 *hum_i, u8 *hum_d);  /* 1=成功 */
#endif
```

```c
/* TempNode/dht11.c — 数据脚 P0.7，读取全程 ~5ms，调用方需 EA=0 保护 */
#include <ioCC2530.h>
#include "dht11.h"
#include "delay.h"
#define DHT P0_7
static u8 read_byte(void)
{
    u8 i, dat = 0;
    for(i = 0; i < 8; i++)
    {
        while(DHT == 0);      /* 等待本位 50us 低电平结束 */
        Delay_us(40);         /* 40us 后采样：高持续 26-28us=0，70us=1 */
        dat <<= 1;
        if(DHT == 1)
        {
            dat |= 0x01;
            while(DHT == 1);  /* 等待高电平结束 */
        }
    }
    return dat;
}
u8 DHT11_Read(u8 *temp_i, u8 *temp_d, u8 *hum_i, u8 *hum_d)
{
    u8 buf[5], i;
    u16 t;
    P0DIR |= 0x80;            /* 输出 */
    DHT = 0;
    Delay_ms(20);             /* 主机拉低 ≥18ms */
    DHT = 1;
    Delay_us(30);             /* 释放总线 20-40us */
    P0DIR &= ~0x80;           /* 切输入 */
    t = 3000;
    while(DHT == 0)  if(--t == 0) return 0;   /* DHT 响应 80us 低 */
    t = 3000;
    while(DHT == 1)  if(--t == 0) return 0;   /* DHT 响应 80us 高 */
    for(i = 0; i < 5; i++) buf[i] = read_byte();
    if((u8)(buf[0] + buf[1] + buf[2] + buf[3]) != buf[4]) return 0;
    *hum_i = buf[0]; *hum_d = buf[1]; *temp_i = buf[2]; *temp_d = buf[3];
    return 1;
}
```

- [ ] **步骤 3：TempNode/main.c 完整实现**

```c
/* TempNode/main.c — 温湿度节点（ID=0x02） */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#include "..\Common\rtc.h"
#include "..\Common\frame.h"
#include "..\Common\rf.h"
#include "dht11.h"
#define NODE_ID 0x02
#define LED_ALARM P1_0                /* 核心板 LED1，低电平点亮 */

static u8 page_alarm = 0;             /* 1=火灾警报页 */
static u8 temp_i = 0, temp_d = 0, hum_i = 0, hum_d = 0;
static u8 dirty = 0;

static void draw_time_row(void)
{
    char b[17];
    rtc_fmt(b);
    LCD_P8x16Str(0, 0, b);
}
static void draw_data_rows(void)
{
    char b[8];
    /* 行1（页2）：温度:xx.x℃ */
    LCD_P16x16Ch(0, 2, 0);  LCD_P16x16Ch(16, 2, 2);
    b[0]=':'; b[1]='0'+temp_i/10; b[2]='0'+temp_i%10;
    b[3]='.'; b[4]='0'+temp_d; b[5]='\0';
    LCD_P8x16Str(32, 2, b);
    LCD_P16x16Ch(72, 2, 16);          /* ℃ */
    /* 行2（页4）：湿度:xx.x% */
    LCD_P16x16Ch(0, 4, 1);  LCD_P16x16Ch(16, 4, 2);
    b[0]=':'; b[1]='0'+hum_i/10; b[2]='0'+hum_i%10;
    b[3]='.'; b[4]='0'+hum_d; b[5]='%'; b[6]='\0';
    LCD_P8x16Str(32, 4, b);
    /* 行3（页6）：节点标识 */
    LCD_P8x16Str(40, 6, "NODE 2");
}
static void draw_alarm_page(void)
{
    LCD_CLS();
    LCD_P16x16Ch(32, 3, 10); LCD_P16x16Ch(48, 3, 11);
    LCD_P16x16Ch(64, 3, 12); LCD_P16x16Ch(80, 3, 13);   /* 火灾警报 居中 */
    LCD_Invert(1);
}
static void draw_main_page(void)
{
    LCD_CLS();
    LCD_Invert(0);
    draw_time_row();
    draw_data_rows();
}
static void send_report(void)
{
    u8 d[5], buf[FRAME_MAX_LEN], n;
    static u8 seq = 0;
    d[0] = ++seq; d[1] = temp_i; d[2] = temp_d; d[3] = hum_i; d[4] = hum_d;
    n = frame_pack(buf, NODE_ID, 0x01, 0x01, d, 5);
    RF_Send(buf, n);
}
static void handle_rf(void)
{
    u8 src, dst, cmd, out[FRAME_MAX_LEN], n;
    if(!rf_rxLen) return;
    n = frame_parse(rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
    rf_rxLen = 0;
    if(!n || (dst != NODE_ID && dst != 0xFF)) return;
    if(cmd == 0x02 && n == 6)                 /* 对时广播 */
    {
        rtc_set(out);
        if(!page_alarm) draw_time_row();
    }
    else if(cmd == 0x03 && n == 2)            /* 报警状态广播 */
    {
        if((out[0] & 0x01) && !page_alarm) { page_alarm = 1; draw_alarm_page(); }
        else if(!(out[0] & 0x01) && page_alarm) { page_alarm = 0; draw_main_page(); }
    }
}
void main(void)
{
    u32 last_1s = 0, last_2s = 0;
    u8  last_min = 0xFF;
    CLK_Init();
    T1_Init();
    RF_Init();
    P1SEL &= ~0x01; P1DIR |= 0x01; LED_ALARM = 1;
    LCD_Init(); LCD_CLS();
    draw_time_row(); draw_data_rows();
    while(1)
    {
        if(g_ms - last_1s >= 1000)
        {
            last_1s += 1000;
            rtc_sec_tick();
            if(page_alarm) LCD_Invert(g_rtc.sec & 1);   /* 报警页 1Hz 反显闪烁 */
            else if(g_rtc.min != last_min) { last_min = g_rtc.min; draw_time_row(); }
        }
        if(g_ms - last_2s >= 2000)
        {
            last_2s += 2000;
            EA = 0;                     /* DHT11 时序 ~5ms，期间丢 RF 帧可接受（2s 周期） */
            if(DHT11_Read(&temp_i, &temp_d, &hum_i, &hum_d)) dirty = 1;
            EA = 1;
            send_report();              /* 数据包即心跳 */
            if(dirty && !page_alarm) { draw_data_rows(); dirty = 0; }
        }
        handle_rf();
        LED_ALARM = (page_alarm && (g_rtc.sec & 1)) ? 0 : 1;   /* 报警联动闪烁 */
    }
}
```

- [ ] **步骤 4：编译烧录验证现象**

TempNode 烧入 2 号板。**判定**：① OLED 显示 `温度:xx.x℃`、`湿度:xx.x%`，手指捂 DHT11 十几秒温度上升、对它哈气湿度上升；② 读数长期不动或恒 00.0 时检查 Delay_us 系数（40us 采样点）与 P0DIR 切换顺序；③ 若读数乱跳，先确认 Delay_ms(20) 实测约 20ms（把 `1070` 系数乘/除 2 微调）。

- [ ] **步骤 5：Commit**

```bash
git add Common/rtc.c Common/rtc.h TempNode/ && git commit -m "feat: 温湿度节点DHT11采集上报与RTC走时"
```

---

### 任务 7：气体节点完整实现（ADC + 滑动平均）

**文件：**
- 创建：`GasNode/adc.c`、`GasNode/adc.h`
- 修改：`GasNode/main.c`（完整实现）、`GasNode.ewp` 追加 adc.c

- [ ] **步骤 1：编写 adc.c/h**

```c
/* GasNode/adc.h */
#ifndef ADC_H
#define ADC_H
#include "timer.h"
u16 ADC_Read6(void);        /* AIN6(P0.6) 单次 12 位采样 */
u16 ADC_Avg6(u16 v);        /* 8 点滑动平均（对应规格"滤波算法"要求） */
#endif
```

```c
/* GasNode/adc.c */
#include <ioCC2530.h>
#include "adc.h"
u16 ADC_Read6(void)
{
    ADCCFG |= 0x40;               /* P0.6 ADC 输入使能 */
    ADCCON3 = 0xB6;               /* 参考 AVDD5(3.3V)、64 分频 12 位、通道 AIN6 */
    while(!(ADCCON1 & 0x80));     /* 等待 EOC */
    return (((u16)ADCH) << 4) | (ADCL >> 4);   /* 12 位结果 0~4095 */
}
u16 ADC_Avg6(u16 v)
{
    static u16 buf[8];
    static u8 idx = 0, full = 0;
    u32 sum = 0;
    u8 i, n;
    buf[idx] = v;
    idx = (idx + 1) & 7;
    if(!full && idx == 0) full = 1;
    n = full ? 8 : idx;
    for(i = 0; i < n; i++) sum += buf[i];
    return (u16)(sum / n);
}
```

- [ ] **步骤 2：硬件安全检查（在烧录前做）**

MQ-2 模块按资料用 5V 供电时 AO 输出可能超过 CC2530 的 3.3V ADC 量程。**用万用表测模块 AO 对地电压**：清洁空气预热后应 < 1V；若酒精测试时可能 > 3.3V，在 AO 与 P0.6 之间加两个电阻分压（上 10kΩ 下 20kΩ，把 5V 上限压到 3.33V）。检查结果记录进 commit 说明。

- [ ] **步骤 3：GasNode/main.c 完整实现**

```c
/* GasNode/main.c — 气体节点（ID=0x03） */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#include "..\Common\rtc.h"
#include "..\Common\frame.h"
#include "..\Common\rf.h"
#include "adc.h"
#define NODE_ID 0x03
#define LED_ALARM P1_0
#define MQ2_DO P0_5                   /* DO：超模块电位器阈值为低 */

static u8  page_alarm = 0;
static u16 gas_avg = 0;
static u8  dirty = 0;

static void draw_time_row(void)       /* 与 TempNode 相同实现 */
{
    char b[17];
    rtc_fmt(b);
    LCD_P8x16Str(0, 0, b);
}
static void draw_data_rows(void)
{
    char b[6];
    /* 行1（页2）：有害气体:正常/异常（按 DO 判） */
    LCD_P16x16Ch(0, 2, 3); LCD_P16x16Ch(16, 2, 4);
    LCD_P16x16Ch(32, 2, 5); LCD_P16x16Ch(48, 2, 6);
    LCD_P8x16Str(64, 2, ":");
    if(MQ2_DO == 0) { LCD_P16x16Ch(72, 2, 8); LCD_P16x16Ch(88, 2, 9); }   /* 异常 */
    else            { LCD_P16x16Ch(72, 2, 7); LCD_P16x16Ch(88, 2, 9); }   /* 正常 */
    /* 行2（页4）：ADC:xxxx（平均后浓度值） */
    b[0] = '0' + gas_avg / 1000;
    b[1] = '0' + gas_avg / 100 % 10;
    b[2] = '0' + gas_avg / 10 % 10;
    b[3] = '0' + gas_avg % 10;
    b[4] = '\0';
    LCD_P8x16Str(0, 4, "ADC:");
    LCD_P8x16Str(32, 4, b);
    /* 行3（页6）：NODE 3 */
    LCD_P8x16Str(40, 6, "NODE 3");
}
static void draw_alarm_page(void)
{
    LCD_CLS();
    LCD_P16x16Ch(32, 3, 10); LCD_P16x16Ch(48, 3, 11);
    LCD_P16x16Ch(64, 3, 12); LCD_P16x16Ch(80, 3, 13);
    LCD_Invert(1);
}
static void draw_main_page(void)
{
    LCD_CLS();
    LCD_Invert(0);
    draw_time_row();
    draw_data_rows();
}
static void send_report(void)
{
    u8 d[4], buf[FRAME_MAX_LEN], n;
    static u8 seq = 0;
    d[0] = ++seq;
    d[1] = (u8)(gas_avg >> 8); d[2] = (u8)(gas_avg & 0xFF);
    d[3] = (MQ2_DO == 0) ? 1 : 0;
    n = frame_pack(buf, NODE_ID, 0x01, 0x01, d, 4);
    RF_Send(buf, n);
}
static void handle_rf(void)           /* 与 TempNode 相同：0x02 对时、0x03 报警页切换 */
{
    u8 src, dst, cmd, out[FRAME_MAX_LEN], n;
    if(!rf_rxLen) return;
    n = frame_parse(rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
    rf_rxLen = 0;
    if(!n || (dst != NODE_ID && dst != 0xFF)) return;
    if(cmd == 0x02 && n == 6)
    {
        rtc_set(out);
        if(!page_alarm) draw_time_row();
    }
    else if(cmd == 0x03 && n == 2)
    {
        if((out[0] & 0x01) && !page_alarm) { page_alarm = 1; draw_alarm_page(); }
        else if(!(out[0] & 0x01) && page_alarm) { page_alarm = 0; draw_main_page(); }
    }
}
void main(void)
{
    u32 last_1s = 0, last_2s = 0;
    u8  last_min = 0xFF, warmup = 30;         /* 上电 60s 预热期（30 次×2s） */
    CLK_Init();
    T1_Init();
    RF_Init();
    P1SEL &= ~0x01; P1DIR |= 0x01; LED_ALARM = 1;
    P0SEL &= ~0x20; P0DIR &= ~0x20;           /* P0.5 输入（DO） */
    LCD_Init(); LCD_CLS();
    LCD_P8x16Str(16, 4, "WARM UP 60s");       /* 预热提示（ASCII） */
    draw_time_row();
    while(1)
    {
        if(g_ms - last_1s >= 1000)
        {
            last_1s += 1000;
            rtc_sec_tick();
            if(page_alarm) LCD_Invert(g_rtc.sec & 1);
            else if(g_rtc.min != last_min && !warmup) { last_min = g_rtc.min; draw_time_row(); }
        }
        if(g_ms - last_2s >= 2000)
        {
            last_2s += 2000;
            gas_avg = ADC_Avg6(ADC_Read6());
            if(warmup) { warmup--; if(!warmup) { LCD_CLS(); draw_data_rows(); } }
            else { send_report(); if(dirty) { draw_data_rows(); dirty = 0; } dirty = 1; }
        }
        handle_rf();
        LED_ALARM = (page_alarm && (g_rtc.sec & 1)) ? 0 : 1;
    }
}
```

（说明：`draw_data_rows` 无其他隐藏依赖，与 TempNode 版本同名函数职责一致，复制时注意本节点没有 `dirty` 之外的额外状态。）

- [ ] **步骤 4：编译烧录验证现象**

GasNode 烧入 3 号板，MQ-2 提前通电预热 5 分钟以上。**判定**：① OLED 显示 `ADC:xxxx`（清洁空气典型值 100~500，随预热缓慢下降后稳定）；② 酒精棉/打火机放气（**不点火**）靠近 3 秒，ADC 值明显飙升且 DO 变低、状态切`异常`；③ 移开后回落。

- [ ] **步骤 5：Commit**

```bash
git add GasNode/ && git commit -m "feat: 气体节点ADC滑动平均采样与上报"
```

---

### 任务 8：主节点完整应用（界面/判决/CSV/指令）

**文件：**
- 创建：`Master/csv.c`、`Master/csv.h`
- 修改：`Master/main.c`（完整实现，替换任务 5 验证代码）、`Master.ewp` 追加 csv.c

- [ ] **步骤 1：编写 csv.c/h（串口消息打包 + 下行解析）**

```c
/* Master/csv.h */
#ifndef CSV_H
#define CSV_H
#include "timer.h"
void csv_send_body(const char *body);      /* 自动补 *校验 + \r\n 并发送 */
void csv_send_data_th(u8 ti, u8 td, u8 hi, u8 hd);          /* D,2,… */
void csv_send_data_gas(u16 adc, u8 do_hit);                 /* D,3,… */
void csv_send_status(u8 node, u8 online);                   /* S,2,ONLINE */
void csv_send_alarm(u8 on, u8 src);                         /* A,1,2 */
void csv_send_loss(u8 node, u16 lost, u16 total);           /* L,2,3,128 */
void csv_send_thresh(u16 t, u16 g);                         /* T,45,600 */
/* 下行解析：uart_line 匹配 SET/TEST/TIME，成功返回 1（内部已 uart_line_consume） */
u8   csv_handle_line(void);
#endif
```

```c
/* Master/csv.c — ASCII 数字手写转换，不用 sprintf（8051 资源紧张） */
#include <ioCC2530.h>
#include <string.h>
#include "csv.h"
#include "..\Common\uart.h"
#include "..\Common\rtc.h"
extern u16 th_temp, th_gas;               /* 定义在 main.c */
extern u8  test_on;

static const char hex_tab[] = "0123456789ABCDEF";
static u8 u16_to_str(u16 v, char *b)      /* 返回位数 */
{
    char t[5]; u8 n = 0, i = 0;
    do { t[n++] = '0' + v % 10; v /= 10; } while(v);
    while(n) b[i++] = t[--n];
    return i;
}
void csv_send_body(const char *body)
{
    char out[48]; u8 i = 0, cs = 0;
    const char *p = body;
    while(*p) { cs ^= (u8)*p; out[i++] = *p++; }
    out[i++] = '*';
    out[i++] = hex_tab[cs >> 4];
    out[i++] = hex_tab[cs & 0x0F];
    out[i++] = '\r'; out[i++] = '\n';
    UART_SendBytes((u8 *)out, i);
}
void csv_send_data_th(u8 ti, u8 td, u8 hi, u8 hd)
{
    char b[24]; u8 i = 0;
    strcpy(b, "D,2,"); i = 4;
    b[i++] = '0' + ti / 10; b[i++] = '0' + ti % 10; b[i++] = ',';
    b[i++] = '0' + td; b[i++] = ',';
    b[i++] = '0' + hi / 10; b[i++] = '0' + hi % 10; b[i++] = ',';
    b[i++] = '0' + hd; b[i] = '\0';
    csv_send_body(b);
}
void csv_send_data_gas(u16 adc, u8 do_hit)
{
    char b[20], n[5]; u8 i = 0, k;
    strcpy(b, "D,3,"); i = 4;
    k = u16_to_str(adc, n);
    while(k) b[i++] = n[--k];
    b[i++] = ',';
    b[i++] = '0' + do_hit; b[i] = '\0';
    csv_send_body(b);
}
void csv_send_status(u8 node, u8 online)
{
    char b[16]; u8 i = 0;
    b[i++] = 'S'; b[i++] = ','; b[i++] = '0' + node; b[i++] = ',';
    strcpy(b + i, online ? "ONLINE" : "OFFLINE");
    csv_send_body(b);
}
void csv_send_alarm(u8 on, u8 src)
{
    char b[10]; u8 i = 0;
    b[i++] = 'A'; b[i++] = ','; b[i++] = '0' + on; b[i++] = ','; b[i++] = '0' + src; b[i] = '\0';
    csv_send_body(b);
}
void csv_send_loss(u8 node, u16 lost, u16 total)
{
    char b[24], n[6]; u8 i = 0, k;
    b[i++] = 'L'; b[i++] = ','; b[i++] = '0' + node; b[i++] = ',';
    k = u16_to_str(lost, n);  while(k) b[i++] = n[--k];
    b[i++] = ',';
    k = u16_to_str(total, n); while(k) b[i++] = n[--k];
    b[i] = '\0';
    csv_send_body(b);
}
void csv_send_thresh(u16 t, u16 g)
{
    char b[20], n[6]; u8 i = 0, k;
    strcpy(b, "T,"); i = 2;
    k = u16_to_str(t, n); while(k) b[i++] = n[--k];
    b[i++] = ',';
    k = u16_to_str(g, n); while(k) b[i++] = n[--k];
    b[i] = '\0';
    csv_send_body(b);
}
/* —— 下行解析 —— */
static const char *skip_to(const char *s, u8 n)   /* 跳过 n 个逗号 */
{
    while(n && *s) { if(*s++ == ',') n--; }
    return s;
}
static u16 parse_u16(const char **ps)
{
    u16 v = 0;
    while(**ps >= '0' && **ps <= '9') v = v * 10 + (*(*ps)++ - '0');
    return v;
}
u8 csv_handle_line(void)
{
    const char *s = (const char *)uart_line;
    if(!strncmp(s, "SET,", 4))
    {
        const char *p = skip_to(s, 1);
        th_temp = parse_u16(&p); p = skip_to(s, 2);
        th_gas  = parse_u16(&p);
        csv_send_thresh(th_temp, th_gas);
        uart_line_consume();
        return 1;
    }
    if(!strncmp(s, "TEST,", 5))
    {
        const char *p = skip_to(s, 1);
        test_on = (parse_u16(&p) == 1);
        uart_line_consume();
        return 2;                             /* main.c 据此触发/解除模拟报警 */
    }
    if(!strncmp(s, "TIME,", 5))
    {
        const char *p = skip_to(s, 1);
        u8 t[6], i;
        for(i = 0; i < 6; i++) { t[i] = (u8)parse_u16(&p); p = skip_to(s, i + 2); }
        rtc_set(t);
        uart_line_consume();
        return 3;                             /* main.c 据此立即广播对时 */
    }
    uart_line_consume();
    return 0;
}
```

（实现提示：`skip_to`/`parse_u16` 的游标推进逻辑以"从行首按逗号取第 n 个字段"为准，落地时用 `"SET,50,700"`、`"TIME,26,9,8,16,30,0"` 两个样例在串口助手上验证解析结果，回显 `T,50,700` 与 OLED 时间跳变即正确。）

- [ ] **步骤 2：Master/main.c 完整实现**

```c
/* Master/main.c — 主节点（ID=0x01） */
#include <ioCC2530.h>
#include "..\Common\clk.h"
#include "..\Common\timer.h"
#include "..\Common\oled.h"
#include "..\Common\font16.h"
#include "..\Common\rtc.h"
#include "..\Common\frame.h"
#include "..\Common\rf.h"
#include "..\Common\uart.h"
#include "csv.h"
#define NODE_ID 0x01
#define LED_ALARM P0_5                   /* 低电平点亮 */

typedef struct {
    u8  online;
    u32 last_ms;
    u8  last_seq;
    u16 loss, total;
    u8  temp_i, temp_d, hum_i, hum_d;    /* 节点 2 用 */
    u16 gas;  u8  gas_do;                /* 节点 3 用 */
} node_info_t;

node_info_t n2, n3;
u16 th_temp = 45, th_gas = 600;
u8  alarm_on = 0, alarm_src = 0, test_on = 0;

static void draw_main_page(void)
{
    char b[17];
    LCD_CLS(); LCD_Invert(0);
    rtc_fmt(b); LCD_P8x16Str(0, 0, b);
    /* 温度行 */
    LCD_P16x16Ch(0, 2, 0); LCD_P16x16Ch(16, 2, 2);
    b[0]=':'; b[1]='0'+n2.temp_i/10; b[2]='0'+n2.temp_i%10;
    b[3]='.'; b[4]='0'+n2.temp_d; b[5]='\0';
    LCD_P8x16Str(32, 2, b); LCD_P16x16Ch(72, 2, 16);
    /* 湿度行 */
    LCD_P16x16Ch(0, 4, 1); LCD_P16x16Ch(16, 4, 2);
    b[0]=':'; b[1]='0'+n2.hum_i/10; b[2]='0'+n2.hum_i%10;
    b[3]='.'; b[4]='0'+n2.hum_d; b[5]='%'; b[6]='\0';
    LCD_P8x16Str(32, 4, b);
    /* 有害气体行：正常/异常/离线 */
    LCD_P16x16Ch(0, 6, 3); LCD_P16x16Ch(16, 6, 4);
    LCD_P16x16Ch(32, 6, 5); LCD_P16x16Ch(48, 6, 6);
    LCD_P8x16Str(64, 6, ":");
    if(!n3.online)      { LCD_P16x16Ch(72, 6, 14); LCD_P16x16Ch(88, 6, 15); }  /* 离线 */
    else if(n3.gas_do)  { LCD_P16x16Ch(72, 6, 7);  LCD_P16x16Ch(88, 6, 9);  }  /* 正常 */
    else                { LCD_P16x16Ch(72, 6, 8);  LCD_P16x16Ch(88, 6, 9);  }  /* 异常 */
}
static void draw_alarm_page(void)
{
    LCD_CLS();
    LCD_P16x16Ch(32, 3, 10); LCD_P16x16Ch(48, 3, 11);
    LCD_P16x16Ch(64, 3, 12); LCD_P16x16Ch(80, 3, 13);
    LCD_Invert(1);
}
static void broadcast_time(void)
{
    u8 d[6] = { g_rtc.year, g_rtc.mon, g_rtc.day, g_rtc.hour, g_rtc.min, g_rtc.sec };
    u8 buf[FRAME_MAX_LEN], n;
    n = frame_pack(buf, NODE_ID, 0xFF, 0x02, d, 6);
    RF_Send(buf, n);
}
static void set_alarm(u8 on, u8 src)
{
    alarm_on = on; alarm_src = src;
    if(!on) test_on = 0;
    if(on) draw_alarm_page(); else draw_main_page();
    {
        u8 d[2] = { on, src };
        u8 buf[FRAME_MAX_LEN], n;
        n = frame_pack(buf, NODE_ID, 0xFF, 0x03, d, 2);
        RF_Send(buf, n);
    }
    csv_send_alarm(on, src);
}
static void judge_alarm(void)             /* 500ms 调一次；回差 5% 防抖 */
{
    if(alarm_on)
    {
        u8 still = 0;
        if(alarm_src == 1 && n2.online && n2.temp_i > th_temp - th_temp / 20) still = 1;
        else if(alarm_src == 2 && n3.online && n3.gas > th_gas - th_gas / 20) still = 1;
        else if(alarm_src == 3 && test_on) still = 1;
        if(!still) set_alarm(0, 0);
    }
    else
    {
        if(n2.online && n2.temp_i > th_temp)      set_alarm(1, 1);
        else if(n3.online && n3.gas > th_gas)     set_alarm(1, 2);
        else if(test_on)                          set_alarm(1, 3);
    }
}
static void handle_rf(void)
{
    u8 src, dst, cmd, out[FRAME_MAX_LEN], n, diff;
    if(!rf_rxLen) return;
    n = frame_parse(rf_rxBuf, rf_rxLen, &src, &dst, &cmd, out);
    rf_rxLen = 0;
    if(!n || dst != NODE_ID) return;
    if(cmd == 0x01 && src == 0x02 && n == 5)
    {
        diff = (u8)(out[0] - n2.last_seq);
        if(n2.online && diff > 1) n2.loss += diff - 1;
        n2.total++;
        n2.last_seq = out[0];
        n2.temp_i = out[1]; n2.temp_d = out[2]; n2.hum_i = out[3]; n2.hum_d = out[4];
        if(!n2.online) { n2.online = 1; csv_send_status(2, 1); csv_send_loss(2, n2.loss, n2.total); }
        n2.last_ms = g_ms;
        csv_send_data_th(n2.temp_i, n2.temp_d, n2.hum_i, n2.hum_d);
        if(!alarm_on) draw_main_page();       /* 数值行刷新（简化为整页重画，OLED 无可感闪烁） */
    }
    else if(cmd == 0x01 && src == 0x03 && n == 4)
    {
        diff = (u8)(out[0] - n3.last_seq);
        if(n3.online && diff > 1) n3.loss += diff - 1;
        n3.total++;
        n3.last_seq = out[0];
        n3.gas = ((u16)out[1] << 8) | out[2]; n3.gas_do = out[3];
        if(!n3.online) { n3.online = 1; csv_send_status(3, 1); csv_send_loss(3, n3.loss, n3.total); }
        n3.last_ms = g_ms;
        csv_send_data_gas(n3.gas, n3.gas_do);
        if(!alarm_on) draw_main_page();
    }
}
static void check_offline(void)              /* 1s 调一次 */
{
    if(n2.online && g_ms - n2.last_ms > 10000)
    { n2.online = 0; csv_send_status(2, 0); csv_send_loss(2, n2.loss, n2.total); if(!alarm_on) draw_main_page(); }
    if(n3.online && g_ms - n3.last_ms > 10000)
    { n3.online = 0; csv_send_status(3, 0); csv_send_loss(3, n3.loss, n3.total); if(!alarm_on) draw_main_page(); }
}
void main(void)
{
    u32 last_500 = 0, last_1s = 0, last_60s = 0;
    u8  last_min = 0xFF;
    CLK_Init();
    T1_Init();
    RF_Init();
    UART_Init();
    P0SEL &= ~0x20; P0DIR |= 0x20; LED_ALARM = 1;
    LCD_Init(); LCD_CLS();
    draw_main_page();
    csv_send_thresh(th_temp, th_gas);        /* 上线告知上位机当前阈值 */
    while(1)
    {
        if(uart_line_ready)
        {
            u8 r = csv_handle_line();
            if(r == 2) judge_alarm();         /* TEST 置位/复位后立即判决 */
            else if(r == 3) { broadcast_time(); draw_main_page(); }
        }
        handle_rf();
        if(g_ms - last_500 >= 500) { last_500 += 500; judge_alarm(); }
        if(g_ms - last_1s >= 1000)
        {
            last_1s += 1000;
            rtc_sec_tick();
            check_offline();
            if(alarm_on) LCD_Invert(g_rtc.sec & 1);      /* 报警 1Hz 闪烁 */
            else if(g_rtc.min != last_min) { last_min = g_rtc.min; draw_main_page(); }
        }
        if(g_ms - last_60s >= 60000) { last_60s += 60000; broadcast_time(); }
        LED_ALARM = (alarm_on && (g_rtc.sec & 1)) ? 0 : 1;
    }
}
```

- [ ] **步骤 3：编译 + 串口助手验证（终端未全上也可验）**

烧录主节点，串口助手依次发送（每条以 `\r\n` 结尾）：
- `SET,50,700` → 应回 `T,50,700,*63`
- `TEST,1` → 应回 `A,1,3,*4E`（校验值以串口实测为准）且主节点 OLED 切"火灾警报"反显闪烁、LED 闪烁
- `TEST,0` → 恢复主界面，回 `A,0,0,*??`
- `TIME,26,9,8,16,30,0` → OLED 时间行变为 `2026:09:08 16:30` 并继续走时

（`A,1,3` 校验：0x41^0x2C^0x31^0x2C^0x33=0x44 → `A,1,3,*44`；`A,0,0`：0x41^0x2C^0x30^0x2C^0x30=0x47 → `A,0,0,*47`。）

- [ ] **步骤 4：Commit**

```bash
git add Master/ && git commit -m "feat: 主节点界面判决CSV上报与下行指令"
```

---

### 任务 9：三节点组网联调

**文件：** 无新增（联调任务；发现问题按来源回到对应任务修复后重新验证）

- [ ] **步骤 1：三节点全上电组网**

三块板各自上电（MQ-2 先预热 5 分钟），主节点接 PC 串口、开串口助手。**逐项判定：**
1. 主节点 OLED 时间在首次 `TIME,26,9,8,16,30,0` 指令后正确，之后每分钟自动广播对时（验证：串口发一次对时后拔掉串口助手 10 分钟，三块屏时间仍一致，误差 ≤ 数秒）；
2. 主节点四行界面实时刷新温湿度与气体状态（与两终端 OLED 显示一致）；
3. 串口助手每 2 秒收到 `D,2,…` 与 `D,3,…` 各一条；
4. 拔掉 3 号板电源 → 约 10 秒后主节点气体行显示`离线`，串口收到 `S,3,OFFLINE` 与 `L,3,…`；重新上电 → 恢复 `S,3,ONLINE`；
5. 串口发 `TEST,1` → 三块 OLED 同时切"火灾警报"反显闪烁，主节点 LED 与两终端 LED1 同步闪；`TEST,0` 全部恢复。

- [ ] **步骤 2：真实报警标定与联动**

1. 打火机放气（不点火）靠近 MQ-2 → 主节点气体行切`异常`、LED 闪烁报警、终端联动、串口收到 `A,1,2`；散去后 5% 回差内自动解除；
2. 记录触发时刻串口里的 ADC 值：若与默认阈值 600 相差悬殊，修改 `Master/main.c` 的 `th_gas` 初值（取"清洁空气值"与"触发值"的中点），重新烧录；
3. 热源（如吹风机热风）靠近 DHT11 至 45℃ 以上 → 温度报警路径 `A,1,1` 同样验证。

- [ ] **步骤 3：Commit（记录标定结果）**

```bash
git add -A && git commit -m "chore: 三节点联调通过并记录MQ-2阈值标定"
```

---

### 任务 10：Python 桥 bridge.py（含单元测试）

**文件：**
- 创建：`bridge.py`、`test_bridge.py`
- 环境：项目内便携 Python（`Python311\python.exe`），依赖 `pyserial`、`websockets`

- [ ] **步骤 1：安装依赖**

```bash
"C:\Users\orangeneko\Documents\HomeFireAlarmSystem\Python311\python.exe" -m pip install pyserial websockets
```

预期：两包安装成功（命令是往便携环境的 site-packages 装两个纯 Python 包，不影响系统 Python）。

- [ ] **步骤 2：编写 bridge.py**

```python
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""家庭火灾报警系统串口桥：CC2530 主节点 CSV <-> 网页 WebSocket JSON"""
import asyncio
import json
import os
import sys
import threading
import time
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer

import serial
import websockets

WS_PORT = 8081
HTTP_PORT = 8080
WEB_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "web")
clients = set()          # 当前连接的 WebSocket

def xor_cs(text: str) -> str:
    cs = 0
    for ch in text:
        cs ^= ord(ch)
    return f"{cs:02X}"

def parse_line(line: str):
    """'D,2,25,0,61,0,*5A' -> dict；校验失败/不认识返回 None"""
    if "*" not in line:
        return None
    body, cs = line.rsplit("*", 1)
    if xor_cs(body) != cs.strip().upper():
        return None
    f = body.split(",")
    try:
        if f[0] == "D":
            if len(f) == 7:      # D,2,25,0,61,0  温湿度
                return {"type": "data", "node": int(f[1]),
                        "temp": int(f[2]) + int(f[3]) / 10,
                        "hum": int(f[4]) + int(f[5]) / 10}
            if len(f) == 5:      # D,3,812,1  气体
                return {"type": "data", "node": int(f[1]),
                        "gas": int(f[2]), "do": int(f[3])}
            return None
        if f[0] == "S" and len(f) == 3:
            return {"type": "status", "node": int(f[1]), "online": f[2] == "ONLINE"}
        if f[0] == "A" and len(f) == 3:
            return {"type": "alarm", "on": f[1] == "1", "src": int(f[2])}
        if f[0] == "L" and len(f) == 4:
            return {"type": "loss", "node": int(f[1]),
                    "lost": int(f[2]), "total": int(f[3])}
        if f[0] == "T" and len(f) == 3:
            return {"type": "threshold", "temp": int(f[1]), "gas": int(f[2])}
    except (ValueError, IndexError):
        return None
    return None

def build_downlink(msg: dict):
    """网页 JSON -> 串口字节行（含校验）；不认识返回 None"""
    t = msg.get("type")
    if t == "setThreshold":
        body = f"SET,{int(msg['temp'])},{int(msg['gas'])}"
    elif t == "testAlarm":
        body = f"TEST,{1 if msg.get('on') else 0}"
    elif t == "setTime":
        now = time.localtime()
        body = (f"TIME,{now.tm_year - 2000},{now.tm_mon},{now.tm_mday},"
                f"{now.tm_hour},{now.tm_min},{now.tm_sec}")
    else:
        return None
    return (body + "*" + xor_cs(body) + "\r\n").encode("ascii")

class Bridge:
    def __init__(self, port: str):
        self.ser = serial.Serial(port, 115200, timeout=1)
        self.loop = None

    def reader_thread(self):
        """串口读线程：逐行解析 -> WS 广播（带桥端时间戳）"""
        buf = b""
        while True:
            data = self.ser.read(64)
            if not data:
                continue
            buf += data
            while b"\n" in buf:
                line, buf = buf.split(b"\n", 1)
                text = line.decode("ascii", "ignore").strip()
                if not text:
                    continue
                msg = parse_line(text)
                if msg:
                    msg["ts"] = time.time()
                    asyncio.run_coroutine_threadsafe(self.broadcast(msg), self.loop)

    async def broadcast(self, msg: dict):
        if clients:
            text = json.dumps(msg, ensure_ascii=False)
            await asyncio.gather(*(c.send(text) for c in clients),
                                 return_exceptions=True)

    async def ws_handler(self, ws):
        clients.add(ws)
        try:
            async for raw in ws:
                try:
                    msg = json.loads(raw)
                except json.JSONDecodeError:
                    continue
                frame = build_downlink(msg)
                if frame:
                    self.ser.write(frame)
        finally:
            clients.discard(ws)

def main():
    port = sys.argv[1] if len(sys.argv) > 1 else None
    if not port:
        from serial.tools import list_ports
        print("用法: Python311\\python.exe bridge.py COM口")
        print("可用串口:", [p.device for p in list_ports.comports()] or "无")
        sys.exit(1)
    bridge = Bridge(port)
    loop = asyncio.new_event_loop()
    bridge.loop = loop
    threading.Thread(target=bridge.reader_thread, daemon=True).start()

    def http_worker():
        os.chdir(WEB_DIR)
        ThreadingHTTPServer(("0.0.0.0", HTTP_PORT),
                            SimpleHTTPRequestHandler).serve_forever()
    threading.Thread(target=http_worker, daemon=True).start()

    print(f"串口 {port} 已连接")
    print(f"网页  http://localhost:{HTTP_PORT}")
    print(f"WS    ws://localhost:{WS_PORT}")

    async def serve():
        async with websockets.serve(bridge.ws_handler, "0.0.0.0", WS_PORT):
            await asyncio.Future()
    loop.run_until_complete(serve())

if __name__ == "__main__":
    main()
```

- [ ] **步骤 3：编写 test_bridge.py（先于集成验证运行，TDD 顺序可为：先写测试看它失败）**

```python
# -*- coding: utf-8 -*-
"""bridge.py 纯逻辑单元测试：Python311\\python.exe -m unittest test_bridge -v"""
import unittest
from bridge import xor_cs, parse_line, build_downlink

class TestChecksum(unittest.TestCase):
    def test_known_values(self):
        self.assertEqual(xor_cs("D,2,25,0,61,0"), "5A")
        self.assertEqual(xor_cs("D,3,812,1"), "51")
        self.assertEqual(xor_cs("S,2,ONLINE"), "6E")
        self.assertEqual(xor_cs("A,1,2"), "42")
        self.assertEqual(xor_cs("L,2,3,128"), "5A")
        self.assertEqual(xor_cs("T,45,600"), "63")
        self.assertEqual(xor_cs("SET,50,700"), "70")
        self.assertEqual(xor_cs("TEST,1"), "0B")
        self.assertEqual(xor_cs("TIME,26,9,8,16,30,0"), "24")

class TestParseLine(unittest.TestCase):
    def test_data_temp(self):
        self.assertEqual(parse_line("D,2,25,0,61,0,*5A"),
                         {"type": "data", "node": 2, "temp": 25.0, "hum": 61.0})
    def test_data_gas(self):
        self.assertEqual(parse_line("D,3,812,1,*51"),
                         {"type": "data", "node": 3, "gas": 812, "do": 1})
    def test_status(self):
        self.assertEqual(parse_line("S,2,ONLINE,*6E"),
                         {"type": "status", "node": 2, "online": True})
        self.assertEqual(parse_line("S,3,OFFLINE,*21"),
                         {"type": "status", "node": 3, "online": False})
    def test_alarm(self):
        self.assertEqual(parse_line("A,1,2,*42"),
                         {"type": "alarm", "on": True, "src": 2})
    def test_loss_and_threshold(self):
        self.assertEqual(parse_line("L,2,3,128,*5A"),
                         {"type": "loss", "node": 2, "lost": 3, "total": 128})
        self.assertEqual(parse_line("T,45,600,*63"),
                         {"type": "threshold", "temp": 45, "gas": 600})
    def test_bad_checksum_rejected(self):
        self.assertIsNone(parse_line("D,2,25,0,61,0,*FF"))
        self.assertIsNone(parse_line("D,2,25,0,61,0"))
        self.assertIsNone(parse_line("GARBAGE,*00"))

class TestBuildDownlink(unittest.TestCase):
    def test_set_threshold(self):
        self.assertEqual(build_downlink({"type": "setThreshold", "temp": 50, "gas": 700}),
                         b"SET,50,700,*70\r\n")
    def test_test_alarm(self):
        self.assertEqual(build_downlink({"type": "testAlarm", "on": True}),
                         b"TEST,1,*0B\r\n")
        self.assertEqual(build_downlink({"type": "testAlarm", "on": False}),
                         b"TEST,0,*0A\r\n")
    def test_set_time(self):
        import bridge
        from unittest.mock import patch
        fake = type("Tm", (), {"tm_year": 2026, "tm_mon": 9, "tm_mday": 8,
                               "tm_hour": 16, "tm_min": 30, "tm_sec": 0})()
        with patch.object(bridge.time, "localtime", return_value=fake):
            self.assertEqual(build_downlink({"type": "setTime"}),
                             b"TIME,26,9,8,16,30,0,*24\r\n")
    def test_unknown_rejected(self):
        self.assertIsNone(build_downlink({"type": "nonsense"}))

if __name__ == "__main__":
    unittest.main()
```

- [ ] **步骤 4：运行单元测试**

```bash
"C:\Users\orangeneko\Documents\HomeFireAlarmSystem\Python311\python.exe" -m unittest test_bridge -v
```

预期：全部 PASS（若 `S,3,OFFLINE` 的期望校验值不对，按实算值修正断言）。

- [ ] **步骤 5：桥冒烟测试（串口助手模拟主节点）**

临时用串口助手占住桥要用的 COM 口不可行（独占）——改为：先拔掉主节点 USB，用**两个虚拟串口**不可用时跳过本步，直接做任务 13 端到端。若手头有 USB 转串口线 x2 可对插模拟：

```bash
"C:\Users\orangeneko\Documents\HomeFireAlarmSystem\Python311\python.exe" bridge.py COM口
```

浏览器控制台执行 `new WebSocket("ws://localhost:8081").onmessage = e => console.log(e.data)`，另一端串口助手发 `D,2,25,0,61,0,*5A\r\n` → 浏览器收到 `{"type": "data", "node": 2, ...}`。反向：浏览器 `ws.send('{"type":"testAlarm","on":true}')` → 串口助手收到 `TEST,1,*0B`。

- [ ] **步骤 6：Commit**

```bash
git add bridge.py test_bridge.py && git commit -m "feat: Python串口桥与单元测试通过"
```

---

### 任务 11：网页上位机骨架（布局 / WS / 演示模式）

**文件：**
- 创建：`web/index.html`、`web/style.css`、`web/main.js`
- 下载：`web/three.min.js`（任务 12 用，提前就位）

- [ ] **步骤 1：本地化 three.js（演示现场可能无网，禁止 CDN 依赖）**

```bash
curl -L -o "C:\Users\orangeneko\Documents\HomeFireAlarmSystem\web\three.min.js" https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js
```

预期：文件约 600KB；`head -c 200 web/three.min.js` 能看到 JS 内容而非 404 页面。

- [ ] **步骤 2：index.html**

```html
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<title>家庭火灾监测 · 元素感知</title>
<link rel="stylesheet" href="style.css">
</head>
<body>
<header id="topbar">
  <div class="title">家庭火灾监测 · 元素感知</div>
  <div id="clock">----:--:-- --:--</div>
  <div id="link-info" class="offline">未连接 · 演示模式</div>
</header>
<main>
  <aside id="node-cards">
    <div class="node-card" id="card-master">
      <div class="node-name">主节点 · 协调器</div>
      <div class="node-state">离线</div>
    </div>
    <div class="node-card" id="card-temp">
      <div class="node-name">温湿度节点</div>
      <div class="node-data" id="card-temp-data">-- ℃ / -- %</div>
      <div class="node-state">离线</div>
    </div>
    <div class="node-card" id="card-gas">
      <div class="node-name">有害气体节点</div>
      <div class="node-data" id="card-gas-data">ADC --</div>
      <div class="node-state">离线</div>
    </div>
  </aside>
  <section id="stage3d"><div id="demo-badge" hidden>演示模式</div></section>
  <aside id="data-panel">
    <div class="metric" id="m-temp"><span class="elem pyro">火</span>
      <span class="val" id="v-temp">--</span>℃<canvas id="c-temp" width="200" height="40"></canvas></div>
    <div class="metric" id="m-hum"><span class="elem hydro">水</span>
      <span class="val" id="v-hum">--</span>%<canvas id="c-hum" width="200" height="40"></canvas></div>
    <div class="metric" id="m-gas"><span class="elem anemo">风</span>
      <span class="val" id="v-gas">--</span><canvas id="c-gas" width="200" height="40"></canvas></div>
    <div id="loss-info">丢包率 --</div>
  </aside>
</main>
<footer id="console">
  <div id="alarm-banner" hidden>⚠ 火灾警报 ⚠</div>
  <label>温度阈值 <input id="th-temp" type="number" value="45">℃</label>
  <label>气体阈值 <input id="th-gas" type="number" value="600"></label>
  <button id="btn-thresh">下发阈值</button>
  <button id="btn-test">模拟报警</button>
  <button id="btn-test-off" hidden>解除模拟</button>
</footer>
<div id="burst-overlay"></div>
<script src="three.min.js"></script>
<script src="main.js"></script>
</body>
</html>
```

- [ ] **步骤 3：style.css（原神视觉规范落地）**

```css
:root {
  --bg: #0b1c3f; --panel: #122448; --gold: #d3bc8e; --ink: #ece5d8;
  --pyro: #ef7938; --hydro: #4cc2f1; --anemo: #74c2a8; --alarm: #d5544f;
}
* { margin: 0; padding: 0; box-sizing: border-box; }
body {
  background: radial-gradient(ellipse at 50% 30%, #12264d 0%, var(--bg) 65%);
  color: var(--ink); height: 100vh; display: flex; flex-direction: column;
  font-family: "Noto Serif SC", "Source Han Serif SC", serif; overflow: hidden;
}
#topbar { display: flex; justify-content: space-between; align-items: center;
  padding: 10px 24px; border-bottom: 1px solid var(--gold); }
#topbar .title { color: var(--gold); font-size: 20px; letter-spacing: 4px; }
#link-info.online { color: #9fd6a8; } #link-info.offline { color: #888; }
main { flex: 1; display: grid; grid-template-columns: 230px 1fr 260px; gap: 12px; padding: 12px; min-height: 0; }
.node-card, .metric {
  background: linear-gradient(160deg, var(--panel), #0d1c3a);
  border: 1px solid var(--gold); clip-path: polygon(0 8px, 8px 0, 100% 0, 100% calc(100% - 8px), calc(100% - 8px) 100%, 0 100%);
  padding: 12px; margin-bottom: 10px;
}
.node-card.online { box-shadow: 0 0 12px rgba(211,188,142,.45); }
.node-card.alarm  { border-color: var(--alarm); animation: blink 0.6s infinite alternate; }
.node-state { color: #888; font-size: 12px; } .node-card.online .node-state { color: var(--gold); }
#stage3d { position: relative; } #stage3d canvas { width: 100%; height: 100%; display: block; }
#demo-badge { position: absolute; right: 8px; top: 8px; color: #888; font-size: 12px; border: 1px solid #555; padding: 2px 8px; }
.elem { display: inline-block; width: 26px; height: 26px; line-height: 26px; text-align: center;
  border-radius: 50%; color: #fff; margin-right: 6px; }
.pyro { background: var(--pyro); } .hydro { background: var(--hydro); } .anemo { background: var(--anemo); }
.metric .val { font-size: 26px; color: var(--gold); }
#console { display: flex; gap: 16px; align-items: center; padding: 10px 24px;
  border-top: 1px solid var(--gold); }
#console button {
  background: transparent; border: 1px solid var(--gold); color: var(--gold);
  padding: 6px 18px; cursor: pointer; font-family: inherit;
}
#console button:hover { background: rgba(211,188,142,.15); }
#console input { width: 64px; background: var(--panel); color: var(--ink); border: 1px solid #445; padding: 4px; }
#alarm-banner { color: var(--alarm); border: 1px solid var(--alarm); padding: 4px 14px;
  animation: blink 0.5s infinite alternate; }
#burst-overlay { position: fixed; inset: 0; pointer-events: none; opacity: 0;
  background: radial-gradient(circle, rgba(255,200,120,.55), rgba(116,194,168,.25) 55%, transparent 75%); }
@keyframes blink { from { opacity: 1; } to { opacity: .35; } }
```

- [ ] **步骤 4：main.js（本任务实现数据层；3D 容器留空由任务 12 填充）**

```javascript
/* web/main.js */
const state = {
  nodes: {
    2: { online: false, temp: null, hum: null },
    3: { online: false, gas: null, do: null },
  },
  alarm: { on: false, src: 0 },
  loss: {},                    // node -> {lost, total}
  hist: { temp: [], hum: [], gas: [] },
  demo: false,
};

const $ = id => document.getElementById(id);
const clockEl = $("clock"), linkEl = $("link-info");

/* ---------- WebSocket ---------- */
let ws = null, wsTimer = null;
function connectWS() {
  try { ws = new WebSocket("ws://localhost:8081"); } catch (e) { enterDemo(); return; }
  ws.onopen = () => {
    clearInterval(wsTimer);
    linkEl.textContent = "已连接"; linkEl.className = "online";
    if (state.demo) exitDemo();
    ws.send(JSON.stringify({ type: "setTime" }));   // 连上即对时
  };
  ws.onmessage = e => handleMsg(JSON.parse(e.data));
  ws.onclose = () => { linkEl.textContent = "未连接 · 演示模式"; linkEl.className = "offline";
    wsTimer = setTimeout(connectWS, 3000); };
}
function sendCmd(obj) {
  if (ws && ws.readyState === 1) ws.send(JSON.stringify(obj));
  else if (state.demo) applyDemoCmd(obj);           // 演示模式下本地生效
}

/* ---------- 消息处理 ---------- */
function handleMsg(m) {
  if (m.type === "data" && m.node === 2) { state.nodes[2] = { online: true, temp: m.temp, hum: m.hum };
    pushHist("temp", m.temp); pushHist("hum", m.hum); }
  if (m.type === "data" && m.node === 3) { state.nodes[3] = { online: true, gas: m.gas, do: m.do };
    pushHist("gas", m.gas); }
  if (m.type === "status") { state.nodes[m.node].online = m.online; }
  if (m.type === "alarm") state.alarm = { on: m.on, src: m.src };
  if (m.type === "loss") state.loss[m.node] = m;
  if (m.type === "threshold") { $("th-temp").value = m.temp; $("th-gas").value = m.gas; }
  render();
}

/* ---------- 演示模式 ---------- */
let demoTimer = null;
function enterDemo() { state.demo = true; $("demo-badge").hidden = false;
  demoTimer = setInterval(demoTick, 1000); demoTick(); render(); }
function exitDemo() { state.demo = false; $("demo-badge").hidden = true;
  clearInterval(demoTimer); }
function demoTick() {
  const t = 25 + Math.sin(Date.now() / 9000) * 2 + Math.random() * 0.4;
  const h = 60 + Math.sin(Date.now() / 7000) * 4;
  let g = 420 + Math.sin(Date.now() / 5000) * 40;
  if (state.demoAlarmAt && Date.now() > state.demoAlarmAt) g = 900 + Math.random() * 200; // 演示报警爬升
  handleMsg({ type: "data", node: 2, temp: +t.toFixed(1), hum: +h.toFixed(1) });
  handleMsg({ type: "data", node: 3, gas: Math.round(g), do: g > 600 ? 1 : 0 });
  handleMsg({ type: "alarm", on: g > 600, src: 2 });
}
function applyDemoCmd(obj) {
  if (obj.type === "testAlarm") state.demoAlarmAt = obj.on ? Date.now() : 0;
  if (obj.type === "setThreshold") handleMsg({ type: "threshold", temp: obj.temp, gas: obj.gas });
}

/* ---------- 渲染 ---------- */
function pushHist(k, v) { const a = state.hist[k]; a.push(v); if (a.length > 60) a.shift(); }
function drawCurve(canvas, arr, color) {
  const ctx = canvas.getContext("2d"); ctx.clearRect(0, 0, canvas.width, canvas.height);
  if (arr.length < 2) return;
  const min = Math.min(...arr), max = Math.max(...arr), span = (max - min) || 1;
  ctx.strokeStyle = color; ctx.lineWidth = 1.5; ctx.beginPath();
  arr.forEach((v, i) => {
    const x = i / (arr.length - 1) * canvas.width;
    const y = canvas.height - 4 - (v - min) / span * (canvas.height - 8);
    i ? ctx.lineTo(x, y) : ctx.moveTo(x, y);
  });
  ctx.stroke();
}
function render() {
  const n2 = state.nodes[2], n3 = state.nodes[3];
  $("card-temp").classList.toggle("online", n2.online);
  $("card-temp-data").textContent = n2.online ? `${n2.temp} ℃ / ${n2.hum} %` : "-- ℃ / -- %";
  $("card-gas").classList.toggle("online", n3.online);
  $("card-gas-data").textContent = n3.online ? `ADC ${n3.gas}` : "ADC --";
  $("v-temp").textContent = n2.temp ?? "--";
  $("v-hum").textContent = n2.hum ?? "--";
  $("v-gas").textContent = n3.gas ?? "--";
  drawCurve($("c-temp"), state.hist.temp, getComputedStyle(document.body).getPropertyValue("--pyro"));
  drawCurve($("c-hum"), state.hist.hum, getComputedStyle(document.body).getPropertyValue("--hydro"));
  drawCurve($("c-gas"), state.hist.gas, getComputedStyle(document.body).getPropertyValue("--anemo"));
  const l2 = state.loss[2];
  $("loss-info").textContent = l2 ? `节点2丢包 ${l2.lost}/${l2.total}` : "丢包率 --";
  $("alarm-banner").hidden = !state.alarm.on;
  $("btn-test-off").hidden = !state.alarm.on;
  document.querySelectorAll(".node-card").forEach(c => c.classList.remove("alarm"));
  if (state.alarm.on) { $("card-temp").classList.add("alarm"); $("card-gas").classList.add("alarm"); }
  onAlarmFx(state.alarm.on);          // 任务 12 实现；本任务先提供空函数
}
function onAlarmFx() {}               // 任务 12 覆盖

/* ---------- 控制台 ---------- */
$("btn-thresh").onclick = () => sendCmd({ type: "setThreshold",
  temp: +$("th-temp").value, gas: +$("th-gas").value });
$("btn-test").onclick = () => sendCmd({ type: "testAlarm", on: true });
$("btn-test-off").onclick = () => sendCmd({ type: "testAlarm", on: false });

/* ---------- 时钟 ---------- */
setInterval(() => {
  const d = new Date(), p = n => String(n).padStart(2, "0");
  clockEl.textContent = `${d.getFullYear()}:${p(d.getMonth() + 1)}:${p(d.getDate())} ${p(d.getHours())}:${p(d.getMinutes())}`;
}, 1000);

connectWS();
setTimeout(() => { if (!ws || ws.readyState !== 1) enterDemo(); }, 2000);  // 2s 连不上进演示
```

- [ ] **步骤 5：浏览器验证（无硬件）**

启动 `Python311\python.exe bridge.py`（它会托管 web/，即使没有串口 COM 参数会打印提示退出——无硬件时用任意方式开静态服务，如 `Python311\python.exe -m http.server 8080 -d web`）。
**判定**：① 打开 http://localhost:8080，2 秒后右上角"演示模式"，数据每秒刷新、三条曲线滚动；② 点"模拟报警"→ 数据爬升、横幅出现、卡片爆闪（3D 区暂为空白，任务 12 填充）；③ 解除恢复。

- [ ] **步骤 6：Commit**

```bash
git add web/ && git commit -m "feat: 上位机页面骨架WS与演示模式"
```

---

### 任务 12：Three.js 元素核心与扩散反应特效

**文件：**
- 修改：`web/main.js`（追加 3D 模块并覆盖 `onAlarmFx`）

- [ ] **步骤 1：追加 3D 场景模块到 main.js 末尾**

```javascript
/* ================= 3D：元素核心 ================= */
let scene, camera, renderer, coreGroup;
const particles = {};                 // name -> {points, speed, radius, base}
const P_CONF = [
  { key: "temp", name: "pyro",  color: 0xef7938, radius: 2.0, count: 400, dir: 1 },
  { key: "hum",  name: "hydro", color: 0x4cc2f1, radius: 2.6, count: 350, dir: -1 },
  { key: "gas",  name: "anemo", color: 0x74c2a8, radius: 3.2, count: 300, dir: 1 },
];
function makeParticles(conf) {
  const geo = new THREE.BufferGeometry();
  const pos = new Float32Array(conf.count * 3);
  for (let i = 0; i < conf.count; i++) {
    const a = Math.random() * Math.PI * 2;
    const r = conf.radius * (0.9 + Math.random() * 0.2);
    pos[i * 3] = Math.cos(a) * r;
    pos[i * 3 + 1] = (Math.random() - 0.5) * 0.8;
    pos[i * 3 + 2] = Math.sin(a) * r;
  }
  geo.setAttribute("position", new THREE.BufferAttribute(pos, 3));
  const mat = new THREE.PointsMaterial({
    color: conf.color, size: 0.07, transparent: true, opacity: 0.75,
    blending: THREE.AdditiveBlending, depthWrite: false,
  });
  const points = new THREE.Points(geo, mat);
  points.userData = { angle: 0, dir: conf.dir };
  return points;
}
function init3D() {
  const box = document.getElementById("stage3d");
  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera(50, box.clientWidth / box.clientHeight, 0.1, 100);
  camera.position.set(0, 1.6, 7);
  renderer = new THREE.WebGLRenderer({ antialias: true, alpha: true });
  renderer.setSize(box.clientWidth, box.clientHeight);
  renderer.setPixelRatio(window.devicePixelRatio);
  box.appendChild(renderer.domElement);
  // 元素核心：金色线框八面体 + 深蓝内芯
  coreGroup = new THREE.Group();
  const wire = new THREE.LineSegments(
    new THREE.EdgesGeometry(new THREE.OctahedronGeometry(1.15)),
    new THREE.LineBasicMaterial({ color: 0xd3bc8e }));
  const inner = new THREE.Mesh(
    new THREE.OctahedronGeometry(0.95),
    new THREE.MeshBasicMaterial({ color: 0x1a2b4d, transparent: true, opacity: 0.9 }));
  coreGroup.add(wire, inner);
  coreGroup.position.y = 0.2;
  scene.add(coreGroup);
  P_CONF.forEach(c => { const p = makeParticles(c); particles[c.name] = p; scene.add(p); });
  // 鼠标拖拽旋转
  let drag = null;
  box.addEventListener("pointerdown", e => drag = e.clientX);
  window.addEventListener("pointermove", e => {
    if (drag === null) return;
    coreGroup.rotation.y += (e.clientX - drag) * 0.01; drag = e.clientX;
  });
  window.addEventListener("pointerup", () => drag = null);
  window.addEventListener("resize", () => {
    camera.aspect = box.clientWidth / box.clientHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(box.clientWidth, box.clientHeight);
  });
  animate();
}
function animate() {
  requestAnimationFrame(animate);
  coreGroup.rotation.y += 0.004;
  coreGroup.rotation.x = Math.sin(Date.now() / 4000) * 0.15;
  // 数据驱动粒子：温度→火速度、湿度→水亮度、气体→风速度
  const n2 = state.nodes[2], n3 = state.nodes[3];
  const tBoost = n2.temp ? (n2.temp - 20) / 30 : 0;          // 20~50℃ → 0~1
  const hAlpha = n2.hum ? 0.35 + Math.min(n2.hum, 100) / 200 : 0.35;
  const gBoost = n3.gas ? Math.min(n3.gas, 1200) / 1200 : 0;
  spin(particles.pyro, 0.006 + tBoost * 0.03);
  spin(particles.hydro, 0.005);
  spin(particles.anemo, 0.004 + gBoost * 0.04);
  particles.hydro.material.opacity = hAlpha;
  // 报警扩散：火粒子膨胀脉冲
  if (state.alarm.on) {
    const s = 1 + 0.25 * Math.sin(Date.now() / 120);
    particles.pyro.scale.set(s, s, s);
  } else particles.pyro.scale.set(1, 1, 1);
  renderer.render(scene, camera);
}
function spin(p, step) {
  const pos = p.geometry.attributes.position;
  const { dir } = p.userData;
  for (let i = 0; i < pos.count; i++) {
    const x = pos.getX(i), z = pos.getZ(i);
    pos.setX(i, x * Math.cos(step * dir) - z * Math.sin(step * dir));
    pos.setZ(i, x * Math.sin(step * dir) + z * Math.cos(step * dir));
  }
  pos.needsUpdate = true;
}
function burstFx(on) {
  const ov = document.getElementById("burst-overlay");
  if (on) {
    ov.style.transition = "none"; ov.style.opacity = 1;      // 爆发闪
    requestAnimationFrame(() => {
      ov.style.transition = "opacity .9s ease-out"; ov.style.opacity = 0;
    });
  }
}
onAlarmFx = burstFx;                   // 覆盖任务 11 的空实现
init3D();
```

- [ ] **步骤 2：浏览器验证（演示模式）**

刷新页面。**判定**：① 3D 区出现金色线框八面体 + 火/水/风三色粒子环，鼠标可拖拽旋转；② 温度波动时火粒子转速可感变化，哈气演示（演示模式不会，此条留硬件联调）；③ 点"模拟报警"→ 全屏暖色冲击闪一下、火粒子周期膨胀、水粒子变亮；解除后恢复；④ F12 控制台无红色报错。

- [ ] **步骤 3：Commit**

```bash
git add web/main.js && git commit -m "feat: 元素核心3D粒子与扩散反应报警特效"
```

---

### 任务 13：端到端联调与课程设计文档

**文件：**
- 创建：`README.md`
- 修改：发现的问题回到对应任务修复

- [ ] **步骤 1：全链路场景清单（逐项打勾）**

前置：三节点烧录最终版、MQ-2 预热 ≥5 分钟、主节点 USB 接 PC。

1. `Python311\python.exe bridge.py COM口` 启动 → 网页自动连接、自动对时（三块 OLED 与网页时钟一致）；
2. 网页实时显示温湿度/气体/节点状态/丢包率，曲线滚动；
3. 网页"下发阈值"改温度阈值 30 → 串口可回 `T,30,…`、哈气/热风使温度超 30 → 三端联动报警（LED + OLED 火灾警报 + 网页扩散特效）→ 回落自动解除；
4. 网页"模拟报警" → 真实三端联动；"解除"恢复；
5. 拔任一终端电源 → 网页卡片 10 秒后变灰"离线"，OLED 显示`离线`；上电恢复；
6. 拔 USB（断 WS）→ 网页进演示模式角标提示；重连后自动恢复真实数据。

- [ ] **步骤 2：编写 README.md**

内容清单（逐节写全，不留 TODO）：
1. 项目简介 + 系统架构图（复用规格第 2 节）；
2. 硬件清单与接线表（复用规格第 3 节）；
3. 烧录步骤：IAR 打开 `HomeFireAlarmSystem.eww` → 选工程 → Download and Debug，三块板分别烧 Master/TempNode/GasNode；
4. 启动步骤：MQ-2 预热提醒（首次 24-48h 最佳、演示前 ≥5 分钟）→ `Python311\python.exe bridge.py COM口` → Edge/Chrome 打开 http://localhost:8080；
5. 演示剧本（答辩用）：正常监测 → 改阈值触发温度报警 → 模拟报警 → 解除 → 拔节点看离线检测 → 恢复；
6. 常见问题：串口占用（关掉串口助手）、网页连不上（防火墙/端口）、RF 收不到（对齐信道 FREQCTRL）、字模乱码（对照任务 3 步骤 4 排查）。

- [ ] **步骤 3：最终验收对照任务书**

对照 `docs/MinerU_markdown_24081049-无线传感网技术课程设计任务书*.md` 逐条核对：协调器 OLED 显示 ✓、汉字 ✓、终端 OLED 显示 ✓、超限报警 ✓、终端与协调器同时报警（LED 替代蜂鸣器，已与用户确认）✓、无线传输 ✓、判别逻辑 ✓。

- [ ] **步骤 4：Commit**

```bash
git add README.md docs/ && git commit -m "docs: 端到端联调通过并补充README"
```


