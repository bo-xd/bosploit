#pragma once
#include "../../sdk/AbstractClass.h"
#include "../../Minecraft.h"

class EntityPlayerSP : public AbstractClass {
public:
    explicit EntityPlayerSP();
    void setSprinting(jboolean sprinting);

private:
    Minecraft* mc;
    jmethodID mdSetSprinting;
};
