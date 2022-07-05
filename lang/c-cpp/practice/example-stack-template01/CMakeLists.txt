
project(example-template-stack01)

add_executable(example-template-stack01)

target_include_directories(example-template-stack01 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(example-template-stack01 PRIVATE main.cpp Video.cpp)
