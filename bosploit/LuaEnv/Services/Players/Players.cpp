#include "Players.h"
#include "../../src/Java.h"
#include "../../net/Minecraft.h"
#include "../../net/minecraft/Players/LocalPlayer.h"

int lua_getPlayer(lua_State* L) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = LocalPlayer::getPlayer();

    if (!player || !env) {
        lua_pushnil(L);
        return 1;
    }

    jobject globalPlayer = env->NewGlobalRef(player);
    lua_pushlightuserdata(L, globalPlayer);
    return 1;
}

int lua_setSprinting(lua_State* L) {
    if (!lua_isboolean(L, 2)) {
        return luaL_error(L, "Expected boolean argument for setSprinting");
    }

    bool sprinting = lua_toboolean(L, 2);

    lua_getfield(L, 1, "__userdata");
    jobject player = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!player) {
        return luaL_error(L, "Invalid player userdata");
    }

    LocalPlayer::setSprinting(sprinting);

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
