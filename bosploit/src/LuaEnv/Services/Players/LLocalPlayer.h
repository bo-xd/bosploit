#pragma once
#include <lua.hpp>

namespace LuaBindings::LocalPlayer {
    int getPlayer(lua_State* L);

    int lua_setSprinting(lua_State* L);
    int lua_dropItem(lua_State* L);

    int lua_isSprinting(lua_State* L);
    int lua_isCrouching(lua_State* L);

    int lua_getX(lua_State* L);
    int lua_getY(lua_State* L);
    int lua_getZ(lua_State* L);
}
