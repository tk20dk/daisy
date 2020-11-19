#ifndef GPS_H_
#define GPS_H_

#include <cstdint>
#include "stm32f0xx_hal.h"


class TGps
{
public:
  struct TDataGLL
  {
    uint32_t Time:24;
    uint32_t LatDeg:8;
    uint32_t LonDeg:8;
    uint32_t LatSec:20;
    uint32_t LonSec:20;
    uint32_t LatMin:6;
    uint32_t LonMin:6;
    uint32_t LatSouth:1;
    uint32_t LonWest:1;
  } __attribute__((packed));

  struct TDataRMC
  {
    uint32_t Time:24;
    uint32_t LatDeg:8;
    uint32_t LonDeg:8;
    uint32_t LatSec:20;
    uint32_t LonSec:20;
    uint32_t LatMin:6;
    uint32_t LonMin:6;
    uint32_t LatSouth:1;
    uint32_t LonWest:1;
    uint32_t Speed:16;
  } __attribute__((packed));

public:
  TGps( UART_HandleTypeDef &huart );

  void Init();
  void Loop();
  auto GetGLL()
  {
    return DataGLL;
  }
  auto GetRMC()
  {
    return DataRMC;
  }

  char const* GetGpsLine();
  void HAL_UART_ErrorCallback( UART_HandleTypeDef const *const huart );
  void HAL_UART_RxCpltCallback( UART_HandleTypeDef const *const huart );

private:
  void ParseGLL( char const *const Line );
  void ParseRMC( char const *const Line );
  char GetChar( char const* &Line );
  void GetSkip( char const* &Line );
  void GetNumeric( char const* &Line, int32_t &Value0 );
  void GetDecimal( char const* &Line, int32_t &Value0, uint32_t &Value1 );

  static bool ValidateChecksum( char const *const Line );

private:
  char RxTmp;
  char TxTmp;
  bool RxFlag;
  bool TxFlag;
  bool RxError;
  char RxData[ 128 ];
  char TxData[ 128 ];
  uint8_t RxLen;
  uint8_t TxLen;
  uint8_t RxHead;
  uint8_t TxHead;
  uint8_t RxTail;
  uint8_t TxTail;
  TDataGLL DataGLL;
  TDataRMC DataRMC;
  UART_HandleTypeDef &huart;
};
extern TGps Gps;

#endif // GPS_H_
