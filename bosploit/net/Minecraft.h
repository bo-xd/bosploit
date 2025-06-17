#pragma once
#include <jni.h>

class Minecraft {
public:
    static jclass getMinecraftClass(JNIEnv* env);
    static jstring getVersion(JNIEnv* env);
    static jobject getInstance(JNIEnv* env);
private:
    static jclass minecraftClass;
};
