#include "GetService.h"
// services
#include "../Services/Players/Players.h"
#include "../Services/Chat/ChatService.h"
// utils
#include "../../net/Minecraft.h"
#include "../../src/Java.h"
#include <iostream>

static Minecraft* g_minecraft = nullptr;

void initMinecraft() {
    if (!g_minecraft) {
        g_minecraft = new Minecraft();
    }
}

int lua_GetService(lua_State* L) {
    const char* serviceName = luaL_checkstring(L, 2);
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env) {
        std::cerr << "[!] Failed to get JNI environment" << std::endl;
        return luaL_error(L, "JNI environment not available");
    }

    if (strcmp(serviceName, "Players") == 0) {
        initMinecraft();
        if (!g_minecraft) {
            std::cerr << "[!] Failed to initialize Minecraft" << std::endl;
            return luaL_error(L, "Failed to initialize Minecraft");
        }

        jobject player = g_minecraft->getPlayer();
        if (!player) {
            std::cerr << "[!] Failed to get player object" << std::endl;
            return luaL_error(L, "Failed to get player object");
        }

        jobject globalPlayer = env->NewGlobalRef(player);
        if (!globalPlayer || env->ExceptionCheck()) {
            env->ExceptionClear();
            std::cerr << "[!] Failed to create global reference" << std::endl;
            return luaL_error(L, "Failed to create global reference");
        }

        luaL_checkstack(L, 10, "Not enough stack space");
        lua_newtable(L);

        lua_newtable(L);
        lua_pushlightuserdata(L, globalPlayer);
        lua_setfield(L, -2, "__userdata");

        lua_pushcfunction(L, lua_dropItem);
        lua_setfield(L, -2, "dropItem");

        lua_newtable(L);
        lua_pushlightuserdata(L, globalPlayer);
        lua_setfield(L, -2, "__userdata");

        lua_pushcfunction(L, lua_setSprinting);
        lua_setfield(L, -2, "setSprinting");
        lua_pushcfunction(L, lua_isSprinting);
        lua_setfield(L, -2, "isSprinting");
        lua_pushcfunction(L, lua_isCrouching);
        lua_setfield(L, -2, "isCrouching");
        lua_pushcfunction(L, lua_getX);
        lua_setfield(L, -2, "getX");
        lua_pushcfunction(L, lua_getY);
        lua_setfield(L, -2, "getY");
        lua_pushcfunction(L, lua_getZ);
        lua_setfield(L, -2, "getZ");

        lua_setfield(L, -2, "Character");
        lua_setfield(L, -2, "LocalPlayer");

        lua_newtable(L);
        lua_pushcfunction(L, [](lua_State* L) -> int {
            lua_getfield(L, 1, "LocalPlayer");
            if (lua_istable(L, -1)) {
                lua_getfield(L, -1, "__userdata");
                if (lua_islightuserdata(L, -1)) {
                    jobject globalRef = static_cast<jobject>(lua_touserdata(L, -1));
                    JNIEnv* env = javaVmManager->GetJNIEnv();
                    if (env && globalRef) {
                        env->DeleteGlobalRef(globalRef);
                    }
                }
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
            return 0;
            });
        lua_setfield(L, -2, "__gc");
        lua_setmetatable(L, -2);

        return 1;
    }
    else if (strcmp(serviceName, "ChatService") == 0) {
        lua_newtable(L);
        lua_pushcfunction(L, lua_sendMessage);
        lua_setfield(L, -2, "sendMessage");
        return 1;
    }

    std::cerr << "[!] Unknown service: " << serviceName << std::endl;
    return luaL_error(L, "Unknown service: %s", serviceName);
}

void cleanupServices() {
    if (g_minecraft) {
        delete g_minecraft;
        g_minecraft = nullptr;
    }
}