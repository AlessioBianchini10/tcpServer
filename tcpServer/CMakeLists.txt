cmake_minimum_required(VERSION 3.13)
project(tcpServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(tcpServer main.cpp PracticalSocket.cpp PracticalSocket.h)

SET(CMAKE_CXX_FLAGS -pthread)