#include "Java.h"

std::unique_ptr<JavaVmManager> javaVmManager = std::make_unique<JavaVmManager>();

bool JavaVmManager::Init() {
    jsize vmCount;
    if (JNI_GetCreatedJavaVMs(&jvm, 1, &vmCount) != JNI_OK || vmCount == 0) {
        std::cerr << "[-] JNI_GetCreatedJavaVMs failed or no JVMs found\n";
        return false;
    }

    jint result = jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
    if (result == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr) != JNI_OK) {
            std::cerr << "[-] Failed to attach current thread to JVM\n";
            return false;
        }
    }
    else if (result != JNI_OK) {
        std::cerr << "[-] Failed to get JNI env with error code: " << result << "\n";
        return false;
    }

    return true;
}

JNIEnv* JavaVmManager::GetJNIEnv() {
    JNIEnv* currentEnv = nullptr;
    jint ret = jvm->GetEnv(reinterpret_cast<void**>(&currentEnv), JNI_VERSION_1_6);
    if (ret == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread(reinterpret_cast<void**>(&currentEnv), nullptr) != JNI_OK) {
            std::cerr << "[-] Failed to attach current thread to JVM\n";
            return nullptr;
        }
    }
    else if (ret != JNI_OK) {
        std::cerr << "[-] GetEnv failed with code " << ret << std::endl;
        return nullptr;
    }
    return currentEnv;
}

jvmtiEnv* JavaVmManager::GetjvmtiEnv() {
    jvmtiEnv* currentEnv = nullptr;
    jint ret = jvm->GetEnv(reinterpret_cast<void**>(&currentEnv), JNI_VERSION_1_6);
    if (ret == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread(reinterpret_cast<void**>(&currentEnv), nullptr) != JNI_OK) {
            std::cerr << "[-] Failed to attach current thread to JVM (jvmti)\n";
            return nullptr;
        }
    }
    else if (ret != JNI_OK) {
        std::cerr << "[-] GetEnv for JVMTI failed with code " << ret << std::endl;
        return nullptr;
    }
    return currentEnv;
}
