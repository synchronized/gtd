
project(example-clib02)

add_executable(example-clib02)

target_include_directories(example-clib02 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(example-clib02 PRIVATE CppLibTest.cpp CppLib.cpp)
