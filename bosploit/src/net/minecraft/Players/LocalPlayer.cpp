#include "LocalPlayer.h"
#include "../../Minecraft.h"
#include "../../../Mappings/Mapping.h"

#include <iostream>

LocalPlayer::LocalPlayer() {
	mc = new Minecraft();

    methodSetSprinting = Mapping::GetMethod("Entity", "setSprint");
    dropMethod = Mapping::GetMethod("LocalPlayer", "drop");

    methodIsSprinting = Mapping::GetMethod("Entity", "isSprinting");
    methodIsCrouching = Mapping::GetMethod("Entity", "isCrouching");

	swingmethod = Mapping::GetMethod("LocalPlayer", "swing");
	attackmethod = Mapping::GetMethod("LocalPlayer", "attack");

    methodX = Mapping::GetMethod("Entity", "x");
    methodY = Mapping::GetMethod("Entity", "y");
    methodZ = Mapping::GetMethod("Entity", "z");
}

// Actions
void LocalPlayer::setSprinting(jboolean sprinting) {
	g_classLoader->env->CallVoidMethod(mc->getPlayer(), methodSetSprinting, sprinting);
}

void LocalPlayer::drop(jboolean fullstack) {
	g_classLoader->env->CallBooleanMethod(mc->getPlayer(), dropMethod, fullstack);
}

void LocalPlayer::swing() {
}

// state
bool LocalPlayer::isSprinting() {
	jboolean result = g_classLoader->env->CallBooleanMethod(mc->getPlayer(), methodIsSprinting);
    return result == JNI_TRUE;
}

bool LocalPlayer::isCrouching() {
    jboolean result = g_classLoader->env->CallBooleanMethod(mc->getPlayer(), methodIsCrouching);
	return result == JNI_TRUE;
}

//Positions
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

