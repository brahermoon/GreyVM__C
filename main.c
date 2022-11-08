#include <stdio.h>
#include "VM_memory.h"
#include "CPU.h"
#include "Instructions.h"

int main() {
    CPU *cpu = constructCPU(32);
    printf("cpu construct works\n");
    int i = 0;
    cpu->memory[i++] = MOV_LIT_REG_OP;
    cpu->memory[i++] = 11;
    cpu->memory[i++] = REGISTER_1;
    cpu->memory[i++] = MOV_LIT_REG_OP;
    cpu->memory[i++] = 13;
    cpu->memory[i++] = REGISTER_2;
    cpu->memory[i++] = ADD_REG_REG_OP;
    cpu->memory[i++] = REGISTER_1;
    cpu->memory[i++] = REGISTER_2;
    step(cpu);
    step(cpu);
    step(cpu);
    step(cpu);
    printf("%d\n", getRegister(cpu, REGISTER_1));
    printf("%d\n", getRegister(cpu, REGISTER_2));
    printf("%d\n", getRegister(cpu, ACCUMULATOR));
    freeCPU(cpu);
}