#ifndef _LUABGC_HS_H
#define _LUABGC_HS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int lualibbgc_hs_create(lua_State* L);
int lualibbgc_hs_run(lua_State* L);


#endif
