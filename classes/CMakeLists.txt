cmake_minimum_required(VERSION 2.8)

project(Units)

set (
	SOURCES
	all_english_units.cpp
	all_french_units.cpp
	all_abstract_units.cpp
	squad.cpp
	army.cpp
	unit.cpp
)

add_library(Classes SHARED ${SOURCES})

install(TARGETS Classes
	LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
)
