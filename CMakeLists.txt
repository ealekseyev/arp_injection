cmake_minimum_required(VERSION 3.21)
project(arp_injection)

set(CMAKE_CXX_STANDARD 14)

add_executable(arp_injection main.cpp stack/DHCPSniffer.h)
add_executable(test examples/test_arp.cpp)