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
    buf[3] ^= 0xFF;                              /* ÆÆ»µÐ£ÑéºÍ */
    if(frame_parse(buf, n, &s, &d2, &c, out) != 0) return 0;
    return 1;
}
