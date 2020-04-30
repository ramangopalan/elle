// Lua EGC (Emergeny Garbage Collector) interface

#include <elle/src/lua/legc.h>
#include <elle/src/lua/lstate.h>

void legc_set_mode(lua_State *L, int mode, unsigned limit) {
   global_State *g = G(L); 
   
   g->egcmode = mode;
   g->memlimit = limit;
}

