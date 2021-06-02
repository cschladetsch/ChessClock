cmake_minimum_required(VERSION 3.12)

project(ChessClock)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

add_subdirectory(Gambit)
add_subdirectory(ChessClock)


