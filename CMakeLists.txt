cmake_minimum_required(VERSION 3.23)
project(GreyVM_C C)

set(CMAKE_C_STANDARD 99)

add_executable(GreyVM_C main.c VM_memory.c VM_memory.h CPU.c CPU.h Instructions.c Instructions.h)
