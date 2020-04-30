
#ifndef __PLATFORM_CONF_H__
#define __PLATFORM_CONF_H__

#include <DAVE.h>
#include <elle/src/platform/xmc4700/stacks.h>
#include <elle/src/platform/xmc4700/type.h>
#include <elle/src/modules/auxmods.h>
#include <elle/src/platform/xmc4700/stacks.h>
#include <elle/inc/elua_int.h>
#include <elle/src/platform/xmc4700/lcd.h>

#define BUILD_CON_GENERIC
#define BUILD_SHELL
#define BUILD_TERM
#define BUILD_MMCFS
#define BUILD_ADVANCED_SHELL
//#define BUILD_LINENOISE
#define BUILD_EDITOR_ED
#define BUILD_XMODEM
#define BUILD_LUA_COMPILER
#define BUILD_TOY_COMPILER
#define BUILD_ELLE_SELF_HOSTED_MACHINE

// *****************************************************************************
// UART/Timer IDs configuration data (used in main.c)

#define CON_UART_ID           0
#define CON_UART_TFT          1
#define CON_UART_SPEED        115200
#if !defined( BUILD_ELLE_SELF_HOSTED_MACHINE )
# define TERM_LINES           25
# define TERM_COLS            80
#else
# define TERM_LINES           LCD_ROWS
# define TERM_COLS            LCD_COLS
#endif

#define PLATFORM_HAS_SYSTIMER

#ifdef BUILD_ADC
#define ADCLINE _ROM( AUXLIB_ADC, luaopen_adc, adc_map )
#else
#define ADCLINE
#endif

#if defined( ELUA_BOOT_RPC ) && !defined( BUILD_RPC )
#define BUILD_RPC
#endif

#if defined( BUILD_RPC )
#define RPCLINE _ROM( AUXLIB_RPC, luaopen_rpc, rpc_map )
#else
#define RPCLINE
#endif

#ifdef PS_LIB_TABLE_NAME
#define PLATLINE _ROM( PS_LIB_TABLE_NAME, luaopen_platform, platform_map )
#else
#define PLATLINE
#endif

#define LUA_PLATFORM_LIBS_ROM\
  _ROM( AUXLIB_PD, luaopen_pd, pd_map )\
  _ROM( AUXLIB_TERM, luaopen_term, term_map )\
  _ROM( AUXLIB_PACK, luaopen_pack, pack_map )\
  _ROM( AUXLIB_BIT, luaopen_bit, bit_map )\
  _ROM( AUXLIB_CPU, luaopen_cpu, cpu_map )\
  _ROM( AUXLIB_ELUA, luaopen_elua, elua_map )\
  _ROM( LUA_MATHLIBNAME, luaopen_math, math_map )\
  _ROM( AUXLIB_PIO, luaopen_pio, pio_map )\
  PLATLINE

// *****************************************************************************
// Configuration data

#define EGC_INITIAL_MODE      1

// Number of resources (0 if not available/not implemented)
#define NUM_PIO               16
#define NUM_SPI               0
#define NUM_UART              1
#define NUM_TIMER             0
#define NUM_PHYS_TIMER        0
#define NUM_PWM               0
#define NUM_ADC               0
#define NUM_CAN               0

// PIO prefix ('0' for P0, P1, ... or 'A' for PA, PB, ...)
#define PIO_PREFIX            '0'
// Pins per port configuration:
// #define PIO_PINS_PER_PORT (n) if each port has the same number of pins, or
// #define PIO_PIN_ARRAY { n1, n2, ... } to define pins per port in an array
// Use #define PIO_PINS_PER_PORT 0 if this isn't needed
#define PIO_PIN_ARRAY         { 16, 16, 16, 16, 8, 12, 7, 0, 0, 0, 0, 0, 0, 0, 14, 12 }

#define LINENOISE_HISTORY_SIZE_LUA    50
#define LINENOISE_HISTORY_SIZE_SHELL  10

// Interrupt queue size
#define PLATFORM_INT_QUEUE_LOG_SIZE 5

// Allocator data: define your free memory zones here in two arrays
// (start address and end address)
#define MEM_START_ADDRESS     { ( void* )Heap_Bank1_Start }
#define MEM_END_ADDRESS       { ( void* )Heap_Bank1_End }
#define CPU_FREQUENCY         OSCHP_GetFrequency()
#define ELLE_PLATFORM         XMC-4700
#define ELLE_CPU              XMC-4700F144K2048
#define ELLE_BOARD            XMC-4700: Relax kit

#endif // #ifndef __PLATFORM_CONF_H__

