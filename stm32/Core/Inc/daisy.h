#ifndef DAISY_H_
#define DAISY_H_

#include "gps.h"
#include "main.h"
#include "sx1268.h"


class TDaisy
{
public:
  TDaisy();

  void Loop();
  void Setup();
  void HAL_GPIO_EXTI_Callback( uint16_t const GPIO_Pin );

private:
  void HmiError();
  void Hmi1Error();
  void Hmi2Error();
  void Hmi1Blue( uint32_t const Interval = 0 );
  void Hmi2Blue( uint32_t const Interval = 0 );
  void HmiLoop();
  void Radio433Event( TRadioEvent const Event );
  void Radio868Event( TRadioEvent const Event );

private:
  bool Radio433Flag;
  bool Radio868Flag;
  TSx1268 Radio433;
  TSx1268 Radio868;
  uint32_t TimeoutHmiBlue1;
  uint32_t TimeoutHmiBlue2;
};

#endif // DAISY_H_
