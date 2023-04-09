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
#ifndef __LQ_LED_H_
#define __LQ_LED_H_

#include "include.h"

//����ģ���
typedef enum
{
  LED0=0,  //���İ���LED0
  LED1=1,  //���İ���LED1
  LED2=2,  //ĸ����LED0
  LED3=3,  //ĸ����LED1
  LEDALL=4
} LEDn_e;

typedef enum
{
  ON=0,  //��
  OFF=1, //��
  RVS=2, //��ת
}LEDs_e;

//����Ĺܽ�Ҫ��Ӧʵ�ʰ���
#define LED0p      P42   //���İ���LED0 ����
#define LED1p      P42   //���İ���LED1 ����
#define LED2p      P22   //ĸ����LED0
#define LED3p      P23   //ĸ����LED1
#define beep       P34    

/*********************** UART���ܺ��� **************************/
//��ʼ��
void GPIO_LED_Init(void);
void LED_Ctrl(LEDn_e LEDno, LEDs_e sta);
void Test_GPIO_LED(void);
void delayms(u16 nms);
void Led_Flash(u16 time);
#endif
