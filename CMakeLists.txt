cmake_minimum_required(VERSION 4.2)
project(dehm_server)

set(CMAKE_CXX_STANDARD 23)

add_executable(dehm_server main.cpp
        ClientID.h
        ClientID.cpp
        ClientCatalog.cpp
        ClientCatalog.h
        ClientData.cpp
        ClientData.h
        Packet.cpp
        Packet.h
        SensorsPacket.cpp
        SensorsPacket.h
        PacketFactory.cpp
        PacketFactory.h
        ProgArgs.h)
