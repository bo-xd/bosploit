#include "AbstractClass.h"
#include "ClassLoader.h"
#include "Mapping.h"
#include "../src/Java.h"

AbstractClass::AbstractClass(const char* clsName) {
    this->clsKey = clsName;

    const char* realName = Mapping::getClassName(clsName);
    if (!realName) {
        std::cerr << "[-] No class mapping found for: " << clsName << std::endl;
        return;
    }

    cls = g_classLoader->FindClass(realName);
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
    return isStatic ? env->GetStaticFieldID(cls, name, sig) : env->GetFieldID(cls, name, sig);
}

jmethodID AbstractClass::getMethodIDByDetails(const char* name, const char* sig, bool isStatic) {
    JNIEnv* env = javaVmManager->GetJNIEnv();
    return isStatic ? env->GetStaticMethodID(cls, name, sig) : env->GetMethodID(cls, name, sig);
}
