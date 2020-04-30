// Module for interfacing with platform data

#include <elle/src/modules/auxmods.h>
#include <elle/src/platform/xmc4700/platform_conf.h>
#include <elle/src/lua/lua.h>
#include <elle/src/lua/lualib.h>
#include <elle/src/lua/lauxlib.h>
#include <elle/inc/platform.h>
#include <elle/src/lua/lrotable.h>

#define MACRO_NAME( x ) MACRO_AGAIN( x )
#define MACRO_AGAIN( x ) #x

// Lua: platform = platform()
static int pd_platform( lua_State* L )
{
  lua_pushstring( L, MACRO_NAME( ELLE_PLATFORM ) );
  return 1;
}

// Lua: cpuname = cpu()
static int pd_cpu( lua_State* L )
{
  lua_pushstring( L, MACRO_NAME( ELLE_CPU ) );
  return 1;
}

// Lua: boardname = board()
static int pd_board( lua_State* L )
{
  lua_pushstring( L, MACRO_NAME( ELLE_BOARD ) );
  return 1;
}

// Module function map
#define MIN_OPT_LEVEL 2
#include <elle/src/lua/lrodefs.h>
const LUA_REG_TYPE pd_map[] = 
{
  { LSTRKEY( "platform" ), LFUNCVAL( pd_platform ) }, 
  { LSTRKEY( "cpu" ), LFUNCVAL( pd_cpu ) },
  { LSTRKEY( "board" ), LFUNCVAL( pd_board ) },
  { LNILKEY, LNILVAL }
};

LUALIB_API int luaopen_pd( lua_State* L )
{
  LREGISTER( L, AUXLIB_PD, pd_map );
}
