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

#define EX2 0x10
#define EX3 0x20
#define EX4 0x40

u8  INT0_cnt, INT1_cnt; 					//测试用的计数变量
u8  INT2_cnt, INT3_cnt, INT4_cnt; //测试用的计数变量

/********************* INT0中断函数 *************************/
void INT0_int (void) interrupt 0  //进中断时已经清除标志
{
    INT0_cnt++;										//中断+1
}

/********************* INT1中断函数 *************************/
void INT1_int (void) interrupt 2      //进中断时已经清除标志
{
    INT1_cnt++; //中断+1
}

/********************* INT2中断函数 *************************/
void INT2_int (void) interrupt 10 //进中断时已经清除标志
{//IMU用
    INT2_cnt++; 									//中断+1
	
}

/********************* INT3中断函数 *************************/
void INT3_int (void) interrupt 11 //进中断时已经清除标志
{//干簧管用
  INT3_cnt++; 									//中断+1
	LED_Ctrl(LED1, RVS);   				//LED闪烁;
}

/********************* INT4中断函数 *************************/
void INT4_int (void) interrupt 16 //进中断时已经清除标志
{
    INT4_cnt++; 									//中断+1
}
/*************************************************************************
*  函数名称：void LED_Init(void)
*  功能说明：GPIO初始化函数 LED灯所用PB10、PA3初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
void GPIO_EXIT_Init(void)
{                                
    IE1 = 0;                      //外中断1标志位
    IE0 = 0;                      //外中断0标志位    
    EX0 = 0;                      //INT0 不使能
	  EX1 = 0;                      //INT1 不使能
    IT0 = 1;                      //INT0 下降沿中断       
//  IT0 = 0;                      //INT0 上升,下降沿中断
    IT1 = 1;                      //INT1 下降沿中断 

    //INT2, INT3, INT4 ，供需要时参考使用
    //INTCLKO |= EX2;             //使能 INT2 下降沿中断 IMU模块
    INTCLKO |= EX3; 	            //使能 INT3 下降沿中断 干簧管 
    //INTCLKO |= EX4;             //使能 INT4 下降沿中断
                                  
    EA = 1;     			            //允许总中断
}


/*************************************************************************
*  函数名称：void Test_GPIO_EXIT_Init(void)
*  功能说明：测试程序
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：核心板上的LED灯闪烁
*************************************************************************/
void Test_GPIO_EXIT_Init(void)
{
	char txt[32];
	GPIO_LED_Init();				
	GPIO_EXIT_Init();
  OLED_CLS();   							//清屏	
 	while(1)
 	{
 		sprintf(txt,"INT3_cnt:%03d ",INT3_cnt);  //显示ADC11的值
		OLED_P8x16Str(0,4,(u8*)txt);      
 	}
 }
