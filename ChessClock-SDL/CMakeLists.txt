cmake_minimum_required(VERSION 3.12)

project(main)

set(THIRD_PARTY ${PROJECT_SOURCE_DIR}/ThirdParty)

include_directories(${THIRD_PARTY}/SDL/include)
link_directories(${THIRD_PARTY}/SDL/build/Debug)

aux_source_directory(Source SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)

