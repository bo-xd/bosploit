#include "EntityPlayer.h"
#include "../../Minecraft.h"
#include "../../../Mappings/Mapping.h"

#include "../../../src/Java.h"

#include <iostream>

EntityPlayer::EntityPlayer() {
    mc = new Minecraft();
    dropMethod = Mapping::GetMethod("EntityPlayer", "drop");

    if (!dropMethod) {
        std::cerr << "[!] Failed to get dropMethod for EntityPlayer" << std::endl;
    }
}

void EntityPlayer::drop(jboolean fullstack) {
    jobject player = mc->getPlayer();
    if (!player || !dropMethod) return;

    g_classLoader->env->CallBooleanMethod(player, dropMethod, fullstack);
}
