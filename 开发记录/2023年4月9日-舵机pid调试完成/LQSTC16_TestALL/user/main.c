
#include "include.h"
#include "PID.h"

//PID�ṹ���ʼ��
pid_param_t  pid_servor;



//����ȫ�ֱ���  �������  ռ�ձ�����  ��ʼ��Ϊ 20
// ��ռ�ձ�Ϊ10M/12.5k=800
//PWM2_CLOCK  10000000 //10M
//ռ�ձ� = duty / 800 
//�����ѹ =  ��ص�ѹ * ռ�ձ�
volatile int16_t Duty_Motor = 260;						// ���ռ�ձȳ�ʼ��

//���ռ�ձ�����  ռ�ձȼ� ���Ҵ��
//ʹ��ǰ���ö����ֵ ���� �� 1675
volatile uint16_t Duty_Servor_Center = 1675;		// �����ֵ��ʼ��


volatile short enc1;  // �������ֵ
volatile short enc2;	// �ұ�����ֵ


//��Ȧ���
int16_t ADC_Data[5];  //�õ� ��Ȧ�ĸ�Ӧ��ѹ

//����·�м�ʱ �ĵ��ֵ	 ǰ��	 ǰ��	 ����	 ����	 ǰ��
static int16_t ADC_Center[5] = {2411, 1717, 2218, 2344, 1599};


/******************** ������ **************************/
void main(void)  
{	 	
	
  sysinit(); 																//ϵͳ��ʼ��
	
	GPIO_LED_Init();													// LED ��ʼ��
	
	//OLED_Init();															// OLED��ʾ����ʼ��
	
	//Timer34EncInit();													//��������ʼ��
	
	MotorInit(MOTOR_FREQUENCY);    						// �����ʼ��
	
	ServoInit(100);													  // ��һ����ʼ����� ��֤��������ʱ�����ǶԵ�
	     																			  // �����ʼ����Ƶ��Ϊ100Hz	�����ֵ 1675 
	ServoCtrl(Duty_Servor_Center); 									// ���ö����ֵ
	
  //UART1_config(1);												// ʹ�ö�ʱ��2������4�Ĳ���������ʱ��
  OLED_Init(); 														// OLED��ʾ����ʼ��
  OLED_CLS();   													// ����	
  OLED_P6x8Str(0, 0, "WytZnc");						// ��ʾ�ַ�
	
	PidInit_wz(&pid_servor);						//���PID��ʼ��
	
	ADC_Init();
 
	//Timer1_init();															//timer1��ʼ������
	//EA = 1;
  delayms(1200);														// �ȴ�����ȫ���ϵ����
	MotorCtrl(0, Duty_Motor * 0.7);									// ����Ҫ duty�˸�ϵ��  �����ٶȲ�����  ��ȻΪ��ѹΪ0Ҫ���ͷ�ת
	
  while (1)
  {
		
		Get_ADC_Data();
		Servor_Control(ADC_Data);
		//show_ADC_Data();

		/* ��ȡ������ֵ */
    // enc1 =  Read_Encoder(1); 			        // ���� ĸ���ϱ�����1��С��ǰ��Ϊ��ֵ
    // enc2 = -Read_Encoder(2); 			        // �ҵ�� ĸ���ϱ�����2��С������Ϊ��ֵ
  }
}

/***************************************************************
����������void sysinit(void)  
����  �ܡ�ϵͳ��ʼ�� �����ɶ���ֲ�
������ֵ����
������ֵ����
****************************************************************/
void sysinit(void)  
{	
  WTST = 0; 
  P_SW2 |= 0x80;	
	IRCBAND=0;        //1��35MƵ�Σ�0��24MƵ��
	//IRTRIM =0;
	//LIRTRIM=0;  
  CLKDIV = 0;				//24MHz��Ƶ����Ƶ����
  P_SW2 &= 0x7F;
  RSTCFG|=1<<4;           //P5.4��λ�ܽ�
  P0M1 =0x40; P0M0 = 0;   //����Ϊ׼˫���,P0.6  0.7Ϊ����ڣ���������
	P0PU =0x40;             //P0.6  0.7ʹ���ڲ�4.1K��������
  P1M1 = 0;   P1M0 = 0;   //����Ϊ׼˫���
  P3M1 = 0;   P3M0 = 0;   //����Ϊ׼˫���
  P4M1 = 0;   P4M0 = 0;   //����Ϊ׼˫���
  P5M1 = 0;   P5M0 = 0;   //����Ϊ׼˫���
  P6M1 = 0;   P6M0 = 0;   //����Ϊ׼˫���
  P7M1 =0xFF; P7M0 = 0;   //����Ϊ׼˫��� 
  P7PU =0xFF;	            //����Ϊ׼˫���,P7.0123Ϊ����ڽӰ���,P7.4567Ϊ����ڽӵ������
  P40 = 0;		//��LED��Դ 
	EA=1;
}

/***************************************************************
���������� void Working(void)
����  �ܡ� ��ʾϵͳ��������
������ֵ�� ��	
������ֵ�� ��		�������ж��еĺ��� ��Ҫ����ʱ Ӱ�������������� 
****************************************************************/
void Working(void){

		P42 = 0;  //���İ��̵� 
		delayms(200); 
		P42 = 1;
		delayms(200);  
	//LED_Ctrl(LED1p,RVS);        //LEDͬʱ��˸
}

/***************************************************************
����������void timer1_int (void) interrupt 3 
����  �ܡ��ж�1������
������ֵ����
������ֵ����
****************************************************************/
void timer1_int (void) interrupt 3
{
	  //Working();
}

/***************************************************************
����������void Get_ADC_Data(void)
����  �ܡ��õ�ADC��õĸ�Ӧ��ѹ
������ֵ����
������ֵ����
****************************************************************/
void Get_ADC_Data(void){
	
	  ADC_Data[0]=ADC_Read(0);    //ǰ��  	    	p 1.0  0
    ADC_Data[1]=ADC_Read(1);    //ǰ��    	 		p 1.1  1
    ADC_Data[2]=ADC_Read(10);   //����    		 	p 0.2  10
    ADC_Data[3]=ADC_Read(9);    //���� 				 	p 0.1  9
    ADC_Data[4]=ADC_Read(11);   //ǰ�� 					p 0.3  11
//		ADC_Data[5]=ADC_Read(8);	  //					  p 0.0  8

}

/***************************************************************
����������void show_ADC_Data(void)
����  �ܡ�OLED��ʾ��Ӧ��ѹ
������ֵ����
������ֵ����
****************************************************************/
void show_ADC_Data(void){
	
	  char txt[10];
		OLED_CLS(); 
	
		sprintf(txt,"AD0:%04d ",ADC_Data[0]);  //��ʾADC11��ֵ
		OLED_P6x8Str(0,0,(u8*)txt);
	
		sprintf(txt,"AD1:%04d ",ADC_Data[1]);  //��ʾADC11��ֵ
		OLED_P6x8Str(0,1,(u8*)txt);
	
		sprintf(txt,"AD2:%04d ",ADC_Data[2]);  //��ʾADC11��ֵ
		OLED_P6x8Str(0,2,(u8*)txt);
	
		sprintf(txt,"AD3:%04d ",ADC_Data[3]);  //��ʾADC11��ֵ
		OLED_P6x8Str(0,3,(u8*)txt);
	
		sprintf(txt,"AD4:%04d ",ADC_Data[4]);  //��ʾADC11��ֵ
		OLED_P6x8Str(0,4,(u8*)txt);
	

	
		delayms(40);
	
}

//�����ֵΪ  1657
//����·�м�ʱ �ĵ��ֵ	 					ǰ��	 ǰ��	 ����	 ����	 ǰ��
//static int16_t ADC_Center[5] = {2411, 1717, 2218, 2344, 1599};
int fx = 0;  //1��   2��
void Servor_Control(int16_t adc[5]){

	//�ڶ���˼· ����ǰ�� ǰ�� �������������źŽ����ж�  һ��ʼ���ǰ�д�������ֵΪ2411
	//�������ֵȥ�жϵ�ǰƫ���˵�·����ƫ���˶�Զ
	//Ӧ���ǿ���ʵ�ֵ��� û�м�PID���� �����Ƿǳ��� ������ֱ��
	int16_t error;
	short pwm_out;
	//ƫ�� = ǰ�� - ǰ��
	//error = dc[1] - adc[4]; //�������� ���ֲ��� ת��̫�� �ú�� 2 ��
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

	//��һ��˼· ����4����������ƫ�Ʒ����жϳ�����̬ ���� ���ѵ��� ��Ҫ�ĵ����Ĳ���̫��
	/*
	int16_t qzhong = 0, qzhong_flag = 0;
	int16_t qzuo   = 0, qzuo_flag 	= 0;
	int16_t hzuo   = 0,	hzuo_flag 	= 0;
	int16_t hyou   = 0,	hyou_flag 	= 0;
	int16_t qyou   = 0, qyou_flag		= 0;
	
	// ���ݲ�ֵ �жϳ���ǰ�����
	qzuo = adc[1] - ADC_Center[1];
	hzuo = adc[2] - ADC_Center[2];
	hyou = adc[3] - ADC_Center[3];
	qyou = adc[4] - ADC_Center[4];
	
	if(qzuo > 0) qzuo_flag = 2; else {qzuo_flag = 1; qzuo =- qzuo;}
	if(hzuo > 0) hzuo_flag = 2; else {hzuo_flag = 1; hzuo =- hzuo;}
	if(hyou > 0) hyou_flag = 1; else {hyou_flag = 2; hyou =- hyou;}
	if(qyou > 0) qyou_flag = 1; else {qyou_flag = 2; qyou =- qyou;}
	
	//���� ƫ�� ���������
	if(qzuo_flag == 2 && hzuo_flag == 2 && hyou_flag == 2 && qyou_flag == 2){
		Duty_Servor_Center	= Duty_Servor_Center + (qzuo + hzuo) * 0.005;
		ServoCtrl(Duty_Servor_Center);
	}
	
	//���� ƫ�� ������Ҵ��
	if(qzuo_flag == 1 && hzuo_flag == 1 && hyou_flag == 1 && qyou_flag == 1){
		Duty_Servor_Center	= Duty_Servor_Center - (qzuo + hzuo) * 0.005;
		ServoCtrl(Duty_Servor_Center);
	}
	*/
}









