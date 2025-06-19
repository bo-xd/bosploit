#include "Minecraft.h"

Minecraft::Minecraft() : AbstractClass("Minecraft") {
    getMinecraftMethod = getMethodID("getMinecraft");
    if (!getMinecraftMethod) {
        std::cerr << "[-] Failed to resolve getMinecraft method!\n";
    }
}

jobject Minecraft::getMinecraft() {
    return getObject(getMinecraftMethod);
}
