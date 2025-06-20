#include "Mapping.h"
#include "../sdk/Mappings/Vanilla1215.h"
#include "../sdk/Mappings/Fabric1215.h"

std::map<std::string, CM*> lookup;

CM* Mapping::getClass(const char *key) {
	CM* cm = lookup.at(std::string(key));
	return cm;
}

const char *Mapping::getClassName(const char *key) {
	return getClass(key)->name;
}

void Mapping::setup() {
	Fabric1215::setup();
}

void Mapping::field(CM *cm, const char* name, const char* desc, bool isStatic) {
	field(cm, name, name, desc, isStatic);
}

void Mapping::method(CM *cm, const char* name, const char* desc, bool isStatic) {
	method(cm, name, name, desc, isStatic);
}

void Mapping::field(CM* cm, const char* keyName, const char* obName, const char* desc, bool isStatic) {
	std::cout << " Mapping " << obName << " to " << keyName << std::endl;
	Mem* m = new Mem(obName, desc, isStatic);
	cm->fields.insert(std::make_pair(std::string(keyName), *m));
}

void Mapping::method(CM* cm, const char* keyName, const char* obName, const char* desc, bool isStatic) {
	std::cout << " Mapping " << obName << desc << " to " << keyName << std::endl;
	Mem* m = new Mem(obName, desc, isStatic);
	cm->methods.insert(std::make_pair(std::string(keyName), *m));
}

CM* Mapping::make(const char* key, const char* name) {
	auto* cm = new CM(name);
	std::cout << "Mapping " << name << " to " << key << std::endl;
	lookup.insert(std::make_pair(std::string(key), cm));
	return cm;
}