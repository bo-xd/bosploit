#pragma once
#include <jni.h>
#include <string>

class LocalPlayer {
public:
    static jobject getPlayer();

    // Actions
    static void swing();
	static void getSlot(int* slot);
	static void getHotBar(int* hotbar);
    static void setSlot(int slot);
	static bool drop(bool fullstack);

    // State
    static bool setSprinting(bool sprinting);
    static bool isSprinting(bool* result);
	static bool isCrouching(bool* result);

    // pos
	static void getY(double* y);
    static void getX(double* x);
    static void getZ(double* z);
};
