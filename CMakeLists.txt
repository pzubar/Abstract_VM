cmake_minimum_required(VERSION 3.9)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 11)

add_executable(avm main.cpp AbstractVM.cpp AbstractVM.hpp Operand.tpp IOperand.hpp Factory.cpp Factory.hpp Exception.cpp Exception.hpp)