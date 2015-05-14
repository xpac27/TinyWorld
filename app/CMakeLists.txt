cmake_minimum_required(VERSION 2.8.10)

project(app)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)
find_package(PNG REQUIRED)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(app ${SOURCE_FILES})
add_library(applib ${SOURCE_FILES})
target_include_directories(app PUBLIC "src")
target_include_directories(applib PUBLIC "src")
target_link_libraries(app ${PNG_LIBRARIES} ${GLM_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
target_link_libraries(applib ${PNG_LIBRARIES} ${GLM_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
