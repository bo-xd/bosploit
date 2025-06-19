#include "Players.h"
#include "../../src/Java.h"
#include "../../net/Minecraft.h"
#include "../../net/minecraft/Players/LocalPlayer.h"

int lua_getY(lua_State* L) {
    lua_getfield(L, 1, "__userdata");
    jobject character = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!character) {
        lua_pushnumber(L, 0);
        return 1;
    }

    double y = 0.0;

    LocalPlayer::getY(&y);

    lua_pushnumber(L, y);
    return 1;
}

int lua_getX(lua_State* L) {
    lua_getfield(L, 1, "__userdata");
    jobject character = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!character) {
        lua_pushnumber(L, 0);
        return 1;
    }

    double y = 0.0;

    LocalPlayer::getX(&y);

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

    double y = 0.0;

    LocalPlayer::getZ(&y);

    lua_pushnumber(L, y);
    return 1;
}
