# SHOULD NOT BE RUN DIRECTLY

project(reports)

# configurations
set(EXECUTABLE_NAME "report")

# change compiler
set(CMAKE_CXX_COMPILER "c++-analyzer")

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Weverything \
                                -Wno-global-constructors \
                                -Wno-c++98-compat \
                                -Wno-c++98-compat-pedantic \
                                -Wno-newline-eof \
                                -Wno-padded")

# Add include directories
include_directories("../app/inc")

# get all *.cpp files recursively
file(GLOB_RECURSE source_files "../app/src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${source_files})

# link
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES})
