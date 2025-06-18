#include "GetService.h"

// services
#include "../Services/Players/Players.h"
#include "../Services/Chat/ChatService.h"

// others
#include "../../net/minecraft/Players/LocalPlayer.h"
#include "../../src/Java.h"

int lua_GetService(lua_State* L) {
    const char* serviceName = luaL_checkstring(L, 2);

    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env) {
        lua_pushnil(L);
        return 1;
    }

    if (strcmp(serviceName, "Players") == 0) {
        jobject player = LocalPlayer::getPlayer();
        if (!player) {
            lua_pushnil(L);
            return 1;
        }

        jobject globalPlayer = env->NewGlobalRef(player);

        lua_newtable(L);

        lua_newtable(L);

        lua_pushlightuserdata(L, globalPlayer);
        lua_setfield(L, -2, "__userdata");

        lua_newtable(L);

        // Character table
        lua_pushlightuserdata(L, globalPlayer);
        lua_setfield(L, -2, "__userdata");

        lua_pushcfunction(L, lua_setSprinting);
        lua_setfield(L, -2, "setSprinting");

        lua_pushcfunction(L, lua_isSprinting);
        lua_setfield(L, -2, "isSprinting");

        lua_pushcfunction(L, lua_isCrouching);
		lua_setfield(L, -2, "isCrouching");

        lua_pushcfunction(L, lua_getY);
        lua_setfield(L, -2, "getY");
        lua_pushcfunction(L, lua_getX);
        lua_setfield(L, -2, "getX");
        lua_pushcfunction(L, lua_getX);
        lua_setfield(L, -2, "getZ");

        lua_setfield(L, -2, "Character");

        lua_setfield(L, -2, "LocalPlayer");

        return 1;
    }
    else if (strcmp(serviceName, "ChatService") == 0) {
        lua_newtable(L);

        lua_pushcfunction(L, lua_sendMessage);
        lua_setfield(L, -2, "sendMessage");

        return 1;
    }

    lua_pushnil(L);
    return 1;
}
