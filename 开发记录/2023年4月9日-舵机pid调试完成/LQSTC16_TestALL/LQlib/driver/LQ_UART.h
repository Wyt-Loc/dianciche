/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
 ��ƽ    ̨�������������ܿƼ�CH32V103R8T6���İ�
 ����    д��chiusir
 ��E-mail  ��chiusir@163.com
 ������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
 �������¡�2020��10��28��
 �������Ϣ�ο����е�ַ��
 ����    վ��http://www.lqist.cn
 ���Ա����̡�http://longqiu.taobao.com
 ------------------------------------------------
 ��IDE��CH32V103R8T6:MounRiver Studio�����ϰ汾
 ��Target �� CH32V103R8T6
 ��SYS PLL�� 80MHz
=================================================================
����������Ƶ��ַ��https://space.bilibili.com/95313236
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
