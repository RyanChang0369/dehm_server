#include <fstream>
#include <iostream>
#include <random>
#include <bits/this_thread_sleep.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ClientData.h"
#include "DeadlineManager.h"
#include "HelloPacket.h"
#include "ProgramArguments.h"
#include "Warning.h"
using namespace std::chrono;

/// <summary>
/// Simulates a 200 kHz processor.
/// </summary>
#define CPU_PERIOD  5ms

static std::unordered_map<unsigned long, ClientData*> client_catalog;

[[noreturn]] void main_loop();

int main(const int argc, char* argv[])
{
    // Process cmd-args.
    prog_args.process_arguments(argc, argv);
    main_loop();
}

bool receive_messages(const int server_socket, const sockaddr_in server_address)
{
    const int client_fd = accept(server_socket, nullptr, nullptr);

    if (client_fd >= 0)
    {
        // Handle valid FD from the client.
        sockaddr_in client_sock{};
        socklen_t len = sizeof(client_sock);
        char buffer[65536] = {0};
        recvfrom(client_fd, buffer, sizeof(buffer), 0, (sockaddr*)&client_sock,
            &len);
        std::istringstream buffer_stream(buffer);
        const std::string client_ip = inet_ntoa(client_sock.sin_addr);

        std::cout << "New client from: " << client_ip << std::endl;

        std::string prefix;
        std::getline(buffer_stream, prefix);

        if (prefix == "Hello")
        {
            // New client; setup & respond w/ client ID.
            HelloPacket hello(buffer_stream);
            std::ostringstream hello_ss;
            hello.serialize(hello_ss);
            const auto hello_str = hello_ss.str();
            sendto(client_fd, hello_str.c_str(), hello_str.length(), 0, nullptr,
                0);
            client_catalog[hello.uuid] = new ClientData(hello.uuid);
        }
        else if (prefix == "Sensors")
        {
            SensorsPacket sensors_packet(buffer_stream);
            client_catalog[sensors_packet.get_uuid()]->update_history(
                sensors_packet);
        }
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

void write_log()
{
    auto log = json();

    for (const ClientData* client : client_catalog | std::views::values)
    {
        if (!client->history.empty())
            log[client->uuid] = client->history;
    }
    
    if (log.empty())
        return;

    const std::string json_dumped = log.dump(2);
    std::ofstream log_fh{prog_args.log_file};
    log_fh.write(json_dumped.c_str(),
        static_cast<std::streamsize>(json_dumped.length()));
}

void monitor()
{
    for (const auto& client : client_catalog | std::views::values)
    {
        Warning::generate_warning(client->history, nullptr);
    }
}

/// <summary>
/// Perform localized updates.
/// </summary>
/// <returns>True if any action was successfully performed.</returns>
bool update_things()
{
    using enum DeadlineManager::DeadlineType;
    if (DeadlineManager::singleton()->expired(monitoring))
    {
        monitor();
        DeadlineManager::singleton()->contact(monitoring);
        return true;
    }
    if (DeadlineManager::singleton()->expired(logging))
    {
        write_log();
        DeadlineManager::singleton()->contact(logging);
        return true;
    }

    return false;
}

/// <summary>
/// The main loop for the program.
/// </summary>
void main_loop()
{
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

        if (receive_messages(server_socket, server_address))
            continue;
        if (update_things())
            continue;
    }
}
