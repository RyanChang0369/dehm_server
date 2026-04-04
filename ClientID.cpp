#include "ClientID.h"

/// <summary>
/// 
/// </summary>
/// <param name="ip_address">Address of the client.</param>
/// <param name="hostname">Hostname of the client.</param>
/// <param name="uuid">Random UUID</param>
ClientID::ClientID(const char* ip_address, const char* hostname, const char* uuid)
{
    this->ipAddress = ip_address;
    this->hostname = hostname;
    this->uuid = uuid;
}
