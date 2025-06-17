#include "Minecraft.h"
#include "../src/Java.h"

jclass Minecraft::minecraftClass = nullptr;

jclass Minecraft::getMinecraftClass(JNIEnv* env) {
    if (minecraftClass == nullptr) {
        jclass localClass = javaVmManager->GetClass("fqq");

        if (localClass == nullptr) return nullptr;
        minecraftClass = (jclass)env->NewGlobalRef(localClass);
        env->DeleteLocalRef(localClass);
    }
    return minecraftClass;
}

jobject Minecraft::getInstance(JNIEnv* env) {
    jclass mcClass = getMinecraftClass(env);
    if (mcClass == nullptr) return nullptr;

    jmethodID mid = env->GetStaticMethodID(mcClass, "Q", "()Lfqq;");
    if (!mid) return nullptr;

    return env->CallStaticObjectMethod(mcClass, mid);
}
