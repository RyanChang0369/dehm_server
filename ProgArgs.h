//
// Created by rchang on 3/4/26.
//

#ifndef DEHM_SERVER_PROGARGS_H
#define DEHM_SERVER_PROGARGS_H
#include <string>

struct ProgArgs
{
    int port = 14050;
    int connections = 8;
    std::string log_file = "dehm_log.json";
};
static ProgArgs prog_args;

#endif //DEHM_SERVER_PROGARGS_H