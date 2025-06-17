#pragma once

#include <jni.h>
#include <jvmti.h>
#include <unordered_map>
#include <memory>
#include <string>

class JavaVmManager {
public:
    JNIEnv* env{ nullptr };
    JavaVM* jvm{ nullptr };

    bool Init();
    JNIEnv* GetJNIEnv();

    void GetLoadedClasses();
    jclass GetClass(std::string className);

private:
    std::unordered_map<std::string, jclass> classes;
};

extern std::unique_ptr<JavaVmManager> javaVmManager;
