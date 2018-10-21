cmake_minimum_required(VERSION 3.9)
project(AbstractVM)

set(CMAKE_CXX_STANDARD 11)

add_executable(avm src/main.cpp src/AbstractVM.cpp includes/AbstractVM.hpp includes/Operand.hpp includes/IOperand.hpp src/Factory.cpp includes/Factory.hpp src/Exception.cpp includes/Exception.hpp)