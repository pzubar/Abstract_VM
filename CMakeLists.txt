cmake_minimum_required(VERSION 3.9)
project(avm)

set(CMAKE_CXX_STANDARD 17)

add_executable(avm main.cpp AbstractVM.cpp AbstractVM.hpp Operand.cpp Operand.hpp)