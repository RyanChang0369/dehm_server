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
    /// <summary>
    /// Defines the specific prefix for this packet.
    /// </summary>
    /// <returns>The generated prefix</returns>
    virtual std::string prefix() = 0;

public:
    virtual ~Packet() = default;

    /// <summary>
    /// Decodes a line.
    /// </summary>
    /// <param name="stream">The stream to decode.</param>
    /// <returns>A decoded line.</returns>
    static std::string decode(std::istringstream& stream);

    explicit Packet(std::istringstream& stream);

    /// <summary>
    /// Encodes a line.
    /// </summary>
    /// <param name="line">The line to encode.</param>
    /// <param name="stream">The string stream.</param>
    static void encode(const std::string& line, std::ostringstream& stream);

    /// <summary>
    /// Serializes the packet into a character string.
    /// </summary>
    /// <param name="stream">The serialized stream.</param>
    virtual void serialize(std::ostringstream& stream);
};


#endif //DEHM_SERVER_PACKET_H
