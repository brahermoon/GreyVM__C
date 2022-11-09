//
// Created by Bryan Herz on 08.11.22.
//

#include "CPUTest.h"

void TestCPU() {
    int memSize = 256;
    TestCase *CPUTest = createTestCase("CPUTest");
    CPU *cpu = constructCPU(memSize, false);
    int i = 0;
    cpu->memory[i++] = MOV_LIT_REG_OP;
    cpu->memory[i++] = 11;
    cpu->memory[i++] = REGISTER_1 >> 24;
    cpu->memory[i++] = REGISTER_1;

    cpu->memory[i++] = MOV_LIT_REG_OP;
    cpu->memory[i++] = 13;
    cpu->memory[i++] = REGISTER_2 >> 24;
    cpu->memory[i++] = REGISTER_2;

    cpu->memory[i++] = ADD_REG_REG_OP;
    cpu->memory[i++] = REGISTER_1 >> 24;
    cpu->memory[i++] = REGISTER_1;
    cpu->memory[i++] = REGISTER_2 >> 24;
    cpu->memory[i++] = REGISTER_2;

    cpu->memory[i++] = MOV_REG_REG_OP;
    cpu->memory[i++] = ACCUMULATOR >> 24;
    cpu->memory[i++] = ACCUMULATOR;
    cpu->memory[i++] = REGISTER_1 >> 24;
    cpu->memory[i++] = REGISTER_1;

    cpu->memory[i++] = MOV_LIT_MEM_OP;
    cpu->memory[i++] = 200;
    cpu->memory[i++] = 0x00;
    cpu->memory[i++] = 0xFF;

    cpu->memory[i++] = MOV_REG_MEM_OP;
    cpu->memory[i++] = ACCUMULATOR >> 24;
    cpu->memory[i++] = ACCUMULATOR;
    cpu->memory[i++] = 0x00;
    cpu->memory[i++] = 0xFF;

    cpu->memory[i++] = ADD_LIT_REG_OP;
    cpu->memory[i++] = 70;
    cpu->memory[i++] = REGISTER_1 >> 24;
    cpu->memory[i++] = REGISTER_1;

    cpu->memory[i++] = DBG_OP;

    cpu->memory[i++] = HLT_OP;

    step(cpu);
    printTest(CPUTest, "test that register r1 is set to 11",
              assertEquals(getRegister(cpu, REGISTER_1) == (uint16_t) 11));
    step(cpu);
    printTest(CPUTest, "test that register r2 is set to 13",
              assertEquals(getRegister(cpu, REGISTER_2) == (uint16_t) 13));
    step(cpu);
    printTest(CPUTest, "test that register acc is set to 24",
              assertEquals(getRegister(cpu, ACCUMULATOR) == (uint16_t) 24));
    step(cpu);
    printTest(CPUTest, "test that register r1 is equal to acc", assertEquals(getRegister(cpu, REGISTER_1) ==
                                                                             getRegister(cpu, ACCUMULATOR)));
    step(cpu);
    printTest(CPUTest, "test that 200 gets saved at position 0x00FF in memory",
              assertEquals(cpu->memory[0x00FF] == 200));
    step(cpu);
    printTest(CPUTest, "test that the value of acc gets saved at position 0x00FF in memory",
              assertEquals(cpu->memory[0x00FF] == getRegister(cpu, ACCUMULATOR)));
    step(cpu);
    printTest(CPUTest, "test that the acc register contains the sum of r1 and 70",
              assertEquals(getRegister(cpu, ACCUMULATOR) ==
                           getRegister(cpu, REGISTER_1) + 70));
    step(cpu);
    printTest(CPUTest, "test that the debug flag is set to true", assertEquals(cpu->debug == true));
    step(cpu);
    printTest(CPUTest, "test that halt is false", assertEquals(cpu->halt == true));
    freeCPU(cpu);
    freeTestCase(CPUTest);
}

