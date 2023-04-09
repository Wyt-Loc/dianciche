/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
 【平    台】北京龙邱智能科技CH32V103R8T6核心板
 【编    写】chiusir
 【E-mail  】chiusir@163.com
 【软件版本】V1.1 版权所有，单位使用请先联系授权
 【最后更新】2020年10月28日
 【相关信息参考下列地址】
 【网    站】http://www.lqist.cn
 【淘宝店铺】http://longqiu.taobao.com
 ------------------------------------------------
 【IDE】CH32V103R8T6:MounRiver Studio及以上版本
 【Target 】 CH32V103R8T6
 【SYS PLL】 80MHz
=================================================================
程序配套视频地址：https://space.bilibili.com/95313236
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_UART_BT_H_
#define __LQ_UART_BT_H_

#include "include.h"

void UART1_config(u16 tmr);
void UART1_PutChar(char ch);
void UART1_PutStr(char *str);
char UART1_GetChar(void );

void UART4_config(u16 tmr);
void UART4_PutChar(char ch);
void UART4_PutStr(char *str);
char UART4_GetChar(void );

#endif
