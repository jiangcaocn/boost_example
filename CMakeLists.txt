cmake_minimum_required(VERSION 3.8)
project(boost_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ENV{BOOST_ROOT} /opt/boost)
add_definitions(-DBOOST_LOG_DYN_LINK=1)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY=1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(asio)
add_subdirectory(log)
