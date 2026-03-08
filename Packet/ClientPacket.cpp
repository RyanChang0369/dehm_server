//
// Created by rchang on 3/5/26.
//

#include "ClientPacket.h"

#include <iomanip>

#define UUID_HEX_SIZE 16

ClientPacket::ClientPacket(std::istringstream& stream) : Packet(stream)
{
    char buffer[UUID_HEX_SIZE];
    stream.read(buffer, sizeof(buffer));
    // Convert hex string to long. 
    this->uuid = strtoul(buffer, nullptr, UUID_HEX_SIZE);
}

void ClientPacket::serialize(std::ostringstream& stream)
{
    Packet::serialize(stream);
    stream << std::setfill('0') << std::setw(UUID_HEX_SIZE) << std::hex << this
        ->uuid << std::endl;
}

long unsigned int ClientPacket::get_uuid() const
{
    return uuid;
}
