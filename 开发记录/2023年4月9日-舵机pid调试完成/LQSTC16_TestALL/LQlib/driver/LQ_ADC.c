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
����ʱ, ѡ��ʱ�� 30MHZ (�û��������޸�Ƶ��).
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"


int16_t ad_max[4] = {500,500};  // �°��ӷŵ������궨���ֵ,�ᱻ����ˢ��
int16_t ad_min[4] = { 0,0};   	// �°��Ӿ���Ҫ�궨��Сֵ,�ᱻ����ˢ��
int16_t left = 0, right = 0;
int16_t LnowADC[6];
u16 Voltage; 
/********************************************************************************************************
**������Ϣ ��ADC1_SingleChannel_Get(uint8_t ADC_Channel_x)       
**�������� ����ȡADC1ת������
**������� ��ADC_Channel_x , xΪ0~11
**������� ��puiADDataΪADC������ֵ��Ĭ����12λ
********************************************************************************************************/
u16 ADC_Read(uint8 ADC_Channel_x)
{
    ADC_RES = 0;
    ADC_RESL = 0;

    ADC_CONTR = (ADC_CONTR & 0xF0) | 0x40 | ADC_Channel_x;    //���� AD ת��
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    while((ADC_CONTR & 0x20) == 0)  ;   //wait for ADC finish
    ADC_CONTR &= ~0x20;     																	//���ADC������־
    return  (((u16)ADC_RES << 8) | ADC_RESL);//Ĭ����12λ
}

/********************************************************************************************************
**������Ϣ ��Get_Adc_Average(uint8_t ADC_Channel_x,uint8_t times)     
**�������� ����ȡ����ADC1����ֵ��ƽ��ֵ
**������� ��ADC_Channel_x , xΪ0~8
**������� ��puiADDataΪADC������ֵ
********************************************************************************************************/
u16 ADC_Read_Average(uint8 ADC_Channel_x,uint8 times)
{
    u32 temp_val=0;
    u8 t;
    u8 delay;
    for(t=0;t<times;t++)
    {
        temp_val+=ADC_Read(ADC_Channel_x);
        for(delay=0;delay<100;delay++);
    }
    return temp_val/times;
} 
/*************************************************************************
 *  �������ƣ�void InductorInit (void)
 *  ����˵�����ĸ����ADC��ʼ��������
 *  ����˵������
 *  �������أ���
 *  �޸�ʱ�䣺2020��11��18��
 *  ��    ע��
 *************************************************************************/
void ADC_Init (void)
{
	/*
		P0M1 |= 0x0f; P0M0 &= ~0x0f;  //����0.0 0.1 0.2 0.3Ϊ����̬
	  P1M1 |= 0x03; P1M0 &= ~0x03;  //����1.0 1.1Ϊ����̬
	
    P_SW2 |= 0x80;
    ADCTIM = 0x3f;					//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
    P_SW2 &= 0x7f;
    ADCCFG = 0x2f;					//���� ADC ʱ��Ϊϵͳʱ��/2/16/16
    ADC_CONTR = 0x80; 			//ʹ�� ADC ģ��
	*/
	
  P_SW2 |= 0x80;   
  ADCTIM = 0x3f;					//���� ADC �ڲ�ʱ��ADC����ʱ�佨�������ֵ
  P_SW2 &= 0x7f;
  ADCCFG |= 0x2f;					//���� ADC ʱ��Ϊϵͳʱ��/2/16/16
	ADCCFG |= 1<<5;					//�Ҷ���
  ADC_CONTR = 0x80; 			//ʹ�� ADC ģ��
	
	//p0��ʹ����9 10 11   ��Ӧ io 0.1 0.2 0.3
	P0M0 = P0M0 & 0xf1;    //0        1 1 1 1 0 0 0 0   p0.0~p0.3Ϊ�������
	P0M1 = P0M1 | 0x0e;	   //1				1 1 1 1 1 1 1 1 	p0.4~p0.7Ϊ��©���
	
	//p1��ʹ����0 1       ��Ӧ io 1.0 1.1
	P1M0 &= 0xfc;        //0          1 1 1 1 0 1 0 0  p1.0~p1.1 p1.3Ϊ�������� 
	P1M1 |= 0x0f;				 //1					1 1 1 1 1 1 1 1  p1.2Ϊ�������  p1.4~p1.7Ϊ��©���

}

/**************************************************************************
�������ܣ���ȡ���ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Get_Adc(void)
{
	LnowADC[0]=ADC_Read(11);      //��ȡADC11ͨ��ֵ
	LnowADC[1]=ADC_Read(10);			//��ȡADC10ͨ��ֵ
	LnowADC[2]=ADC_Read(9); 			//��ȡADC9ͨ��ֵ
	LnowADC[3]=ADC_Read(8);				//��ȡADC8ͨ��ֵ	
	
}
/*************************************************************************
 *  �������ƣ�void InductorNormal(void)
 *  ����˵�����ɼ���е�ѹ������һ����
 *  �������أ���
 *  �޸�ʱ�䣺2020��11��26��
 *  ��    ע�� 
 *************************************************************************/
void InductorNormal(void)
{
    Get_Adc();  //��ȡADC
	  if (LnowADC[0] < ad_min[0])            ad_min[0] = LnowADC[0];     // ˢ����Сֵ
    else if (LnowADC[0] > ad_max[0])       ad_max[0] = LnowADC[0];     // ˢ�����ֵ
	
    if (LnowADC[1] < ad_min[1])            ad_min[1] = LnowADC[1];
    else if (LnowADC[1] > ad_max[1])       ad_max[1] = LnowADC[1]; 
	
    if (LnowADC[2] < ad_min[2])            ad_min[2] = LnowADC[2];
    else if (LnowADC[2] > ad_max[2])       ad_max[2] = LnowADC[2];
	
    if (LnowADC[3] < ad_min[3])            ad_min[3] = LnowADC[3];
    else if (LnowADC[3] > ad_max[3])       ad_max[3] = LnowADC[3];	
	
	  left = (LnowADC[0] - ad_min[0]) * 100 / (ad_max[0] - ad_min[0]);     // ��ƫ������һ����0--1000����
    right = (LnowADC[1] - ad_min[1]) * 100 / (ad_max[1] - ad_min[1]);
}
/*************************************************************************
*  �������ƣ�void Test_ADC(void)
*  ����˵�������Գ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע����Ļ��ʾADC�ɼ��ĵ��ֵ
*************************************************************************/
void Test_ADC(void)
 {
	char txt[30]; 
	OLED_Init();    //OLED��ʼ��
	OLED_CLS();  	 	//����		
	OLED_P14x16Str(0,2,(unsigned char*)"�����������ܿƼ�");		//�ַ�����ʾ
	OLED_P6x8Str(0,4,"Long Qiu i.s.t.");		//�ַ�����ʾ
	delayms(1000);  //��ʱ�ȴ�
	OLED_CLS();     //����		
	ADC_Init();			//ADC��ʼ��
 	while(1)
 	{
		Get_Adc();	
		sprintf(txt,"AD0:%04d ",LnowADC[0]);  //��ʾADC11��ֵ
		OLED_P8x16Str(0,0,(u8*)txt);
		sprintf(txt,"AD1:%04d ",LnowADC[1]);	//��ʾADC10��ֵ
		OLED_P8x16Str(0,2,(u8*)txt);
		sprintf(txt,"AD2:%04d ",LnowADC[2]);	//��ʾADC9��ֵ
		OLED_P8x16Str(0,4,(u8*)txt);
		sprintf(txt,"AD3:%04d ",LnowADC[3]);	//��ʾADC8��ֵ
		OLED_P8x16Str(0,6,(u8*)txt);
		}
}