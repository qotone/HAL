#include "spi_api.h"
#include "pin_api.h"

static uint8_t SPI_Enabled = 0;

void hal_spi_init(SPI_TypeDef *spi)
{
  SPI_InitTypeDef* SPI_InitStruct;
  GPIO_InitTypeDef* GPIO_InitStruct;
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_Mode = SPI_MASTERSLAVER;
  SPI_InitStruct.SPI_DataSize = SPI_DATASIZE;
  SPI_InitStruct.SPI_FirstBit = SPI_FIRSTBIT;
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_PRESCALER;
  if(SPI_MODE == SPI_MODE_0)
  {
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
  }
  else if(SPI_MODE == SPI_MODE_1)
  {
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
  }
  else if(SPI_MODE == SPI_MODE_2)
  {
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
  }
  else
  {
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
  }

  if(spi == SPI1)
  {

    hal_pin_mode(SPI_SS_PIN,AF_OUTPUT_PUSHPULL);
    hal_pin_write(SPI_SS_PIN, BIT_SET); // High

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    //    SPI_Init(SPI1,&SPI_InitStruct);
    //    SPI_Cmd(SPI1,ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;// sck,miso,mosi
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    //    SPI_Init(spi, &SPI_InitStruct);
    //    SPI_Cmd(spi,ENABLE);
  }
  else if(spi == SPI2)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;// sck,miso,mosi
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);

  }
  /*
  else if(spi == SPI3)
  {
    //
  }
  */
  SPI_Init(spi,&SPI_InitStruct);
  SPI_Cmd(spi,ENABLE);
  SPI_Enabled = 1;
}

uint16_t hal_spi_send_receive_data(SPI_TypeDef *spi, uint16_t data)
{
  while(SPI_I2S_GetFlagStatus(spi,SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(spi, data);
  while(SPI_I2S_GetFlagStatus(spi,SPI_I2S_FLAG_RXNE) == RESET);
  return SPI_I2S_ReceiveData(spi);
}

void hal_spi_deinit(SPI_TypeDef *spi)
{
  if(SPI_Enabled != false)
  {
    SPI_Cmd(spi,DISABLE);
    SPI_Enabled = 0;
  }
}
