#include "LocalPlayer.h"
#include "../JNIContext.h"

bool LocalPlayer::drop(bool fullstack) {
    JNIContext ctx;
    if (!ctx.isValid()) return false;

    jmethodID method = ctx.env->GetMethodID(ctx.playerClass, "a", "(Z)Z");
    if (!method) {
        ctx.env->DeleteLocalRef(ctx.playerClass);
        return false;
    }

    jboolean result = ctx.env->CallBooleanMethod(ctx.player, method, fullstack);
    return result == JNI_TRUE;
}


