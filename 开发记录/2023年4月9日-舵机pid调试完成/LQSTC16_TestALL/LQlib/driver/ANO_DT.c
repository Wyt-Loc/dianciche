/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�STC16���İ�
����    д��chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2021��1��25��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��IDE��STC16
��Target �� C251Keil5.57������
��SYS PLL�� 30MHzʹ���ڲ�����
=================================================================
STC16���������Ƶ��
����Ƽ�Bվ��ַ��https://space.bilibili.com/95313236
STC16�������زο���Ƶ�� https://www.bilibili.com/video/BV1gy4y1p7T1/
STC16һ����ӽ�����Ƶ�� https://www.bilibili.com/video/BV1Jy4y1e7R4/
=================================================================
����ʱ, ѡ��ʱ�� 30MHZ (�û��������޸�Ƶ��).
STC16F��������:����IRCBND=0��ISP��������Ϊ24M��
оƬ���һ��2038...Ȼ��IRCBND=0������Ƶ��Ϊ30M��
оƬ���һ��2010...����IRCBND=1������Ƶ��Ϊ30M��
�ٷ��������β�ͬ�����в��죬����Ϊ׼������
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ

�����������վ��λ��

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include <LQ_UART.h>
#include <ANO_DT.h>

//ʹ������4.3��λ��Э��
/////////////////////////////////////////////////////////////////////////////////////
//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )     /*!< uint32_t ���ݲ�� byte0  */
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )     /*!< uint32_t ���ݲ�� byte1  */
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )     /*!< uint32_t ���ݲ�� byte2  */
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )     /*!< uint32_t ���ݲ�� byte3  */

/*!
  * @brief    Send_Data������Э�������з������ݹ���ʹ�õ��ķ��ͺ���
  *
  * @param    dataToSend   :   Ҫ���͵������׵�ַ
  * @param    length       :   Ҫ���͵����ݳ���
  *
  * @return   ��
  *
  * @note     ��ֲʱ���û�Ӧ��������Ӧ�õ����������ʹ�õ�ͨ�ŷ�ʽ��ʵ�ִ˺���
  *
  * @see      �ڲ�����
  *
  * @date     2019/5/28 ���ڶ�
  */
void ANO_DT_Send_Data(unsigned char *dataToSend , unsigned short length)
{

    /**ʹ�ô��������������ݣ������Ҫ1.5ms*/
	//UART4_PutBuff(dataToSend, length);     //�����޸Ĳ�ͬ�Ĵ��ڷ�������

}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����������void UART4_SendInt16(unsigned char Function, int outData)
����  �ܡ�������λ���û�Э�飬ʹ��ʱռ��MCU��Դ�ϴ��ܳ�ʱ��ʹ��
������ֵ��unsigned char Function, �����ַ�
������ֵ��int outData ����
������ֵ���� 
����  �ߡ�chiusir
�������¡�2021��1��22�� 
������汾��V1.0
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
//void UART4_SendInt16(unsigned char Function, int outData)
//{
//	unsigned char sum;
//	unsigned char outData_H = ((unsigned short)outData)>>8;
//	unsigned char outData_L = (unsigned char)outData;
//	S4BUF = (0xAA);   // ͷ
//	delayus(90);
//	S4BUF = (0xAA);   // ͷ
//	delayus(90);
//	S4BUF = Function; // ����
//	delayus(90);
//	S4BUF = (0x02);   // ����Ϊ�����ֽ�
//	delayus(90);
//	S4BUF = outData_H;// ���ݸ�8λ
//	delayus(90);
//	S4BUF = outData_L;// ���ݵ�8λ
//	delayus(90);
//	sum = 0xAA | 0xAA | 0xF1 | 0x02 | outData_H | outData_L;// У��ֵ
//	S4BUF = sum;
//	delayus(90);
//}

void UART4_SendInt16(int outData1, int outData2, int outData3, int outData4, int outData5, int outData6, int outData7, int outData8)
{
	unsigned char sum;
//	unsigned char outData_H = ((unsigned short)outData)>>8;
//	unsigned char outData_L = (unsigned char)outData;
	S4BUF = (0xAA);   // ͷ
	delayus(90);
	S4BUF = (0xAA);   // ͷ
	delayus(90);
	S4BUF = 0xf1; // ����
	delayus(90);
	S4BUF = (0x0f);   // ����Ϊ16���ֽ�
	delayus(90);
	S4BUF = ((unsigned short)outData1)>>8;   // ���ݸ�8λ
	delayus(90);
	S4BUF = (unsigned char)outData1;         // ���ݵ�8λ
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
	
	sum = 0xAA | 0xAA | 0xF1 | 0x02;// У��ֵ
//	sum = sum | ((unsigned short)outData1)>>8 | (unsigned char)outData1 | ((unsigned short)outData2)>>8 | (unsigned char)outData2;
//	sum = sum | ((unsigned short)outData3)>>8 | (unsigned char)outData3 | ((unsigned short)outData4)>>8 | (unsigned char)outData4;
//	sum = sum | ((unsigned short)outData5)>>8 | (unsigned char)outData5 | ((unsigned short)outData6)>>8 | (unsigned char)outData6;
//	sum = sum | ((unsigned short)outData7)>>8 | (unsigned char)outData7 | ((unsigned short)outData8)>>8 | (unsigned char)outData8;
	S4BUF = sum;
	delayus(90);
}


