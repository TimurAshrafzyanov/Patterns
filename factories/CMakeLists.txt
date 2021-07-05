cmake_minimum_required(VERSION 2.8)
project(Factories)

set(
	SOURCES
	english_factory.cpp
	french_factory.cpp
)

add_library(Factories SHARED ${SOURCES})
target_link_libraries(Factories Classes)

install(TARGETS Factories
	LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
)
