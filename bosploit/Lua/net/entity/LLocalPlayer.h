#pragma once
#include "lua.hpp"
#include "../../src/Java.h"
#include "../../net/Minecraft.h"
#include "../../net/minecraft/client/LocalPlayer.h"

struct lua_State;

int lua_getPlayer(lua_State* L);
int lua_setSprinting(lua_State* L);
int lua_isSprinting(lua_State* L);