
#include "include.h"
#include "PID.h"

//PID结构体初始化
pid_param_t  pid_servor;



//定义全局变量  电机控制  占空比设置  初始设为 20
// 满占空比为10M/12.5k=800
//PWM2_CLOCK  10000000 //10M
//占空比 = duty / 800 
//电机电压 =  电池电压 * 占空比
volatile int16_t Duty_Motor = 260;						// 电机占空比初始化

//舵机占空比设置  占空比减 向右打角
//使用前设置舵机中值 测试 得 1675
volatile uint16_t Duty_Servor_Center = 1675;		// 舵机中值初始化


volatile short enc1;  // 左编码器值
volatile short enc2;	// 右编码器值


//线圈电感
int16_t ADC_Data[5];  //得到 线圈的感应电压

//车在路中间时 的电感值	 前中	 前左	 后左	 后右	 前右
static int16_t ADC_Center[5] = {2411, 1717, 2218, 2344, 1599};


/******************** 主函数 **************************/
void main(void)  
{	 	
	
  sysinit(); 																//系统初始化
	
	GPIO_LED_Init();													// LED 初始化
	
	//OLED_Init();															// OLED显示屏初始化
	
	//Timer34EncInit();													//编码器初始化
	
	MotorInit(MOTOR_FREQUENCY);    						// 电机初始化
	
	ServoInit(100);													  // 第一个初始化舵机 保证车在启动时方向是对的
	     																			  // 舵机初始化，频率为100Hz	舵机中值 1675 
	ServoCtrl(Duty_Servor_Center); 									// 设置舵机中值
	
  //UART1_config(1);												// 使用定时器2做串口4的波特率生成时钟
  OLED_Init(); 														// OLED显示屏初始化
  OLED_CLS();   													// 清屏	
  OLED_P6x8Str(0, 0, "WytZnc");						// 显示字符
	
	PidInit_wz(&pid_servor);						//舵机PID初始化
	
	ADC_Init();
 
	//Timer1_init();															//timer1初始化函数
	//EA = 1;
  delayms(1200);														// 等待整车全部上电完成
	MotorCtrl(0, Duty_Motor * 0.7);									// 必须要 duty乘个系数  设置速度才能用  不然为电压为0要不就疯转
	
  while (1)
  {
		
		Get_ADC_Data();
		Servor_Control(ADC_Data);
		//show_ADC_Data();

		/* 获取编码器值 */
    // enc1 =  Read_Encoder(1); 			        // 左电机 母板上编码器1，小车前进为负值
    // enc2 = -Read_Encoder(2); 			        // 右电机 母板上编码器2，小车后退为正值
  }
}

/***************************************************************
【函数名】void sysinit(void)  
【功  能】系统初始化 具体干啥看手册
【参数值】无
【返回值】无
****************************************************************/
void sysinit(void)  
{	
  WTST = 0; 
  P_SW2 |= 0x80;	
	IRCBAND=0;        //1：35M频段；0：24M频段
	//IRTRIM =0;
	//LIRTRIM=0;  
  CLKDIV = 0;				//24MHz主频，分频设置
  P_SW2 &= 0x7F;
  RSTCFG|=1<<4;           //P5.4复位管脚
  P0M1 =0x40; P0M0 = 0;   //设置为准双向口,P0.6  0.7为输入口，编码器用
	P0PU =0x40;             //P0.6  0.7使能内部4.1K上拉电阻
  P1M1 = 0;   P1M0 = 0;   //设置为准双向口
  P3M1 = 0;   P3M0 = 0;   //设置为准双向口
  P4M1 = 0;   P4M0 = 0;   //设置为准双向口
  P5M1 = 0;   P5M0 = 0;   //设置为准双向口
  P6M1 = 0;   P6M0 = 0;   //设置为准双向口
  P7M1 =0xFF; P7M0 = 0;   //设置为准双向口 
  P7PU =0xFF;	            //设置为准双向口,P7.0123为输入口接按键,P7.4567为输出口接电机驱动
  P40 = 0;		//打开LED电源 
	EA=1;
}

/***************************************************************
【函数名】 void Working(void)
【功  能】 提示系统在运行中
【参数值】 无	
【返回值】 无		运行在中断中的函数 不要加延时 影响主函数的运行 
****************************************************************/
void Working(void){

		P42 = 0;  //核心板绿灯 
		delayms(200); 
		P42 = 1;
		delayms(200);  
	//LED_Ctrl(LED1p,RVS);        //LED同时闪烁
}

/***************************************************************
【函数名】void timer1_int (void) interrupt 3 
【功  能】中断1服务函数
【参数值】无
【返回值】无
****************************************************************/
void timer1_int (void) interrupt 3
{
	  //Working();
}

/***************************************************************
【函数名】void Get_ADC_Data(void)
【功  能】得到ADC测得的感应电压
【参数值】无
【返回值】无
****************************************************************/
void Get_ADC_Data(void){
	
	  ADC_Data[0]=ADC_Read(0);    //前中  	    	p 1.0  0
    ADC_Data[1]=ADC_Read(1);    //前左    	 		p 1.1  1
    ADC_Data[2]=ADC_Read(10);   //后左    		 	p 0.2  10
    ADC_Data[3]=ADC_Read(9);    //后右 				 	p 0.1  9
    ADC_Data[4]=ADC_Read(11);   //前右 					p 0.3  11
//		ADC_Data[5]=ADC_Read(8);	  //					  p 0.0  8

}

/***************************************************************
【函数名】void show_ADC_Data(void)
【功  能】OLED显示感应电压
【参数值】无
【返回值】无
****************************************************************/
void show_ADC_Data(void){
	
	  char txt[10];
		OLED_CLS(); 
	
		sprintf(txt,"AD0:%04d ",ADC_Data[0]);  //显示ADC11的值
		OLED_P6x8Str(0,0,(u8*)txt);
	
		sprintf(txt,"AD1:%04d ",ADC_Data[1]);  //显示ADC11的值
		OLED_P6x8Str(0,1,(u8*)txt);
	
		sprintf(txt,"AD2:%04d ",ADC_Data[2]);  //显示ADC11的值
		OLED_P6x8Str(0,2,(u8*)txt);
	
		sprintf(txt,"AD3:%04d ",ADC_Data[3]);  //显示ADC11的值
		OLED_P6x8Str(0,3,(u8*)txt);
	
		sprintf(txt,"AD4:%04d ",ADC_Data[4]);  //显示ADC11的值
		OLED_P6x8Str(0,4,(u8*)txt);
	

	
		delayms(40);
	
}

//舵机中值为  1657
//车在路中间时 的电感值	 					前中	 前左	 后左	 后右	 前右
//static int16_t ADC_Center[5] = {2411, 1717, 2218, 2344, 1599};
int fx = 0;  //1左   2右
void Servor_Control(int16_t adc[5]){

	//第二种思路 根据前左 前右 两个传感器的信号进行判断  一开始测得前中传感器的值为2411
	//根据这个值去判断当前偏离了道路中心偏移了多远
	//应该是可以实现但是 没有加PID控制 舵机打角非常快 很难走直线
	int16_t error;
	short pwm_out;
	//偏差 = 前左 - 前右
	//error = dc[1] - adc[4]; //经过测试 发现不好 转向太早 用后边 2 个
	error = adc[2] - adc[3];

	pwm_out = (short)PidLocCtrl_wz(&pid_servor, error);

	if(pwm_out > 100){
		pwm_out = 100;
	}

	else if(pwm_out < -100){
		pwm_out = -100;
	}

	ServoCtrl(Duty_Servor_Center + pwm_out);
	
	//delayms(200);

	//第一种思路 根据4个传感器的偏移方向判断车身姿态 不好 很难调试 需要的调整的参数太多
	/*
	int16_t qzhong = 0, qzhong_flag = 0;
	int16_t qzuo   = 0, qzuo_flag 	= 0;
	int16_t hzuo   = 0,	hzuo_flag 	= 0;
	int16_t hyou   = 0,	hyou_flag 	= 0;
	int16_t qyou   = 0, qyou_flag		= 0;
	
	// 根据差值 判断车身当前的情况
	qzuo = adc[1] - ADC_Center[1];
	hzuo = adc[2] - ADC_Center[2];
	hyou = adc[3] - ADC_Center[3];
	qyou = adc[4] - ADC_Center[4];
	
	if(qzuo > 0) qzuo_flag = 2; else {qzuo_flag = 1; qzuo =- qzuo;}
	if(hzuo > 0) hzuo_flag = 2; else {hzuo_flag = 1; hzuo =- hzuo;}
	if(hyou > 0) hyou_flag = 1; else {hyou_flag = 2; hyou =- hyou;}
	if(qyou > 0) qyou_flag = 1; else {qyou_flag = 2; qyou =- qyou;}
	
	//车身 偏右 舵机向左打角
	if(qzuo_flag == 2 && hzuo_flag == 2 && hyou_flag == 2 && qyou_flag == 2){
		Duty_Servor_Center	= Duty_Servor_Center + (qzuo + hzuo) * 0.005;
		ServoCtrl(Duty_Servor_Center);
	}
	
	//车身 偏左 舵机向右打角
	if(qzuo_flag == 1 && hzuo_flag == 1 && hyou_flag == 1 && qyou_flag == 1){
		Duty_Servor_Center	= Duty_Servor_Center - (qzuo + hzuo) * 0.005;
		ServoCtrl(Duty_Servor_Center);
	}
	*/
}









