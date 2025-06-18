#pragma once

#include <jni.h>

class JNIContext {
public:
    JNIEnv* env;
	jclass MinecraftClass;
    jobject MinecraftInstance;

    jobject player;
    jclass entityClass;


    JNIContext();
    ~JNIContext();

    bool isValid() const;
};
