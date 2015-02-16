# SHOULD NOT BE RUN DIRECTLY

project(tests)

enable_testing()

# configurations
set(EXECUTABLE_NAME "tests")

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11")

# add .cpp file
add_executable(${EXECUTABLE_NAME} "src/test_project1.cpp")

# GTest
add_subdirectory("lib/googletest")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# link
target_link_libraries(${EXECUTABLE_NAME} gtest gtest_main)
