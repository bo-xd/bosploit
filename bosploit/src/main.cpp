#include <Windows.h>
#include <iostream>

#include "java.h"
#include "lua.hpp"

#include "../sdk/Mapping.h"
#include "../LuaEnv/Init.h"

#include "../sdk/AbstractClass.h"
#include "../sdk/ClassLoader.h"

FILE* file{ nullptr };

DWORD WINAPI Init(LPVOID instance) {
    AllocConsole();
    FILE* outFile = nullptr;
    freopen_s(&outFile, "CONOUT$", "w", stdout);
    freopen_s(&outFile, "CONOUT$", "w", stderr);

    if (!javaVmManager->Init()) {
        std::cerr << "[-] Failed to initialize Java VM Manager." << std::endl;
        FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 1);
        return 1;
    }

    Mapping::setup();
    g_classLoader->GetLoadedClasses();
    std::cout << "[*] Loaded classes cached" << std::endl;

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
    FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
    return 0;
}


BOOL APIENTRY DllMain(HMODULE instance, DWORD reason, LPVOID reserved) {
    DisableThreadLibraryCalls(instance);

    if (reason == DLL_PROCESS_ATTACH) {
        HANDLE hThread = CreateThread(nullptr, 0, Init, instance, 0, nullptr);
        if (hThread) CloseHandle(hThread);
    }

    return TRUE;
}

