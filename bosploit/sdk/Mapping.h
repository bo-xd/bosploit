#pragma once

#include <map>
#include <string>
#include <iostream>

#include "CM.h"
#include "Mem.h"

extern std::map<std::string, CM*> lookup;

class Mapping {
public:
	Mapping() {
		setup();
	}

	friend struct Vanilla1215;
	friend struct Fabric1215;

	static CM* getClass(const char* key);
	static const char* getClassName(const char* key);
	static void setup();
private:
	static void field(CM *cm, const char* name, const char* desc, bool isStatic);
	static void method(CM* cm, const char* name, const char* desc, bool isStatic);
	static void field(CM *cm, const char* keyName, const char* obName, const char* desc, bool isStatic);
	static void method(CM* cm, const char* keyName, const char* obName, const char* desc, bool isStatic);
	
	static CM* make(const char* key, const char* name);
};