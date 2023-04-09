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
*  �������ƣ�void GPIO_KEY_Init(void)
*  ����˵����GPIO��ʼ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void GPIO_KEY_Init(void)
{
    P7M1 = 0;   P7M0 = 0;   //����Ϊ׼˫���
	
}

/*************************************************************************
*  �������ƣ�unsigned char KEY_Read(KEYn_e KEYno)
*  ����˵������ȡ����״̬
*  ����˵����KEYn_e KEYno�������
*  �������أ�����״̬��0/1
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
unsigned char KEY_Read(KEYn_e KEYno)
{
    switch(KEYno)
    {
      case KEY0:
        return P70;				//ĸ���ϰ���0
      break;

      case KEY1:
        return P71;				//ĸ���ϰ���1
      break;

      case KEY2:
        return P72;				//ĸ���ϰ���2
      break;
			
			case KEY3:
				if(P73)
					return 1;				//ĸ���ϰ���3
				else
				{
					while(P73==0);  //�ȴ��ɿ�����
					return 0;	
				}
      break;

      case DSW0:
        return P32;				//ĸ���ϲ��뿪��0
      break;

      case DSW1:
        return P33;				//ĸ���ϲ��뿪��1
      break;
      default:
        return 0XFF;
    }
    return 0;
}


/*************************************************************************
*  �������ƣ�unsigned char KEY_Read_All(void)
*  ����˵������ȡȫ������״̬
*  ����˵������
*  �������أ��������״̬��0--7����״̬
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע����ȡ��������״̬��������ϼ�ʹ��
*************************************************************************/
unsigned char KEY_Read_All(void)
{
   unsigned char tm=0;

   tm = P70 | (P7^1 << 1) | (P7^2 << 2);//��ȡ��������״̬������	
   if(tm==0x07)
	{
	   return 0;
	}
   return  (~tm)&0X07;
}


/*************************************************************************
*  �������ƣ�void Test_GPIO_KEY(void)
*  ����˵�������Գ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע������KEY0/1/2����� LEDȫ��
*************************************************************************/
void Test_GPIO_KEY(void)
 {
	unsigned char k=0xFF;
	GPIO_LED_Init();
	GPIO_KEY_Init();
 	while(1)
 	{
 		k= KEY_Read(KEY0)& KEY_Read(KEY1)& KEY_Read(KEY2)& KEY_Read(KEY3);

 		if(k==0) LED_Ctrl(LEDALL, ON); //����KEY0/1/2����� LEDȫ��
 		else     LED_Ctrl(LEDALL, OFF);//�ɿ�KEY0/1/2����� LEDȫ��

 		delayms(100);                //��ʱ�ȴ�
 	}
 }


/*************************************************************************
*  �������ƣ�void Test_ComKEY_Tft(void)
*  ����˵����������ϰ������ڲ�����ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע������״̬������ʾ
*************************************************************************/
void Test_ComKEY_Tft(void)
 {
	unsigned char k=0xFF;
  OLED_Init();                                              //OLED��ʼ��
	OLED_CLS();                                               //����		
	OLED_P14x16Str(0,0,(unsigned char*)"�����������ܿƼ�");		//�ַ�����ʾ
	OLED_P6x8Str(0,2,"Long Qiu i.s.t.");	                  	//�ַ�����ʾ
	delayms(1000);                                            //��ʱ�ȴ�
	OLED_CLS();                                               //����		
	OLED_P6x8Str(0,1,"KEY Pressed:  ");	                    	//�ַ�����ʾ
	GPIO_KEY_Init();
 	while(1)
 	{
 		k= KEY_Read_All();
 		switch(k)
 		{
 		  case NOKEYDOWN:
 			 //OLED_P6x8Str(35,3,"NO key!  ");		//�ַ�����ʾ
 		  break;
 		  case KEY0DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY0!    ");		  //�ַ�����ʾ
 		  break;
 		  case KEY1DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY1!    ");		  //�ַ�����ʾ
 		  break;
 		  case KEY2DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY2!    ");		  //�ַ�����ʾ
 		  break;
 		  case KEY01DOWN:
 			 OLED_P6x8Str(35,3,"KEY0&1!  ");		  //�ַ�����ʾ
 		  break;
 		  case KEY02DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY0&2!  ");		  //�ַ�����ʾ
 		  break;
 		  case KEY12DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY1&2!  ");		  //�ַ�����ʾ
 		  break;
 		  case KEY012DOWN:
 		 	 OLED_P6x8Str(35,3,"KEY0&1&2!");	  	//�ַ�����ʾ
 		  break;
 		  default:
 		  break;
 		 }
 		LED_Ctrl(LED0,RVS);                     //�ĸ�LEDͬʱ��˸
 		delayms(100);                           //��ʱ�ȴ�
 	}
 }



