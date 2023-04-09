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
#ifndef __LQ_KEY_H_
#define __LQ_KEY_H_

#include "include.h"

//����ģ���
typedef enum
{
    KEY0 = 0,  //ĸ���ϰ���0
    KEY1 = 1,
    KEY2 = 2,
	  KEY3 = 3,
    DSW0 = 4,    //ĸ���ϲ��뿪��0
    DSW1 = 5,
} KEYn_e;

typedef enum
{
    LOW = 0,  //����
    HIGH = 1, //�ɿ�
    FAIL = 0xff, //����
} KEYs_e;

typedef enum //
{
    NOKEYDOWN = 0, KEY0DOWN = 0x01,  //ĸ���ϰ���0
    KEY1DOWN = 0x02,
    KEY2DOWN = 0x04,
    KEY01DOWN = 0x03,  //ĸ���ϰ���0
    KEY02DOWN = 0x05,
    KEY12DOWN = 0x06,
    KEY012DOWN = 0x07,
    KEYError = 0xFF,
} KEYdown_e;
//����Ĺܽ�Ҫ��Ӧʵ�ʰ���
#define KEY0p      P70 //ĸ���ϰ���0
#define KEY1p      P71 //ĸ���ϰ���1
#define KEY2p      P72 //ĸ���ϰ���2
#define KEY3p      P73 //ĸ���ϰ���2

#define REEDp      P37 //ĸ���ϸɻɹ�
/*********************** UART���ܺ��� **************************/
//��ʼ��
void GPIO_KEY_Init (void);
unsigned char KEY_Read (KEYn_e KEYno);
unsigned char KEY_Read_All (void);
void Test_GPIO_KEY (void);
void Test_ComKEY_Tft (void);
/*************************************************************************
*  �������ƣ�void Reed_Init(void)
*  ����˵�����ɻɹ�GPIO���жϳ�ʼ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��11��21��
*  ��    ע��   �ж����Ǹ��˳�ʼ�����ж�VECTABNUM�ű����Ӧ��cpu,���򲻻�����жϺ���
*          �жϷ�����PIN_INT0_IRQHandler��LQ_GPIO.c��
*************************************************************************/
void Reed_Init(void);
#endif
