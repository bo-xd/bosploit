#include "init.h"
#include "Services/GetService.h"

void registerLuaEnv(lua_State* L) {
    lua_newtable(L);

    lua_pushcfunction(L, lua_GetService);
    lua_setfield(L, -2, "GetService");

    lua_newtable(L);

    lua_pushvalue(L, -2);
    lua_setfield(L, -2, "__index");

    lua_setmetatable(L, -2);

    lua_setglobal(L, "game");
}
