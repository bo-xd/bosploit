#include "Java.h"

std::unique_ptr<JavaVmManager> javaVmManager = std::make_unique<JavaVmManager>();

bool JavaVmManager::Init() {
    jsize vmCount;
    if (JNI_GetCreatedJavaVMs(&jvm, 1, &vmCount) != JNI_OK || vmCount == 0)
        return false;

    jint result = jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
    if (result == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr) != JNI_OK)
            return false;
    }
    else if (result != JNI_OK) {
        return false;
    }

    return true;
}

JNIEnv* JavaVmManager::GetJNIEnv() {
    JNIEnv* currentEnv = nullptr;
    if (jvm->GetEnv(reinterpret_cast<void**>(&currentEnv), JNI_VERSION_21) != JNI_OK) {
        if (jvm->AttachCurrentThread(reinterpret_cast<void**>(&currentEnv), nullptr) != JNI_OK)
            return nullptr;
    }
    return currentEnv;
}

void JavaVmManager::GetLoadedClasses() {
    jvmtiEnv* jvmti;
    if (jvm->GetEnv(reinterpret_cast<void**>(&jvmti), JVMTI_VERSION_21) != JNI_OK) return;

    jclass clazz = env->FindClass("java/lang/Class");
    jmethodID getName = env->GetMethodID(clazz, "getName", "()Ljava/lang/String;");

    jclass* classesPtr = nullptr;
    jint count = 0;
    jvmti->GetLoadedClasses(&count, &classesPtr);

    for (int i = 0; i < count; ++i) {
        jstring name = (jstring)env->CallObjectMethod(classesPtr[i], getName);
        const char* className = env->GetStringUTFChars(name, nullptr);
        env->ReleaseStringUTFChars(name, className);
    }
}

jclass JavaVmManager::GetClass(const std::string& className) {
    auto it = classes.find(className);
    if (it != classes.end()) return it->second;

    jclass clazz = env->FindClass(className.c_str());
    if (clazz) {
        classes[className] = clazz;
        return clazz;
    }

    return nullptr;
}
