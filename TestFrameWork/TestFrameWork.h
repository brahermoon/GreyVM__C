//
// Created by Bryan Herz on 08.11.22.
//

#include <stdbool.h>

#ifndef GREYVM_C_TESTFRAMEWORK_H
#define GREYVM_C_TESTFRAMEWORK_H

#endif //GREYVM_C_TESTFRAMEWORK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *name;
} TestCase;
TestCase *createTestCase(char *name);
bool assertEquals(bool any);
void printTest(TestCase *testCase, char *description, bool test);
void freeTestCase(TestCase *testCase);