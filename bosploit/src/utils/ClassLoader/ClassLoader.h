#pragma once
#include <jni.h>
#include <jvmti.h>
#include <mutex>
#include <unordered_map>
#include <string>

class ClassLoader {
public:
    bool Initialize();
    void GetLoadedClasses();
    jclass FindClass(const std::string& className);
    ~ClassLoader();

    JNIEnv* env = nullptr;
    JavaVM* jvm = nullptr;
    jvmtiEnv* jvmti = nullptr;

private:
    std::mutex classesMutex;
    std::unordered_map<std::string, jclass> loadedClasses;
    bool threadAttached = false;
};

extern std::unique_ptr<ClassLoader> g_classLoader;