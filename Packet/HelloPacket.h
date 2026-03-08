//
// Created by rchang on 3/7/26.
//

#ifndef DEHM_SERVER_HELLOPACKET_H
#define DEHM_SERVER_HELLOPACKET_H
#include "Packet.h"

/// <summary>
/// The only packet type originating from the client that is not a ClientPacket.
/// Client will send this packet to create a connection with the server.
/// </summary>
class HelloPacket : public Packet
{
public:
    explicit HelloPacket(std::istringstream& stream);

    void serialize(std::ostringstream& stream) override;

private:
    std::string prefix() override
    {
        return "Hello";
    }

public:
    unsigned long uuid;
};


#endif //DEHM_SERVER_HELLOPACKET_H