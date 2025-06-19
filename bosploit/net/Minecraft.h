#pragma once
#include "../sdk/AbstractClass.h"

class Minecraft : public AbstractClass {
public:
    explicit Minecraft();
    jobject getMinecraft();
    jobject getPlayer();
    jobject getConnection();

    void sendChat(const std::string& message);
private:
    jmethodID getMinecraftMethod;
    jmethodID getConnectionMethod;
    jfieldID getPlayerMethod;
};
