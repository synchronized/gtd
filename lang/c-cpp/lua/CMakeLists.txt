cmake_minimum_required(VERSION 3.23)

project(cpp-lua)

add_subdirectory(external/lua)

file(GLOB sources src/*.cpp)

foreach(cppfile ${sources})
    get_filename_component(fname "${cppfile}" NAME_WLE)
    message("cppfile:${cppfile} fname:${fname}")
    add_executable("${fname}")
    target_sources("${fname}" PRIVATE "${cppfile}")
    target_link_libraries("${fname}" PRIVATE lua::lib lua::header)
endforeach()
