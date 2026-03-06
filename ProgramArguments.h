//
// Created by rchang on 3/6/26.
//

#ifndef DEHM_SERVER_PROGRAMARGUMENTS_H
#define DEHM_SERVER_PROGRAMARGUMENTS_H
#include <string>

/// <summary>
/// Defines the program arguments for the program.
/// </summary>
class ProgramArguments
{
public:
    int port = 14050;
    int connections = 8;
    std::string log_file = "dehm_log.json";

    /// <summary>
    /// Process command line arguments (from the main() function).
    /// </summary>
    /// <param name="argc">Number of arguments.</param>
    /// <param name="argv">The program arguments.</param>
    void process_arguments(int argc, char* argv[]);
    
private:
    /// <summary>
    /// Prints a help message to stdout.
    /// </summary>
    static void print_help();
};

/// <summary>
/// Static instance of the ProgramArguments object.
/// </summary>
static ProgramArguments prog_args;

#endif //DEHM_SERVER_PROGRAMARGUMENTS_H
