/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】ZYF/chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年10月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】AURIX Development Studio1.2.2及以上版本
【Target 】 TC264DA/TC264D
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，
除了CIF为TC264DA独有外，其它的代码兼容TC264D
本库默认初始化了EMEM：512K，如果用户使用TC264D，注释掉EMEM_InitConfig()初始化函数。
工程下\Libraries\iLLD\TC26B\Tricore\Cpu\CStart\IfxCpu_CStart0.c第164行左右。
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
#include "LQ_I2C_MPU9250.h"

/**
* @brief    初始化MPU9250
*
* @param    无
*
* @return   0：初始化成功   1：失败
*
* @note     使用前先初始化IIC接口
*
* @see      MPU9250_Init();
*
* @date     2020/12/15 星期二
*/
void MPU9250_Init(void)
{
  IIC_Init();                                           //MPU9250 支持400K IIC  

  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU9250
  delayms(100);  //延时100ms
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//唤醒MPU9250
  MPU9250_Set_Gyro_Fsr(3);                                //陀螺仪传感器,±2000dps
  MPU9250_Set_Accel_Fsr(1);                               //加速度传感器,±4g
  MPU9250_Set_Rate(1000);                                 //设置采样率1000Hz
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //关闭所有中断
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,0x02);      //设置数字低通滤波器   98hz
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2C主模式关闭
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);  //关闭FIFO
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);//INT引脚低电平有效，开启bypass模式
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);//设置CLKSEL,PLL X轴为参考
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);//加速度与陀螺仪都工作
}

/**
* @brief    设置陀螺仪测量范围
*
* @param    fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
*
* @return   0 ：设置成功
*
* @note     无
*
* @see      MPU9250_Set_Gyro_Fsr(3);		  //陀螺仪传感器,±2000dps
*
* @date     2020/12/10 星期四
*/
unsigned char MPU9250_Set_Gyro_Fsr(uint8 fsr)
{
  return MPU9250_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3);
}



/**
* @brief    设置加速度计测量范围
*
* @param    fsr:0,±2g;1,±4g;2,±8g;3,±16g
*
* @return   0：设置成功
*
* @note     无
*
* @see      MPU9250_Set_Accel_Fsr(1);		  //加速度传感器,±4g
*
* @date     2020/12/10 星期四
*/
unsigned char MPU9250_Set_Accel_Fsr(uint8 fsr)
{
  return MPU9250_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);
}



/**
* @brief    设置数字低通滤波
*
* @param    lpf:数字低通滤波频率(Hz)
*
* @return   0：设置成功
*
* @note     无
*
* @see      MPU9250_Set_LPF(100);
*
* @date     2020/12/10 星期四
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
  return MPU9250_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,lqdat);//设置数字低通滤波器
}




/**
* @brief    设置采样率
*
* @param    rate:4~1000(Hz)
*
* @return   0：设置成功
*
* @note     无
*
* @see      MPU9250_Set_Rate(1000);       	   //设置采样率1000Hz
*
* @date     2020/12/10 星期四
*/
unsigned char MPU9250_Set_Rate(unsigned short rate)
{
  unsigned char  lqdat;
  if(rate>1000)rate=1000;
  if(rate<4)rate=4;
  lqdat = 1000/rate-1;
  MPU9250_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,lqdat);	    //设置数字低通滤波器
  return MPU9250_Set_LPF(rate/2);	                                //自动设置LPF为采样率的一半
}



/**
* @brief    获取温度值
*
* @param    无
*
* @return   温度值(扩大了100倍)
*
* @note     无
*
* @see      signed short temp = MPU9250_Get_Temperature();
*
* @date     2020/12/10 星期四
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
* @brief    获取陀螺仪值
*
* @param    gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
*
* @return   0：读取成功
*
* @note     无
*
* @see      signed short lqdat[3];
* @see      MPU9250_Get_Gyroscope(&lqdat[0], &lqdat[1], &lqdat[2]);
*
* @date     2020/12/10 星期四
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
* @brief    获取加速度值
*
* @param    ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
*
* @return   0：读取成功
*
* @note     无
*
* @see      signed short lqdat[3];
* @see      MPU9250_Get_Accelerometer(&lqdat[0], &lqdat[1], &lqdat[2]);
*
* @date     2020/12/10 星期四
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
* @brief    获取磁力计值
*
* @param    mx,my,mz:磁力计仪x,y,z轴的原始读数(带符号)
*
* @return   0：读取成功
*
* @note     无
*
* @see      signed short lqdat[3];
* @see      MPU9250_Get_Magnetometer(&lqdat[0], &lqdat[1], &lqdat[2]);
*
* @date     2020/12/15 星期二
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
* @brief    获取 加速度值 角速度值
*
* @param    ax,ay,az:陀螺仪x,y,z轴的原始读数(带符号)
* @param    gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
*
* @return   0：读取成功
*
* @note     无
*
* @see      signed short lqdat[6];
* @see      MPU9250_Get_Raw_data(&lqdat[0], &lqdat[1], &lqdat[2],&lqdat[3], &lqdat[4], &lqdat[5]);
*
* @date     2020/12/10 星期四
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
* @brief    IIC 连续写
*
* @param    addr:器件地址
* @param    reg :要写入的寄存器地址
* @param    len :要写入的长度
* @param    buf :写入到的数据存储区
*
* @return   0 ：写入成功
*
* @note     底层驱动 移植时需要修改
*
* @see      unsigned char buf[14];
* @see      MPU9250_Write_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
*
* @date     2020/12/10 星期四
*/
unsigned char MPU9250_Write_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
  return IIC_WriteMultByteToSlave(addr<<1, reg, len, buf);
}


/**
* @brief    IIC 连续读
*
* @param    addr:器件地址
* @param    reg :要读取的寄存器地址
* @param    len :要读取的长度
* @param    buf :读取到的数据存储区
*
* @return   0 ：读取成功
*
* @note     底层驱动 移植时需要修改
*
* @see      unsigned char buf[14];
* @see      MPU9250_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,14,buf);
*
* @date     2020/12/10 星期四
*/
unsigned char MPU9250_Read_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf)
{
  return IIC_ReadMultByteFromSlave(addr<<1, reg, len, buf);
}



/**
* @brief    IIC 写一个寄存器
*
* @param    addr  :器件地址
* @param    reg   :寄存器地址
* @param    value :要写入的值
*
* @return   0 ：读取成功
*
* @note     底层驱动 移植时需要修改
*
* @see      MPU9250_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,1);
*
* @date     2020/12/10 星期四
*/
unsigned char MPU9250_Write_Byte(unsigned char addr,unsigned char reg,unsigned char value)
{
  return IIC_WriteByteToSlave(addr<<1, reg, value);
}


/**
* @brief    IIC 读一个寄存器
*
* @param    addr  :器件地址
* @param    reg   :寄存器地址
*
* @return   读取的值
*
* @note     底层驱动 移植时需要修改
*
* @see      MPU9250_Read_Byte(MPU9250_ADDR,WHO_AM_I);
*
* @date     2020/12/10 星期四
*/
unsigned char MPU9250_Read_Byte(unsigned char addr,unsigned char reg)
{
  unsigned char value[1];
  IIC_ReadByteFromSlave(addr<<1, reg, &value[0]);
  return value[0];
}

// 通过加速度计获取绝对坐标
float MPU9250_Get_Angle(short accx, short accy, short accz, char choose)
{
  double temp;
  float res = 0;
  switch(choose)
  {
  case 0 ://与自然x轴的角度
    temp = (float)accx / sqrt( (accy * accy + accz * accz) );
    res = atan(temp);
    break;
  case 1 ://与自然y轴的角度
    temp = (float)accy / sqrt((accx * accx + accz * accz));
    res = atan(temp);
    break;
  case 2 ://与自然z轴的角度
    temp = (float)accz / sqrt(accx * accx + accy * accy);
    res = atan(temp);
    break;
  }
  return res * 1800 / 3.1415;
}



//测试程序
//单位为0.1毫米每秒
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
    MPU9250_Get_Raw_data(&aacx,&aacy,&aacz,&gyrox,&gyroy,&gyroz);   //得到加速度传感器数据
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



