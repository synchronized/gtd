
project(example-class-hide-multi-impl01)

add_executable(example-class-hide-multi-impl-array)
target_include_directories(example-class-hide-multi-impl-array PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(example-class-hide-multi-impl-array PRIVATE main.cpp StackImpOfArray.cpp)

add_executable(example-class-hide-multi-impl-vector)
target_include_directories(example-class-hide-multi-impl-vector PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_sources(example-class-hide-multi-impl-vector PRIVATE main.cpp StackImpOfVector.cpp)
