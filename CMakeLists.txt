cmake_minimum_required(VERSION 3.12)

project(ChessClock)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(AddBoost)
include(cotire)

option(BUILD_TESTS "Build unit tests" ON)
option(CCLOCK_USE_KAI "Use KAI" OFF)

if (CCLOCK_USE_KAI)
	set(KAI_BUILD_TEST_ALL OFF)
	add_subdirectory(ChessClock/ThirdParty/KAI)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


include_directories(${Boost_INCLUDE_DIRS})
message(STATUS "Boost Include: ${Boost_INCLUDE_DIRS}")

set(GAMBIT_DIR ${PROJECT_SOURCE_DIR}/Gambit)
set(THIRD_PARTY ${GAMBIT_DIR}/ThirdParty)

if (WIN32)
    set(SDL_IMAGE_ROOT ${CMAKE_SOURCE_DIR}/Gambit/ThirdParty/SDL2_image-2.0.5)
    include_directories(${SDL_IMAGE_ROOT}/include)
    add_definitions(-D_WINSOCKAPI_ -DCPPHTTPLIB_OPENSSL_SUPPORT7)
endif()

include_directories(${GAMBIT_DIR}/Include)
include_directories(${THIRD_PARTY}/SDL/include)
include_directories(${THIRD_PARTY}/SDL_ttf)
include_directories(${THIRD_PARTY}/json/include)
include_directories(${THIRD_PARTY}/crossguid/include)
include_directories(${THIRD_PARTY}/harfbuzz/src)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Include)

link_directories(${THIRD_PARTY}/lib)
link_directories(${Boost_LIBRARY_DIR})

add_subdirectory(Gambit)
add_subdirectory(ChessClock)

