//
// Created by rchang on 3/7/26.
//

#include "HelloPacket.h"

#include "RNG.h"

HelloPacket::HelloPacket(std::istringstream& stream) : Packet(stream)
{
    uuid = RNG::get();
}

void HelloPacket::serialize(std::ostringstream& stream)
{
    Packet::serialize(stream);
    stream << uuid << std::endl;
}
