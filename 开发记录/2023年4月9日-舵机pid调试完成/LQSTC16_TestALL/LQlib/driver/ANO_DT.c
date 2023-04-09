/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技STC16核心板
【编    写】chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2021年1月25日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【IDE】STC16
【Target 】 C251Keil5.57及以上
【SYS PLL】 30MHz使用内部晶振
=================================================================
STC16相关配套视频：
龙邱科技B站网址：https://space.bilibili.com/95313236
STC16环境下载参考视频： https://www.bilibili.com/video/BV1gy4y1p7T1/
STC16一体板子介绍视频： https://www.bilibili.com/video/BV1Jy4y1e7R4/
=================================================================
下载时, 选择时钟 30MHZ (用户可自行修改频率).
STC16F初次下载:先用IRCBND=0，ISP界面设置为24M，
芯片最后一行2038...然后IRCBND=0，下载频率为30M；
芯片最后一行2010...或者IRCBND=1，下载频率为30M；
官方出库批次不同，略有差异，好用为准！！！
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ

配合匿名地面站上位机

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include <LQ_UART.h>
#include <ANO_DT.h>

//使用匿名4.3上位机协议
/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )     /*!< uint32_t 数据拆分 byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t 数据拆分 byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t 数据拆分 byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t 数据拆分 byte3  */

/*!
  * @brief    Send_Data函数是协议中所有发送数据功能使用到的发送函数
  *
  * @param    dataToSend   :   要发送的数据首地址
  * @param    length       :   要发送的数据长度
  *
  * @return   无
  *
  * @note     移植时，用户应根据自身应用的情况，根据使用的通信方式，实现此函数
  *
  * @see      内部调用
  *
  * @date     2019/5/28 星期二
  */
void ANO_DT_Send_Data(unsigned char *dataToSend , unsigned short length)
{

    /**使用串口正常发送数据，大概需要1.5ms*/
	//UART4_PutBuff(dataToSend, length);     //可以修改不同的串口发送数据

}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【函数名】void UART4_SendInt16(unsigned char Function, int outData)
【功  能】匿名上位机用户协议，使用时占用MCU资源较大，跑车时不使用
【参数值】unsigned char Function, 功能字符
【参数值】int outData 数据
【返回值】无 
【作  者】chiusir
【最后更新】2021年1月22日 
【软件版本】V1.0
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
//void UART4_SendInt16(unsigned char Function, int outData)
//{
//	unsigned char sum;
//	unsigned char outData_H = ((unsigned short)outData)>>8;
//	unsigned char outData_L = (unsigned char)outData;
//	S4BUF = (0xAA);   // 头
//	delayus(90);
//	S4BUF = (0xAA);   // 头
//	delayus(90);
//	S4BUF = Function; // 功能
//	delayus(90);
//	S4BUF = (0x02);   // 数据为两个字节
//	delayus(90);
//	S4BUF = outData_H;// 数据高8位
//	delayus(90);
//	S4BUF = outData_L;// 数据低8位
//	delayus(90);
//	sum = 0xAA | 0xAA | 0xF1 | 0x02 | outData_H | outData_L;// 校验值
//	S4BUF = sum;
//	delayus(90);
//}

void UART4_SendInt16(int outData1, int outData2, int outData3, int outData4, int outData5, int outData6, int outData7, int outData8)
{
	unsigned char sum;
//	unsigned char outData_H = ((unsigned short)outData)>>8;
//	unsigned char outData_L = (unsigned char)outData;
	S4BUF = (0xAA);   // 头
	delayus(90);
	S4BUF = (0xAA);   // 头
	delayus(90);
	S4BUF = 0xf1; // 功能
	delayus(90);
	S4BUF = (0x0f);   // 数据为16个字节
	delayus(90);
	S4BUF = ((unsigned short)outData1)>>8;   // 数据高8位
	delayus(90);
	S4BUF = (unsigned char)outData1;         // 数据低8位
	delayus(90);
	S4BUF = ((unsigned short)outData2)>>8;
	delayus(90);
	S4BUF = (unsigned char)outData2;
	delayus(90);
	S4BUF = ((unsigned short)outData3)>>8;
	delayus(90);
	S4BUF = (unsigned char)outData3;
	delayus(90);
	S4BUF = ((unsigned short)outData4)>>8;
	delayus(90);
	S4BUF = (unsigned char)outData4;
	delayus(90);
	S4BUF = ((unsigned short)outData5)>>8;
	delayus(90);
	S4BUF = (unsigned char)outData5;
	delayus(90);
	S4BUF = ((unsigned short)outData6)>>8;
	delayus(90);
	S4BUF = (unsigned char)outData6;
	delayus(90);
	S4BUF = ((unsigned short)outData7)>>8;
	delayus(90);
	S4BUF = (unsigned char)outData7;
	delayus(90);
	S4BUF = ((unsigned short)outData8)>>8;
	delayus(90);
	S4BUF = (unsigned char)outData8;
	delayus(90);
	
	sum = 0xAA | 0xAA | 0xF1 | 0x02;// 校验值
//	sum = sum | ((unsigned short)outData1)>>8 | (unsigned char)outData1 | ((unsigned short)outData2)>>8 | (unsigned char)outData2;
//	sum = sum | ((unsigned short)outData3)>>8 | (unsigned char)outData3 | ((unsigned short)outData4)>>8 | (unsigned char)outData4;
//	sum = sum | ((unsigned short)outData5)>>8 | (unsigned char)outData5 | ((unsigned short)outData6)>>8 | (unsigned char)outData6;
//	sum = sum | ((unsigned short)outData7)>>8 | (unsigned char)outData7 | ((unsigned short)outData8)>>8 | (unsigned char)outData8;
	S4BUF = sum;
	delayus(90);
}


