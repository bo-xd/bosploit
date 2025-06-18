#include "LocalPlayer.h"
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
}

void LocalPlayer::setSprinting(bool sprinting) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = getPlayer();
    jclass entityClass = env->FindClass("bxe");

	if (!player || !entityClass) return;

    jmethodID setSprintingMethod = env->GetMethodID(entityClass, "h", "(Z)V");
    if (!setSprintingMethod) return;

    env->CallVoidMethod(player, setSprintingMethod, sprinting);
}

void LocalPlayer::isSprinting(bool* sprinting) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = getPlayer();
	jclass entityClass = env->FindClass("bxe");

    if (!player || !entityClass) return;

	jmethodID isSprintingMethod = env->GetMethodID(entityClass, "ci", "()Z");

	env->CallBooleanMethod(player, isSprintingMethod);
};

void LocalPlayer::isCrouching(bool* crouching) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = getPlayer();
    jclass entityClass = env->FindClass("bxe");

    if (!player || !entityClass) return;

    jmethodID isCrouchingMethod = env->GetMethodID(entityClass, "ch", "()Z");

    env->CallBooleanMethod(player, isCrouchingMethod);
}

void LocalPlayer::getY(double* y) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = getPlayer();
    jclass entityClass = env->FindClass("bxe");
    if (!player || !entityClass) return;
    jmethodID getYMethod = env->GetMethodID(entityClass, "dC", "()D");
    *y = env->CallDoubleMethod(player, getYMethod);
}

void LocalPlayer::getX(double* x) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = getPlayer();
    jclass entityClass = env->FindClass("bxe");
    if (!player || !entityClass) return;
    jmethodID getXMethod = env->GetMethodID(entityClass, "dA", "()D");
    *x = env->CallDoubleMethod(player, getXMethod);
}

void LocalPlayer::getZ(double* z) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jobject player = getPlayer();
    jclass entityClass = env->FindClass("bxe");
    if (!player || !entityClass) return;
    jmethodID getZMethod = env->GetMethodID(entityClass, "dG", "()D");
    *z = env->CallDoubleMethod(player, getZMethod);
}

