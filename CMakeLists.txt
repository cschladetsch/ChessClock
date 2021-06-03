cmake_minimum_required(VERSION 3.12)

project(ChessClock)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

set(GAMBIT_DIR ${PROJECT_SOURCE_DIR}/Gambit)
set(THIRD_PARTY ${GAMBIT_DIR}/ThirdParty)

include_directories(${GAMBIT_DIR}/Include)
include_directories(${THIRD_PARTY}/SDL/include)
include_directories(${THIRD_PARTY}/SDL_ttf)
include_directories(${THIRD_PARTY}/json/include)
include_directories(${THIRD_PARTY}/crossguid/include)
include_directories(${THIRD_PARTY}/harfbuzz/src)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Include)

link_directories(${THIRD_PARTY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(Gambit)
add_subdirectory(ChessClock)
