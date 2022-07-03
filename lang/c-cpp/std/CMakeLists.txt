# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (std)

# 指定生成目标
add_executable(sharedptr1 sharedptr1.cpp)

# 指定生成目标
add_executable(sharedptr2 sharedptr2.cpp)

# 指定生成目标
add_executable(sharedptr3 sharedptr3.cpp)

# 指定生成目标
add_executable(sharedptr4 sharedptr4.cpp str_blob.cpp)
target_include_directories(sharedptr4 PRIVATE ".")

# 指定生成目标
add_executable(sharedptr5 sharedptr5.cpp)

# 指定生成目标
add_executable(sharedptr6 sharedptr6.cpp str_blob.cpp str_blob_ptr.cpp)
target_include_directories(sharedptr6 PRIVATE ".")

add_executable(string1 string1.cpp)

add_executable(factor1 factor1.cpp)

add_executable(map1 map1.cpp)

# 字节对其
add_executable(align1 align1.cpp)

# 折叠
add_executable(fold_expression fold_expression.cpp)
