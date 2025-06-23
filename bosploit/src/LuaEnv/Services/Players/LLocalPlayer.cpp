#include "LLocalPlayer.h"
#include "../../../net/Minecraft.h"
#include "../../../net/minecraft/Players/LocalPlayer.h"
#include "../../../utils/ClassLoader/ClassLoader.h"

namespace LuaBindings::LocalPlayer {
    int getPlayer(lua_State* L) {
        Minecraft mc;
        jobject player = mc.getPlayer();
        if (!player) {
            lua_pushnil(L);
            return 1;
        }
        jobject globalPlayer = g_classLoader->env->NewGlobalRef(player);
        lua_pushlightuserdata(L, globalPlayer);
        return 1;
    }

    int lua_setSprinting(lua_State* L) {
        if (!lua_isboolean(L, 2)) {
            lua_pushstring(L, "Expected a boolean argument for setSprinting");
            lua_error(L);
        }
        bool sprinting = lua_toboolean(L, 2);

        static ::LocalPlayer localPlayer;
        localPlayer.setSprinting((jboolean)sprinting);
        return 0;
    }

    int lua_getX(lua_State* L) {
        static ::LocalPlayer localPlayer;
        double x = localPlayer.x();
        lua_pushnumber(L, x);
        return 1;
    }

    int lua_getY(lua_State* L) {
        static ::LocalPlayer localPlayer;
        double y = localPlayer.y();
        lua_pushnumber(L, y);
        return 1;
    }

    int lua_getZ(lua_State* L) {
        static ::LocalPlayer localPlayer;
        double z = localPlayer.z();
        lua_pushnumber(L, z);
        return 1;
    }

    int lua_dropItem(lua_State* L) {
        if (!lua_isboolean(L, 2)) {
            lua_pushstring(L, "Expected boolean argument for drop");
            lua_error(L);
        }
        bool drop = lua_toboolean(L, 2);

        static ::LocalPlayer localPlayer;
        localPlayer.drop((jboolean)drop);
        return 0;
    }

    int lua_isSprinting(lua_State* L) {
        static ::LocalPlayer localPlayer;
        bool sprinting = localPlayer.isSprinting();
        lua_pushboolean(L, sprinting);
        return 1;
    }

    int lua_isCrouching(lua_State* L) {
        static ::LocalPlayer localPlayer;
        bool crouching = localPlayer.isCrouching();
        lua_pushboolean(L, crouching);
        return 1;
    }
}