cmake_minimum_required(VERSION 2.8.10)

project(tests)
enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE source_files "src/*.cpp")

add_executable(tests ${source_files})
target_include_directories(tests PUBLIC "lib")
target_include_directories(app PUBLIC "../app/src")
target_link_libraries(tests applib)
