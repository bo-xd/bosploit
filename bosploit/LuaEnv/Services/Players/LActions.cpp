#include "Players.h"
#include "../../src/Java.h"
#include "../../net/Minecraft.h"
#include "../../net/minecraft/Players/LocalPlayer.h"

int lua_dropItem(lua_State* L) {
    if (!lua_isboolean(L, 2)) {
        return luaL_error(L, "Expected boolean argument for drop");
    }

    bool drop = lua_toboolean(L, 2);

    lua_getfield(L, 1, "__userdata");
    jobject player = static_cast<jobject>(lua_touserdata(L, -1));
    lua_pop(L, 1);

    if (!player) {
        return luaL_error(L, "Invalid player userdata");
    }

    LocalPlayer::drop(drop);

    lua_pushboolean(L, drop);  // push the bool to Lua stack
    return 1;                  // returning 1 value
}
