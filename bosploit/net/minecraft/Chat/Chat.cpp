#include "Chat.h"
#include "../JNIContext.h"
#include <iostream>

void Chat::sendMessage(const std::string& message) {
    JNIContext ctx;
    JNIEnv* env = ctx.env;
    jobject mcInstance = ctx.MinecraftInstance;
    jclass mcClass = ctx.MinecraftClass;

    jstring jMessage = env->NewStringUTF(message.c_str());
    if (jMessage == nullptr) {
        std::cerr << "Error: Failed to create Java string" << std::endl;
        return;
    }

    jmethodID getConnectionMethod = env->GetMethodID(mcClass, "L", "()Lglp;");
    if (getConnectionMethod == nullptr) {
        std::cerr << "Error: Failed to find Minecraft.getConnection method (L, ()Lglp;)" << std::endl;
        env->DeleteLocalRef(jMessage);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return;
    }

    jobject clientPacketListener = env->CallObjectMethod(mcInstance, getConnectionMethod);
    if (clientPacketListener == nullptr) {
        std::cerr << "Error: ClientPacketListener is null" << std::endl;
        env->DeleteLocalRef(jMessage);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return;
    }

    jclass listenerClass = env->GetObjectClass(clientPacketListener);
    if (listenerClass == nullptr) {
        std::cerr << "Error: Failed to get ClientPacketListener class" << std::endl;
        env->DeleteLocalRef(jMessage);
        env->DeleteLocalRef(clientPacketListener);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return;
    }

    jmethodID sendChatMethod = env->GetMethodID(listenerClass, "b", "(Ljava/lang/String;)V");
    if (sendChatMethod == nullptr) {
        std::cerr << "Error: Failed to find ClientPacketListener.sendChat method (b, (Ljava/lang/String;)V)" << std::endl;
        env->DeleteLocalRef(jMessage);
        env->DeleteLocalRef(clientPacketListener);
        env->DeleteLocalRef(listenerClass);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return;
    }

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