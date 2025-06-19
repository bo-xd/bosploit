#include "ChatService.h"
#include "../../../net/Minecraft.h"

int lua_sendMessage(lua_State* L) {
    if (!lua_isstring(L, 2)) {
        return luaL_error(L, "Expected string as second argument to sendMessage");
    }

    const char* message = lua_tostring(L, 2);
    Minecraft mc;
    mc.sendChat(message);

    return 0;
}
