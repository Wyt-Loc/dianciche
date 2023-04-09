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

#define EX2 0x10
#define EX3 0x20
#define EX4 0x40

u8  INT0_cnt, INT1_cnt; 					//�����õļ�������
u8  INT2_cnt, INT3_cnt, INT4_cnt; //�����õļ�������

/********************* INT0�жϺ��� *************************/
void INT0_int (void) interrupt 0  //���ж�ʱ�Ѿ������־
{
    INT0_cnt++;										//�ж�+1
}

/********************* INT1�жϺ��� *************************/
void INT1_int (void) interrupt 2      //���ж�ʱ�Ѿ������־
{
    INT1_cnt++; //�ж�+1
}

/********************* INT2�жϺ��� *************************/
void INT2_int (void) interrupt 10 //���ж�ʱ�Ѿ������־
{//IMU��
    INT2_cnt++; 									//�ж�+1
	
}

/********************* INT3�жϺ��� *************************/
void INT3_int (void) interrupt 11 //���ж�ʱ�Ѿ������־
{//�ɻɹ���
  INT3_cnt++; 									//�ж�+1
	LED_Ctrl(LED1, RVS);   				//LED��˸;
}

/********************* INT4�жϺ��� *************************/
void INT4_int (void) interrupt 16 //���ж�ʱ�Ѿ������־
{
    INT4_cnt++; 									//�ж�+1
}
/*************************************************************************
*  �������ƣ�void LED_Init(void)
*  ����˵����GPIO��ʼ������ LED������PB10��PA3��ʼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void GPIO_EXIT_Init(void)
{                                
    IE1 = 0;                      //���ж�1��־λ
    IE0 = 0;                      //���ж�0��־λ    
    EX0 = 0;                      //INT0 ��ʹ��
	  EX1 = 0;                      //INT1 ��ʹ��
    IT0 = 1;                      //INT0 �½����ж�       
//  IT0 = 0;                      //INT0 ����,�½����ж�
    IT1 = 1;                      //INT1 �½����ж� 

    //INT2, INT3, INT4 ������Ҫʱ�ο�ʹ��
    //INTCLKO |= EX2;             //ʹ�� INT2 �½����ж� IMUģ��
    INTCLKO |= EX3; 	            //ʹ�� INT3 �½����ж� �ɻɹ� 
    //INTCLKO |= EX4;             //ʹ�� INT4 �½����ж�
                                  
    EA = 1;     			            //�������ж�
}


/*************************************************************************
*  �������ƣ�void Test_GPIO_EXIT_Init(void)
*  ����˵�������Գ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע�����İ��ϵ�LED����˸
*************************************************************************/
void Test_GPIO_EXIT_Init(void)
{
	char txt[32];
	GPIO_LED_Init();				
	GPIO_EXIT_Init();
  OLED_CLS();   							//����	
 	while(1)
 	{
 		sprintf(txt,"INT3_cnt:%03d ",INT3_cnt);  //��ʾADC11��ֵ
		OLED_P8x16Str(0,4,(u8*)txt);      
 	}
 }
