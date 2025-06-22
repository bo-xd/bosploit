#include "Java.h"

std::unique_ptr<JavaVmManager> javaVmManager = std::make_unique<JavaVmManager>();

bool JavaVmManager::Init() {
    std::lock_guard<std::mutex> guard(lock);

    if (initialized) return true;

    jsize vmCount = 0;
    if (JNI_GetCreatedJavaVMs(&jvm, 1, &vmCount) != JNI_OK || vmCount == 0 || !jvm) {
        std::cerr << "[-] JNI_GetCreatedJavaVMs failed or returned no VMs\n";
        return false;
    }

    JNIEnv* env = nullptr;
    if (!AttachIfNeeded(&env)) {
        return false;
    }

    if (jvm->GetEnv(reinterpret_cast<void**>(&jvmti), JVMTI_VERSION_1_2) != JNI_OK || !jvmti) {
        std::cerr << "[-] Failed to get JVMTI environment\n";
        return false;
    }

    initialized = true;
    return true;
}

bool JavaVmManager::AttachIfNeeded(JNIEnv** outEnv) {
    if (!jvm || !outEnv) return false;

    jint result = jvm->GetEnv(reinterpret_cast<void**>(outEnv), JNI_VERSION_1_6);
    if (result == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread(reinterpret_cast<void**>(outEnv), nullptr) != JNI_OK) {
            std::cerr << "[-] AttachCurrentThread failed\n";
            return false;
        }
    }
    else if (result != JNI_OK) {
        std::cerr << "[-] GetEnv failed with code: " << result << "\n";
        return false;
    }

    return true;
}

JNIEnv* JavaVmManager::GetJNIEnv() {
    JNIEnv* env = nullptr;
    if (!AttachIfNeeded(&env)) {
        std::cerr << "[-] GetJNIEnv: Failed to attach or get environment\n";
        return nullptr;
    }
    return env;
}

jvmtiEnv* JavaVmManager::GetjvmtiEnv() {
    return jvmti;
}

JavaVM* JavaVmManager::GetJavaVM() {
    return jvm;
}
