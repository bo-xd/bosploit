#include "LocalPlayer.h"
#include "../JNIContext.h"

#include "../../Minecraft.h"
#include "EntityPlayerSP.h"

bool LocalPlayer::setSprinting(bool sprinting) {
    JNIContext ctx;
    if (!ctx.isValid()) return false;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "h", "(Z)V");
    if (!method) return false; 

    ctx.env->CallVoidMethod(ctx.player, method, sprinting);
    return true;
}

bool LocalPlayer::isSprinting(bool* sprinting) {
    JNIContext ctx;
    if (!ctx.isValid()) return false;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "ci", "()Z");
    if (!method) return false;

    *sprinting = ctx.env->CallBooleanMethod(ctx.player, method) == JNI_TRUE;
    return true;
}

bool LocalPlayer::isCrouching(bool* crouching) {
    JNIContext ctx;
    if (!ctx.isValid()) return false;

    jmethodID method = ctx.env->GetMethodID(ctx.entityClass, "ch", "()Z");
    if (!method) return false;

    *crouching = ctx.env->CallBooleanMethod(ctx.player, method) == JNI_TRUE;
    return true;
}
