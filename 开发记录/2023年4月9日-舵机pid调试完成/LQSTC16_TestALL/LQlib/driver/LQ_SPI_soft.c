
#include "include.h"


/*************************************************************************
*  函数名称：void SPI_SoftReadWriteNbyte(u8 *lqbuff, u16 len)
*  功能说明：SPI读写数据及长度
*  参数说明：u8 *buf数据指针,u16 len长度
*  函数返回：
*  修改时间：2020年8月10日
*  备    注：   
*************************************************************************/
void Soft_SPI_ReadWriteNbyte(u8 *lqbuff, u16 len)
{
	u8 i;
	
  SPI_CS_OUT = 0;
  SPI_SCK_OUT= 1;
  do
  {
    for(i = 0; i < 8; i++)
    {
      SPI_MOSI_OUT = ((*lqbuff) >= 0x80);
      SPI_SCK_OUT= 0;
      (*lqbuff) = (*lqbuff)<<1;      
      
      SPI_SCK_OUT= 1;
      
      (*lqbuff) |= SPI_MISO_IN;          
    }
    lqbuff++;
  }while(--len);
  SPI_CS_OUT = 1;
}

/*************************************************************************
*  函数名称：void SPI_SoftInit(void)
*  功能说明：模拟SPI口初始化
*  参数说明：无
*  函数返回：无
*  修改时间：2020年8月10日
*  备    注：   
*************************************************************************/
void Soft_SPI_Init(void)
{
	P2M1 = 0; P2M0 = 0;  //设置为准双向口
	P2PU =0x3C;          //上拉
}



//


