cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME cclock)

project(${PROJECT_NAME})

set(THIRD_PARTY ${PROJECT_SOURCE_DIR}/ThirdParty)
set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Include")
message(STATUS "*** Include: " ${PROJECT_INCLUDE_DIR})

link_directories(${THIRD_PARTY}/SDL/build/Debug)

file(GLOB ALL_HEADERS
        "${PROJECT_INCLUDE_DIR}/ChessClock/*.hpp"
        "${PROJECT_INCLUDE_DIR}/ChessClock/*.h"
)

file(GLOB ALL_SOURCES
        "${PROJECT_SOURCE_DIR}/Source/*.cpp"
) 

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})
include_directories(${THIRD_PARTY}/SDL/include)
include_directories(${PROJECT_INCLUDE_DIR})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2d SDL2maind)
else()
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)
endif()

