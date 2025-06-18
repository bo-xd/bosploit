#pragma once
#include <jni.h>

class LocalPlayer {
public:
    static jobject getPlayer();

    //Character
    static void setSprinting(bool sprinting);
    static void isSprinting(bool* result);
	static void isCrouching(bool* result);

    // pos
	static void getY(double* y);
    static void getX(double* x);
    static void getZ(double* z);
};
