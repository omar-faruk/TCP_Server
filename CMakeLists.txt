cmake_minimum_required(VERSION 3.8)
project(VTSTestServer)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c channel.h channel.c crypto.h crypto.c lookup.h lookup.c)

find_package(Threads)

add_executable(VTSTestServer ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(VTSTestServer pthread)