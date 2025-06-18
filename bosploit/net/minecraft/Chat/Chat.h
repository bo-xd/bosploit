#pragma once
#include <jni.h>
#include <string>

class Chat {
public:
	static void sendMessage(const std::string& message);
};