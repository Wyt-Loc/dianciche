/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技自平衡摩托车
【编    写】chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年4月10日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】Keil5.2及以上版本
【Target 】 STC16F40K
【SYS PLL】 36MHz
------------------------------------------------

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"


/*************************************************************************
*  函数名称：void LED_Init(void)
*  功能说明：GPIO初始化函数 LED灯所用PB10、PA3初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
void GPIO_LED_Init(void)
{
    P2M1 &= 0xFE;
    P2M1 |= 0x00;
    P2M0 &= 0xFE;
		P2M0 |= 0x01;   //设置为推挽输出
	
}

/*************************************************************************
*  函数名称：void LED_Ctrl(LEDn_e LEDno, LEDs_e sta)
*  功能说明：LED控制
*  参数说明：LEDn_e LEDno编号,LEDs_e sta状态亮/灭/翻转
*  函数返回：按键状态，0/1
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
void LED_Ctrl(LEDn_e LEDno, LEDs_e sta)
{
    switch(LEDno)
    {
    case LED0:
      if(sta==ON)        LED0p=0;
      else if(sta==OFF)  LED0p=1;
      else if(sta==RVS) (LED0p)?(LED0p=0):(LED0p=1);
    break;

    case LED1:
      if(sta==ON)        LED1p=0;
      else if(sta==OFF)  LED1p=1;
      else if(sta==RVS) (LED1p)?(LED1p=0):(LED1p=1);
    break;

    case LED2:
      if(sta==ON)        LED2p=0;
      else if(sta==OFF)  LED2p=1;
      else if(sta==RVS) (LED2p)?(LED2p=0):(LED2p=1);
    break;

    case LED3:
      if(sta==ON)        LED3p=0;
      else if(sta==OFF)  LED3p=1;
      else if(sta==RVS) (LED3p)?(LED3p=0):(LED3p=1);
    break;
    case LEDALL:
      if(sta==ON)
      {
    	  LED0p=0;
    	  LED1p=0;
    	  LED2p=0;
				LED3p=0;
      }
      else if(sta==OFF)
      {
    	  LED0p=1;
    	  LED1p=1;
    	  LED2p=1;
				LED3p=1;
      }
      else if(sta==RVS)
      {
    	  (LED0p)?(LED0p=0):(LED0p=1);
    	  (LED1p)?(LED1p=0):(LED1p=1);
    	  (LED2p)?(LED2p=0):(LED2p=1);
    	  (LED3p)?(LED3p=0):(LED3p=1);
      }
    break;
    default:
    break;
    }
}
/**************************************************************************
函数功能：LED闪烁
入口参数：闪烁频率 
返回  值：无
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
	  if(0==time) LED0p=0;
	  else if(++temp>time)	LED0p=~LED0p,temp=0;
}
/*************************************************************************
*  函数名称：void Test_GPIO_LED(void)
*  功能说明：测试程序
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：核心板上的LED灯闪烁--四个LED同时闪烁
*************************************************************************/
void Test_GPIO_LED(void)
 {
	GPIO_LED_Init();
 	while(1)
 	{
 		LED_Ctrl(LEDALL,RVS);        //LED同时闪烁
 		delayms(200);                //延时等待
 	}
 }
