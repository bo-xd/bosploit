#include "Minecraft.h"
#include "../Mappings/Mapping.h"
#include <iostream>

#include "../src/Java.h"

Minecraft::Minecraft() {
    getMinecraftMethod = Mapping::GetMethod("Minecraft", "getMinecraft");
    getConnectionMethod = Mapping::GetMethod("Minecraft", "getConnection");
    getPlayerField = Mapping::GetField("Minecraft", "player");

    minecraftClass = Mapping::GetClass("Minecraft");

    if (!minecraftClass || !getMinecraftMethod || !getConnectionMethod || !getPlayerField) {
        std::cerr << "[!] Failed to initialize Minecraft mappings" << std::endl;
    }
}

jobject Minecraft::getMinecraft() {
    if (!minecraftClass || !getMinecraftMethod) return nullptr;

    return g_classLoader->env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
}

jobject Minecraft::getPlayer() {
    if (!getPlayerField) return nullptr;

    jobject mcInstance = getMinecraft();
    if (!mcInstance) return nullptr;

    return g_classLoader->env->GetObjectField(mcInstance, getPlayerField);
}

jobject Minecraft::getConnection() {
    if (!getConnectionMethod) return nullptr;

    jobject mcInstance = getMinecraft();
    if (!mcInstance) return nullptr;

    return g_classLoader->env->CallObjectMethod(mcInstance, getConnectionMethod);
}

void Minecraft::sendChat(const std::string& message) {
    jobject connection = getConnection();
    if (!connection) return;

    jclass connectionClass = g_classLoader->env->GetObjectClass(connection);
    if (!connectionClass) return;

    jmethodID sendChatMethod = g_classLoader->env->GetMethodID(connectionClass, "b", "(Ljava/lang/String;)V");
    if (!sendChatMethod) return;

    jstring jMessage = g_classLoader->env->NewStringUTF(message.c_str());
    g_classLoader->env->CallVoidMethod(connection, sendChatMethod, jMessage);
    g_classLoader->env->DeleteLocalRef(jMessage);
}
