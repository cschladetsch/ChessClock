cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME ChessClock)
project(${PROJECT_NAME})

include_directories(Include/)

file(GLOB_RECURSE ALL_SOURCES Source/*.cpp)
file(GLOB_RECURSE ALL_HEADERS Include/*.hpp)

include_directories(ThirdParty/KAI/Include)
include_directories(${Boost_INCLUDE_DIRS})
 
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

set(KAI_LIBS Executor Core PiLang RhoLang ${Boost_LIBRARIES})

if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        Gambit
        ${SDL_IMAGE_ROOT}/lib/x64/SDL2_image.lib
		${KAI_LIBS}
        )
else()
    target_link_libraries(${PROJECT_NAME}
        Gambit
        SDL2_image
		${KAI_LIBS}
    )
endif()

set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
file(GLOB_RECURSE ALL_RESOURCES "${RESOURCES_DIR}/*")

source_group(TREE ${RESOURCES_DIR} PREFIX Resources FILES ${ALL_RESOURCES})

