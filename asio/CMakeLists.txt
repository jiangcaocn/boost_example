cmake_minimum_required(VERSION 3.5)
project(asio)

find_package(Boost 1.64.0 REQUIRED COMPONENTS coroutine)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(steadytimer steady_timer.cpp)

add_executable(client client.cpp)
target_link_libraries(client pthread)

add_executable(timeserver time_server.cpp)

add_executable(timeservercoroutine time_server_coroutine.cpp)
target_link_libraries(timeservercoroutine ${Boost_LIBRARIES})
