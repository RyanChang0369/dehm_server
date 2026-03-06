#include <fstream>
#include <iostream>
#include <random>
#include <bits/this_thread_sleep.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "ClientCatalog.h"
#include "DeadlineManager.h"
#include "ProgramArguments.h"
using namespace std::chrono;

/// <summary>
/// Simulates a 200 kHz processor.
/// </summary>
#define CPU_PERIOD  5ms

[[noreturn]] void main_loop();

int main(const int argc, char* argv[])
{
    // Process cmd-args.
    prog_args.process_arguments(argc, argv);
    main_loop();
}

bool receive_messages(std::unordered_map<int, ClientData*>& catalog,
    const int server_socket, const sockaddr_in server_address)
{
    const int client_fd = accept(server_socket, nullptr, nullptr);

    if (client_fd >= 0)
    {
        // Handle valid FD from the client.
        // TODO: Receive messages
        sockaddr_in client_sock{};
        socklen_t len = sizeof(client_sock);
        char buffer[65536] = {0};
        recvfrom(client_fd, buffer, sizeof(buffer), 0,
            reinterpret_cast<sockaddr*>(&client_sock), &len);
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

void write_log(const std::unordered_map<int, ClientData*>& catalog)
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
    log_fh.write(json_dumped.c_str(),
        static_cast<std::streamsize>(json_dumped.length()));
}

/// <summary>
/// Perform localized updates.
/// </summary>
/// <param name="catalog">The client catalog.</param>
/// <returns>True if any action was successfully performed.</returns>
bool update_things(const std::unordered_map<int, ClientData*>& catalog)
{
    if (DeadlineManager::singleton()->expired(
        DeadlineManager::DeadlineType::logging))
    {
        write_log(catalog);

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
    const int server_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK,
        IPPROTO_TCP);

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
        if (update_things(catalog))
            continue;
    }
}
