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
}

void LocalPlayer::setSprinting(bool sprinting) {
    JNIContext ctx;
    if (!ctx.isValid()) return;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "h", "(Z)V");
    if (!method) return;

    ctx.env->CallVoidMethod(ctx.player, method, sprinting);
}

void LocalPlayer::isSprinting(bool* sprinting) {
    JNIContext ctx;
    if (!ctx.isValid()) return;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "ci", "()Z");
    if (!method) return;

    *sprinting = ctx.env->CallBooleanMethod(ctx.player, method);
}

void LocalPlayer::isCrouching(bool* crouching) {
    JNIContext ctx;
    if (!ctx.isValid()) return;
    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "ch", "()Z");
    if (!method) return;
	*crouching = ctx.env->CallBooleanMethod(ctx.player, method);
}

void LocalPlayer::getY(double* y) {
    JNIContext ctx;
    if (!ctx.isValid()) return;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "dC", "()D");
    if (!method) return;

    *y = ctx.env->CallDoubleMethod(ctx.player, method);
}

void LocalPlayer::getX(double* x) {
    JNIContext ctx;
    if (!ctx.isValid()) return;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "dA", "()D");
    if (!method) return;

    *x = ctx.env->CallDoubleMethod(ctx.player, method);
}

void LocalPlayer::getZ(double* z) {
    JNIContext ctx;
    if (!ctx.isValid()) return;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "dG", "()D");
    if (!method) return;

    *z = ctx.env->CallDoubleMethod(ctx.player, method);
}
