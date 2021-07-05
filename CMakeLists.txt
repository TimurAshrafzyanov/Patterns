cmake_minimum_required(VERSION 3.0)

project(Game)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(MAIN_SOURCE ${CMAKE_SOURCE_DIR}/main.cpp)

add_executable(Game ${MAIN_SOURCE})
add_subdirectory(classes)
add_subdirectory(factories)

set(ADDITIONAL_LIBRARIES Classes Factories)
target_link_libraries(Game ${ADDITIONAL_LIBRARIES})
