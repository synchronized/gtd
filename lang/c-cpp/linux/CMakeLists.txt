
cmake_minimum_required(VERSION 2.6)

include_directories(".")

project(linux)
add_executable(select1 select1.c)

find_package(Threads)
add_executable(select2 select2.c)
target_link_libraries(select2 ${CMAKE_THREAD_LIBS_INIT})

find_package(Threads)
add_executable(select3 select3.c)
target_link_libraries(select3 ${CMAKE_THREAD_LIBS_INIT})

add_executable(select4 select4.c)

add_executable(select4client select4_client.c)

add_executable(select5 select5.cpp)

add_executable(select5client select5_client.cpp)

add_executable(poll1 poll1.c)

add_executable(poll2 poll2.c)

add_executable(epoll1 epoll1.c)

add_executable(epoll2 epoll2.c sd_epoll.c)

add_executable(epoll1client epoll1_client.c sd_epoll.c)

add_executable(epoll3 epoll3.c sd_buffer.c)

add_executable(epoll4 epoll4.c sd_buffer.c sd_epoll.c)
target_link_libraries(epoll4 ${CMAKE_THREAD_LIBS_INIT})

add_executable(epoll5 epoll5.c)

add_executable(sd_thread_pool_test sd_thread_pool_test.c sd_thread_pool.c)
target_link_libraries(sd_thread_pool_test ${CMAKE_THREAD_LIBS_INIT})


find_package(Threads)
add_executable(thraed1 thread1.c)
target_link_libraries(thraed1 ${CMAKE_THREAD_LIBS_INIT})

find_package(Threads)
add_executable(thraed2 thread2.c)
target_link_libraries(thraed2 ${CMAKE_THREAD_LIBS_INIT})
