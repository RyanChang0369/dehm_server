#include <cstring>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <random>
#include <bits/this_thread_sleep.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "ClientCatalog.h"
#include "DeadlineManager.h"
#include "ProgArgs.h"
using namespace std::chrono;

constexpr unsigned char REQUEST_SENSORS = 'r';

/// <summary>
/// Simulates a 200 kHz processor.
/// </summary>
#define CPU_PERIOD  5ms

static option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"port", required_argument, nullptr, 'p'},
    {"connections", required_argument, nullptr, 'c'},
    {"log", required_argument, nullptr, 'l'},
    {nullptr, 0, nullptr, 0}
};

const char* short_options = "hp:l:";

void print_help()
{
    const auto spacer = "    ";
    const auto spacer_eq = " =  ";
    std::cout << "Usage: dehm-server [OPTIONS]\n" << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << std::setw(8) << "--help," << std::setw(4) << "-h" << spacer <<
        "Prints this help message." << std::endl;
    std::cout << std::setw(8) << "--port," << std::setw(4) << "-p" << spacer_eq
        << "Port to listen on (default is 14050)." << std::endl;
    std::cout << std::setw(8) << "--connections," << std::setw(4) << "-c" <<
        spacer_eq << "Maximum number of connections (default is 8)." <<
        std::endl;
    std::cout << std::setw(8) << "--log," << std::setw(4) << "-l" << spacer_eq
        << "Location of the log file (default is 'dehm.log', in the program directory)."
        << std::endl;
}

[[noreturn]] void main_loop();

int main(const int argc, char* argv[])
{
    // Process cmd-args.
    while (true)
    {
        // getopt_long stores the option index here.
        int option_index = 0;

        const int c = getopt_long(
            argc,
            argv,
            short_options,
            long_options,
            &option_index
        );

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
            prog_args.port = static_cast<int>(strtol(optarg, nullptr, 10));
            break;
        case 'c':
            prog_args.connections = static_cast<int>(strtol(
                optarg,
                nullptr,
                10
            ));
            break;
        case 'l':
            prog_args.log_file = optarg;
            break;
        default:
            break;
        }
    }

    main_loop();
}

bool receive_messages(
    std::unordered_map<int, ClientData*>& catalog,
    const int server_socket,
    const sockaddr_in server_address
)
{
    const int client_fd = accept(server_socket, nullptr, nullptr);

    if (client_fd >= 0)
    {
        // Handle valid FD from the client.
        // TODO: Receive messages
        sockaddr_in client_sock{};
        socklen_t len = sizeof(client_sock);
        char buffer[65536] = {0};
        recvfrom(
            client_fd,
            buffer,
            sizeof(buffer),
            0,
            reinterpret_cast<sockaddr*>(&client_sock),
            &len
        );
        std::istringstream buffer_stream(buffer);
        // const std::string client_ip = inet_ntoa(client_sock.sin_addr);

        ClientData* client_data;
        if (!catalog.contains(client_fd))
        {
            // New client; setup.
            client_data = new ClientData(ClientPacket{buffer_stream});
            catalog[client_fd] = client_data;
        }
        else
        {
            client_data = catalog.at(client_fd);
        }

        client_data->update_history(buffer);
        return true;
    }
    else if (errno == EWOULDBLOCK)
    {
        // No messages available.
        // TODO: 
        return false;
    }
    else
    {
        // Some other error.
        std::cerr << "Server had error accessing on " << server_address.sin_addr
            .s_addr << ":" << server_socket << std::endl;
        return false;
    }
}

bool update_things(
    const std::unordered_map<int, ClientData*>& catalog,
    const int server_socket,
    sockaddr_in server_address
)
{
    if (DeadlineManager::singleton()->expired(
        DeadlineManager::DeadlineType::logging
    ))
    {
        json log;

        for (const auto& client : catalog | std::views::values)
        {
            std::ostringstream id_stream;
            client->id.Serialize(id_stream);
            log[id_stream.str()] = client->history;
        }

        const std::string json_dumped = log.dump(2);
        std::ofstream log_fh{prog_args.log_file};
        log_fh.write(
            json_dumped.c_str(),
            static_cast<std::streamsize>(json_dumped.length())
        );

        return true;
    }

    return false;
}

/// <summary>
/// The main loop for the program.
/// </summary>
void main_loop()
{
    std::unordered_map<int, ClientData*> catalog{};

    // Create server socket (TCP).
    const int server_socket = socket(
        AF_INET,
        SOCK_STREAM | SOCK_NONBLOCK,
        IPPROTO_TCP
    );

    // Define server address (default is 14050).
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(prog_args.port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    const auto server_sockaddr = reinterpret_cast<sockaddr*>(&server_address);

    // Bind socket & listen for connections.
    int status = bind(server_socket, server_sockaddr, sizeof(server_address));

    if (status < 0)
        throw std::runtime_error("Failed to bind socket.");

    status = listen(server_socket, prog_args.connections);

    if (status < 0)
        throw std::runtime_error("Failed to listen to socket.");

    while (true)
    {
        // This is the main loop that simulates a RTOS. The thread will sleep
        // for CPU_PERIOD (5ms), after which the system will perform one action
        // for one client (simulating a cheap single-threaded microprocessor).
        std::this_thread::sleep_for(CPU_PERIOD);

        if (receive_messages(catalog, server_socket, server_address))
            continue;
        if (update_things(catalog, server_socket, server_address))
            continue;
    }
}
