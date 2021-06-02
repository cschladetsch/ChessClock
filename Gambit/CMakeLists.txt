cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

set(PROJECT_NAME Gambit)

project(${PROJECT_NAME})

set(THIRD_PARTY ${PROJECT_SOURCE_DIR}/ThirdParty)
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(ThirdParty/crossguid)
add_subdirectory(${THIRD_PARTY}/json)

link_directories(${THIRD_PARTY}/lib)

file(GLOB_RECURSE ALL_HEADERS
	"${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/*.hpp"
	"${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/*.h"
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

add_subdirectory(Source/Test)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf freetyped harfbuzz-subset harfbuzz nlohmann_json::nlohmann_json crossguid )
else()
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf nlohmann_json::nlohmann_json crossguid )
endif()

cotire(${PROJECT_NAME})

