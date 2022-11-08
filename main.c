#include <stdio.h>
#include "VM_memory.h"
#include "CPU.h"
#include "Instructions.h"

int main() {
    CPU *cpu = constructCPU(32);
    printf("cpu construct works\n");
    cpu->memory[0] = MOV_LIT_REG_OP;
    cpu->memory[1] = 11;
    cpu->memory[2] = REGISTER_1;
    cpu->memory[3] = MOV_LIT_REG_OP;
    cpu->memory[4] = 13;
    cpu->memory[5] = REGISTER_2;
    cpu->memory[6] = ADD_REG_REG_OP;
    cpu->memory[7] = REGISTER_1;
    cpu->memory[8] = REGISTER_2;
    step(cpu);
    step(cpu);
    step(cpu);
    step(cpu);
    printf("%d\n", getRegister(cpu, REGISTER_1));
    printf("%d\n", getRegister(cpu, REGISTER_2));
    printf("%d\n", getRegister(cpu, ACCUMULATOR));
    freeCPU(cpu);
}