#include "LMinecraft.h"

int lua_getMinecraft(lua_State* L) {
	JNIEnv* env = javaVmManager->GetJNIEnv();
	jobject minecraft = Minecraft::getInstance(env);

	if (!minecraft) {
		lua_pushnil(L);
		return true;
	}

	lua_pushlightuserdata(L, minecraft);
	return true;
}


int lua_getVersion(lua_State* L) {
	lua_pushstring(L, "1.21.5");
	return true;
}