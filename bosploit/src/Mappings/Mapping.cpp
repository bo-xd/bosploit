#ifdef RegisterClass
#undef RegisterClass
#endif
#include "Mapping.h"
#include "../utils/ClassLoader/ClassLoader.h"
#include <iostream>

JNIEnv* Mapping::env = nullptr;
ClassLoader* Mapping::classLoader = nullptr;
std::unordered_map<std::string, std::string> Mapping::classNames;
std::unordered_map<std::string, jclass> Mapping::classes;
std::unordered_map<std::string, std::unordered_map<std::string, MethodInfo>> Mapping::methods;
std::unordered_map<std::string, std::unordered_map<std::string, FieldInfo>> Mapping::fields;

void Mapping::Initialize(JNIEnv* env_, ClassLoader* classLoader_) {
    env = env_;
    classLoader = classLoader_;

    for (auto& [logicalName, javaClassName] : classNames) {
        jclass foundClass = classLoader->FindClass(javaClassName);
        classes[logicalName] = foundClass;
        if (!foundClass) {
            std::cerr << "[!] Failed to find class " << javaClassName << std::endl;
        }
    }

    CacheMethodIds();
    CacheFieldIds();
}

void Mapping::RegisterClass(const std::string& logicalName, const std::string& javaClassName) {
    classNames[logicalName] = javaClassName;
    classes[logicalName] = nullptr;
}

void Mapping::RegisterMethod(const std::string& classLogicalName,
    const std::string& methodLogicalName,
    const std::string& methodName,
    const std::string& signature,
    bool isStatic) {
    methods[classLogicalName][methodLogicalName] = MethodInfo{ methodName, signature, nullptr, isStatic };
}

void Mapping::RegisterField(const std::string& classLogicalName,
    const std::string& fieldLogicalName,
    const std::string& fieldName,
    const std::string& signature) {
    fields[classLogicalName][fieldLogicalName] = FieldInfo{ fieldName, signature, nullptr };
}

void Mapping::CacheMethodIds() {
    for (auto& [classLogicalName, methodMap] : methods) {
        jclass clazz = classes[classLogicalName];
        if (!clazz) continue;

        for (auto& [methodLogicalName, info] : methodMap) {
            jmethodID mid;
            if (info.isStatic) {
                mid = env->GetStaticMethodID(clazz, info.name.c_str(), info.signature.c_str());
            }
            else {
                mid = env->GetMethodID(clazz, info.name.c_str(), info.signature.c_str());
            }

            if (!mid) {
                std::cerr << "[!] Failed to find method " << info.name << " with signature " << info.signature << std::endl;
            }
            info.methodId = mid;
        }
    }
}


void Mapping::CacheFieldIds() {
    for (auto& [classLogicalName, fieldMap] : fields) {
        jclass clazz = classes[classLogicalName];
        if (!clazz) continue;

        for (auto& [fieldLogicalName, info] : fieldMap) {
            jfieldID fid = env->GetFieldID(clazz, info.name.c_str(), info.signature.c_str());
            if (!fid) {
                std::cerr << "[!] Failed to find field " << info.name << " with signature " << info.signature << std::endl;
            }
            info.fieldId = fid;
        }
    }
}

jclass Mapping::GetClass(const std::string& logicalName) {
    auto it = classes.find(logicalName);
    if (it != classes.end()) return it->second;
    return nullptr;
}

jmethodID Mapping::GetMethod(const std::string& classLogicalName, const std::string& methodLogicalName) {
    auto itClass = methods.find(classLogicalName);
    if (itClass == methods.end()) return nullptr;

    auto itMethod = itClass->second.find(methodLogicalName);
    if (itMethod == itClass->second.end()) return nullptr;

    return itMethod->second.methodId;
}

jfieldID Mapping::GetField(const std::string& classLogicalName, const std::string& fieldLogicalName) {
    auto itClass = fields.find(classLogicalName);
    if (itClass == fields.end()) return nullptr;

    auto itField = itClass->second.find(fieldLogicalName);
    if (itField == itClass->second.end()) return nullptr;

    return itField->second.fieldId;
}