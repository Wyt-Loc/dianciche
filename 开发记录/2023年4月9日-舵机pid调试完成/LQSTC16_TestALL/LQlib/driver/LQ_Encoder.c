
#include "include.h"


/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ����������ע���ȡ֮�������ڣ���Ҫ����16λ���ֵ
**************************************************************************/
short Read_Encoder(u8 encno)
{
  short tm=0;
  if(encno==1)
  {
		if(P07)//������������A:P06  DIR:P07 	
			tm=(T4H<<8)|T4L;	
		else 
			tm=0-((T4H<<8)|T4L);	
		
		T4T3M &= ~(1<<7);
		T4H = 0;
		T4L = 0;
		T4T3M |= (1<<7);		
  }
  else if(encno==2)
  {
		if(P05)//������������A:P04  DIR:P05 	
			tm=(T3H<<8)|T3L;	
		else
			tm=0-((T3H<<8)|T3L);	
		
		T4T3M &= ~(1<<3);
		T3H = 0;
		T3L = 0;
		T4T3M |= (1<<3);		
  }	
  return tm;
}

/*************************************************************************
*  �������ƣ�void Timer4EncInit(void)
*  ����˵������������ʼ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��12��1��
*  ��    ע������2��������
*************************************************************************/
void Timer34EncInit (void)
{   
	/*
  T4T3M &= ~0xf0;     	//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��  
  T4T3M &= ~0x01;    		//�����ʱ��
  T4T3M |=  (1<<2);    	//12T mode ;P0.4����
  T3H = 0;
  T3L = 0;
	
	T4T3M |=  (1<<3);     //��ʼ����
	//ET3 = 1;   					//�����ж�
	
  T4T3M &= ~0x10;    	  //�����ʱ��
  T4T3M |=  (1<<6);     //12T mode ;P0.6����
  T4H = 0;
  T4L = 0; 
  T4T3M |=  (1<<7);     //��ʼ����
	//ET4 = 1;   					//�����ж�	
	//EA=1;
	*/
	T3L = 0; 
	T3H = 0;
	T4T3M |= 0x0c; 
			
	T4L = 0;
	T4H = 0;
	T4T3M |= 0xc0; 
}

/*************************************************************************
 *  �������ƣ�void TestEncoder(void)
 *  ����˵�������Գ���TFT1.8��ʾ
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��4��10��
 *  ��    ע��
 *************************************************************************/

void TestEncoder(void)
{
    char txt[16];
    short duty = 20;
	  short enc1,enc2;

    OLED_CLS();   	                         	//����
    OLED_P6x8Str(0, 0, "Test Encoder");       //�ַ�����ʾ
    Timer34EncInit();                          //�������ӿڳ�ʼ��
    MotorInit(MOTOR_FREQUENCY);    
    while (1)
    {
        if (KEY_Read(KEY0) == 0)      //����KEY0����ռ�ձȼ�С
        {
            if (duty > -PWM2_CLOCK/MOTOR_FREQUENCY)//��ռ�ձ�Ϊ10M/12.5k=800
                duty -= 50;
        }
        if (KEY_Read(KEY2) == 0)      //����KEY2����ռ�ձȼӴ�
        {
            if (duty < PWM2_CLOCK/MOTOR_FREQUENCY)  //��ռ�ձ�Ϊ10M/12.5k=800
                duty += 50;
        }
        if (KEY_Read(KEY1) == 0)      //����KEY1����ռ�ձ���ֵ
        {
            duty = 20;
        }

        MotorCtrl(duty,duty);

        /* ��ȡ������ֵ */
        enc1 = Read_Encoder(1); 			        //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
        enc2 = Read_Encoder(2); 			        //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ

        sprintf(txt, "Enc1: %04d  ", enc1);
        OLED_P6x8Str(0, 3, txt);			        //�ַ�����ʾ
        sprintf(txt, "PWM: %05d;", duty);
        OLED_P6x8Str(0, 4, txt);   //�ַ�����ʾ
        sprintf(txt, "Enc2: %04d  ", enc2);
        OLED_P6x8Str(0, 5, txt);			        //�ַ�����ʾ

        LED_Ctrl(LED1, RVS);       		        //��ƽ��ת,LED��˸
        delayms(50);							            //��ʱ�ȴ�
    }
}
/*
void TestEncoder(void)
{
    char txt[16];
	  short enc1,enc2;

    OLED_CLS();   	                         	//����
    OLED_P6x8Str(0, 0, "Test Encoder");       //�ַ�����ʾ
    Timer34EncInit();                          //�������ӿڳ�ʼ��
    while (1)
    {
        /* ��ȡ������ֵ 
        enc1 = Read_Encoder(1); 			        //���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
        enc2 = Read_Encoder(2); 			        //�ҵ�� ĸ���ϱ�����2��С��ǰ��Ϊ��ֵ

        sprintf(txt, "Enc1: %04d  ", enc1);
        OLED_P6x8Str(0, 3, txt);			        //�ַ�����ʾ
        sprintf(txt, "Enc2: %04d  ", enc2);
        OLED_P6x8Str(0, 5, txt);			        //�ַ�����ʾ

        LED_Ctrl(LED0, RVS);       		        //��ƽ��ת,LED��˸
        delayms(50);							            //��ʱ�ȴ�
    }
}*/