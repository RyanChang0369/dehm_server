//
// Created by rchang on 3/4/26.
//

#include "PacketFactory.h"

#include <stdexcept>


Packet* PacketFactory::factory(const std::string& buffer)
{
    // std::string buffer(PACKET_SIZE, '\0');
    // size_t actual_size = read(fd, &buffer[0], PACKET_SIZE);

    switch (buffer[0])
    {
    case 's':
        // SensorsPacket
        return new SensorsPacket{buffer.substr(1)};
    default:
        throw std::runtime_error("Unknown packet type");
    }
}
