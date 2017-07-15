cmake_minimum_required(VERSION 3.8)
project(log)

find_package(Boost 1.64.0 REQUIRED COMPONENTS log thread filesystem system)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES log.cpp)
add_executable(log ${SOURCE_FILES})
target_link_libraries(log ${Boost_LIBRARIES} pthread)
