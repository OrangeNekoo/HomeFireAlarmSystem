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
