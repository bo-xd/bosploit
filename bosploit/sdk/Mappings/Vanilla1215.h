#pragma once
#include "../Mapping.h"

struct Vanilla1215 {
    static void setup() {
        struct CM* m = Mapping::make("List", "java.util.List");
        // EntityPlayerSP
        m = Mapping::make("EntityPlayerSP", "bxe");
        Mapping::method(m, "setSprint", "h", "(Z)V", false);
        Mapping::method(m, "isSprinting", "ci", "()Z", false);
        Mapping::method(m, "isCrouching", "ch", "()Z", false);
        Mapping::method(m, "x", "dA", "()D", false);
        Mapping::method(m, "y", "dC", "()D", false);
        Mapping::method(m, "z", "dG", "()D", false);
        // EntityPlayer
        m = Mapping::make("EntityPlayer", "gqm");
        Mapping::method(m, "drop", "a", "(Z)Z", false);
        // minecraft
        m = Mapping::make("Minecraft", "fqq");
        Mapping::method(m, "getMinecraft", "Q", "()Lfqq;", true);
        Mapping::field(m, "player", "t", "Lgqm;", false);

    }
};
