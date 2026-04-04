//
// Created by rchang on 3/3/26.
//

#ifndef DEHM_SERVER_CLIENTID_H
#define DEHM_SERVER_CLIENTID_H
#include <string>

/// <summary>
/// Represents an unique ID for a particular client.
/// </summary>
struct ClientID
{
    /// <summary>
    /// IP address of the client (only IPV4 for now).
    /// </summary>
    std::string ipAddress;

    /// <summary>
    /// Host name of the client.
    /// </summary>
    std::string hostname;

    /// <summary>
    /// Random uuid for the client.
    /// </summary>
    std::string uuid;
    
    ClientID(const char* ip_address, const char* hostname, const char* uuid);
};


#endif //DEHM_SERVER_CLIENTID_H