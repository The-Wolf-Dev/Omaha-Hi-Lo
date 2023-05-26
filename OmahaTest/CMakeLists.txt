# CMakeList.txt : CMake project for OmahaTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR "Source Files")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++14")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add source to this project's executable.
add_executable (OmahaTest ${SOURCE_DIR}/OmahaTest.cpp ${SOURCE_DIR}/CardTest.cpp)

enable_testing()

target_link_libraries(
  OmahaTest
  GTest::gtest_main
  OmahaCompLib
)

include(GoogleTest)
gtest_discover_tests(OmahaTest)

#install(TARGETS OmahaTest LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})