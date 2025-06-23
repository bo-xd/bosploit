#include "LocalPlayer.h"
#include "../../Minecraft.h"
#include "../../../Mappings/Mapping.h"

LocalPlayer::LocalPlayer() {
	mc = new Minecraft();

    methodSetSprinting = Mapping::GetMethod("EntityPlayerSP", "setSprint");
    dropMethod = Mapping::GetMethod("EntityPlayer", "drop");

    methodIsSprinting = Mapping::GetMethod("EntityPlayerSP", "isSprinting");
    methodIsCrouching = Mapping::GetMethod("EntityPlayerSP", "isCrouching");

    methodX = Mapping::GetMethod("EntityPlayerSP", "x");
    methodY = Mapping::GetMethod("EntityPlayerSP", "y");
    methodZ = Mapping::GetMethod("EntityPlayerSP", "z");
}

void LocalPlayer::setSprinting(jboolean sprinting) {
	g_classLoader->env->CallVoidMethod(mc->getPlayer(), methodSetSprinting, sprinting);
}

void LocalPlayer::drop(jboolean fullstack) {
	g_classLoader->env->CallBooleanMethod(mc->getPlayer(), dropMethod, fullstack);
}

bool LocalPlayer::isSprinting() {
	jboolean result = g_classLoader->env->CallBooleanMethod(mc->getPlayer(), methodIsSprinting);
    return result == JNI_TRUE;
}

bool LocalPlayer::isCrouching() {
    jboolean result = g_classLoader->env->CallBooleanMethod(mc->getPlayer(), methodIsCrouching);
	return result == JNI_TRUE;
}

double LocalPlayer::x() {
    jdouble result = g_classLoader->env->CallDoubleMethod(mc->getPlayer(), methodX);
	return result;
}

double LocalPlayer::y() {
    jdouble result = g_classLoader->env->CallDoubleMethod(mc->getPlayer(), methodY);
    return result;
}

double LocalPlayer::z() {
    jdouble result = g_classLoader->env->CallDoubleMethod(mc->getPlayer(), methodZ);
    return result;
}

