cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME CClock)
project(${PROJECT_NAME})

include_directories(Include/)

file(GLOB_RECURSE SOURCE_FILES Source/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES Include/*.hpp)

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${INCLUDE_FILES}
        )
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        )


add_subdirectory(Test)

link_directories(/usr/lib/arm-linux-gnueabihf)

if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        Gambit
        ${SDL_IMAGE_ROOT}/lib/x64/SDL2_image.lib
        )
else()
    target_link_libraries(${PROJECT_NAME}
        Gambit
        SDL_image
    )
endif()

