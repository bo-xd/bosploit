#pragma once
#include <cstring>

#include "lua.hpp"
#include "Players/Players.h"
#include "../../src/Java.h"

struct lua_State;

int lua_GetService(lua_State* L);