#include "ClientID.h"

/// <summary>
/// 
/// </summary>
/// <param name="ipAddress">Address of the client.</param>
/// <param name="hostname">Hostname of the client.</param>
/// <param name="uuid">Random UUID</param>
ClientID::ClientID(const char* ipAddress, const char* hostname, const char* uuid)
{
    this->ipAddress = ipAddress;
    this->hostname = hostname;
    this->uuid = uuid;
}
