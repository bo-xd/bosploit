#pragma once
#include "../Mapping.h"

struct Fabric1215 {
    static void setup() {
        struct CM* m = Mapping::make("List", "java.util.List");
        // EntityPlayerSP
        m = Mapping::make("EntityPlayerSP", "net.minecraft.class_1297");
        Mapping::method(m, "setSprint", "method_5728", "(Z)V", false);
        Mapping::method(m, "isSprinting", "method_5624", "()Z", false);
        Mapping::method(m, "isCrouching", "method_5715", "()Z", false);
        Mapping::method(m, "x", "method_23317", "()D", false);
        Mapping::method(m, "y", "method_23318", "()D", false);
        Mapping::method(m, "z", "method_23321", "()D", false);
        // EntityPlayer
        m = Mapping::make("EntityPlayer", "net.minecraft.class_746");
        Mapping::method(m, "drop", "method_7290", "(Z)Z", false);
        // minecraft
        m = Mapping::make("Minecraft", "net.minecraft.class_310");
        Mapping::method(m, "getMinecraft", "method_1551", "()Lnet/minecraft/class_310;", true);
        Mapping::method(m, "getConnection", "method_1562", "()Lglp;", false);
        Mapping::field(m, "player", "field_1724", "Lgqm;", false);
    }
};
