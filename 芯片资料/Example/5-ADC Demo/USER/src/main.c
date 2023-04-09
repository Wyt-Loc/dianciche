/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"


/*
 *关于内核频率的设定，可以查看board.h文件
 *在board_init中,已经将P54引脚设置为复位
 *如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */
 
 
uint16 adc_data[3];
void main()
{

    //sys_clk可选值:33177600, 30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行时的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
    sys_clk = 30000000;     //设置系统频率为30MHz
	
	board_init();	
	
	adc_init(ADC_P10, ADC_SYSclk_DIV_2);	//初始化ADC,P1.0通道 ，ADC时钟频率：SYSclk/2
	adc_init(ADC_P11, ADC_SYSclk_DIV_2);	//初始化ADC,P1.1通道 ，ADC时钟频率：SYSclk/2
	adc_init(ADC_P13, ADC_SYSclk_DIV_2);	//初始化ADC,P1.2通道 ，ADC时钟频率：SYSclk/2
	

    while(1)
	{
		//使用在线调试，查看adc_data数组的数值，可以得到AD数据。
		adc_data[0] = adc_once(ADC_P10, ADC_12BIT);	//采集一次ADC，精度10位
		adc_data[1] = adc_once(ADC_P11, ADC_10BIT);	//采集一次ADC，精度9位
		adc_data[2] = adc_once(ADC_P13, ADC_8BIT);	//采集一次ADC，精度8位
		printf("adc_data[0] = %d\r\n", adc_data[0]);
		printf("adc_data[1] = %d\r\n", adc_data[1]);
		printf("adc_data[2] = %d\r\n", adc_data[2]);
		
		delay_ms(100);
    }
}

