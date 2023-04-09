#ifndef __LQINCLUDES_H
#define __LQINCLUDES_H	  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STC16f.h"
#include "intrins.h"

#include "math.h"

typedef 	unsigned char	u8;
typedef 	unsigned char	uint8;
typedef 	unsigned char	uint8_t;
typedef 	unsigned int	u16;
typedef 	unsigned int	uint16;
typedef 	unsigned int	uint16_t;
typedef 	unsigned long	u32;
typedef 	unsigned long	uint32;
typedef 	unsigned long	uint32_t;
typedef 	signed char	int8;
typedef 	signed char	int8_t;
typedef 	signed int	int16;
typedef 	signed int	int16_t;
typedef 	signed long	int32;
typedef 	signed long	int32_t;

#include <LQ_GPIO_KEY.h>
#include <LQ_GPIO_LED.h>
#include <LQ_GPIO_EXIT.h>
#include <LQ_OLED096.h>
#include <LQ_MotorServo.h>
#include "LQ_ICM20689.h"
//#include "LQ_ICM42605.h"
#include <LQ_UART.h>
#include <LQ_ADC.h>
#include "LQ_PWM.h"
#include <LQ_I2C.h>
#include <LQ_I2C_soft.h>
#include <LQ_TIMER.h>
#include <LQ_SPI.h>
#include <LQ_SPI_soft.h>
#include <LQ_Encoder.h>
#include <LQ_UART.h>



#define EnableInterrupts (EA = 1)                 //�����ж�
#define DisableInterrupts (EA = 0)                //�����ж�

#define MAIN_Fosc 30000000UL

 
extern u8 Way_Angle;                              //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
extern u8 Flag_Add,Flag_Dec,Flag_Left,Flag_Right; //����ң����صı���
extern u8 Trace_BT;                               //����ң�ػ�������CCDѭ�� 1��Ĭ�ϣ�����ң�أ�0������CCDѭ��
extern u8 Flag_Stop,Flag_Show,Flag_Angle;         //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
extern unsigned short data Encoder;            									  //���ұ��������������
extern short data PWMMotor,PWMServo;                     //���PWM����
//extern short data Velocity;                            	//��ʾ�ٶ�     
extern u16 Voltage;                               //��ص�ѹ������صı���                     
extern float data Angle_Balance,Gyro_Balance,Gyro_Turn;//ƽ����� ƽ�������� ת��������
extern float Acceleration_Z;                      //Z����ٶȼ�  
extern float Balance_Kp,Balance_Kd,Balance_Ki,Velocity_Kp,Velocity_Ki;//PID����
extern float Balance_Kcf;                         //����������ϵ��
extern u8 Uart4_Receive;                          //uart4��������
extern short LeftRightFlag,ForwardBackFlag;
extern float data Angle;
extern float angle_dot;





// �û�����
void sysinit(void);
void Working(void);
void Get_ADC_Data(void);
void show_ADC_Data(void);
void Servor_Control(int16_t adc[5]);

	





#endif











