#pragma once
#include <jni.h>

class LocalPlayer {
public:
    static jobject getPlayer();
    static void setSprinting(bool sprinting);
    static void isSprinting(bool* result);
};
