cmake_minimum_required(VERSION 4.2)
project(dehm_server)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(Packet)

add_executable(dehm_server
        Deadlines.h
        Packet/ClientPacket.cpp
        Packet/ClientPacket.h
        Packet/Packet.cpp
        Packet/Packet.h
        Packet/SensorsPacket.cpp
        Packet/SensorsPacket.h
        ClientCatalog.cpp
        ClientCatalog.h
        ClientData.cpp
        ClientData.h
        ClientID.cpp
        ClientID.h
        DeadlineManager.cpp
        DeadlineManager.h
        main.cpp
        ProgramArguments.cpp
        ProgramArguments.h
)
