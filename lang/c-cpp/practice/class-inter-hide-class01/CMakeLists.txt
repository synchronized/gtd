
project(class-inter-hide-class01)

add_executable(class-inter-hide-class01)

target_include_directories(class-inter-hide-class01 PRIVATE "$CMAKE_CURRENT_SOURCE_DIR")
target_sources(class-inter-hide-class01 PRIVATE main.cpp Handle.cpp)
