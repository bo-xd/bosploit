#pragma once
#include <jni.h>
#include <jvmti.h>
#include <unordered_map>
#include <memory>
#include <string>

class JavaVmManager {
public:
    bool Init();
    JNIEnv* GetJNIEnv();
    void GetLoadedClasses();
    jclass GetClass(const std::string& className);
private:
    JNIEnv* env{ nullptr };
    JavaVM* jvm{ nullptr };
    std::unordered_map<std::string, jclass> classes;

    friend class JavaInitializer;
};

extern std::unique_ptr<JavaVmManager> javaVmManager;
