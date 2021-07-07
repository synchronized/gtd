# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# aux_source_directory(. DIR_SRCS)

include_directories(".")

project (virtualfunc)
add_executable(virtualfunc virtualfunc.cpp)

