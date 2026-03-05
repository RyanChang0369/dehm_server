//
// Created by rchang on 3/3/26.
//

#include "ClientData.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "ProgArgs.h"

constexpr milliseconds period_duration(const ClientData::PeriodType period)
{
    switch (period)
    {
    case ClientData::polling:
        // The period for polling information (SRS-001).
        return 20ms;
    case ClientData::logging:
        // The period for logging (SRS-016).
        return 50ms;
    case ClientData::keep_alive:
        // The period after which the connection to the client is killed.
        return 500ms;
    default:
        throw std::logic_error("Unknown period type");
    }
}

ClientData::ClientData(const int fd) : fd(fd)
{
    this->last_contact = {};
}

void ClientData::touch(const PeriodType period)
{
    this->last_contact[period] = steady_clock::now();

    // Always update keep_alive
    if (period != keep_alive)
        this->touch(keep_alive);
}

milliseconds ClientData::since_last_contact(const PeriodType period) const
{
    return duration_cast<milliseconds>(
        steady_clock::now() - this->last_contact.at(period));
}

bool ClientData::period_expired(const PeriodType period) const
{
    return this->last_contact.contains(period)
        ? this->since_last_contact(period) > period_duration(period)
        : true;
}

void ClientData::write_log()
{
    const std::string json_dumped = this->history.dump(2);
    std::ofstream log_fh{prog_args.log_file};
    log_fh.write(json_dumped.c_str(), json_dumped.length());
    
    this->touch(logging);
}

void ClientData::update_history(const std::string& buffer)
{
    auto json = json::parse(buffer.substr(1));
    
    this->history[std::format("{}", system_clock::now())] = json;
    // return std::format("s{}", this->data.dump());
}
