#pragma once

#include <jni.h>

class JNIContext {
public:
    JNIEnv* env;
	jclass MinecraftClass;
    jobject MinecraftInstance;

    jobject player;
	jclass playerClass;
    jclass entityClass;
	jclass LivingEntityClass;

    JNIContext();
    ~JNIContext();

    bool isValid() const;
};
