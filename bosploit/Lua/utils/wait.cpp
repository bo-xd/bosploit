#include <chrono>
#include <thread>
#include "lua.hpp"

// HOLY SHIT THIS CODE SUCKS, i hope no one sees this garbage!!
int lua_wait(lua_State* L) {
    if (!lua_isnumber(L, 1)) {
        return luaL_error(L, "Expected number of milliseconds");
    }
    int ms = (int)lua_tointeger(L, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    return 0;
}
