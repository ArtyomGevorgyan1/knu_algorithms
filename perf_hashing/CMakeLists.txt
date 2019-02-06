cmake_minimum_required(VERSION 3.13)
project(perf_hashing)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest)

include_directories(lib/googletest/googletest/include)
set(SOURCE_FILES src/main.cpp src/Commons.h src/HTLibrary.cpp src/HTLibrary.h src/Book.cpp src/Book.h src/HTFlexible.cpp
        src/HTFlexible.h)
add_executable(perf_hashing ${SOURCE_FILES})
target_link_libraries(perf_hashing gtest)
