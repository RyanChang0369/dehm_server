//
// Created by rchang on 3/5/26.
//

#ifndef DEHM_SERVER_CLIENTPACKET_H
#define DEHM_SERVER_CLIENTPACKET_H

#include "Packet.h"

/// <summary>
/// Represents a packet originating from a client. It has some information that
/// identifies the client.
/// </summary>
class ClientPacket : public Packet
{
private:
    // /// <summary>
    // /// Host name of the client.
    // /// </summary>
    // std::string hostname;
    //
    // /// <summary>
    // /// IP address of the client.
    // /// </summary>
    // std::string ip;
    //
    // /// <summary>
    // /// Mac address of the client.
    // /// </summary>
    // std::string mac;

    /// <summary>
    /// Randomly generated UUID to distinguish between clients. This is
    /// generated and stored by the server, and is stored by the client.
    /// </summary>
    long unsigned int uuid;
    
public:
    explicit ClientPacket(std::istringstream& stream);
    void serialize(std::ostringstream& stream) override;
    [[nodiscard]] long unsigned int get_uuid() const;

private:
    std::string prefix() override
    {
        return "Client";
    }
};


#endif //DEHM_SERVER_CLIENTPACKET_H