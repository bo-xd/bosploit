#include <Windows.h>
#include <iostream>
#include <memory>

#include "lua.hpp"
#include "LuaEnv/Init.h"
#include "utils/ClassLoader/ClassLoader.h"
#include "Mappings/Mapping.h"
#include "Mappings/Fabric/Fabric1215.h"
#include "Mappings/Vanilla/Vanilla1215.h"
#include "net/Minecraft.h"

#include "utils/LoaderDetection/LoaderDetection.h"

static FILE* consoleOut = nullptr;
static std::unique_ptr<Mapping> g_mapping;

void modloader() {
    if (!g_classLoader) {
        std::cerr << "[!] ClassLoader not initialized, cannot detect mod loader.\n";
        return;
    }

    std::cout << "\n[*] Detecting mod loader..." << std::endl;
    ModLoader modLoader = LoaderDetection::DetectModLoader(g_classLoader.get());

    std::cout << "\n=== MOD LOADER DETECTION RESULT ===" << std::endl;
    std::cout << "Mod Loader: ";

    switch (modLoader) {
    case ModLoader::VANILLA:
        std::cout << "Vanilla";
        break;
    case ModLoader::FABRIC:
        std::cout << "Fabric";
        break;
    case ModLoader::FORGE:
        std::cout << "Forge";
        break;
    case ModLoader::QUILT:
        std::cout << "Quilt";
        break;
    case ModLoader::NEOFORGE:
        std::cout << "NeoForge";
        break;
    default:
        std::cout << "Unknown";
        break;
    }

    std::cout << std::endl << "==================================\n" << std::endl;
}

void InitializeConsole() {
    AllocConsole();
    freopen_s(&consoleOut, "CONOUT$", "w", stdout);
    freopen_s(&consoleOut, "CONOUT$", "w", stderr);
    std::cout << "[*] Bosploit Injected\n";
}

void ExecuteLuaScript() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    registerLuaEnv(L);

    const char* scriptPath = "C:/Users/bovan/OneDrive/Bureaublad/minecraft.lua";
    if (luaL_dofile(L, scriptPath) != LUA_OK) {
        std::cerr << "Lua error: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }

    while (!(GetAsyncKeyState(VK_DELETE) & 1)) {
        Sleep(100);
    }

    lua_close(L);
}

void MainThread(HMODULE hModule) {
    InitializeConsole();

    g_classLoader = std::make_unique<ClassLoader>();
    if (!g_classLoader->Initialize()) {
        std::cerr << "[!] Failed to initialize ClassLoader\n";
        FreeLibraryAndExitThread(hModule, 0);
        return;
    }

    std::cout << "[*] JVM, JNI, and JVMTI environments acquired!\n";
    g_classLoader->GetLoadedClasses();
    std::cout << "[*] Loaded classes cached\n";

    modloader();

    g_mapping = std::make_unique<Mapping>();
    Vanilla1215Mappings::setup();
    g_mapping->Initialize(g_classLoader->env, g_classLoader.get());

    ExecuteLuaScript();

    std::cout << "[*] Uninjecting\n";
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        g_mapping.reset();
        g_classLoader.reset();
        break;
    }
    return TRUE;
}