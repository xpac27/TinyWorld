cmake_minimum_required(VERSION 2.8.10)

project(tests)
enable_testing()
add_definitions(-Dlest_FEATURE_AUTO_REGISTER=1)
add_definitions(-Dlest_FEATURE_COLOURISE=1)

file(GLOB_RECURSE source_files "src/*.cpp")

add_executable(tests ${source_files})
target_include_directories(tests PUBLIC "lib")
target_link_libraries(tests applib)
