cmake_minimum_required(VERSION 3.23)
project(GreyVM_C C)

set(CMAKE_C_STANDARD 99)

add_executable(GreyVM_C main.c VM_memory/VM_memory.c VM_memory/VM_memory.h CPU/CPU.c CPU/CPU.h Instructions.c Instructions.h TestFrameWork/TestFrameWork.c TestFrameWork/TestFrameWork.h CPU/CPUTest.c CPU/CPUTest.h)
