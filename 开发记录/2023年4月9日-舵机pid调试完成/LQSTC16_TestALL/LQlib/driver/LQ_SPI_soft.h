#ifndef __LQ_SPIsoft_H_
#define __LQ_SPIsoft_H_
#include "include.h"

//                  单片机    龙邱20689模块
#define SPI_SCK      P25      //SCK
#define SPI_MISO     P23      //单片机MISO接模块--SDO
#define SPI_MOSI     P24      //单片机MOSI接模块--SDI
#define SPI_CS       P22      //CS

#define SPI_SCK_OUT       P25
#define SPI_MISO_IN       P23
#define SPI_MOSI_OUT      P24
#define SPI_CS_OUT        P22


void Soft_SPI_ReadWriteNbyte(u8 *lqbuff, u16 len);
void Soft_SPI_Init(void);
#endif