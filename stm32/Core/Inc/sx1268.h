#ifndef SX1268_H__
#define SX1268_H__

#include <functional>
#include "system.h"
#include "spi.h"


union RadioStatus_t
{
  uint8_t Value;
  struct
  { //bit order is lsb -> msb
    uint8_t Reserved  : 1;  // Reserved
    uint8_t CmdStatus : 3;  // Command status
    uint8_t ChipMode  : 3;  // Chip mode
    uint8_t CpuBusy   : 1;  // Flag for CPU radio busy
  } Fields;
};

#define GetDeviceType() SX1268

enum class TRadioSpreadingFactors : uint8_t
{
  LORA_SF5  = 0x05,
  LORA_SF6  = 0x06,
  LORA_SF7  = 0x07,
  LORA_SF8  = 0x08,
  LORA_SF9  = 0x09,
  LORA_SF10 = 0x0A,
  LORA_SF11 = 0x0B,
  LORA_SF12 = 0x0C,
};

enum class TRadioBandwidths : uint8_t
{
  LORA_BW_500 = 6,
  LORA_BW_250 = 5,
  LORA_BW_125 = 4,
  LORA_BW_062 = 3,
  LORA_BW_041 = 10,
  LORA_BW_031 = 2,
  LORA_BW_020 = 9,
  LORA_BW_015 = 1,
  LORA_BW_010 = 8,
  LORA_BW_007 = 0,
};

enum class TRadioCodingRates : uint8_t
{
  LORA_CR_4_5 = 0x01,
  LORA_CR_4_6 = 0x02,
  LORA_CR_4_7 = 0x03,
  LORA_CR_4_8 = 0x04,
};

enum class TRadioEvent : uint8_t
{
  RxDone,
  TxDone,
  Timeout,
  NoCrc,
  CrcError
};


class TSx1268
{
  typedef std::function<void(TRadioEvent)> TCallback;

public:
  TSx1268(
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
	TCallback const Callback );

  bool Init( Modulation_t const &Modulation, int32_t const TxPower, uint32_t const Channel );
  void Receive();
  void Transmit( void const *const Buffer, uint16_t const Length );
  void Interrupt();
  int32_t GetSnr();
  int32_t GetRssi();
  uint16_t ReadPacket( void *const Buffer, uint32_t const MaxLength );
  void SetTxPower( int32_t const TxPower );
  void SetRfChannel( uint32_t const RfChannel );
  void SetModulation( Modulation_t const &Modulation );

private:
  void Reset();
  void SetStandby( RadioStandbyModes_t const StandbyConfig );
  void SetPacketType( RadioPacketTypes_t const PacketType );
  void SetRfFrequency( uint32_t const Frequency );
  void CalibrateImage( uint32_t const Frequency );
  void SetBufferBaseAddresses( uint8_t const TxBaseAddress, uint8_t const RxBaseAddress );
  void SetModulationParams( ModulationParams_t &ModulationParams );
  void SetPacketParams( PacketParams_t &PacketParams );
  void SetCrcSeed( uint16_t const Seed );
  void GetPacketStatus( PacketStatus_t &pktStatus );
  void SetCrcPolynomial( uint16_t const Polynomial );
  void SetDioIrqParams( uint16_t const IrqMask, uint16_t const Dio1Mask, uint16_t const Dio2Mask, uint16_t const Dio3Mask );
  void SetRx( uint32_t const Timeout );
  void SetTxParams( int8_t const Power, RadioRampTimes_t const RampTime );
  void SetPaConfig( uint8_t const PaDutyCycle, uint8_t const HpMax, uint8_t const DeviceSel, uint8_t const PaLUT );
  void SetRegulatorMode( RadioRegulatorMode_t mode );
  void ClearIrqStatus( uint32_t const IrqMask );
  void SetRxBoosted( uint32_t const Timeout );
  void SetDio3AsTcxoCtrl( RadioTcxoCtrlVoltage_t const TcxoVoltage, uint32_t const Timeout );
  void ClearDeviceErrors();
  void Calibrate( CalibrationParams_t const &CalibParam );
  void SetTx( uint32_t const Timeout );
  void GetRxBufferStatus( uint8_t &PayloadLength, uint8_t &RxStartBufferPointer );

  uint32_t GetIrqStatus();
  RadioError_t GetDeviceErrors();
  RadioStatus_t GetStatus();

  void WaitOnBusy();
  void WriteCommand( RadioCommands_t const Command, uint8_t const *const Buffer, uint32_t const Length );
  void ReadCommand( RadioCommands_t const Command, uint8_t *const Buffer, uint32_t const Length );
  void WriteRegister( uint32_t const Address, uint8_t const *const Buffer, uint32_t const Length );
  void WriteReg( uint32_t const Address, uint8_t const Value );
  void ReadRegister( uint32_t const Address, uint8_t *const Buffer, uint32_t const Length );
  uint8_t ReadReg( uint32_t const Address );
  void WriteBuffer( uint8_t const Offset, void const *const Buffer, uint16_t const Length );
  void ReadBuffer( uint8_t const Offset, void *const Buffer, uint16_t const Length );

private:
  bool ImageCalibrated;
  uint32_t const BaseFreq;
  uint32_t FrequencyError;
  RadioOperatingModes_t OperatingMode;
  PacketParams_t PacketParams;
  GPIO_TypeDef *const PortNSS;
  uint32_t const PinNSS;
  GPIO_TypeDef *const PortNRST;
  uint32_t const PinNRST;
  GPIO_TypeDef *const PortBUSY;
  uint32_t const PinBUSY;
  GPIO_TypeDef *const PortRXEN;
  uint32_t const PinRXEN;
  GPIO_TypeDef *const PortTXEN;
  uint32_t const PinTXEN;
  TCallback const Callback;
};

#endif // SX1268_H__
