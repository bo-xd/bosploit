#include "EntityPlayerSP.h"
#include "../../Minecraft.h"

#include "../../../src/Java.h"

EntityPlayerSP::EntityPlayerSP() : AbstractClass("EntityPlayerSP") {
    mc = new Minecraft();
    mdSetSprinting = getMethodID("setSprint");
}

void EntityPlayerSP::setSprinting(jboolean sprinting) {
    callMethod(mc->getPlayer(), mdSetSprinting, sprinting);
}
