# SHOULD NOT BE RUN DIRECTLY

project(app)

# configurations
set(EXECUTABLE_NAME "app")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Add include directories
include_directories("src")

# get all *.cpp files recursively
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Add the library
add_library("TinyWorld" ${SOURCE_FILES})

# link
target_link_libraries(${EXECUTABLE_NAME} ${PNG_LIBRARIES} ${GLM_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
