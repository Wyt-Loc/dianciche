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
*  函数名称：void GPIO_KEY_Init(void)
*  功能说明：GPIO初始化函数
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
void GPIO_KEY_Init(void)
{
    P7M1 = 0;   P7M0 = 0;   //设置为准双向口
	
}

/*************************************************************************
*  函数名称：unsigned char KEY_Read(KEYn_e KEYno)
*  功能说明：读取按键状态
*  参数说明：KEYn_e KEYno按键编号
*  函数返回：按键状态，0/1
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
unsigned char KEY_Read(KEYn_e KEYno)
{
    switch(KEYno)
    {
      case KEY0:
        return P70;				//母板上按键0
      break;

      case KEY1:
        return P71;				//母板上按键1
      break;

      case KEY2:
        return P72;				//母板上按键2
      break;
			
			case KEY3:
				if(P73)
					return 1;				//母板上按键3
				else
				{
					while(P73==0);  //等待松开按键
					return 0;	
				}
      break;

      case DSW0:
        return P32;				//母板上拨码开关0
      break;

      case DSW1:
        return P33;				//母板上拨码开关1
      break;
      default:
        return 0XFF;
    }
    return 0;
}


/*************************************************************************
*  函数名称：unsigned char KEY_Read_All(void)
*  功能说明：读取全部按键状态
*  参数说明：无
*  函数返回：按键组合状态，0--7八种状态
*  修改时间：2020年3月10日
*  备    注：读取三个按键状态，方便组合键使用
*************************************************************************/
unsigned char KEY_Read_All(void)
{
   unsigned char tm=0;

   tm = P70 | (P7^1 << 1) | (P7^2 << 2);//读取各个按键状态并编码	
   if(tm==0x07)
	{
	   return 0;
	}
   return  (~tm)&0X07;
}


/*************************************************************************
*  函数名称：void Test_GPIO_KEY(void)
*  功能说明：测试程序
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：按下KEY0/1/2任意键 LED全亮
*************************************************************************/
void Test_GPIO_KEY(void)
 {
	unsigned char k=0xFF;
	GPIO_LED_Init();
	GPIO_KEY_Init();
 	while(1)
 	{
 		k= KEY_Read(KEY0)& KEY_Read(KEY1)& KEY_Read(KEY2)& KEY_Read(KEY3);

 		if(k==0) LED_Ctrl(LEDALL, ON); //按下KEY0/1/2任意键 LED全亮
 		else     LED_Ctrl(LEDALL, OFF);//松开KEY0/1/2任意键 LED全灭

 		delayms(100);                //延时等待
 	}
 }


/*************************************************************************
*  函数名称：void Test_ComKEY_Tft(void)
*  功能说明：测试组合按键并在彩屏显示
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：按键状态彩屏显示
*************************************************************************/
void Test_ComKEY_Tft(void)
 {
	unsigned char k=0xFF;
  OLED_Init();                                              //OLED初始化
	OLED_CLS();                                               //清屏		
	OLED_P14x16Str(0,0,(unsigned char*)"北京龙邱智能科技");		//字符串显示
	OLED_P6x8Str(0,2,"Long Qiu i.s.t.");	                  	//字符串显示
	delayms(1000);                                            //延时等待
	OLED_CLS();                                               //清屏		
	OLED_P6x8Str(0,1,"KEY Pressed:  ");	                    	//字符串显示
	GPIO_KEY_Init();
 	while(1)
 	{
 		k= KEY_Read_All();
 		switch(k)
 		{
 		  case NOKEYDOWN:
 			 //OLED_P6x8Str(35,3,"NO key!  ");		//字符串显示
 		  break;
 		  case KEY0DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY0!    ");		  //字符串显示
 		  break;
 		  case KEY1DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY1!    ");		  //字符串显示
 		  break;
 		  case KEY2DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY2!    ");		  //字符串显示
 		  break;
 		  case KEY01DOWN:
 			 OLED_P6x8Str(35,3,"KEY0&1!  ");		  //字符串显示
 		  break;
 		  case KEY02DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY0&2!  ");		  //字符串显示
 		  break;
 		  case KEY12DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY1&2!  ");		  //字符串显示
 		  break;
 		  case KEY012DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY0&1&2!");	  	//字符串显示
 		  break;
 		  default:
 		  break;
 		 }
 		LED_Ctrl(LED0,RVS);                     //四个LED同时闪烁
 		delayms(100);                           //延时等待
 	}
 }



