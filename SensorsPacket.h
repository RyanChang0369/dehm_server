//
// Created by rchang on 3/4/26.
//



#ifndef DEHM_SERVER_SENSORSPACKET_H
#define DEHM_SERVER_SENSORSPACKET_H
#include <nlohmann/json.hpp>
#include "Packet.h"


class SensorsPacket : public Packet
{
private:
    nlohmann::json data;

public:
    explicit SensorsPacket(const std::string& buffer);

    std::string Serialize() override;
};


#endif //DEHM_SERVER_SENSORSPACKET_H
