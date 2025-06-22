#pragma once

#include <jni.h>
#include <jvmti.h>
#include <iostream>
#include <memory>
#include <mutex>

class JavaVmManager {
public:
    bool Init();
    JNIEnv* GetJNIEnv();
    jvmtiEnv* GetjvmtiEnv();
    JavaVM* GetJavaVM();

private:
    JavaVM* jvm = nullptr;
    jvmtiEnv* jvmti = nullptr;
    std::mutex lock;
    bool initialized = false;

    bool AttachIfNeeded(JNIEnv** outEnv);

    friend class JavaInitializer;
};

extern std::unique_ptr<JavaVmManager> javaVmManager;
