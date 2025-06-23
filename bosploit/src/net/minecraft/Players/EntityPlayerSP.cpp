#include "EntityPlayerSP.h"
#include "../../Minecraft.h"
#include "../../../Mappings/Mapping.h"

EntityPlayerSP::EntityPlayerSP() {
    mc = new Minecraft();
    methodSetSprinting = Mapping::GetMethod("EntityPlayerSP", "setSprint");
    methodIsSprinting = Mapping::GetMethod("EntityPlayerSP", "isSprinting");
    methodIsCrouching = Mapping::GetMethod("EntityPlayerSP", "isCrouching");
    methodX = Mapping::GetMethod("EntityPlayerSP", "x");
    methodY = Mapping::GetMethod("EntityPlayerSP", "y");
    methodZ = Mapping::GetMethod("EntityPlayerSP", "z");
}

void EntityPlayerSP::setSprinting(jboolean sprinting) {
    if (!g_classLoader || !g_classLoader->env) {
        return;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodSetSprinting) {
        return;
    }

    g_classLoader->env->CallVoidMethod(player, methodSetSprinting, sprinting);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
    }
}

bool EntityPlayerSP::isSprinting() {
    if (!g_classLoader || !g_classLoader->env) {
        return false;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodIsSprinting) return false;

    jboolean result = g_classLoader->env->CallBooleanMethod(player, methodIsSprinting);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        return false;
    }

    return result;
}

bool EntityPlayerSP::isCrouching() {
    if (!g_classLoader || !g_classLoader->env) {
        return false;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodIsCrouching) return false;

    jboolean result = g_classLoader->env->CallBooleanMethod(player, methodIsCrouching);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        return false;
    }

    return result;
}

double EntityPlayerSP::x() {
    if (!g_classLoader || !g_classLoader->env) {
        return 0.0;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodX) return 0.0;

    jdouble result = g_classLoader->env->CallDoubleMethod(player, methodX);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        return 0.0;
    }

    return result;
}

double EntityPlayerSP::y() {
    if (!g_classLoader || !g_classLoader->env) {
        return 0.0;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodY) return 0.0;

    jdouble result = g_classLoader->env->CallDoubleMethod(player, methodY);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        return 0.0;
    }

    return result;
}

double EntityPlayerSP::z() {
    if (!g_classLoader || !g_classLoader->env) {
        return 0.0;
    }

    jobject player = mc->getPlayer();
    if (!player || !methodZ) return 0.0;

    jdouble result = g_classLoader->env->CallDoubleMethod(player, methodZ);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        return 0.0;
    }

    return result;
}
