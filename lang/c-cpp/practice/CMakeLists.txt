cmake_minimum_required(VERSION 3.23)

project(20140202 LANGUAGES C CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB files *.cpp)
foreach(file ${files})
    get_filename_component(name ${file} NAME_WLE)
    add_executable(${name} ${file})
endforeach()

add_subdirectory(example-clib01)
add_subdirectory(example-clib02)
add_subdirectory(example-stack-template01)
add_subdirectory(class-inter-hide-class01)
add_subdirectory(example-class-hide-multi-impl01)
