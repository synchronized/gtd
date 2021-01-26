# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# aux_source_directory(. DIR_SRCS)

include_directories(".")

# 项目信息
project (demo1)
# 指定生成目标
add_executable(demo1 main1.cpp)

# 项目信息
project (demo2)
# 指定生成目标
add_executable(demo2 main2.cpp)

# 项目信息
project (demo3)
# 指定生成目标
add_executable(demo3 main3.cpp)

# 项目信息
project (demo4)
# 指定生成目标
add_executable(demo4 main4.cpp str_blob.cpp)

# 项目信息
project (demo5)
# 指定生成目标
add_executable(demo5 main5.cpp)

# 项目信息
project (demo6)
# 指定生成目标
add_executable(demo6 main6.cpp str_blob.cpp str_blob_ptr.cpp)
