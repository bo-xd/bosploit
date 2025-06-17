#pragma once
#include "lua.hpp"
#include "../../net/Minecraft.h"
#include "../../src/Java.h"

struct lua_State;

int lua_getMinecraft(lua_State* L);
int lua_getVersion(lua_State* L);