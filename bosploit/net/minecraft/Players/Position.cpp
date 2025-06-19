#include "LocalPlayer.h"
#include "../JNIContext.h"

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