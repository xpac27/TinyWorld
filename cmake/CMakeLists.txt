cmake_minimum_required (VERSION 2.8)

project (wip)

# configurations
set (EXECUTABLE_NAME "wip")

# CMake extra
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

# compiler flags
set (CMAKE_CXX_FLAGS "-Weverything -std=c++11")

# get all *.cpp files recursively
file (GLOB_RECURSE source_files ../src/*.cpp)
add_executable (${EXECUTABLE_NAME} ${source_files})

# libraries
find_package (SFML 2 REQUIRED graphics window system)
find_package (OpenGL REQUIRED)
if (SFML_FOUND AND OPENGL_FOUND)
  include_directories   (${SFML_INCLUDE_DIR})
  include_directories   (${OPENGL_INCLUDE_DIR})
  target_link_libraries (${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES})
endif()
