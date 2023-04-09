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
#ifndef __LQ_9250_H_
#define __LQ_9250_H_


//AD0���Ž���GND����ַΪ0x68
#define MPU9250_ADDR    0x68  //MPU6500��������ַ
#define MPU6500_ID1     0x71  //MPU6500������ID1
#define MPU6500_ID2     0x73  //MPU6500������ID1

//MPU9250�ڲ���װ��һ��AK8963
#define AK8963_ADDR     0x0C    //AK8963��I2C��ַ
#define AK8963_ID       0x48    //AK8963������ID
//****************************************
// ����MPU9250�ڲ���ַ
//****************************************
//AK8963���ڲ��Ĵ���
#define MPU_MAG_WIA                 0X00    //AK8963������ID�Ĵ�����ַ

#define MPU_MAG_XOUTL_REG           0X03    //������ֵ,X���8λ�Ĵ���
#define MPU_MAG_XOUTH_REG           0X04    //������ֵ,X���8λ�Ĵ���
#define MPU_MAG_YOUTL_REG           0X05    //������ֵ,Y���8λ�Ĵ���
#define MPU_MAG_YOUTH_REG           0X06    //������ֵ,Y���8λ�Ĵ���
#define MPU_MAG_ZOUTL_REG           0X07    //������ֵ,Z���8λ�Ĵ���
#define MPU_MAG_ZOUTH_REG           0X08    //������ֵ,Z���8λ�Ĵ���

#define MPU_MAG_ST1_REG             0X02    //�����ƶ�ȡ״̬
#define MPU_MAG_ST2_REG             0X09    //�����ƶ�ȡ״̬
#define MPU_MAG_CNTL1_REG           0X0A    //������ģʽ����
#define MPU_MAG_CNTL2_REG           0X0B    //������ģʽ����

//MPU6500���ڲ��Ĵ���
#define MPU_SELF_TESTX_GYRO_REG     0X00    //������X���Լ�Ĵ���
#define MPU_SELF_TESTY_GYRO_REG     0X01    //������Y���Լ�Ĵ���
#define MPU_SELF_TESTZ_GYRO_REG     0X02    //������Z���Լ�Ĵ���

#define MPU_SELF_TESTX_ACCEL_REG    0X0D    //���ٶȼ��Լ�Ĵ���X
#define MPU_SELF_TESTY_ACCEL_REG    0X0E	 //���ٶȼ��Լ�Ĵ���Y
#define MPU_SELF_TESTZ_ACCEL_REG    0X0F	 //���ٶȼ��Լ�Ĵ���Z
#define MPU_SAMPLE_RATE_REG         0X19	 //����Ƶ�ʷ�Ƶ��
#define MPU_CFG_REG		         0X1A	 //���üĴ���
#define MPU_GYRO_CFG_REG		     0X1B	 //���������üĴ���
#define MPU_ACCEL_CFG_REG		     0X1C	 //���ٶȼ����üĴ���
#define MPU_MOTION_DET_REG		    0X1F	//�˶���ֵⷧ���üĴ���
#define MPU_FIFO_EN_REG	         0X23	 //FIFOʹ�ܼĴ���

#define MPU_I2CMST_STA_REG		     0X36	//IIC����״̬�Ĵ���
#define MPU_INTBP_CFG_REG           0X37	//�ж�/��·���üĴ���
#define MPU_INT_EN_REG			     0X38	//�ж�ʹ�ܼĴ���
#define MPU_INT_STA_REG	         0X3A	//�ж�״̬�Ĵ���

#define MPU_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define MPU_TEMP_OUTH_REG		    0X41	//�¶�ֵ�߰�λ�Ĵ���
#define MPU_TEMP_OUTL_REG		    0X42	//�¶�ֵ��8λ�Ĵ���

#define MPU_GYRO_XOUTH_REG		    0X43	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_XOUTL_REG		    0X44	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_YOUTH_REG		    0X45	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_YOUTL_REG		    0X46	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_ZOUTH_REG		    0X47	//������ֵ,Z���8λ�Ĵ���
#define MPU_GYRO_ZOUTL_REG		    0X48	//������ֵ,Z���8λ�Ĵ���

#define MPU_I2CSLV0_DO_REG		    0X63	//IIC�ӻ�0���ݼĴ���
#define MPU_I2CSLV1_DO_REG		    0X64	//IIC�ӻ�1���ݼĴ���
#define MPU_I2CSLV2_DO_REG		    0X65	//IIC�ӻ�2���ݼĴ���
#define MPU_I2CSLV3_DO_REG		    0X66	//IIC�ӻ�3���ݼĴ���

#define MPU_I2CMST_DELAY_REG	    0X67	//IIC������ʱ����Ĵ���
#define MPU_SIGPATH_RST_REG        0X68	//�ź�ͨ����λ�Ĵ���
#define MPU_MDETECT_CTRL_REG	    0X69	//�˶������ƼĴ���
#define MPU_USER_CTRL_REG		    0X6A	//�û����ƼĴ���
#define MPU_PWR_MGMT1_REG		    0X6B	//��Դ����Ĵ���1
#define MPU_PWR_MGMT2_REG		    0X6C	//��Դ����Ĵ���2
#define MPU_FIFO_CNTH_REG		    0X72	//FIFO�����Ĵ����߰�λ
#define MPU_FIFO_CNTL_REG		    0X73	//FIFO�����Ĵ����Ͱ�λ
#define MPU_FIFO_RW_REG	        0X74	//FIFO��д�Ĵ���
#define WHO_AM_I		            0X75	//����ID�Ĵ���

extern void Test_MPU9250(void);
void MPU9250_Init(void);
unsigned char MPU9250_WaitForReady(unsigned char addr);
unsigned char MPU9250_Write_Byte(unsigned char addr,unsigned char reg,unsigned char lqdat);
unsigned char MPU9250_Read_Byte(unsigned char addr,unsigned char reg);
unsigned char MPU9250_Set_Gyro_Fsr(unsigned char fsr);
unsigned char MPU9250_Set_Accel_Fsr(unsigned char fsr);
unsigned char MPU9250_Set_Rate(unsigned short rate);
unsigned char MPU9250_Write_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf);
unsigned char MPU9250_Read_Len(unsigned char addr,unsigned char reg,unsigned char len,unsigned char *buf);
short MPU9250_Get_Temperature(void);
unsigned char MPU9250_Get_Gyroscope(signed short *gx,signed short *gy,signed short *gz);
unsigned char MPU9250_Get_Accelerometer(signed short *ax,signed short *ay,signed short *az);
unsigned char MPU9250_Get_Magnetometer(short *mx,short *my,short *mz);
unsigned char MPU9250_Get_Raw_data(signed short *ax,signed short *ay,signed short *az,signed short *gx,signed short *gy,signed short *gz);
float MPU9250_Get_Angle(short accx, short accy, short accz, char choose);

void mget_ms(unsigned long *count);

#endif

