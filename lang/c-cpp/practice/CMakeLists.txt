cmake_minimum_required(VERSION 3.23)

project(20140202 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
message("CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB files src/*.cpp)
foreach(file ${files})
    get_filename_component(name ${file} NAME_WLE)
    add_executable(${name} ${file})
endforeach()

add_subdirectory(src/example-clib01)
add_subdirectory(src/example-clib02)
add_subdirectory(src/example-stack-template01)
add_subdirectory(src/example-class-inter-hide-class01)
add_subdirectory(src/example-class-hide-multi-impl01)
