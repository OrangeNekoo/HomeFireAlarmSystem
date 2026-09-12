/* Master/csv.c — 串口 CSV 打包/解析。ASCII 数字手写转换，不用 sprintf（8051 资源紧张） */
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
    char b[20], n[5]; u8 i = 0, k, j;
    strcpy(b, "D,3,"); i = 4;
    k = u16_to_str(adc, n);
    for(j = 0; j < k; j++) b[i++] = n[j];
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
void csv_send_easter(u8 on)
{
    char b[4];
    if(on) strcpy(b, "E,1");
    else strcpy(b, "E,0");
    csv_send_body(b);
}
void csv_send_loss(u8 node, u16 lost, u16 total)
{
    char b[24], n[6]; u8 i = 0, k, j;
    b[i++] = 'L'; b[i++] = ','; b[i++] = '0' + node; b[i++] = ',';
    k = u16_to_str(lost, n);  for(j = 0; j < k; j++) b[i++] = n[j];
    b[i++] = ',';
    k = u16_to_str(total, n); for(j = 0; j < k; j++) b[i++] = n[j];
    b[i] = '\0';
    csv_send_body(b);
}
void csv_send_thresh(u16 t, u16 g)
{
    char b[20], n[6]; u8 i = 0, k, j;
    strcpy(b, "T,"); i = 2;
    k = u16_to_str(t, n); for(j = 0; j < k; j++) b[i++] = n[j];
    b[i++] = ',';
    k = u16_to_str(g, n); for(j = 0; j < k; j++) b[i++] = n[j];
    b[i] = '\0';
    csv_send_body(b);
}
/* —— 下行解析 ——
   游标约定：skip_to(s,n) 从行首跳过 n 个逗号，指向第 n+1 个字段首字符；
   parse_u16 从当前游标连续读数字并前移游标。SET/TIME 每个字段都从行首
   重新定位（skip_to(s, 字段序号)），与"从行首按逗号取第 n 个字段"意图一致 */
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
