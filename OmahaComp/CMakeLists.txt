# CMakeList.txt : CMake project for OmahaComp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(SOURCE_DIR "Source Files")
set(HEADER_DIR "Header Files")

include_directories("Header Files")
file(GLOB sources ${SOURCE_DIR}/Card.cpp
				${SOURCE_DIR}/Hand.cpp
				${SOURCE_DIR}/Board.cpp
				${SOURCE_DIR}/Poker.cpp
				)

add_library(OmahaCompLib STATIC ${sources})

target_include_directories(OmahaCompLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_DIR})

# Add source to this project's executable.
add_executable (OmahaComp ${SOURCE_DIR}/main.cpp
	${HEADER_DIR}/Poker.h ${SOURCE_DIR}/Poker.cpp
	${HEADER_DIR}/Card.h ${SOURCE_DIR}/Card.cpp
	${HEADER_DIR}/Hand.h ${SOURCE_DIR}/Hand.cpp
	${HEADER_DIR}/Board.h ${SOURCE_DIR}/Board.cpp
	${HEADER_DIR}/Enums.h
	)