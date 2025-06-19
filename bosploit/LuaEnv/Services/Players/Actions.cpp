#include "Players.h"
#include "../../../net/minecraft/Players/EntityPlayer.h"

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

    EntityPlayer playerWrapper;
    playerWrapper.drop(drop);

    return 0;
}
