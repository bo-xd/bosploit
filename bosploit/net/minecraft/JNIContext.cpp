#include "JNIContext.h"
#include "../minecraft/Players/LocalPlayer.h"
#include "../Minecraft.h"
#include "../../src/Java.h"

JNIContext::JNIContext() {
    env = javaVmManager->GetJNIEnv();

    jobject localPlayerRef = LocalPlayer::getPlayer();
    if (localPlayerRef) {
        player = env->NewGlobalRef(localPlayerRef);
        env->DeleteLocalRef(localPlayerRef);
    }
    else {
        player = nullptr;
    }

    MinecraftClass = (env) ? (jclass)env->NewGlobalRef(Minecraft::getMinecraftClass(env)) : nullptr;
    MinecraftInstance = (env) ? env->NewGlobalRef(Minecraft::getInstance(env)) : nullptr;
    entityClass = (env) ? (jclass)env->NewGlobalRef(env->FindClass("bxe")) : nullptr;
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
    }
}


bool JNIContext::isValid() const {
    return env && player && entityClass && MinecraftClass && MinecraftInstance;
}
