#include "Minecraft.h"
#include <iostream>

Minecraft::Minecraft() : AbstractClass("Minecraft") {
    getMinecraftMethod = getMethodID("getMinecraft");
    getPlayerMethod = getFieldID("player");
}

jobject Minecraft::getMinecraft() {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env || !getMinecraftMethod) return nullptr;

    jobject mc = env->CallStaticObjectMethod(cls, getMinecraftMethod);
    return mc;
}

jobject Minecraft::getPlayer() {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env || !getPlayerMethod) return nullptr;

    jobject mcInstance = getMinecraft();
    if (!mcInstance) return nullptr;

    jobject player = env->GetObjectField(mcInstance, getPlayerMethod);
    return player;
}

