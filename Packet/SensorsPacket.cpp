//
// Created by rchang on 3/4/26.
//
#include "SensorsPacket.h"

SensorsPacket::SensorsPacket(std::istringstream& stream) : ClientPacket(stream)
{
    data = nlohmann::json::parse(stream);
}

void SensorsPacket::Serialize(std::ostringstream& stream)
{
    ClientPacket::Serialize(stream);
    stream << data.dump();
}
