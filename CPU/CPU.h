//
// Created by Bryan Herz on 08.11.22.
//
#pragma once
#ifndef GREYVM_C_CPU_H
#define GREYVM_C_CPU_H

#endif //GREYVM_C_CPU_H

#include <stdbool.h>
#include <stdint.h>
#include "../VM_memory/VM_memory.h"
#include "../Instructions.h"

enum Registers {
    STACK_POINTER = 0,
    ACCUMULATOR = 2,
    REGISTER_1 = 4,
    REGISTER_2 = 6
};

typedef struct {
    uint8_t *registerMemory;
    uint8_t *memory;
    int memsize;
    bool halt;
    bool debug;
} CPU;

typedef void(*cpuVoidFuncs)(CPU *cpu);

void resetCPU(CPU *cpu);

uint8_t fetchByte(CPU *cpu);

uint16_t fetchWord(CPU *cpu);

CPU *constructCPU(int memSize, bool debug);

cpuVoidFuncs *getMemonicFunctions();

void MOV_LIT_REG(CPU *cpu);

void setRegister(CPU *cpu, int regIndex, uint16_t value);

uint16_t getRegister(CPU *cpu, int regIndex);

void freeCPU(CPU *cpu);

void execute(CPU *cpu, uint8_t instruction);

void step(CPU *cpu);

void run(CPU *cpu);

void loadProgramm(CPU *cpu, const uint8_t *programmArray, int size);