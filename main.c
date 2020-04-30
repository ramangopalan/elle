
#include <DAVE.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <elle/src/platform/xmc4700/type.h>
#include <elle/inc/newlib/devman.h>
#include <elle/inc/platform.h>
#include <elle/inc/romfs.h>                           /* ROM file system */
#include <elle/inc/xmodem.h>
#include <elle/inc/shell.h>                           /* Shell interface */
#include <elle/src/lua/lua.h>
#include <elle/src/lua/lauxlib.h>
#include <elle/src/lua/lualib.h>
#include <elle/inc/term.h>                            /* Terminal */
#include <elle/src/platform/xmc4700/platform_conf.h>  /* Platform configuration */
#include <elle/inc/elua_rfs.h>                        /* Remote file system */
#include <elle/src/platform/xmc4700/ps2.h>            /* Keyboard drivers */
#include <elle/src/platform/xmc4700/lcd.h>            /* 16x4 LCD module */
#ifdef ELUA_SIMULATOR
#include "hostif.h"
#endif

// Validate eLua configuratin options
#include <elle/inc/validate.h>

#include <elle/inc/mmcfs.h>
#include <elle/inc/romfs.h>
#include <elle/inc/semifs.h>

// Define here your autorun/boot files,
// in the order you want eLua to search for them
char *boot_order[] = {
#if defined(BUILD_MMCFS)
  "/mmc/autorun.lua",
  "/mmc/autorun.lc",
#endif
#if defined(BUILD_ROMFS)
  "/rom/autorun.lua",
  "/rom/autorun.lc",
#endif
};

extern char etext[];

#if defined ( BUILD_ELLE_SELF_HOSTED_MACHINE )

lcd_t lcd; /* LCD instance */

/*
 * A skull glyph, signifying the lambda suture, N. :)
 * Skull from https://www.makerguides.com/character-lcd-arduino-tutorial/
 */
static uint8_t lcd_skull[] = {
  0B00000,
  0B01110,
  0B10101,
  0B11011,
  0B01110,
  0B01110,
  0B00000,
  0B00000
};

#endif /* #if defined ( BUILD_ELLE_SELF_HOSTED_MACHINE ) */

#ifdef ELUA_BOOT_RPC

#ifndef RPC_UART_ID
  #define RPC_UART_ID     CON_UART_ID
#endif

#ifndef RPC_TIMER_ID
  #define RPC_TIMER_ID    PLATFORM_TIMER_SYS_ID
#endif

#ifndef RPC_UART_SPEED
  #define RPC_UART_SPEED  CON_UART_SPEED
#endif

void boot_rpc( void )
{
  lua_State *L = lua_open();
  luaL_openlibs(L);  /* open libraries */

  // Set up UART for 8N1 w/ adjustable baud rate
  platform_uart_setup( RPC_UART_ID, RPC_UART_SPEED, 8, PLATFORM_UART_PARITY_NONE, PLATFORM_UART_STOPBITS_1 );

  // Start RPC Server
  lua_getglobal( L, "rpc" );
  lua_getfield( L, -1, "server" );
  lua_pushnumber( L, RPC_UART_ID );
  lua_pushnumber( L, RPC_TIMER_ID );
  lua_pcall( L, 2, 0, 0 );
}
#endif

// ****************************************************************************
//  Program entry point

int main( void )
{
  int i;
  FILE* fp;

  // Initialize platform first
  if( platform_init() != PLATFORM_OK )
  {
    // This should never happen
    while( 1 );
  }

  // Initialize device manager
  dm_init();

  // Register the ROM filesystem
  romfs_init();

  // Register the MMC filesystem
  mmcfs_init();

  // Register the Semihosting filesystem
  semifs_init();

  // Register the remote filesystem
  remotefs_init();

#if defined (BUILD_ELLE_SELF_HOSTED_MACHINE)
  // Initialize the keyboard driver
  ps2_begin(&ps2_keymap_us);

  // Initialize main LCD driver for the self hosted computer.
  lcd_init_4bits_mode(&lcd);

  // Raman: N, you're now a part of Elle's easter egg - the
  // skull - signifying the lambda suture.
  lcd_create_char(&lcd, 1, lcd_skull);

  // Set initial cursor position
  lcd_set_cursor(&lcd, 0, 0);
#endif /* #if defined (BUILD_ELLE_SELF_HOSTED_MACHINE) */

  // Search for autorun files in the defined order and execute the 1st if found
  for( i = 0; i < sizeof( boot_order ) / sizeof( *boot_order ); i++ )
  {
    if( ( fp = fopen( boot_order[ i ], "r" ) ) != NULL )
    {
      fclose( fp );
      char* lua_argv[] = { "lua", boot_order[i], NULL };
      lua_main( 2, lua_argv );
      break; // autoruns only the first found
    }
  }

#ifdef ELUA_BOOT_RPC
  boot_rpc();
#else

  // Run the shell
  if( shell_init() == 0 )
  {
    // Start Lua directly
    char* lua_argv[] = { "lua", NULL };
    lua_main( 1, lua_argv );
  }
  else
    shell_start();
#endif // #ifdef ELUA_BOOT_RPC

#ifdef ELUA_SIMULATOR
  hostif_exit(0);
  return 0;
#else
  while( 1 );
#endif
}
