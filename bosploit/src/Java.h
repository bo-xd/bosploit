#pragma once
#include <jni.h>
#include <jvmti.h>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>

class JavaVmManager {
public:
    bool Init();
    JNIEnv* GetJNIEnv();
    jvmtiEnv* GetjvmtiEnv();
private:
    JNIEnv* env{ nullptr };
    jvmtiEnv* jvmti{ nullptr };
    JavaVM* jvm{ nullptr };
    std::unordered_map<std::string, jclass> classes;

    friend class JavaInitializer;
};

extern std::unique_ptr<JavaVmManager> javaVmManager;
