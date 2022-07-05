
project(example-clib01)

add_executable(example-clib01)

target_include_directories(example-clib01 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(example-clib01 PRIVATE CLibTest.cpp CLib.cpp)
