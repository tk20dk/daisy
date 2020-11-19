#include <cstdlib>
#include <cstring>
#include "system.h"
#include "gps.h"


TGps::TGps( UART_HandleTypeDef &huart ) :
  RxTmp(),
  TxTmp(),
  RxFlag( false ),
  TxFlag( false ),
  RxError( false ),
  RxData(),
  TxData(),
  RxLen( 0 ),
  TxLen( 0 ),
  RxHead( 0 ),
  TxHead( 0 ),
  RxTail( 0 ),
  TxTail( 0 ),
  huart( huart )
{
}

void TGps::Init()
{
  HAL_UART_Receive_IT( &huart, (uint8_t*)&RxTmp, 1 );
}

void TGps::Loop()
{
  auto Line = GetGpsLine();

  if( Line )
  {
    if( memcmp( Line, "$GPGLL", 6 ) == 0 )
    {
      ParseGLL( &Line[ 6 ] );
    }
    else if( memcmp( Line, "$GPRMC", 6 ) == 0 )
    {
//      UsbPrintf( Line );
      ParseRMC( &Line[ 6 ] );
    }
  }
}

// $GPGLL,5609.04359,N,00928.67676,E,075300.00,A,A*6C
void TGps::ParseGLL( char const *const Line )
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

  int32_t Value0;
  uint32_t Value1;
  TDataGLL Data;
  char const* Ptr = Line;

  // Latitude
  GetDecimal( Ptr, Value0, Value1 );
  Data.LatDeg = Value0 / 100;
  Data.LatMin = Value0 % 100;
  Data.LatSec = Value1;
  Data.LatSouth = ( GetChar( Ptr ) == 'S' );

  // Longitude
  GetDecimal( Ptr, Value0, Value1 );
  Data.LonDeg = Value0 / 100;
  Data.LonMin = Value0 % 100;
  Data.LonSec = Value1;
  Data.LonWest = ( GetChar( Ptr ) == 'W' );

  // Time
  GetDecimal( Ptr, Value0, Value1 );
  Data.Time = Value0;

  if( GetChar( Ptr ) != 'A' )
  {
    return;
  }

  if( GetChar( Ptr ) != 'A' )
  {
    return;
  }

  if( *Ptr == '*' )
  {
    DataGLL = Data;
  }

#pragma GCC diagnostic pop
}

// Recommended Minimum data
// $GPRMC,083559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A*57
// $GPRMC ,162103.00 ,A ,5609.04137 ,N ,00928.67938 ,E ,0.011 ,,200419,,,A*72\r\n""

void TGps::ParseRMC( char const *const Line )
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"

  int32_t Value0;
  uint32_t Value1;
  TDataRMC Data;
  char const* Ptr = Line;

  // Time
  GetDecimal( Ptr, Value0, Value1 );
  if( GetChar( Ptr ) != 'A' ) return;
  Data.Time = Value0;

  // Latitude
  GetDecimal( Ptr, Value0, Value1 );
  Data.LatDeg = Value0 / 100;
  Data.LatMin = Value0 % 100;
  Data.LatSec = Value1;
  Data.LatSouth = ( GetChar( Ptr ) == 'S' );

  // Longitude
  GetDecimal( Ptr, Value0, Value1 );
  Data.LonDeg = Value0 / 100;
  Data.LonMin = Value0 % 100;
  Data.LonSec = Value1;
  Data.LonWest = ( GetChar( Ptr ) == 'W' );

  // Speed over ground (1 knots = 1.852km/h)
  GetDecimal( Ptr, Value0, Value1 );
  Data.Speed = (( Value0 * 1000 + Value1 ) * 1852 ) / 1000;

  // Course over ground
  GetSkip( Ptr );

  // Date
  GetNumeric( Ptr, Value0 );

  // Magnetic variation value
  GetSkip( Ptr );

  // Magnetic variation E/W indicator
  GetSkip( Ptr );

  // Mode Indicator
  if( GetChar( Ptr ) != 'A' ) return;

  if( *Ptr == '*' )
  {
    DataRMC = Data;
  }

#pragma GCC diagnostic pop
}

char const* TGps::GetGpsLine()
{
  char const *Line = nullptr;

  if( RxFlag )
  {
    RxFlag = false;

    if( RxLen < sizeof( RxData ))
    {
      RxData[ RxHead ] = RxTmp;
      RxLen++;
      ++RxHead %= sizeof( RxData );
    }

    if( RxTmp == '\n' )
    {
      RxData[ RxHead ] = '\0';
      RxLen = 0;
      RxHead = 0;

      Line = ValidateChecksum( RxData ) ? RxData : nullptr;
    }

    HAL_UART_Receive_IT( &huart, (uint8_t*)&RxTmp, 1 );
  }

  return Line;
}

char TGps::GetChar( char const* &Line )
{
  if( Line == nullptr )
  {
    return '\0';
  }

  if( Line[ 0 ]  != ',' )
  {
    Line = nullptr;
    return '\0';
  }

  Line = &Line[ 2 ];
  return Line[ -1 ];
}

void TGps::GetSkip( char const* &Line )
{
  if( Line == nullptr )
  {
    return;
  }

  if( *Line++ != ',' )
  {
    Line = nullptr;
  }

  while( *Line != ',' )
  {
    Line++;
  }
}

void TGps::GetNumeric( char const* &Line, int32_t &Value0 )
{
  if( Line == nullptr )
  {
    return;
  }

  if( *Line++ != ',' )
  {
    Line = nullptr;
  }

  char *End;
  Value0 = strtol( Line, &End, 10 );
  if( End == Line )
  {
    Line = nullptr;
    return;
  }

  Line = End;
}

void TGps::GetDecimal( char const* &Line, int32_t &Value0, uint32_t &Value1 )
{
  if( Line == nullptr )
  {
    return;
  }

  if( Line[ 0 ] != ',' )
  {
    Line = nullptr;
  }

  char *End;
  char const* Start = &Line[ 1 ];
  Value0 = strtol( Start, &End, 10 );
  if( End == Start )
  {
    Line = nullptr;
    return;
  }

  if( *End++ != '.' )
  {
    Line = nullptr;
    return;
  }

  Start = End;
  Value1 = strtoul( Start, &End, 10 );
  if( End == Start )
  {
    Line = nullptr;
    return;
  }

  Line = End;
}

bool TGps::ValidateChecksum( char const *const Line )
{
  if(( Line == nullptr ) || ( Line[ 0 ] != '$' ))
  {
    return false;
  }

  auto Index = 1;
  uint8_t Sum = 0;
  while( Line[ Index ] )
  {
    if( Line[ Index ] == '*' )
    {
      break;
    }
    Sum = Sum ^ static_cast< uint8_t >( Line[ Index++ ] );
  }

  if( Line[ Index++ ] != '*' )
  {
    return false;
  }

  char *End;
  auto const Checksum = strtoul( &Line[ Index ], &End, 16 );
  if(( End == &Line[ Index ] ) || ( *End != '\r' ))
  {
    return false;
  }

  return Sum == Checksum;
}

void TGps::HAL_UART_RxCpltCallback( UART_HandleTypeDef const *const huart )
{
  (void)huart;
  RxFlag = true;
}

void TGps::HAL_UART_ErrorCallback( UART_HandleTypeDef const *const huart )
{
  (void)huart;
  RxError = true;
}

extern "C" void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart )
{
  Gps.HAL_UART_RxCpltCallback( huart );
}

extern "C" void HAL_UART_ErrorCallback( UART_HandleTypeDef *huart )
{
  Gps.HAL_UART_ErrorCallback( huart );
}
