#ifndef SX1268_DEF_H_
#define SX1268_DEF_H_


#define XTAL_FREQ                                   32000000
#define FREQ_DIV                                    33554432
#define FREQ_STEP                                   0.95367431640625 // ( ( double )( XTAL_FREQ / ( double )FREQ_DIV ) )
#define FREQ_ERR                                    0.47683715820312

#define SX1261  0
#define SX1262  1
#define SX1268  2

#define MATCHING_FREQ_915                           0
#define MATCHING_FREQ_780                           1
#define MATCHING_FREQ_490                           2
#define MATCHING_FREQ_434                           3
#define MATCHING_FREQ_280                           4
#define MATCHING_FREQ_169                           5
#define MATCHING_FREQ_868                           6

#define AUTO_RX_TX_OFFSET                           2

#define CRC_IBM_SEED                                0xFFFF
#define CRC_CCITT_SEED                              0x1D0F

#define CRC_POLYNOMIAL_IBM                          0x8005
#define CRC_POLYNOMIAL_CCITT                        0x1021

#define REG_LR_CRCSEEDBASEADDR                      0x06BC
#define REG_LR_CRCPOLYBASEADDR                      0x06BE
#define REG_LR_WHITSEEDBASEADDR_MSB                 0x06B8
#define REG_LR_WHITSEEDBASEADDR_LSB                 0x06B9
#define REG_LR_PACKETPARAMS                         0x0704
#define REG_LR_PAYLOADLENGTH                        0x0702
#define REG_LR_SYNCWORDBASEADDRESS                  0x06C0
#define REG_LR_SYNCWORD                             0x0740

#define LORA_MAC_PRIVATE_SYNCWORD                   0x1424
#define LORA_MAC_PUBLIC_SYNCWORD                    0x3444

#define RANDOM_NUMBER_GENERATORBASEADDR             0x0819
#define REG_RX_GAIN                                 0x08AC
#define REG_FREQUENCY_ERRORBASEADDR                 0x076B
#define REG_XTA_TRIM                                0x0911

#define REG_OCP                                     0x08E7

enum RadioStates_t
{
  RF_IDLE = 0x00, // The radio is idle
  RF_RX_RUNNING,  // The radio is in reception state
  RF_TX_RUNNING,  // The radio is in transmission state
  RF_CAD,         // The radio is doing channel activity detection
};

enum RadioOperatingModes_t
{
  MODE_SLEEP = 0x00, // The radio is in sleep mode
  MODE_STDBY_RC,     // The radio is in standby mode with RC oscillator
  MODE_STDBY_XOSC,   // The radio is in standby mode with XOSC oscillator
  MODE_FS,           // The radio is in frequency synthesis mode
  MODE_TX,           // The radio is in transmit mode
  MODE_RX,           // The radio is in receive mode
  MODE_RX_DC,        // The radio is in receive duty cycle mode
  MODE_CAD           // The radio is in channel activity detection mode
};

enum RadioStandbyModes_t
{
  STDBY_RC   = 0x00,
  STDBY_XOSC = 0x01,
};

enum RadioRegulatorMode_t
{
  USE_LDO  = 0x00,  // default
  USE_DCDC = 0x01,
};

enum RadioRampTimes_t
{
  RADIO_RAMP_10_US   = 0x00,
  RADIO_RAMP_20_US   = 0x01,
  RADIO_RAMP_40_US   = 0x02,
  RADIO_RAMP_80_US   = 0x03,
  RADIO_RAMP_200_US  = 0x04,
  RADIO_RAMP_800_US  = 0x05,
  RADIO_RAMP_1700_US = 0x06,
  RADIO_RAMP_3400_US = 0x07,
};

enum RadioPacketTypes_t
{
  PACKET_TYPE_GFSK = 0x00,
  PACKET_TYPE_LORA = 0x01,
  PACKET_TYPE_NONE = 0x0F,
};

enum RadioLoRaCadSymbols_t
{
  LORA_CAD_01_SYMBOL = 0x00,
  LORA_CAD_02_SYMBOL = 0x01,
  LORA_CAD_04_SYMBOL = 0x02,
  LORA_CAD_08_SYMBOL = 0x03,
  LORA_CAD_16_SYMBOL = 0x04,
};

enum RadioCadExitModes_t
{
  LORA_CAD_ONLY = 0x00,
  LORA_CAD_RX = 0x01,
  LORA_CAD_LBT = 0x10,
};

enum RadioModShapings_t
{
  MOD_SHAPING_OFF                         = 0x00,
  MOD_SHAPING_G_BT_03                     = 0x08,
  MOD_SHAPING_G_BT_05                     = 0x09,
  MOD_SHAPING_G_BT_07                     = 0x0A,
  MOD_SHAPING_G_BT_1                      = 0x0B,
};

enum RadioRxBandwidth_t
{
  RX_BW_4800                              = 0x1F,
  RX_BW_5800                              = 0x17,
  RX_BW_7300                              = 0x0F,
  RX_BW_9700                              = 0x1E,
  RX_BW_11700                             = 0x16,
  RX_BW_14600                             = 0x0E,
  RX_BW_19500                             = 0x1D,
  RX_BW_23400                             = 0x15,
  RX_BW_29300                             = 0x0D,
  RX_BW_39000                             = 0x1C,
  RX_BW_46900                             = 0x14,
  RX_BW_58600                             = 0x0C,
  RX_BW_78200                             = 0x1B,
  RX_BW_93800                             = 0x13,
  RX_BW_117300                            = 0x0B,
  RX_BW_156200                            = 0x1A,
  RX_BW_187200                            = 0x12,
  RX_BW_234300                            = 0x0A,
  RX_BW_312000                            = 0x19,
  RX_BW_373600                            = 0x11,
  RX_BW_467000                            = 0x09,
};

enum RadioLoRaSpreadingFactors_t
{
    LORA_SF5                                = 0x05,
    LORA_SF6                                = 0x06,
    LORA_SF7                                = 0x07,
    LORA_SF8                                = 0x08,
    LORA_SF9                                = 0x09,
    LORA_SF10                               = 0x0A,
    LORA_SF11                               = 0x0B,
    LORA_SF12                               = 0x0C,
};

enum RadioLoRaBandwidths_t
{
  LORA_BW_500                             = 6,
  LORA_BW_250                             = 5,
  LORA_BW_125                             = 4,
  LORA_BW_062                             = 3,
  LORA_BW_041                             = 10,
  LORA_BW_031                             = 2,
  LORA_BW_020                             = 9,
  LORA_BW_015                             = 1,
  LORA_BW_010                             = 8,
  LORA_BW_007                             = 0,
};

enum RadioLoRaCodingRates_t
{
  LORA_CR_4_5                             = 0x01,
  LORA_CR_4_6                             = 0x02,
  LORA_CR_4_7                             = 0x03,
  LORA_CR_4_8                             = 0x04,
};

enum RadioPreambleDetection_t
{
  RADIO_PREAMBLE_DETECTOR_OFF             = 0x00,         //!< Preamble detection length off
  RADIO_PREAMBLE_DETECTOR_08_BITS         = 0x04,         //!< Preamble detection length 8 bits
  RADIO_PREAMBLE_DETECTOR_16_BITS         = 0x05,         //!< Preamble detection length 16 bits
  RADIO_PREAMBLE_DETECTOR_24_BITS         = 0x06,         //!< Preamble detection length 24 bits
  RADIO_PREAMBLE_DETECTOR_32_BITS         = 0x07,         //!< Preamble detection length 32 bit
};

enum RadioAddressComp_t
{
  RADIO_ADDRESSCOMP_FILT_OFF              = 0x00,         //!< No correlator turned on, i.e. do not search for SyncWord
  RADIO_ADDRESSCOMP_FILT_NODE             = 0x01,
  RADIO_ADDRESSCOMP_FILT_NODE_BROAD       = 0x02,
};

enum RadioPacketLengthModes_t
{
  RADIO_PACKET_FIXED_LENGTH               = 0x00,         //!< The packet is known on both sides, no header included in the packet
  RADIO_PACKET_VARIABLE_LENGTH            = 0x01,         //!< The packet is on variable size, header included
};

enum RadioCrcTypes_t
{
  RADIO_CRC_OFF                           = 0x01, // No CRC in use
  RADIO_CRC_1_BYTES                       = 0x00,
  RADIO_CRC_2_BYTES                       = 0x02,
  RADIO_CRC_1_BYTES_INV                   = 0x04,
  RADIO_CRC_2_BYTES_INV                   = 0x06,
  RADIO_CRC_2_BYTES_IBM                   = 0xF1,
  RADIO_CRC_2_BYTES_CCIT                  = 0xF2,
};

enum RadioDcFree_t
{
  RADIO_DC_FREE_OFF                       = 0x00,
  RADIO_DC_FREEWHITENING                  = 0x01,
};

enum RadioLoRaPacketLengthsMode_t
{
  LORA_PACKET_VARIABLE_LENGTH             = 0x00,         // The packet is on variable size, header included
  LORA_PACKET_FIXED_LENGTH                = 0x01,         // The packet is known on both sides, no header included in the packet
  LORA_PACKET_EXPLICIT                    = LORA_PACKET_VARIABLE_LENGTH,
  LORA_PACKET_IMPLICIT                    = LORA_PACKET_FIXED_LENGTH,
};

enum RadioLoRaCrcModes_t
{
  LORA_CRC_ON                             = 0x01, // CRC activated
  LORA_CRC_OFF                            = 0x00, // CRC not used
};

enum RadioLoRaIQModes_t
{
  LORA_IQ_NORMAL                          = 0x00,
  LORA_IQ_INVERTED                        = 0x01,
};

enum RadioTcxoCtrlVoltage_t
{
  TCXO_CTRL_1_6V                          = 0x00,
  TCXO_CTRL_1_7V                          = 0x01,
  TCXO_CTRL_1_8V                          = 0x02,
  TCXO_CTRL_2_2V                          = 0x03,
  TCXO_CTRL_2_4V                          = 0x04,
  TCXO_CTRL_2_7V                          = 0x05,
  TCXO_CTRL_3_0V                          = 0x06,
  TCXO_CTRL_3_3V                          = 0x07,
};

enum RadioIrqMasks_t
{
  IRQ_RADIO_NONE                          = 0x0000,
  IRQ_TX_DONE                             = 0x0001,
  IRQ_RX_DONE                             = 0x0002,
  IRQ_PREAMBLE_DETECTED                   = 0x0004,
  IRQ_SYNCWORD_VALID                      = 0x0008,
  IRQ_HEADER_VALID                        = 0x0010,
  IRQ_HEADER_ERROR                        = 0x0020,
  IRQ_CRC_ERROR                           = 0x0040,
  IRQ_CAD_DONE                            = 0x0080,
  IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
  IRQ_RX_TX_TIMEOUT                       = 0x0200,
  IRQ_RADIO_ALL                           = 0xFFFF,
};

enum RadioCommands_t
{
  RADIO_GET_STATUS                        = 0xC0,
  RADIO_WRITE_REGISTER                    = 0x0D,
  RADIO_READ_REGISTER                     = 0x1D,
  RADIO_WRITE_BUFFER                      = 0x0E,
  RADIO_READ_BUFFER                       = 0x1E,
  RADIO_SET_SLEEP                         = 0x84,
  RADIO_SET_STANDBY                       = 0x80,
  RADIO_SET_FS                            = 0xC1,
  RADIO_SET_TX                            = 0x83,
  RADIO_SET_RX                            = 0x82,
  RADIO_SET_RXDUTYCYCLE                   = 0x94,
  RADIO_SET_CAD                           = 0xC5,
  RADIO_SET_TXCONTINUOUSWAVE              = 0xD1,
  RADIO_SET_TXCONTINUOUSPREAMBLE          = 0xD2,
  RADIO_SET_PACKETTYPE                    = 0x8A,
  RADIO_GET_PACKETTYPE                    = 0x11,
  RADIO_SET_RFFREQUENCY                   = 0x86,
  RADIO_SET_TXPARAMS                      = 0x8E,
  RADIO_SET_PACONFIG                      = 0x95,
  RADIO_SET_CADPARAMS                     = 0x88,
  RADIO_SET_BUFFERBASEADDRESS             = 0x8F,
  RADIO_SET_MODULATIONPARAMS              = 0x8B,
  RADIO_SET_PACKETPARAMS                  = 0x8C,
  RADIO_GET_RXBUFFERSTATUS                = 0x13,
  RADIO_GET_PACKETSTATUS                  = 0x14,
  RADIO_GET_RSSIINST                      = 0x15,
  RADIO_GET_STATS                         = 0x10,
  RADIO_RESET_STATS                       = 0x00,
  RADIO_CFG_DIOIRQ                        = 0x08,
  RADIO_GET_IRQSTATUS                     = 0x12,
  RADIO_CLR_IRQSTATUS                     = 0x02,
  RADIO_CALIBRATE                         = 0x89,
  RADIO_CALIBRATEIMAGE                    = 0x98,
  RADIO_SET_REGULATORMODE                 = 0x96,
  RADIO_GET_ERROR                         = 0x17,
  RADIO_CLR_ERROR                         = 0x07,
  RADIO_SET_TCXOMODE                      = 0x97,
  RADIO_SET_TXFALLBACKMODE                = 0x93,
  RADIO_SET_RFSWITCHMODE                  = 0x9D,
  RADIO_SET_STOPRXTIMERONPREAMBLE         = 0x9F,
  RADIO_SET_LORASYMBTIMEOUT               = 0xA0,
};

struct ModulationParams_t
{
  RadioLoRaSpreadingFactors_t SpreadingFactor;     // Spreading Factor for the LoRa modulation
  RadioLoRaBandwidths_t       Bandwidth;           // Bandwidth for the LoRa modulation
  RadioLoRaCodingRates_t      CodingRate;          // Coding rate for the LoRa modulation
  uint8_t                     LowDatarateOptimize; // Indicates if the modem uses the low datarate optimization
};

struct PacketParams_t
{
  uint16_t            PreambleLength; // The preamble length is the number of LoRa symbols in the preamble
  uint8_t             PayloadLength;  // Size of the payload in the LoRa packet
  RadioLoRaCrcModes_t CrcMode;        // Size of CRC block in LoRa packet
};

struct PacketStatus_t
{
  int8_t RssiPkt;       // The RSSI of the last packet
  int8_t SnrPkt;        // The SNR of the last packet
  int8_t SignalRssiPkt;
  uint32_t FreqError;
};

struct RxCounter_t
{
  uint16_t PacketReceived;
  uint16_t CrcOk;
  uint16_t LengthError;
};

union CalibrationParams_t
{
  struct
  {
    uint8_t RC64KEnable:1;    // Calibrate RC64K clock
    uint8_t RC13MEnable:1;    // Calibrate RC13M clock
    uint8_t PLLEnable:1;      // Calibrate PLL
    uint8_t ADCPulseEnable:1; // Calibrate ADC Pulse
    uint8_t ADCBulkNEnable:1; // Calibrate ADC bulkN
    uint8_t ADCBulkPEnable:1; // Calibrate ADC bulkP
    uint8_t ImgEnable:1;
    uint8_t Reserved:1;
  } Fields;
  uint8_t Value;
};

union SleepParams_t
{
  struct
  {
    uint8_t WakeUpRTC:1; // Get out of sleep mode if wakeup signal received from RTC
    uint8_t Reset:1;
    uint8_t WarmStart:1;
    uint8_t Reserved:5;
  } Fields;
  uint8_t Value;
};

union RadioError_t
{
  struct
  {
    uint8_t Rc64kCalib:1; // RC 64kHz oscillator calibration failed
    uint8_t Rc13mCalib:1; // RC 13MHz oscillator calibration failed
    uint8_t PllCalib:1;   // PLL calibration failed
    uint8_t AdcCalib:1;   // ADC calibration failed
    uint8_t ImgCalib:1;   // Image calibration failed
    uint8_t XoscStart:1;  // XOSC oscillator failed to start
    uint8_t PllLock:1;    // PLL lock failed
    uint8_t BuckStart:1;  // Buck converter failed to start
    uint8_t PaRamp:1;     // PA ramp failed
    uint8_t Reserved:7;
  } Fields;
  uint16_t Value;
};

struct Modulation_t
{
  uint8_t Bandwidth;
  uint8_t CodingRate;
  uint8_t SpreadingFactor;
};

#endif // SX1268_DEF_H_
