#include "AbstractClass.h"

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

jobject AbstractClass::getClassLoader() {
    JNIEnv* env = javaVmManager->GetJNIEnv();

    jclass launch = env->FindClass("net/minecraft/launchwrapper/Launch");
    jfieldID sfid = env->GetStaticFieldID(launch, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
    jobject classLoader = env->GetStaticObjectField(launch, sfid);

    return classLoader;
}

jclass AbstractClass::getClass(const char* clsName, const char* loaderType) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    jstring name = env->NewStringUTF(clsName);

    jobject classLoader = nullptr;

    if (strcmp(loaderType, "forge") == 0 || strcmp(loaderType, "fabric") == 0) {
        classLoader = getClassLoader();
    }
    else if (strcmp(loaderType, "vanilla") == 0) {
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

