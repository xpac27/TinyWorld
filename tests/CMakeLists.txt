# SHOULD NOT BE RUN DIRECTLY

project(tests)

enable_testing()

# configurations
set(EXECUTABLE_NAME "tests")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11")

# libs
include_directories("lib")

file(GLOB_RECURSE source_files "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${source_files})
