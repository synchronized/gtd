
cmake_minimum_required(VERSION 2.6)

include_directories(".")

project(select1)
add_executable(select1 select1.c)

project(select2)
find_package(Threads)
add_executable(select2 select2.c)
target_link_libraries(select2 ${CMAKE_THREAD_LIBS_INIT})

project(select3)
find_package(Threads)
add_executable(select3 select3.c)
target_link_libraries(select3 ${CMAKE_THREAD_LIBS_INIT})

project(select4)
add_executable(select4 select4.c)

project(select4client)
add_executable(select4client select4_client.c)

# project(epoll)
# add_executable(epoll epoll.c)
