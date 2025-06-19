#pragma once
#include "../../sdk/AbstractClass.h"
#include "../../Minecraft.h"

class EntityPlayerSP : public AbstractClass {
public:
    explicit EntityPlayerSP();
    void setSprinting(jboolean sprinting);

    bool isSprinting();
    bool isCrouching();

    double x();
    double y();
    double z();
private:
    Minecraft* mc;
    jmethodID mdSetSprinting;
    jmethodID mdisSprinting;
    jmethodID mdisCrouching;
    jmethodID mdx;
    jmethodID mdy;
    jmethodID mdz;
};
