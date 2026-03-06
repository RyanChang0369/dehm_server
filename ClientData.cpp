//
// Created by rchang on 3/3/26.
//


#include "ClientData.h"

#include <chrono>
#include <format>


void ClientData::update_history(const std::string& buffer)
{
    std::istringstream stream{buffer};
    const SensorsPacket pkt{stream};

    const auto& curr_time = std::format("{0:%F}T{0:%T}",
        round<seconds>(system_clock::now()));
    const auto& data = pkt.get_data();
    history[curr_time] = data;
}
