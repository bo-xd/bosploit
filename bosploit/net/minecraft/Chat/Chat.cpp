#include "Chat.h"
#include "../JNIContext.h"
#include <iostream>

void Chat::sendMessage(const std::string& message) {
    JNIContext ctx;
    JNIEnv* env = ctx.env;
    jobject mcInstance = ctx.MinecraftInstance;
    jclass mcClass = ctx.MinecraftClass;

    jstring jMessage = env->NewStringUTF(message.c_str());
    jmethodID getConnectionMethod = env->GetMethodID(mcClass, "L", "()Lglp;");
    jobject clientPacketListener = env->CallObjectMethod(mcInstance, getConnectionMethod);
    jclass listenerClass = env->GetObjectClass(clientPacketListener);
    jmethodID sendChatMethod = env->GetMethodID(listenerClass, "b", "(Ljava/lang/String;)V");

    env->CallVoidMethod(clientPacketListener, sendChatMethod, jMessage);
    if (env->ExceptionCheck()) {
        std::cerr << "Error: Exception occurred during sendChat" << std::endl;
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    else {
        std::cout << "sendChat called successfully with message: " << message << std::endl;
    }

    env->DeleteLocalRef(jMessage);
    env->DeleteLocalRef(clientPacketListener);
    env->DeleteLocalRef(listenerClass);
}