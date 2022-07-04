cmake_minimum_required(VERSION 3.23)

project(20140202 LANGUAGES C CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB files *.cpp)
foreach(file ${files})
    get_filename_component(name ${file} NAME_WLE)
    add_executable(${name} ${file})
endforeach()
