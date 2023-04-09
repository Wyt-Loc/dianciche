/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ���ƽ��Ħ�г�
����    д��chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��12��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Keil5.2�����ϰ汾
��Target �� STC16F40K
��SYS PLL�� 36MHz
------------------------------------------------
����������Ƶ��ַ��https://space.bilibili.com/95313236
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

u8 Uart4_Receive;
bit busy;
int wptr;
char rptr;
char buffer[64];
#define Baudrate1   (65536 - MAIN_Fosc / 115200 / 4)
#define Baudrate4   (65536 - MAIN_Fosc / 115200 / 4)


//========================================================================
// ����: void UART1_int (void) interrupt UART1_VECTOR
// ����: UART1�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART1_int (void) interrupt 4
{
    if(RI)
    {
        RI = 0;
       //
    }

    if(TI)
    {
        TI = 0;
       //
    }
}
//========================================================================
// ����: void UART4_int (void) interrupt UART4_VECTOR
// ����: UART4�жϺ�����
// ����: nine.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART4_int (void) interrupt 18
{
//	  static	int uart_receive=0;                              //����������ر���
//    static u8 Flag_PID,i,j,Receive[50];                      
//    static float Data;                                       
	             
	if(S4CON & 0x02)
	{
		S4CON &= ~0x02;  //Clear Tx flag  ������ͱ�־λ
		busy=0;
	}
	if(S4CON & 0x01)                                  
	{
		S4CON &= ~0x01;  //Clear Rx flag	������ձ�־λ
		buffer[wptr++]= S4BUF;
		wptr &= 0xff;
	}
	
//    if((S4CON & 0x01) != 0)                                  
//    {                                                        
//        S4CON &= ~0x01;                                      //Clear Rx flag
//                                                             
//                                                             
//    uart_receive=S4BUF;                                      
//    Uart4_Receive=uart_receive;                              
//	                                                           
//    if(uart_receive=='A')                                    
//		{                                                        
//			Flag_Add=1,Flag_Dec=0;                                 //0x41--65
//			if(ForwardBackFlag<500) ForwardBackFlag+=50;           //===���� 			
//		}                                                        
//		else if(uart_receive=='D')                               //����
//		{                                                        
//			Flag_Add=0,Flag_Dec=1;                                 //0x45--69���ٵ���Ĭ��ֵ��
//			if(ForwardBackFlag>-1000) ForwardBackFlag-=50;         //===����
//		}
//    else if(uart_receive=='L')	Flag_Left=1,Flag_Right=0;    //��ת��0x4C--76         
//    else if(uart_receive=='R')	Flag_Left=0,Flag_Right=1;    //��ת��0x52--82  
//    else if(uart_receive=='T')	Trace_BT=0;                  //����CCDѭ��
// 		else if(uart_receive=='B')	Trace_BT=1;                  //����ң��
//    else if(uart_receive=='P')
//		{
//			Flag_Left=0,Flag_Right=0;                              //ͣ��
//			Flag_Add=0,Flag_Dec=0;
//			MotorCtrl(0,0);                                        //������DRV8701����BTN7971������
//      ServoCtrl(Servo_Center);                           //�������PWM �����Χ����0��10000��	
//			Flag_Stop=1;		
//		}
//  }  											 

//    if((S4CON & 0x02) != 0)
//    {
//        S4CON &= ~0x02;                                      //Clear Tx flag
//        //
//    }
}
//========================================================================
// ����: SetTimer2Baudraye(u32 dat)
// ����: ����Timer2�������ʷ�������
// ����: dat: Timer2����װֵ.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void    SetTimer2Baudraye(u32 dat)
{
    AUXR &= ~(1<<4);                                         //Timer stop
    AUXR &= ~(1<<3);                                         //Timer2 set As Timer
    AUXR |=  (1<<2);                                         //Timer2 set as 1T mode
    T2H = (u8)(dat / 256);
    T2L = (u8)(dat % 256);
    IE2  &= ~(1<<2);                                         //��ֹ�ж�
    AUXR |=  (1<<4);                                         //Timer run enable
}
//========================================================================
// ����: void   UART1_config(u16 tmr)
// ����: UART1��ʼ��������
// ����: tmr: ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer1��������.
// ����: none.
// �汾: VER1.0
// ����: 2014-11-28
// ��ע: 
//========================================================================
void UART1_config(u16 tmr)
{
    /*********** ������ʹ�ö�ʱ��2 *****************/
    if(tmr == 2)
    {
        AUXR |= 0x01;                                         //S1 tmr Use Timer2;
        SetTimer2Baudraye(Baudrate1);
    }
    /*********** ������ʹ�ö�ʱ��1 *****************/
    else
    {
        TR1 = 0;
        AUXR &= ~0x01;                                        //S1 tmr Use Timer1;
        AUXR |=  (1<<6);                                      //Timer1 set as 1T mode
        TMOD &= ~(1<<6);                                      //Timer1 set As Timer
        TMOD &= ~0x30;                                        //Timer1_16bitAutoReload;
        TH1 = (u8)(Baudrate1 / 256);
        TL1 = (u8)(Baudrate1 % 256);
        ET1 = 0;    				                           	//��ֹ�ж�
        INTCLKO &= ~0x02;		                               	//�����ʱ��
        TR1  = 1;
    }
    /*************************************************/

    SCON = (SCON & 0x3f) | 0x40;                              	//UART1ģʽ, 0x00: ͬ����λ���, 0x40: 8λ����,�ɱ䲨����, 0x80: 9λ����,�̶�������, 0xc0: 9λ����,�ɱ䲨����
//  PS  = 1;                                                  	//�����ȼ��ж�
    ES  = 1;                                                  	//�����ж�
    REN = 1;                                                 	 //�������
    P_SW1 &= 0x3f;
//  P_SW1 |= 0x00;                                            	//UART1 switch to, 0x00: P3.0 P3.1, 0x40: P3.6 P3.7, 0x80: P1.6 P1.7, 0xC0: P4.3 P4.4

}
void UART4_config(u16 tmr)                                    	// ѡ������, 2: ʹ��Timer2��������, ����ֵ: ʹ��Timer4��������.
{
	if(tmr == 2)
    {
		SetTimer2Baudraye(Baudrate4);
		S4CON = 0x10;                                       	//8λ����, ʹ��Timer2�������ʷ�����, �������
    }
	else
	{
        S4CON = 0x50;                                          	//8λ����, ʹ��Timer4�������ʷ�����, �������
        T4H = (Baudrate4) / 256;
        T4L = (Baudrate4) % 256;
        T4T3M = 0xA0;
	}
    IE2 |= 0x10;                                               	//����UART4�ж�
//    P_SW2 &= ~0x04;                                            	//UART4 switch bit2 to: 0: P0.2 P0.3
    P_SW2 |= 0x04;                                           	//UART4 switch bit2 to: 1: P5.2 P5.3
}
/*************************************************************************
*  �������ƣ�void UART_PutChar(UART_t  uratn, char ch)
*  ����˵����UART�����ֽں���,ʹ��ǰ���ȳ�ʼ����Ӧ����
*  ����˵����uratn �� UART0 - UART3/ ch    �� Ҫ��ӡ���ַ�
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_PutChar(UART0, 'a');  //��ӡ�ַ�a
*************************************************************************/
void UART1_PutChar(char ch)
{
		SBUF = ch;    
}
void UART4_PutChar(char ch)
{
		while(busy);
		busy=1;
		S4BUF = ch; 
}
/*************************************************************************
*  �������ƣ�void UART_PutStr(UART_t  uratn, char *st)
*  ����˵����UART�����ַ�������(�� NULL ֹͣ����),ʹ��ǰ���ȳ�ʼ����Ӧ����
*  ����˵����uratn �� UART0 - UART3/ str   �� Ҫ��ӡ���ַ�����ַ
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_PutStr(UART3, "123456789"); //����9���ֽ�
*************************************************************************/
void UART1_PutStr(char *st)
{
  while(*st)
  {
    UART1_PutChar(*st++);
  }
}
void UART4_PutStr(char *st)
{
  char *p1;
	p1=st;
	while(*p1)
	{
		UART4_PutChar(*p1++);
	}
}
/*************************************************************************
*  �������ƣ�char UART_GetChar(UART_t  uratn)
*  ����˵����UART��ȡ�ֽ� ʹ��ǰ���ȳ�ʼ����Ӧ���� ����ǰ��ȷ���н��յ����� �����ȴ����ݵ���
*  ����˵����uratn �� UART0 - UART3
*  �������أ���ȡ�ֽ�
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��UART_GetChar(UART3); //����һ���ַ�
*************************************************************************/
char UART1_GetChar(void)
{  
  return (SBUF);
}
char UART4_GetChar(void)
{  
  return (S4BUF);
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void delayus(unsigned int us)
����  �ܡ���ʱ����
������ֵ��us /30M
������ֵ���� 
����  �ߡ�chiusir
�������¡�2021��1��22�� 
������汾��V1.0
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void  delayus(unsigned int us)
{
  unsigned int i;
  do{    
    i=MAIN_Fosc/6000001;//��Լ1us
    while(--i);
  }while(--us);
}
//
