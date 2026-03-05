//
// Created by rchang on 3/4/26.
//



#ifndef DEHM_SERVER_SENSORSFACTORY_H
#define DEHM_SERVER_SENSORSFACTORY_H
#include "Packet.h"
#include "SensorsPacket.h"

class PacketFactory
{
public:
    static Packet* factory(const std::string& buffer);
};

#endif //DEHM_SERVER_SENSORSFACTORY_H
