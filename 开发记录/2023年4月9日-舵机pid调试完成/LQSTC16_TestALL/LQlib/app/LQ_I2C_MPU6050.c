/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��4��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Hightec4.9.3/Tasking6.3�����ϰ汾
��Target �� TC264DA
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#include "LQ_I2C_MPU6050.h"
/**
* @brief    ��ȡMPU6050����ICM20602ԭʼ���� ����
*
* @param
*
* @return
*
* @note
*
* @see      Test_MPU6050();
*
* @date     2019/6/12 ������
*/
void Test_MPU6050(void)
{
  char  txt[30];
  signed short  aacx,aacy,aacz;	         //���ٶȴ�����ԭʼ����
  signed short  gyrox,gyroy,gyroz;          //������ԭʼ����
  
  OLED_Init();                          //LCD��ʼ��
  OLED_CLS();                           //LCD����
  IIC_Init();
  
  OLED_P8x16Str(15,0,"LQ 6050 Test");
  
  if(MPU6050_Init())
  {
    OLED_P8x16Str(15,2,"6050 Test Fail \r\n");
    while (1);
  }
  
  while(1)
  {
    MPU_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);	//�õ����ٶȴ���������
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
    
  }
  
}

/**
* @brief    ����ȷ��ʱ
*
* @param    ��
*
* @return   ��
*
* @note     ��
*
* @see      delayms_mpu(100);
*
* @date     2019/4/22 ����һ
*/
void delayms_mpu(unsigned short ms)
{
  while(ms--)
  {
    unsigned short  i = 300;
    while(i--)
    {
      ;
    }
  }
}


/**
* @brief    ��ʼ��MPU6050 ���� ICM20602
*
* @param    ��
*
* @return   0����ʼ���ɹ�   1��ʧ��
*
* @note     ʹ��ǰ�ȳ�ʼ��IIC�ӿ�
*
* @see      MPU6050_Init();
*
* @date     2019/6/12 ������
*/
unsigned char MPU6050_Init(void)
{
  int  res;
  res = MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);           //��ȡMPU6050��ID
  if(res == MPU6050_ID)                                 //����ID��ȷ
  {
    //printf("MPU6050 is OK!\r\n");
  }
  else if(res == 0x12)                                  //ICM20602 ����ID��ȷ
  {
    
    //printf("ICM20602 is OK!\r\n");
  }
  else
  {
    //printf("\r\nThe correct IMU was not detected\r\nPlease check the wiring ID=%X\r\n",res);
    return 1;
  }  
  
  MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU6050
  delayms_mpu(100);  //��ʱ100ms
  MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X00);//����MPU6050
  MPU_Set_Gyro_Fsr(3);					        	   //�����Ǵ�����,��2000dps
  MPU_Set_Accel_Fsr(1);					       	   //���ٶȴ�����,��4g
  MPU_Set_Rate(1000);						       	   //���ò�����1000Hz
  MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
  MPU_Write_Byte(MPU6050_ADDR,MPU_INT_EN_REG,0X00);   //�ر������ж�
  MPU_Write_Byte(MPU6050_ADDR,MPU_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
  MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
  MPU_Write_Byte(MPU6050_ADDR,MPU_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����

  
  return 0;
}




/**
* @brief    ���������ǲ�����Χ
*
* @param    fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
*
* @return   0 �����óɹ�
*
* @note     ��
*
* @see      MPU_Set_Gyro_Fsr(3);		  //�����Ǵ�����,��2000dps
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Set_Gyro_Fsr(unsigned char fsr)
{
  return MPU_Write_Byte(MPU6050_ADDR,MPU_GYRO_CFG_REG,fsr<<3);
}



/**
* @brief    ���ü��ٶȼƲ�����Χ
*
* @param    fsr:0,��2g;1,��4g;2,��8g;3,��16g
*
* @return   0�����óɹ�
*
* @note     ��
*
* @see      MPU_Set_Accel_Fsr(1);		  //���ٶȴ�����,��4g
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Set_Accel_Fsr(unsigned char fsr)
{
  return MPU_Write_Byte(MPU6050_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
}



/**
* @brief    �������ֵ�ͨ�˲�
*
* @param    lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
*
* @return   0�����óɹ�
*
* @note     ��
*
* @see      MPU_Set_LPF(100);
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Set_LPF(unsigned short lpf)
{
  unsigned char  dat=0;
	
  if(lpf>=188)dat=1;
  else if(lpf>=98)dat=2;
  else if(lpf>=42)dat=3;
  else if(lpf>=20)dat=4;
  else if(lpf>=10)dat=5;
  else dat=6;
  return MPU_Write_Byte(MPU6050_ADDR,MPU_CFG_REG,dat);//�������ֵ�ͨ�˲���
}




/**
* @brief    ���ò�����
*
* @param    rate:4~1000(Hz)
*
* @return   0�����óɹ�
*
* @note     ��
*
* @see      MPU_Set_Rate(1000);       	   //���ò�����1000Hz
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Set_Rate(unsigned short rate)
{
  unsigned char  dat;
	
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  dat=1000/rate-1;
  MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,dat);	    //�������ֵ�ͨ�˲���
  return MPU_Set_LPF(rate/2);	                                //�Զ�����LPFΪ�����ʵ�һ��
}



/**
* @brief    ��ȡ�¶�ֵ
*
* @param    ��
*
* @return   �¶�ֵ(������100��)
*
* @note     ��
*
* @see      signed short temp = MPU_Get_Temperature();
*
* @date     2019/6/12 ������
*/
short MPU_Get_Temperature(void)
{
  unsigned char  buf[2];
  short raw;
  float temp;
  MPU_Read_Len(MPU6050_ADDR,MPU_TEMP_OUTH_REG,2,buf);
  raw=((u16)buf[0]<<8)|buf[1];
  temp=21+((double)raw)/333.87;
  return (short)temp*100;
}





/**
* @brief    ��ȡ������ֵ
*
* @param    gx,gy,gz:������x,y,z���ԭʼ����(������)
*
* @return   0����ȡ�ɹ�
*
* @note     ��
*
* @see      signed short data[3];
* @see      MPU_Get_Gyroscope(&data[0], &data[1], &data[2]);
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Get_Gyroscope(signed short *gx,signed short *gy,signed short *gz)
{
  unsigned char  buf[6],res;
  res=MPU_Read_Len(MPU6050_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
  if(res==0)
  {
    *gx=((unsigned short)buf[0]<<8)|buf[1];
    *gy=((unsigned short)buf[2]<<8)|buf[3];
    *gz=((unsigned short)buf[4]<<8)|buf[5];
  }
  return res;
}




/**
* @brief    ��ȡ���ٶ�ֵ
*
* @param    ax,ay,az:������x,y,z���ԭʼ����(������)
*
* @return   0����ȡ�ɹ�
*
* @note     ��
*
* @see      signed short data[3];
* @see      MPU_Get_Accelerometer(&data[0], &data[1], &data[2]);
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Get_Accelerometer(signed short *ax,signed short *ay,signed short *az)
{
  unsigned char  buf[6],res;
  res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
  if(res==0)
  {
    *ax=((unsigned short)buf[0]<<8)|buf[1];
    *ay=((unsigned short)buf[2]<<8)|buf[3];
    *az=((unsigned short)buf[4]<<8)|buf[5];
  }
  return res;
}




/**
* @brief    ��ȡ ���ٶ�ֵ ���ٶ�ֵ
*
* @param    ax,ay,az:������x,y,z���ԭʼ����(������)
* @param    gx,gy,gz:������x,y,z���ԭʼ����(������)
*
* @return   0����ȡ�ɹ�
*
* @note     ��
*
* @see      signed short data[6];
* @see      ICM_Get_Raw_data(&data[0], &data[1], &data[2],&data[3], &data[4], &data[5]);
*
*/
unsigned char MPU_Get_Raw_data(signed short *ax,signed short *ay,signed short *az,signed short *gx,signed short *gy,signed short *gz)
{
  unsigned char  buf[14],res;
  res=MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
  if(res==0)
  {
    *ax=((unsigned short)buf[0]<<8)|buf[1];
    *ay=((unsigned short)buf[2]<<8)|buf[3];
    *az=((unsigned short)buf[4]<<8)|buf[5];
    *gx=((unsigned short)buf[8]<<8)|buf[9];
    *gy=((unsigned short)buf[10]<<8)|buf[11];
    *gz=((unsigned short)buf[12]<<8)|buf[13];
  }
  return res;
}





/**
* @brief    IIC ������
*
* @param    addr:������ַ
* @param    reg :Ҫ��ȡ�ļĴ�����ַ
* @param    len :Ҫ��ȡ�ĳ���
* @param    buf :��ȡ�������ݴ洢��
*
* @return   0 ����ȡ�ɹ�
*
* @note     �ײ����� ��ֲʱ��Ҫ�޸�
*
* @see      unsigned char buf[14];
* @see      MPU_Read_Len(MPU6050_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Read_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
  return IIC_ReadMultByteFromSlave(addr<<1, reg, len, buf);
}



/**
* @brief    IIC дһ���Ĵ���
*
* @param    addr  :������ַ
* @param    reg   :�Ĵ�����ַ
* @param    value :Ҫд���ֵ
*
* @return   0 ����ȡ�ɹ�
*
* @note     �ײ����� ��ֲʱ��Ҫ�޸�
*
* @see      MPU_Write_Byte(MPU6050_ADDR,MPU_SAMPLE_RATE_REG,1);
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Write_Byte(unsigned char addr,unsigned char reg,unsigned char value)
{
  return IIC_WriteByteToSlave(addr<<1, reg, value);
}


/**
* @brief    IIC ��һ���Ĵ���
*
* @param    addr  :������ַ
* @param    reg   :�Ĵ�����ַ
*
* @return   ��ȡ��ֵ
*
* @note     �ײ����� ��ֲʱ��Ҫ�޸�
*
* @see      MPU_Read_Byte(MPU6050_ADDR,WHO_AM_I);
*
* @date     2019/6/12 ������
*/
unsigned char MPU_Read_Byte(unsigned char addr,unsigned char reg)
{
  unsigned char value[1];
  MPU_Read_Len(addr, reg, 1, value);
  return value[0];
}





