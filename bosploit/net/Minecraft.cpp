#include "Minecraft.h"
#include "../Mappings/Mapping.h"
#include "../src/Java.h"

Minecraft::Minecraft() {
    getMinecraftMethod = Mapping::GetMethod("Minecraft", "getMinecraft");
    getConnectionMethod = Mapping::GetMethod("Minecraft", "getConnection");
    getPlayerField = Mapping::GetField("Minecraft", "player");
    minecraftClass = Mapping::GetClass("Minecraft");

    if (!minecraftClass || !getMinecraftMethod || !getConnectionMethod || !getPlayerField) {
        isValid = false;
    }
    else {
        isValid = true;
    }
}

jobject Minecraft::getMinecraft() {
    if (!isValid || !minecraftClass || !getMinecraftMethod) return nullptr;
    if (!g_classLoader || !g_classLoader->env) return nullptr;

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
    }

    jobject result = g_classLoader->env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        return nullptr;
    }

    return result;
}

jobject Minecraft::getPlayer() {
    if (!isValid || !getPlayerField) return nullptr;

    jobject mcInstance = getMinecraft();
    if (!mcInstance) return nullptr;

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
    }

    jobject player = g_classLoader->env->GetObjectField(mcInstance, getPlayerField);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        g_classLoader->env->DeleteLocalRef(mcInstance);
        return nullptr;
    }

    g_classLoader->env->DeleteLocalRef(mcInstance);

    if (!player) return nullptr;

    return player;
}

jobject Minecraft::getConnection() {
    if (!isValid || !getConnectionMethod) return nullptr;

    jobject mcInstance = getMinecraft();
    if (!mcInstance) return nullptr;

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
    }

    jobject connection = g_classLoader->env->CallObjectMethod(mcInstance, getConnectionMethod);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
        g_classLoader->env->DeleteLocalRef(mcInstance);
        return nullptr;
    }

    g_classLoader->env->DeleteLocalRef(mcInstance);

    if (!connection) return nullptr;

    return connection;
}

void Minecraft::sendChat(const std::string& message) {
    if (!isValid) return;

    jobject connection = getConnection();
    if (!connection) return;

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
    }

    jclass connectionClass = g_classLoader->env->GetObjectClass(connection);
    if (!connectionClass) {
        if (g_classLoader->env->ExceptionCheck()) {
            g_classLoader->env->ExceptionClear();
        }
        g_classLoader->env->DeleteLocalRef(connection);
        return;
    }

    jmethodID sendChatMethod = g_classLoader->env->GetMethodID(connectionClass, "b", "(Ljava/lang/String;)V");
    if (!sendChatMethod) {
        if (g_classLoader->env->ExceptionCheck()) {
            g_classLoader->env->ExceptionClear();
        }
        g_classLoader->env->DeleteLocalRef(connectionClass);
        g_classLoader->env->DeleteLocalRef(connection);
        return;
    }

    jstring jMessage = g_classLoader->env->NewStringUTF(message.c_str());
    if (!jMessage) {
        if (g_classLoader->env->ExceptionCheck()) {
            g_classLoader->env->ExceptionClear();
        }
        g_classLoader->env->DeleteLocalRef(connectionClass);
        g_classLoader->env->DeleteLocalRef(connection);
        return;
    }

    g_classLoader->env->CallVoidMethod(connection, sendChatMethod, jMessage);

    if (g_classLoader->env->ExceptionCheck()) {
        g_classLoader->env->ExceptionClear();
    }

    g_classLoader->env->DeleteLocalRef(jMessage);
    g_classLoader->env->DeleteLocalRef(connectionClass);
    g_classLoader->env->DeleteLocalRef(connection);
}
