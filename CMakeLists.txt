cmake_minimum_required(VERSION 3.9)
project(DirectedGraphHandler)

set(CMAKE_CXX_STANDARD 98)

add_executable(DirectedGraphHandler main.cpp util_vector.h util_stack.h directed_graph.h)