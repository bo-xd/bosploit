#pragma once

#include <string>

class PacketService {
public:
    static void sendPacket(const std::string& packetClassName, const std::string& message);
};
