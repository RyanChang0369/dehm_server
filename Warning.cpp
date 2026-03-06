//
// Created by rchang on 3/6/26.
//

#include "Warning.h"

int Warning::generate_warning(const nlohmann::json& data, Warning* warnings)
{
    for (auto elem : data)
    {
        elem.type();
    }
    return -1;
}
