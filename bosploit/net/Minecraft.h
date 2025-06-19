#pragma once
#include "../sdk/AbstractClass.h"

class Minecraft : public AbstractClass {
public:
    explicit Minecraft();
    jobject getMinecraft();

private:
    jmethodID getMinecraftMethod;
};
