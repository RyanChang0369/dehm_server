//
// Created by rchang on 3/4/26.
//


#ifndef DEHM_SERVER_SENSORSPACKET_H
#define DEHM_SERVER_SENSORSPACKET_H
#include <nlohmann/json.hpp>

#include "ClientPacket.h"


class SensorsPacket : public ClientPacket
{
private:
    nlohmann::json data;

public:
    explicit SensorsPacket(std::istringstream& stream);

    void Serialize(std::ostringstream& stream) override;

    const nlohmann::json& get_data() const
    {
        return data;
    }
};


#endif //DEHM_SERVER_SENSORSPACKET_H
