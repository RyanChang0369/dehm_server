//
// Created by rchang on 3/3/26.
//


#ifndef DEHM_SERVER_CLIENTDATA_H
#define DEHM_SERVER_CLIENTDATA_H

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "SensorsPacket.h"

using namespace std::chrono;
using namespace nlohmann;

/// <summary>
/// Data of a singular client.
/// </summary>
class ClientData
{
public:
    /// <summary>
    /// UUID of the client.
    /// </summary>
    unsigned long uuid;

    /// <summary>
    /// History of measurements.
    /// </summary>
    json history;

    explicit ClientData(const unsigned long uuid) :
        uuid(uuid) {}

    /// <summary>
    /// Updates the history of the log file.
    /// </summary>
    void update_history(const SensorsPacket& pkt);
};


#endif //DEHM_SERVER_CLIENTDATA_H
