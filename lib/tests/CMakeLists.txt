cmake_minimum_required(VERSION 2.8.10)

project(tests)
enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(tests ${SOURCE_FILES})
target_include_directories(tests PUBLIC "lib" "../src" "../inc")
target_link_libraries(tests lib)
