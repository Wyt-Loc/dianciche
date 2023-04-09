#ifndef __LQ_ADC_H_
#define __LQ_ADC_H_
#include "include.h"
u16 ADC_Read(uint8_t ADC_Channel_x);
u16 ADC_Read_Average(uint8_t ADC_Channel_x,uint8_t times);
void ADC_Init (void);
void Get_Adc(void);
void InductorNormal(void);
//extern int16_t LnowADC[6];
extern int16_t ad_max[4]; // �°��ӷŵ������궨���ֵ,�ᱻ����ˢ��
extern int16_t ad_min[4]; // �°��Ӿ���Ҫ�궨��Сֵ,�ᱻ����ˢ��
extern int16_t left, right;
#endif