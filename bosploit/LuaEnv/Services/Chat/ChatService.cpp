#include "ChatService.h"

#include "../../src/Java.h"
#include "../../net/minecraft/Chat/Chat.h"

int lua_sendMessage(lua_State* L) {
    if (!lua_isstring(L, 2)) {
        return luaL_error(L, "Expected string as second argument to sendMessage");
    }

    const char* message = lua_tostring(L, 2);
    Chat::sendMessage(message);

    return 0;
}
