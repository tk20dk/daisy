#include <system.h>


extern "C" UART_HandleTypeDef huart1;

int putchar( char const ch )
{
  if( ch == '\n' )
  {
    char cr = '\r';
    auto const Status = HAL_UART_Transmit( &huart1, (uint8_t*)&cr, 1, 50U );
    assert_param( Status == HAL_OK );
  }

  auto const Status = HAL_UART_Transmit( &huart1, (uint8_t*)&ch, 1, 50U );
  assert_param( Status == HAL_OK );

  return 0;
}

void UartPrintf( char const *const Format, ... )
{
  char Buffer[ 256 ];
  va_list Args;
  va_start( Args, Format );
  int const Result = vsnprintf( Buffer, sizeof( Buffer ), Format, Args );
  va_end( Args );

  for( auto Index = 0; Index < Result; Index ++ )
  {
    putchar( Buffer[ Index ] );
  }
}

extern "C" char usbgetchar(void);
char const* UsbGetLine()
{
  static char Data[ 128 ];
  static uint32_t Length;

  char Char = usbgetchar();
  if(( Char == '\0' ) || ( Char == '\n' ))
  {
    return nullptr;
  }

  if( Char == '\r' )
  {
    Data[ Length ] = '\0';
    Length = 0;
    return Data;
  }

  Data[ Length++ ] = Char;
  return nullptr;
}

char const* UartGetLine()
{
  static char Data[ 256 ];
  static uint32_t Length;

  char Char;
  auto Status = HAL_UART_Receive( &huart1, (uint8_t*)&Char, 1, 0 );
  if( Status == HAL_TIMEOUT )
  {
    return nullptr;
  }

  if( Char == '\r' )
  {
    Data[ Length ] = '\0';
    Length = 0;
    return Data;
  }

  Data[ Length++ ] = Char;

  if(( Length + 1 ) == sizeof( Data ))
  {
    Data[ Length ] = '\0';
    Length = 0;
    return Data;
  }

  return nullptr;
}

void UsbPrintf( char const *const Format, ... )
{
  static int Length;
  static char Buffer[ 512 ];
  va_list Args;

  va_start( Args, Format );
  Length += vsnprintf( &Buffer[ Length ], sizeof( Buffer ) - Length, Format, Args );
  va_end( Args );

  if( Length > 0 )
  {
    auto Status = CDC_Transmit_FS( reinterpret_cast<uint8_t*>( Buffer ), static_cast<uint16_t>( Length ));
    if( Status != USBD_BUSY )
    {
      Length = 0;
    }
  }
}
