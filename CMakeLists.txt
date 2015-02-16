cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/build/modules")

# OPENGL
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
else()
  message(FATAL_ERROR "Cannot find OpenGL library.")
endif()

# SFML
find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
else()
  message(FATAL_ERROR "Cannot find SFML library.")
endif()

add_subdirectory(app)
add_subdirectory(tests)
add_subdirectory(reports)
