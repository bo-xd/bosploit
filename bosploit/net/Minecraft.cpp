#include "Minecraft.h"
#include "../Mappings/Mapping.h"
#include <iostream>
#include "../src/Java.h"

Minecraft::Minecraft() {
    std::cout << "[DEBUG] Initializing Minecraft class..." << std::endl;

    // Get mappings with error checking
    getMinecraftMethod = Mapping::GetMethod("Minecraft", "getMinecraft");
    getConnectionMethod = Mapping::GetMethod("Minecraft", "getConnection");
    getPlayerField = Mapping::GetField("Minecraft", "player");
    minecraftClass = Mapping::GetClass("Minecraft");

    // Debug output
    std::cout << "[DEBUG] Minecraft mappings:" << std::endl;
    std::cout << "  minecraftClass: " << minecraftClass << std::endl;
    std::cout << "  getMinecraftMethod: " << getMinecraftMethod << std::endl;
    std::cout << "  getConnectionMethod: " << getConnectionMethod << std::endl;
    std::cout << "  getPlayerField: " << getPlayerField << std::endl;

    if (!minecraftClass || !getMinecraftMethod || !getConnectionMethod || !getPlayerField) {
        std::cerr << "[!] Failed to initialize Minecraft mappings" << std::endl;
        // Don't return here - let it continue but mark as invalid
        isValid = false;
    }
    else {
        std::cout << "[DEBUG] Minecraft mappings initialized successfully" << std::endl;
        isValid = true;
    }
}

jobject Minecraft::getMinecraft() {
    std::cout << "[DEBUG] getMinecraft() called" << std::endl;

    if (!isValid || !minecraftClass || !getMinecraftMethod) {
        std::cerr << "[!] getMinecraft: Invalid state" << std::endl;
        return nullptr;
    }

    if (!g_classLoader || !g_classLoader->env) {
        std::cerr << "[!] getMinecraft: ClassLoader or env is null" << std::endl;
        return nullptr;
    }

    // Clear any existing exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cout << "[WARNING] Exception present before getMinecraft call" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
    }

    std::cout << "[DEBUG] Calling static method getMinecraft..." << std::endl;
    jobject result = g_classLoader->env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);

    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] Exception during getMinecraft call" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        return nullptr;
    }

    if (!result) {
        std::cout << "[WARNING] getMinecraft returned null" << std::endl;
        return nullptr;
    }

    std::cout << "[DEBUG] getMinecraft successful, result: " << result << std::endl;
    return result;
}

jobject Minecraft::getPlayer() {
    std::cout << "[DEBUG] getPlayer() called" << std::endl;

    if (!isValid || !getPlayerField) {
        std::cerr << "[!] getPlayer: Invalid state or field" << std::endl;
        return nullptr;
    }

    jobject mcInstance = getMinecraft();
    if (!mcInstance) {
        std::cerr << "[!] getPlayer: Failed to get Minecraft instance" << std::endl;
        return nullptr;
    }

    // Clear any existing exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cout << "[WARNING] Exception present before getPlayer field access" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
    }

    std::cout << "[DEBUG] Getting player field..." << std::endl;
    jobject player = g_classLoader->env->GetObjectField(mcInstance, getPlayerField);

    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] Exception during getPlayer field access" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        // Clean up local reference
        g_classLoader->env->DeleteLocalRef(mcInstance);
        return nullptr;
    }

    // Clean up local reference to minecraft instance
    g_classLoader->env->DeleteLocalRef(mcInstance);

    if (!player) {
        std::cout << "[WARNING] Player field is null" << std::endl;
        return nullptr;
    }

    std::cout << "[DEBUG] getPlayer successful, result: " << player << std::endl;
    return player;
}

jobject Minecraft::getConnection() {
    std::cout << "[DEBUG] getConnection() called" << std::endl;

    if (!isValid || !getConnectionMethod) {
        std::cerr << "[!] getConnection: Invalid state or method" << std::endl;
        return nullptr;
    }

    jobject mcInstance = getMinecraft();
    if (!mcInstance) {
        std::cerr << "[!] getConnection: Failed to get Minecraft instance" << std::endl;
        return nullptr;
    }

    // Clear any existing exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cout << "[WARNING] Exception present before getConnection call" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
    }

    std::cout << "[DEBUG] Calling getConnection method..." << std::endl;
    jobject connection = g_classLoader->env->CallObjectMethod(mcInstance, getConnectionMethod);

    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] Exception during getConnection call" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
        // Clean up local reference
        g_classLoader->env->DeleteLocalRef(mcInstance);
        return nullptr;
    }

    // Clean up local reference to minecraft instance
    g_classLoader->env->DeleteLocalRef(mcInstance);

    if (!connection) {
        std::cout << "[WARNING] getConnection returned null" << std::endl;
        return nullptr;
    }

    std::cout << "[DEBUG] getConnection successful, result: " << connection << std::endl;
    return connection;
}

void Minecraft::sendChat(const std::string& message) {
    std::cout << "[DEBUG] sendChat() called with message: " << message << std::endl;

    if (!isValid) {
        std::cerr << "[!] sendChat: Minecraft class not properly initialized" << std::endl;
        return;
    }

    jobject connection = getConnection();
    if (!connection) {
        std::cerr << "[!] sendChat: Failed to get connection" << std::endl;
        return;
    }

    // Clear any existing exceptions
    if (g_classLoader->env->ExceptionCheck()) {
        std::cout << "[WARNING] Exception present before sendChat operations" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
    }

    std::cout << "[DEBUG] Getting connection class..." << std::endl;
    jclass connectionClass = g_classLoader->env->GetObjectClass(connection);
    if (!connectionClass) {
        std::cerr << "[!] sendChat: Failed to get connection class" << std::endl;
        if (g_classLoader->env->ExceptionCheck()) {
            g_classLoader->env->ExceptionDescribe();
            g_classLoader->env->ExceptionClear();
        }
        g_classLoader->env->DeleteLocalRef(connection);
        return;
    }

    std::cout << "[DEBUG] Getting sendChat method..." << std::endl;
    jmethodID sendChatMethod = g_classLoader->env->GetMethodID(connectionClass, "b", "(Ljava/lang/String;)V");
    if (!sendChatMethod) {
        std::cerr << "[!] sendChat: Failed to get sendChat method 'b'" << std::endl;
        if (g_classLoader->env->ExceptionCheck()) {
            std::cout << "[ERROR] Exception details:" << std::endl;
            g_classLoader->env->ExceptionDescribe();
            g_classLoader->env->ExceptionClear();
        }
        g_classLoader->env->DeleteLocalRef(connectionClass);
        g_classLoader->env->DeleteLocalRef(connection);
        return;
    }

    std::cout << "[DEBUG] Creating message string..." << std::endl;
    jstring jMessage = g_classLoader->env->NewStringUTF(message.c_str());
    if (!jMessage) {
        std::cerr << "[!] sendChat: Failed to create jstring" << std::endl;
        if (g_classLoader->env->ExceptionCheck()) {
            g_classLoader->env->ExceptionDescribe();
            g_classLoader->env->ExceptionClear();
        }
        g_classLoader->env->DeleteLocalRef(connectionClass);
        g_classLoader->env->DeleteLocalRef(connection);
        return;
    }

    std::cout << "[DEBUG] Calling sendChat method..." << std::endl;
    g_classLoader->env->CallVoidMethod(connection, sendChatMethod, jMessage);

    if (g_classLoader->env->ExceptionCheck()) {
        std::cerr << "[!] Exception during sendChat method call" << std::endl;
        g_classLoader->env->ExceptionDescribe();
        g_classLoader->env->ExceptionClear();
    }
    else {
        std::cout << "[DEBUG] sendChat call successful" << std::endl;
    }

    // Clean up all local references
    g_classLoader->env->DeleteLocalRef(jMessage);
    g_classLoader->env->DeleteLocalRef(connectionClass);
    g_classLoader->env->DeleteLocalRef(connection);

    std::cout << "[DEBUG] sendChat cleanup complete" << std::endl;
}