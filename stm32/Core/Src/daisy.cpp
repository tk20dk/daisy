#include "daisy.h"


#define GPS_CLIENT_no
#define GPS_SERVER_no
#define SBUS_CLIENT_no
#define SBUS_SERVER

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart1;

TSpi Spi( hspi1 );
TGps Gps( huart1 );
TDaisy Daisy;
TSystem System;

struct TSbusFrame
{
  static uint8_t const SbusSOF       = 0x0f;
  static uint8_t const SbusEOF       = 0x00;
  static uint8_t const FlagNull      = 0x00;
  static uint8_t const FlagCh17      = 0x01;
  static uint8_t const FlagCh18      = 0x02;
  static uint8_t const FlagLostFrame = 0x04;
  static uint8_t const FlagFailSafe  = 0x08;

  uint8_t Sof;
  uint32_t Ch1:11;
  uint32_t Ch2:11;
  uint32_t Ch3:11;
  uint32_t Ch4:11;
  uint32_t Ch5:11;
  uint32_t Ch6:11;
  uint32_t Ch7:11;
  uint32_t Ch8:11;
  uint32_t Ch9:11;
  uint32_t Ch10:11;
  uint32_t Ch11:11;
  uint32_t Ch12:11;
  uint32_t Ch13:11;
  uint32_t Ch14:11;
  uint32_t Ch15:11;
  uint32_t Ch16:11;
  uint8_t Flag;
  uint8_t Eof;
} __attribute__((__packed__));

void TDaisy::Setup()
{
//  NvDataInit();
//  CalDataInit();
  Gps.Init();

  SetPin( LED1_GREEN_GPIO_Port, LED1_GREEN_Pin );
  SetPin( LED2_GREEN_GPIO_Port, LED2_GREEN_Pin );

  if( Radio433.Init( System.Config.Modulation[ 2 ], System.Config.TxPower, System.Config.Channel ))
  {
    Radio433.Receive();
  }
  else
  {
    Hmi1Error();
  }

  if( Radio868.Init( System.Config.Modulation[ 2 ], System.Config.TxPower, System.Config.Channel ))
  {
    Radio868.Receive();
  }
  else
  {
    Hmi2Error();
  }
}

void TDaisy::Loop()
{
  HmiLoop();
  Gps.Loop();

  if( Radio433Flag )
  {
    Radio433Flag = false;
    Radio433.Interrupt();
  }
  if( Radio868Flag )
  {
    Radio868Flag = false;
    Radio868.Interrupt();
  }

#ifdef SBUS_SERVER
  auto const Tick = HAL_GetTick();
  static uint32_t LastTick;
  if(( Tick > LastTick ) && ( Tick % 100 ) == 0 )
  {
    LastTick = Tick;

    TSbusFrame SbusFrame;
    SbusFrame.Sof = TSbusFrame::SbusSOF;
    SbusFrame.Ch1 = 0;
    SbusFrame.Ch2 = 0;
    SbusFrame.Ch3 = 0;
    SbusFrame.Ch4 = 0;
    SbusFrame.Ch5 = 0;
    SbusFrame.Ch6 = 0;
    SbusFrame.Ch7 = 0;
    SbusFrame.Ch8 = 0;
    SbusFrame.Ch9 = 0;
    SbusFrame.Ch10 = 0;
    SbusFrame.Ch11 = 0;
    SbusFrame.Ch12 = 0;
    SbusFrame.Ch13 = 0;
    SbusFrame.Ch14 = 0;
    SbusFrame.Ch15 = 0;
    SbusFrame.Ch16 = 0;
    SbusFrame.Flag = TSbusFrame::FlagNull;
    SbusFrame.Eof = TSbusFrame::SbusEOF;

    Radio433.Transmit( &SbusFrame, sizeof( SbusFrame ));
  }
#endif

#ifdef GPS_SERVER
  auto const Tick = HAL_GetTick();
  static uint32_t LastTick;
  if(( Tick > LastTick ) && ( Tick % 10000 ) == 0 )
  {
    LastTick = Tick;
    auto const DataRMC = Gps.GetRMC();


    if(( Tick % 20000 ) == 0 )
    {
      Radio433.Transmit( &DataRMC, sizeof( DataRMC ));
      UsbPrintf( "433 %4d %3d.%u %06u %3u.%03u : %02u %u.%05u %c %03u %u.%05u %c\n",
        0, 0, 0,
        DataRMC.Time,
        DataRMC.Speed / 1000, DataRMC.Speed % 1000,
        DataRMC.LatDeg, DataRMC.LatMin, DataRMC.LatSec, DataRMC.LatSouth ? 'S' : 'N',
        DataRMC.LonDeg, DataRMC.LonMin, DataRMC.LonSec, DataRMC.LonWest ? 'W' : 'E' );
    }
    else
    {
      Radio868.Transmit( &DataRMC, sizeof( DataRMC ));
      UsbPrintf( "868 %4d %3d.%u %06u %3u.%03u : %02u %u.%05u %c %03u %u.%05u %c\n",
        0, 0, 0,
        DataRMC.Time,
        DataRMC.Speed / 1000, DataRMC.Speed % 1000,
        DataRMC.LatDeg, DataRMC.LatMin, DataRMC.LatSec, DataRMC.LatSouth ? 'S' : 'N',
        DataRMC.LonDeg, DataRMC.LonMin, DataRMC.LonSec, DataRMC.LonWest ? 'W' : 'E' );
    }
  }
#endif
}

void TDaisy::Radio433Event( TRadioEvent const Event )
{
  union
  {
    uint8_t Buffer[ 256 ];
    TSbusFrame SbusFrame;
    TGps::TDataRMC DataRMC;
  };

  if( Event == TRadioEvent::RxDone )
  {
    auto const Snr = Radio433.GetSnr();
    auto const Rssi = Radio433.GetRssi();
    auto const Length = Radio433.ReadPacket( Buffer, sizeof( Buffer ));

    if( Length == sizeof( TGps::TDataRMC ))
    {
      Hmi1Blue( 10 );
      UsbPrintf( "-433 %4d %3d.%u %06u %3u.%03u : %02u %u.%05u %c %03u %u.%05u %c\n",
        Rssi, Snr / 10, abs(Snr) % 10,
        DataRMC.Time,
        DataRMC.Speed / 1000, DataRMC.Speed % 1000,
        DataRMC.LatDeg, DataRMC.LatMin, DataRMC.LatSec, DataRMC.LatSouth ? 'S' : 'N',
        DataRMC.LonDeg, DataRMC.LonMin, DataRMC.LonSec, DataRMC.LonWest ? 'W' : 'E' );
      }
    else if( Length == sizeof( TSbusFrame ))
    {
      Hmi1Blue( 10 );
      UsbPrintf( "433 Rssi:%4d Snr:%3d.%u Len:%u Sbus frame\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
    }
    else
    {
      UsbPrintf( "433 Rssi:%4d Snr:%3d.%u Len:%u Length error\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
    }

#ifdef GPS_SERVER
    Radio433.Receive();
#endif
#ifdef GPS_CLIENT
    Radio433.Transmit( Buffer, Length);
#endif
#ifdef SBUS_SERVER
    Radio433.Receive();
#endif
#ifdef SBUS_CLIENT
    Radio433.Receive();
#endif
  }

  if( Event == TRadioEvent::TxDone )
  {
    Hmi1Blue( 10 );
    Radio433.Receive();
  }

  if( Event == TRadioEvent::Timeout )
  {
    Hmi1Error();
  }

  if( Event == TRadioEvent::CrcError )
  {
    auto const Snr = Radio433.GetSnr();
    auto const Rssi = Radio433.GetRssi();
    auto const Length = Radio433.ReadPacket( Buffer, sizeof( Buffer ));

    UsbPrintf( "433 Rssi:%4d Snr:%3d.%u Len:%u CRC Error\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
  }

  if( Event == TRadioEvent::NoCrc )
  {
    auto const Snr = Radio433.GetSnr();
    auto const Rssi = Radio433.GetRssi();
    auto const Length = Radio433.ReadPacket( Buffer, sizeof( Buffer ));

    UsbPrintf( "433 Rssi:%4d Snr:%3d.%u Len:%u No CRC\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
  }
}

void TDaisy::Radio868Event( TRadioEvent const Event )
{
  union
  {
    uint8_t Buffer[ 256 ];
    TSbusFrame SbusFrame;
    TGps::TDataRMC DataRMC;
  };

  if( Event == TRadioEvent::RxDone )
  {
    auto const Snr = Radio868.GetSnr();
    auto const Rssi = Radio868.GetRssi();
    auto const Length = Radio868.ReadPacket( Buffer, sizeof( Buffer ));

    if( Length == sizeof( TGps::TDataRMC ))
    {
      Hmi2Blue( 10 );
      UsbPrintf( "-868 %4d %3d.%u %06u %3u.%03u : %02u %u.%05u %c %03u %u.%05u %c\n",
        Rssi, Snr / 10, abs(Snr) % 10,
        DataRMC.Time,
        DataRMC.Speed / 1000, DataRMC.Speed % 1000,
        DataRMC.LatDeg, DataRMC.LatMin, DataRMC.LatSec, DataRMC.LatSouth ? 'S' : 'N',
        DataRMC.LonDeg, DataRMC.LonMin, DataRMC.LonSec, DataRMC.LonWest ? 'W' : 'E' );
    }
    else if( Length == sizeof( TSbusFrame ))
    {
      Hmi2Blue( 10 );
      UsbPrintf( "868 Rssi:%4d Snr:%3d.%u Len:%u Sbus frame\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
    }
    else
    {
      UsbPrintf( "868 Rssi:%4d Snr:%3d.%u Len:%u Length error\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
    }

#ifdef GPS_SERVER
    Radio868.Receive();
#endif
#ifdef GPS_CLIENT
    Radio868.Transmit( Buffer, Length);
#endif
#ifdef SBUS_SERVER
    Radio868.Receive();
#endif
#ifdef SBUS_CLIENT
    Radio868.Receive();
#endif
  }

  if( Event == TRadioEvent::TxDone )
  {
    Hmi2Blue( 10 );
    Radio868.Receive();
  }

  if( Event == TRadioEvent::Timeout )
  {
    Hmi2Error();
  }

  if( Event == TRadioEvent::CrcError )
  {
    auto const Snr = Radio868.GetSnr();
    auto const Rssi = Radio868.GetRssi();
    auto const Length = Radio868.ReadPacket( Buffer, sizeof( Buffer ));

    UsbPrintf( "868 Rssi:%4d Snr:%3d.%u Len:%u CRC Error\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
  }

  if( Event == TRadioEvent::NoCrc )
  {
    auto const Snr = Radio868.GetSnr();
    auto const Rssi = Radio868.GetRssi();
    auto const Length = Radio868.ReadPacket( Buffer, sizeof( Buffer ));

    UsbPrintf( "868 Rssi:%4d Snr:%3d.%u Len:%u No CRC\n", Rssi, Snr / 10, abs(Snr) % 10, Length );
  }
}

void TDaisy::HAL_GPIO_EXTI_Callback( uint16_t const GPIO_Pin )
{
  switch( GPIO_Pin )
  {
    case DIO1_RADIO433_Pin:
    {
      Radio433Flag = true;
    }
    break;

    case DIO1_RADIO868_Pin:
    {
      Radio868Flag = true;
    }
    break;

    default:
    {
      HmiError();
    }
    break;
  }
}

void TDaisy::HmiLoop()
{
  if( TimeoutHmiBlue1 && ( HAL_GetTick() >= TimeoutHmiBlue1 ))
  {
    TimeoutHmiBlue1 = 0;
    ResetPin( LED1_BLUE_GPIO_Port, LED1_BLUE_Pin );
    SetPin( LED1_GREEN_GPIO_Port, LED1_GREEN_Pin );
  }

  if( TimeoutHmiBlue2 && ( HAL_GetTick() >= TimeoutHmiBlue2 ))
  {
    TimeoutHmiBlue2 = 0;
    ResetPin( LED2_BLUE_GPIO_Port, LED2_BLUE_Pin );
    SetPin( LED2_GREEN_GPIO_Port, LED2_GREEN_Pin );
  }
}

void TDaisy::Hmi1Blue( uint32_t const Interval )
{
  TimeoutHmiBlue1 = HAL_GetTick() + Interval;
  ResetPin( LED1_GREEN_GPIO_Port, LED1_GREEN_Pin );
  SetPin( LED1_BLUE_GPIO_Port, LED1_BLUE_Pin );
}

void TDaisy::Hmi2Blue( uint32_t const Interval )
{
  TimeoutHmiBlue2 = HAL_GetTick() + Interval;
  ResetPin( LED2_GREEN_GPIO_Port, LED2_GREEN_Pin );
  SetPin( LED2_BLUE_GPIO_Port, LED2_BLUE_Pin );
}

void TDaisy::HmiError()
{
  Hmi1Error();
  Hmi2Error();
}

void TDaisy::Hmi1Error()
{
  ResetPin( LED1_GREEN_GPIO_Port, LED1_GREEN_Pin );
  ResetPin( LED1_BLUE_GPIO_Port, LED1_BLUE_Pin );
  SetPin( LED1_RED_GPIO_Port, LED1_RED_Pin );
}

void TDaisy::Hmi2Error()
{
  ResetPin( LED2_GREEN_GPIO_Port, LED2_GREEN_Pin );
  ResetPin( LED2_BLUE_GPIO_Port, LED2_BLUE_Pin );
  SetPin( LED2_RED_GPIO_Port, LED2_RED_Pin );
}

extern "C" void SetupDaisy()
{
  Daisy.Setup();
}

extern "C" void LoopDaisy()
{
  Daisy.Loop();
}

extern "C" void HAL_GPIO_EXTI_Callback( uint16_t const GPIO_Pin )
{
  Daisy.HAL_GPIO_EXTI_Callback( GPIO_Pin );
}

TDaisy::TDaisy() :
  Radio433Flag( false ),
  Radio868Flag( false ),
  Radio433(
    433050000U,
    NSS_RADIO433_GPIO_Port,
    NSS_RADIO433_Pin,
    NRST_RADIO433_GPIO_Port,
    NRST_RADIO433_Pin,
    BUSY_RADIO433_GPIO_Port,
    BUSY_RADIO433_Pin,
    RXEN_RADIO433_GPIO_Port,
    RXEN_RADIO433_Pin,
    TXEN_RADIO433_GPIO_Port,
    TXEN_RADIO433_Pin,
    std::bind( &TDaisy::Radio433Event, this, std::placeholders::_1 )),
  Radio868(
    868000000U,
    NSS_RADIO868_GPIO_Port,
    NSS_RADIO868_Pin,
    NRST_RADIO868_GPIO_Port,
    NRST_RADIO868_Pin,
    BUSY_RADIO868_GPIO_Port,
    BUSY_RADIO868_Pin,
    RXEN_RADIO868_GPIO_Port,
    RXEN_RADIO868_Pin,
    TXEN_RADIO868_GPIO_Port,
    TXEN_RADIO868_Pin,
    std::bind( &TDaisy::Radio868Event, this, std::placeholders::_1 )),
  TimeoutHmiBlue1( 0 ),
  TimeoutHmiBlue2( 0 )
{
}
