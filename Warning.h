//
// Created by rchang on 3/6/26.
//

#ifndef DEHM_SERVER_WARNING_H
#define DEHM_SERVER_WARNING_H
#include <nlohmann/json.hpp>

/// <summary>
/// A warning for a monitored status. (SRS-006 - SRT-013).
/// </summary>
class Warning
{
public:
    /// <summary>
    /// Generates a number of warnings based on the status of the json data.
    /// </summary>
    /// <param name="data">The JSON data.</param>
    /// <param name="warnings">Array of warnings generated (or nullptr if no
    /// warnings present).</param>
    /// <returns>The number of warnings generated.</returns>
    static int generate_warning(const nlohmann::json& data, Warning* warnings);
};


#endif //DEHM_SERVER_WARNING_H
