# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_DIR "headers")
set(SOURCE_DIR "src")

project ("Omaha-Hi-Lo")

# Include sub-projects.
add_subdirectory ("OmahaComp")
add_subdirectory ("OmahaTest")