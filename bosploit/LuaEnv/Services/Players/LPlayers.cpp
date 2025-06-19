#include "Players.h"
#include "../../src/Java.h"
#include "../../net/Minecraft.h"
#include "../../net/minecraft/Players/LocalPlayer.h"

int lua_getPlayer(lua_State* L) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = LocalPlayer::getPlayer();

    if (!player || !env) {
        lua_pushnil(L);
        return 1;
    }

    jobject globalPlayer = env->NewGlobalRef(player);
    lua_pushlightuserdata(L, globalPlayer);
    return 1;
}
