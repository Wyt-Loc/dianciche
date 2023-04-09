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
#ifndef __LQ_LED_H_
#define __LQ_LED_H_

#include "include.h"

//定义模块号
typedef enum
{
  LED0=0,  //核心板上LED0
  LED1=1,  //核心板上LED1
  LED2=2,  //母板上LED0
  LED3=3,  //母板上LED1
  LEDALL=4
} LEDn_e;

typedef enum
{
  ON=0,  //亮
  OFF=1, //灭
  RVS=2, //反转
}LEDs_e;

//定义的管脚要对应实际按键
#define LED0p      P42   //核心板上LED0 翠绿
#define LED1p      P42   //核心板上LED1 蓝灯
#define LED2p      P22   //母板上LED0
#define LED3p      P23   //母板上LED1
#define beep       P34    

/*********************** UART功能函数 **************************/
//初始化
void GPIO_LED_Init(void);
void LED_Ctrl(LEDn_e LEDno, LEDs_e sta);
void Test_GPIO_LED(void);
void delayms(u16 nms);
void Led_Flash(u16 time);
#endif
