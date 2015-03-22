# SHOULD NOT BE RUN DIRECTLY

project(reports)

# configurations
set(EXECUTABLE_NAME "report")

# change compiler
set(CMAKE_CXX_COMPILER "c++-analyzer")

# Add include directories
include_directories("../app/src")

# get all *.cpp files recursively
file(GLOB_RECURSE source_files "../app/src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${source_files})

# link
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES})
