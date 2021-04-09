# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# aux_source_directory(. DIR_SRCS)

include_directories(".")

# 项目信息
project (sharedptr1)
# 指定生成目标
add_executable(sharedptr1 sharedptr1.cpp)

# 项目信息
project (sharedptr2)
# 指定生成目标
add_executable(sharedptr2 sharedptr2.cpp)

# 项目信息
project (sharedptr3)
# 指定生成目标
add_executable(sharedptr3 sharedptr3.cpp)

# 项目信息
project (sharedptr4)
# 指定生成目标
add_executable(sharedptr4 sharedptr4.cpp str_blob.cpp)

# 项目信息
project (sharedptr5)
# 指定生成目标
add_executable(sharedptr5 sharedptr5.cpp)

# 项目信息
project (sharedptr6)
# 指定生成目标
add_executable(sharedptr6 sharedptr6.cpp str_blob.cpp str_blob_ptr.cpp)

project(string1)
add_executable(string1 string1.cpp)

project(factor1)
add_executable(factor1 factor1.cpp)
