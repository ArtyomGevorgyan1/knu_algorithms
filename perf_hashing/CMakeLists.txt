cmake_minimum_required(VERSION 3.13)
project(perf_hashing)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)
set(SOURCE_FILES main.cpp)
add_executable(perf_hashing ${SOURCE_FILES})
target_link_libraries(perf_hashing gtest gtest_main)