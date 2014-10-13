#ifndef LUAAPI_H
#define LUAAPI_H

extern "C" {

#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>

lua_State *chdkptp_init(int argc, char ** argv);
int chdkptp_exit(lua_State *L);

}

#include <LuaIntf/LuaIntf.h>

#endif // LUAAPI_H
