#include "LocalPlayer.h"
#include "../JNIContext.h"
#include "../../Minecraft.h"
#include "../../../src/Java.h"

jobject LocalPlayer::getPlayer() {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject mcInstance = Minecraft::getInstance(env);
    jclass mcClass = Minecraft::getMinecraftClass(env);

    if (!mcInstance || !mcClass) return nullptr;

    jfieldID playerField = env->GetFieldID(mcClass, "t", "Lgqm;");
    if (!playerField) return nullptr;

    return env->GetObjectField(mcInstance, playerField);
};