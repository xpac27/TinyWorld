cmake_minimum_required(VERSION 2.8.10)

project(app)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(app ${SOURCE_FILES})
target_include_directories(app PUBLIC "src")
target_link_libraries(app lib ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
