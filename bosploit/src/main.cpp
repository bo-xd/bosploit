#include <Windows.h>
#include <iostream>

#include "java.h"
#include "lua.hpp"

#include "../sdk/Mapping.h"
#include "../LuaEnv/Init.h"

#include "../sdk/AbstractClass.h"

FILE* file{ nullptr };

DWORD WINAPI Init(LPVOID instance) {
    AllocConsole();
    freopen_s(&file, "CONOUT$", "w", stdout);
    freopen_s(&file, "CONOUT$", "w", stderr);

    if (!javaVmManager->Init()) {
        std::cerr << "[-] Failed to initialize Java VM Manager." << std::endl;
        return 1;
    }

    Mapping::setup();
    AbstractClass myClass;
    myClass.GetLoadedClasses();
    std::cout << "[+] cached all classes" << std::endl;


    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    registerLuaEnv(L);

    if (luaL_dofile(L, "C:/Users/bovan/OneDrive/Bureaublad/minecraft.lua") != LUA_OK) {
        const char* err = lua_tostring(L, -1);
        printf("Lua error: %s\n", err);
        lua_pop(L, 1);
    }
    
    while (!(GetAsyncKeyState(VK_DELETE))) {
        Sleep(100);
    }

    lua_close(L);

    std::cout << "[*] Uninjecting\n";
    FreeConsole();
    FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
    return false;
}

BOOL APIENTRY DllMain(HMODULE instance, DWORD reason, LPVOID reserved) {
    DisableThreadLibraryCalls(instance);

    if (reason == DLL_PROCESS_ATTACH) {
        HANDLE hThread = CreateThread(nullptr, 0, Init, instance, 0, nullptr);
        if (hThread) CloseHandle(hThread);
    }

    return TRUE;
}

