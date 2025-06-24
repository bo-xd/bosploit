#pragma once
#include <jni.h>

class Minecraft;

class LocalPlayer {
public:
	LocalPlayer();

	void setSprinting(jboolean sprinting);
	void swing();
	void drop(jboolean fullstack);
	bool isSprinting();
	bool isCrouching();

	double x();
	double y();
	double z();
private:
	Minecraft* mc;

	jmethodID methodSetSprinting = nullptr;

	jmethodID dropMethod = nullptr;
	jmethodID swingmethod = nullptr;
	jmethodID attackmethod = nullptr;

	jfieldID Mainhand = nullptr;

	jmethodID methodIsSprinting = nullptr;
	jmethodID methodIsCrouching = nullptr;

	jmethodID methodX = nullptr;
	jmethodID methodY = nullptr;
	jmethodID methodZ = nullptr;
};