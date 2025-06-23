#include "Players.h"
#include "../../../net/minecraft/Players/EntityPlayerSP.h"
#include "../../../Mappings/Mapping.h"
#include <iostream>

static EntityPlayerSP* g_playerWrapper = nullptr;

void initPlayerWrapper() {
    if (!g_playerWrapper) {
        g_playerWrapper = new EntityPlayerSP();
    }
}

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

    static jmethodID setSprinting_method = nullptr;
    if (!setSprinting_method) {
        setSprinting_method = Mapping::GetMethod("EntityPlayerSP", "setSprint");
        if (!setSprinting_method) {
            return luaL_error(L, "Could not find setSprinting method");
        }
    }

    if (!g_classLoader || !g_classLoader->env) {
        return luaL_error(L, "JNI environment not available");
    }

    g_classLoader->env->CallVoidMethod(playerObj, setSprinting_method, (jboolean)sprinting);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        return luaL_error(L, "JNI exception in setSprinting");
    }

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

    initPlayerWrapper();

    if (!g_playerWrapper) {
        lua_pushboolean(L, false);
        return 1;
    }

    bool result = false;
    try {
        result = g_playerWrapper->isSprinting();
    }
    catch (...) {
        std::cerr << "[!] Error in isSprinting" << std::endl;
        result = false;
    }

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

    initPlayerWrapper();

    if (!g_playerWrapper) {
        lua_pushboolean(L, false);
        return 1;
    }

    bool result = false;
    try {
        result = g_playerWrapper->isCrouching();
    }
    catch (...) {
        std::cerr << "[!] Error in isCrouching" << std::endl;
        result = false;
    }

    lua_pushboolean(L, result);
    return 1;
}

void cleanupPlayerWrapper() {
    if (g_playerWrapper) {
        delete g_playerWrapper;
        g_playerWrapper = nullptr;
    }
}