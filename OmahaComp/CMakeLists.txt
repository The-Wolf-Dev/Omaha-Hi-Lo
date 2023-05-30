# CMakeList.txt : CMake project for OmahaComp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories(${HEADER_DIR})
set(PROJECT_SOURCE_FILES ${SOURCE_DIR}/Card.cpp
				${SOURCE_DIR}/Hand.cpp
				${SOURCE_DIR}/Board.cpp
				${SOURCE_DIR}/Poker.cpp
				)

add_library(OmahaCompLib STATIC ${PROJECT_SOURCE_FILES})

target_include_directories(OmahaCompLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_DIR})

# Add source to this project's executable.
add_executable (OmahaComp ${SOURCE_DIR}/main.cpp)

target_link_libraries(OmahaComp OmahaCompLib)