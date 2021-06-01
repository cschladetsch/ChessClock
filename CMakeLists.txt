cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Gambit/CMake")
include(cotire)

add_subdirectory(Gambit)
add_subdirectory(ChessClock)
