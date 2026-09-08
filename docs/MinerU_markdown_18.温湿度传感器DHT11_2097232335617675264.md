## 18. 温湿度传感器 DHT11

## 1. 实验目的

1) 通过实验掌握 CC2530 芯片 GPIO 的配置方法

2) 掌握温湿度传感器 DHT11 的使用

## 2. 实验设备

硬件：PC机一台、ZB2530（底板、核心板、仿真器、USB线）一套、DHT11一个软件：2000/XP/win7系统，IAR8.10集成开发环境、串口助手

## 3. 实验相关电路图

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/ef5ab6f7-e43f-4f32-8bfd-63d9fbb08c0f/8f905306b3ef5a79776e7973e3be02391996296dca57f244fc4c6e16e7c8abea.jpg)


注意：传感器模块上面从左到右是 VCC DATA GND，板子上面从左到右是 3V3 P07 GND 刚好是对应起来的。

DHT11 数字温湿度传感器是一款含有已校准数字信号输出的温湿度复合传感器。它应用专用的数字模块采集技术和温湿度传感技术，确保产品具有极高的可靠性与卓越的长期稳定性。

请按图中接线，自己购买的模块请按：3V3 接模块 VCC、GND 接模块的 GND、P07 接到模块数据输出脚。

技术工程师: QQ 2357481431

## 4. 实验相关寄存器

实验中用到了串口和 P0_7,前面已详细讲解了串口相关寄存器的配置与使用，此实验就不再重复讲串口配置了。DHT11 程序采用模块化编程思想，只需调用温度读取函数即可，相当方便，移植到其它平台也非常容易。重点讲 P0_7 的配置和 DHT11 使用 P0_7 的方法：

POSEL &= 0x7f; // 设置连接 DHT11 的 IO 口

#define DATA_PIN P0_7 //传感器引脚，在 DHT11.c 修改，不同 IO 修改此处即可

## 5. 源码分析

```c
/******************************************************************************************
文件名: main.c
描述: 将采集到的温湿度通过串口发送到串口调试助手上显示 9600 8N1
******************************************************************************************/
#include <ioCC2530.h>
#include <string.h>
#include "UART.H"
#include "DHT11.H"
```

```txt
/****************************************************************************************** 
```

```txt
程序入口函数
**************************/
```

```javascript
void main(void)
{
    uchar temp[3];
    uchar
    humidity[3];
    uchar
    strTemp[13]="Temperature:";
    uchar
    strHumidity[10]="Humidity:

    Delay_ms(1000); //让设备稳定 InitUart(); //串口初始化 while(1)
```

```txt
{
    memset(temp, 0, 3);
    memset(humidity, 0, 3);

    DHT11(); // 获取温湿度
    // 将温湿度的转换成字符串
    temp[0] = wendu_shi + 0x30;
    temp[1] = wendu_ge + 0x30;
    humidity[0] = shidu_shi + 0x30;
    humidity[1] = shidu_ge + 0x30;

    // 获得的温湿度通过串口输出到电脑显示
    UartSendString(strTemp, 12);
    UartSendString(temp, 2);
    UartSendString(" ", 3);
    UartSendString(strHumidity, 9);
    UartSendString(humidity, 2);
    UartSendString("\n", 1);

    Delay_ms(2000); // 延时，2S读取1次
}
```

## 6. 实验现象

![image](https://cdn-mineru.openxlab.org.cn/result/2026-09-08/ef5ab6f7-e43f-4f32-8bfd-63d9fbb08c0f/85ab683cfbfd1764bcf4918a48b688a1e76cbb49548ca386d07c0d74ef0e2dd8.jpg)



注意：左边是温度，手摸可以改变温度数据。右边是湿度，哈气可以改变数据。
