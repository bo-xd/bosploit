#pragma once
#include "../Mapping.h"

struct Vanilla1215Mappings {
    static void setup() {
        Mapping::RegisterClass("List", "java.util.List");

        // EntityPlayerSP (bxe)
        Mapping::RegisterClass("EntityPlayerSP", "bxe");
        Mapping::RegisterMethod("EntityPlayerSP", "setSprint", "h", "(Z)V", false);
        Mapping::RegisterMethod("EntityPlayerSP", "isSprinting", "ci", "()Z", false);
        Mapping::RegisterMethod("EntityPlayerSP", "isCrouching", "ch", "()Z", false);
        Mapping::RegisterMethod("EntityPlayerSP", "x", "dA", "()D", false);
        Mapping::RegisterMethod("EntityPlayerSP", "y", "dC", "()D", false);
        Mapping::RegisterMethod("EntityPlayerSP", "z", "dG", "()D", false);

        // EntityPlayer (gqm)
        Mapping::RegisterClass("EntityPlayer", "gqm");
        Mapping::RegisterMethod("EntityPlayer", "drop", "a", "(Z)Z", false);

        // Minecraft (fqq)
        Mapping::RegisterClass("Minecraft", "fqq");
        Mapping::RegisterMethod("Minecraft", "getMinecraft", "Q", "()Lfqq;", true);
        Mapping::RegisterMethod("Minecraft", "getConnection", "L", "()Lglp;", false);
        Mapping::RegisterField("Minecraft", "player", "t", "Lgqm;");
    }
};
