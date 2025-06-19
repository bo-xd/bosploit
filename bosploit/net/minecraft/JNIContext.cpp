#include "JNIContext.h"
#include "../minecraft/Players/LocalPlayer.h"
#include "../Minecraft.h"
#include "../../src/Java.h"

JNIContext::JNIContext() {
    env = javaVmManager->GetJNIEnv();

    // Use the LocalPlayer instance properly
    jobject localPlayerRef = nullptr;
    {
        LocalPlayer lp;
        localPlayerRef = lp.getPlayer();
    }

    if (localPlayerRef) {
        player = env->NewGlobalRef(localPlayerRef);
        env->DeleteLocalRef(localPlayerRef);
    }
    else {
        player = nullptr;
    }

    Minecraft mc;
    jobject mcInstance = mc.getMinecraft();
    jclass mcClass = mc.getClass();

    MinecraftInstance = (mcInstance) ? env->NewGlobalRef(mcInstance) : nullptr;
    MinecraftClass = (mcClass) ? (jclass)env->NewGlobalRef(mcClass) : nullptr;

    entityClass = (env) ? (jclass)env->NewGlobalRef(env->FindClass("bxe")) : nullptr;
    LivingEntityClass = (env) ? (jclass)env->NewGlobalRef(env->FindClass("byf")) : nullptr;
    playerClass = (env) ? (jclass)env->NewGlobalRef(env->FindClass("gqm")) : nullptr;
}

JNIContext::~JNIContext() {
    if (env) {
        if (entityClass) {
            env->DeleteGlobalRef(entityClass);
        }
        if (MinecraftClass) {
            env->DeleteGlobalRef(MinecraftClass);
        }
        if (MinecraftInstance) {
            env->DeleteGlobalRef(MinecraftInstance);
        }
        if (player) {
            env->DeleteGlobalRef(player);
        }
        if (LivingEntityClass) {
            env->DeleteGlobalRef(LivingEntityClass);
        }
        if (playerClass) {
            env->DeleteGlobalRef(playerClass);
        }
    }
}

bool JNIContext::isValid() const {
    return env && player && entityClass && MinecraftClass && MinecraftInstance && LivingEntityClass && playerClass;
}
