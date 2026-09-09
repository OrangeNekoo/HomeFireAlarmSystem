/* Common/font16.h — 字库接口 */
#ifndef FONT16_H
#define FONT16_H
extern const unsigned char F16x16[];   /* 17 个 16x16 汉字，每字 32 字节 */
extern const unsigned char F6x8[][6];  /* ASCII 6x8，起始于空格 0x20 */
extern const unsigned char F8X16[];    /* ASCII 8x16，起始于空格 0x20 */
/* 汉字索引（与 font matrix.txt 一致）：
   0温 1湿 2度 3有 4害 5气 6体 7正 8异 9常
   10火 11灾 12警 13报 14离 15线 16℃ */
#endif
