//
// Created by rchang on 3/3/26.
//


#include "ClientData.h"

#include <format>


void ClientData::update_history(const std::string& buffer)
{
    std::istringstream stream{buffer};
    const SensorsPacket pkt{stream};

    const auto& curr_time = std::format("{}",
        system_clock::to_time_t(system_clock::now()));
    const auto& data = pkt.get_data();
    history[curr_time] = data;
}
