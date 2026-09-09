/* Master/csv.h — 串口 CSV 消息打包（上行）+ 下行指令解析 */
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
/* 下行解析：uart_line 匹配 SET/TEST/TIME，成功返回 1（SET）/2（TEST）/3（TIME），
   未知行返回 0；无论结果内部均已 uart_line_consume */
u8   csv_handle_line(void);
#endif
