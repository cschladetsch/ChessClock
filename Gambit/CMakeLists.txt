cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME Gambit)
project(${PROJECT_NAME})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(ThirdParty/crossguid)
add_subdirectory(${THIRD_PARTY}/json)

file(GLOB_RECURSE ALL_HEADERS
	"${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/*.hpp"
	"${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/*.h"
)

file(GLOB ALL_SOURCES
    "${PROJECT_SOURCE_DIR}/Source/*.cpp"
) 

add_library(${PROJECT_NAME}
    ${ALL_SOURCES}
    ${ALL_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF)

add_subdirectory(Test)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf freetyped harfbuzz-subset harfbuzz nlohmann_json::nlohmann_json crossguid )
else()
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf nlohmann_json::nlohmann_json crossguid )
endif()

cotire(${PROJECT_NAME})

