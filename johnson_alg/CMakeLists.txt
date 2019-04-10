cmake_minimum_required(VERSION 3.13)
project(johnson_alg)

set(CMAKE_CXX_STANDARD 14)

add_executable(johnson_alg main.cpp Graph.cpp Graph.h Book.cpp Book.h FH.h List.h)