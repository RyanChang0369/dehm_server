//
// Created by rchang on 3/4/26.
//

#include "Packet.h"

Packet::Packet(std::istringstream& stream)
{
    prefix = static_cast<char>(stream.get());
}

void Packet::serialize(std::ostringstream& stream)
{
    stream << prefix;
}
