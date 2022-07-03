cmake_minimum_required(VERSION 3.23)

project(20140202 LANGUAGES C CXX)

file(GLOB files *.cpp)
foreach(file ${files})
    get_filename_component(name ${file} NAME_WLE)
    add_executable(${name} ${file})
endforeach()
