#pragma once
#include <jni.h>
#include <string>

class Minecraft;

class EntityPlayer {
public:
    EntityPlayer();

    void drop(jboolean fullstack);

private:
    Minecraft* mc;
    jmethodID dropMethod = nullptr;
};
