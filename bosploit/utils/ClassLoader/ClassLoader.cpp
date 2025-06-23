#include "ClassLoader.h"
#include <iostream>

extern std::unique_ptr<ClassLoader> g_classLoader = nullptr;

bool ClassLoader::Initialize() {
    std::cout << "[DEBUG] Starting ClassLoader initialization..." << std::endl;

    JavaVM* vms[1];
    jsize count;
    jint result = JNI_GetCreatedJavaVMs(vms, 1, &count);

    std::cout << "[DEBUG] JNI_GetCreatedJavaVMs result: " << result << ", count: " << count << std::endl;

    if (result != JNI_OK || count == 0) {
        std::cerr << "[!] No JVM found or JNI_GetCreatedJavaVMs failed" << std::endl;
        return false;
    }

    jvm = vms[0];
    std::cout << "[DEBUG] Got JVM pointer: " << jvm << std::endl;

    jint envResult = jvm->GetEnv((void**)&env, JNI_VERSION_1_8);
    std::cout << "[DEBUG] GetEnv result: " << envResult << ", env ptr: " << env << std::endl;

    if (envResult == JNI_EDETACHED) {
        std::cout << "[DEBUG] Thread detached, attempting to attach..." << std::endl;
        JNIEnv* tempEnv = nullptr;
        if (jvm->AttachCurrentThread((void**)&tempEnv, nullptr) != JNI_OK) {
            std::cerr << "[!] Failed to attach thread" << std::endl;
            return false;
        }
        env = tempEnv;
        threadAttached = true;
        std::cout << "[DEBUG] Thread attached successfully, env ptr: " << env << std::endl;
    }
    else if (envResult != JNI_OK) {
        std::cerr << "[!] Failed to get JNI environment: " << envResult << std::endl;
        return false;
    }

    if (env == nullptr) {
        std::cerr << "[!] JNI environment pointer is null after attach" << std::endl;
        return false;
    }

    jint jvmtiResult = jvm->GetEnv((void**)&jvmti, JVMTI_VERSION_1_2);
    std::cout << "[DEBUG] JVMTI GetEnv result: " << jvmtiResult << std::endl;

    if (jvmtiResult != JNI_OK) {
        std::cout << "[WARNING] JVMTI not available, some features will be disabled" << std::endl;
        jvmti = nullptr;
    }

    std::cout << "[DEBUG] ClassLoader initialization complete" << std::endl;
    return true;
}


void ClassLoader::GetLoadedClasses() {
    std::cout << "[DEBUG] GetLoadedClasses called" << std::endl;

    if (!env) {
        std::cerr << "[!] JNI environment is null" << std::endl;
        return;
    }

    if (!jvmti) {
        std::cout << "[WARNING] JVMTI not available, cannot get loaded classes" << std::endl;
        return;
    }

    jclass* classes = nullptr;
    jint count = 0;

    std::cout << "[DEBUG] Calling JVMTI GetLoadedClasses..." << std::endl;
    jvmtiError err = jvmti->GetLoadedClasses(&count, &classes);

    if (err != JVMTI_ERROR_NONE) {
        std::cerr << "[!] GetLoadedClasses failed with error: " << err << std::endl;
        return;
    }

    std::cout << "[DEBUG] Found " << count << " loaded classes" << std::endl;

    if (env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception detected before processing classes" << std::endl;
        env->ExceptionDescribe();
        env->ExceptionClear();
        jvmti->Deallocate((unsigned char*)classes);
        return;
    }

    jclass classClass = env->FindClass("java/lang/Class");
    if (!classClass) {
        std::cerr << "[!] Failed to find java.lang.Class" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        jvmti->Deallocate((unsigned char*)classes);
        return;
    }

    jmethodID getName = env->GetMethodID(classClass, "getName", "()Ljava/lang/String;");
    if (!getName) {
        std::cerr << "[!] Failed to get getName method" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        env->DeleteLocalRef(classClass);
        jvmti->Deallocate((unsigned char*)classes);
        return;
    }

    std::lock_guard<std::mutex> lock(classesMutex);

    for (auto& pair : loadedClasses) {
        if (pair.second) {
            env->DeleteGlobalRef(pair.second);
        }
    }
    loadedClasses.clear();

    std::cout << "[DEBUG] Processing " << count << " classes..." << std::endl;

    for (int i = 0; i < count; i++) {
        if (!classes[i]) {
            std::cout << "[WARNING] Null class at index " << i << std::endl;
            continue;
        }

        if (env->ExceptionCheck()) {
            std::cerr << "[!] Exception at class index " << i << std::endl;
            env->ExceptionDescribe();
            env->ExceptionClear();
            continue;
        }

        jstring name = (jstring)env->CallObjectMethod(classes[i], getName);
        if (!name) {
            std::cout << "[WARNING] Failed to get name for class at index " << i << std::endl;
            if (env->ExceptionCheck()) {
                env->ExceptionDescribe();
                env->ExceptionClear();
            }
            continue;
        }

        const char* className = env->GetStringUTFChars(name, nullptr);
        if (className) {
            std::string classNameStr(className);

            jclass globalRef = (jclass)env->NewGlobalRef(classes[i]);
            if (globalRef) {
                loadedClasses[classNameStr] = globalRef;
                std::cout << "[DEBUG] Added class: " << classNameStr << std::endl;
            }
            else {
                std::cout << "[WARNING] Failed to create global ref for: " << classNameStr << std::endl;
            }

            env->ReleaseStringUTFChars(name, className);
        }

        env->DeleteLocalRef(name);
    }

    env->DeleteLocalRef(classClass);
    jvmti->Deallocate((unsigned char*)classes);

    std::cout << "[DEBUG] GetLoadedClasses complete, stored " << loadedClasses.size() << " classes" << std::endl;
}

jclass ClassLoader::FindClass(const std::string& className) {
    std::cout << "[DEBUG] FindClass called for: " << className << std::endl;

    if (!env) {
        std::cerr << "[!] JNI environment is null" << std::endl;
        return nullptr;
    }

    {
        std::lock_guard<std::mutex> lock(classesMutex);
        auto it = loadedClasses.find(className);
        if (it != loadedClasses.end()) {
            std::cout << "[DEBUG] Found class in cache: " << className << std::endl;
            return it->second;
        }
    }

    std::cout << "[DEBUG] Class not in cache, attempting to load: " << className << std::endl;

    if (env->ExceptionCheck()) {
        std::cerr << "[!] JNI exception present before FindClass" << std::endl;
        env->ExceptionDescribe();
        env->ExceptionClear();
        return nullptr;
    }

    jstring jClassName = env->NewStringUTF(className.c_str());
    if (!jClassName) {
        std::cerr << "[!] Failed to create jstring for class name" << std::endl;
        return nullptr;
    }

    jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
    if (!classLoaderClass) {
        std::cerr << "[!] Failed to find ClassLoader class" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        env->DeleteLocalRef(jClassName);
        return nullptr;
    }

    jmethodID getSystemClassLoader = env->GetStaticMethodID(classLoaderClass,
        "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
    if (!getSystemClassLoader) {
        std::cerr << "[!] Failed to get getSystemClassLoader method" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        env->DeleteLocalRef(jClassName);
        env->DeleteLocalRef(classLoaderClass);
        return nullptr;
    }

    jobject systemClassLoader = env->CallStaticObjectMethod(classLoaderClass, getSystemClassLoader);
    if (!systemClassLoader) {
        std::cerr << "[!] Failed to get system class loader" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        env->DeleteLocalRef(jClassName);
        env->DeleteLocalRef(classLoaderClass);
        return nullptr;
    }

    jmethodID loadClass = env->GetMethodID(classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    if (!loadClass) {
        std::cerr << "[!] Failed to get loadClass method" << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        env->DeleteLocalRef(jClassName);
        env->DeleteLocalRef(classLoaderClass);
        env->DeleteLocalRef(systemClassLoader);
        return nullptr;
    }

    jclass clazz = (jclass)env->CallObjectMethod(systemClassLoader, loadClass, jClassName);

    env->DeleteLocalRef(jClassName);
    env->DeleteLocalRef(classLoaderClass);
    env->DeleteLocalRef(systemClassLoader);

    if (!clazz) {
        std::cout << "[WARNING] Failed to load class: " << className << std::endl;
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return nullptr;
    }

    jclass globalRef = (jclass)env->NewGlobalRef(clazz);
    env->DeleteLocalRef(clazz);

    if (globalRef) {
        std::lock_guard<std::mutex> lock(classesMutex);
        loadedClasses[className] = globalRef;
        std::cout << "[DEBUG] Successfully loaded and cached class: " << className << std::endl;
    }

    return globalRef;
}

ClassLoader::~ClassLoader() {
    std::cout << "[DEBUG] ClassLoader destructor called" << std::endl;

    if (env) {
        std::lock_guard<std::mutex> lock(classesMutex);

        for (auto& pair : loadedClasses) {
            if (pair.second) {
                env->DeleteGlobalRef(pair.second);
            }
        }
        loadedClasses.clear();

        if (threadAttached && jvm) {
            std::cout << "[DEBUG] Detaching thread" << std::endl;
            jvm->DetachCurrentThread();
        }
    }

    std::cout << "[DEBUG] ClassLoader destructor complete" << std::endl;
}