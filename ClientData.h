//
// Created by rchang on 3/3/26.
//


#ifndef DEHM_SERVER_CLIENTDATA_H
#define DEHM_SERVER_CLIENTDATA_H

#include <chrono>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
using namespace std::chrono;
using namespace nlohmann;

/// <summary>
/// Data of a singular client.
/// </summary>
class ClientData
{
public:
    enum PeriodType : int { polling, logging, keep_alive };

private:
    /// <summary>
    /// File descriptor used to communicate with the client.
    /// </summary>
    int fd;

    /// <summary>
    /// Timestamp (of the particular PeriodType) since the time of last contact
    /// with the server.
    /// </summary>
    std::unordered_map<PeriodType, time_point<steady_clock>> last_contact;

    /// <summary>
    /// History of measurements.
    /// </summary>
    json history;

public:
    /// <summary>
    /// Creates a new ClientData class instance.
    /// </summary>
    /// <param name="fd">The file descriptor used for the ClientData.</param>
    explicit ClientData(int fd);;

    /// <summary>
    /// Update lastContact.
    /// </summary>
    void touch(PeriodType period);

    /// <summary>
    /// Retrieves the number of milliseconds since lastContact.
    /// </summary>
    /// <returns>Number of milliseconds since lastContact.</returns>
    [[nodiscard]] milliseconds since_last_contact(PeriodType period) const;

    /// <summary>
    /// Determines if the server should request information from the client.
    /// </summary>
    /// <returns>True if the polling period (SRS-001) has expired.</returns>
    [[nodiscard]] bool period_expired(PeriodType period) const;

    /// <summary>
    /// Writes the history (since the specified time period) to the log file.
    /// </summary>
    void write_log();

    /// <summary>
    /// Updates the history of the log file.
    /// </summary>
    void update_history(const std::string& buffer);
};


#endif //DEHM_SERVER_CLIENTDATA_H
