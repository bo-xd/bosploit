#pragma once
#include "../Mapping.h"

struct Vanilla1215Mappings {
    static void setup() {
        Mapping::RegisterClass("List", "java.util.List");

        Mapping::RegisterClass("Entity", "bxe");
        Mapping::RegisterMethod("Entity", "setSprint", "h", "(Z)V", false);
        Mapping::RegisterMethod("Entity", "isSprinting", "ci", "()Z", false);
        Mapping::RegisterMethod("Entity", "isCrouching", "ch", "()Z", false);
        Mapping::RegisterMethod("Entity", "x", "dA", "()D", false);
        Mapping::RegisterMethod("Entity", "y", "dC", "()D", false);
        Mapping::RegisterMethod("Entity", "z", "dG", "()D", false);

		Mapping::RegisterClass("InteractionHand", "bvb");
		Mapping::RegisterField("InteractionHand", "MAIN_HAND", "a", "Lbvb;");

        Mapping::RegisterClass("LocalPlayer", "gqm");
        Mapping::RegisterMethod("LocalPlayer", "drop", "a", "(Z)Z", false);
        Mapping::RegisterMethod("LocalPlayer", "swing", "a", "(Lbvb;)V", false);

        Mapping::RegisterClass("player", "csi");
		Mapping::RegisterMethod("player", "attack", "e", "(Lbxe;)V", false);

        Mapping::RegisterClass("HitResult", "fga");
		Mapping::RegisterMethod("HitResult", "getType", "d", "()Lfgb;", false);

        Mapping::RegisterClass("Minecraft", "fqq");
        Mapping::RegisterMethod("Minecraft", "getMinecraft", "Q", "()Lfqq;", true);
        Mapping::RegisterMethod("Minecraft", "getConnection", "L", "()Lglp;", false);
        Mapping::RegisterField("Minecraft", "player", "t", "Lgqm;");
		Mapping::RegisterMethod("Minecraft", "getCameraEntity", "ao", "()Lbxe;", false);
    }
};