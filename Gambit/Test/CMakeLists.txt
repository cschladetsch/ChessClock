cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

set(PROJECT_NAME GambitTest)

project(${PROJECT_NAME})

file(GLOB TEST_SOURCES "*.cpp") 

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${ALL_HEADERS})
cotire(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf freetyped harfbuzz-subset harfbuzz nlohmann_json::nlohmann_json crossguid )
else()
    target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_ttf nlohmann_json::nlohmann_json crossguid )
endif()


