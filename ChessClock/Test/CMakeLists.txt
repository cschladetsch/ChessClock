cmake_minimum_required(VERSION 3.12)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

set(PROJECT_NAME ChessClockTest)

project(${PROJECT_NAME})

file(GLOB TEST_SOURCES
    "*.cpp"
) 

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${ALL_HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF)

if (WIN32)
	target_link_libraries(${PROJECT_NAME}
		Gambit
		${SDL_IMAGE_ROOT}/lib/x64/SDL2_image.lib
		)
else()
	target_link_libraries(${PROJECT_NAME}
		Gambit
		SDL2_image
		)
endif()

cotire(${PROJECT_NAME})

