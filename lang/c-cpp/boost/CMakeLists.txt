# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# aux_source_directory(. DIR_SRCS)

include_directories(".")

set(BOOST_REQUIRED_VERSION 1.67)

project (syncdemo1)
find_package(Threads)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(syncdemo1 syncdemo1.cpp)
target_link_libraries(syncdemo1 ${Boost_LIBRARIES})

project (io_context1)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(io_context1 io_context1.cpp)
target_link_libraries(io_context1 ${Boost_LIBRARIES})

project (timer1)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(timer1 timer1.cpp)
target_link_libraries(timer1 ${Boost_LIBRARIES})

project (timer2)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(timer2 timer2.cpp)
target_link_libraries(timer2 ${Boost_LIBRARIES})

project (timer5_multithread)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(timer5_multithread timer5_multithread_1.6.7.cpp)
target_link_libraries(timer5_multithread ${Boost_LIBRARIES})

project (asio_resolver_client)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(asio_resolver_client asio_resolver_client.cpp)
target_link_libraries(asio_resolver_client ${Boost_LIBRARIES})

project (asio_resolver_server)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(asio_resolver_server asio_resolver_server.cpp)
target_link_libraries(asio_resolver_server ${Boost_LIBRARIES})

project (asio_sync_echo_server)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(asio_sync_echo_server asio_sync_echo_server.cpp)
target_link_libraries(asio_sync_echo_server ${Boost_LIBRARIES})

project (asio_async_echo_server)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(asio_async_echo_server asio_async_echo_server.cpp)
target_link_libraries(asio_async_echo_server ${Boost_LIBRARIES})

project (asio_sync_echo_client)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(asio_sync_echo_client asio_sync_echo_client.cpp)
target_link_libraries(asio_sync_echo_client ${Boost_LIBRARIES})

project (asio_async_echo_client)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(asio_async_echo_client asio_async_echo_client.cpp)
target_link_libraries(asio_async_echo_client ${Boost_LIBRARIES})

project (asio_async_daytime_server)
find_package(Boost ${BOOST_REQUIRED_VERSION} COMPONENTS program_options thread)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
add_executable(asio_async_daytime_server asio_async_daytime_server.cpp)
target_link_libraries(asio_async_daytime_server ${Boost_LIBRARIES})
