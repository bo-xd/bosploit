#include "Players.h"
#include "../../../net/Minecraft.h"

int lua_getPlayer(lua_State* L) {
    Minecraft mc;
    jobject player = mc.getPlayer();

    if (!player) {
        lua_pushnil(L);
        return 1;
    }

    jobject globalPlayer = player;
    lua_pushlightuserdata(L, globalPlayer);
    return 1;
}
