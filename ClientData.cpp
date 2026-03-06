//
// Created by rchang on 3/3/26.
//


#include "ClientData.h"

#include <format>


void ClientData::update_history(const std::string& buffer)
{
    std::istringstream stream{buffer};
    const SensorsPacket pkt{stream};

    this->history[system_clock::to_time_t(system_clock::now())] = pkt.
        get_data();
}
