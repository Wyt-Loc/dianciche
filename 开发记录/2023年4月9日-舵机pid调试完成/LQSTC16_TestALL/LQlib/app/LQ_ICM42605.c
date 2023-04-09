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
=================================================================
����������Ƶ��ַ��https://space.bilibili.com/95313236
����ʱ, ѡ��ʱ�� 30MHZ (�û��������޸�Ƶ��).
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

#define USE_SOFT_SPI //ʹ��ģ��SPI,����ʹ��Ӳ��SPI


/*************************************************************************
*  �������ƣ�void ICM_Get_Gyroscope(short *gx,short *gy,short *gz)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Get_Gyroscope(short *gx,short *gy,short *gz)
{
  unsigned char buf[7]; 
  ICM_Read_Len(ICM_GYRO_XOUTH_REG,buf,6);
  
  *gx=((uint16_t)buf[1]<<8)|buf[2];  
  *gy=((uint16_t)buf[3]<<8)|buf[4];  
  *gz=((uint16_t)buf[5]<<8)|buf[6];
  
}
/*************************************************************************
*  �������ƣ�void ICM_Get_Accelerometer(short *ax,short *ay,short *az)
*  ����˵����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Get_Accelerometer(short *ax,short *ay,short *az)
{
  unsigned char buf[7];  
  ICM_Read_Len(ICM_ACCEL_XOUTH_REG,buf,6);
  
  *ax=((uint16_t)buf[1]<<8)|buf[2];  
  *ay=((uint16_t)buf[3]<<8)|buf[4];  
  *az=((uint16_t)buf[5]<<8)|buf[6];  
}

/*************************************************************************
*  �������ƣ�void ICM_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz)
*  ����˵������ȡ���ٶ�����������
*  ����˵��������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Get_Raw_data(short *ax,short *ay,short *az,short *gx,short *gy,short *gz)
{
  unsigned char buf[14];  
  ICM_Read_Len(ICM_ACCEL_XOUTH_REG,buf,12);
  
  *ax=((uint16_t)buf[1]<<8)|buf[2];  
  *ay=((uint16_t)buf[3]<<8)|buf[4];  
  *az=((uint16_t)buf[5]<<8)|buf[6];
  *gx=((uint16_t)buf[7]<<8)|buf[8];  
  *gy=((uint16_t)buf[9]<<8)|buf[10];  
  *gz=((uint16_t)buf[11]<<8)|buf[12];  
}
/*************************************************************************
*  �������ƣ�void ICM_Write_Byte(unsigned char reg,unsigned char value)
*  ����˵������Ĵ���д����
*  ����˵����unsigned char reg�Ĵ���,unsigned char value����
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Write_Byte(unsigned char reg,unsigned char value)
{
#ifdef USE_SOFT_SPI
  unsigned char buff[2];  
  buff[0] = reg;          				//�ȷ��ͼĴ���
  buff[1] = value;       				  //�ٷ�������  
  Soft_SPI_ReadWriteNbyte(buff, 2);//����buff�����ݣ����ɼ��� buff��  
  
#else
  SPI_CS=0;
  SPI_WriteByte(reg|0x80);
  SPI_WriteByte(value);
  SPI_CS=1;
#endif
}

/*************************************************************************
*  �������ƣ�void ICM_Write_Byte(unsigned char reg,unsigned char value)
*  ����˵������Ĵ���д����
*  ����˵����unsigned char reg�Ĵ���,
*  �������أ�unsigned char value����
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
unsigned char ICM_Read_Byte(unsigned char reg)
{  
  unsigned char buff[2];
#ifdef USE_SOFT_SPI
  buff[0] = reg | 0x80;    //�ȷ��ͼĴ���  
  Soft_SPI_ReadWriteNbyte(buff, 2);   
  return buff[1];
#else
  SPI_CS=0;
  SPI_WriteByte(reg| 0x80);  
  buff[0]=SPI_ReadByte();
  SPI_CS=1;
  return buff[0];
#endif 
  
}

/*************************************************************************
*  �������ƣ�void ICM_Read_Len(unsigned char reg,unsigned char len,unsigned char *buf)
*  ����˵����unsigned char reg��ʼ�Ĵ���,unsigned char *buf����ָ��,u16 len����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void ICM_Read_Len(unsigned char reg,unsigned char *buf,unsigned char len)
{  
#ifdef USE_SOFT_SPI
  buf[0] = reg | 0x80;  
  Soft_SPI_ReadWriteNbyte(buf, len + 1);  
#else
  SPI_Read_Nbytes(reg|0x80, buf, len);
#endif
}
/*************************************************************************
*  �������ƣ�unsigned char ICM42605_Init(void)
*  ����˵����ICM42605��ʼ��
*  ����˵������
*  �������أ�0 �ɹ���1ʧ��
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
unsigned char ICM42605_Init(void)
{   
  unsigned char lqv;
  char  txt[30];
  
  Soft_SPI_Init(); 
  delayms(200);  
  
  lqv = ICM_Read_Byte(WHO_AM_I);//WHO_AM_I
  sprintf(txt,"ID:0x%02X",lqv);
  OLED_P8x16Str(66,2,(unsigned char*)txt);
  
  ICM_Write_Byte(reg_bank_sel,0x00);//Set to bank 0
  ICM_Write_Byte(reg_bank_sel,0x00);//Set to bank 0
  ICM_Write_Byte(device_config_reg,bit_soft_reset_chip_config);//chip soft reset
  delayms(100);  
  
  if(lqv==0x42)
  {
    ICM_Write_Byte(reg_bank_sel,0x01);//Change to bank 1
    ICM_Write_Byte(intf_config4,0x02);//4 wire spi mode
    
    ICM_Write_Byte(reg_bank_sel,0x00);        
    ICM_Write_Byte(fifo_config_reg,0x40);//Stream-to-FIFO Mode
    
    lqv = ICM_Read_Byte(int_source0_reg);      
    ICM_Write_Byte(int_source0_reg,0x00);    
    ICM_Write_Byte(fifo_config2_reg,0x00);// watermark
    ICM_Write_Byte(fifo_config3_reg,0x02);// watermark
    ICM_Write_Byte(int_source0_reg, lqv); 
    ICM_Write_Byte(fifo_config1_reg,0x63);// Enable the accel and gyro to the FIFO
    
    ICM_Write_Byte(reg_bank_sel,0x00);
    ICM_Write_Byte(int_config_reg,0x36);   
    
    ICM_Write_Byte(reg_bank_sel, 0x00);
    lqv = (ICM_Read_Byte(int_source0_reg)|bit_int_fifo_ths_int1_en);      
    ICM_Write_Byte(int_source0_reg, lqv);
    
    ICM_Write_Byte(reg_bank_sel, 0x00);
    lqv = ((ICM_Read_Byte(accel_config0_reg)&0x1F)|(bit_accel_ui_fs_sel_8g));//8g
    ICM_Write_Byte(accel_config0_reg, lqv);
    
    ICM_Write_Byte(reg_bank_sel, 0x00);
    lqv = ((ICM_Read_Byte(accel_config0_reg)&0xF0)|bit_accel_odr_50hz);
    ICM_Write_Byte(accel_config0_reg, lqv); 
    
    ICM_Write_Byte(reg_bank_sel, 0x00);
    lqv = ((ICM_Read_Byte(gyro_config0_reg)&0x1F)|(bit_gyro_ui_fs_sel_1000dps));
    ICM_Write_Byte(gyro_config0_reg,lqv);
    
    ICM_Write_Byte(reg_bank_sel, 0x00);      
    lqv = ((ICM_Read_Byte(gyro_config0_reg)&0xF0)|bit_gyro_odr_50hz);
    ICM_Write_Byte(gyro_config0_reg, lqv); 
    
    ICM_Write_Byte(reg_bank_sel, 0x00);
    lqv = ICM_Read_Byte(pwr_mgmt0_reg)|(bit_accel_mode_ln); // Accel on in LNM
    ICM_Write_Byte(pwr_mgmt0_reg, lqv);  
    delayms(1);   
    
    ICM_Write_Byte(reg_bank_sel, 0x00);
    lqv = ICM_Read_Byte(pwr_mgmt0_reg)|(bit_gyro_mode_ln); // Gyro on in LNM
    ICM_Write_Byte(pwr_mgmt0_reg, lqv);  
    delayms(1);   
    //printf("ok");
    OLED_P6x8Str(66,4,(unsigned char*)"Init Pass");
    return 0;
  }
  else 
  {
    OLED_P6x8Str(66,4,(unsigned char*)"Init Fail");
    return 1;
  }   
}

/*************************************************************************
*  �������ƣ�void Test_ICM42605(void)
*  ����˵�������ԣ���ȡ���ٶ�����������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��8��10��
*  ��    ע��   
*************************************************************************/
void Test_ICM42605(void)
{
  unsigned char  txt[30];
  //Sample_data_type_t *lqdat;
  short aacx,aacy,aacz;	        //���ٶȴ�����ԭʼ����
  short gyrox,gyroy,gyroz;        //������ԭʼ����
  UART1_config(1);						  //����
  OLED_Init();                  //LCD��ʼ��
  OLED_CLS();                   //LCD����
  OLED_P8x16Str(15,0,"ICM42605 Test");  
  
  ICM42605_Init();
  
  while(1)
  {
    ICM_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������  
    sprintf((char*)txt,"ax:%06d",aacx);
    OLED_P6x8Str(0,2,txt);
    sprintf((char*)txt,"ay:%06d",aacy);
    OLED_P6x8Str(0,3,txt);
    sprintf((char*)txt,"az:%06d",aacz);
    OLED_P6x8Str(0,4,txt);
    sprintf((char*)txt,"gx:%06d",gyrox);
    OLED_P6x8Str(0,5,txt);
    sprintf((char*)txt,"gy:%06d",gyroy);
    OLED_P6x8Str(0,6,txt);
    sprintf((char*)txt,"gz:%06d",gyroz);
    OLED_P6x8Str(0,7,txt);
		delayms(100);
/*
    printf("\r\nAX: %d  ",aacx); 
    printf("\r\nAY: %d  ",aacy);
    printf("\r\nAZ: %d  ",aacz); 
    printf("\r\nGX: %d  ",gyrox);
    printf("\r\nGY: %d  ",gyroy); 
    printf("\r\nGZ: %d  ",gyroz);
    delayms(100);
    printf("\r\n*********************\n");
*/
  }
  
}


//


