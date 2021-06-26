cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME CClock)
project(${PROJECT_NAME})

include_directories(Include/)

file(GLOB_RECURSE ALL_SOURCES Source/*.cpp)
file(GLOB_RECURSE ALL_HEADERS Include/*.hpp)

add_executable(${PROJECT_NAME}
    ${ALL_SOURCES}
    ${ALL_HEADERS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

cotire(${PROJECT_NAME})

if (BUILD_TESTS)
    add_subdirectory(Test)
endif()

link_directories(/usr/lib/arm-linux-gnueabihf)

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


set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
file(GLOB_RECURSE ALL_RESOURCES "${RESOURCES_DIR}/*")

source_group(TREE ${RESOURCES_DIR} PREFIX Resources FILES ${ALL_RESOURCES})
