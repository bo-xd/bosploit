#pragma once
#include "../Mapping.h"

struct Fabric1215Mappings {
    static void setup() {
        // List class
        Mapping::RegisterClass("List", "java.util.List");

        // EntityPlayerSP class and methods
        Mapping::RegisterClass("EntityPlayerSP", "net.minecraft.class_1297");
        Mapping::RegisterMethod("EntityPlayerSP", "setSprint", "method_5728", "(Z)V", false);
        Mapping::RegisterMethod("EntityPlayerSP", "isSprinting", "method_5624", "()Z", false);
        Mapping::RegisterMethod("EntityPlayerSP", "isCrouching", "method_5715", "()Z", false);
        Mapping::RegisterMethod("EntityPlayerSP", "x", "method_23317", "()D", false);
        Mapping::RegisterMethod("EntityPlayerSP", "y", "method_23318", "()D", false);
        Mapping::RegisterMethod("EntityPlayerSP", "z", "method_23321", "()D", false);

        // EntityPlayer class and methods
        Mapping::RegisterClass("EntityPlayer", "net.minecraft.class_746");
        Mapping::RegisterMethod("EntityPlayer", "drop", "method_7290", "(Z)Z", false);

        // Minecraft class, methods and fields
        Mapping::RegisterClass("Minecraft", "net.minecraft.class_310");
        Mapping::RegisterMethod("Minecraft", "getMinecraft", "method_1551", "()Lnet/minecraft/class_310;", true);
        Mapping::RegisterMethod("Minecraft", "getConnection", "method_1562", "()Lglp;", false);
        Mapping::RegisterField("Minecraft", "player", "field_1724", "Lgqm;");
    }
};
