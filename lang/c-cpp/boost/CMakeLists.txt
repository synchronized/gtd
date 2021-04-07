# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# aux_source_directory(. DIR_SRCS)

include_directories(".")

set(BOOST_REQUIRED_VERSION 1.67)

project (syncdemo1)
find_package(Threads)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options REQUIRED thread)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_executable(syncdemo1 syncdemo1.cpp)
target_link_libraries(syncdemo1 ${Boost_LIBRARIES})

