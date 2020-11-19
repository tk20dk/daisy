#include "main.h"
#include "sx1268.h"

TSx1268::TSx1268(
  uint32_t const BaseFreq,
  GPIO_TypeDef *const PortNSS,
  uint32_t const PinNSS,
  GPIO_TypeDef *const PortNRST,
  uint32_t const PinNRST,
  GPIO_TypeDef *const PortBUSY,
  uint32_t const PinBUSY,
  GPIO_TypeDef *const PortRXEN,
  uint32_t const PinRXEN,
  GPIO_TypeDef *const PortTXEN,
  uint32_t const PinTXEN,
  TCallback const Callback ) :
  ImageCalibrated( false ),
  BaseFreq( BaseFreq ),
  FrequencyError( 0 ),
  OperatingMode( MODE_SLEEP ),
  PacketParams(),
  PortNSS( PortNSS ),
  PinNSS( PinNSS ),
  PortNRST( PortNRST ),
  PinNRST( PinNRST ),
  PortBUSY( PortBUSY ),
  PinBUSY( PinBUSY ),
  PortRXEN( PortRXEN ),
  PinRXEN( PinRXEN ),
  PortTXEN( PortTXEN ),
  PinTXEN( PinTXEN ),
  Callback( Callback )
{
}

bool TSx1268::Init( Modulation_t const &Modulation, int32_t const TxPower, uint32_t const Channel )
{
  Reset();

  SetRegulatorMode( USE_DCDC );
  SetDio3AsTcxoCtrl( TCXO_CTRL_1_8V, 500 );

  RadioStatus_t Status =  GetStatus();
  RadioError_t Errors = GetDeviceErrors();
  if(( Errors.Value != 0x2000 ) || ( Status.Fields.CpuBusy != 0 ) ||
     ( Status.Fields.ChipMode != 2 ) || ( Status.Fields.CmdStatus != 1 ))
  {
    return false;
  }

  CalibrationParams_t calibParam;
  calibParam.Value = 0x7F;
  Calibrate( calibParam );

  Status =  GetStatus();
  Errors = GetDeviceErrors();
  if(( Errors.Value != 0x2000 ) || ( Status.Fields.CpuBusy != 0 ) ||
     ( Status.Fields.ChipMode != 2 ) || ( Status.Fields.CmdStatus != 1 ))
  {
    return false;
  }

  SetBufferBaseAddresses( 0, 0 );

  auto const Size = 128;
  uint8_t BufRx[ Size ] = { 0 };
  uint8_t BufTx[ Size ];
  for( auto Index = 0; Index < Size; Index++ )
  {
    BufTx[ Index ] = static_cast< uint8_t >( Index );
  }
  WriteBuffer( 0, BufTx, Size );
  ReadBuffer( 0, BufRx, Size );
  if( memcmp( BufTx, BufRx, Size ) != 0 )
  {
    return false;
  }

  PacketParams.PayloadLength       = 0;
  PacketParams.PreambleLength      = 12;
  PacketParams.CrcMode             = LORA_CRC_ON;

  ModulationParams_t ModulationParams;
  ModulationParams.Bandwidth       = (RadioLoRaBandwidths_t)Modulation.Bandwidth;
  ModulationParams.CodingRate      = (RadioLoRaCodingRates_t)Modulation.CodingRate;
  ModulationParams.SpreadingFactor = (RadioLoRaSpreadingFactors_t)Modulation.SpreadingFactor;

  if(( ModulationParams.SpreadingFactor == LORA_SF5 ) || ( ModulationParams.SpreadingFactor == LORA_SF6 ))
  {
    if( PacketParams.PreambleLength < 12 )
    {
       PacketParams.PreambleLength = 12;
    }
  }

  SetStandby( STDBY_RC );
  ClearIrqStatus( IRQ_RADIO_ALL );
  ClearDeviceErrors();

  SetPacketType( PACKET_TYPE_LORA );
  SetModulationParams( ModulationParams );
  SetPacketParams( PacketParams );
  SetRfChannel( Channel );
  SetTxParams( TxPower, RADIO_RAMP_200_US );

  return true;
}

void TSx1268::SetTxPower( int32_t const TxPower )
{
  SetTxParams( TxPower, RADIO_RAMP_200_US );
}
void TSx1268::SetModulation( Modulation_t const &Modulation )
{
  ModulationParams_t ModulationParams;
  ModulationParams.Bandwidth       = (RadioLoRaBandwidths_t)Modulation.Bandwidth;
  ModulationParams.CodingRate      = (RadioLoRaCodingRates_t)Modulation.CodingRate;
  ModulationParams.SpreadingFactor = (RadioLoRaSpreadingFactors_t)Modulation.SpreadingFactor;
  SetModulationParams( ModulationParams );
}

void TSx1268::Interrupt()
{
  auto const IrqStatus = GetIrqStatus();
  ClearIrqStatus( IrqStatus );

  if( IrqStatus & IRQ_RX_DONE )
  {
    if( IrqStatus & IRQ_CRC_ERROR )
    {
      Callback( TRadioEvent::CrcError );
    }
    else
    {
      Callback( TRadioEvent::RxDone );
    }
  }

  if( IrqStatus & IRQ_TX_DONE )
  {
    Callback( TRadioEvent::TxDone );
  }

  if( IrqStatus & IRQ_RX_TX_TIMEOUT )
  {
    Callback( TRadioEvent::Timeout );
  }
}

void TSx1268::SetRfChannel( uint32_t const Channel )
{
  SetRfFrequency( BaseFreq + 25000U * Channel );
}

void TSx1268::Receive()
{
  auto const IrqMask = IRQ_RX_DONE | IRQ_CRC_ERROR | IRQ_RX_TX_TIMEOUT;
  SetDioIrqParams( IrqMask, IrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );

//  SetRx( 0 );
  SetRxBoosted( 0 );
}

void TSx1268::SetStandby( RadioStandbyModes_t const standbyConfig )
{
  WriteCommand( RADIO_SET_STANDBY, ( uint8_t* )&standbyConfig, 1 );
  if( standbyConfig == STDBY_RC )
  {
    OperatingMode = MODE_STDBY_RC;
  }
  else
  {
    OperatingMode = MODE_STDBY_XOSC;
  }
}

void TSx1268::SetPacketType( RadioPacketTypes_t packetType )
{
  WriteCommand( RADIO_SET_PACKETTYPE, ( uint8_t* )&packetType, 1 );
}

void TSx1268::SetRfFrequency( uint32_t const Frequency )
{
  if( ImageCalibrated == false )
  {
    CalibrateImage( Frequency );
    ImageCalibrated = true;
  }

  uint8_t buf[4];
  uint32_t const freq = (uint32_t)((double)Frequency / (double)FREQ_STEP);
  buf[0] = ( uint8_t )( ( freq >> 24 ) & 0xFF );
  buf[1] = ( uint8_t )( ( freq >> 16 ) & 0xFF );
  buf[2] = ( uint8_t )( ( freq >> 8 ) & 0xFF );
  buf[3] = ( uint8_t )( freq & 0xFF );
  WriteCommand( RADIO_SET_RFFREQUENCY, buf, 4 );
}

void TSx1268::CalibrateImage( uint32_t const freq )
{
  uint8_t calFreq[ 2 ];

  if( freq > 900000000 )
  {
    calFreq[0] = 0xE1;
    calFreq[1] = 0xE9;
  }
  else if( freq > 850000000 )
  {
    calFreq[0] = 0xD7;
    calFreq[1] = 0xD8;
  }
  else if( freq > 770000000 )
  {
    calFreq[0] = 0xC1;
    calFreq[1] = 0xC5;
  }
  else if( freq > 460000000 )
  {
    calFreq[0] = 0x75;
    calFreq[1] = 0x81;
  }
  else if( freq > 425000000 )
  {
    calFreq[0] = 0x6B;
    calFreq[1] = 0x6F;
  }
  WriteCommand( RADIO_CALIBRATEIMAGE, calFreq, 2 );
}

void TSx1268::SetBufferBaseAddresses( uint8_t const txBaseAddress, uint8_t const rxBaseAddress )
{
  uint8_t buf[2];

  buf[0] = txBaseAddress;
  buf[1] = rxBaseAddress;
  WriteCommand( RADIO_SET_BUFFERBASEADDRESS, buf, 2 );
}

void TSx1268::SetModulationParams( ModulationParams_t &ModulationParams )
{
  switch( ModulationParams.Bandwidth )
  {
    case LORA_BW_500:
       ModulationParams.LowDatarateOptimize = 0x00;
       break;
    case LORA_BW_250:
      if( ModulationParams.SpreadingFactor == 12 )
      {
        ModulationParams.LowDatarateOptimize = 0x01;
      }
      else
      {
        ModulationParams.LowDatarateOptimize = 0x00;
      }
      break;
    case LORA_BW_125:
      if( ModulationParams.SpreadingFactor >= 11 )
      {
        ModulationParams.LowDatarateOptimize = 0x01;
      }
      else
      {
        ModulationParams.LowDatarateOptimize = 0x00;
      }
      break;
    case LORA_BW_062:
      if( ModulationParams.SpreadingFactor >= 10 )
      {
        ModulationParams.LowDatarateOptimize = 0x01;
      }
      else
      {
        ModulationParams.LowDatarateOptimize = 0x00;
      }
      break;
    case LORA_BW_041:
      if( ModulationParams.SpreadingFactor >= 9 )
      {
        ModulationParams.LowDatarateOptimize = 0x01;
      }
      else
      {
        ModulationParams.LowDatarateOptimize = 0x00;
      }
      break;
    case LORA_BW_031:
    case LORA_BW_020:
    case LORA_BW_015:
    case LORA_BW_010:
    case LORA_BW_007:
      ModulationParams.LowDatarateOptimize = 0x01;
      break;
    default:
      break;
  }

  uint8_t buf[4];
  buf[0] = ModulationParams.SpreadingFactor;
  buf[1] = ModulationParams.Bandwidth;
  buf[2] = ModulationParams.CodingRate;
  buf[3] = ModulationParams.LowDatarateOptimize;
  WriteCommand( RADIO_SET_MODULATIONPARAMS, buf, sizeof( buf ));
}

void TSx1268::SetPacketParams( PacketParams_t &PacketParams )
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

  uint8_t buf[ 6 ];
  buf[0] = ( PacketParams.PreambleLength >> 8 ) & 0xFF;
  buf[1] = PacketParams.PreambleLength;
  buf[2] = LORA_PACKET_EXPLICIT;
  buf[3] = PacketParams.PayloadLength;
  buf[4] = PacketParams.CrcMode;
  buf[5] = LORA_IQ_NORMAL;
  WriteCommand( RADIO_SET_PACKETPARAMS, buf, sizeof( buf ));

#pragma GCC diagnostic pop
}

void TSx1268::SetDioIrqParams( uint16_t irqMask, uint16_t dio1Mask, uint16_t dio2Mask, uint16_t dio3Mask )
{
  uint8_t buf[8];

  buf[0] = ( uint8_t )( ( irqMask >> 8 ) & 0x00FF );
  buf[1] = ( uint8_t )( irqMask & 0x00FF );
  buf[2] = ( uint8_t )( ( dio1Mask >> 8 ) & 0x00FF );
  buf[3] = ( uint8_t )( dio1Mask & 0x00FF );
  buf[4] = ( uint8_t )( ( dio2Mask >> 8 ) & 0x00FF );
  buf[5] = ( uint8_t )( dio2Mask & 0x00FF );
  buf[6] = ( uint8_t )( ( dio3Mask >> 8 ) & 0x00FF );
  buf[7] = ( uint8_t )( dio3Mask & 0x00FF );
  WriteCommand( RADIO_CFG_DIOIRQ, buf, 8 );
}

void TSx1268::SetRx( uint32_t const Timeout )
{
  OperatingMode = MODE_RX;

  SetPin( PortRXEN, PinRXEN );
  ResetPin( PortTXEN, PinTXEN );

  uint8_t buf[3];
  buf[0] = ( uint8_t )( ( Timeout >> 16 ) & 0xFF );
  buf[1] = ( uint8_t )( ( Timeout >> 8 ) & 0xFF );
  buf[2] = ( uint8_t )( Timeout & 0xFF );
  WriteCommand( RADIO_SET_RX, buf, 3 );
}

void TSx1268::SetRxBoosted( uint32_t const Timeout )
{
  WriteReg( REG_RX_GAIN, 0x96 ); // max LNA gain, increase current by ~2mA for around ~3dB in sensitivity
  SetRx( Timeout );
}

uint32_t TSx1268::GetIrqStatus()
{
  uint8_t Buffer[2];
  ReadCommand( RADIO_GET_IRQSTATUS, Buffer, 2 );
  return Buffer[ 0 ] * 256 + Buffer[ 1 ];
}

void TSx1268::SetTxParams( int8_t const Power_, RadioRampTimes_t const RampTime )
{
  auto Power = Power_;

  if( GetDeviceType() == SX1261 )
  {
    if( Power == 15 )
    {
      SetPaConfig( 0x06, 0x00, 0x01, 0x01 );
    }
    else
    {
      SetPaConfig( 0x04, 0x00, 0x01, 0x01 );
    }
    if( Power >= 14 )
    {
      Power = 14;
    }
    else if( Power < -3 )
    {
      Power = -3;
    }
    WriteReg( REG_OCP, 0x18 ); // current max is 80 mA for the whole device
  }
  else // sx1262 or sx1268
  {
    SetPaConfig( 0x04, 0x07, 0x00, 0x01 );
    if( Power > 22 )
    {
      Power = 22;
    }
    else if( Power < -3 )
    {
      Power = -3;
    }
    WriteReg( REG_OCP, 0x38 ); // current max 160mA for the whole device
  }

  uint8_t buf[2];
  buf[0] = Power;
  buf[1] = (uint8_t)RampTime;
  WriteCommand( RADIO_SET_TXPARAMS, buf, 2 );
}

void TSx1268::SetPaConfig( uint8_t const PaDutyCycle, uint8_t const HpMax, uint8_t const DeviceSel, uint8_t const PaLUT )
{
  uint8_t Buf[4];

  Buf[0] = PaDutyCycle;
  Buf[1] = HpMax;
  Buf[2] = DeviceSel;
  Buf[3] = PaLUT;
  WriteCommand( RADIO_SET_PACONFIG, Buf, 4 );
}

void TSx1268::SetRegulatorMode( RadioRegulatorMode_t const Mode )
{
  WriteCommand( RADIO_SET_REGULATORMODE, ( uint8_t* )&Mode, 1 );
}

void TSx1268::ClearIrqStatus( uint32_t const IrqMask )
{
  uint8_t Buffer[ 2 ];
  Buffer[ 0 ] = ( uint8_t )( ( ( uint16_t )IrqMask >> 8 ) & 0x00FF );
  Buffer[ 1 ] = ( uint8_t )( ( uint16_t )IrqMask & 0x00FF );
  WriteCommand( RADIO_CLR_IRQSTATUS, Buffer, sizeof( Buffer ));
}

void TSx1268::SetDio3AsTcxoCtrl( RadioTcxoCtrlVoltage_t const TcxoVoltage, uint32_t const Timeout )
{
  uint8_t Buffer[ 4 ];
  Buffer[ 0 ] = TcxoVoltage & 0x07;
  Buffer[ 1 ] = ( uint8_t )( ( Timeout >> 16 ) & 0xFF );
  Buffer[ 2 ] = ( uint8_t )( ( Timeout >> 8 ) & 0xFF );
  Buffer[ 3 ] = ( uint8_t )( Timeout & 0xFF );

  WriteCommand( RADIO_SET_TCXOMODE, Buffer, sizeof( Buffer ));
}

RadioError_t TSx1268::GetDeviceErrors()
{
  RadioError_t Error;
  ReadCommand( RADIO_GET_ERROR, ( uint8_t * )&Error, 2 );
  return Error;
}

void TSx1268::ClearDeviceErrors()
{
  uint8_t const Buffer[ 1 ] = { 0 };
  WriteCommand( RADIO_CLR_ERROR, Buffer, sizeof( Buffer ));
}

RadioStatus_t TSx1268::GetStatus()
{
  uint8_t Buffer[ 1 ];
  ReadCommand( RADIO_GET_STATUS, Buffer, sizeof( Buffer));

  RadioStatus_t Status;
  Status.Value = Buffer[ 0 ];

  return Status;
}

void TSx1268::Calibrate( CalibrationParams_t const &CalibParam )
{
  WriteCommand( RADIO_CALIBRATE, &CalibParam.Value, 1 );
}

void TSx1268::Transmit( void const *const Buffer, uint16_t const Length )
{
  auto const IrqMask = IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT;
  SetDioIrqParams( IrqMask, IrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );

  if( Length != PacketParams.PayloadLength )
  {
    SetStandby( STDBY_RC );
    PacketParams.PayloadLength = static_cast< uint8_t >( Length );
    SetPacketParams( PacketParams );
  }

  WriteBuffer( 0x00, Buffer, Length );
  SetTx( 0xFFFFFF );
}

void TSx1268::SetTx( uint32_t const Timeout )
{
  OperatingMode = MODE_TX;

  SetPin( PortTXEN, PinTXEN );
  ResetPin( PortRXEN, PinRXEN );

  uint8_t buf[3];
  buf[0] = (uint8_t)( ( Timeout >> 16 ) & 0xFF );
  buf[1] = (uint8_t)( ( Timeout >> 8 ) & 0xFF );
  buf[2] = (uint8_t)( Timeout & 0xFF );
  WriteCommand( RADIO_SET_TX, buf, 3 );
}

void TSx1268::WriteCommand( RadioCommands_t const Command, uint8_t const *const Buffer, uint32_t const Length )
{
  WaitOnBusy( );

  ResetPin( PortNSS, PinNSS );
  Spi.Write( ( uint8_t )Command );
  for( auto i = 0U; i < Length; i++ )
  {
    Spi.Write( Buffer[i] );
  }
  SetPin( PortNSS, PinNSS );

  for( auto counter = 0; counter < 15; counter++ )
  {
    __NOP();
  }
}

void TSx1268::ReadCommand( RadioCommands_t const Command, uint8_t *const Buffer, uint32_t const Length )
{
  WaitOnBusy( );

  ResetPin( PortNSS, PinNSS );
  Spi.Write( (uint8_t)Command );
  Spi.Write( 0 );
  for( auto i = 0U; i < Length; i++ )
  {
    Buffer[i] = Spi.WriteRead( 0 );
  }
  SetPin( PortNSS, PinNSS );
}

void TSx1268::WriteRegister( uint32_t const Address, uint8_t const *const Buffer, uint32_t const Length )
{
  WaitOnBusy( );

  ResetPin( PortNSS, PinNSS );
  Spi.Write( RADIO_WRITE_REGISTER );
  Spi.Write( ( Address & 0xFF00 ) >> 8 );
  Spi.Write( Address & 0x00FF );
  for( auto i = 0U; i < Length; i++ )
  {
    Spi.Write( Buffer[i] );
  }
  SetPin( PortNSS, PinNSS );
}

void TSx1268::WriteReg( uint32_t const Address, uint8_t const Value )
{
  WriteRegister( Address, &Value, 1 );
}

void TSx1268::ReadRegister( uint32_t const Address, uint8_t *const Buffer, uint32_t const Length )
{
  WaitOnBusy( );

  ResetPin( PortNSS, PinNSS );
  Spi.Write( RADIO_READ_REGISTER );
  Spi.Write( ( Address & 0xFF00 ) >> 8 );
  Spi.Write( Address & 0x00FF );
  Spi.Write( 0 );
  for( auto i = 0U; i < Length; i++ )
  {
    Buffer[i] = Spi.WriteRead( 0 );
  }
  SetPin( PortNSS, PinNSS );
}

uint8_t TSx1268::ReadReg( uint32_t const Address )
{
  uint8_t Data;

  ReadRegister( Address, &Data, 1 );
  return Data;
}

void TSx1268::WriteBuffer( uint8_t const Offset, void const *const Buffer, uint16_t const Length )
{
  WaitOnBusy( );

  ResetPin( PortNSS, PinNSS );
  Spi.Write( RADIO_WRITE_BUFFER );
  Spi.Write( Offset );
  Spi.Write( Buffer, Length );
  SetPin( PortNSS, PinNSS );
}

void TSx1268::ReadBuffer( uint8_t const Offset, void *const Buffer, uint16_t const Length )
{
  WaitOnBusy( );

  ResetPin( PortNSS, PinNSS );
  Spi.Write( RADIO_READ_BUFFER );
  Spi.Write( Offset );
  Spi.Write( 0 );
  Spi.Read( Buffer, Length );
  SetPin( PortNSS, PinNSS );
}

void TSx1268::WaitOnBusy()
{
  while( ReadPin( PortBUSY, PinBUSY ) == true )
  {
  }
}

void TSx1268::Reset( void )
{
  ResetPin( PortNRST, PinNRST );
  HAL_Delay( 2 );
  SetPin( PortNRST, PinNRST );
  HAL_Delay( 2 );
}

uint16_t TSx1268::ReadPacket( void *const Buffer, uint32_t const MaxLength )
{
  uint8_t Length;
  uint8_t Offset;
  GetRxBufferStatus( Length, Offset );
  if( Length > MaxLength )
  {
    return 0;
  }

  ReadBuffer( Offset, Buffer, Length );
  return Length;
}

void TSx1268::GetRxBufferStatus( uint8_t &payloadLength, uint8_t &rxStartBufferPointer )
{
  uint8_t Buffer[ 2 ];
  ReadCommand( RADIO_GET_RXBUFFERSTATUS, Buffer, sizeof( Buffer ));
  payloadLength = Buffer[ 0 ];
  rxStartBufferPointer = Buffer[ 1 ];
}

int32_t TSx1268::GetSnr()
{
  uint8_t Buffer[ 3 ];
  ReadCommand( RADIO_GET_PACKETSTATUS, Buffer, sizeof( Buffer ));

  int32_t const Snr = static_cast<int8_t>( Buffer[ 1 ] );
  return ( Snr * 10 ) / 4;
}

int32_t TSx1268::GetRssi()
{
  uint8_t Buffer[ 3 ];
  ReadCommand( RADIO_GET_PACKETSTATUS, Buffer, sizeof( Buffer ));
  return -Buffer[ 0 ] / 2;
}

void TSx1268::GetPacketStatus( PacketStatus_t &PktStatus )
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

  uint8_t Buffer[ 3 ];
  ReadCommand( RADIO_GET_PACKETSTATUS, Buffer, sizeof( Buffer ));

  PktStatus.RssiPkt = -Buffer[ 0 ] / 2;
  PktStatus.SnrPkt = Buffer[ 1 ] < 128 ? Buffer[ 1 ] / 4 : ( Buffer[ 1 ] - 256 ) / 4;
  PktStatus.SignalRssiPkt = -Buffer[ 2 ] / 2;
  PktStatus.FreqError = FrequencyError;

#pragma GCC diagnostic pop
}
