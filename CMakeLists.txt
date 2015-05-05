cmake_minimum_required(VERSION 2.8.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find OpenGL library.")
endif()

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find GLEW library.")
endif()

find_package(GLFW REQUIRED)
if(GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find GLFW library.")
endif()

find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find GLM library.")
endif()

find_package(PNG REQUIRED)
if(GLM_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find GLM library.")
endif()

# compiler flags
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++11 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-exit-time-destructors")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

add_subdirectory(app)
add_subdirectory(tests)
add_subdirectory(reports)
