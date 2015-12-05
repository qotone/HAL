#ifndef __SPI_API_H
#define __SPI_API_H

#include "stm32f10x.h"
#include "defines.h"
#include "attributes.h"

#define SPI_MODE_0    0x00
#define SPI_MODE_1    0x01
#define SPI_MODE_2    0x02
#define SPI_MODE_3    0x03


#define SPI_SS_DEFAULT    ((uint16_t)(-1)) // 0xFFFF or 65535

#ifndef SPI_PRESCALER
#define SPI_PRESCALER    SPI_BaudRatePrescaler_32
#endif

#ifndef SPI_DATASIZE
#define SPI_DATASIZE    SPI_DataSize_8b
#endif

#ifndef SPI_FIRSTBIT
#define SPI_FIRSTBIT    SPI_FirstBit_MSB
#endif

#ifndef SPI_MODE
#define SPI_MODE    SPI_MODE_0
#endif

#ifndef SPI_MASTERSLAVE
#define SPI_MASTERSLAVE    SPI_Mode_Master
#endif

#ifndef SPI_SS_PIN
#define SPI_SS_PIN    SPI_SS_DEFAULT
#endif

void hal_spi_init(SPI_TypeDef *SPIx);
void hal_spi_deinit(SPI_TypeDef *SPIx);
uint16_t hal_spi_send_receive_data(SPI_TypeDef *SPIx, uint16_t data);


#endif
