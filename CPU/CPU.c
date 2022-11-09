//
// Created by Bryan Herz on 08.11.22.
//

#include "CPU.h"

uint16_t getRegister(CPU *cpu, int regIndex) {
    uint8_t firstByte = cpu->registerMemory[regIndex];
    uint8_t secondByte = cpu->registerMemory[regIndex + 1];
    uint16_t wd = (uint16_t) (firstByte << 8 | secondByte);
    if (cpu->debug) {
        printf("In getRegister\n");
        printf("firstbyte: %hx \n", firstByte);
        printf("secondbyte: %hx \n", secondByte);
        printf("Register index: %d \n", regIndex);
    }
    return wd;
}

void setRegister(CPU *cpu, int regIndex, uint16_t value) {
    uint8_t valPart1 = (uint8_t) value >> 8;
    uint8_t valPart2 = (uint8_t) value;
    cpu->registerMemory[regIndex] = valPart1;
    cpu->registerMemory[regIndex + 1] = valPart2;
    if (cpu->debug) {
        printf("In setRegister\n");
        printf("regIndex: %d\n", regIndex);
        printf("valPart1 : %hhx\n", valPart1);
        printf("valPart2 : %hhx\n", valPart2);
    }
}

void MOV_LIT_REG(CPU *cpu) {
    uint16_t litetal = fetchByte(cpu);
    uint16_t registeR = fetchWord(cpu);
    setRegister(cpu, registeR, litetal);
    if (cpu->debug) {
        printf("In MOV_LIT_REG\n");
        printf("literal Val: %hx\n", litetal);
    }
}

void ADD_REG_REG(CPU *cpu) {
    uint16_t registeR1 = fetchWord(cpu);
    uint16_t firstReg = getRegister(cpu, registeR1);
    uint16_t registeR2 = fetchWord(cpu);
    uint16_t secodReg = getRegister(cpu, registeR2);
    uint16_t value = (uint16_t) firstReg + secodReg;
    setRegister(cpu, ACCUMULATOR, value);
    if (cpu->debug) {
        printf("In ADD_REG_REG\n");
        printf("ACCUMULATOR REGISTERS GOT: %d\n", value);
    }
}

void ADD_LIT_REG(CPU *cpu) {
    uint16_t litetal = fetchByte(cpu);
    uint16_t registeR = fetchWord(cpu);
    uint16_t value = (uint16_t) litetal + getRegister(cpu, registeR);
    setRegister(cpu, ACCUMULATOR, value);
    if (cpu->debug) {
        printf("In ADD_LIT_REG\n");
        printf("literal Val: %hx\n", litetal);
        printf("ACCUMULATOR REGISTERS GOT: %d\n", value);
    }
}

void MOV_REG_REG(CPU *cpu) {
    uint16_t registeR1 = fetchWord(cpu);
    uint16_t firstReg = getRegister(cpu, registeR1);
    uint16_t registeR2 = fetchWord(cpu);
    setRegister(cpu, registeR2, firstReg);
    if (cpu->debug) {
        printf("In MOV_REG_REG\n");
    }
}

void HLT(CPU *cpu) {
    cpu->halt = true;
    if (cpu->debug) {
        printf("In HLT\n");
    }
}

void DBG(CPU *cpu) {
    if (cpu->debug) {
        printf("In DBG");
    }
    cpu->debug = !cpu->debug;
}

void MOV_LIT_MEM(CPU *cpu) {
    uint8_t litetal = fetchByte(cpu);
    uint16_t memLocation = fetchWord(cpu);
    cpu->memory[memLocation] = litetal;
    if (cpu->debug) {
        printf("In MOV_LIT_MEM\n");
    }
}

void MOV_REG_MEM(CPU *cpu) {
    uint16_t registeR = fetchWord(cpu);
    uint16_t RegVal = getRegister(cpu, registeR);
    uint16_t memLocation = fetchWord(cpu);
    cpu->memory[memLocation] = RegVal;
    if (cpu->debug) {
        printf("In MOV_REG_MEM\n");
    }
}

void MOV_MEM_REG(CPU *cpu) {
    uint16_t memLocation = fetchWord(cpu);
    uint8_t memVal = cpu->memory[memLocation];
    uint16_t registeR = fetchWord(cpu);
    setRegister(cpu, registeR, memVal);
    if (cpu->debug) {
        printf("In MOV_MEM_REG\n");
    }
}

void MOV_MEM_MEM(CPU *cpu) {
    uint16_t memLocation = fetchWord(cpu);
    uint8_t memVal = cpu->memory[memLocation];
    uint16_t memLocation2 = fetchWord(cpu);
    cpu->memory[memLocation2] = memVal;
    if (cpu->debug) {
        printf("In MOV_MEM_REG\n");
        printf("MEM1_Location : %d", memLocation);
        printf("MEM1_Val : %d", memVal);
        printf("MEM2_Location : %d", memLocation2);
    }
}

cpuVoidFuncs *getMemonicFunctions() {
    cpuVoidFuncs *func = malloc((sizeof(Instructions) / sizeof(uint16_t)) * sizeof(cpuVoidFuncs));
    func[MOV_LIT_MEM_OP] = &MOV_LIT_MEM;
    func[MOV_REG_MEM_OP] = &MOV_REG_MEM;
    func[MOV_MEM_REG_OP] = &MOV_MEM_REG;
    func[MOV_LIT_REG_OP] = &MOV_LIT_REG;
    func[MOV_REG_REG_OP] = &MOV_REG_REG;
    func[ADD_REG_REG_OP] = &ADD_REG_REG;
    func[MOV_MEM_MEM_OP] = &MOV_MEM_MEM;
    func[ADD_LIT_REG_OP] = &ADD_LIT_REG;
    func[DBG_OP] = &DBG;
    func[HLT_OP] = &HLT;
    return func;
}

void resetCPU(CPU *cpu) {
    setRegister(cpu, STACK_POINTER, 0);
    setRegister(cpu, ACCUMULATOR, 0);
    setRegister(cpu, REGISTER_1, 0);
    setRegister(cpu, REGISTER_2, 0);
    resetMemory(cpu->memory, cpu->memsize);
    if (cpu->debug) {
        printf("In resetCPU\n");
    }
}


uint8_t fetchByte(CPU *cpu) {
    uint8_t instruction = cpu->memory[cpu->registerMemory[STACK_POINTER]];
    cpu->registerMemory[STACK_POINTER]++;
    if (cpu->debug) {
        printf("In fetchByte\n");
    }
    return instruction;
}

uint16_t fetchWord(CPU *cpu) {
    uint8_t firstByte = fetchByte(cpu);
    uint8_t secondByte = fetchByte(cpu);
    uint16_t wd = (uint16_t) (firstByte << 8 | secondByte);
    if (cpu->debug) {
        printf("In fetchWord\n");
    }
    return wd;
}

CPU *constructCPU(int memSize, bool debug) {
    printf("begin cpu construct\n");
    uint8_t *memory = createMemory(memSize);
    CPU *cpu = malloc(sizeof(CPU));
    cpu->debug = debug;
    cpu->registerMemory = createMemory(sizeof(Instructions) * 2);
    cpu->memory = memory;
    cpu->memsize = memSize;
    cpu->halt = false;
    if (cpu->debug) {
        printf("set all members of cpu\n");
        resetCPU(cpu);
        printf("reseted registers and memory\n");
    } else {
        resetCPU(cpu);
    }
    return cpu;
}

void freeCPU(CPU *cpu) {
    if (cpu->debug) {
        printf("In freeCPU\n");
    }
    free(cpu);

}

void execute(CPU *cpu, uint8_t instruction) {
    if (cpu->debug) {
        printf("In execute\n");
    }
    cpuVoidFuncs *funcs = getMemonicFunctions();
    funcs[instruction](cpu);
    free(funcs);
}

void step(CPU *cpu) {
    uint8_t instruction = fetchByte(cpu);
    if (cpu->debug) {
        printf("In step\n");
        printf("Instruction is: %d\n", instruction);
    }
    execute(cpu, instruction);
}

void run(CPU *cpu) {
    if (cpu->debug) {
        printf("RUn ran\n");
    }
    while (!cpu->halt) {
        step(cpu);
    }
}

void loadProgramm(CPU *cpu, const uint8_t *programmArray, int size) {

    for (int i = 0; i < size; i++) {
        cpu->memory[i] = programmArray[i];
    }
}