//
// Created by rchang on 3/3/26.
//



#ifndef DEHM_SERVER_CLIENTCATALOG_H
#define DEHM_SERVER_CLIENTCATALOG_H
#include <unordered_map>

#include "ClientData.h"

/// <summary>
/// Catalog of client information.
/// </summary>
class ClientCatalog
{
    public:
    /// <summary>
    /// Catalog of ClientData.
    /// </summary>
    std::unordered_map<int, ClientData> catalog;
    
    ClientCatalog();
};


#endif //DEHM_SERVER_CLIENTCATALOG_H