#include "Players.h"
#include "../../src/Java.h"
#include "../../net/Minecraft.h"
#include "../../net/minecraft/Players/LocalPlayer.h"

#include "../../../net/minecraft/Players/EntityPlayerSP.h"

int lua_setSprinting(lua_State* L) {
    if (!lua_isboolean(L, 2)) {
        return luaL_error(L, "Expected boolean argument for setSprinting");
    }

    bool sprinting = lua_toboolean(L, 2);

    lua_getfield(L, 1, "__userdata");
    jobject playerObj = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!playerObj) {
        return luaL_error(L, "Invalid player userdata");
    }

    EntityPlayerSP playerWrapper;
    playerWrapper.setSprinting(sprinting);

    return 0;
}


int lua_isSprinting(lua_State* L) {
    lua_getfield(L, 1, "__userdata");
    jobject player = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!player) {
        lua_pushboolean(L, false);
        return 1;
    }

    bool result = false;
    LocalPlayer::isSprinting(&result);

    lua_pushboolean(L, result);
    return 1;
}

int lua_isCrouching(lua_State* L) {
    lua_getfield(L, 1, "__userdata");
    jobject player = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!player) {
        lua_pushboolean(L, false);
        return 1;
    }

    bool result = false;
    LocalPlayer::isCrouching(&result);

    lua_pushboolean(L, result);
    return 1;
}