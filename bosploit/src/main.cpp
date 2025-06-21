#include <Windows.h>
#include <iostream>

#include "java.h"
#include "lua.hpp"

#include "../LuaEnv/Init.h"

#include "../ClassLoader/ClassLoader.h"
#include "../Mappings/Mapping.h"

#include "../Mappings/Fabric/Fabric1215.h"
#include "../Mappings/Vanilla/Vanilla1215.h"

#include "../net/minecraft/Players/EntityPlayerSP.h"

FILE* file{ nullptr };
std::unique_ptr<ClassLoader> g_classLoader;
std::unique_ptr<Mapping> g_mapping;

void MainThread(HMODULE module) {
    AllocConsole();
    freopen_s(&file, "CONOUT$", "w", stdout);
    freopen_s(&file, "CONOUT$", "w", stderr);
    std::cout << "[*] Bosploit Injected" << std::endl;
    g_classLoader = std::make_unique<ClassLoader>();

    if (!g_classLoader->Initialize()) {
        std::cerr << "[!] Failed to initialize ClassLoader" << std::endl;
        FreeLibraryAndExitThread(module, 0);
        return;
    }
    
    std::cout << "[*] JVM, JNI, and JVMTI environments acquired!" << std::endl;
    g_classLoader->GetLoadedClasses();
    std::cout << "[*] Loaded classes cached" << std::endl;

    g_mapping = std::make_unique<Mapping>();

    Vanilla1215Mappings::setup();

    g_mapping->Initialize(g_classLoader->env, g_classLoader.get());

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    registerLuaEnv(L);

    if (luaL_dofile(L, "C:/Users/bovan/OneDrive/Bureaublad/minecraft.lua") != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        std::cerr << "Lua error: " << err << std::endl;
        lua_pop(L, 1);
    }

    while (!(GetAsyncKeyState(VK_DELETE) & 1)) {
        Sleep(100);
    }

    lua_close(L);

    std::cout << "[*] Uninjecting\n";
    FreeConsole();
    FreeLibraryAndExitThread(module, 0);
}


BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(module);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, module, 0, nullptr);
    }
    else if (reason == DLL_PROCESS_DETACH) {
        g_mapping.reset();
        g_classLoader.reset();
    }
    return TRUE;
}
