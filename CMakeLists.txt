cmake_minimum_required(VERSION 3.27)
project(task2)

set(CMAKE_CXX_STANDARD 14)

add_executable(task2
        main.cpp
        Account.h
        Account.cpp
        PhysicalClient.cpp
        PhysicalClient.h
        JurClient.cpp
        Client.cpp
        Bank.cpp
        SberBank.h
        GazpromBank.h
        Client.h
        JurClient.h
        Bank.h
)
