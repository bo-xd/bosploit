#pragma once
#include "../Mapping.h"

struct Vanilla1215 {
    static void setup() {
        struct CM* m = Mapping::make("List", "java.util.List");

        // minecraft
        m = Mapping::make("Minecraft", "fqq");
        Mapping::method(m, "getMinecraft", "Q", "()Lfqq;", true);
    }
};
