//
// Created by Bryan Herz on 08.11.22.
//

#ifndef GREYVM_C_CPU_H
#define GREYVM_C_CPU_H

#endif //GREYVM_C_CPU_H

#include "stdint.h"
#include "VM_memory.h"
#include "Instructions.h"
enum Registers {
    STACK_POINTER,
    ACCUMULATOR,
    REGISTER_1,
    REGISTER_2
};

typedef struct {
    uint8_t *registerMemory;
    uint8_t *memory;
    int memsize;
} CPU;
typedef void(*cpuVoidFuncs)(CPU*);
void resetCPU(CPU *cpu);

uint8_t fetchByte(CPU *cpu);

uint16_t fetchWord(CPU *cpu);

CPU *constructCPU(int memSize);
cpuVoidFuncs *getMemonicFunctions();
void MOV_LIT_REG(CPU *cpu);
void setRegister(CPU *cpu, int regIndex, uint8_t value);
uint8_t getRegister(CPU *cpu, int regIndex);
void freeCPU(CPU *cpu);
void execute(CPU *cpu, uint8_t instruction);
void step(CPU *cpu);