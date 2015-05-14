cmake_minimum_required(VERSION 2.8.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions( "-Weverything" )
    add_definitions( "-Wno-c++98-compat" )
    add_definitions( "-Wno-c++98-compat-pedantic" )
    add_definitions( "-Wno-newline-eof" )
    add_definitions( "-Wno-padded" )
    add_definitions( "-Wno-exit-time-destructors" )
endif()
add_definitions( "-std=c++11" )

add_subdirectory(app)
add_subdirectory(tests)
