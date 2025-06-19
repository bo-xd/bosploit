#pragma once
#include "../Mapping.h"

struct Vanilla1215 {
    static void setup() {
        struct CM* m = Mapping::make("List", "java.util.List");
        // player
        m = Mapping::make("EntityPlayerSP", "bxe");
        Mapping::method(m, "setSprint", "h", "(Z)V", false);

        // minecraft
        m = Mapping::make("Minecraft", "fqq");
        Mapping::method(m, "getMinecraft", "Q", "()Lfqq;", true);
        Mapping::field(m, "player", "t", "Lgqm;", false);

    }
};
