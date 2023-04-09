
#include "include.h"

sbit SDA = P3^3;
sbit SCL = P3^2;
#define SLAW    0xA2
#define SLAR    0xA3

void I2C_init(void)
{
    I2CCFG = 0xe0;                          //ʹ��I2C����ģʽ
    I2CMSST = 0x00;
}

void Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

void Start()
{
    I2CMSCR = 0x01;                         //����START����
    Wait();
}

void SendData(char dat)
{
    I2CTXD = dat;                           //д���ݵ����ݻ�����
    I2CMSCR = 0x02;                         //����SEND����
    Wait();
}

void RecvACK()
{
    I2CMSCR = 0x03;                         //���Ͷ�ACK����
    Wait();
}

char RecvData()
{
    I2CMSCR = 0x04;                         //����RECV����
    Wait();
    return I2CRXD;
}

void SendACK()
{
    I2CMSST = 0x00;                         //����ACK�ź�
    I2CMSCR = 0x05;                         //����ACK����
    Wait();
}

void SendNAK()
{
    I2CMSST = 0x01;                         //����NAK�ź�
    I2CMSCR = 0x05;                         //����ACK����
    Wait();
}

void Stop()
{
    I2CMSCR = 0x06;                         //����STOP����
    Wait();
}

void WriteNbyte(u8 addr, u8 *p, u8 number)  /*  WordAddress,First Data Address,Byte lenth   */
{
    Start();                                //������ʼ����
    SendData(SLAW);                         //�����豸��ַ+д����
    RecvACK();
    SendData(addr);                         //���ʹ洢��ַ
    RecvACK();
    do
    {
        SendData(*p++);
        RecvACK();
    }
    while(--number);
    Stop();                                 //����ֹͣ����
}

void ReadNbyte(u8 addr, u8 *p, u8 number)   /*  WordAddress,First Data Address,Byte lenth   */
{
    Start();                                //������ʼ����
    SendData(SLAW);                         //�����豸��ַ+д����
    RecvACK();
    SendData(addr);                         //���ʹ洢��ַ
    RecvACK();
    Start();                                //������ʼ����
    SendData(SLAR);                         //�����豸��ַ+������
    RecvACK();
    do
    {
        *p = RecvData();
        p++;
        if(number != 1) SendACK();          //send ACK
    }
    while(--number);
    SendNAK();                              //send no ACK	
    Stop();                                 //����ֹͣ����
}
/****************************/
