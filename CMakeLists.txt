cmake_minimum_required(VERSION 3.21)
project(solidity-sourcemap-decompressor C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_C_STANDARD 99)

add_executable(sourcemap_decompressor main.c solidity_sourcemap.c solidity_sourcemap.h)
