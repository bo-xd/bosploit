#pragma once
#pragma once
#include "../../sdk/AbstractClass.h"
#include "../../Minecraft.h"

class EntityPlayer : public AbstractClass {
public:
	explicit EntityPlayer();
	void drop(jboolean fullstack);
private:
	Minecraft* mc;
	jmethodID mdDrop;
};

