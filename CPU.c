//
// Created by Bryan Herz on 08.11.22.
//

#include "CPU.h"

uint8_t getRegister(CPU *cpu, int regIndex) {
    return cpu->registerMemory[regIndex];
}

void setRegister(CPU *cpu, int regIndex, uint8_t value) {
    cpu->registerMemory[regIndex] = value;
}

void MOV_LIT_REG(CPU *cpu) {
    printf("In MOV_LIT_REG");
    uint8_t litetal = fetchByte(cpu);
    printf("literal Val: %d\n", litetal);
    int registeR = fetchByte(cpu);
    setRegister(cpu, registeR, litetal);
}

void ADD_REG_REG(CPU *cpu) {
    int registeR1 = fetchByte(cpu);
    int firstReg = getRegister(cpu, registeR1);
    int registeR2 = fetchByte(cpu);
    int secodReg = getRegister(cpu, registeR2);
    uint8_t value = (uint8_t) firstReg + secodReg;
    printf("ADD REGISTERS GOT: %d\n", value);
    setRegister(cpu, ACCUMULATOR, value);
}

cpuVoidFuncs *getMemonicFunctions() {
    cpuVoidFuncs *func = malloc((sizeof(Instructions) / sizeof(int)) * sizeof(cpuVoidFuncs));
    func[MOV_LIT_REG_OP] = &MOV_LIT_REG;
    func[ADD_REG_REG_OP] = &ADD_REG_REG;
    return func;
}

void resetCPU(CPU *cpu) {
    cpu->registerMemory[STACK_POINTER] = 0;
    cpu->registerMemory[ACCUMULATOR] = 0;
    cpu->registerMemory[REGISTER_1] = 0;
    cpu->registerMemory[REGISTER_2] = 0;
    resetMemory(cpu->memory, cpu->memsize);
}


uint8_t fetchByte(CPU *cpu) {

    uint8_t instruction = cpu->memory[cpu->registerMemory[STACK_POINTER]];
    cpu->registerMemory[STACK_POINTER]++;
    return instruction;
}

uint16_t fetchWord(CPU *cpu) {
    uint8_t firstByte = fetchByte(cpu);
    uint8_t secondByte = fetchByte(cpu);
    uint16_t wd = ((uint16_t) firstByte << 8) | secondByte;
    return wd;
}

CPU *constructCPU(int memSize) {
    printf("begin cpu construct");
    uint8_t *memory = createMemory(memSize);
    CPU *cpu = malloc(sizeof(cpu));
    cpu->registerMemory = createMemory(4);
    resetCPU(cpu);
    cpu->memory = memory;
    cpu->memsize = memSize;
    return cpu;
}

void freeCPU(CPU *cpu) {
    free(cpu);
}

void execute(CPU *cpu, uint8_t instruction) {
    printf("In execute\n");
    cpuVoidFuncs *funcs = getMemonicFunctions();
    funcs[instruction](cpu);
    free(funcs);
}

void step(CPU *cpu) {
    uint8_t instruction = fetchByte(cpu);
    printf("Instruction is: %d\n", instruction);
    execute(cpu, instruction);
}