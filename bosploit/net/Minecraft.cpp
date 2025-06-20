#include "Minecraft.h"
#include <iostream>

Minecraft::Minecraft() : AbstractClass("Minecraft") {
    getMinecraftMethod = getMethodID("getMinecraft");
    getConnectionMethod = getMethodID("getConnection");
    getPlayerMethod = getFieldID("player");
}

jobject Minecraft::getMinecraft() {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env || !getMinecraftMethod) return nullptr;

    jobject mc = env->CallStaticObjectMethod(cls, getMinecraftMethod);
    return mc;
}

jobject Minecraft::getPlayer() {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env || !getPlayerMethod) return nullptr;

    jobject mcInstance = getMinecraft();
    if (!mcInstance) return nullptr;

    jobject player = env->GetObjectField(mcInstance, getPlayerMethod);
    return player;
}

jobject Minecraft::getConnection() {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env || !getConnectionMethod) return nullptr;

    jobject mcInstance = getMinecraft();
    if (!mcInstance) return nullptr;

    jobject connection = env->CallObjectMethod(mcInstance, getConnectionMethod);
    return connection;
}

void Minecraft::sendChat(const std::string& message) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (!env) return;

    jobject connection = getConnection();
    if (!connection) return;

    jclass connectionClass = env->GetObjectClass(connection);
    if (!connectionClass) return;
    jmethodID sendChatMethod = env->GetMethodID(connectionClass, "b", "(Ljava/lang/String;)V");
    if (!sendChatMethod) return;

    jstring jMessage = env->NewStringUTF(message.c_str());
    env->CallVoidMethod(connection, sendChatMethod, jMessage);
    env->DeleteLocalRef(jMessage);
}