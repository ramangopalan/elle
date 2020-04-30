// Platform-dependent functions

#include <reent.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <DAVE.h>
#include <elle/inc/common.h>
#include <elle/inc/newlib/devman.h>
#include <elle/inc/newlib/genstd.h>
#include <elle/inc/platform.h>
#include <elle/inc/utils.h>
#include <elle/src/platform/xmc4700/platform_conf.h>
#include <elle/src/platform/xmc4700/stacks.h>
#include <elle/src/platform/xmc4700/type.h>

// Handles uart receive
uint8_t recv_byte;

// ****************************************************************************
// Function references

// ****************************************************************************
// Platform initialization

/* Main platform initialization */
int platform_init()
{
  DAVE_STATUS_t status = DAVE_Init();
  /* Can never go here. But just keeping it */
  if (status == DAVE_STATUS_FAILURE) {
    XMC_DEBUG(("DAVE Apps initialization failed with status %d\n", status));
    while (1U) {

    }
  }

  cmn_platform_init();

  return PLATFORM_OK;
}

// ****************************************************************************
// PIO

static XMC_GPIO_PORT_t *const pio_port[] =
{
  XMC_GPIO_PORT0,
  XMC_GPIO_PORT1,
  XMC_GPIO_PORT2,
  XMC_GPIO_PORT3,
  XMC_GPIO_PORT4,
  XMC_GPIO_PORT5,
  XMC_GPIO_PORT6,
  XMC_GPIO_PORT14,
  XMC_GPIO_PORT15
};

static void platformh_setup_pins( unsigned port, pio_type pinmask, u8 mask )
{
  unsigned i;
  u8 shift;
  XMC_GPIO_PORT_t *base = pio_port[ port ];

  for( i = 0; i < platform_pio_get_num_pins( port ); i ++ )
    if( pinmask & ( 1 << i ) )
    {
      shift = ( i & 3 ) << 3;
      base->IOCR[ i >> 2 ] = ( base->IOCR[ i >> 2 ] & ~( 0xFF << shift ) ) | ( mask << shift );
    }
}

pio_type platform_pio_op( unsigned port, pio_type pinmask, int op )
{
  pio_type retval = 1;
  XMC_GPIO_PORT_t *base = pio_port[ port ];

  switch( op )
  {
    case PLATFORM_IO_PORT_SET_VALUE:
      base->OUT = pinmask;
      break;

    case PLATFORM_IO_PIN_SET:
      base->OMR = pinmask;
      break;

    case PLATFORM_IO_PIN_CLEAR:
      base->OMR = pinmask << 16;
      break;

    case PLATFORM_IO_PORT_DIR_INPUT:
      base->IOCR[ 0 ] = base->IOCR[ 1 ] = 0;
      base->IOCR[ 2 ] = base->IOCR[ 3 ] = 0;
      break;

    case PLATFORM_IO_PIN_DIR_INPUT:
    case PLATFORM_IO_PIN_NOPULL:
      platformh_setup_pins( port, pinmask, 0 );
      break;

    case PLATFORM_IO_PORT_DIR_OUTPUT:
      base->IOCR[ 0 ] = base->IOCR[ 1 ] = 0x80808080;
      base->IOCR[ 2 ] = base->IOCR[ 3 ] = 0x80808080;
      break;

    case PLATFORM_IO_PIN_DIR_OUTPUT:
      platformh_setup_pins( port, pinmask, 0x80 );
      break;

    case PLATFORM_IO_PORT_GET_VALUE:
      retval = base->IN;
      break;

    case PLATFORM_IO_PIN_GET:
      retval = ( base->IN & pinmask ) ? 1 : 0;
      break;

    case PLATFORM_IO_PIN_PULLUP:
      platformh_setup_pins( port, pinmask, 0x10 );
      break;

    case PLATFORM_IO_PIN_PULLDOWN:
      platformh_setup_pins( port, pinmask, 0x08 );
      break;

    default:
      retval = 0;
      break;
  }
  return retval;
}

// ****************************************************************************
// Timer

u64 platform_timer_sys_raw_read()
{
  return SysTick->LOAD - SysTick->VAL;
}

void platform_timer_sys_disable_int()
{
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

void platform_timer_sys_enable_int()
{
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

timer_data_type platform_timer_read_sys()
{
  return cmn_systimer_get();
}

timer_data_type platform_s_timer_op( unsigned id, int op,timer_data_type data )
{
  return 0;
}

// ****************************************************************************
// UART

static UART_t *const system_uarts[] = {
  &PC_UART,
};

void elua_uart_rx_callback( void )
{
  // Enabled, but empty for now.
}

void elua_uart_tx_callback( void )
{
  // Enabled, but empty for now.
}

void platform_s_uart_send( unsigned id, u8 data )
{
  // Internally invokes DMA for transmit
  while( system_uarts[id]->runtime->tx_busy )
  {

  }
  UART_Transmit( system_uarts[id], &data, 1 );
}

int platform_s_uart_recv( unsigned id, timer_data_type timeout )
{
  UART_STATUS_t s;

  if( timeout == 0 )
  {
	s = UART_Receive( &PC_UART, &recv_byte, 1 );
    if( s != UART_STATUS_SUCCESS )
      return 0;
    else
      return recv_byte;
  }
  // Receive character blocking
  while( PC_UART.runtime->rx_busy );
  UART_Receive( &PC_UART, &recv_byte, 1 );
  return recv_byte;
}

int platform_s_uart_set_flow_control( unsigned id, int type )
{
  return PLATFORM_ERR;
}

u32 platform_uart_setup( unsigned id, u32 baud, int databits, int parity, int stopbits )
{
  return 0;
}

