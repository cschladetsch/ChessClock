cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

set(PROJECT_NAME cclock)

project(${PROJECT_NAME})

set(THIRD_PARTY ${PROJECT_SOURCE_DIR}/ThirdParty)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(ThirdParty/crossguid)

link_directories(${THIRD_PARTY}/lib)

file(GLOB_RECURSE ALL_HEADERS
        "${PROJECT_INCLUDE_DIR}/ChessClock/*.hpp"
        "${PROJECT_INCLUDE_DIR}/ChessClock/*.h"
)

file(GLOB ALL_SOURCES
        "${PROJECT_SOURCE_DIR}/Source/*.cpp"
) 

add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF)

include_directories(${THIRD_PARTY}/SDL/include)
include_directories(${THIRD_PARTY}/SDL_ttf)
include_directories(${THIRD_PARTY}/json/include)
include_directories(${THIRD_PARTY}/crossguid/include)
include_directories(${THIRD_PARTY}/harfbuzz/src)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Include)

add_subdirectory(${THIRD_PARTY}/json)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf freetyped harfbuzz-subset harfbuzz nlohmann_json::nlohmann_json crossguid )
else()
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main crossguid)
endif()

cotire(${PROJECT_NAME})



