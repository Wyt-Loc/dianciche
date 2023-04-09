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

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_SOFTIIC_H
#define __LQ_SOFTIIC_H

#include "include.h"

// 注意 IIC总线规定，IIC空闲时 SCL和SDA都为高电平 最好外部上拉（一定不能下拉） 
// 模拟 IIC需要注意，IIC地址左移一位 例如MPU6050 模拟就是地址 0xD0 
// 想换用别的IO 直接修改宏定义 SOFT_IIC_SCL_PIN 、 SOFT_IIC_SDA_PIN 即可 
#define SOFT_IIC_SCL_PIN   P25   // 作为 SCL 
#define SOFT_IIC_SDA_PIN   P24   // 作为 SDA 

#define SDA_OUT        ;
#define SDA_IN         ;

#define IIC_SCL_INIT   ;
#define IIC_SDA_INIT   ;

#define IIC_SCL_H      SOFT_IIC_SCL_PIN=1
#define IIC_SCL_L      SOFT_IIC_SCL_PIN=0

#define IIC_SDA_H      SOFT_IIC_SDA_PIN=1
#define IIC_SDA_L      SOFT_IIC_SDA_PIN=0

#define IIC_SDA_READ   P24

void IIC_Start(void);			    //发送IIC开始信号
void IIC_Stop(void);	  	        //发送IIC停止信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
unsigned char IIC_WaitAck(void); 		    //IIC等待ACK信号
void IIC_SendByte(unsigned char data_t);    //IIC发送一个字节
unsigned char IIC_ReadByte(unsigned char ack);      //IIC读取一个字节


void IIC_Init(void);
unsigned char IIC_ReadByteFromSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char *buf);
unsigned char IIC_ReadMultByteFromSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char *data_t);
unsigned char IIC_WriteByteToSlave(unsigned char I2C_Addr,unsigned char reg,unsigned char buf);
unsigned char IIC_WriteMultByteToSlave(unsigned char dev, unsigned char reg, unsigned char length, unsigned char* data_t);

#endif
