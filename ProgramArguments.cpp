//
// Created by rchang on 3/6/26.
//

#include "ProgramArguments.h"

#include <iomanip>
#include <iostream>
#include <getopt.h>

static option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"port", required_argument, nullptr, 'p'},
    {"connections", required_argument, nullptr, 'c'},
    {"log", required_argument, nullptr, 'l'}, {nullptr, 0, nullptr, 0}
};

auto short_options = "hp:l:";

void option_help(const char* long_name, const char* short_name,
    const bool has_argument, const char* description)
{
    const char* spacer = has_argument ? " =  " : "    ";
    std::cout << std::setw(8) << long_name << ',' << std::setw(4) << short_name
        << spacer << description << std::endl;
}

void ProgramArguments::print_help()
{
    std::cout << "Usage: dehm-server [OPTIONS]\n" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    option_help("--help", "-h", false, "Prints this help message.");
    option_help("--port", "-p", true, "Port to listen on (default is 14050).");
    option_help("--connections", "-c", true,
        "Maximum number of connections (default is 8).");
    option_help("--log", "-l", true,
        "Location of the log file (default is 'dehm.log', in the program directory).");
}

void ProgramArguments::process_arguments(const int argc, char* argv[])
{
    while (true)
    {
        // getopt_long stores the option index here.
        int option_index = 0;

        const int c = getopt_long(argc, argv, short_options, long_options,
            &option_index);

        // Detect the end of the options.
        if (c == -1)
            break;

        // Handle options.
        switch (c)
        {
        case 'h':
            print_help();
            exit(0);
        case 'p':
            port = static_cast<int>(strtol(optarg, nullptr, 10));
            break;
        case 'c':
            connections = static_cast<int>(
                strtol(optarg, nullptr, 10));
            break;
        case 'l':
            log_file = optarg;
            break;
        default:
            break;
        }
    }
}
