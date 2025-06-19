#include "LocalPlayer.h"
#include "../JNIContext.h"
#include "../../Minecraft.h"
#include "../../../src/Java.h"

jobject LocalPlayer::getPlayer() {
    JNIEnv* env = javaVmManager->GetJNIEnv();

    Minecraft mc;
    jobject mcInstance = mc.getMinecraft();
    jclass mcClass = mc.getClass();

    if (!mcInstance || !mcClass) {
        std::cerr << "[-] Failed to get Minecraft instance or class.\n";
        return nullptr;
    }

    jfieldID playerField = env->GetFieldID(mcClass, "t", "Lgqm;");
    if (!playerField) {
        std::cerr << "[-] Failed to find 't' field in Minecraft class.\n";
        return nullptr;
    }

    return env->GetObjectField(mcInstance, playerField);
}
