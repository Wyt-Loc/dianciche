/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ���ƽ��Ħ�г�
����    д��chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��4��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Keil5.2�����ϰ汾
��Target �� STC16F40K
��SYS PLL�� 36MHz
------------------------------------------------

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"


/*************************************************************************
*  �������ƣ�void LED_Init(void)
*  ����˵����GPIO��ʼ������ LED������PB10��PA3��ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void GPIO_LED_Init(void)
{
    P2M1 &= 0xFE;
    P2M1 |= 0x00;
    P2M0 &= 0xFE;
		P2M0 |= 0x01;   //����Ϊ�������
	
}

/*************************************************************************
*  �������ƣ�void LED_Ctrl(LEDn_e LEDno, LEDs_e sta)
*  ����˵����LED����
*  ����˵����LEDn_e LEDno���,LEDs_e sta״̬��/��/��ת
*  �������أ�����״̬��0/1
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
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
�������ܣ�LED��˸
��ڲ�������˸Ƶ�� 
����  ֵ����
**************************************************************************/
void Led_Flash(u16 time)
{
	  static int temp;
	  if(0==time) LED0p=0;
	  else if(++temp>time)	LED0p=~LED0p,temp=0;
}
/*************************************************************************
*  �������ƣ�void Test_GPIO_LED(void)
*  ����˵�������Գ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע�����İ��ϵ�LED����˸--�ĸ�LEDͬʱ��˸
*************************************************************************/
void Test_GPIO_LED(void)
 {
	GPIO_LED_Init();
 	while(1)
 	{
 		LED_Ctrl(LEDALL,RVS);        //LEDͬʱ��˸
 		delayms(200);                //��ʱ�ȴ�
 	}
 }
