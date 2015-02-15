# SHOULD NOT BE RUN DIRECTLY

project(app)

# configurations
set(EXECUTABLE_NAME "app")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Weverything \
                                -Wno-c++98-compat \
                                -Wno-c++98-compat-pedantic \
                                -Wno-newline-eof \
                                -Wno-padded")

# get all *.cpp files recursively
file(GLOB_RECURSE source_files "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${source_files})

# link
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES})
