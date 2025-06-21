#pragma once
#include <jni.h>
#include <string>

class Minecraft {
public:
    Minecraft();

    jobject getMinecraft();
    jobject getPlayer();
    jobject getConnection();

    void sendChat(const std::string& message);

private:
    jclass minecraftClass = nullptr;

    jmethodID getMinecraftMethod = nullptr;
    jmethodID getConnectionMethod = nullptr;
    jfieldID getPlayerField = nullptr;
};
