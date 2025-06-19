#include "EntityPlayer.h"
#include "../../Minecraft.h"

EntityPlayer::EntityPlayer() : AbstractClass("EntityPlayer") {
	mc = new Minecraft();
	mdDrop = getMethodID("drop");
}

void EntityPlayer::drop(jboolean fullstack) {
	callMethod(mc->getPlayer(), mdDrop, fullstack);
}
