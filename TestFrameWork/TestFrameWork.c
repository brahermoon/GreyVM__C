//
// Created by Bryan Herz on 08.11.22.
//

#include "TestFrameWork.h"

TestCase *createTestCase(char *name) {
    TestCase *testCase = malloc(sizeof(TestCase));
    testCase->name = name;
    return testCase;
}

bool assertEquals(bool any) {
    if (any) {
        return true;
    } else {
        return false;
    }
}

void printTest(TestCase *testCase, char *description, bool test) {
    if (test) {
        printf("%s : %s PASSED\n", testCase->name, description);
    } else {
        printf("%s : %s FAILED\n", testCase->name, description);
    }
}

void freeTestCase(TestCase *testCase) {
    free(testCase);
}
