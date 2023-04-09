/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��10��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��AURIX Development Studio1.2.2�����ϰ汾
��Target �� TC264DA/TC264D
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·����
����CIFΪTC264DA�����⣬�����Ĵ������TC264D
����Ĭ�ϳ�ʼ����EMEM��512K������û�ʹ��TC264D��ע�͵�EMEM_InitConfig()��ʼ��������
������\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c��164�����ҡ�
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#include "LQ_I2C_MPU9250.h"

/**
* @brief    ��ʼ��MPU9250
*
* @param    ��
*
* @return   0����ʼ���ɹ�   1��ʧ��
*
* @note     ʹ��ǰ�ȳ�ʼ��IIC�ӿ�
*
* @see      MPU9250_Init();
*
* @date     2020/12/15 ���ڶ�
*/
void MPU9250_Init(void)
{
  IIC_Init();                                           //MPU9250 ֧��400K IIC  

  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU9250
  delayms(100);  //��ʱ100ms
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//����MPU9250
  MPU9250_Set_Gyro_Fsr(3);                                //�����Ǵ�����,��2000dps
  MPU9250_Set_Accel_Fsr(1);                               //���ٶȴ�����,��4g
  MPU9250_Set_Rate(1000);                                 //���ò�����1000Hz
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //�ر������ж�
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,0x02);      //�������ֵ�ͨ�˲���   98hz
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2C��ģʽ�ر�
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);  //�ر�FIFO
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);//INT���ŵ͵�ƽ��Ч������bypassģʽ
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);//����CLKSEL,PLL X��Ϊ�ο�
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);//���ٶ��������Ƕ�����
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
* @see      MPU9250_Set_Gyro_Fsr(3);		  //�����Ǵ�����,��2000dps
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Set_Gyro_Fsr(uint8 fsr)
{
  return MPU9250_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3);
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
* @see      MPU9250_Set_Accel_Fsr(1);		  //���ٶȴ�����,��4g
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Set_Accel_Fsr(uint8 fsr)
{
  return MPU9250_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
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
* @see      MPU9250_Set_LPF(100);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Set_LPF(unsigned short lpf)
{
  unsigned char  lqdat=0;
  
  if(lpf>=188)lqdat=1;
  else if(lpf>=98)lqdat=2;
  else if(lpf>=42)lqdat=3;
  else if(lpf>=20)lqdat=4;
  else if(lpf>=10)lqdat=5;
  else lqdat=6;
  return MPU9250_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,lqdat);//�������ֵ�ͨ�˲���
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
* @see      MPU9250_Set_Rate(1000);       	   //���ò�����1000Hz
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Set_Rate(unsigned short rate)
{
  unsigned char  lqdat;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  lqdat = 1000/rate-1;
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,lqdat);	    //�������ֵ�ͨ�˲���
  return MPU9250_Set_LPF(rate/2);	                                //�Զ�����LPFΪ�����ʵ�һ��
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
* @see      signed short temp = MPU9250_Get_Temperature();
*
* @date     2020/12/10 ������
*/
short MPU9250_Get_Temperature(void)
{
  unsigned char  buf[2];
  short raw;
  float temp;
  MPU9250_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf);
  raw=((unsigned short)buf[0]<<8)|buf[1];
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
* @see      signed short lqdat[3];
* @see      MPU9250_Get_Gyroscope(&lqdat[0], &lqdat[1], &lqdat[2]);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Get_Gyroscope(signed short *gx,signed short *gy,signed short *gz)
{
  unsigned char  buf[6],res;
  res=MPU9250_Read_Len(MPU9250_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
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
* @see      signed short lqdat[3];
* @see      MPU9250_Get_Accelerometer(&lqdat[0], &lqdat[1], &lqdat[2]);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Get_Accelerometer(signed short *ax,signed short *ay,signed short *az)
{
  unsigned char  buf[6],res;
  res=MPU9250_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
  if(res==0)
  {
    *ax=((unsigned short)buf[0]<<8)|buf[1];
    *ay=((unsigned short)buf[2]<<8)|buf[3];
    *az=((unsigned short)buf[4]<<8)|buf[5];
  }
  return res;
}


/**
* @brief    ��ȡ������ֵ
*
* @param    mx,my,mz:��������x,y,z���ԭʼ����(������)
*
* @return   0����ȡ�ɹ�
*
* @note     ��
*
* @see      signed short lqdat[3];
* @see      MPU9250_Get_Magnetometer(&lqdat[0], &lqdat[1], &lqdat[2]);
*
* @date     2020/12/15 ���ڶ�
*/
unsigned char MPU9250_Get_Magnetometer(short *mx,short *my,short *mz)
{
  
  unsigned char  buf[6],res;
  res=MPU9250_Read_Len(AK8963_ADDR,MPU_MAG_XOUTL_REG,6,buf);
  if(res==0)
  {
    *mx=((unsigned short)buf[1]<<8)|buf[0];
    *my=((unsigned short)buf[3]<<8)|buf[2];
    *mz=((unsigned short)buf[5]<<8)|buf[4];
  }
  //MPU9250_Write_Byte(AK8963_ADDR,MPU_MAG_CNTL1_REG,0X11);
  MPU9250_Read_Byte(AK8963_ADDR,MPU_MAG_ST2_REG);
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
* @see      signed short lqdat[6];
* @see      MPU9250_Get_Raw_data(&lqdat[0], &lqdat[1], &lqdat[2],&lqdat[3], &lqdat[4], &lqdat[5]);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Get_Raw_data(signed short *ax,signed short *ay,signed short *az,signed short *gx,signed short *gy,signed short *gz)
{
  unsigned char  buf[14],res;
  res=MPU9250_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
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
* @brief    IIC ����д
*
* @param    addr:������ַ
* @param    reg :Ҫд��ļĴ�����ַ
* @param    len :Ҫд��ĳ���
* @param    buf :д�뵽�����ݴ洢��
*
* @return   0 ��д��ɹ�
*
* @note     �ײ����� ��ֲʱ��Ҫ�޸�
*
* @see      unsigned char buf[14];
* @see      MPU9250_Write_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Write_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
  return IIC_WriteMultByteToSlave(addr<<1, reg, len, buf);
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
* @see      MPU9250_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Read_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
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
* @see      MPU9250_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,1);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Write_Byte(unsigned char addr,unsigned char reg,unsigned char value)
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
* @see      MPU9250_Read_Byte(MPU9250_ADDR,WHO_AM_I);
*
* @date     2020/12/10 ������
*/
unsigned char MPU9250_Read_Byte(unsigned char addr,unsigned char reg)
{
  unsigned char value[1];
  IIC_ReadByteFromSlave(addr<<1, reg, &value[0]);
  return value[0];
}

// ͨ�����ٶȼƻ�ȡ��������
float MPU9250_Get_Angle(short accx, short accy, short accz, char choose)
{
  double temp;
  float res = 0;
  switch(choose)
  {
  case 0 ://����Ȼx��ĽǶ�
    temp = (float)accx / sqrt( (accy * accy + accz * accz) );
    res = atan(temp);
    break;
  case 1 ://����Ȼy��ĽǶ�
    temp = (float)accy / sqrt((accx * accx + accz * accz));
    res = atan(temp);
    break;
  case 2 ://����Ȼz��ĽǶ�
    temp = (float)accz / sqrt(accx * accx + accy * accy);
    res = atan(temp);
    break;
  }
  return res * 1800 / 3.1415;
}



//���Գ���
//��λΪ0.1����ÿ��
void Test_MPU9250(void)
{
  char txt[30];
  short aacx, aacy, aacz;
  short gyrox, gyroy, gyroz;
  short magx, magy, magz;	
  
  MPU9250_Set_LPF(10);  
  //UART_PutStr(//UART0,"LQ MPU9250 Test\r\n");
  MPU9250_Init(); 
  
  while(1)
  {
    MPU9250_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);   //�õ����ٶȴ���������
    MPU9250_Get_Magnetometer(&magx, &magy, &magz);
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
    /*
    ////UART_PutBuff(//UART0, ch, 12);
    ANO_DT_sendOnebyte_int16(0xF1, (short)aacx-450);
    ANO_DT_sendOnebyte_int16(0xF2, (short)aacy-140);
    ANO_DT_sendOnebyte_int16(0xF3, (short)aacz);
    ANO_DT_sendOnebyte_int16(0xF4, (short)gyrox);
    ANO_DT_sendOnebyte_int16(0xF5, (short)gyroy);
    ANO_DT_sendOnebyte_int16(0xF6, (short)gyroz);
    */
  }
}



