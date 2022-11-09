#include "CPU/CPUTest.h"
#include "string.h"

int main(int argc, char *argv[]) {
    char *testFlag = "--test";
    if (strcmp(argv[1], testFlag) == 0) {
        printf("got into the if\n");
        TestCPU();
    }
}

void checkWhatToTest(const char *argv1) {

}