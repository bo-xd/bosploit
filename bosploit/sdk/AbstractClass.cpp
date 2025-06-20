#include "AbstractClass.h"

AbstractClass::AbstractClass() {
    this->clsKey = nullptr;
    this->cls = nullptr;
}

AbstractClass::AbstractClass(const char* clsName) {
    this->clsKey = clsName;

    const char* realName = Mapping::getClassName(clsName);
    if (!realName) {
        std::cerr << "[-] No class mapping found for: " << clsName << std::endl;
        return;
    }

    cls = getClass(realName, "vanilla");
    if (!cls) {
        std::cerr << "[-] Failed to load class for: " << realName << std::endl;
        return;
    }

    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
}

void AbstractClass::GetLoadedClasses() {
    std::cout << "[Debug] Entered GetLoadedClasses()" << std::endl;

    if (!javaVmManager) {
        std::cerr << "[!] javaVmManager is null!" << std::endl;
        return;
    }

    JNIEnv* env = javaVmManager->GetJNIEnv();
    jvmtiEnv* jenv = javaVmManager->GetjvmtiEnv();

    if (!env || !jenv) {
        std::cerr << "[!] JNIEnv or jvmtiEnv is null!" << std::endl;
        return;
    }

    jclass* classes = nullptr;
    jint count = 0;

    jvmtiError err = jenv->GetLoadedClasses(&count, &classes);
    if (err != JVMTI_ERROR_NONE || !classes || count <= 0) {
        std::cerr << "[!] GetLoadedClasses failed or returned no classes. Error: " << err << std::endl;
        return;
    }

    jclass classClass = env->FindClass("java/lang/Class");
    if (!classClass) {
        std::cerr << "[!] Failed to find java/lang/Class" << std::endl;
        jenv->Deallocate((unsigned char*)classes);
        return;
    }

    jmethodID getName = env->GetMethodID(classClass, "getName", "()Ljava/lang/String;");
    if (!getName) {
        std::cerr << "[!] Failed to get getName() method" << std::endl;
        jenv->Deallocate((unsigned char*)classes);
        return;
    }

    std::lock_guard<std::mutex> lock(classesMutex);
    loadedClasses.clear();

    for (int i = 0; i < count; i++) {
        jstring name = (jstring)env->CallObjectMethod(classes[i], getName);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
            continue;
        }

        if (name) {
            const char* className = env->GetStringUTFChars(name, nullptr);
            if (className) {
                std::string classNameStr(className);
                jclass globalRef = (jclass)env->NewGlobalRef(classes[i]);
                if (globalRef) {
                    loadedClasses[classNameStr] = globalRef;
                }
                env->ReleaseStringUTFChars(name, className);
            }
            env->DeleteLocalRef(name);
        }
    }

    jenv->Deallocate((unsigned char*)classes);
    std::cout << "[*] Loaded classes cached (" << loadedClasses.size() << " entries)" << std::endl;
}

jclass AbstractClass::getClassLoaded(const std::string& className) {
    std::lock_guard<std::mutex> lock(classesMutex);
    auto it = loadedClasses.find(className);
    return it != loadedClasses.end() ? it->second : nullptr;
}

jclass AbstractClass::getClass(const char* clsName, const char* loaderType) {
    if (strcmp(loaderType, "fabric") == 0) {
        jclass cached = getClassLoaded(clsName);
        if (cached != nullptr) {
            return cached;
        }
        else {
            std::cerr << "[-] Class not found in loaded class cache: " << clsName << std::endl;
            return nullptr;
        }
    }

    JNIEnv* env = javaVmManager->GetJNIEnv();
    jstring name = env->NewStringUTF(clsName);

    jobject classLoader = nullptr;

    if (strcmp(loaderType, "vanilla") == 0) {
        jclass clsLoaderClass = env->FindClass("java/lang/ClassLoader");
        jmethodID getSysLoader = env->GetStaticMethodID(clsLoaderClass, "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
        classLoader = env->CallStaticObjectMethod(clsLoaderClass, getSysLoader);
    }
    else {
        std::cerr << "[-] Unknown loader type: " << loaderType << std::endl;
        return nullptr;
    }

    if (!classLoader) {
        std::cerr << "[-] Failed to get class loader for " << loaderType << std::endl;
        return nullptr;
    }

    jclass classLoaderClass = env->GetObjectClass(classLoader);
    jmethodID mid = env->GetMethodID(classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    if (!mid) {
        std::cerr << "[-] Could not find loadClass method." << std::endl;
        return nullptr;
    }

    return (jclass)env->CallObjectMethod(classLoader, mid, name);
}


jclass AbstractClass::getClass() {
    return cls;
}

jfieldID AbstractClass::getFieldID(const char* name) {
    CM* cm = Mapping::getClass(clsKey);
    Mem field = cm->fields.at(std::string(name));
    return getFieldIDByDetails(field.name, field.desc, field.isStatic);
}

jmethodID AbstractClass::getMethodID(const char* name) {
    CM* cm = Mapping::getClass(clsKey);
    Mem method = cm->methods.at(std::string(name));
    return getMethodIDByDetails(method.name, method.desc, method.isStatic);
}

jfieldID AbstractClass::getFieldIDByDetails(const char* name, const char* sig, bool isStatic) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (isStatic) return env->GetStaticFieldID(cls, name, sig);
    return env->GetFieldID(cls, name, sig);
}

jmethodID AbstractClass::getMethodIDByDetails(const char* name, const char* sig, bool isStatic) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    if (isStatic) return env->GetStaticMethodID(cls, name, sig);
    return env->GetMethodID(cls, name, sig);
}

