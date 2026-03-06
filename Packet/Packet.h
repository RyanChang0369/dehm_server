//
// Created by rchang on 3/4/26.
//


#ifndef DEHM_SERVER_PACKET_H
#define DEHM_SERVER_PACKET_H
#include <sstream>

/// <summary>
/// A packet/datagram that is responsible for parsing/formatting communications
/// for client/server.
/// </summary>
class Packet
{
private:
    /// <summary>
    /// Each packet has a one-character prefix that allows us to distinguish
    /// between different packet types.
    /// </summary>
    char prefix;

public:
    explicit Packet(std::istringstream& stream);

    /// <summary>
    /// Serializes the packet into a character string.
    /// </summary>
    /// <returns>The serialized string.</returns>
    virtual void serialize(std::ostringstream& stream);
};


#endif //DEHM_SERVER_PACKET_H
