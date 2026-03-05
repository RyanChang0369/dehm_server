//
// Created by rchang on 3/4/26.
//



#ifndef DEHM_SERVER_PACKET_H
#define DEHM_SERVER_PACKET_H
#include <string>

/// <summary>
/// A packet/datagram that is responsible for parsing/formatting communications
/// for client/server.
/// </summary>
class Packet
{
public:
    explicit Packet(const std::string& buffer);

    /// <summary>
    /// Serializes the packet into a character string.
    /// </summary>
    /// <returns>The serialized string.</returns>
    virtual std::string Serialize() = 0;
};


#endif //DEHM_SERVER_PACKET_H
