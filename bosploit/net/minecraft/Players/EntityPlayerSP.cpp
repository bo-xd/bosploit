#include "EntityPlayerSP.h"
#include "../../Minecraft.h"

EntityPlayerSP::EntityPlayerSP() : AbstractClass("EntityPlayerSP") {
    mc = new Minecraft();
    mdSetSprinting = getMethodID("setSprint");
    mdisSprinting = getMethodID("isSprinting");
    mdisCrouching = getMethodID("isCrouching");
    mdx = getMethodID("x");
    mdy = getMethodID("y");
    mdz = getMethodID("z");
}

void EntityPlayerSP::setSprinting(jboolean sprinting) {
    callMethod(mc->getPlayer(), mdSetSprinting, sprinting);
}

bool EntityPlayerSP::isSprinting() {
    return getBoolean(mc->getPlayer(), mdisSprinting);
}

bool EntityPlayerSP::isCrouching() {
    return getBoolean(mc->getPlayer(), mdisCrouching);
}

double EntityPlayerSP::x() {
    return getDouble(mc->getPlayer(), mdx);
}
double EntityPlayerSP::y() {
    return getDouble(mc->getPlayer(), mdy);
}
double EntityPlayerSP::z() {
    return getDouble(mc->getPlayer(), mdz);
}