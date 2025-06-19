#pragma once

#include <jvmti.h>
#include "CM.h"
#include "Mapping.h"
#include "../src/Java.h"

class AbstractClass {
public:
    AbstractClass(const char* clsName);

    jobject getClassLoader();
    jclass getClass(const char* clsName, const char* loadertype);
    jclass getClass();

    //Boolean
    template <class T> jboolean getBoolean(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallBooleanMethod(parent, method, values); }
    template <class T> jboolean getBoolean(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticBooleanMethod(cls, method, values); }
    jboolean getBoolean(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallBooleanMethod(parent, method); }
    jboolean getBoolean(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticBooleanMethod(cls, method); }
    jboolean getBoolean(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetBooleanField(parent, field); }
    jboolean getBoolean(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticBooleanField(cls, field); }

    //Byte
    template <class T> jbyte getByte(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallByteMethod(parent, method, values); }
    template <class T> jbyte getByte(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticByteMethod(cls, method, values); }
    jbyte getByte(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallByteMethod(parent, method); }
    jbyte getByte(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticByteMethod(cls, method); }
    jbyte getByte(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetByteField(parent, field); }
    jbyte getByte(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticByteField(cls, field); }

    //Char
    template <class T> jchar getChar(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallCharMethod(parent, method, values); }
    template <class T> jchar getChar(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticCharMethod(cls, method, values); }
    jchar getChar(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallCharMethod(parent, method); }
    jchar getChar(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticCharMethod(cls, method); }
    jchar getChar(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetCharField(parent, field); }
    jchar getChar(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticCharField(cls, field); }

    //Short
    template <class T> jshort getShort(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallShortMethod(parent, method, values); }
    template <class T> jshort getShort(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticShortMethod(cls, method, values); }
    jshort getShort(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallShortMethod(parent, method); }
    jshort getShort(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticShortMethod(cls, method); }
    jshort getShort(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetShortField(parent, field); }
    jshort getShort(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticShortField(cls, field); }

    //Int
    template <class T> jint getInt(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallIntMethod(parent, method, values); }
    template <class T> jint getInt(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticIntMethod(cls, method, values); }
    jint getInt(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallIntMethod(parent, method); }
    jint getInt(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticIntMethod(cls, method); }
    jint getInt(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetIntField(parent, field); }
    jint getInt(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticIntField(cls, field); }

    //Long
    template <class T> jlong getLong(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallLongMethod(parent, method, values); }
    template <class T> jlong getLong(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticLongMethod(cls, method, values); }
    jlong getLong(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallLongMethod(parent, method); }
    jlong getLong(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticLongMethod(cls, method); }
    jlong getLong(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetLongField(parent, field); }
    jlong getLong(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticLongField(cls, field); }

    //Float
    template <class T> jfloat getFloat(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallFloatMethod(parent, method, values); }
    template <class T> jfloat getFloat(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticFloatMethod(cls, method, values); }
    jfloat getFloat(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallFloatMethod(parent, method); }
    jfloat getFloat(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticFloatMethod(cls, method); }
    jfloat getFloat(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetFloatField(parent, field); }
    jfloat getFloat(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticFloatField(cls, field); }

    //Double
    template <class T> jdouble getDouble(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallDoubleMethod(parent, method, values); }
    template <class T> jdouble getDouble(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticDoubleMethod(cls, method, values); }
    jdouble getDouble(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallDoubleMethod(parent, method); }
    jdouble getDouble(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticDoubleMethod(cls, method); }
    jdouble getDouble(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetDoubleField(parent, field); }
    jdouble getDouble(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticDoubleField(cls, field); }

    //Object
    template <class T> jobject getObject(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallObjectMethod(parent, method, values); }
    template <class T> jobject getObject(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticObjectMethod(cls, method, values); }
    jobject getObject(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallObjectMethod(parent, method); }
    jobject getObject(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticObjectMethod(cls, method); }
    jobject getObject(jobject parent, jfieldID field) { return javaVmManager->GetJNIEnv()->GetObjectField(parent, field); }
    jobject getObject(jfieldID field) { return javaVmManager->GetJNIEnv()->GetStaticObjectField(cls, field); }

    //Array
    int getArrayLength(jobjectArray arr) { return javaVmManager->GetJNIEnv()->GetArrayLength(arr); }
    jobject getArrayElement(jobjectArray arr, jsize index) { return javaVmManager->GetJNIEnv()->GetObjectArrayElement(arr, index); }

    //Void
    template <class T> void callMethod(jobject parent, jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallVoidMethod(parent, method, values); }
    template <class T> void callMethod(jmethodID method, T values...) { return javaVmManager->GetJNIEnv()->CallStaticVoidMethod(cls, method, values); }
    void callMethod(jobject parent, jmethodID method) { return javaVmManager->GetJNIEnv()->CallVoidMethod(parent, method); }
    void callMethod(jmethodID method) { return javaVmManager->GetJNIEnv()->CallStaticVoidMethod(cls, method); }

    void setBoolean(jobject parent, jfieldID field, jboolean value) { javaVmManager->GetJNIEnv()->SetBooleanField(parent, field, value); }
    void setBoolean(jfieldID field, jboolean value) { javaVmManager->GetJNIEnv()->SetStaticBooleanField(cls, field, value); }

    void setByte(jobject parent, jfieldID field, jbyte value) { javaVmManager->GetJNIEnv()->SetByteField(parent, field, value); }
    void setByte(jfieldID field, jbyte value) { javaVmManager->GetJNIEnv()->SetStaticByteField(cls, field, value); }

    void setChar(jobject parent, jfieldID field, jchar value) { javaVmManager->GetJNIEnv()->SetCharField(parent, field, value); }
    void setChar(jfieldID field, jchar value) { javaVmManager->GetJNIEnv()->SetStaticCharField(cls, field, value); }

    void setShort(jobject parent, jfieldID field, jshort value) { javaVmManager->GetJNIEnv()->SetShortField(parent, field, value); }
    void setShort(jfieldID field, jshort value) { javaVmManager->GetJNIEnv()->SetStaticShortField(cls, field, value); }

    void setInt(jobject parent, jfieldID field, jint value) { javaVmManager->GetJNIEnv()->SetIntField(parent, field, value); }
    void setInt(jfieldID field, jint value) { javaVmManager->GetJNIEnv()->SetStaticIntField(cls, field, value); }

    void setLong(jobject parent, jfieldID field, jlong value) { javaVmManager->GetJNIEnv()->SetLongField(parent, field, value); }
    void setLong(jfieldID field, jlong value) { javaVmManager->GetJNIEnv()->SetStaticLongField(cls, field, value); }

    void setFloat(jobject parent, jfieldID field, jfloat value) { javaVmManager->GetJNIEnv()->SetFloatField(parent, field, value); }
    void setFloat(jfieldID field, jfloat value) { javaVmManager->GetJNIEnv()->SetStaticFloatField(cls, field, value); }

    void setDouble(jobject parent, jfieldID field, jdouble value) { javaVmManager->GetJNIEnv()->SetDoubleField(parent, field, value); }
    void setDouble(jfieldID field, jdouble value) { javaVmManager->GetJNIEnv()->SetStaticDoubleField(cls, field, value); }

    void setObject(jobject parent, jfieldID field, jobject value) { javaVmManager->GetJNIEnv()->SetObjectField(parent, field, value); }
    void setObject(jfieldID field, jobject value) { javaVmManager->GetJNIEnv()->SetStaticObjectField(cls, field, value); }

protected:
    const char* clsKey;
    jclass cls;

    jfieldID getFieldID(const char* name);
    jmethodID getMethodID(const char* name);

private:
    jfieldID getFieldIDByDetails(const char* name, const char* sig, bool isStatic);
    jmethodID getMethodIDByDetails(const char* name, const char* sig, bool isStatic);
};