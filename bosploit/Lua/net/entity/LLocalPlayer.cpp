#include "LLocalPlayer.h"

int lua_getPlayer(lua_State* L) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = LocalPlayer::getPlayer();

    if (!player || !env) {
        lua_pushnil(L);
        return true;
    }

    jobject globalPlayer = env->NewGlobalRef(player);
    lua_pushlightuserdata(L, globalPlayer);
    return true;
}

int lua_setSprinting(lua_State* L) {
    if (!lua_isboolean(L, 1)) {
        return luaL_error(L, "Expected boolean argument for setSprinting");
    }

    bool sprinting = lua_toboolean(L, 1);
    LocalPlayer::setSprinting(sprinting);
    return false;
}

int lua_isSprinting(lua_State* L) {
    bool result = false;
    LocalPlayer::isSprinting(&result);
    lua_pushboolean(L, result);
    return 1;
}
