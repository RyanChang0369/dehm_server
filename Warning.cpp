//
// Created by rchang on 3/6/26.
//

#include "Warning.h"

int Warning::generate_warning(const nlohmann::json& data, Warning* warnings)
{
    for (const auto& datapoint : data.items())
    {
        const auto time = datapoint.key();
        const auto value = datapoint.value();

        for (const auto& metric : value.items())
        {
            const auto metric_name = metric.key();
            const auto metric_value = metric.value();
        }
    }
    return -1;
}
