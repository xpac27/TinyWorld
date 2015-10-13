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
file(GLOB_RECURSE TEST_SOURCE_FILES "tests/src/*.cpp")

add_library(lib ${SOURCE_FILES})
target_include_directories(lib PUBLIC "src" "inc")
target_link_libraries(lib ${PNG_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_executable(lib_coverage ${SOURCE_FILES} ${TEST_SOURCE_FILES})
set_target_properties(lib_coverage PROPERTIES COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set_target_properties(lib_coverage PROPERTIES LINK_FLAGS "--coverage")
target_include_directories(lib_coverage PUBLIC "src" "inc" "tests/lib")
target_link_libraries(lib_coverage ${PNG_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

add_subdirectory(tests)
