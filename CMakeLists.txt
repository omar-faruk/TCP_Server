cmake_minimum_required(VERSION 3.8)
project(VTSTestServer)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)

find_package(Threads)

add_executable(VTSTestServer ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(VTSTestServer pthread)