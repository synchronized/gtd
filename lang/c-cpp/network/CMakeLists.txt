
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

project(select5)
add_executable(select5 select5.cpp)

project(select5client)
add_executable(select5client select5_client.cpp)

project(poll1)
add_executable(poll1 poll1.c)

project(epoll1)
add_executable(epoll1 epoll1.c)

project(epoll2)
add_executable(epoll2 epoll2.c sd_epoll.c)

project(epoll1client)
add_executable(epoll1client epoll1_client.c sd_epoll.c)

project(epoll3)
add_executable(epoll3 epoll3.c)
