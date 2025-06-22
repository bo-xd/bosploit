#include "EntityPlayerSP.h"
#include "../../Minecraft.h"
#include "../../../Mappings/Mapping.h"
#include "../../../src/Java.h"
#include <iostream>

EntityPlayerSP::EntityPlayerSP() {
    mc = new Minecraft();
    methodSetSprinting = Mapping::GetMethod("EntityPlayerSP", "setSprint");
    methodIsSprinting = Mapping::GetMethod("EntityPlayerSP", "isSprinting");
    methodIsCrouching = Mapping::GetMethod("EntityPlayerSP", "isCrouching");
    methodX = Mapping::GetMethod("EntityPlayerSP", "x");
    methodY = Mapping::GetMethod("EntityPlayerSP", "y");
    methodZ = Mapping::GetMethod("EntityPlayerSP", "z");

    if (!methodSetSprinting) std::cerr << "[!] Failed to find setSprint method" << std::endl;
    if (!methodIsSprinting) std::cerr << "[!] Failed to find isSprinting method" << std::endl;
    if (!methodIsCrouching) std::cerr << "[!] Failed to find isCrouching method" << std::endl;
    if (!methodX) std::cerr << "[!] Failed to find x method" << std::endl;
    if (!methodY) std::cerr << "[!] Failed to find y method" << std::endl;
    if (!methodZ) std::cerr << "[!] Failed to find z method" << std::endl;
}

void EntityPlayerSP::setSprinting(jboolean sprinting) {
    if (!g_classLoader || !g_classLoader->env) {
        std::cerr << "[!] JNI environment not available" << std::endl;
        return;
    }

    jobject player = mc->getPlayer();
    if (!player) {
        std::cerr << "[!] Player object is null" << std::endl;
        return;
    }

    if (!methodSetSprinting) {
        std::cerr << "[!] setSprinting method not found" << std::endl;
        return;
    }

    g_classLoader->env->CallVoidMethod(player, methodSetSprinting, sprinting);

    // Check for JNI exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception in setSprinting" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
    }
}

bool EntityPlayerSP::isSprinting() {
    if (!g_classLoader || !g_classLoader->env) {
        std::cerr << "[!] JNI environment not available" << std::endl;
        return false;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodIsSprinting) return false;

    jboolean result = g_classLoader->env->CallBooleanMethod(player, methodIsSprinting);

    // Check for JNI exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception in isSprinting" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        return false;
    }

    return result;
}

bool EntityPlayerSP::isCrouching() {
    if (!g_classLoader || !g_classLoader->env) {
        std::cerr << "[!] JNI environment not available" << std::endl;
        return false;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodIsCrouching) return false;

    jboolean result = g_classLoader->env->CallBooleanMethod(player, methodIsCrouching);

    // Check for JNI exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception in isCrouching" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        return false;
    }

    return result;
}

double EntityPlayerSP::x() {
    if (!g_classLoader || !g_classLoader->env) {
        std::cerr << "[!] JNI environment not available" << std::endl;
        return 0.0;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodX) return 0.0;

    jdouble result = g_classLoader->env->CallDoubleMethod(player, methodX);

    // Check for JNI exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception in x()" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        return 0.0;
    }

    return result;
}

double EntityPlayerSP::y() {
    if (!g_classLoader || !g_classLoader->env) {
        std::cerr << "[!] JNI environment not available" << std::endl;
        return 0.0;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodY) return 0.0;

    jdouble result = g_classLoader->env->CallDoubleMethod(player, methodY);

    // Check for JNI exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception in y()" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        return 0.0;
    }

    return result;
}

double EntityPlayerSP::z() {
    if (!g_classLoader || !g_classLoader->env) {
        std::cerr << "[!] JNI environment not available" << std::endl;
        return 0.0;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodZ) return 0.0;

    jdouble result = g_classLoader->env->CallDoubleMethod(player, methodZ);

    // Check for JNI exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception in z()" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        return 0.0;
    }

    return result;
}