#pragma once
#include <jni.h>

class Minecraft;

class EntityPlayerSP {
public:
    EntityPlayerSP();

    void setSprinting(jboolean sprinting);
    bool isSprinting();
    bool isCrouching();

    double x();
    double y();
    double z();

private:
    Minecraft* mc;

    jmethodID methodSetSprinting = nullptr;
    jmethodID methodIsSprinting = nullptr;
    jmethodID methodIsCrouching = nullptr;
    jmethodID methodX = nullptr;
    jmethodID methodY = nullptr;
    jmethodID methodZ = nullptr;
};
