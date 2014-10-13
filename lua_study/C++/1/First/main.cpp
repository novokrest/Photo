#include <cstdio>
#include <cstring>

extern "C" {
#include <lua5.2/lua.h>
#include <lua5.2/lauxlib.h>
#include <lua5.2/lualib.h>
}

int main(int argc, char **argv) {
    char buff[256];
    int error;
    lua_State* L = lua_newstate();
    luaL_openlibs(L);
    
    while (fgets(buff, sizeof(buff), stdin) != nullptr) {
        error = luaL_loadstring(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s", lua_tolstring(L, -1, nullptr));
            lua_pop(L, 1);
        }
    }
    lua_close(L);
    return 0;
}
