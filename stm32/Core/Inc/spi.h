#ifndef SPI_H__
#define SPI_H__

#include "stm32f0xx_hal.h"


class TSpi
{
  static uint32_t const SpiTimeout = 10U; // 10ms

public:
  TSpi( SPI_HandleTypeDef &hspi );

  void Write( uint8_t const Data );
  void Write( void const *const Data, uint16_t const Length );

  uint8_t Read();
  void Read( void *const Data, uint16_t const Length );

  uint8_t WriteRead( uint8_t const Data );
  void WriteRead( void const *const TxData, void *const RxData, uint16_t const Length );

private:
  SPI_HandleTypeDef &hspi;
};
extern TSpi Spi;

#endif // SPI_H__


