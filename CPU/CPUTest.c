//
// Created by Bryan Herz on 08.11.22.
//

#include "CPUTest.h"

void TestCPU() {
    uint8_t programmArray[256];
    resetMemory(programmArray, 256);
    int memSize = 256;
    TestCase *CPUTest = createTestCase("CPUTest");
    CPU *cpu = constructCPU(memSize, false);
    int i = 0;
    programmArray[i++] = MOV_LIT_REG_OP;
    programmArray[i++] = 11;
    programmArray[i++] = REGISTER_1 >> 24;
    programmArray[i++] = REGISTER_1;

    programmArray[i++] = MOV_LIT_REG_OP;
    programmArray[i++] = 13;
    programmArray[i++] = REGISTER_2 >> 24;
    programmArray[i++] = REGISTER_2;

    programmArray[i++] = ADD_REG_REG_OP;
    programmArray[i++] = REGISTER_1 >> 24;
    programmArray[i++] = REGISTER_1;
    programmArray[i++] = REGISTER_2 >> 24;
    programmArray[i++] = REGISTER_2;

    programmArray[i++] = MOV_REG_REG_OP;
    programmArray[i++] = ACCUMULATOR >> 24;
    programmArray[i++] = ACCUMULATOR;
    programmArray[i++] = REGISTER_1 >> 24;
    programmArray[i++] = REGISTER_1;

    programmArray[i++] = MOV_LIT_MEM_OP;
    programmArray[i++] = 200;
    programmArray[i++] = 0x00;
    programmArray[i++] = 0xFF;

    programmArray[i++] = MOV_REG_MEM_OP;
    programmArray[i++] = ACCUMULATOR >> 24;
    programmArray[i++] = ACCUMULATOR;
    programmArray[i++] = 0x00;
    programmArray[i++] = 0xFF;

    programmArray[i++] = ADD_LIT_REG_OP;
    programmArray[i++] = 70;
    programmArray[i++] = REGISTER_1 >> 24;
    programmArray[i++] = REGISTER_1;

    programmArray[i++] = INC_OP;
    programmArray[i++] = REGISTER_1 >> 24;
    programmArray[i++] = REGISTER_1;

    programmArray[i++] = DEC_OP;
    programmArray[i++] = REGISTER_2 >> 24;
    programmArray[i++] = REGISTER_2;

    programmArray[i++] = JMP_LIT_OP;
    programmArray[i++] = 41;

    programmArray[i++] = DBG_OP;

    programmArray[i++] = HLT_OP;

    programmArray[i++] = MOV_LIT_REG_OP;
    programmArray[i++] = 39;
    programmArray[i++] = REGISTER_1 >> 24;
    programmArray[i++] = REGISTER_1;

    programmArray[i++] = JMP_REG_OP;
    programmArray[i++] = REGISTER_1 >> 24;
    programmArray[i++] = REGISTER_1;

    loadProgramm(cpu, programmArray, 256);

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

    uint16_t prevR1 = getRegister(cpu, REGISTER_1);
    step(cpu);
    printTest(CPUTest, "test that the value of r1 is equal to the previous value +1",
              assertEquals(getRegister(cpu, REGISTER_1) == prevR1 + 1));

    uint16_t prevR2 = getRegister(cpu, REGISTER_2);
    step(cpu);
    printTest(CPUTest, "test that the value of r1 is equal to the previous value -1",
              assertEquals(getRegister(cpu, REGISTER_2) == prevR2 - 1));

    step(cpu);
    printTest(CPUTest, "test that the value of INSTRUCTION_POINTER (ip) is 41",
              assertEquals(getRegister(cpu, INSTRUCTION_POINTER) == 41));

    step(cpu);
    printTest(CPUTest, "test that register r1 is set to 39",
              assertEquals(getRegister(cpu, REGISTER_1) == (uint16_t) 39));

    step(cpu);
    printTest(CPUTest, "test that the value of INSTRUCTION_POINTER (ip) is same as REGISTER1",
              assertEquals(getRegister(cpu, INSTRUCTION_POINTER) == getRegister(cpu, REGISTER_1)));
    step(cpu);
    printTest(CPUTest, "test that the debug flag is set to true", assertEquals(cpu->debug == true));

    step(cpu);
    printTest(CPUTest, "test that halt is true", assertEquals(cpu->halt == true));

    freeCPU(cpu);
    freeTestCase(CPUTest);
}

