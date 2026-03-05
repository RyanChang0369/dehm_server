//
// Created by rchang on 3/4/26.
//
#include "SensorsPacket.h"

SensorsPacket::SensorsPacket(const std::string& buffer) : Packet(buffer)
{
    this->data = nlohmann::json::parse(buffer);
}

std::string SensorsPacket::Serialize()
{
    return std::format("s{}", this->data.dump());
}
