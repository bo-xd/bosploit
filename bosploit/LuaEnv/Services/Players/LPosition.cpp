#include "Players.h"
#include "../../../net/minecraft/Players/EntityPlayerSP.h"

int lua_getX(lua_State* L) {
    lua_getfield(L, 1, "__userdata");
    jobject character = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!character) {
        lua_pushnumber(L, 0);
        return 1;
    }

    EntityPlayerSP playerWrapper;
    double x = playerWrapper.x();

    lua_pushnumber(L, x);
    return 1;
}

int lua_getY(lua_State* L) {
    lua_getfield(L, 1, "__userdata");
    jobject character = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!character) {
        lua_pushnumber(L, 0);
        return 1;
    }

    EntityPlayerSP playerWrapper;
    double y = playerWrapper.y();


    lua_pushnumber(L, y);
    return 1;
}

int lua_getZ(lua_State* L) {
    lua_getfield(L, 1, "__userdata");
    jobject character = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!character) {
        lua_pushnumber(L, 0);
        return 1;
    }

    EntityPlayerSP playerWrapper;
    double z = playerWrapper.z();

    lua_pushnumber(L, z);
    return 1;
}
