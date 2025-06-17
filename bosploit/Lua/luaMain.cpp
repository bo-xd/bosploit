#include "lua.hpp"

#include "net/entity/LLocalPlayer.h"
#include "net/LMinecraft.h"
#include "utils/utils.h"

void registerLuaFunctions(lua_State* L) {
	// functions
	lua_register(L, "wait", lua_wait);
	// LocalPlayer functions
	lua_register(L, "getPlayer", lua_getPlayer);
	lua_register(L, "setSprinting", lua_setSprinting);
	lua_register(L, "isSprinting", lua_isSprinting);
	// Minecraft
	lua_register(L, "getMinecraft", lua_getMinecraft);
	lua_register(L, "getVersion", lua_getVersion);
}