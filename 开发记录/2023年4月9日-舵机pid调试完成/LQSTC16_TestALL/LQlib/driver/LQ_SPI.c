
#include "include.h"

/*************  SPI�豸��ر�������   **************/
sbit    LQ_IMU_SCK = P2^5;                 //SCK
sbit    LQ_IMU_SO  = P2^4;                 //MISO
sbit    LQ_IMU_SI  = P2^3;                 //MOSI
sbit    LQ_IMU_CE  = P2^2;                 //CS

#define SPI_CE_High()   LQ_IMU_CE  = 1     // set CE high
#define SPI_CE_Low()    LQ_IMU_CE  = 0     // clear CE low
#define SPI_Hold()      P_SPI_Hold = 0     // clear Hold pin
#define SPI_UnHold()    P_SPI_Hold = 1     // set Hold pin
#define SPI_WP()        P_SPI_WP   = 0     // clear WP pin
#define SPI_UnWP()      P_SPI_WP   = 1     // set WP pin

/************************************************************************/
void SPI_init(void)
{
    SPCTL |=  (1 << 7);                    //���� SS ���Ź��ܣ�ʹ�� MSTR ȷ���������������Ǵӻ�
    SPCTL |=  (1 << 6);                    //ʹ�� SPI ����
    SPCTL &= ~(1 << 5);                    //�ȷ���/�������ݵĸ�λ�� MSB��
    SPCTL |=  (1 << 4);                    //��������ģʽ
    SPCTL &= ~(1 << 3);                    //SCLK ����ʱΪ�͵�ƽ��SCLK ��ǰʱ����Ϊ�����أ���ʱ����Ϊ�½���
    SPCTL &= ~(1 << 2);                    //���� SS �ܽ�Ϊ�͵�ƽ������һλ���ݲ��� SCLK �ĺ�ʱ���ظı�����
    SPCTL = (SPCTL & ~3) | 0;              //SPI ʱ��Ƶ��ѡ��, 0: 4T, 1: 8T,  2: 16T,  3: 32T
	  P_SW1 = (P_SW1 & ~(3<<2)) | (1<<2);    //IO���л�. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 
											                     //1: P2.2 P2.3 P2.4 P2.5, 
											                     //2: P5.4 P4.0 P4.1 P4.3, 
											                     //3: P3.5 P3.4 P3.3 P3.2
                                           
    LQ_IMU_SCK = 0;                        // set clock to low initial state
    LQ_IMU_SI = 1;	  
    SPSTAT = SPIF + WCOL;                  //��0 SPIF��WCOL��־
}

/************************************************************************/
void SPI_WriteByte(u8 out)
{	 
    SPDAT = out;
    while((SPSTAT & SPIF) == 0) ;
    SPSTAT = SPIF + WCOL;                  //��0 SPIF��WCOL��־	
}

/************************************************************************/
u8 SPI_ReadByte(void)
{	 
    SPDAT = 0xff;
    while((SPSTAT & SPIF) == 0) ;
    SPSTAT = SPIF + WCOL;                  //��0 SPIF��WCOL��־
    return (SPDAT);
}

/************************************************
��Flash�ж�ȡ����
��ڲ���:
    addr   : ��ַ����
    lqbuf : �����Flash�ж�ȡ������
    lqsize   : ���ݿ��С
���ڲ���:
    ��
************************************************/
void SPI_Read_Nbytes(u8 addr, u8 *lqbuf, u16 lqsize)
{
    SPI_CE_Low();                         //enable device
    SPI_WriteByte(addr);                  //������ʼ��ַ
	  lqbuf++;                              
    do{                                   
        *lqbuf = SPI_ReadByte();          //receive byte and store at lqbuf
        lqbuf++;                          
    }while(--lqsize);                     //read until no_bytes is reached
    SPI_CE_High();                        //disable device
}

/************************************************
д���ݵ�Flash��
��ڲ���:
    addr   : ��ַ����
    lqbuf : ������Ҫд��Flash������
    lqsizee   : ���ݿ��С
���ڲ���: ��
************************************************/
void SPI_Write_Nbytes(u8 addr, u8 *lqbuf, u8 lqsize)
{

    SPI_CE_Low();                         // enable device
    SPI_WriteByte(addr);        				  // ����ҳ�������
	  lqbuf++;                              
    do{                                   
        SPI_WriteByte(*lqbuf++);          //����ҳ��д
        addr++;                           
        if ((addr & 0xff) == 0) break;    
    }while(--lqsize);                     
    SPI_CE_High();                        // disable device
}