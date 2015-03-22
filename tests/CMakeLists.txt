# SHOULD NOT BE RUN DIRECTLY

project(tests)

enable_testing()

# configurations
set(EXECUTABLE_NAME "tests")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# lest options
add_definitions(-Dlest_FEATURE_AUTO_REGISTER=1)
add_definitions(-Dlest_FEATURE_COLOURISE=1)

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11")

# libs
include_directories("lib")
include_directories("../app/src")

# get all *.cpp files recursively
file(GLOB_RECURSE source_files "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${source_files})

# link
target_link_libraries(${EXECUTABLE_NAME} "wip")
