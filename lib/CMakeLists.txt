cmake_minimum_required(VERSION 2.8.10)

project(app)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(PNG REQUIRED)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_library(lib ${SOURCE_FILES})
target_include_directories(lib PUBLIC "src" "inc")
target_link_libraries(lib ${PNG_LIBRARIES} ${GLM_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_subdirectory(tests)
